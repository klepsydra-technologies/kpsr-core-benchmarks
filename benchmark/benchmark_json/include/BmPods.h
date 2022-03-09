#ifndef BMPODS_H
#define BMPODS_H

#include <VectorFloatStruct4Pods.h>
#include <benchmark/benchmark.h>

namespace bmrkPods {
class BmPods
{
public:
    static void DeserializeJsonStreamToVectorAllocationsBenchmarked(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;
                deserializedVectorCereal.deserializeJsonFileToVector(filename);

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());

                pods::JsonSerializer<pods::ResizableOutputBuffer> serializer(out);
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError) {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) {
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods;
                state.ResumeTiming();

                pods::InputBuffer in(out.data(), out.size());
                pods::JsonDeserializer<pods::InputBuffer> deserializer(in);
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
            }

            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr
                << "Controller exception in DeserializeJsonStreamToVectorAllocationsBenchmarked(): "
                << std::endl;
        }
    }

    static void DeserializeJsonStreamToVectorNoAllocationsBenchmarked(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;
                deserializedVectorCereal.deserializeJsonFileToVector(filename);

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());

                pods::JsonSerializer<pods::ResizableOutputBuffer> serializer(out);
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError) {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) {
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods;
                pods::InputBuffer in(out.data(), out.size());
                pods::JsonDeserializer<pods::InputBuffer> deserializer(in);
                state.ResumeTiming();

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
            }

            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in "
                         "DeserializeJsonStreamToVectorNoAllocationsBenchmarked(): "
                      << std::endl;
        }
    }

    static void DeserializeBinaryStreamToVectorAllocationsBenchmarked(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;
                deserializedVectorCereal.deserializeJsonFileToVector(filename);

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());

                pods::BinarySerializer<decltype(out)> serializer(out);
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError) {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) {
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods;
                state.ResumeTiming();

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
            }

            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in "
                         "DeserializeBinaryStreamToVectorAllocationsBenchmarked(): "
                      << std::endl;
        }
    }

    static void DeserializeBinaryStreamToVectorNoAllocationsBenchmarked(benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;
                deserializedVectorCereal.deserializeJsonFileToVector(filename);

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());

                pods::BinarySerializer<decltype(out)> serializer(out);
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError) {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) {
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods;
                pods::InputBuffer in(out.data(), out.size());
                pods::BinaryDeserializer<decltype(in)> deserializer(in);
                state.ResumeTiming();

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
            }

            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in "
                         "DeserializeBinaryStreamToVectorNoAllocationsBenchmarked(): "
                      << std::endl;
        }
    }

    static void DeserializeBinaryStreamToVectorAllocationsBenchmarkedResizedBuffer(
        benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;
                deserializedVectorCereal.deserializeJsonFileToVector(filename);

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());

                pods::BinarySerializer<decltype(out)> serializer(out);
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError) {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) {
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods(vectorSize, 0.0);
                state.ResumeTiming();

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
            }

            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in "
                         "DeserializeBinaryStreamToVectorAllocationsBenchmarkedResizedBuffer(): "
                      << std::endl;
        }
    }

    static void DeserializeBinaryStreamToVectorNoAllocationsBenchmarkedResizedBuffer(
        benchmark::State &state)
    {
        try {
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;
                deserializedVectorCereal.deserializeJsonFileToVector(filename);

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());

                pods::BinarySerializer<decltype(out)> serializer(out);
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError) {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) {
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods(vectorSize, 0.0);
                pods::InputBuffer in(out.data(), out.size());
                pods::BinaryDeserializer<decltype(in)> deserializer(in);
                state.ResumeTiming();

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
            }

            state.SetBytesProcessed(int64_t(state.iterations()) *
                                    int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        } catch (...) {
            std::cerr << "Controller exception in "
                         "DeserializeBinaryStreamToVectorNoAllocationsBenchmarkedResizedBuffer(): "
                      << std::endl;
        }
    }
}; // end class.
} // namespace bmrkPods

#endif // BMPODS_H
