#include <VectorFloatStruct4Cereal.h>
#include <VectorFloatStruct4Pods.h>
#include <VectorFloatStruct4Yas.h>
#include <gtest/gtest.h>
#include <simdjson.h>

TEST(TS_Cereal_vs_Pods, Cereal_DeserializeJsonStringToVector_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string json_string;
            size_t retrievedVectorSize = 0;

            VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
            std::string json_str = vecInitialConditions.serializeVectorToJson();

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeJsonToVector(json_str);
            retrievedVectorSize = deserializedVectorCereal.getSize();

            EXPECT_EQ(retrievedVectorSize, vectorSize);
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVectorCereal.getVec()[i], vecInitialConditions.getVec()[i]);
            }
        }
    } catch (...) {
        std::cerr << "Controller exception in "
                     "Cereal_RetriveFloatVector_CheckRetrievedSizeAndContent_GC(): "
                  << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 31);
    }
}

TEST(TS_Cereal_vs_Pods, Cereal_DeserializeJsonFileToVector_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string json_string;
            size_t retrievedVectorSize = 0;

            VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            vecInitialConditions.serializeVectorToJsonFile(filename);

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeJsonFileToVector(filename);
            retrievedVectorSize = deserializedVectorCereal.getSize();

            EXPECT_EQ(retrievedVectorSize, vectorSize);
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVectorCereal.getVec()[i], vecInitialConditions.getVec()[i]);
            }
        }
    } catch (...) {
        std::cerr << "Controller exception in "
                     "Cereal_RetriveFloatVectorFromDiskJsonFile_CheckRetrievedSizeAndContent_GC(): "
                  << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 60);
    }
}

TEST(TS_Cereal_vs_Pods, Cereal_DeserializeBinaryFileToVector_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string json_string;
            size_t retrievedVectorSize = 0;

            VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize) + "_bin"};
            vecInitialConditions.serializeVectorToBinaryFile(filename);

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeBinaryFileToVector(filename);
            retrievedVectorSize = deserializedVectorCereal.getSize();

            EXPECT_EQ(retrievedVectorSize, vectorSize);
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVectorCereal.getVec()[i], vecInitialConditions.getVec()[i]);
            }
        }
    } catch (...) {
        std::cerr
            << "Controller exception in "
               "Cereal_RetriveFloatVectorFromDiskBinaryFile_CheckRetrievedSizeAndContent_GC(): "
            << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 90);
    }
}

TEST(TS_Cereal_vs_Pods, Cereal_DeserializeBinaryStreamToVector_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            size_t retrievedVectorSize = 0;
            std::stringstream ssWithInitialConditions;

            VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
            vecInitialConditions.serializeVectorToBinaryStream(ssWithInitialConditions);

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeBinaryStreamToVector(ssWithInitialConditions);
            retrievedVectorSize = deserializedVectorCereal.getSize();

            EXPECT_EQ(retrievedVectorSize, vectorSize);
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVectorCereal.getVec()[i], vecInitialConditions.getVec()[i]);
            }
        }

    } catch (...) {
        std::cerr << "Controller exception in Cereal_RetriveFloatVectorFromBinaryStream(): "
                  << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 120);
    }
}

TEST(TS_Cereal_vs_Pods, Cereal_DeserializeBinaryStringToVector_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            size_t retrievedVectorSize = 0;
            std::string json_string;

            VectorFloatStruct4Cereal vecInitialConditions(vectorSize);
            json_string = vecInitialConditions.serializeVectorToBinaryString();

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeBinaryStringToVector(json_string);

            retrievedVectorSize = deserializedVectorCereal.getSize();
            EXPECT_EQ(retrievedVectorSize, vectorSize);
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVectorCereal.getVec()[i], vecInitialConditions.getVec()[i]);
            }
        }

    } catch (...) {
        std::cerr << "Controller exception in Cereal_RetriveFloatVectorFromBinaryString(): "
                  << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 150);
    }
}

