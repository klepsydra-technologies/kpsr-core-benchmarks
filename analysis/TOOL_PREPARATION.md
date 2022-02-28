<p align="right">
  <img width="25%" height="25%"src="./../images/klepsydra_logo.jpg">
</p>

# Benchmarks ***compare.py*** - Tool Preparation

## References

* Google Benchmark tools <https://github.com/google/benchmark/blob/main/docs/tools.md>

## Related docs

* [Main Readme](./../README.md)
* [Tool Execution](./TOOL_EXECUTION.md)

## System dependencies

* Tested in Ubuntu 20.04 LTS
* Tested with Python 3.8

## Installation of dependencies missing in tested steps

Previous reference document introduce the need to install the requirements.txt file prior to be able to use **compare.py** tool.

Following this requirement and with an Ubuntu 20.04 LTS with python3.8 installed in default locations, some issues were found and will be writed below to help as much as we can reader user.

Once requirements.txt installed, first command line call to **./comppare.py** tool output first issue as below:

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ ./compare.py 
/usr/bin/env: ‘python’: No such file or directory
```

This is due python3 is installed but python is expected to be found in system. Can be solved as user needs but we solve this issue creating a symbolic link to bypass python call to our python3 installation.

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ sudo ln -s /usr/bin/python3.8 /usr/bin/python
```

Once solved this step, below execution raises next issue.

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ ./compare.py
Traceback (most recent call last):
  File "./compare.py", line 13, in <module>
    from gbench import util, report
  File "/home/jose/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools/gbench/report.py", line 10, in <module>
    from scipy.stats import mannwhitneyu, gmean
ImportError: No module named scipy.stats
```

Has been solved installing **scipy** module as follows:

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ pip install scipy
/home/jose/.local/lib/python3.8/site-packages/pkg_resources/__init__.py:122: PkgResourcesDeprecationWarning: 0.1.36ubuntu1 is an invalid version and will not be supported in a future release
  warnings.warn(
/home/jose/.local/lib/python3.8/site-packages/pkg_resources/__init__.py:122: PkgResourcesDeprecationWarning: 0.23ubuntu1 is an invalid version and will not be supported in a future release
  warnings.warn(
Collecting scipy
  Downloading scipy-1.8.0-cp38-cp38-manylinux_2_17_x86_64.manylinux2014_x86_64.whl (41.6 MB)
     |████████████████████████████████| 41.6 MB 158 kB/s 
Collecting numpy<1.25.0,>=1.17.3
  Downloading numpy-1.22.2-cp38-cp38-manylinux_2_17_x86_64.manylinux2014_x86_64.whl (16.8 MB)
     |████████████████████████████████| 16.8 MB 657 kB/s 
Installing collected packages: numpy, scipy
Successfully installed numpy-1.22.2 scipy-1.8.0
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ ./compare.py
```

Next, new issue raised due to **pandas** module as follow:

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ ./compare.py
Traceback (most recent call last):
  File "./compare.py", line 13, in <module>
    from gbench import util, report
  File "/home/jose/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools/gbench/report.py", line 12, in <module>
    from pandas import Timedelta
ModuleNotFoundError: No module named 'pandas'
```

Has been solved installing module using below command:

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ pip install pandas
/home/jose/.local/lib/python3.8/site-packages/pkg_resources/__init__.py:122: PkgResourcesDeprecationWarning: 0.1.36ubuntu1 is an invalid version and will not be supported in a future release
  warnings.warn(
/home/jose/.local/lib/python3.8/site-packages/pkg_resources/__init__.py:122: PkgResourcesDeprecationWarning: 0.23ubuntu1 is an invalid version and will not be supported in a future release
  warnings.warn(
Collecting pandas
  Downloading pandas-1.4.1-cp38-cp38-manylinux_2_17_x86_64.manylinux2014_x86_64.whl (11.7 MB)
     |████████████████████████████████| 11.7 MB 766 kB/s 
Collecting python-dateutil>=2.8.1
  Downloading python_dateutil-2.8.2-py2.py3-none-any.whl (247 kB)
     |████████████████████████████████| 247 kB 897 kB/s 
Collecting pytz>=2020.1
  Downloading pytz-2021.3-py2.py3-none-any.whl (503 kB)
     |████████████████████████████████| 503 kB 582 kB/s 
Requirement already satisfied: numpy>=1.18.5; platform_machine != "aarch64" and platform_machine != "arm64" and python_version < "3.10" in /home/jose/.local/lib/python3.8/site-packages (from pandas) (1.22.2)
Requirement already satisfied: six>=1.5 in /usr/lib/python3/dist-packages (from python-dateutil>=2.8.1->pandas) (1.14.0)
Installing collected packages: python-dateutil, pytz, pandas
Successfully installed pandas-1.4.1 python-dateutil-2.8.2 pytz-2021.3
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$
```

Once installed and tested **compare.py** command again, we success obtaining below ouput.

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ ./compare.py
usage: compare.py [-h] [-a] [--no-color] [-d DUMP_TO_JSON] [--no-utest] [--alpha UTEST_ALPHA] {benchmarks,filters,benchmarksfiltered} ...

versatile benchmark output compare tool

positional arguments:
  {benchmarks,filters,benchmarksfiltered}
                        This tool has multiple modes of operation:
    benchmarks          The most simple use-case, compare all the output of these two benchmarks
    filters             Compare filter one with the filter two of benchmark
    benchmarksfiltered  Compare filter one of first benchmark with filter two of the second benchmark

optional arguments:
  -h, --help            show this help message and exit
  -a, --display_aggregates_only
                        If there are repetitions, by default, we display everything - the actual runs, and the aggregates computed.
                        Sometimes, it is desirable to only view the aggregates. E.g. when there are a lot of repetitions. Do note that
                        only the display is affected. Internally, all the actual runs are still used, e.g. for U test.
  --no-color            Do not use colors in the terminal output
  -d DUMP_TO_JSON, --dump_to_json DUMP_TO_JSON
                        Additionally, dump benchmark comparison output to this file in JSON format.

  --no-utest            The tool can do a two-tailed Mann-Whitney U test with the null hypothesis that it is equally likely that a
                        randomly selected value from one sample will be less than or greater than a randomly selected value from a second
                        sample. WARNING: requires **LARGE** (no less than 9) number of repetitions to be meaningful! The test is being
                        done by default, if at least 2 repetitions were done. This option can disable the U Test.
  --alpha UTEST_ALPHA   significance level alpha. if the calculated p-value is below this value, then the result is said to be
                        statistically significant and the null hypothesis is rejected. (default: 0.0500)
```

Thus, now seems all are ready to be able to execute **./compare.py** script tool. 

You can see execution steps and considerations done for this benchmarks in [Tool Execution](./TOOL_EXECUTION.md) c.

# License

&copy; Copyright 2019-2020, Klepsydra Technologies, all rights reserved. Licensed under the terms in [LICENSE.md](./LICENSE.md)

This software and documentation are Copyright 2019-2020, Klepsydra Technologies
Limited and its licensees. All rights reserved. See [license file](./LICENSE.md) for full copyright notice and license terms.

# Contact

<https://www.klepsydra.com>
support@klepsydra.com
