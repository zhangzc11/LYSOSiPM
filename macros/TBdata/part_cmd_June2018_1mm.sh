#!/bin/bash
destDir=/afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_June2018_v5_final_1mm/

run=1071To1180
#root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"1\",\"1\",\"LP2_10\",100.0,250.0,100.0,400.0,13.0,21.0,13.0,21.0,15.0,18.0,15.0,18.0,\"_LP2_10\"\)  > log.log
#mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",100.0,250.0,300.0,800.0,13.0,24.0,10.0,21.0,16.0,22.0,12.0,18.0,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1154To1180
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"2\",\"2\",\"LP2_10\",100.0,250.0,100.0,400.0,15.5,20.5,12.5,17.5,16.5,19.5,13.5,16.5,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1185To1215
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"2\",\"2\",\"LP2_10\",100.0,250.0,100.0,400.0,14.5,19.5,12.5,17.5,15.5,18.5,13.5,16.5,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1438To1505
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"6\",\"6\",\"LP2_10\",100.0,250.0,200.0,500.0,14.5,22.5,9.5,17.5,17.0,20.0,12.0,15.0,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"5\",\"5\",\"LP2_10\",100.0,250.0,200.0,500.0,16.0,21.0,12.5,17.5,17.0,20.0,13.5,16.5,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot


run=1320To1429
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"6\",\"6\",\"LP2_10\",160.0,300.0,200.0,800.0,17.5,22.5,12.0,17.0,18.5,21.5,13.0,16.0,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1226To1276
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"2\",\"2\",\"LP2_10\",100.0,250.0,200.0,800.0,13.5,18.5,14.5,18.5,14.5,17.5,15.0,18.0,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=660To827
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",100.0,250.0,180.0,800.0,12.0,25.0,9.5,22.5,16.0,22.0,13.0,19.0,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1314To1360
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",160.0,300.0,200.0,800.0,11.5,23.5,11.0,23.0,14.0,20.0,14.0,20.0,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=660To680
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",100.0,250.0,200.0,800.0,13.0,26.0,11.5,24.5,16.0,22.0,14.5,20.5,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1438To1505
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",100.0,250.0,300.0,800.0,12.0,22.0,11.0,21.0,14.0,20.0,13.0,19.0,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1185To1276
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",100.0,250.0,500.0,880.0,14.0,19.0,15.5,20.5,14.0,19.0,15.5,20.5,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1314To1360
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",160.0,300.0,500.0,880.0,14.0,19.0,15.5,20.5,14.0,19.0,15.5,20.5,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1371To1393
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",80.0,150.0,500.0,880.0,14.0,19.0,15.5,20.5,14.0,19.0,15.5,20.5,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1394To1424
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"4\",\"4\",\"LP2_10\",50.0,90.0,500.0,880.0,14.0,19.0,15.5,20.5,14.0,19.0,15.5,20.5,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=1226To1276
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"3\",\"3\",\"LP2_10\",100.0,250.0,600.0,900.0,13.5,21.5,11.0,19.0,14.5,20.5,12.0,18.0,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

run=518To523
root -l -b -q goodplot_0618_v5_final_1mm.C+\(\""${run}"\",\"0\",\"5\",\"5\",\"LP2_10\",70.0,140.0,600.0,900.0,15.5,20.5,21.0,25.0,15.5,20.5,21.0,25.0,\"_LP2_10\"\)  > log.log
mv plots_0618_v5_final_1mm/*.png ${destDir}; echo "${run}" >> count_June2018.txt; cat log.log | grep tot

#mv plots_0618_v5_final_1mm/Run${run}*.png ${destDir} 
#mv plots_0618_v5_final_1mm/*.png ${destDir} 
