<p align="right">
  <img width="25%" height="25%"src="./../images/klepsydra_logo.jpg">
</p>

# Benchmarks ***compare.py*** - Tool Execution

## References

* Google Benchmark tools <https://github.com/google/benchmark/blob/main/docs/tools.md>

## Related docs

* [Main Readme](./../README.md)
* [Tool Preparation](./TOOL_PREPARATION.md)
* [Results output file bm.out](./bm.out)

## System dependencies

* Tested in Ubuntu 20.04 LTS
* Tested with Python 3.8

## Execution

As in Google Benchmark reference tool documentation explains, **compare.py** tool can be used in various modes. Due to our benchmark design to this use case, all benchmarked code must be executed sequentially. 

This means first mode of operation is now valid for this use case because we can not ouput a file for family benchmarks about **Cereal__Retrive_float_vector_from_disk_jsonfile** and a new and independent one for family benchmarks **Simdjon__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile**, as instance.

As we need to create whole ouput file in same execution due to dependencies created in firsts family benchmmarks, we will use mode 2 of operation as follows.

### Step 1 - Create ouput results file

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/build$ ./bin/kpsr_benchmark_json_test --benchmark_counters_tabular=true --benchmark_out=bm.out
```

Once this commad is executed, **bm.out** specified name file will be created in root execution folder.

### Step 2 - Execute ***./compare.py*** script tool

In below example command, we have located into benchmarks/tool folder to have **compare.py** tool in root execution folder.

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ 
./compare.py filters 
../../../test/bm.out 
Cereal__Retrive_float_vector_from_disk_jsonfile 
Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile

Comparing Cereal__Retrive_float_vector_from_disk_jsonfile to Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile (from ../../../test/bm.out)
Benchmark                                                                                                                                                      Time             CPU      Time Old      Time New       CPU Old       CPU New
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/1024/real_time                  -0.4589         -0.4589       1624833        879265       1624841        879215
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/2048/real_time                  -0.4602         -0.4601       3233711       1745671       3232996       1745365
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/3072/real_time                  -0.4598         -0.4598       4823870       2605667       4822853       2605347
...
...

```

NOTE: Required to have a fully working **./compare.py** tool script as specified in help steps provided in [Tool Preparation](./TOOL_PREPARATION.md).

### Step 3 - Result analysis

Is responsability of the final user to execute filter comparisons between families and results with some sense. In this case, has been choiced families which both makes file disk access and benchmark families are both expressed for the exactly same DenseRanges obtaining same vector size for each row to be compared.

This results seems tell us use of SimdJSON to deserialize JSON files has best performance than Cereal deserialze.

**NOTE:** To be remembered that values in Time and CPU columns are calculated as **(new - old) / |old|**.

## Results obtained

