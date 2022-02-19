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
make test
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

Example

```bash
cmake .. -DCMAKE_PREFIX_PATH="/home/jose/klepsydra/klepsydra/development/community/install" -DCMAKE_INSTALL_PREFIX="/home/jose/klepsydra/klepsydra/development/community/install"
```

## Google Benchmak support

Test case target project cxx03_test is not supported by kpsr-core thus, will be not compiled.

To use UserCounters column-tabbed please, use the command line argument **--benchmark_counters_tabular=true** after the test executable.

```bash
user@ubuntu:~/kpsr-core-benchmarks/build$ ./bin/kpsr_benchmark_core_test --benchmark_counters_tabular=true
```

# License

&copy; Copyright 2019-2020, Klepsydra Technologies, all rights reserved. Licensed under the terms in [LICENSE.md](./LICENSE.md)

This software and documentation are Copyright 2019-2020, Klepsydra Technologies
Limited and its licensees. All rights reserved. See [license file](./LICENSE.md) for full copyright notice and license terms.

# Contact

<https://www.klepsydra.com>
support@klepsydra.com
