#ifndef BMSIMDJSON_H
#define BMSIMDJSON_H

#include <benchmark/benchmark.h>
#include <simdjson.h>
#include <iostream>


namespace bmrkSimdjson {
class BmSimdjson
{
public:
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    // benchmarks: Deserialize existing JSON string to memory structures.
    //
    // This test benchmarks spent time serializing an existing JSON formatted string
    // of std::vector<float>, to a memory std::vector<float> with as many floats as
    // in JSON vector representation loaded.
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeUsingGetArrayAndCountElements(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);
            size_t retrievedVectorSize = 0;

            simdjson::ondemand::parser parser;
            for (auto _ : state) {
                auto doc = parser.iterate(json_string);
                simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();

                retrievedVectorSize =  jsonVectorFloat.count_elements();
                std::vector<float> deserializedVector(retrievedVectorSize);

                size_t index = 0;
                for (auto value : jsonVectorFloat) {
                    double d_val = 0;
                    auto error = value.get_double().get(d_val);
                    if (error) {
                        std::cerr << "Error in value.get_double(): " << error << std::endl; 
                        return;
                    }
                    deserializedVector[index++] = (static_cast<float>(d_val));
                }
            }

            state.counters["retrievedVectorSz"] = retrievedVectorSize;
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));

        }catch(simdjson::simdjson_error & e) {
            std::cerr << "Controller exception in DeserializeUsingGetArrayAndCountElements(): " 
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeUsingGetArrayWithoutCountElements(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0); 
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};  // WARNING: Precompiler variable created through root CMakeLists file.
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);
            std::vector<float> deserializedVector(vectorSize);

            simdjson::ondemand::parser parser;
            for (auto _ : state) {
                auto doc = parser.iterate(json_string);
                simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();

                size_t index = 0;
                for (auto value : jsonVectorFloat) {
                    double d_val = 0;
                    auto error = value.get_double().get(d_val);
                    if (error) {
                        std::cerr << "Error in value.get_double(): " << error << std::endl; 
                        return;
                    }
                    deserializedVector[index++] = (static_cast<float>(d_val));
                }
            }

            state.counters["wellKnownVectorSz"] = vectorSize;
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(vectorSize * sizeof(float)));

        }catch(simdjson::simdjson_error & e) {
            std::cerr << "Controller exception in DeserializeUsingGetArrayWithoutCountElements(): " 
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeUsingGetArrayAndCountElementsFromDiskJsonFile(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};       // WARNING: Precompiler variable created through root CMakeLists file.
            size_t retrievedVectorSize = 0;
            
            simdjson::ondemand::parser parser;
            for (auto _ : state) {
                simdjson::padded_string json_string = simdjson::padded_string::load(filename);
                auto doc = parser.iterate(json_string);

                simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();
                retrievedVectorSize =  jsonVectorFloat.count_elements();
                std::vector<float> deserializedVector(retrievedVectorSize);

                size_t index = 0;
                for (auto value : jsonVectorFloat) {
                    double d_val = 0;
                    auto error = value.get_double().get(d_val);
                    if (error) {
                        std::cerr << "Error in value.get_double(): " << error << std::endl; 
                        return;
                    }
                    deserializedVector[index++] = (static_cast<float>(d_val));
                }
            }
            
            state.counters["retrievedVectorSz"] = retrievedVectorSize;
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));

        }catch(simdjson::simdjson_error & e) {
            std::cerr << "Controller exception in DeserializeUsingGetArrayAndCountElementsFromDiskJsonFile(): " 
                << std::endl; 
        }
        
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeUsingGetArrayWithoutCountElementsFromDiskJsonFile(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};      // WARNING: Precompiler variable created through root CMakeLists file.
            
            simdjson::ondemand::parser parser;
            for (auto _ : state) {
                simdjson::padded_string json_string = simdjson::padded_string::load(filename);
                auto doc = parser.iterate(json_string);

                simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();
                std::vector<float> vec_f(vectorSize);

                size_t index = 0;
                for (auto value : jsonVectorFloat) {
                    double d_val = 0;
                    auto error = value.get_double().get(d_val);
                    if (error) {
                        std::cerr << "Error in value.get_double(): " << error << std::endl; 
                        return;
                    }
                    vec_f[index++] = (static_cast<float>(d_val));
                }
            }

            state.counters["wellKnownVectorSz"] = vectorSize;
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(vectorSize * sizeof(float)));

        }catch(simdjson::simdjson_error & e) {
            std::cerr << "Controller exception in DeserializeUsingGetArrayWithoutCountElementsFromDiskJsonFile(): " 
                << std::endl; 
        }
    }




    // Preserves original simdjson double retrieved value.
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeUsingGetArrayDoubleWithoutCountElements(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};      // WARNING: Precompiler variable created through root CMakeLists file.
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);

            simdjson::ondemand::parser parser;
            for (auto _ : state) {
                auto doc = parser.iterate(json_string);
                simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();
                std::vector<double> vec_d(vectorSize);

                size_t index = 0;
                for (auto value : jsonVectorFloat) {
                    auto error = value.get_double().get(vec_d[index++]);
                    if (error) {
                        std::cerr << "Error in value.get_double(): " << error << std::endl; 
                        return;
                    }
                }
            }

            state.counters["wellKnownVectorSz"] = vectorSize;
            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(vectorSize * sizeof(float)));

        }catch(simdjson::simdjson_error & e) {
            std::cerr << "Controller exception in DeserializeUsingGetArrayDoubleWithoutCountElements(): " 
                << std::endl; 
        }
    }




    // Preserves original simdjson double retrieved value.
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeUsingGetArrayDoubleWithoutCountElementsFromDiskJsonFile(benchmark::State &state)
    {
        try{
            long vectorSize          = state.range(0);
            std::string filename    = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};      // WARNING: Precompiler variable created through root CMakeLists file.

            simdjson::ondemand::parser parser;
            for (auto _ : state) {
                simdjson::padded_string json_string = simdjson::padded_string::load(filename);
                auto doc = parser.iterate(json_string);

                simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();
                std::vector<double> vec_d(vectorSize);

                size_t index = 0;
                for (auto value : jsonVectorFloat) {
                    auto error = value.get_double().get(vec_d[index++]);
                    if (error) {
                        std::cerr << "Error in value.get_double(): " << error << std::endl; 
                        return;
                    }
                }
            }

            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(vectorSize * sizeof(float)));
            state.counters["wellKnownVectorSz"] = vectorSize;

        }catch(simdjson::simdjson_error & e) {
            std::cerr << "Controller exception in DeserializeUsingGetArrayDoubleWithoutCountElementsFromDiskJsonFile(): " 
                << std::endl; 
        }
    }

}; // end class BmSimdjson.
}// end namespace.

#endif // BMPODS_H
