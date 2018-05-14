#!/bin/bash

date > count.txt

run=781To783
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",200.0,450.0,20.0,30.0,5.0,12.0,23.0,27.0,8.0,12.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt


run=774To775
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",300.0,450.0,20.0,30.0,5.0,12.0,23.0,27.0,8.0,12.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt

run=759To762
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",350.0,450.0,9.0,21.0,10.0,17.0,12.0,18.0,13.0,17.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt


run=767To769
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",350.0,450.0,20.0,30.0,5.0,12.0,23.0,27.0,8.0,12.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt

run=870To872_and_891To895
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",200.0,450.0,13.0,23.0,10.0,21.0,15.0,20.0,12.0,17.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt



run=777
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",300.0,450.0,20.0,30.0,5.0,12.0,23.0,27.0,8.0,12.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt


run=873To877
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",200.0,850.0,13.0,23.0,10.0,21.0,15.0,20.0,12.0,17.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt


run=788
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",180.0,280.0,20.0,30.0,5.0,12.0,23.0,27.0,8.0,12.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt


run=878To882
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",200.0,850.0,13.0,23.0,10.0,21.0,15.0,20.0,12.0,17.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt

run=886To889
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",200.0,850.0,13.0,23.0,10.0,21.0,15.0,20.0,12.0,17.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt

run=981To985
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",120.0,450.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt

run=1022To1026
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",350.0,450.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt

run=975To978
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",180.0,450.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=1005To1011
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",200.0,850.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=955To960
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",200.0,450.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1012To1015
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",200.0,850.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=962To966
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",250.0,450.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=1016To1021
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",200.0,850.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=968To973
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",250.0,450.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=1089To1092
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",250.0,450.0,18.0,28.0,15.0,25.0,22.0,27.0,18.0,23.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1086To1088
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",350.0,450.0,18.0,28.0,15.0,25.0,22.0,27.0,18.0,23.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1097To1100
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",300.0,850.0,20.0,30.0,14.0,25.0,23.0,27.0,17.0,22.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=1103To1109
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",300.0,850.0,20.0,30.0,14.0,25.0,23.0,27.0,17.0,22.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1134To1139
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",300.0,850.0,20.0,30.0,14.0,25.0,23.0,27.0,17.0,22.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1140To1149
root -l -b -q goodplot_V3.C+\(\""${run}"\",\"14\",300.0,850.0,20.0,30.0,14.0,25.0,23.0,27.0,17.0,22.0\)  > log.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1012To1015
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",400.0,850.0,15.0,25.0,13.0,23.0,17.0,20.0,15.0,18.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1005To1011
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",400.0,850.0,15.0,25.0,13.0,23.0,17.0,20.0,15.0,18.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=997To999
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",400.0,850.0,15.0,25.0,13.0,23.0,17.0,20.0,15.0,18.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=829To850
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",400.0,850.0,12.0,22.0,10.0,19.0,14.0,17.0,13.0,16.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=855To895
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",400.0,850.0,14.0,24.0,10.0,19.0,16.0,19.0,13.0,16.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=955To996
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",400.0,850.0,15.0,25.0,13.0,23.0,17.0,20.0,15.0,18.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1103To1109
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",180.0,400.0,20.0,30.0,12.0,24.0,23.0,26.0,16.0,19.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1097To1100
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",220.0,500.0,20.0,30.0,12.0,24.0,23.0,26.0,16.0,19.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1089To1092
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",300.0,850.0,18.0,28.0,15.0,24.0,24.0,27.0,17.0,20.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1086To1088
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",400.0,850.0,18.0,28.0,15.0,24.0,24.0,27.0,17.0,20.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1134To1139
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",400.0,850.0,20.0,30.0,12.0,24.0,23.0,26.0,16.0,19.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1140To1149
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",400.0,850.0,20.0,30.0,12.0,24.0,23.0,26.0,16.0,19.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt

run=571To584
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",200.0,450.0,17.0,27.0,3.0,14.0,21.0,24.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=496To567
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",300.0,450.0,17.0,27.0,3.0,14.0,21.0,24.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt

run=476To485
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",180.0,450.0,17.0,27.0,3.0,14.0,21.0,24.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=486To491
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",220.0,450.0,17.0,27.0,3.0,14.0,21.0,24.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=492To494
root -l -b -q goodplot_V3.C+\(\"${run}\",\"16\",250.0,450.0,17.0,27.0,3.0,14.0,21.0,24.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=571To584
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",120.0,450.0,16.0,26.0,3.0,14.0,18.5,21.5,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=496To567
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",200.0,450.0,16.0,26.0,3.0,14.0,18.5,21.5,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=476To485
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",120.0,450.0,16.0,26.0,3.0,14.0,18.5,21.5,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=486To491
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",150.0,450.0,16.0,26.0,3.0,14.0,18.5,21.5,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=492To494
root -l -b -q goodplot_V3.C+\(\"${run}\",\"14\",180.0,450.0,16.0,26.0,3.0,14.0,18.5,21.5,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=571To584
root -l -b -q goodplot_V3.C+\(\"${run}\",\"15\",150.0,450.0,16.0,26.0,3.0,14.0,18.0,21.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=496To567
root -l -b -q goodplot_V3.C+\(\"${run}\",\"15\",200.0,450.0,16.0,26.0,3.0,14.0,18.0,21.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=476To485
root -l -b -q goodplot_V3.C+\(\"${run}\",\"15\",150.0,450.0,16.0,26.0,3.0,14.0,18.0,21.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=486To491
root -l -b -q goodplot_V3.C+\(\"${run}\",\"15\",180.0,450.0,16.0,26.0,3.0,14.0,18.0,21.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=492To494
root -l -b -q goodplot_V3.C+\(\"${run}\",\"15\",200.0,450.0,16.0,26.0,3.0,14.0,18.0,21.0,7.0,10.0\)  > log.log
cp plots_V3/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt

date >> count.txt