TEST(TS_Cereal_vs_Pods,
     Pods_DeserializeJsonStreamToVectorAllocationsBenchmarked_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeJsonFileToVector(filename);

            VectorFloatStruct4Pods vecInitialConditionsPods;
            vecInitialConditionsPods.loadFrom(deserializedVectorCereal.getVec());

            pods::ResizableOutputBuffer out;
            pods::JsonSerializer<pods::ResizableOutputBuffer> serializer(out);
            if (serializer.save(vecInitialConditionsPods) != pods::Error::NoError) {
                std::cerr << "serialization error\n";
            }

            size_t retrievedVectorSize = 0;
            VectorFloatStruct4Pods deserializedVectorPods;
            pods::InputBuffer in(out.data(), out.size());
            pods::JsonDeserializer<pods::InputBuffer> deserializer(in);
            switch (deserializer.load(deserializedVectorPods)) {
            case (pods::Error::NoError):
                break;
            case (pods::Error::ArchiveVersionMismatch):
                std::cerr << "ArchiveVersionMismatch error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 200);
                break;
            case (pods::Error::MandatoryFieldMissed):
                std::cerr << "MandatoryFieldMissed error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 204);
                break;
            case (pods::Error::OptionalFieldMissed):
                std::cerr << "OptionalFieldMissed error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 208);
                break;
            case (pods::Error::CorruptedArchive):
                std::cerr << "CorruptedArchive error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 212);
                break;
            case (pods::Error::NotEnoughMemory):
                std::cerr << "NotEnoughMemory error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 216);
                break;
            case (pods::Error::UnexpectedEnd):
                std::cerr << "UnexpectedEnd error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 220);
                break;
            case (pods::Error::SizeToLarge):
                std::cerr << "SizeToLarge error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 224);
                break;
            case (pods::Error::WriteError):
                std::cerr << "WriteError error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 228);
                break;
            case (pods::Error::ReadError):
                std::cerr << "ReadError error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 232);
                break;
            case (pods::Error::Eof):
                std::cerr << "Eof error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 236);
                break;
            case (pods::Error::UnknownError):
                std::cerr << "UnknownError error\n";
                ADD_FAILURE_AT("GT_Cereal_vs_Pods_Test.cpp", 240);
                break;
            }
            retrievedVectorSize = deserializedVectorCereal.getSize();

            EXPECT_EQ(retrievedVectorSize, vectorSize);
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVectorPods.getVec()[i], deserializedVectorCereal.getVec()[i]);
            }
        }
    } catch (...) {
        std::cerr
            << "Controller exception in Pods_RetriveFromJson_CheckRetrievedSizeAndContent_GC(): "
            << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 254);
    }
}

TEST(TS_Cereal_vs_Pods,
     Pods_DeserializeBinaryStreamToVectorAllocationsBenchmarked_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeJsonFileToVector(filename);

            VectorFloatStruct4Pods vec_pods_initial_conditions;
            vec_pods_initial_conditions.loadFrom(deserializedVectorCereal.getVec());

            pods::ResizableOutputBuffer out;
            pods::BinarySerializer<decltype(out)> serializer(out);
            if (serializer.save(vec_pods_initial_conditions) != pods::Error::NoError) {
                std::cerr << "serialization error\n";
            }

            size_t retrievedVectorSize = 0;
            VectorFloatStruct4Pods deserializedVectorPods;
            pods::InputBuffer in(out.data(), out.size());
            pods::BinaryDeserializer<decltype(in)> deserializer(in);
            switch (deserializer.load(deserializedVectorPods)) {
            case (pods::Error::NoError):
                break;
            case (pods::Error::ArchiveVersionMismatch):
                std::cerr << "ArchiveVersionMismatch error\n";
                break;
            case (pods::Error::MandatoryFieldMissed):
                std::cerr << "MandatoryFieldMissed error\n";
                break;
            case (pods::Error::OptionalFieldMissed):
                std::cerr << "OptionalFieldMissed error\n";
                break;
            case (pods::Error::CorruptedArchive):
                std::cerr << "CorruptedArchive error\n";
                break;
            case (pods::Error::NotEnoughMemory):
                std::cerr << "NotEnoughMemory error\n";
                break;
            case (pods::Error::UnexpectedEnd):
                std::cerr << "UnexpectedEnd error\n";
                break;
            case (pods::Error::SizeToLarge):
                std::cerr << "SizeToLarge error\n";
                break;
            case (pods::Error::WriteError):
                std::cerr << "WriteError error\n";
                break;
            case (pods::Error::ReadError):
                std::cerr << "ReadError error\n";
                break;
            case (pods::Error::Eof):
                std::cerr << "Eof error\n";
                break;
            case (pods::Error::UnknownError):
                std::cerr << "UnknownError error\n";
                break;
            }
            retrievedVectorSize = deserializedVectorCereal.getSize();

            EXPECT_EQ(retrievedVectorSize, vectorSize);
            for (long i = 0; i < retrievedVectorSize; i++) {
                EXPECT_EQ(deserializedVectorPods.getVec()[i], deserializedVectorCereal.getVec()[i]);
            }
        }
    } catch (...) {
        std::cerr
            << "Controller exception in "
               "Pods_RetriveFromBinaryAllocationsBenchmarked_CheckRetrievedSizeAndContent_GC(): "
            << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 333);
    }
}

