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

#ifndef VECTORFLOATSTRUCT_H
#define VECTORFLOATSTRUCT_H

#include <SerializationBenchmarkUtils.h>
#include <iostream>
#include <memory>
#include <vector>

struct VectorFloatStruct
{
    std::vector<float> _vec_f;

    void fillWithRandomData(int l_vec_size)
    {
        float f_rand_value = 0.0;
        _vec_f.clear();
        _vec_f.resize(l_vec_size);
        for (int i = 0; i < l_vec_size; i++) {
            f_rand_value = SerializationBenchmarkUtils::getRandomFloatUsingWholeRange();
            _vec_f[i] = f_rand_value;
        }
    }

    size_t getSize() { return _vec_f.size(); }

    std::vector<float> getVec() { return _vec_f; }

    void clearVector() { _vec_f.clear(); }

    void loadFrom(std::vector<float> vec)
    {
        _vec_f.clear();
        _vec_f.resize(vec.size());
        for (int i = 0; i < _vec_f.size(); i++) {
            _vec_f[i] = vec[i];
        }
    }

    VectorFloatStruct(long l_size_vec) { fillWithRandomData(l_size_vec); };

    VectorFloatStruct(long l_size_vec, float initFloatValue)
    {
        _vec_f.clear();
        _vec_f.resize(l_size_vec, initFloatValue);
    };

    VectorFloatStruct() = default;

    ~VectorFloatStruct() { _vec_f.clear(); }
};

#endif
