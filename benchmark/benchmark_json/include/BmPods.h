#ifndef BMPODS_H
#define BMPODS_H

#include <benchmark/benchmark.h>
#include <VectorFloatStruct4Pods.h>

namespace bmrkPods {
class BmPods
{
public:
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    // benchmarks: Deserialize existing JSON string to memory structures.
    //
    // This test benchmarks spent time deserializing an existing JSON formatted string
    // of std::vector<float>, to a memory std::vector<float> with as many floats as
    // in JSON vector representation loaded.
    //
    // Pods seems not easy to fit a previous serialized std::vecto<float> if it does not 
    // have the expected JSON structure by Pods. When serializes a std::vector>float> 
    // creates a json string as below.
    // "{\"__version\":1,\"_vec_f\":{\"__size\":1024,\"__data\":[2.034305400836659e37,
    // 2.304417202029674e38,3.0840754610831969e38,2.489590936756805e38,
    // ......
    // ......
    // 4.044533553232823e37,6.322436778132219e37,2.9630624924239696e38]}}"
    //
    // But previous existing JSON created by Cereal, has a different output for a 
    // std::vector<float> thus, retrieve float set using same structure is not trivial.
    //
    // This test solves this undesired complexity retrieving float set using cereal
    // over a std::vector<float> memory region using well-known myVectorFloat object.
    // Once std::vector<float> is retrieved, is used to build required 
    // pods::ResizableOutputBuffer with float vector contents. This pods buffer will
    // be used later as needed input parameter of deserialization pods procedure which
    // loads VectorFloatStruct4Pods deserializedVector object. 
    // 
    //
    // TO BE DISCUSSED.
    // Benchmarked time considers to register time spent in buffer allocation due to
    // pods instructions:
    // pods::InputBuffer in(out.data(), out.size());
    // pods::JsonDeserializer<pods::InputBuffer> deserializer(in);
    //
    // Must be discussed if we need to benchmark time used in deserialization only or
    // in the real whole need related to use case. If last approach must be used, time
    // spent in buffer allocation SHALL BE considered.
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeJsonStreamToVectorAllocationsBenchmarked(benchmark::State &state)
    {
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;                                  // Use Cereal to load from disk.
                deserializedVectorCereal.deserializeJsonFileToVector(filename); 

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());               // Load initial conditions from previous Cereal load.

                
                pods::JsonSerializer<pods::ResizableOutputBuffer> serializer(out);                  // Generate Buffer needed by next deserialization.
                if(serializer.save(vecPodsInitialConditions) != pods::Error::NoError){
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) 
            {   
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods;
                state.ResumeTiming();

                pods::InputBuffer in(out.data(), out.size());                                       // Memory allocation benchmarked.
                pods::JsonDeserializer<pods::InputBuffer> deserializer(in);
                switch(deserializer.load(deserializedVectorPods)){
                    case (pods::Error::NoError):
                        //std::cout << "SUCCESS\n";
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

            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;
        
        }catch(...) {
            std::cerr << "Controller exception in DeserializeJsonStreamToVectorAllocationsBenchmarked(): "  
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    // NOTE: This test seems not be possible due to google benchamrk for(auto _ : state)
    // loop procedure meaning. Must be studied to undertand deply how it works and what
    // limitations we have when considering benchmarking designs.
    // In this case, seems out stream received by InputBuffer must be sent again to
    // InputBuffer in each loop of for.
    //
    // benchmarks: Deserialize existing JSON string to memory structures.
    //
    // The other case than previous. This case DOES NOT benchmarks time spent in 
    // allocate buffers needed by pods due to instructions below:
    // pods::InputBuffer in(out.data(), out.size());
    // pods::JsonDeserializer<pods::InputBuffer> deserializer(in);
    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    //static void Pods_RetriveNoAllocationsBenchmarked(benchmark::State &state)
    static void DeserializeJsonStreamToVectorNoAllocationsBenchmarked(benchmark::State &state)
    {    
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};          // WARNING: Precompiler variable created through root CMakeLists file.

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;                                  // Use Cereal to load from disk.
                deserializedVectorCereal.deserializeJsonFileToVector(filename); 

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());               // Load initial conditions from previous Cereal load.

                
                pods::JsonSerializer<pods::ResizableOutputBuffer> serializer(out);                  // Generate Buffer needed by next deserialization.
                if(serializer.save(vecPodsInitialConditions) != pods::Error::NoError){
                    std::cerr << "serialization error\n";
                }
            }
            
