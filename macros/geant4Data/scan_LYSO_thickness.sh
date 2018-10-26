#!/bin/sh

for LYSOthick in 2.5 3.0 3.5 4.0 4.5
do
	rm -rf LYSOSiPM_LYSOthick${LYSOthick}
	git clone git@github.com:zhangzc11/LYSOSiPM.git LYSOSiPM_LYSOthick${LYSOthick}
	cd LYSOSiPM_LYSOthick${LYSOthick}
	sed  "s/crystal_thick = 4\.0/crystal_thick = ${LYSOthick}/g" include/LYSOSiPMDetectorConstruction.hh > new.hh
	cp new.hh include/LYSOSiPMDetectorConstruction.hh
	rm new.hh 
	cd ..
	mkdir LYSOSiPM_LYSOthick${LYSOthick}-build
	cd LYSOSiPM_LYSOthick${LYSOthick}-build
	cmake ../LYSOSiPM_LYSOthick${LYSOthick}
	make -j8
	./LYSOSiPM -m run_x0.mac
	mv ntuple.root ../ntuples/ntuple_LYSOthickScan_thick${LYSOthick}_center.root
	./LYSOSiPM -m run_edge_s8.mac
	mv ntuple.root ../ntuples/ntuple_LYSOthickScan_thick${LYSOthick}_edge.root
	cd ../
	rm -rf LYSOSiPM_LYSOthick${LYSOthick}
	rm -rf LYSOSiPM_LYSOthick${LYSOthick}-build
done
