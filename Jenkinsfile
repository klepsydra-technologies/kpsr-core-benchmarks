pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Pull dependencies from repository'
                sh 'rm  ~/.dockercfg || true'
                sh 'rm ~/.docker/config.json || true'

                script {
                    docker.withRegistry("https://337955887028.dkr.ecr.us-east-2.amazonaws.com/kpsr-docker-registry/kpsr-serialization:ubuntu_18_04", "ecr:us-east-2:AWS_ECR_CREDENTIALS") {
                    docker.image("337955887028.dkr.ecr.us-east-2.amazonaws.com/kpsr-docker-registry/kpsr-serialization:ubuntu_18_04").pull()
                    docker.image("337955887028.dkr.ecr.us-east-2.amazonaws.com/kpsr-docker-registry/kpsr-thirdparties").pull()
                    }
                }

                sh 'docker tag 337955887028.dkr.ecr.us-east-2.amazonaws.com/kpsr-docker-registry/kpsr-serialization:ubuntu_18_04 kpsr-serialization:latest'
                sh 'docker tag 337955887028.dkr.ecr.us-east-2.amazonaws.com/kpsr-docker-registry/kpsr-thirdparties kpsr-thirdparties:latest'

                sh 'docker build -f Dockerfile . --build-arg="BUILD_ID=${BUILD_ID}" --no-cache'

                sh 'container_id=$(docker create $(docker images -a -f "label=kpsr-core=builder" -f  "label=BUILD_ID=${BUILD_ID}" --format "{{.ID}}")) && \
                    docker cp $container_id:/opt/kpsr-core/build/copy_cppcheck.sh . && \
                    bash copy_cppcheck.sh $container_id && \
                    docker cp $container_id:/opt/kpsr-core/build/coverage.xml . && \
                    docker cp $container_id:/opt/kpsr-core/build/code_generator/kpsr_codegen/coverage.xml code_generator/kpsr_codegen && \
                    sed -i -e "s@[./]opt[./]kpsr-core[./]@@g" code_generator/kpsr_codegen/coverage.xml'

                // Pruning
                sh 'docker container prune --force --filter label=kpsr-core=builder  --filter  label=BUILD_ID=${BUILD_ID}'
                sh 'docker image prune --force --filter label=kpsr-core=builder  --filter  label=BUILD_ID=${BUILD_ID}'

                // Run cppcheck
                publishCppcheck(
                    pattern: '**/cppcheck-result.xml',
                    ignoreBlankFiles: false, threshold: '19',
                    allowNoReport: false,
                    newThreshold: '', failureThreshold: '',
                    newFailureThreshold: '', healthy: '', unHealthy: '',
                    severityError: true,
                    severityWarning: true,
                    severityStyle: true,
                    severityPerformance: true,
                    severityInformation: true,
                    severityNoCategory: true,
                    severityPortability: true,
                    XSize: 1000, YSize: 200,
                    numBuildsInGraph: 0,
                    displayAllErrors: true,
                    displayErrorSeverity: true,
                    displayNoCategorySeverity: true,
                    displayPerformanceSeverity: true,
                    displayPortabilitySeverity: true,
                    displayStyleSeverity: true,
                    displayWarningSeverity: true
                )

                cobertura(coberturaReportFile: 'coverage.xml,code_generator/kpsr_codegen/coverage.xml', failUnhealthy: false, failUnstable: false, onlyStable: false)

            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
    }
}



