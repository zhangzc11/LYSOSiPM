#!/bin/bash
for LYSOsize in 4 6 8 10 12
do
root -l -b -q rereco.C+\(\"ntuple_LYSOsizeScan_size${LYSOsize}_center.root\"\)
root -l -b -q rereco.C+\(\"ntuple_LYSOsizeScan_size${LYSOsize}_edge.root\"\)
root -l -b -q rereco.C+\(\"ntuple_LYSOsizeScan_size${LYSOsize}_center_md.root\"\)
root -l -b -q rereco.C+\(\"ntuple_LYSOsizeScan_size${LYSOsize}_edge_md.root\"\)
done

for LYSOthick in 2.5 3.0 3.5 4.0 4.5
do
root -l -b -q rereco.C+\(\"ntuple_LYSOthickScan_thick${LYSOthick}_center.root\"\)
root -l -b -q rereco.C+\(\"ntuple_LYSOthickScan_thick${LYSOthick}_edge.root\"\)
root -l -b -q rereco.C+\(\"ntuple_LYSOthickScan_thick${LYSOthick}_center_md.root\"\)
root -l -b -q rereco.C+\(\"ntuple_LYSOthickScan_thick${LYSOthick}_edge_md.root\"\)
done

for LYSOpolish in 20 40 60 80 90 100
do
root -l -b -q rereco.C+\(\"ntuple_LYSOpolishScan_polish${LYSOpolish}_center.root\"\)
root -l -b -q rereco.C+\(\"ntuple_LYSOpolishScan_polish${LYSOpolish}_edge.root\"\)
root -l -b -q rereco.C+\(\"ntuple_LYSOpolishScan_polish${LYSOpolish}_center_md.root\"\)
root -l -b -q rereco.C+\(\"ntuple_LYSOpolishScan_polish${LYSOpolish}_edge_md.root\"\)
done