TEST(TS_Cereal_vs_Pods,
     Pods_DeserializeBinaryStreamToVectorAllocationsBenchmarkedResizedBuffer_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            pods::ResizableOutputBuffer out;

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeJsonFileToVector(filename);

            VectorFloatStruct4Pods vecPodsInitialConditions;
            vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());

            pods::BinarySerializer<decltype(out)> serializer(out);
            if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError) {
                std::cerr << "serialization error\n";
            }

            size_t retrievedVectorSize = 0;
            VectorFloatStruct4Pods deserializedVectorPods(vectorSize, 0.0);
            pods::InputBuffer in(out.data(), out.size());
            pods::BinaryDeserializer<decltype(in)> deserializer(in);
            switch (deserializer.load(deserializedVectorPods)) {
            case (pods::Error::NoError):
                break;
            case (pods::Error::ArchiveVersionMismatch):
                std::cerr << "ArchiveVersionMismatch error\n";
                break;
            case (pods::Error::MandatoryFieldMissed):
                std::cerr << "MandatoryFieldMissed error\n";
                break;
            case (pods::Error::OptionalFieldMissed):
                std::cerr << "OptionalFieldMissed error\n";
                break;
            case (pods::Error::CorruptedArchive):
                std::cerr << "CorruptedArchive error\n";
                break;
            case (pods::Error::NotEnoughMemory):
                std::cerr << "NotEnoughMemory error\n";
                break;
            case (pods::Error::UnexpectedEnd):
                std::cerr << "UnexpectedEnd error\n";
                break;
            case (pods::Error::SizeToLarge):
                std::cerr << "SizeToLarge error\n";
                break;
            case (pods::Error::WriteError):
                std::cerr << "WriteError error\n";
                break;
            case (pods::Error::ReadError):
                std::cerr << "ReadError error\n";
                break;
            case (pods::Error::Eof):
                std::cerr << "Eof error\n";
                break;
            case (pods::Error::UnknownError):
                std::cerr << "UnknownError error\n";
                break;
            }
            retrievedVectorSize = deserializedVectorPods.getSize();

            EXPECT_EQ(retrievedVectorSize, vectorSize);
            for (long i = 0; i < retrievedVectorSize; i++) {
                EXPECT_EQ(deserializedVectorPods.getVec()[i], deserializedVectorCereal.getVec()[i]);
            }
        }

    } catch (...) {
        std::cerr
            << "Controller exception in Pods_RetriveFromBinaryAllocationsBenchmarkedResized(): "
            << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 412);
    }
}

TEST(TS_Cereal_vs_Yas, Yas_DeserializeFromBinaryFileToVector_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize) + "_bin"};
            size_t retrievedVectorSize = 0;

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeBinaryFileToVector(filename);

            std::string fileNameYas = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize) +
                                       "_bin_yasTest"};
            VectorFloatStruct4Yas vecYasInitialConditions;
            vecYasInitialConditions.loadFrom(deserializedVectorCereal.getVec());
            vecYasInitialConditions.serializeVectorToBinaryFile(fileNameYas);

            VectorFloatStruct4Yas deserializedVectorYas;
            deserializedVectorYas.deserializeBinaryFileToVector(fileNameYas);

            retrievedVectorSize = deserializedVectorYas.getSize();

            EXPECT_EQ(deserializedVectorYas.getSize(), vectorSize);

            retrievedVectorSize = deserializedVectorCereal.getSize();
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVectorYas.getVec()[i], deserializedVectorCereal.getVec()[i]);
            }
        }
    } catch (...) {
        std::cerr << "Controller exception in "
                     "Yas_DeserializeFromBinaryFileToVector_CheckRetrievedSizeAndContent_GC(): "
                  << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 469);
    }
}

