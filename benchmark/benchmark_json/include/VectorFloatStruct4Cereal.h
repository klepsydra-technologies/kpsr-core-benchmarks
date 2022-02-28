#ifndef VECTORFLOATSTRUCT4CEREAL_H
#define VECTORFLOATSTRUCT4CEREAL_H

#pragma once
#include <SerializationBenchmarkUtils.h>
#include <VectorFloatStruct.h>
#include <iostream>
#include <fstream>
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>



// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
// cereal needs to know which data members to serialize in your classes. 
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
struct VectorFloatStruct4Cereal : public VectorFloatStruct {
    // IMPORTANT; As we use vector, we need to add related cereal
    // include '#include <cereal/types/vector.hpp>'.
    VectorFloatStruct4Cereal() : VectorFloatStruct() {};
    VectorFloatStruct4Cereal(long l_size_vec) : VectorFloatStruct(l_size_vec) {};
    VectorFloatStruct4Cereal(long l_size_vec, float initFloatValue) : VectorFloatStruct(l_size_vec, initFloatValue) {};

    friend class cereal::access;

    template<class Archive>
    void serialize(Archive & archive) {
        archive( cereal::make_nvp("vector" , _vec_f) );
    }
    
    void serializeVectorToJsonFile(const std::string & filename_string){
        std::ofstream os(filename_string);
        {
            cereal::JSONOutputArchive archive_out(os);
            serialize(archive_out);
        }
        return;
    }

    std::string serializeVectorToJson(){
        std::stringstream os;
        {
            cereal::JSONOutputArchive archive_out(os);
            serialize(archive_out);
        }
        return os.str();
    }
    
    void serializeVectorToBinaryFile(const std::string & filename_string){
        std::ofstream os(filename_string, std::ios::binary);
        {
            cereal::BinaryOutputArchive archive_out(os);
            serialize(archive_out);
        }
        return;
    }

    std::string serializeVectorToBinaryString(){
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive_out(ss);
            serialize(archive_out);
        }
        return ss.str();
    }

    void serializeVectorToBinaryStream(std::stringstream & ss)
    {
        std::stringstream is;
        {
            cereal::BinaryOutputArchive archive_out(is);
            serialize(archive_out);
        }
        ss << is.rdbuf();
    }


    
    // json_string provided must have expected format as created by cereal::JSONOutputArchive.
    std::vector<float> deserializeJsonToVector(const std::string & json_string){
        std::stringstream is (json_string);
        {
            cereal::JSONInputArchive archive_in(is);
            serialize(archive_in);
        }
        return _vec_f;
    }
    
    std::vector<float> deserializeJsonFileToVector(const std::string & filename_string){
        std::ifstream is(filename_string);
        {
            cereal::JSONInputArchive archive_in(is);
            serialize(archive_in);
        }
        return _vec_f;
    }

    std::vector<float> deserializeBinaryFileToVector(const std::string & filename_string){
        std::ifstream is(filename_string);
        {
            cereal::BinaryInputArchive archive_in(is);
            serialize(archive_in);
        }
        return _vec_f;
    }

    std::vector<float> deserializeBinaryStringToVector(const std::string & json_string){
        std::stringstream ss(json_string);
        {
            cereal::BinaryInputArchive archive_in(ss);
            serialize(archive_in);
        }
        return _vec_f;
    }
    
    std::vector<float> deserializeBinaryStreamToVector(std::stringstream & is)
    {
        std::stringstream ss(is.str());
        {
            cereal::BinaryInputArchive archive_in(ss);
            serialize(archive_in);
        }
        return _vec_f;
    }
};

#endif
