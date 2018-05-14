#!/bin/bash


run=1292To1324
root -l -b -q goodplot_V3_3mm.C+\(\""${run}"\",\"15\",250.0,450.0,16.0,25.0,14.0,26.0,21.0,25.0,20.0,24.0\)  > log2.log
root -l -b -q goodplot_V3_3mm.C+\(\""${run}"\",\"14\",250.0,450.0,16.0,25.0,12.0,24.0,17.0,20.0,16.0,19.0\)  > log2.log
cp plots_V3/Run"${run}"_*.png /afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_March2018_V3/
echo "${run}" >> count2.txt; cat log2.log | grep tot

