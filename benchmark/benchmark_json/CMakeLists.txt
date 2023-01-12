
SET(PROJ_NAME_JSON kpsr_benchmark_json_test)
PROJECT(${PROJ_NAME_JSON})
SET(PROJ_NAME_TEST kpsr_gtest_json_test)

# Source
#---------------------------------------------------#
FILE(GLOB ${PROJ_NAME_JSON}_HEADERS
    "include/Bm*.h"
)
FILE(GLOB ${PROJ_NAME_TEST}_SRC
    "tests/*.cpp"
)

# Create Library
#---------------------------------------------------#
ADD_LIBRARY(SerializationBenchmarkUtils SHARED 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/SerializationBenchmarkUtils.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/VectorFloatStruct.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/VectorFloatStruct4Yas.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/VectorFloatStruct4Pods.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/VectorFloatStruct4Cereal.h 
    )

TARGET_INCLUDE_DIRECTORIES(SerializationBenchmarkUtils
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

SET_TARGET_PROPERTIES(SerializationBenchmarkUtils PROPERTIES LINKER_LANGUAGE CXX)

# Create Executable
#---------------------------------------------------#
ADD_EXECUTABLE(${PROJ_NAME_JSON} 
    ${${PROJ_NAME_JSON}_HEADERS} 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/BmMain.cpp
    )

TARGET_LINK_LIBRARIES(${PROJ_NAME_JSON} PUBLIC 
    kpsr_core 
    benchmark 
    benchmark_main 
    gtest 
    simdjson 
    SerializationBenchmarkUtils
    )

TARGET_INCLUDE_DIRECTORIES(${PROJ_NAME_JSON} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GBENCHMARK_PATH}/include
    ${GBENCHMARK_PATH}/include/benchmark
    ${CMAKE_SOURCE_DIR}/thirdparties/cereal/include/cereal/external
    ${CMAKE_SOURCE_DIR}/thirdparties/simdjson/include
    ${CMAKE_SOURCE_DIR}/thirdparties/cereal/include
    ${CMAKE_SOURCE_DIR}/thirdparties/pods/include
    ${CMAKE_SOURCE_DIR}/thirdparties/yas/include
    )


# Create Test Executable
#---------------------------------------------------#
ADD_EXECUTABLE(${PROJ_NAME_TEST} ${${PROJ_NAME_TEST}_SRC} ) 

TARGET_LINK_LIBRARIES(${PROJ_NAME_TEST} gtest simdjson SerializationBenchmarkUtils)
TARGET_INCLUDE_DIRECTORIES(${PROJ_NAME_TEST} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GOOGLETEST_PATH}/googletest/include
    ${CMAKE_SOURCE_DIR}/thirdparties/cereal/include/cereal/external
    ${CMAKE_SOURCE_DIR}/thirdparties/simdjson/include
    ${CMAKE_SOURCE_DIR}/thirdparties/cereal/include
    ${CMAKE_SOURCE_DIR}/thirdparties/pods/include
    ${CMAKE_SOURCE_DIR}/thirdparties/yas/include
    )

# Create test for ctest.
#---------------------------------------------------#
add_test(NAME ${PROJ_NAME_TEST} COMMAND ${PROJ_NAME_TEST})