### compare between **Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile**

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ 
./compare.py filters 
../../../test/bm.out 
Cereal__Retrive_float_vector_from_disk_jsonfile 
Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile
Comparing Cereal__Retrive_float_vector_from_disk_jsonfile to Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile (from ../../../test/bm.out)
Benchmark                                                                                                                                                      Time             CPU      Time Old      Time New       CPU Old       CPU New
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/1024/real_time                  -0.4589         -0.4589       1624833        879265       1624841        879215
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/2048/real_time                  -0.4602         -0.4601       3233711       1745671       3232996       1745365
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/3072/real_time                  -0.4598         -0.4598       4823870       2605667       4822853       2605347
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/4096/real_time                  -0.4620         -0.4619       6426162       3457206       6424787       3456998
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/5120/real_time                  -0.4724         -0.4722       8277991       4367766       8272298       4366527
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/6144/real_time                  -0.4620         -0.4621       9658833       5196433       9657817       5195163
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/7168/real_time                  -0.4551         -0.4550      11250427       6130559      11247418       6129474
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/8192/real_time                  -0.4572         -0.4572      12915189       7010815      12912737       7008640
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/9216/real_time                  -0.4565         -0.4564      14464973       7861359      14458838       7859455
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/10240/real_time                 -0.4637         -0.4636      16164587       8668496      16157472       8667578
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/11264/real_time                 -0.4651         -0.4651      17812915       9528114      17811982       9526911
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/12288/real_time                 -0.4619         -0.4620      19557451      10524754      19556156      10522052
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/13312/real_time                 -0.4658         -0.4659      21268735      11362596      21266312      11358286
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/14336/real_time                 -0.4643         -0.4643      22869653      12250606      22864527      12247962
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/15360/real_time                 -0.4913         -0.4914      25702337      13074526      25698677      13070524
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/16384/real_time                 -0.4655         -0.4654      25832542      13808568      25830600      13807839
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/17408/real_time                 -0.4622         -0.4622      27378214      14722753      27372230      14721632
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/18432/real_time                 -0.4631         -0.4631      29239888      15697844      29230203      15694845
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/19456/real_time                 -0.4797         -0.4798      31963176      16629938      31960165      16625919
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/20480/real_time                 -0.4663         -0.4663      32826298      17519933      32823041      17516330
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/21504/real_time                 -0.4601         -0.4601      33937536      18323709      33935788      18321936
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/22528/real_time                 -0.4634         -0.4634      35828111      19225784      35822070      19222005
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/23552/real_time                 -0.4632         -0.4631      37448573      20103285      37428213      20096677
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/24576/real_time                 -0.4635         -0.4635      38951016      20897099      38947915      20894216
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/25600/real_time                 -0.4756         -0.4755      41276794      21645931      41270754      21644614
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/26624/real_time                 -0.4768         -0.4767      42991684      22491161      42974263      22487935
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/27648/real_time                 -0.4497         -0.4497      43568214      23975585      43560960      23971302
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/28672/real_time                 -0.4587         -0.4586      45320989      24533680      45307959      24529912
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/29696/real_time                 -0.4617         -0.4618      47322133      25471561      47316167      25467277
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/30720/real_time                 -0.4817         -0.4816      50883503      26374632      50871441      26370419
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/31744/real_time                 -0.4749         -0.4747      51945111      27275133      51912368      27268534
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/32768/real_time                 -0.4733         -0.4734      53361863      28104072      53360881      28098327
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/33792/real_time                 -0.4907         -0.4906      55541687      28284639      55523292      28281433
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/34816/real_time                 -0.4841         -0.4841      56430796      29111820      56423403      29109785
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/35840/real_time                 -0.4822         -0.4822      58341224      30209807      58335490      30204174
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/36864/real_time                 -0.4820         -0.4821      60104547      31131854      60093644      31124427
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/37888/real_time                 -0.4707         -0.4706      60223574      31877933      60213245      31874770
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/38912/real_time                 -0.4708         -0.4707      61915719      32764656      61895468      32759914
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/39936/real_time                 -0.4975         -0.4974      67035762      33684848      67012918      33678457
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/40960/real_time                 -0.4644         -0.4645      65322192      34989281      65321340      34981497
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/41984/real_time                 -0.4651         -0.4651      66754188      35706615      66742686      35701918
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/43008/real_time                 -0.4573         -0.4573      67656023      36718731      67643530      36707446
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/44032/real_time                 -0.4717         -0.4717      72164916      38123523      72139852      38114503
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/45056/real_time                 -0.4619         -0.4618      71729417      38598690      71691112      38586158
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/46080/real_time                 -0.4619         -0.4619      73696856      39658323      73682728      39646565
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/47104/real_time                 -0.4663         -0.4663      74693463      39864155      74676645      39855907
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/48128/real_time                 -0.4699         -0.4697      76398757      40497637      76353379      40492567
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/49152/real_time                 -0.4626         -0.4626      77997484      41915855      77984471      41907865
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/50176/real_time                 -0.4642         -0.4642      79792571      42751935      79770646      42737260
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/51200/real_time                 -0.4600         -0.4598      81074480      43776419      81027547      43767627
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/52224/real_time                 -0.4942         -0.4942      88228507      44627425      88202164      44612115
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/53248/real_time                 -0.4723         -0.4722      85158944      44936683      85122598      44930322
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/54272/real_time                 -0.4758         -0.4758      88432776      46356819      88417507      46344948
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/55296/real_time                 -0.4603         -0.4603      87589005      47273404      87560460      47258330
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/56320/real_time                 -0.4606         -0.4607      89264645      48147210      89258712      48136429
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/57344/real_time                 -0.4652         -0.4652      91337893      48850887      91310398      48828664
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/58368/real_time                 -0.4571         -0.4573      92330974      50125108      92318245      50097820
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/59392/real_time                 -0.4263         -0.4263      94156084      54016366      94134576      54007023
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/60416/real_time                 -0.4643         -0.4643      95890040      51369107      95880434      51362440
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/61440/real_time                 -0.4545         -0.4544      97529336      53199171      97475943      53184363
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/62464/real_time                 -0.4535         -0.4535      98503222      53832048      98487323      53826987
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/63488/real_time                 -0.4549         -0.4549     100386936      54725927     100350301      54702638
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/64512/real_time                 -0.4548         -0.4548     101634316      55412505     101606318      55395510
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/65536/real_time                 -0.4531         -0.4532     103477613      56592325     103469871      56580998
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/66560/real_time                 -0.4557         -0.4556     105473165      57413717     105439274      57406278
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/67584/real_time                 -0.4545         -0.4544     107141408      58450412     107106389      58437970
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/68608/real_time                 -0.4573         -0.4575     108612197      58947815     108612353      58923345
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/69632/real_time                 -0.4517         -0.4518     109206817      59882627     109200376      59865518
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/70656/real_time                 -0.4450         -0.4451     110428654      61285592     110427163      61277233
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/71680/real_time                 -0.4522         -0.4522     113038632      61919379     112992538      61902687
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/72704/real_time                 -0.4521         -0.4522     114101712      62511209     114093475      62495476
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/73728/real_time                 -0.4546         -0.4546     117444337      64056946     117407424      64039756
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/74752/real_time                 -0.4534         -0.4535     118254551      64632096     118228702      64616642
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/75776/real_time                 -0.4562         -0.4562     120522290      65535862     120498557      65531141
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/76800/real_time                 -0.4577         -0.4578     121110802      65676764     121099833      65666092
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/77824/real_time                 -0.4496         -0.4496     122685900      67525171     122656236      67511067
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/78848/real_time                 -0.4516         -0.4514     124542342      68301600     124489595      68294277
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/79872/real_time                 -0.4594         -0.4594     125999586      68112837     125942958      68084599
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/80896/real_time                 -0.4658         -0.4658     127755926      68246838     127715685      68230594
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/81920/real_time                 -0.4543         -0.4542     127750121      69712928     127702069      69704439
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/82944/real_time                 -0.4596         -0.4596     130747065      70658702     130721066      70636901
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/83968/real_time                 -0.4761         -0.4764     137639481      72102496     137617260      72056272
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/84992/real_time                 -0.4632         -0.4629     134720068      72320570     134659779      72320845
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/86016/real_time                 -0.4634         -0.4633     136188037      73076700     136136233      73062519
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/87040/real_time                 -0.4586         -0.4585     137773803      74595266     137743334      74584774
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/88064/real_time                 -0.4788         -0.4789     143904623      75005487     143895568      74986202
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/89088/real_time                 -0.4597         -0.4596     140649719      75994682     140606818      75989701
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/90112/real_time                 -0.4728         -0.4729     143929478      75883438     143929612      75862830
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/91136/real_time                 -0.4776         -0.4778     149033492      77849313     149026233      77827211
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/92160/real_time                 -0.4604         -0.4603     146303033      78940608     146232434      78924282
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/93184/real_time                 -0.4636         -0.4635     147887594      79331139     147850409      79316250
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/94208/real_time                 -0.4644         -0.4645     149200726      79904928     149179304      79890171
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/95232/real_time                 -0.4724         -0.4724     152684484      80557889     152651427      80536366
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/96256/real_time                 -0.4262         -0.4262     151652138      87022110     151621743      86998285
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/97280/real_time                 -0.4613         -0.4613     154391888      83168788     154383263      83161234
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/98304/real_time                 -0.4581         -0.4581     154962480      83966989     154923203      83954102
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/99328/real_time                 -0.4652         -0.4651     157610477      84283901     157552186      84273802
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/100352/real_time                -0.4550         -0.4550     157142475      85644968     157099698      85615537
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/101376/real_time                -0.4560         -0.4559     158811073      86395665     158761681      86378485
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__count_elements_from_disk_jsonfile]/102400/real_time                -0.4853         -0.4853     169854761      87417532     169818274      87411048
OVERALL_GEOMEAN                                                                                                                                             -0.4639         -0.4639             0             0             0             0
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$
```

### compare between **Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile**

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ 
./compare.py filters 
../../../test/bm.out 
Cereal__Retrive_float_vector_from_disk_jsonfile
Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile
Comparing Cereal__Retrive_float_vector_from_disk_jsonfile to Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile (from ../../../test/bm.out)
Benchmark                                                                                                                                                              Time             CPU      Time Old      Time New       CPU Old       CPU New
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/1024/real_time                  -0.5489         -0.5490       1624833        732892       1624841        732777
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/2048/real_time                  -0.5497         -0.5496       3233711       1456231       3232996       1456087
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/3072/real_time                  -0.5439         -0.5441       4823870       2199942       4822853       2198959
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/4096/real_time                  -0.5321         -0.5321       6426162       3007047       6424787       3006202
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/5120/real_time                  -0.5546         -0.5544       8277991       3686849       8272298       3686055
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/6144/real_time                  -0.5459         -0.5459       9658833       4385692       9657817       4385163
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/7168/real_time                  -0.5349         -0.5350      11250427       5232995      11247418       5230353
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/8192/real_time                  -0.5336         -0.5337      12915189       6023886      12912737       6021228
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/9216/real_time                  -0.5436         -0.5435      14464973       6601927      14458838       6601010
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/10240/real_time                 -0.5481         -0.5480      16164587       7304453      16157472       7303655
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/11264/real_time                 -0.5507         -0.5508      17812915       8004051      17811982       8001830
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/12288/real_time                 -0.5499         -0.5501      19557451       8803306      19556156       8798918
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/13312/real_time                 -0.5511         -0.5512      21268735       9548475      21266312       9545329
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/14336/real_time                 -0.5504         -0.5504      22869653      10282761      22864527      10280229
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/15360/real_time                 -0.5718         -0.5719      25702337      11004754      25698677      11002741
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/16384/real_time                 -0.5507         -0.5507      25832542      11606616      25830600      11604728
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/17408/real_time                 -0.5450         -0.5451      27378214      12456447      27372230      12451687
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/18432/real_time                 -0.5605         -0.5604      29239888      12850403      29230203      12848590
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/19456/real_time                 -0.5757         -0.5758      31963176      13560998      31960165      13557981
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/20480/real_time                 -0.5637         -0.5638      32826298      14320693      32823041      14317081
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/21504/real_time                 -0.5557         -0.5558      33937536      15079410      33935788      15075204
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/22528/real_time                 -0.5638         -0.5639      35828111      15626702      35822070      15620883
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/23552/real_time                 -0.5643         -0.5641      37448573      16318008      37428213      16316098
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/24576/real_time                 -0.5605         -0.5606      38951016      17117964      38947915      17113970
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/25600/real_time                 -0.5671         -0.5672      41276794      17869886      41270754      17862344
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/26624/real_time                 -0.5694         -0.5693      42991684      18514131      42974263      18507883
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/27648/real_time                 -0.5577         -0.5578      43568214      19269844      43560960      19260627
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/28672/real_time                 -0.5603         -0.5603      45320989      19927125      45307959      19922763
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/29696/real_time                 -0.5472         -0.5472      47322133      21427770      47316167      21425219
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/30720/real_time                 -0.5732         -0.5732      50883503      21714710      50871441      21711848
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/31744/real_time                 -0.5689         -0.5687      51945111      22392700      51912368      22390671
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/32768/real_time                 -0.5713         -0.5713      53361863      22873671      53360881      22873753
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/33792/real_time                 -0.5719         -0.5718      55541687      23774638      55523292      23773106
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/34816/real_time                 -0.5627         -0.5626      56430796      24678014      56423403      24678099
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/35840/real_time                 -0.5652         -0.5653      58341224      25367370      58335490      25356697
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/36864/real_time                 -0.5657         -0.5656      60104547      26106215      60093644      26101719
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/37888/real_time                 -0.5536         -0.5536      60223574      26882376      60213245      26878367
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/38912/real_time                 -0.5541         -0.5540      61915719      27607771      61895468      27603413
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/39936/real_time                 -0.5838         -0.5838      67035762      27903374      67012918      27888734
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/40960/real_time                 -0.5570         -0.5570      65322192      28940332      65321340      28935360
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/41984/real_time                 -0.5618         -0.5618      66754188      29253309      66742686      29247996
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/43008/real_time                 -0.5490         -0.5491      67656023      30509651      67643530      30502276
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/44032/real_time                 -0.5683         -0.5683      72164916      31152094      72139852      31141870
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/45056/real_time                 -0.5552         -0.5551      71729417      31907271      71691112      31898125
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/46080/real_time                 -0.5586         -0.5587      73696856      32526482      73682728      32518981
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/47104/real_time                 -0.5551         -0.5551      74693463      33233395      74676645      33224007
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/48128/real_time                 -0.5396         -0.5394      76398757      35175782      76353379      35172079
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/49152/real_time                 -0.5625         -0.5625      77997484      34124856      77984471      34119465
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/50176/real_time                 -0.5474         -0.5474      79792571      36114865      79770646      36104066
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/51200/real_time                 -0.5574         -0.5573      81074480      35885041      81027547      35873452
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/52224/real_time                 -0.5846         -0.5846      88228507      36646424      88202164      36638743
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/53248/real_time                 -0.5586         -0.5586      85158944      37585784      85122598      37577328
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/54272/real_time                 -0.5665         -0.5665      88432776      38333906      88417507      38327810
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/55296/real_time                 -0.5586         -0.5585      87589005      38664467      87560460      38658944
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/56320/real_time                 -0.5583         -0.5584      89264645      39428441      89258712      39418043
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/57344/real_time                 -0.5575         -0.5575      91337893      40419714      91310398      40409411
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/58368/real_time                 -0.5561         -0.5561      92330974      40987654      92318245      40975940
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/59392/real_time                 -0.5587         -0.5587      94156084      41552952      94134576      41545374
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/60416/real_time                 -0.5598         -0.5598      95890040      42208101      95880434      42205779
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/61440/real_time                 -0.5574         -0.5573      97529336      43164112      97475943      43153396
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/62464/real_time                 -0.5545         -0.5545      98503222      43883943      98487323      43872386
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/63488/real_time                 -0.5551         -0.5552     100386936      44658541     100350301      44638181
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/64512/real_time                 -0.5598         -0.5597     101634316      44742638     101606318      44736901
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/65536/real_time                 -0.5614         -0.5615     103477613      45390408     103469871      45371874
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/66560/real_time                 -0.5596         -0.5595     105473165      46454464     105439274      46442505
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/67584/real_time                 -0.5581         -0.5582     107141408      47342187     107106389      47316106
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/68608/real_time                 -0.5531         -0.5532     108612197      48540198     108612353      48523057
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/69632/real_time                 -0.5340         -0.5341     109206817      50894805     109200376      50873955
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/70656/real_time                 -0.5457         -0.5458     110428654      50172692     110427163      50158974
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/71680/real_time                 -0.5433         -0.5433     113038632      51619440     112992538      51604721
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/72704/real_time                 -0.5392         -0.5392     114101712      52581549     114093475      52571117
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/73728/real_time                 -0.5485         -0.5486     117444337      53021393     117407424      53001010
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/74752/real_time                 -0.5468         -0.5469     118254551      53591663     118228702      53574603
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/75776/real_time                 -0.5518         -0.5520     120522290      54013698     120498557      53985884
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/76800/real_time                 -0.5496         -0.5497     121110802      54553659     121099833      54528814
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/77824/real_time                 -0.5514         -0.5514     122685900      55040715     122656236      55026235
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/78848/real_time                 -0.5362         -0.5361     124542342      57762275     124489595      57748851
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/79872/real_time                 -0.5553         -0.5552     125999586      56027977     125942958      56022826
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/80896/real_time                 -0.5528         -0.5527     127755926      57128327     127715685      57123529
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/81920/real_time                 -0.5456         -0.5454     127750121      58054736     127702069      58054920
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/82944/real_time                 -0.5559         -0.5559     130747065      58070202     130721066      58056192
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/83968/real_time                 -0.5689         -0.5689     137639481      59330158     137617260      59320881
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/84992/real_time                 -0.5528         -0.5526     134720068      60240083     134659779      60240243
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/86016/real_time                 -0.5446         -0.5447     136188037      62014616     136136233      61987755
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/87040/real_time                 -0.5547         -0.5547     137773803      61349473     137743334      61335854
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/88064/real_time                 -0.5679         -0.5680     143904623      62176623     143895568      62159466
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/89088/real_time                 -0.5515         -0.5514     140649719      63085078     140606818      63072260
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/90112/real_time                 -0.5543         -0.5545     143929478      64143590     143929612      64114994
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/91136/real_time                 -0.5721         -0.5721     149033492      63770235     149026233      63761446
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/92160/real_time                 -0.5575         -0.5575     146303033      64746006     146232434      64710234
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/93184/real_time                 -0.5531         -0.5531     147887594      66098252     147850409      66077146
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/94208/real_time                 -0.5486         -0.5486     149200726      67346774     149179304      67335208
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/95232/real_time                 -0.5516         -0.5518     152684484      68457913     152651427      68419781
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/96256/real_time                 -0.5544         -0.5545     151652138      67570478     151621743      67547232
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/97280/real_time                 -0.5524         -0.5526     154391888      69104575     154383263      69072193
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/98304/real_time                 -0.5468         -0.5470     154962480      70222256     154923203      70179360
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/99328/real_time                 -0.5539         -0.5539     157610477      70308246     157552186      70283626
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/100352/real_time                -0.5504         -0.5505     157142475      70651083     157099698      70615025
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/101376/real_time                -0.5466         -0.5466     158811073      72006089     158761681      71983818
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array__without_count_elements_from_disk_jsonfile]/102400/real_time                -0.5724         -0.5725     169854761      72631166     169818274      72599480
OVERALL_GEOMEAN                                                                                                                                                     -0.5557         -0.5557             0             0             0             0
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$
```


