#!/bin/bash


run=1103To1109
root -l -b -q goodplot_V4.C+\(\""${run}"\",\"14\",300.0,850.0,20.0,30.0,14.0,25.0,23.0,27.0,17.0,22.0\)  > log2.log
cp plots_V4/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count2.txt; cat log2.log | grep tot

run=1005To1011
root -l -b -q goodplot_V4.C+\(\""${run}"\",\"14\",200.0,850.0,14.0,25.0,13.0,24.0,16.0,21.0,16.0,21.0\)  > log2.log
cp plots_V4/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
echo "${run}" >> count2.txt; cat log2.log | grep tot


run=1097To1100
root -l -b -q goodplot_V4.C+\(\""${run}"\",\"14\",300.0,850.0,20.0,30.0,14.0,25.0,23.0,27.0,17.0,22.0\)  > log2.log
cp plots_V4/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V4/
#echo "${run}" >> count2.txt; cat log2.log | grep tot >> count.txt
echo "${run}";  cat log2.log | grep tot 


