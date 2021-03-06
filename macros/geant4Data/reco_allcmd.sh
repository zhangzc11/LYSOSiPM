#!/bin/bash
for LYSOsize in 4 6 8 10 12
do
sed "s/ntuple_ref_center/ntuple_LYSOsizeScan_size${LYSOsize}_center/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
sed "s/ntuple_ref_center/ntuple_LYSOsizeScan_size${LYSOsize}_edge/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
sed "s/ntuple_ref_center/ntuple_LYSOsizeScan_size${LYSOsize}_center_md/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
sed "s/ntuple_ref_center/ntuple_LYSOsizeScan_size${LYSOsize}_edge_md/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
done

for LYSOthick in 2.5 3.0 3.5 4.0 4.5
do
sed "s/ntuple_ref_center/ntuple_LYSOthickScan_thick${LYSOthick}_center/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
sed "s/ntuple_ref_center/ntuple_LYSOthickScan_thick${LYSOthick}_edge/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
sed "s/ntuple_ref_center/ntuple_LYSOthickScan_thick${LYSOthick}_center_md/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
sed "s/ntuple_ref_center/ntuple_LYSOthickScan_thick${LYSOthick}_edge_md/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C

done

for LYSOpolish in 20 40 60 80 90 100
do
sed "s/ntuple_ref_center/ntuple_LYSOpolishScan_polish${LYSOpolish}_center/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
sed "s/ntuple_ref_center/ntuple_LYSOpolishScan_polish${LYSOpolish}_edge/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
sed "s/ntuple_ref_center/ntuple_LYSOpolishScan_polish${LYSOpolish}_center_md/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
sed "s/ntuple_ref_center/ntuple_LYSOpolishScan_polish${LYSOpolish}_edge_md/g" template_rereco_nocompile.C > rereco_nocompile.C
root -l -b -q rereco_nocompile.C
done
