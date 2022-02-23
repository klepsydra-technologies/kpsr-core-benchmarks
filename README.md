<p align="right">
  <img width="25%" height="25%"src="./images/klepsydra_logo.jpg">
</p>

# Installation Instructions

## System dependencies

* Tested in Ubuntu 20.04 LTS
* Cmake 3.5.1 or above
* gcc for C++11 5.4.0 or above.
* Python 3.6 or above

### Dependencies installed by kpsr-core-benchmarks

* Google Benchmark (<https://github.com/google/benchmark.git>)
* Google Test (<https://github.com/klepsydra-technologies/googletest>)
* Cereal (<https://github.com/klepsydra-technologies/cereal>)
* Simdjson (<https://github.com/simdjson/simdjson.git>)

## Related docs

* [Tool Preparation](./analysis/TOOL_PREPARATION.md)
* [Tool Execution](./analysis/TOOL_EXECUTION.md)
* [Results output file bm.out](./analysis/bm.out)

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
git submodule update --init
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
* -DDEFINE_SAVE_FLOATS_TO_TEST_FILE by default is set to OFF. Set to =ON if you need to see how Cereal serialize json test file to disk. Ouput file should be set using absolute path using directive variable DTEST_FILE_PATH_AND_NAME. If not specified, default **out.txt** will be created in exection folder (/build if used to execute as example below **./bin/kpsr_benchmark_json_test**)
* -DTEST_FILE_PATH_AND_NAME used to specify json test ouput file to check format used by Cereal to serialize to json.
* -DJSON_FILE_PATH_AND_NAME used to specify json output files created sequentialy by Cereal TCs when generate random std::vector< float > which will be used to generate the json files used as initial conditions of each benchamrk test. For each size of the vector benchmarked, will be generated a json initial file using this prefix and adding at the end the size number of the vector benchmarked. 
Example

```bash
cmake .. -DCMAKE_PREFIX_PATH="/home/jose/klepsydra/klepsydra/development/community/install" -DCMAKE_INSTALL_PREFIX="/home/jose/klepsydra/klepsydra/development/community/install" -DDEFINE_SAVE_FLOATS_TO_TEST_FILE=ON 
```

## Google Benchmak support

Test case target project cxx03_test is not supported by kpsr-core thus, will be not compiled.

To use UserCounters column-tabbed please, use the command line argument **--benchmark_counters_tabular=true** after the test executable.

```bash
user@ubuntu:~/kpsr-core-benchmarks/build$ ./bin/kpsr_benchmark_core_test --benchmark_counters_tabular=true
```

## Cereal & SimdJSON support

Test cases has been designed to check how benchmark differs when serializing same json input stream of std::vector<float> using both, Cereal and SimdJSON serializers. 

You can execute the TCs using below execute command. Remeber you can use directive variables **DDEFINE_SAVE_FLOATS_TO_TEST_FILE=ON[OFF]** and **DTEST_FILE_PATH_AND_NAME="<path_and_filename>"** when building cmake.  

```bash
user@ubuntu:~/kpsr-core-benchmarks/build$ ./bin/kpsr_benchmark_json_test --benchmark_counters_tabular=true
```

### Note about cmake directives related to JSON files

These benchmark TCs has been designed to be executed sequentialy. First, Cereal TCs are executed and creates serialized json files to disk, as initial conditions. Once initial conditions about benchmarking are set, Retrive_xxx std::vector< float > benchmark cases uses these disk json files in SimdJSON to DESERIALIZE these file expressed vector in a memory std::vector< float > vector variable with the same size.

In the first step of creating these json files as initial conditions, plays a key role the benchmark parameter about size of vector to be benchmrked. Test uses a **->DenseRange(1024, 102400, 1<<10)** as vector size. This means one test json file is created to disk for each size, using as name, the concatenation of filepath provided by JSON_FILE_PATH_AND_NAME and vector size at the end of the string.

Example: 

If we cmake as below:

```bash
cmake .. 
-DCMAKE_PREFIX_PATH="/home/jose/klepsydra/klepsydra/development/community/install"
-DCMAKE_INSTALL_PREFIX="/home/jose/klepsydra/klepsydra/development/community/install" 
-DDEFINE_SAVE_FLOATS_TO_TEST_FILE=ON 
-DTEST_FILE_PATH_AND_NAME="/home/jose/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/build/my_out_cereal.txt"
-DJSON_FILE_PATH_AND_NAME="/home/jose/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/build/my_cereal_json_str.txt"
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

The **my_out_cereal.txt** file is not needed by TCs. Its only used for debugging purposes to show how Cereal ouputs json vector of floats.

```bash
user@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/build$ ./bin/kpsr_benchmark_json_test --benchmark_counters_tabular=true
2022-02-26T00:13:44+01:00
Running ./bin/kpsr_benchmark_json_test
Run on (16 X 3800 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x16)
  L1 Instruction 32 KiB (x16)
  L2 Unified 512 KiB (x16)
  L3 Unified 16384 KiB (x1)
Load Average: 0.99, 0.86, 0.69
-----------------------------------------------------------------------------------------------
Benchmark                                    Time       CPU        Iterations retrievedVectorSz
-----------------------------------------------------------------------------------------------
Cereal__Retrive_float_vector/1024/real_time   219700 ns  219522 ns 3159          1024
Cereal__Retrive_float_vector/2048/real_time   443492 ns  443138 ns 1588        2.048k
Cereal__Retrive_float_vector/3072/real_time   659648 ns  657620 ns 1058        3.072k
Cereal__Retrive_float_vector/4096/real_time   880931 ns  879935 ns  794        4.096k
Cereal__Retrive_float_vector/5120/real_time  1102488 ns 1101694 ns  638         5.12k
Cereal__Retrive_float_vector/6144/real_time  1623337 ns 1622293 ns  433        6.144k
Cereal__Retrive_float_vector/7168/real_time  1567311 ns 1567268 ns  454        7.168k
Cereal__Retrive_float_vector/8192/real_time  1810505 ns 1808814 ns  388        8.192k
Cereal__Retrive_float_vector/9216/real_time  2023501 ns 2020727 ns  350        9.216k
Cereal__Retrive_float_vector/10240/real_time 2215584 ns 2215528 ns  319        10.24k
Cereal__Retrive_float_vector/11264/real_time 2431164 ns 2431098 ns  288       11.264k
Cereal__Retrive_float_vector/12288/real_time 2662929 ns 2662924 ns  266       12.288k
Cereal__Retrive_float_vector/13312/real_time 2908597 ns 2905893 ns  245       13.312k
Cereal__Retrive_float_vector/14336/real_time 3161732 ns 3154675 ns  219       14.336k
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
