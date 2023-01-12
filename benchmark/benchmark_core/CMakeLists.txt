
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

