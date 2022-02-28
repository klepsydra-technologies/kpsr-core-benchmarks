#ifndef BMCEREAL_H
#define BMCEREAL_H

#include <benchmark/benchmark.h>
#include <VectorFloatStruct4Cereal.h>

namespace bmrkCereal {
class BmCereal
{
public:
    
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
            state.SetBytesProcessed(int64_t(state.iterations()) * 
                int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeJsonStringToVector(): "  
                << std::endl; 
        }
    }




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
            state.SetBytesProcessed(int64_t(state.iterations()) * 
                int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeJsonFileToVector(): "  
                << std::endl; 
        }
    }




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
            state.SetBytesProcessed(int64_t(state.iterations()) * 
                int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryFileToVector(): "  
                << std::endl; 
        }
    }




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
            state.SetBytesProcessed(int64_t(state.iterations()) * 
                int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;
            
        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryStreamToVector(): "  
                << std::endl; 
        }
    }




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
            state.SetBytesProcessed(int64_t(state.iterations()) * 
                int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;
            
        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryStringToVector(): "  
                << std::endl; 
        }
    }
};
}// end namespace.

#endif // BM_CEREAL_FXS_H
