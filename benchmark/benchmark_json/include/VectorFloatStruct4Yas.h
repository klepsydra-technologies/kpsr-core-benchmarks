#ifndef VECTORFLOATSTRUCT4YAS_H
#define VECTORFLOATSTRUCT4YAS_H

#pragma once
#include <iostream>
#include <fstream>
#include <SerializationBenchmarkUtils.h>
#include <VectorFloatStruct.h>
#include <yas/binary_oarchive.hpp>
#include <yas/binary_iarchive.hpp>
#include <yas/json_oarchive.hpp>
#include <yas/json_iarchive.hpp>
#include <yas/mem_streams.hpp>
#include <yas/file_streams.hpp>
#include <yas/std_streams.hpp>
#include <yas/serialize.hpp>
#include <yas/std_types.hpp>


struct VectorFloatStruct4Yas : public VectorFloatStruct 
{
    VectorFloatStruct4Yas() : VectorFloatStruct() {};
    VectorFloatStruct4Yas(long l_size_vec) : VectorFloatStruct(l_size_vec) {};
    VectorFloatStruct4Yas(long l_size_vec, float initFloatValue) : VectorFloatStruct(l_size_vec, initFloatValue) {};

    template<typename Archive>
    void serialize(Archive & archive) {
        auto o = YAS_OBJECT_NVP("VectorFloatStruct4Yas", ("vector", _vec_f));
        archive & o;
    }
    
    yas::shared_buffer serializeVectorToJson(){
        yas::shared_buffer buf = yas::save<yas::mem | yas::json>(*this);
        return buf;
    }

    void serializeVectorToJsonFile(const std::string & jsonFileName){
        std::remove(jsonFileName.c_str());
        yas::file_ostream os(jsonFileName.c_str());
        yas::save<yas::file|yas::json>(os, (*this));
    }

    void serializeVectorToBinaryFile(const std::string & jsonFileName){
        std::remove(jsonFileName.c_str());
        yas::file_ostream os(jsonFileName.c_str());
        yas::save<yas::file | yas::binary>(os, *this);
    }

    yas::shared_buffer serializeVectorToBinaryStream(){
        return yas::save<yas::mem | yas::binary>(*this);
    }




    std::vector<float> deserializeJsonToVector(yas::shared_buffer & jsonYasBuffer){
        constexpr std::size_t flags = 
            yas::mem | 
            yas::json;

        yas::load<flags>(jsonYasBuffer, *this);
        return _vec_f;
    }

    std::vector<float> deserializeJsonFileToVector(const std::string & jsonFileName){
        yas::file_istream is(jsonFileName.c_str());
        yas::load<yas::file|yas::json>(is, *this);
        return _vec_f;
    }

    std::vector<float> deserializeBinaryFileToVector(const std::string & binaryFileName){
        yas::file_istream is(binaryFileName.c_str());
        yas::load<yas::file|yas::binary>(is, *this);
        return _vec_f;
    }
    
    std::vector<float> deserializeBinaryStreamToVector(yas::shared_buffer & jsonYasBuffer){
        yas::load<yas::mem | yas::binary>(jsonYasBuffer, *this);
        return _vec_f;
    }
};

#endif
