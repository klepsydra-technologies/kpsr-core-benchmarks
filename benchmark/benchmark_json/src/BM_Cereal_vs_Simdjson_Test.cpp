/****************************************************************************
 *
 *                           Klepsydra Core Modules
 *              Copyright (C) 2019-2020  Klepsydra Technologies GmbH
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/
#define CEREAL_THREAD_SAFE 1

#include <benchmark/benchmark.h>
#include <iostream>
#include <simdjson.h>
#include <vector>
#include <limits>
#include <random>
#include <fstream>  // ofstream

#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>


// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
bool save_to_myfile(const std::string & str, const std::string & fileName)
{
    std::ofstream outFile;
    outFile.open(fileName);
    if(!outFile){
        return false;
    }
    outFile << str << std::endl;
    return true;
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
float get_random_float_using_whole_range(){
    std::random_device rd;
    std::mt19937 gen(rd());
    return std::uniform_real_distribution<float>(std::numeric_limits<float>::max(), std::numeric_limits<float>::min())(gen);
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
// cereal needs to know which data members to serialize in your classes. 
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
struct myVectorFloats {
    // As we use vector, we need to add related cereal include '#include <cereal/types/vector.hpp>'.
    std::vector<float> _vec_f;

    friend class cereal::access;

    template<class Archive>
    void serialize(Archive & archive) {
        archive( cereal::make_nvp("vector" , _vec_f) );
    }
    
    void serialize__Vector_to__JSON_file(const std::string & filename_string){
        std::ofstream os(filename_string);
        {
            cereal::JSONOutputArchive archive_out(os);
            serialize(archive_out);
        }
        return;
    }

    std::string serialize__Vector_to__JSON(){
        std::stringstream os;
        {
            cereal::JSONOutputArchive archive_out(os);
            serialize(archive_out);
        }
        return os.str();
    }

    // json_string provided must have expected format as created by cereal::JSONOutputArchive.
    std::vector<float> deserialize__JSON_to__Vector(const std::string & json_string){
        std::stringstream is (json_string);
        {
            cereal::JSONInputArchive archive_in(is);
            serialize(archive_in);
        }
        return _vec_f;
    }
    
    std::vector<float> deserialize__JSON_file_to__Vector(const std::string & filename_string){
        std::ifstream is(filename_string);
        {
            cereal::JSONInputArchive archive_in(is);
            serialize(archive_in);
        }
        return _vec_f;
    }

    void load_random(int i_vec_size){
        for(int i = 0; i < i_vec_size; i++) 
        {
            float f_rand_value = get_random_float_using_whole_range();
            _vec_f.push_back(f_rand_value);
        }
    }

    size_t get_size(){
        return _vec_f.size();
    }

    std::vector<float> get_vec(){
        return _vec_f;
    }

    void clear_vector(){
        _vec_f.clear();
    }
    
    // Load vector randomly with desired size.
    myVectorFloats(int i_size_vec) {
        load_random(i_size_vec);
    };

    myVectorFloats() = default;
};










// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
// benchmarks: Deserialize memory JSON stream to memory structures.
//
// This test benchmarks spent time deserializing a memory JSON formatted stream
// of std::vector<float>, to a memory std::vector<float> with as many floats as
// in JSON vector representation loaded.
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
static void Cereal__Retrive_float_vector(benchmark::State &state)
{
    try{
        // Create a json_string related to test conditions.
        int i_vec_size = state.range(0);
        std::string json_string;
        size_t retrieved_vector_size=0;

        myVectorFloats vec_f(i_vec_size);                                           // Load vector randomly with specified size.
        std::string json_str = vec_f.serialize__Vector_to__JSON();                  // Now, use this vector to create a JSON serialization memory stream.
#ifdef SAVE_FLOATS_TO_TEST_FILE                                                     // WARNING: Precompiler variable created through root CMakeLists file.
        const std::string fileName = {TEST_FILE_PATH_AND_NAME};                     // WARNING: Precompiler variable created through root CMakeLists file.
        save_to_myfile(json_str, fileName);
#endif
        myVectorFloats vec_f_results;                                               // Create an empty vector to load results;
        for (auto _ : state) 
        {
            vec_f_results.deserialize__JSON_to__Vector(json_str);                   // Deserialize JSON memory stream to std::vector<float> with as many floats as in JSON string.
        }
        // end timed code.
        retrieved_vector_size = vec_f_results.get_size();                           // Get number of floats retrieved to results vector.
        state.counters["retrievedVectorSz"] = retrieved_vector_size;

    }catch(...) {
        std::cerr << "Controller exception in BM_KPE_166_Retrive_float_vector(): "  << std::endl; 
    }
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
// benchmarks: Deserialize existing JSON disk file to memory structures.
//
// This test benchmarks spent time serializing an existing JSON formatted disk file
// of std::vector<float>, to a memory std::vector<float> with as many floats as
// in JSON vector representation loaded.
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
static void Cereal__Retrive_float_vector_from_disk_jsonfile(benchmark::State &state)
{
    try{
        // Create a json_string related to test conditions.
        int i_vec_size = state.range(0);
        std::string json_string;
        size_t retrieved_vector_size=0;

        myVectorFloats vec_f(i_vec_size);                                           // Load vector randomly with specified size.
        // TODO. Si no existe el archivo, lo creamos.
        std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(i_vec_size)};  // WARNING: Precompiler variable created through root CMakeLists file.
        vec_f.serialize__Vector_to__JSON_file(filename);                            // Now, use this vector to create a JSON serialization disk file.
        myVectorFloats vec_f_results;                                               // Create an empty vector to load results;
        for (auto _ : state) 
        {
            vec_f_results.deserialize__JSON_file_to__Vector(filename);              // Deserialize JSON memory stream to std::vector<float> with as many floats as in JSON string.
        }
        // end timed code.
        retrieved_vector_size = vec_f_results.get_size();                           // Get number of floats retrieved to results vector.
        state.counters["retrievedVectorSz"] = retrieved_vector_size;
    }catch(...) {
        std::cerr << "Controller exception in BM_KPE_166_Retrive_float_vector(): "  << std::endl; 
    }
}

// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
// benchmarks: Deserialize existing JSON string to memory structures.
//
// This test benchmarks spent time serializing an existing JSON formatted string
// of std::vector<float>, to a memory std::vector<float> with as many floats as
// in JSON vector representation loaded.
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
static void Simdjson__Retrive_using__get_array__count_elements(benchmark::State &state)
{
    try{
        // Create a json_string related to test conditions.
        int i_vec_size                      = state.range(0);
        int desired_Precission              = 17; //state.range(1);
        bool std_fixed                      = true; //state.range(2);
        std::string filename                = {JSON_FILE_PATH_AND_NAME + std::to_string(i_vec_size)};
        simdjson::padded_string json_string = simdjson::padded_string::load(filename);

        size_t retrieved_vector_size=0;
        // This code gets timed
        for (auto _ : state) {
            simdjson::ondemand::parser parser;
            auto doc = parser.iterate(json_string);

            // TODO
            // revisar un get_array de doubles
            //value.get_double_in_string().get(d)
            //simdjson_really_inline double first_double(ondemand::json_iterator &iter) {
            simdjson::ondemand::array jsonvec_f = doc.find_field("vector").get_array();
            retrieved_vector_size =  jsonvec_f.count_elements();
            std::vector<float> vec_f(retrieved_vector_size);
            size_t index = 0;
            for (auto value : jsonvec_f) {
                double d_val = 0;
                auto error = value.get_double().get(d_val);
                if (error) {
                    std::cerr << "Error in value.get_double(): " << error << std::endl; 
                    return;
                }
                vec_f[index++] = (static_cast<float>(d_val));
            }
        }
        // end timed code.
        state.counters["retrievedVectorSz"] = retrieved_vector_size;
        state.counters["desiredPrecission"] = desired_Precission;

    }catch(simdjson::simdjson_error & e) {
        // e.error() == NUMBER_ERROR
        std::cerr << "Error in get_string() s1: " << e.error() << std::endl; 
        return;
    }
}


static void Simdjson__Retrive_using__get_array__without_count_elements(benchmark::State &state)
{
    try{
        // Create a json_string related to test conditions.
        int i_vec_size = state.range(0); // 3
        int desired_Precission = 17; //state.range(1); //17
        bool std_fixed         = true; //state.range(2);
        std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(i_vec_size)};  // WARNING: Precompiler variable created through root CMakeLists file.
        simdjson::padded_string json_string = simdjson::padded_string::load(filename);
        std::vector<float> vec_f(i_vec_size);

        // This code gets timed
        for (auto _ : state) {
            simdjson::ondemand::parser parser;
            auto doc = parser.iterate(json_string);

            simdjson::ondemand::array jsonvec_f = doc.find_field("vector").get_array();
            // Well-known vector size thus, do not use simdjson count_elements. 
            // We create sized std::vector<float> directly. 
            size_t index = 0;
            for (auto value : jsonvec_f) {
                double d_val = 0;
                auto error = value.get_double().get(d_val);
                if (error) {
                    std::cerr << "Error in value.get_double(): " << error << std::endl; 
                    return;
                }
                vec_f[index++] = (static_cast<float>(d_val));
            }
        }
        // end timed code.
        state.counters["wellKnownVectorSz"] = i_vec_size;
        state.counters["desiredPrecission"] = desired_Precission;

    }catch(simdjson::simdjson_error & e) {
        // e.error() == NUMBER_ERROR
        std::cerr << "Error in get_string() s1: " << e.error() << std::endl; 
        return;
    }
}



static void Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile(benchmark::State &state)
{
    try{
        // Create a json_string related to test conditions.
        int i_vec_size          = state.range(0);
        int desired_Precission  = 17; //state.range(1);
        bool std_fixed          = true; //state.range(2);
        std::string filename    = {JSON_FILE_PATH_AND_NAME + std::to_string(i_vec_size)};      // WARNING: Precompiler variable created through root CMakeLists file.
        size_t retrieved_vector_size = 0;
        // This code gets timed
        for (auto _ : state) {
            simdjson::ondemand::parser parser;
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);  // Now, we benchmarks spent time loading disk file.
            auto doc = parser.iterate(json_string);

            simdjson::ondemand::array jsonvec_f = doc.find_field("vector").get_array();
            retrieved_vector_size =  jsonvec_f.count_elements();
            std::vector<float> vec_f(retrieved_vector_size);
            size_t index = 0;
            for (auto value : jsonvec_f) {
                double d_val = 0;
                auto error = value.get_double().get(d_val);
                if (error) {
                    std::cerr << "Error in value.get_double(): " << error << std::endl; 
                    return;
                }
                vec_f[index++] = (static_cast<float>(d_val));
            }
        }
        // end timed code.
        state.counters["retrievedVectorSz"] = retrieved_vector_size;
        state.counters["desiredPrecission"] = desired_Precission;

    }catch(simdjson::simdjson_error & e) {
        std::cerr << "Error in get_string() s1: " << e.error() << std::endl; 
        return;
    }
    
}


static void Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile(benchmark::State &state)
{
    try{
        // Create a json_string related to test conditions.
        int i_vec_size          = state.range(0); // 3
        int desired_Precission  = 17; //state.range(1); //17
        bool std_fixed          = true; //state.range(2);
        std::string filename    = {JSON_FILE_PATH_AND_NAME + std::to_string(i_vec_size)};      // WARNING: Precompiler variable created through root CMakeLists file.
        // This code gets timed
        for (auto _ : state) {
            simdjson::ondemand::parser parser;
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);  // Now, we benchmarks spent time loading disk file.
            auto doc = parser.iterate(json_string);

            simdjson::ondemand::array jsonvec_f = doc.find_field("vector").get_array();
            // Well-known vector size thus, do not use simdjson count_elements. 
            // We create sized std::vector<float> directly. 
            std::vector<float> vec_f(i_vec_size);
            size_t index = 0;
            for (auto value : jsonvec_f) {
                double d_val = 0;
                auto error = value.get_double().get(d_val);
                if (error) {
                    std::cerr << "Error in value.get_double(): " << error << std::endl; 
                    return;
                }
                vec_f[index++] = (static_cast<float>(d_val));
            }
        }
        // end timed code.
        state.counters["wellKnownVectorSz"] = i_vec_size;
        state.counters["desiredPrecission"] = desired_Precission;

    }catch(simdjson::simdjson_error & e) {
        // e.error() == NUMBER_ERROR
        std::cerr << "Error in get_string() s1: " << e.error() << std::endl; 
        return;
    }
}


// Preserves original simdjson double retrieved value.
static void Simdjson__Retrive_using__get_array_double__without_count_elements(benchmark::State &state)
{
    try{
        // Create a json_string related to test conditions.
        int i_vec_size                      = state.range(0); // 3
        int desired_Precission              = 17; //state.range(1); //17
        bool std_fixed                      = true; //state.range(2);
        std::string filename                = {JSON_FILE_PATH_AND_NAME + std::to_string(i_vec_size)};      // WARNING: Precompiler variable created through root CMakeLists file.
        simdjson::padded_string json_string = simdjson::padded_string::load(filename);

        // This code gets timed
        for (auto _ : state) {
            simdjson::ondemand::parser parser;
            auto doc = parser.iterate(json_string);
            simdjson::ondemand::array jsonvec_f = doc.find_field("vector").get_array();
            // Well-known vector size thus, do not use simdjson count_elements. 
            // We create sized std::vector<float> directly. 
            std::vector<double> vec_d(i_vec_size);
            size_t index = 0;
            for (auto value : jsonvec_f) {
                auto error = value.get_double().get(vec_d[index++]);
                if (error) {
                    std::cerr << "Error in value.get_double(): " << error << std::endl; 
                    return;
                }
            }
        }
        // end timed code.
        state.counters["wellKnownVectorSz"] = i_vec_size;
        state.counters["desiredPrecission"] = desired_Precission;

    }catch(simdjson::simdjson_error & e) {
        // e.error() == NUMBER_ERROR
        std::cerr << "Error in get_string() s1: " << e.error() << std::endl; 
        return;
    }
}


// Preserves original simdjson double retrieved value.
static void Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile(benchmark::State &state)
{
    try{
        // Create a json_string related to test conditions.
        int i_vec_size          = state.range(0); // 3
        int desired_Precission  = 17; //state.range(1); //17
        bool std_fixed          = true; //state.range(2);
        std::string filename    = {JSON_FILE_PATH_AND_NAME + std::to_string(i_vec_size)};      // WARNING: Precompiler variable created through root CMakeLists file.
        // This code gets timed
        for (auto _ : state) {
            simdjson::ondemand::parser parser;
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);                      // Now, we benchmarks spent time loading disk file.
            auto doc = parser.iterate(json_string);

            simdjson::ondemand::array jsonvec_f = doc.find_field("vector").get_array();
            // Well-known vector size thus, do not use simdjson count_elements. 
            // We create sized std::vector<float> directly. 
            std::vector<double> vec_d(i_vec_size);
            size_t index = 0;
            for (auto value : jsonvec_f) {
                auto error = value.get_double().get(vec_d[index++]);
                if (error) {
                    std::cerr << "Error in value.get_double(): " << error << std::endl; 
                    return;
                }
            }
        }
        // end timed code.
        state.counters["wellKnownVectorSz"] = i_vec_size;
        state.counters["desiredPrecission"] = desired_Precission;

    }catch(simdjson::simdjson_error & e) {
        // e.error() == NUMBER_ERROR
        std::cerr << "Error in get_string() s1: " << e.error() << std::endl; 
        return;
    }
}



// Cereal
BENCHMARK(Cereal__Retrive_float_vector)
    ->Name("Cereal__Retrive_float_vector")
    ->UseRealTime()
    ->ArgsProduct({
        benchmark::CreateDenseRange(1024, 102400, 1<<10)});

BENCHMARK(Cereal__Retrive_float_vector_from_disk_jsonfile)
    ->Name("Cereal__Retrive_float_vector_from_disk_jsonfile")
    ->UseRealTime()
    ->ArgsProduct({
        benchmark::CreateDenseRange(1024, 102400, 1<<10)});




// Simdjson
BENCHMARK(Simdjson__Retrive_using__get_array__count_elements)
    ->Name("Simdjson__Retrive_using__get_array__count_elements")
    ->UseRealTime()
    ->ArgsProduct({
        benchmark::CreateDenseRange(1024, 102400, 1<<10)});

BENCHMARK(Simdjson__Retrive_using__get_array__without_count_elements)
    ->Name("Simdjson__Retrive_using__get_array__without_count_elements")
    ->UseRealTime()
    ->ArgsProduct({
        benchmark::CreateDenseRange(1024, 102400, 1<<10)});

BENCHMARK(Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile)
    ->Name("Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile")
    ->UseRealTime()
    ->ArgsProduct({
        benchmark::CreateDenseRange(1024, 102400, 1<<10)});

BENCHMARK(Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile)
    ->Name("Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile")
    ->UseRealTime()
    ->ArgsProduct({
        benchmark::CreateDenseRange(1024, 102400, 1<<10)});

BENCHMARK(Simdjson__Retrive_using__get_array_double__without_count_elements)
    ->Name("Simdjson__Retrive_using__get_array_double__without_count_elements")
    ->UseRealTime()
    ->ArgsProduct({
        benchmark::CreateDenseRange(1024, 102400, 1<<10)});

BENCHMARK(Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile)
    ->Name("Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile")
    ->UseRealTime()
    ->ArgsProduct({
        benchmark::CreateDenseRange(1024, 102400, 1<<10)});


BENCHMARK_MAIN();

