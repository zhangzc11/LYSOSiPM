#!/bin/sh

for LYSOthick in 2.5 3.0 3.5 4.0 4.5
do
	rm -rf LYSOSiPM_LYSOthick${LYSOthick}_md
	git clone git@github.com:zhangzc11/LYSOSiPM.git LYSOSiPM_LYSOthick${LYSOthick}_md
	cd LYSOSiPM_LYSOthick${LYSOthick}_md
	sed  "s/crystal_thick = 4\.0/crystal_thick = ${LYSOthick}/g" include/LYSOSiPMDetectorConstruction.hh > new.hh
	cp new.hh include/LYSOSiPMDetectorConstruction.hh
	rm new.hh 
	cd ..
	mkdir LYSOSiPM_LYSOthick${LYSOthick}_md-build
	cd LYSOSiPM_LYSOthick${LYSOthick}_md-build
	cmake ../LYSOSiPM_LYSOthick${LYSOthick}_md
	make -j8
	./LYSOSiPM -m run_x0_md.mac
	mv ntuple.root ../ntuples/ntuple_LYSOthickScan_thick${LYSOthick}_center_md.root
	./LYSOSiPM -m run_edge_s8_md.mac
	mv ntuple.root ../ntuples/ntuple_LYSOthickScan_thick${LYSOthick}_edge_md.root
	cd ../
	rm -rf LYSOSiPM_LYSOthick${LYSOthick}_md
	rm -rf LYSOSiPM_LYSOthick${LYSOthick}_md-build
done