TEST(TS_Cereal_vs_Yas, Yas_DeserializeFromBinaryStreamToVector_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize) + "_bin"};
            size_t retrievedVectorSize = 0;

            VectorFloatStruct4Cereal deserializedVectorCereal;
            deserializedVectorCereal.deserializeBinaryFileToVector(filename);

            VectorFloatStruct4Yas vecYasInitialConditions;
            vecYasInitialConditions.loadFrom(deserializedVectorCereal.getVec());
            yas::shared_buffer streamBuffer = vecYasInitialConditions.serializeVectorToBinaryStream();

            VectorFloatStruct4Yas deserializedVectorYas;
            deserializedVectorYas.deserializeBinaryStreamToVector(streamBuffer);

            retrievedVectorSize = deserializedVectorYas.getSize();

            EXPECT_EQ(deserializedVectorYas.getSize(), vectorSize);

            retrievedVectorSize = deserializedVectorCereal.getSize();
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVectorYas.getVec()[i], deserializedVectorCereal.getVec()[i]);
            }
        }
    } catch (...) {
        std::cerr << "Controller exception in "
                     "Yas_DeserializeFromBinaryStreamToVector_CheckRetrievedSizeAndContent_GC(): "
                  << std::endl;
        ADD_FAILURE_AT("GtestSerialization.cpp", 506);
    }
}

TEST(TS_Cereal_vs_Simdjson,
     Simdjson_RetriveUsingGetArrayAndCountElements_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);
            size_t retrievedVectorSize = 0;

            simdjson::ondemand::parser parser;
            auto doc = parser.iterate(json_string);
            simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();
            retrievedVectorSize = jsonVectorFloat.count_elements();
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

            EXPECT_EQ(deserializedVector.size(), vectorSize);

            VectorFloatStruct4Cereal vecInitialConditions;
            vecInitialConditions.deserializeJsonFileToVector(filename);
            retrievedVectorSize = vecInitialConditions.getSize();
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVector[i], vecInitialConditions.getVec()[i]);
            }
        }

    } catch (simdjson::simdjson_error &e) {
        std::cerr
            << "Controller exception in "
               "Simdjson_RetriveUsingGetArrayAndCountElements_CheckRetrievedSizeAndContent_GC(): "
            << std::endl;
        ADD_FAILURE_AT("GT_Cereal_vs_Simdjson_Test.cpp", 571);
    }
}

TEST(TS_Cereal_vs_Simdjson,
     Simdjson_RetriveUsingGetArrayWithoutCountElements_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            size_t retrievedVectorSize = 0;
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);
            std::vector<float> deserializedVector(vectorSize);

            simdjson::ondemand::parser parser;
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

            EXPECT_EQ(deserializedVector.size(), vectorSize);

            VectorFloatStruct4Cereal vecInitialConditions;
            vecInitialConditions.deserializeJsonFileToVector(filename);
            retrievedVectorSize = vecInitialConditions.getSize();
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVector[i], vecInitialConditions.getVec()[i]);
            }
        }

    } catch (simdjson::simdjson_error &e) {
        std::cerr << "Controller exception in "
                     "Simdjson_RetriveUsingGetArrayWithoutCountElements_"
                     "CheckRetrievedSizeAndContent_GC(): "
                  << std::endl;
        ADD_FAILURE_AT("GT_Cereal_vs_Simdjson_Test.cpp", 614);
    }
}

TEST(TS_Cereal_vs_Simdjson,
     Simdjson_RetriveUsingGetArrayAndCountElementsFromDiskJsonFile_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            size_t retrievedVectorSize = 0;
            simdjson::ondemand::parser parser;
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);

            auto doc = parser.iterate(json_string);
            simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();
            retrievedVectorSize = jsonVectorFloat.count_elements();
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

            EXPECT_EQ(deserializedVector.size(), vectorSize);

            VectorFloatStruct4Cereal vecInitialConditions;
            vecInitialConditions.deserializeJsonFileToVector(filename);
            retrievedVectorSize = vecInitialConditions.getSize();
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVector[i], vecInitialConditions.getVec()[i]);
            }
        }

    } catch (simdjson::simdjson_error &e) {
        std::cerr << "Controller exception in "
                     "Simdjson_RetriveUsingGetArrayAndCountElementsFromDiskJsonFile_"
                     "CheckRetrievedSizeAndContent_GC(): "
                  << std::endl;
        ADD_FAILURE_AT("GT_Cereal_vs_Simdjson_Test.cpp", 659);
    }
}

