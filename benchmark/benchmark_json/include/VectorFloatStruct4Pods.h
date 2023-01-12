/*
 * Copyright 2023 Klepsydra Technologies AG
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VECTORFLOATSTRUCT4PODS_H
#define VECTORFLOATSTRUCT4PODS_H

#pragma once
#include <SerializationBenchmarkUtils.h>
#include <VectorFloatStruct.h>
#include <iostream>
#include <pods/binary.h>
#include <pods/buffers.h>
#include <pods/json.h>
#include <pods/pods.h>

struct VectorFloatStruct4Pods : public VectorFloatStruct
{
    VectorFloatStruct4Pods()
        : VectorFloatStruct(){};
    VectorFloatStruct4Pods(long l_size_vec)
        : VectorFloatStruct(l_size_vec){};
    VectorFloatStruct4Pods(long l_size_vec, float initFloatValue)
        : VectorFloatStruct(l_size_vec, initFloatValue){};

    PODS_SERIALIZABLE(1, PODS_MDR(_vec_f))
};
#endif