            size_t retrievedVectorSize = 0;
            for (auto _ : state) 
            {
                state.PauseTiming(); 
                VectorFloatStruct4Pods deserializedVectorPods;
                pods::InputBuffer in(out.data(), out.size());                                       // Memory allocation NOT benchmarked.
                pods::JsonDeserializer<pods::InputBuffer> deserializer(in);
                state.ResumeTiming();

                switch(deserializer.load(deserializedVectorPods)){
                    case (pods::Error::NoError):
                        //std::cout << "SUCCESS\n";
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

            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeJsonStreamToVectorNoAllocationsBenchmarked(): "  
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeBinaryStreamToVectorAllocationsBenchmarked(benchmark::State &state)
    {    
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};          // WARNING: Precompiler variable created through root CMakeLists file.

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;                                  // Use Cereal to load from disk.
                deserializedVectorCereal.deserializeJsonFileToVector(filename); 

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());               // Load initial conditions from previous Cereal load.

                
                pods::BinarySerializer<decltype(out)> serializer(out);                              // Generate Buffer needed by next deserialization.
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError)
                {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) 
            {
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods;
                state.ResumeTiming();

                pods::InputBuffer in(out.data(), out.size());
                pods::BinaryDeserializer<decltype(in)> deserializer(in);
                switch(deserializer.load(deserializedVectorPods)){
                    case (pods::Error::NoError):
                        //std::cout << "SUCCESS\n";
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

            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryStreamToVectorAllocationsBenchmarked(): "  
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeBinaryStreamToVectorNoAllocationsBenchmarked(benchmark::State &state)
    {    
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};          // WARNING: Precompiler variable created through root CMakeLists file.

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;                                  // Use Cereal to load from disk.
                deserializedVectorCereal.deserializeJsonFileToVector(filename); 

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());               // Load initial conditions from previous Cereal load.

                pods::BinarySerializer<decltype(out)> serializer(out);                              // Generate Buffer needed by next deserialization.
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError)
                {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) 
            {   
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods;
                pods::InputBuffer in(out.data(), out.size());
                pods::BinaryDeserializer<decltype(in)> deserializer(in);
                state.ResumeTiming();
                
                switch(deserializer.load(deserializedVectorPods)){
                    case (pods::Error::NoError):
                        //std::cout << "SUCCESS\n";
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

            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryStreamToVectorNoAllocationsBenchmarked(): "  
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeBinaryStreamToVectorAllocationsBenchmarkedResizedBuffer(benchmark::State &state)
    {    
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};          // WARNING: Precompiler variable created through root CMakeLists file.

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;                                  // Use Cereal to load from disk.
                deserializedVectorCereal.deserializeJsonFileToVector(filename); 

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());               // Load initial conditions from previous Cereal load.
                
                pods::BinarySerializer<decltype(out)> serializer(out);                              // Generate Buffer needed by next deserialization.
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError)
                {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) 
            {
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods(vectorSize, 0.0);
                state.ResumeTiming();

                pods::InputBuffer in(out.data(), out.size());
                pods::BinaryDeserializer<decltype(in)> deserializer(in);
                switch(deserializer.load(deserializedVectorPods)){
                    case (pods::Error::NoError):
                        //std::cout << "SUCCESS\n";
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

            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;

        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryStreamToVectorAllocationsBenchmarkedResizedBuffer(): "  
                << std::endl; 
        }
    }




    // ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- 
    static void DeserializeBinaryStreamToVectorNoAllocationsBenchmarkedResizedBuffer(benchmark::State &state)
    {    
        try{
            long vectorSize = state.range(0);
            std::string filename = {JSON_FILE_PATH_AND_NAME + std::to_string(vectorSize)};          // WARNING: Precompiler variable created through root CMakeLists file.

            pods::ResizableOutputBuffer out;
            {
                VectorFloatStruct4Cereal deserializedVectorCereal;                                  // Use Cereal to load from disk.
                deserializedVectorCereal.deserializeJsonFileToVector(filename); 

                VectorFloatStruct4Pods vecPodsInitialConditions;
                vecPodsInitialConditions.loadFrom(deserializedVectorCereal.getVec());               // Load initial conditions from previous Cereal load.

                pods::BinarySerializer<decltype(out)> serializer(out);                              // Generate Buffer needed by next deserialization.
                if (serializer.save(vecPodsInitialConditions) != pods::Error::NoError)
                {
                    std::cerr << "serialization error\n";
                }
            }

            size_t retrievedVectorSize = 0;
            for (auto _ : state) 
            {   
                state.PauseTiming();
                VectorFloatStruct4Pods deserializedVectorPods(vectorSize, 0.0);
                pods::InputBuffer in(out.data(), out.size());
                pods::BinaryDeserializer<decltype(in)> deserializer(in);
                state.ResumeTiming();
                
                switch(deserializer.load(deserializedVectorPods)){
                    case (pods::Error::NoError):
                        //std::cout << "SUCCESS\n";
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

            state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
            state.counters["retrievedVectorSz"] = retrievedVectorSize;
            
        }catch(...) {
            std::cerr << "Controller exception in DeserializeBinaryStreamToVectorNoAllocationsBenchmarkedResizedBuffer(): "  
                << std::endl; 
        }
    }
};// end class.
}// end namespace.


#endif // BMPODS_H
