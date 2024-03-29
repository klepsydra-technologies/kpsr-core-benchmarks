// Copyright 2023 Klepsydra Technologies AG
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <BmCereal.h>
#include <BmPods.h>
#include <BmSimdjson.h>
#include <BmYas.h>
#include <benchmark/benchmark.h>

//Cereal
BENCHMARK(bmrkCereal::BmCereal::DeserializeJsonStringToVector)
    ->Name("BmCereal::DeserializeJsonStringToVector")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkCereal::BmCereal::DeserializeJsonFileToVector)
    ->Name("BmCereal::DeserializeJsonFileToVector")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkCereal::BmCereal::DeserializeBinaryFileToVector)
    ->Name("BmCereal::DeserializeBinaryFileToVector")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkCereal::BmCereal::DeserializeBinaryStreamToVector)
    ->Name("BmCereal::DeserializeBinaryStreamToVector")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkCereal::BmCereal::DeserializeBinaryStringToVector)
    ->Name("BmCereal::DeserializeBinaryStringToVector")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

//Pods
BENCHMARK(bmrkPods::BmPods::DeserializeJsonStreamToVectorAllocationsBenchmarked)
    ->Name("BmPods::DeserializeJsonStreamToVectorAllocationsBenchmarked")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkPods::BmPods::DeserializeJsonStreamToVectorNoAllocationsBenchmarked)
    ->Name("BmPods::DeserializeJsonStreamToVectorNoAllocationsBenchmarked")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkPods::BmPods::DeserializeBinaryStreamToVectorAllocationsBenchmarked)
    ->Name("BmPods::DeserializeBinaryStreamToVectorAllocationsBenchmarked")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkPods::BmPods::DeserializeBinaryStreamToVectorNoAllocationsBenchmarked)
    ->Name("BmPods::DeserializeBinaryStreamToVectorNoAllocationsBenchmarked")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkPods::BmPods::DeserializeBinaryStreamToVectorAllocationsBenchmarkedResizedBuffer)
    ->Name("BmPods::DeserializeBinaryStreamToVectorAllocationsBenchmarkedResizedBuffer")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkPods::BmPods::DeserializeBinaryStreamToVectorNoAllocationsBenchmarkedResizedBuffer)
    ->Name("BmPods::DeserializeBinaryStreamToVectorNoAllocationsBenchmarkedResizedBuffer")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

// Yas
BENCHMARK(bmrkYas::BmYas::DeserializeFromJsonMemoryBufferToVector)
    ->Name("BmYas::DeserializeFromJsonMemoryBufferToVector")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkYas::BmYas::DeserializeFromJsonFileToVector)
    ->Name("BmYas::DeserializeFromJsonFileToVector")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkYas::BmYas::DeserializeFromBinaryFileToVector)
    ->Name("BmYas::DeserializeFromBinaryFileToVector")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkYas::BmYas::DeserializeFromBinaryStreamToVector)
    ->Name("BmYas::DeserializeFromBinaryStreamToVector")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

// Simdjson
BENCHMARK(bmrkSimdjson::BmSimdjson::DeserializeUsingGetArrayAndCountElements)
    ->Name("BmSimdjson::DeserializeUsingGetArrayAndCountElements")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkSimdjson::BmSimdjson::DeserializeUsingGetArrayWithoutCountElements)
    ->Name("BmSimdjson::DeserializeUsingGetArrayWithoutCountElements")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkSimdjson::BmSimdjson::DeserializeUsingGetArrayAndCountElementsFromDiskJsonFile)
    ->Name("BmSimdjson::DeserializeUsingGetArrayAndCountElementsFromDiskJsonFile")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkSimdjson::BmSimdjson::DeserializeUsingGetArrayWithoutCountElementsFromDiskJsonFile)
    ->Name("BmSimdjson::DeserializeUsingGetArrayWithoutCountElementsFromDiskJsonFile")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(bmrkSimdjson::BmSimdjson::DeserializeUsingGetArrayDoubleWithoutCountElements)
    ->Name("BmSimdjson::DeserializeUsingGetArrayDoubleWithoutCountElements")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK(
    bmrkSimdjson::BmSimdjson::DeserializeUsingGetArrayDoubleWithoutCountElementsFromDiskJsonFile)
    ->Name("BmSimdjson::DeserializeUsingGetArrayDoubleWithoutCountElementsFromDiskJsonFile")
    ->UseRealTime()
    ->ArgsProduct({benchmark::CreateDenseRange(BM_DENSE_RANGE_START,
                                               BM_DENSE_RANGE_END,
                                               BM_DENSE_RANGE_INCR)});

BENCHMARK_MAIN();