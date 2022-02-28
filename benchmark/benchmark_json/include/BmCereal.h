#ifndef BMCEREAL_H
#define BMCEREAL_H

#include <benchmark/benchmark.h>
#include <VectorFloatStruct4Cereal.h>

namespace bmrkCereal {
class BmCereal
{
public:
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    // benchmarks: Deserialize memory JSON stream to memory structures.
    //
    // This test benchmarks spent time deserializing a memory JSON formatted stream
    // of std::vector<float>, to a memory std::vector<float> with as many floats as
    // in JSON vector representation loaded.
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeJsonStringToVector(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            size_t retrievedVectorSize = 0;
            std::string json_str;

            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                json_str = vecInitialConditions.serializeVectorToJson();
            }
            
            VectorFloatStruct4Cereal deserializedVectorCereal;  
            for (auto _ : state) 
            {
                deserializedVectorCereal.deserializeJsonToVector(json_str);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeJsonStringToVector(): "  
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    // benchmarks: Deserialize existing JSON disk file to memory structures.
    //
    // This test benchmarks spent time serializing an existing JSON formatted disk file
    // of std::vector<float>, to a memory std::vector<float> with as many floats as
    // in JSON vector representation loaded.
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeJsonFileToVector(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            size_t retrievedVectorSize=0;
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            
            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                vecInitialConditions.serializeVectorToJsonFile(filename);
            }
            
            VectorFloatStruct4Cereal deserializedVectorCereal;
            for (auto _ : state) 
            {
                deserializedVectorCereal.deserializeJsonFileToVector(filename);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeJsonFileToVector(): "  
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    // benchmarks: Deserialize existing BINARY disk file to memory structures.
    //
    // This test benchmarks spent time serializing an existing BINARY formatted disk file
    // of std::vector<float>, to a memory std::vector<float> with as many floats as
    // in BIANRY vector representation loaded.
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeBinaryFileToVector(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            size_t retrievedVectorSize=0;
            std::string filename = {JSON_FILE_PATH_AND_NAME + 
                std::to_string(vectorSize) + "_bin"};
            
            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                vecInitialConditions.serializeVectorToBinaryFile(filename);
            }
            
            VectorFloatStruct4Cereal deserializedVectorCereal;
            for (auto _ : state) 
            {
                deserializedVectorCereal.deserializeBinaryFileToVector(filename);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryFileToVector(): "  
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeBinaryStreamToVector(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            size_t retrievedVectorSize=0;

            std::stringstream ssWithInitialConditions;
            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                vecInitialConditions.serializeVectorToBinaryStream(ssWithInitialConditions);
            }

            VectorFloatStruct4Cereal deserializedVectorCereal;
            for (auto _ : state) 
            {
                deserializedVectorCereal.deserializeBinaryStreamToVector(ssWithInitialConditions);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;
            
        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryStreamToVector(): "  
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeBinaryStringToVector(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            size_t retrievedVectorSize = 0;

            std::string json_string;
            {
                VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
                json_string = vecInitialConditions.serializeVectorToBinaryString();
            }
            
            VectorFloatStruct4Cereal deserializedVectorCereal;
            for (auto _ : state) 
            {
                deserializedVectorCereal.deserializeBinaryStringToVector(json_string);
            }

            retrievedVectorSize = deserializedVectorCereal.getSize();
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;
            
        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryStringToVector(): "  
                << std::endl; 
        }
    }
};
}// end namespace.

#endif // BM_CEREAL_FXS_H
