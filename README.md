<p align="right">
  <img width="25%" height="25%"src="./images/klepsydra_logo.jpg">
</p>

[![Check build](https://github.com/klepsydra-technologies/kpsr-core-benchmarks/actions/workflows/push.yml/badge.svg?branch=main)](https://github.com/klepsydra-technologies/kpsr-core-benchmarks/actions/workflows/push.yml) [![Code style check](https://github.com/klepsydra-technologies/kpsr-core-benchmarks/actions/workflows/prcodecheck.yml/badge.svg?branch=main)](https://github.com/klepsydra-technologies/kpsr-core-benchmarks/actions/workflows/prcodecheck.yml) [![codecov](https://codecov.io/gh/klepsydra-technologies/kpsr-core-benchmarks/branch/main/graph/badge.svg?token=PDALQNPJRD)](https://codecov.io/gh/klepsydra-technologies/kpsr-core-benchmarks)

# Installation Instructions

## System dependencies

* Tested in Ubuntu 20.04 LTS
* Cmake 3.5.1 or above
* gcc for C++11 5.4.0 or above.
* Python 3.6 or above

### Dependencies installed by kpsr-core-benchmarks

* Google Benchmark (<https://github.com/google/benchmark.git>)
* Google Test (<https://github.com/klepsydra-technologies/googletest>)
* Simdjson (<https://github.com/simdjson/simdjson.git>)
* Cereal (<https://github.com/klepsydra-technologies/cereal>)
* Pods (<https://github.com/mtrempoltsev/pods.git>)
* Yas (<https://github.com/niXman/yas.git>)

## Related docs

* [Tool Preparation](./analysis/TOOL_PREPARATION.md)
* [Tool Execution](./analysis/TOOL_EXECUTION.md)

## System requirements

```bash
sudo apt-get install build-essential
sudo apt-get install git
sudo apt-get install cmake
sudo apt-get install python3-pip
```

## Installation

Given ```$KLEPSYDRA_HOME```, for example ```$HOME/klepsydra```:

```bash
cd $KLEPSYDRA_HOME
git clone https://github.com/klepsydra-technologies/kpsr-core-benchmarks.git
cd kpsr-core-benchmarks
git submodule update --init --recursive
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="/home/user/klepsydra/community/install" -DCMAKE_INSTALL_PREFIX="/home/user/klepsydra/community/install"
make
sudo make install
```

This cmake exampple proposal will expect dependencies as kpsr-core installed in folder specifed in cmake directive DCMAKE_PREFIX_PATH (i.e. below):

```bash
-DCMAKE_PREFIX_PATH="/home/user/klepsydra/community/install"
```

or default locations of klepsydra installation:

* `/usr/local/include/klepsydra` for kpsr-core include files
* `/usr/local/include/kpsr_3parties` for third party dependencies necessary for Klepsydra package
* `/usr/local/lib/` for kpsr-core libraries

The cmake has the following featured options:

* -DGBENCHMARK_PATH: if new path not specified, thirdparties/benchmark will be used.
* -DGOOGLETEST_PATH: if new path not specified, thirdparties/googletest will be used.
* -DCMAKE_PREFIX_PATH for specifying where to look up for installed dependencies as current Klepsydra installation location (/usr/local by default)
* -DCMAKE_INSTALL_PREFIX to specify where to install binaries, if **make install** executed.
**out.txt** will be created in exection folder (/build if used to execute as example below **./bin/kpsr_benchmark_json_test**)
* -DJSON_FILE_PATH_AND_NAME used to specify json output files created sequentialy by Cereal TCs when generate random std::vector< float > which will be used to generate the json files used as initial conditions of each benchamrk test. For each size of the vector benchmarked, will be generated a json initial file using this prefix and adding at the end the size number of the vector benchmarked.
* -DBM_DENSE_RANGE_START benchmarks uses DenseRange for vectorSize from START to END with INCR. If _START not specified 1024 will be used.
* -DBM_DENSE_RANGE_END benchmarks uses DenseRange for vectorSize from START to END with INCR. If _END not specified 102400 will be used.
* -DBM_DENSE_RANGE_INCR benchmarks uses DenseRange for vectorSize from START to END with INCR. If _INCR not specified 1024 will be used.  

Example

```bash
cmake .. 
-DCMAKE_PREFIX_PATH="/home/jose/klepsydra/klepsydra/development/community/install" 
-DCMAKE_INSTALL_PREFIX="/home/jose/klepsydra/klepsydra/development/community/install" 
-DBM_DENSE_RANGE_START=1024 
-DBM_DENSE_RANGE_END=102400 
-DBM_DENSE_RANGE_INCR=9216
```

## Google Benchmak support

Test case target project cxx03_test is not supported by kpsr-core thus, will be not compiled.

To use UserCounters column-tabbed please, use the command line argument **--benchmark_counters_tabular=true** after the test executable.
To specify output file needed to be used with compare.py script tool, please use the command line argument **--benchmark_out=bm.out**.

```bash
user@ubuntu:~/kpsr-core-benchmarks/build$ ./bin/kpsr_benchmark_core_test --benchmark_counters_tabular=true --benchmark_out=bm.out
```

## Cereal & SimdJSON & Pods & Yas support

Test cases has been designed to check how benchmark differs when serializing same json input stream of `std::vector<float>` using all of them, Cereal, SimdJSON, Pods and Yas serializers.

```bash
user@ubuntu:~/kpsr-core-benchmarks/build$ ./bin/kpsr_benchmark_json_test --benchmark_counters_tabular=true
```

### Note about cmake directives related to JSON files

These benchmark TCs has been designed to be executed sequentialy. First, Cereal TCs are executed and creates serialized json files to disk, as initial conditions. Once initial conditions about benchmarking are set, Retrive_xxx std::vector< float > benchmark cases uses these disk json files in SimdJSON to DESERIALIZE these file expressed vector in a memory std::vector< float > vector variable with the same size.

In the first step of creating these json files as initial conditions, plays a key role the benchmark parameter about size of vector to be benchmrked. Test uses a **->DenseRange(1024, 102400, 1<<10)** as vector size. This means one test json file is created to disk for each size, using as name, the concatenation of filepath provided by JSON_FILE_PATH_AND_NAME and vector size at the end of the string.

Default values for DenseRange are **->DenseRange(1024, 102400, 1024)**. If these values do not fit your needs, you can use featured cmake variables **-DBM_DENSE_RANGE_START, --DBM_DENSE_RANGE_END & D--BM_DENSE_RANGE_INCR**.

Example:

If we cmake as below:

```bash
cmake .. 
-DCMAKE_PREFIX_PATH="/home/jose/klepsydra/klepsydra/development/community/install"
-DCMAKE_INSTALL_PREFIX="/home/jose/klepsydra/klepsydra/development/community/install" 
-DJSON_FILE_PATH_AND_NAME="/home/jose/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/build/my_cereal_json_str.txt"
-DBM_DENSE_RANGE_START=1024 
-DBM_DENSE_RANGE_END=102400 
-DBM_DENSE_RANGE_INCR=9216
```

When **kpsr_benchmark_core_test** test is executed, a set of files will be created for each size of the vector as below:

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/build$ ll
total 87924
drwxrwxr-x 7 jose jose    4096 Feb 26 00:22 ./
drwxrwxr-x 7 jose jose    4096 Feb 26 00:08 ../
drwxrwxr-x 5 jose jose    4096 Feb 26 00:08 benchmark/
drwxrwxr-x 2 jose jose    4096 Feb 26 00:13 bin/
-rw-rw-r-- 1 jose jose   30290 Feb 26 00:08 CMakeCache.txt
drwxrwxr-x 4 jose jose    4096 Feb 26 00:13 CMakeFiles/
-rw-rw-r-- 1 jose jose    2283 Feb 26 00:08 cmake_install.cmake
drwxrwxr-x 2 jose jose    4096 Feb 26 00:12 lib/
-rw-rw-r-- 1 jose jose   30797 Feb 26 00:08 Makefile
-rw-rw-r-- 1 jose jose   31250 Feb 26 00:19 my_cereal_json_str.txt1024
-rw-rw-r-- 1 jose jose  312296 Feb 26 00:19 my_cereal_json_str.txt10240
-rw-rw-r-- 1 jose jose  343454 Feb 26 00:19 my_cereal_json_str.txt11264
-rw-rw-r-- 1 jose jose  374673 Feb 26 00:19 my_cereal_json_str.txt12288
-rw-rw-r-- 1 jose jose  406096 Feb 26 00:19 my_cereal_json_str.txt13312
...
...
-rw-rw-r-- 1 jose jose  281092 Feb 26 00:19 my_cereal_json_str.txt9216
-rw-rw-r-- 1 jose jose 3123179 Feb 26 00:19 my_out_cereal.txt
drwxrwxr-x 5 jose jose    4096 Feb 26 00:08 thirdparties/
```

As is shown, ***my_cereal_json_str.txt*****1024** file is the concatenation of the filename set through ***DJSON_FILE_PATH_AND_NAME*** and **vector size** for this benchmark test.

**NOTE**: If DJSON_FILE_PATH_AND_NAME is not specified, default **cereal_json_str.txt** filename will be used.

**NOTE**: bytes_per_second Counter is calculated as in google benchmark examples but for float size. See below. For binary serialization has not been considered the real serialized size stream. Has been considered the total bytes in floats into the std::vector< float > array to calulate the bytes processed. Its a messure of our real worth processed and not the real binary stream processed.

```bash
state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(retrievedVectorSize * sizeof(float)));
```

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/kpsr-core-benchmarks_pushed/build$ ./bin/kpsr_benchmark_json_test --benchmark_counters_tabular=true --benchmark_out=bm.out
2022-03-05T20:46:07+01:00
Running ./bin/kpsr_benchmark_json_test
Run on (32 X 2394.01 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x32)
  L1 Instruction 32 KiB (x32)
  L2 Unified 1024 KiB (x32)
  L3 Unified 36608 KiB (x2)
Load Average: 3.61, 1.66, 0.93
---------------------------------------------------------------------------------------------------------------------------------------------------------
Benchmark                                                                            Time             CPU   Iterations bytes_per_second retrievedVectorSz
---------------------------------------------------------------------------------------------------------------------------------------------------------
BmCereal::DeserializeJsonStringToVector/1024/real_time                          321860 ns       321694 ns         2435       12.1365M/s              1024
BmCereal::DeserializeJsonStringToVector/10240/real_time                        3510287 ns      3509987 ns          178        11.128M/s            10.24k
BmCereal::DeserializeJsonStringToVector/19456/real_time                        6099882 ns      6095299 ns          130       12.1672M/s           19.456k
BmCereal::DeserializeJsonStringToVector/28672/real_time                        7614730 ns      7614214 ns           72       14.3636M/s           28.672k
BmCereal::DeserializeJsonStringToVector/37888/real_time                       10447849 ns     10445162 ns           71       13.8336M/s           37.888k
BmCereal::DeserializeJsonStringToVector/47104/real_time                       12775893 ns     12774863 ns           54       14.0646M/s           47.104k
BmCereal::DeserializeJsonStringToVector/56320/real_time                       15435543 ns     15429253 ns           40       13.9188M/s            56.32k
BmCereal::DeserializeJsonStringToVector/65536/real_time                       19141684 ns     19135720 ns           40       13.0605M/s           65.536k
BmCereal::DeserializeJsonStringToVector/74752/real_time                       20037854 ns     20036301 ns           36       14.2309M/s           74.752k
BmCereal::DeserializeJsonStringToVector/83968/real_time                       23834237 ns     23827495 ns           29       13.4392M/s           83.968k
BmCereal::DeserializeJsonStringToVector/93184/real_time                       24152091 ns     24145572 ns           29       14.7179M/s           93.184k
BmCereal::DeserializeJsonStringToVector/102400/real_time                      27091990 ns     27089524 ns           24       14.4185M/s            102.4k
BmCereal::DeserializeJsonFileToVector/1024/real_time                            303621 ns       303602 ns         2340       12.8655M/s              1024
BmCereal::DeserializeJsonFileToVector/10240/real_time                          3070668 ns      3070369 ns          244       12.7212M/s            10.24k
BmCereal::DeserializeJsonFileToVector/19456/real_time                          5616963 ns      5616886 ns           94       13.2133M/s           19.456k
BmCereal::DeserializeJsonFileToVector/28672/real_time                          9050409 ns      9049556 ns           81       12.0851M/s           28.672k
BmCereal::DeserializeJsonFileToVector/37888/real_time                         11363902 ns     11362466 ns           62       12.7185M/s           37.888k

...
...

```

## Compare Google Benchmarks using compare.py script tool

Please, visit provided info about how to use Google Benchmark compare.py script tool to compare results in an easy way.

* [Tool Preparation](./analysis/TOOL_PREPARATION.md)
* [Tool Execution](./analysis/TOOL_EXECUTION.md)

# License

&copy; Copyright 2019-2020, Klepsydra Technologies, all rights reserved. Licensed under the terms in [LICENSE.md](./LICENSE.md)

This software and documentation are Copyright 2019-2020, Klepsydra Technologies
Limited and its licensees. All rights reserved. See [license file](./LICENSE.md) for full copyright notice and license terms.

# Contact

<https://www.klepsydra.com>
support@klepsydra.com
