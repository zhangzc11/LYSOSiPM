#!/bin/bash

date > count.txt
mkdir -p /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/

run=870To872_and_891To895
root -l -b -q goodplot_V4.C+\(\"${run}\",\"14\",200.0,450.0,13.0,23.0,10.0,21.0,15.0,20.0,12.0,17.0\)  > log.log
cp plots_V4/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt
cat log.log | grep tot >> count.txt


run=955To960
root -l -b -q goodplot_V4.C+\(\""${run}"\",\"14\",200.0,450.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V4/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=1005To1011
root -l -b -q goodplot_V4.C+\(\""${run}"\",\"14\",200.0,850.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log.log
cp plots_V4/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1103To1109
root -l -b -q goodplot_V4.C+\(\""${run}"\",\"14\",300.0,850.0,20.0,30.0,14.0,25.0,23.0,27.0,17.0,22.0\)  > log.log
cp plots_V4/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=1012To1015
root -l -b -q goodplot_V4.C+\(\"${run}\",\"16\",400.0,850.0,15.0,25.0,13.0,23.0,17.0,20.0,15.0,18.0\)  > log.log
cp plots_V4/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


run=1086To1088
root -l -b -q goodplot_V4.C+\(\"${run}\",\"16\",400.0,850.0,18.0,28.0,15.0,24.0,24.0,27.0,17.0,20.0\)  > log.log
cp plots_V4/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=486To491
root -l -b -q goodplot_V4.C+\(\"${run}\",\"16\",220.0,450.0,17.0,27.0,3.0,14.0,21.0,24.0,7.0,10.0\)  > log.log
cp plots_V4/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=486To491
root -l -b -q goodplot_V4.C+\(\"${run}\",\"14\",150.0,450.0,16.0,26.0,3.0,14.0,18.5,21.5,7.0,10.0\)  > log.log
cp plots_V4/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt



run=486To491
root -l -b -q goodplot_V4.C+\(\"${run}\",\"15\",180.0,450.0,16.0,26.0,3.0,14.0,18.0,21.0,7.0,10.0\)  > log.log
cp plots_V4/Run${run}_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt

run=1292To1324
root -l -b -q goodplot_V4_3mm.C+\(\""${run}"\",\"14\",250.0,450.0,16.0,25.0,12.0,24.0,17.0,20.0,16.0,19.0\)  > log.log
cp plots_V4/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt

run=1292To1324
root -l -b -q goodplot_V4_3mm.C+\(\""${run}"\",\"15\",250.0,450.0,16.0,25.0,14.0,26.0,21.0,25.0,20.0,24.0\)  > log.log
cp plots_V4/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count.txt; cat log.log | grep tot >> count.txt


date >> count.txt