TEST(TS_Cereal_vs_Simdjson,
     Simdjson_RetriveUsingGetArrayWithoutCountElementsFromDiskJsonFile_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            size_t retrievedVectorSize = 0;
            simdjson::ondemand::parser parser;
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);

            auto doc = parser.iterate(json_string);
            simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();
            std::vector<float> deserializedVector(vectorSize);

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

            EXPECT_EQ(deserializedVector.size(), vectorSize);

            VectorFloatStruct4Cereal vecInitialConditions;
            vecInitialConditions.deserializeJsonFileToVector(filename);
            retrievedVectorSize = vecInitialConditions.getSize();
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ(deserializedVector[i], vecInitialConditions.getVec()[i]);
            }
        }

    } catch (simdjson::simdjson_error &e) {
        std::cerr << "Controller exception in "
                     "Simdjson_RetriveUsingGetArrayWithoutCountElementsFromDiskJsonFile_"
                     "CheckRetrievedSizeAndContent_GC(): "
                  << std::endl;
        ADD_FAILURE_AT("GT_Cereal_vs_Simdjson_Test.cpp", 702);
    }
}

TEST(TS_Cereal_vs_Simdjson,
     Simdjson_RetriveUsingGetArrayDoubleWithoutCountElements_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            size_t retrievedVectorSize = 0;
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);
            simdjson::ondemand::parser parser;

            auto doc = parser.iterate(json_string);
            simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();
            std::vector<double> deserializedVector(vectorSize);

            size_t index = 0;
            for (auto value : jsonVectorFloat) {
                auto error = value.get_double().get(deserializedVector[index++]);
                if (error) {
                    std::cerr << "Error in value.get_double(): " << error << std::endl;
                    return;
                }
            }

            EXPECT_EQ(deserializedVector.size(), vectorSize);

            VectorFloatStruct4Cereal vecInitialConditions;
            vecInitialConditions.deserializeJsonFileToVector(filename);
            retrievedVectorSize = vecInitialConditions.getSize();
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ((static_cast<float>(deserializedVector[i])),
                          vecInitialConditions.getVec()[i]);
            }
        }

    } catch (simdjson::simdjson_error &e) {
        std::cerr << "Controller exception in "
                     "Simdjson_RetriveUsingGetArrayDoubleWithoutCountElements_"
                     "CheckRetrievedSizeAndContent_GC(): "
                  << std::endl;
        ADD_FAILURE_AT("GT_Cereal_vs_Simdjson_Test.cpp", 743);
    }
}

TEST(TS_Cereal_vs_Simdjson,
     Simdjson_RetriveUsingGetArrayDoubleWithoutCountElementsFromDiskJsonFile_CheckRetrievedSizeAndContent_GC)
{
    try {
        for (long vectorSize = BM_DENSE_RANGE_START; vectorSize < BM_DENSE_RANGE_END;
             (vectorSize += BM_DENSE_RANGE_INCR)) {
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};
            size_t retrievedVectorSize = 0;
            simdjson::ondemand::parser parser;
            simdjson::padded_string json_string = simdjson::padded_string::load(filename);

            auto doc = parser.iterate(json_string);
            simdjson::ondemand::array jsonVectorFloat = doc.find_field("vector").get_array();
            std::vector<double> deserializedVector(vectorSize);

            size_t index = 0;
            for (auto value : jsonVectorFloat) {
                auto error = value.get_double().get(deserializedVector[index++]);
                if (error) {
                    std::cerr << "Error in value.get_double(): " << error << std::endl;
                    return;
                }
            }

            EXPECT_EQ(deserializedVector.size(), vectorSize);

            VectorFloatStruct4Cereal vecInitialConditions;
            vecInitialConditions.deserializeJsonFileToVector(filename);
            retrievedVectorSize = vecInitialConditions.getSize();
            for (long i = 0; i < vectorSize; i++) {
                EXPECT_EQ((static_cast<float>(deserializedVector[i])),
                          vecInitialConditions.getVec()[i]);
            }
        }

    } catch (simdjson::simdjson_error &e) {
        std::cerr << "Controller exception in "
                     "Simdjson_RetriveUsingGetArrayDoubleWithoutCountElementsFromDiskJsonFile_"
                     "CheckRetrievedSizeAndContent_GC(): "
                  << std::endl;
        ADD_FAILURE_AT("GT_Cereal_vs_Simdjson_Test.cpp", 784);
    }
}
