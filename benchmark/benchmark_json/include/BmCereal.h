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

#ifndef BMCEREAL_H
#define BMCEREAL_H

#include <VectorFloatStruct4Cereal.h>
#include <benchmark/benchmark.h>

namespace bmrkCereal {
class BmCereal
{
public:
    static void DeserializeJsonStringToVector(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            size_t retrievedVectorSize = 0;
            std::string json_str;

            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                json_str = vecInitialConditions.serializeVectorToJson();
            }

            VectorFloatStruct4Cereal deserializedVectorCereal;
            for (auto _ : state) {
                deserializedVectorCereal.deserializeJsonToVector(json_str);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in DeserializeJsonStringToVector(): " << std::endl;
        }
    }

    static void DeserializeJsonFileToVector(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            size_t retrievedVectorSize = 0;
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};

            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                vecInitialConditions.serializeVectorToJsonFile(filename);
            }

            VectorFloatStruct4Cereal deserializedVectorCereal;
            for (auto _ : state) {
                deserializedVectorCereal.deserializeJsonFileToVector(filename);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in DeserializeJsonFileToVector(): " << std::endl;
        }
    }

    static void DeserializeBinaryFileToVector(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            size_t retrievedVectorSize = 0;
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize) + "_bin"};

            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                vecInitialConditions.serializeVectorToBinaryFile(filename);
            }

            VectorFloatStruct4Cereal deserializedVectorCereal;
            for (auto _ : state) {
                deserializedVectorCereal.deserializeBinaryFileToVector(filename);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in DeserializeBinaryFileToVector(): " << std::endl;
        }
    }

    static void DeserializeBinaryStreamToVector(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            size_t retrievedVectorSize = 0;

            std::stringstream ssWithInitialConditions;
            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                vecInitialConditions.serializeVectorToBinaryStream(ssWithInitialConditions);
            }

            VectorFloatStruct4Cereal deserializedVectorCereal;
            for (auto _ : state) {
                deserializedVectorCereal.deserializeBinaryStreamToVector(ssWithInitialConditions);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in DeserializeBinaryStreamToVector(): " << std::endl;
        }
    }

    static void DeserializeBinaryStringToVector(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            size_t retrievedVectorSize = 0;

            std::string json_string;
            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                json_string = vecInitialConditions.serializeVectorToBinaryString();
            }

            VectorFloatStruct4Cereal deserializedVectorCereal;
            for (auto _ : state) {
                deserializedVectorCereal.deserializeBinaryStringToVector(json_string);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in DeserializeBinaryStringToVector(): " << std::endl;
        }
    }
};
} // namespace bmrkCereal

#endif // BM_CEREAL_FXS_H
