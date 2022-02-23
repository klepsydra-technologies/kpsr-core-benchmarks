#****************************************************************************
#
#                           Klepsydra Core Modules
#              Copyright (C) 2020-2022  Klepsydra Technologies GmbH
#                            All Rights Reserved.
#
#  This file is subject to the terms and conditions defined in
#  file 'LICENSE.md', which is part of this source code package.
#
#  NOTICE:  All information contained herein is, and remains the property of Klepsydra
#  Technologies GmbH and its suppliers, if any. The intellectual and technical concepts
#  contained herein are proprietary to Klepsydra Technologies GmbH and its suppliers and
#  may be covered by Swiss and Foreign Patents, patents in process, and are protected by
#  trade secret or copyright law. Dissemination of this information or reproduction of
#  this material is strictly forbidden unless prior written permission is obtained from
#  Klepsydra Technologies GmbH.
#
#****************************************************************************

# Main header: Project name & Configuration
# ------------------------------------------------------------------------------------------------------
CMAKE_MINIMUM_REQUIRED(VERSION 3.12)

SET(PROJ_MAIN_NAME "benchmark")
PROJECT(${PROJ_MAIN_NAME})

# Set kpsr-core-benchmark version.
# ------------------------------------------------------------------------------------------------------
set(BENCHMARK_MAJOR_VERSION 1)
set(BENCHMARK_MINOR_VERSION 0)
set(BENCHMARK_PATCH_VERSION 0)
set(BENCHMARK_VERSION
  ${BENCHMARK_MAJOR_VERSION}.${BENCHMARK_MINOR_VERSION}.${BENCHMARK_PATCH_VERSION})

# Configuration types
# ------------------------------------------------------------------------------------------------------
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
ENDIF()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Configure variables
# ------------------------------------------------------------------------------------------------------
IF(DEFINED GBENCHMARK_PATH)
ELSE()
  SET(GBENCHMARK_PATH ${CMAKE_SOURCE_DIR}/thirdparties/benchmark)
ENDIF()
message(STATUS "Google benchmark path: " ${GBENCHMARK_PATH})

IF(DEFINED GOOGLETEST_PATH)
ELSE()
  SET(GOOGLETEST_PATH ${CMAKE_SOURCE_DIR}/thirdparties/googletest) #google test path var needed for benchmark.
ENDIF()
message(STATUS "Google test path: " ${GOOGLETEST_PATH})

IF(DEFINED SIMDJSON_PATH)
ELSE()
  SET(SIMDJSON_PATH ${CMAKE_SOURCE_DIR}/thirdparties/simdjson)
ENDIF()
message(STATUS "SimdJSON path: " ${SIMDJSON_PATH})

IF(DEFINED cereal_DIR)
ELSE()
  SET(cereal_DIR ${CMAKE_SOURCE_DIR}/thirdparties/cereal)
ENDIF()
message(STATUS "cereal_DIR path: " ${cereal_DIR})

OPTION(DEFINE_SAVE_FLOATS_TO_TEST_FILE "To save output json test file to disk." OFF) # Disabled by default
IF(DEFINE_SAVE_FLOATS_TO_TEST_FILE)
  ADD_DEFINITIONS(-DSAVE_FLOATS_TO_TEST_FILE)
ENDIF(DEFINE_SAVE_FLOATS_TO_TEST_FILE)
message(STATUS "DEFINE_SAVE_FLOATS_TO_TEST_FILE: " ${DEFINE_SAVE_FLOATS_TO_TEST_FILE})

IF(DEFINED TEST_FILE_PATH_AND_NAME)
  ADD_DEFINITIONS(-DTEST_FILE_PATH_AND_NAME="\""${TEST_FILE_PATH_AND_NAME}"\"")
ELSE()
  ADD_DEFINITIONS(-DTEST_FILE_PATH_AND_NAME="out.txt")
  SET(TEST_FILE_PATH_AND_NAME out.txt)
ENDIF()
message(STATUS "TEST_FILE_PATH_AND_NAME: " ${TEST_FILE_PATH_AND_NAME})

IF(DEFINED JSON_FILE_PATH_AND_NAME)
  ADD_DEFINITIONS(-DJSON_FILE_PATH_AND_NAME="\""${JSON_FILE_PATH_AND_NAME}"\"")
ELSE()
  ADD_DEFINITIONS(-DJSON_FILE_PATH_AND_NAME="cereal_json_str.txt")
  SET(JSON_FILE_PATH_AND_NAME cereal_json_str.txt)
ENDIF()
message(STATUS "JSON_FILE_PATH_AND_NAME: " ${JSON_FILE_PATH_AND_NAME})


# Required packages.
# ------------------------------------------------------------------------------------------------------
find_package(Klepsydra REQUIRED)

# Ouput paths.
# ------------------------------------------------------------------------------------------------------
SET(LIBRARY_OUTPUT_PATH          ${PROJECT_BINARY_DIR}/bin                   CACHE PATH "Library output" FORCE)
SET(EXECUTABLE_OUTPUT_PATH       ${PROJECT_BINARY_DIR}/bin                   CACHE PATH "Executable output" FORCE)

######################################################################################
# ADD SUB FOLDERS
######################################################################################
ADD_SUBDIRECTORY(benchmark)
ADD_SUBDIRECTORY(${GOOGLETEST_PATH})
ADD_SUBDIRECTORY(${GBENCHMARK_PATH})
set_target_properties(cxx03_test PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
ADD_SUBDIRECTORY(${SIMDJSON_PATH})
