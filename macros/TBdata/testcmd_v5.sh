#!/bin/bash


run=$1

##alignment of Fridy Jun15 with different aspect ratios, first run 946

root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"1\",\"1\",\"LP2_10\",100.0,400.0,12.5,24.5,10.0,22.0,17.0,19.0,15.0,17.0,\"_LP2_10\"\)  > log.log
root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"2\",\"2\",\"LP2_10\",100.0,400.0,13.0,25.0,10.0,22.0,18.0,20.0,16.0,18.0,\"_LP2_10\"\)  > log.log
root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",100.0,800.0,13.0,26.0,11.5,24.5,17.0,23.0,14.0,20.0,\"_LP2_10\"\)  > log.log
root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"5\",\"5\",\"LP2_10\",50.0,200.0,13.0,25.0,10.0,22.0,16.0,19.0,15.0,18.0,\"_LP2_10\"\)  > log.log
root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"6\",\"6\",\"LP2_10\",50.0,300.0,14.5,22.5,13.0,21.0,17.0,20.0,15.5,18.5,\"_LP2_10\"\)  > log.log



###alignment of Thursday Jun14 with downstream after UVA setup
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"1\",\"1\",\"LP2_10\",100.0,400.0,12.5,24.5,10.0,22.0,17.0,19.0,15.0,17.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"2\",\"2\",\"LP2_10\",100.0,400.0,13.0,25.0,10.0,22.0,18.0,20.0,16.0,18.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",150.0,850.0,12.5,25.5,9.5,22.0,17.0,22.0,12.5,18.5,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",100.0,400.0,13.0,26.0,11.5,24.5,17.0,23.0,14.0,20.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"16\",\"4\",\"15\",\"IL_200mV\",100.0,400.0,13.0,26.0,11.5,24.5,17.0,23.0,14.0,20.0,\"_time_line_IL_200mV\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"5\",\"5\",\"LP2_10\",200.0,600.0,11.5,19.5,17.0,25.0,12.5,18.5,18.0,24.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"5\",\"7\",\"IL_200mV\",200.0,600.0,11.5,19.5,17.0,25.0,12.5,18.5,18.0,24.0,\"_time_line_IL_200mV\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"6\",\"6\",\"LP2_10\",200.0,600.0,15.0,20.0,20.0,25.0,16.0,19.0,21.0,24.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"16\",\"6\",\"13\",\"IL_200mV\",200.0,600.0,15.0,20.0,20.0,25.0,16.0,19.0,21.0,24.0,\"_time_line_IL_200mV\"\)  > log.log




##alignment of Wednesday Jun13 with downstream

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",150.0,850.0,13.0,26.0,13.0,26.0,17.0,23.0,16.0,22.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",150.0,850.0,12.5,25.5,11.5,24.5,17.0,23.0,14.0,20.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"2\",\"2\",\"LP2_10\",100.0,400.0,13.0,25.0,12.0,24.0,18.0,20.0,18.0,20.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"1\",\"1\",\"LP2_10\",100.0,400.0,12.5,24.5,12.0,24.0,18.0,20.0,18.0,20.0,\"_LP2_10\"\)  > log.log

###alignment of Wednesday Jun13 with wide beam

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"23\",\"5\",\"IL_200mV\",180.0,300.0,12.0,17.0,14.0,18.0,12.0,17.0,14.0,18.0,\"_time_line_IL_200mV\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"6\",\"6\",\"LP2_10\",150.0,850.0,13.0,17.0,10.0,14.0,13.0,17.0,10.0,14.0,\"_LP2_10\"\)  > log.log

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",150.0,850.0,10.0,23.0,11.0,24.0,14.0,20.0,14.0,20.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",150.0,850.0,9.5,22.5,9.5,22.0,12.5,18.5,12.0,18.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"2\",\"2\",\"LP2_10\",100.0,400.0,9.5,21.5,8.5,20.5,14.0,16.0,14.0,16.0,\"_LP2_10\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"1\",\"1\",\"LP2_10\",100.0,400.0,10.5,22.5,9.0,21.0,15.0,17.0,14.0,16.0,\"_LP2_10\"\)  > log.log

