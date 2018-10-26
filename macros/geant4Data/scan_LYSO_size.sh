#!/bin/sh

for LYSOsize in 4 6 8 10 12
do
	rm -rf LYSOSiPM_LYSOsize${LYSOsize}
	git clone git@github.com:zhangzc11/LYSOSiPM.git LYSOSiPM_LYSOsize${LYSOsize}
	cd LYSOSiPM_LYSOsize${LYSOsize}
	sed  "s/LYSO_sizeX = 8/LYSO_sizeX = ${LYSOsize}/g" include/LYSOSiPMDetectorConstruction.hh > new.hh
	sed  "s/LYSO_sizeY = 8/LYSO_sizeY = ${LYSOsize}/g" new.hh > new2.hh
	cp new2.hh include/LYSOSiPMDetectorConstruction.hh
	rm new.hh 
	rm new2.hh
	cd ..
	mkdir LYSOSiPM_LYSOsize${LYSOsize}-build
	cd LYSOSiPM_LYSOsize${LYSOsize}-build
	cmake ../LYSOSiPM_LYSOsize${LYSOsize}
	make -j8
	./LYSOSiPM -m run_x0.mac
	mv ntuple.root ../ntuples/ntuple_LYSOsizeScan_size${LYSOsize}_center.root
	./LYSOSiPM -m run_edge_s${LYSOsize}.mac
	mv ntuple.root ../ntuples/ntuple_LYSOsizeScan_size${LYSOsize}_edge.root
	cd ../
	rm -rf LYSOSiPM_LYSOsize${LYSOsize}
	rm -rf LYSOSiPM_LYSOsize${LYSOsize}-build
done
