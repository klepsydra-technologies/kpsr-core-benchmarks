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
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
  SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
ENDIF()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

enable_testing()

# Configure variables
# ------------------------------------------------------------------------------------------------------

# Paths
if(DEFINED KPSR_BUILD_PATH)
else()
    SET(KPSR_BUILD_PATH ${CMAKE_SOURCE_DIR}/kpsr-build)
endif()
message(STATUS "kpsr-build path: " ${KPSR_BUILD_PATH})

IF(DEFINED THIRDPARTIES_PATH)
ELSE()
  SET(THIRDPARTIES_PATH ${CMAKE_SOURCE_DIR}/thirdparties )
ENDIF()
message(STATUS "Thirdparties install path: " ${THIRDPARTIES_PATH})

SET(CMAKE_MODULE_PATH            ${KPSR_BUILD_PATH}/cmake)

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

IF(DEFINED PODS_PATH)
ELSE()
  SET(PODS_PATH ${CMAKE_SOURCE_DIR}/thirdparties/pods)
ENDIF()
message(STATUS "pods path: " ${PODS_PATH})

IF(DEFINED YAS_PATH)
ELSE()
  SET(YAS_PATH ${CMAKE_SOURCE_DIR}/thirdparties/yas)
ENDIF()
message(STATUS "yas path: " ${YAS_PATH})

IF(DEFINED JSON_FILE_PATH_AND_NAME)
  ADD_DEFINITIONS(-DJSON_FILE_PATH_AND_NAME="\""${JSON_FILE_PATH_AND_NAME}"\"")
ELSE()
  ADD_DEFINITIONS(-DJSON_FILE_PATH_AND_NAME="cereal_json_str.txt")
  SET(JSON_FILE_PATH_AND_NAME cereal_json_str.txt)
ENDIF()
message(STATUS "JSON_FILE_PATH_AND_NAME: " ${JSON_FILE_PATH_AND_NAME})

IF(DEFINED BM_DENSE_RANGE_START)
  ADD_DEFINITIONS(-DBM_DENSE_RANGE_START=${BM_DENSE_RANGE_START})
ELSE()
  ADD_DEFINITIONS(-DBM_DENSE_RANGE_START=1024)
  SET(BM_DENSE_RANGE_START 1024)
ENDIF()
message(STATUS "BM_DENSE_RANGE_START: " ${BM_DENSE_RANGE_START})

IF(DEFINED BM_DENSE_RANGE_END)
  ADD_DEFINITIONS(-DBM_DENSE_RANGE_END=${BM_DENSE_RANGE_END})
ELSE()
  ADD_DEFINITIONS(-DBM_DENSE_RANGE_END=102400)
  SET(BM_DENSE_RANGE_END 102400)
ENDIF()
message(STATUS "BM_DENSE_RANGE_END: " ${BM_DENSE_RANGE_END})

IF(DEFINED BM_DENSE_RANGE_INCR)
  ADD_DEFINITIONS(-DBM_DENSE_RANGE_INCR=${BM_DENSE_RANGE_INCR})
ELSE()
  ADD_DEFINITIONS(-DBM_DENSE_RANGE_INCR=1024)
  SET(BM_DENSE_RANGE_INCR 1024)
ENDIF()
message(STATUS "BM_DENSE_RANGE_INCR: " ${BM_DENSE_RANGE_INCR})

# Required packages.
# ------------------------------------------------------------------------------------------------------
find_package(Klepsydra REQUIRED)

# Ouput paths.
# ------------------------------------------------------------------------------------------------------
SET(LIBRARY_OUTPUT_PATH          ${PROJECT_BINARY_DIR}/bin         CACHE PATH "Library output" FORCE)
SET(EXECUTABLE_OUTPUT_PATH       ${PROJECT_BINARY_DIR}/bin         CACHE PATH "Executable output" FORCE)

######################################################################################
# ADD SUB FOLDERS
######################################################################################
ADD_SUBDIRECTORY(benchmark)
ADD_SUBDIRECTORY(${GOOGLETEST_PATH})
ADD_SUBDIRECTORY(${GBENCHMARK_PATH})
#set_target_properties(cxx03_test PROPERTIES EXCLUDE_FROM_ALL 1 EXCLUDE_FROM_DEFAULT_BUILD 1)
ADD_SUBDIRECTORY(${SIMDJSON_PATH})
ADD_SUBDIRECTORY(${PODS_PATH})

######################################################################################
# CODE STYLE
######################################################################################
if (KPSR_WITH_CODE_METRICS)
  include(CodeCoverage)
  set(CODE_COVERAGE_VERBOSE ON)
  APPEND_COVERAGE_COMPILER_FLAGS()
   # Code style check
   include(CppcheckTargets)
   include(Findcppcheck)
ENDIF()

# Code format check
include(CodeFormat)

# Code Coverage
if (KPSR_WITH_CODE_METRICS AND CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX)
  STRING(REPLACE ${CMAKE_SOURCE_DIR}/ "" THIRDPARTIES_PATH_COVERAGE ${THIRDPARTIES_PATH})
  LIST(APPEND COVERAGE_EXCLUDES
    ${THIRDPARTIES_PATH_COVERAGE}
    ${CMAKE_PREFIX_PATH}
    benchmark/benchmark_json/tests
    )
  setup_target_for_coverage_gcovr_xml(
    NAME coverage
    EXECUTABLE make test
    )
ENDIF()

######################################################################################
# CCACHE SUPPORT
######################################################################################
include(FindCcache)