###alignment of Tuesday Jun12

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"23\",\"5\",\"IL_200mV\",50.0,800.0,15.0,24.0,17.0,27.0,16.0,22.0,20.0,25.0,\"_time_line_IL_200mV\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",50.0,800.0,15.0,24.0,17.0,27.0,16.0,22.0,20.0,25.0\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",50.0,800.0,15.0,24.0,17.0,27.0,16.0,22.0,20.0,25.0\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot


#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"5\",\"5\",\"LP2_10\",250.0,800.0,15.0,24.0,17.0,27.0,16.0,22.0,20.0,25.0\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"5\",\"5\",\"LP2_5\",250.0,800.0,15.0,24.0,17.0,27.0,16.0,22.0,20.0,25.0,\"_LP2_5\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot


#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"6\",\"6\",\"LP2_10\",50.0,800.0,15.0,24.0,17.0,27.0,16.0,22.0,20.0,25.0\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot


###alignment of Monday Jun11
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"5\",\"5\",\"LP2_10\",50.0,200.0,15.0,24.0,17.0,27.0,16.0,22.0,20.0,25.0\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"5\",\"7\",\"IL_100mV\",50.0,200.0,15.0,24.0,17.0,27.0,16.0,22.0,20.0,25.0,\"_timeline_IL100mV\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"9\",\"16\",\"10\",\"IL_200mV\",50.0,200.0,14.0,22.0,19.0,27.0,16.0,20.0,20.0,25.0,\"_timeline_IL200mV\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"9\",\"16\",\"16\",\"LP2_10\",50.0,200.0,14.0,22.0,19.0,27.0,16.0,20.0,20.0,25.0,\"_LP2_10\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"5\",\"5\",\"LP2_10\",50.0,800.0,14.0,22.0,19.0,27.0,16.0,20.0,20.0,25.0,\"_LP2_10\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"1\",\"1\",\"LP2_10\",50.0,800.0,14.0,22.0,19.0,27.0,16.0,20.0,20.0,25.0,\"_LP2_10\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"2\",\"2\",\"LP2_10\",50.0,800.0,14.0,22.0,19.0,27.0,16.0,20.0,20.0,25.0,\"_LP2_10\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",50.0,800.0,14.0,22.0,19.0,27.0,16.0,20.0,20.0,25.0,\"_LP2_10\"\)  > log.log
echo "${run}" >> count.txt; cat log.log | grep tot

#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",50.0,800.0,14.0,22.0,19.0,27.0,16.0,20.0,20.0,25.0,\"_LP2_10\"\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot



#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"1\",\"1\",\"LP2_10\",10.0,800.0,15.0,23.0,19.0,27.0,16.0,22.0,20.0,25.0\)  > log.log
#echo "${run}" >> count.txt; cat log.log | grep tot


###alignment of Monday with 1x1mm trigger
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"9\",\"16\",\"16\",\"LP2_10\",600.0,850.0,12.0,20.0,20.0,30.0,16.0,18.0,24.0,26.0,\"_600To850\"\)  > log.log
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"9\",\"16\",\"16\",\"LP2_10\",200.0,600.0,12.0,20.0,20.0,30.0,16.0,18.0,24.0,26.0,\"_200To600\"\)  > log.log


###alignment of Sunday Jun10
#root -l -b -q goodplot_0618_v5.C+\(\""${run}"\",\"0\",\"5\",\"7\",\"SPL_200mV\",100.0,200.0,15.0,24.0,19.0,27.0,18.0,22.0,21.0,25.0,\"_timeline_SPL200mV\"\)  > log.log

scp plots_0618_v5/Run${run}*.png zhicaiz@lxplus.cern.ch:/afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_June2018_v5/
