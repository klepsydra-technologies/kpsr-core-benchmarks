#****************************************************************************
#
#                           Klepsydra Core Modules
#              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
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

SET(PROJ_NAME_JSON kpsr_benchmark_json_test)
PROJECT(${PROJ_NAME_JSON})

# Source
#---------------------------------------------------#
FILE(GLOB ${PROJ_NAME_JSON}_SRC
    "src/*.cpp"
)

# Create Library
#---------------------------------------------------#
ADD_EXECUTABLE(${PROJ_NAME_JSON} ${${PROJ_NAME_JSON}_HEADERS} ${${PROJ_NAME_JSON}_SRC} )

TARGET_LINK_LIBRARIES(${PROJ_NAME_JSON} PUBLIC kpsr_core benchmark benchmark_main gtest simdjson)

TARGET_INCLUDE_DIRECTORIES(${PROJ_NAME_JSON}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${GBENCHMARK_PATH}/include
    ${GBENCHMARK_PATH}/include/benchmark
    ${CMAKE_SOURCE_DIR}/thirdparties/simdjson/include
    ${CMAKE_SOURCE_DIR}/thirdparties/cereal/include
    )

