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

#ifndef VECTORFLOATSTRUCT4CEREAL_H
#define VECTORFLOATSTRUCT4CEREAL_H

#pragma once
#include <SerializationBenchmarkUtils.h>
#include <VectorFloatStruct.h>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>
#include <fstream>
#include <iostream>

struct VectorFloatStruct4Cereal : public VectorFloatStruct
{
    VectorFloatStruct4Cereal()
        : VectorFloatStruct(){};
    VectorFloatStruct4Cereal(long l_size_vec)
        : VectorFloatStruct(l_size_vec){};
    VectorFloatStruct4Cereal(long l_size_vec, float initFloatValue)
        : VectorFloatStruct(l_size_vec, initFloatValue){};

    friend class cereal::access;

    template<class Archive>
    void serialize(Archive &archive)
    {
        archive(cereal::make_nvp("vector", _vec_f));
    }

    void serializeVectorToJsonFile(const std::string &filename_string)
    {
        std::ofstream os(filename_string);
        {
            cereal::JSONOutputArchive archive_out(os);
            serialize(archive_out);
        }
        return;
    }

    std::string serializeVectorToJson()
    {
        std::stringstream os;
        {
            cereal::JSONOutputArchive archive_out(os);
            serialize(archive_out);
        }
        return os.str();
    }

    void serializeVectorToBinaryFile(const std::string &filename_string)
    {
        std::ofstream os(filename_string, std::ios::binary);
        {
            cereal::BinaryOutputArchive archive_out(os);
            serialize(archive_out);
        }
        return;
    }

    std::string serializeVectorToBinaryString()
    {
        std::stringstream ss;
        {
            cereal::BinaryOutputArchive archive_out(ss);
            serialize(archive_out);
        }
        return ss.str();
    }

    void serializeVectorToBinaryStream(std::stringstream &ss)
    {
        std::stringstream is;
        {
            cereal::BinaryOutputArchive archive_out(is);
            serialize(archive_out);
        }
        ss << is.rdbuf();
    }

    std::vector<float> deserializeJsonToVector(const std::string &json_string)
    {
        std::stringstream is(json_string);
        {
            cereal::JSONInputArchive archive_in(is);
            serialize(archive_in);
        }
        return _vec_f;
    }

    std::vector<float> deserializeJsonFileToVector(const std::string &filename_string)
    {
        std::ifstream is(filename_string);
        {
            cereal::JSONInputArchive archive_in(is);
            serialize(archive_in);
        }
        return _vec_f;
    }

    std::vector<float> deserializeBinaryFileToVector(const std::string &filename_string)
    {
        std::ifstream is(filename_string);
        {
            cereal::BinaryInputArchive archive_in(is);
            serialize(archive_in);
        }
        return _vec_f;
    }

    std::vector<float> deserializeBinaryStringToVector(const std::string &json_string)
    {
        std::stringstream ss(json_string);
        {
            cereal::BinaryInputArchive archive_in(ss);
            serialize(archive_in);
        }
        return _vec_f;
    }

    std::vector<float> deserializeBinaryStreamToVector(std::stringstream &is)
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