### compare between **Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile**

```bash
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$ 
./compare.py filters 
../../../test/bm.out 
Cereal__Retrive_float_vector_from_disk_jsonfile 
Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile
Comparing Cereal__Retrive_float_vector_from_disk_jsonfile to Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile (from ../../../test/bm.out)
Benchmark                                                                                                                                                                     Time             CPU      Time Old      Time New       CPU Old       CPU New
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/1024/real_time                  -0.5538         -0.5539       1624833        724970       1624841        724907
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/2048/real_time                  -0.5532         -0.5532       3233711       1444702       3232996       1444437
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/3072/real_time                  -0.5535         -0.5536       4823870       2153717       4822853       2152811
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/4096/real_time                  -0.5508         -0.5509       6426162       2886877       6424787       2885443
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/5120/real_time                  -0.5680         -0.5677       8277991       3576435       8272298       3575704
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/6144/real_time                  -0.5548         -0.5549       9658833       4299857       9657817       4298433
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/7168/real_time                  -0.5528         -0.5530      11250427       5030960      11247418       5028134
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/8192/real_time                  -0.5521         -0.5521      12915189       5785261      12912737       5783948
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/9216/real_time                  -0.5518         -0.5518      14464973       6483271      14458838       6480040
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/10240/real_time                 -0.5570         -0.5568      16164587       7161060      16157472       7160362
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/11264/real_time                 -0.5570         -0.5570      17812915       7891389      17811982       7889849
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/12288/real_time                 -0.5578         -0.5579      19557451       8647697      19556156       8645080
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/13312/real_time                 -0.5579         -0.5580      21268735       9403032      21266312       9399328
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/14336/real_time                 -0.5565         -0.5566      22869653      10141886      22864527      10137051
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/15360/real_time                 -0.5808         -0.5808      25702337      10773542      25698677      10771993
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/16384/real_time                 -0.5524         -0.5525      25832542      11562759      25830600      11558472
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/17408/real_time                 -0.5484         -0.5485      27378214      12364946      27372230      12359285
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/18432/real_time                 -0.5519         -0.5518      29239888      13103199      29230203      13101098
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/19456/real_time                 -0.5647         -0.5649      31963176      13913669      31960165      13907107
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/20480/real_time                 -0.5442         -0.5443      32826298      14961112      32823041      14955831
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/21504/real_time                 -0.5430         -0.5432      33937536      15508944      33935788      15501045
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/22528/real_time                 -0.5561         -0.5562      35828111      15903235      35822070      15898627
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/23552/real_time                 -0.5607         -0.5606      37448573      16451902      37428213      16446142
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/24576/real_time                 -0.5555         -0.5556      38951016      17314918      38947915      17309350
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/25600/real_time                 -0.5631         -0.5631      41276794      18032135      41270754      18030142
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/26624/real_time                 -0.5641         -0.5640      42991684      18742056      42974263      18736076
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/27648/real_time                 -0.5544         -0.5545      43568214      19413110      43560960      19407150
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/28672/real_time                 -0.5529         -0.5530      45320989      20263688      45307959      20253218
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/29696/real_time                 -0.5583         -0.5583      47322133      20903844      47316167      20899514
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/30720/real_time                 -0.5757         -0.5757      50883503      21590919      50871441      21583633
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/31744/real_time                 -0.5712         -0.5711      51945111      22272105      51912368      22263795
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/32768/real_time                 -0.5673         -0.5675      53361863      23087525      53360881      23079231
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/33792/real_time                 -0.5699         -0.5698      55541687      23890202      55523292      23883936
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/34816/real_time                 -0.5666         -0.5666      56430796      24456844      56423403      24451186
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/35840/real_time                 -0.5676         -0.5678      58341224      25225896      58335490      25213765
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/36864/real_time                 -0.5691         -0.5692      60104547      25896197      60093644      25887486
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/37888/real_time                 -0.5578         -0.5578      60223574      26629005      60213245      26625457
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/38912/real_time                 -0.5566         -0.5567      61915719      27454320      61895468      27440933
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/39936/real_time                 -0.5813         -0.5813      67035762      28065298      67012918      28058240
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/40960/real_time                 -0.5589         -0.5591      65322192      28812852      65321340      28802099
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/41984/real_time                 -0.5548         -0.5549      66754188      29717395      66742686      29706456
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/43008/real_time                 -0.5528         -0.5528      67656023      30259004      67643530      30252998
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/44032/real_time                 -0.5687         -0.5688      72164916      31123482      72139852      31105779
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/45056/real_time                 -0.5319         -0.5317      71729417      33579225      71691112      33570619
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/46080/real_time                 -0.5606         -0.5606      73696856      32381731      73682728      32378762
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/47104/real_time                 -0.5560         -0.5559      74693463      33160508      74676645      33160600
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/48128/real_time                 -0.5557         -0.5555      76398757      33943352      76353379      33940623
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/49152/real_time                 -0.5535         -0.5534      77997484      34828857      77984471      34826374
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/50176/real_time                 -0.5546         -0.5546      79792571      35541429      79770646      35533508
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/51200/real_time                 -0.5576         -0.5574      81074480      35868181      81027547      35859175
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/52224/real_time                 -0.5849         -0.5849      88228507      36622102      88202164      36610523
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/53248/real_time                 -0.5609         -0.5607      85158944      37396600      85122598      37394476
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/54272/real_time                 -0.5659         -0.5660      88432776      38388087      88417507      38376718
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/55296/real_time                 -0.5567         -0.5568      87589005      38824829      87560460      38808150
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/56320/real_time                 -0.5574         -0.5575      89264645      39511857      89258712      39494281
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/57344/real_time                 -0.5564         -0.5563      91337893      40521727      91310398      40513114
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/58368/real_time                 -0.5559         -0.5561      92330974      41004397      92318245      40983347
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/59392/real_time                 -0.5579         -0.5579      94156084      41629526      94134576      41618177
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/60416/real_time                 -0.5626         -0.5626      95890040      41938741      95880434      41935478
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/61440/real_time                 -0.5638         -0.5637      97529336      42537928      97475943      42528101
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/62464/real_time                 -0.5592         -0.5593      98503222      43416114      98487323      43405366
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/63488/real_time                 -0.5567         -0.5567     100386936      44504101     100350301      44480730
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/64512/real_time                 -0.5595         -0.5595     101634316      44768378     101606318      44761179
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/65536/real_time                 -0.5470         -0.5472     103477613      46872893     103469871      46852232
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/66560/real_time                 -0.5544         -0.5545     105473165      46995097     105439274      46969861
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/67584/real_time                 -0.5545         -0.5545     107141408      47734982     107106389      47720999
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/68608/real_time                 -0.5564         -0.5566     108612197      48182298     108612353      48159340
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/69632/real_time                 -0.5542         -0.5543     109206817      48683638     109200376      48672193
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/70656/real_time                 -0.5496         -0.5496     110428654      49740396     110427163      49731386
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/71680/real_time                 -0.5558         -0.5556     113038632      50216162     112992538      50212335
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/72704/real_time                 -0.5472         -0.5474     114101712      51660639     114093475      51636427
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/73728/real_time                 -0.5577         -0.5578     117444337      51942472     117407424      51915947
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/74752/real_time                 -0.5576         -0.5577     118254551      52318398     118228702      52297556
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/75776/real_time                 -0.5559         -0.5560     120522290      53522902     120498557      53506646
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/76800/real_time                 -0.5529         -0.5530     121110802      54151235     121099833      54133498
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/77824/real_time                 -0.5548         -0.5548     122685900      54624154     122656236      54604146
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/78848/real_time                 -0.5574         -0.5574     124542342      55116730     124489595      55100237
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/79872/real_time                 -0.5556         -0.5556     125999586      55988136     125942958      55967519
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/80896/real_time                 -0.5567         -0.5568     127755926      56634257     127715685      56607056
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/81920/real_time                 -0.5477         -0.5477     127750121      57775891     127702069      57757118
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/82944/real_time                 -0.5552         -0.5552     130747065      58162340     130721066      58149200
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/83968/real_time                 -0.5718         -0.5719     137639481      58936562     137617260      58917329
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/84992/real_time                 -0.5515         -0.5514     134720068      60422259     134659779      60405364
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/86016/real_time                 -0.5471         -0.5471     136188037      61677889     136136233      61649556
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/87040/real_time                 -0.5512         -0.5512     137773803      61829873     137743334      61821798
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/88064/real_time                 -0.5660         -0.5660     143904623      62451570     143895568      62443825
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/89088/real_time                 -0.5437         -0.5438     140649719      64183110     140606818      64150406
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/90112/real_time                 -0.5345         -0.5346     143929478      66998441     143929612      66979711
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/91136/real_time                 -0.5579         -0.5581     149033492      65889294     149026233      65849754
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/92160/real_time                 -0.5629         -0.5628     146303033      63955494     146232434      63938031
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/93184/real_time                 -0.5614         -0.5614     147887594      64860392     147850409      64854414
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/94208/real_time                 -0.5624         -0.5625     149200726      65286441     149179304      65261677
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/95232/real_time                 -0.5657         -0.5658     152684484      66318354     152651427      66281919
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/96256/real_time                 -0.5560         -0.5561     151652138      67333240     151621743      67307283
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/97280/real_time                 -0.5583         -0.5584     154391888      68201912     154383263      68180320
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/98304/real_time                 -0.5528         -0.5528     154962480      69294564     154923203      69278153
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/99328/real_time                 -0.5547         -0.5547     157610477      70187962     157552186      70162626
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/100352/real_time                -0.5528         -0.5528     157142475      70273101     157099698      70256476
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/101376/real_time                -0.5511         -0.5511     158811073      71292486     158761681      71273302
[Cereal__Retrive_float_vector_from_disk_jsonfile vs. Simdjson__Retrive_using__get_array_double__without_count_elements_from_disk_jsonfile]/102400/real_time                -0.5738         -0.5739     169854761      72396975     169818274      72367221
OVERALL_GEOMEAN                                                                                                                                                            -0.5577         -0.5577             0             0             0             0
jose@ubuntu:~/klepsydra/klepsydra/development/community/kpsr-core-benchmarks/thirdparties/benchmark/tools$
```

# License

&copy; Copyright 2019-2020, Klepsydra Technologies, all rights reserved. Licensed under the terms in [LICENSE.md](./LICENSE.md)

This software and documentation are Copyright 2019-2020, Klepsydra Technologies
Limited and its licensees. All rights reserved. See [license file](./LICENSE.md) for full copyright notice and license terms.

# Contact

<https://www.klepsydra.com>
support@klepsydra.com
