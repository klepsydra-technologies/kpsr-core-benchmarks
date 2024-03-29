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

#ifndef BMYAS_H
#define BMYAS_H

#include <VectorFloatStruct4Yas.h>
#include <benchmark/benchmark.h>
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>

namespace bmrkYas {
class BmYas
{
public:
    static void DeserializeFromJsonMemoryBufferToVector(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            size_t retrievedVectorSize = 0;
            yas::shared_buffer json_Yasbuffer;

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeJsonFileToVector(filename);

            VectorFloatStruct4Yas vecYasInitialConditions;
            vecYasInitialConditions.loadFrom(deserializedVectorCereal.getVec());

            json_Yasbuffer = vecYasInitialConditions.serializeVectorToJson();

            VectorFloatStruct4Yas deserializedVectorYas;
            for (auto _ : state) {
                deserializedVectorYas.deserializeJsonToVector(json_Yasbuffer);
            }

            retrievedVectorSize = deserializedVectorYas.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in DeserializeFromJsonMemoryBufferToVector(): "
                      << std::endl;
        }
    }

    static void DeserializeFromJsonFileToVector(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            size_t retrievedVectorSize = 0;

            VectorFloatStruct4Yas deserializedVectorYas;
            for (auto _ : state) {
                deserializedVectorYas.deserializeJsonFileToVector(filename);
            }

            retrievedVectorSize = deserializedVectorYas.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in DeserializeFromJsonFileToVector(): " << std::endl;
        }
    }

    static void DeserializeFromBinaryFileToVector(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize) + "_bin"};
            size_t retrievedVectorSize = 0;

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeBinaryFileToVector(filename);

            std::string fileNameYas = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize) +
                                       "_yas_bin"};
            VectorFloatStruct4Yas vecYasInitialConditions;
            vecYasInitialConditions.loadFrom(deserializedVectorCereal.getVec());
            vecYasInitialConditions.serializeVectorToBinaryFile(fileNameYas);

            VectorFloatStruct4Yas deserializedVectorYas;
            for (auto _ : state) {
                deserializedVectorYas.deserializeBinaryFileToVector(fileNameYas);
            }

            retrievedVectorSize = deserializedVectorYas.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in DeserializeFromBinaryFileToVector(): "
                      << std::endl;
        }
    }

    static void DeserializeFromBinaryStreamToVector(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize) + "_bin"};
            size_t retrievedVectorSize = 0;

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeBinaryFileToVector(filename);

            VectorFloatStruct4Yas vecYasInitialConditions;
            vecYasInitialConditions.loadFrom(deserializedVectorCereal.getVec());
            yas::shared_buffer streamBuffer = vecYasInitialConditions.serializeVectorToBinaryStream();

            VectorFloatStruct4Yas deserializedVectorYas;
            for (auto _ : state) {
                deserializedVectorYas.deserializeBinaryStreamToVector(streamBuffer);
            }

            retrievedVectorSize = deserializedVectorYas.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in DeserializeFromBinaryStreamToVector(): "
                      << std::endl;
        }
    }

}; // end class BmPods.
} // namespace bmrkYas

#endif // BMPODS_H
