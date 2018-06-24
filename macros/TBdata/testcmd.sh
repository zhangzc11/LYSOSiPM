#!/bin/bash


run=$1
root -l -b -q goodplot_0618.C+\(\""${run}"\",\"5\",180.0,300.0,15.0,24.0,15.0,24.0,18.0,21.0,18.0,21.0\)  > log.log
echo "${run}" >> count.txt; cat log.log | grep tot

scp plots_0618/${run}*.png zhicaiz@lxplus.cern.ch:/afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_June2018/
