# Copyright 2023 Klepsydra Technologies AG
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.


SET(PROJ_NAME kpsr_benchmark_core_test)
PROJECT(${PROJ_NAME})

# Source
#---------------------------------------------------#
FILE(GLOB ${PROJ_NAME}_SRC
    "src/*.cpp"
)

# Create Library
#---------------------------------------------------#
ADD_EXECUTABLE(${PROJ_NAME} ${${PROJ_NAME}_HEADERS} ${${PROJ_NAME}_SRC} )

TARGET_LINK_LIBRARIES(${PROJ_NAME} PUBLIC kpsr_core benchmark benchmark_main gtest)

TARGET_INCLUDE_DIRECTORIES(${PROJ_NAME}
    PRIVATE
    ${GBENCHMARK_PATH}/include
    ${GBENCHMARK_PATH}/include/benchmark
    )

