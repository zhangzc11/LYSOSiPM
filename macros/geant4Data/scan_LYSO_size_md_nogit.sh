#!/bin/sh

for LYSOsize in 4 6 8 10 12
do
	if [ -f ntuples/ntuple_LYSOsizeScan_size${LYSOsize}_edge_md.root ]
    then
        echo "size ${LYSOsize} already done, skipping"
    else
		echo "working on size ${LYSOsize}"
		rm -rf LYSOSiPM_LYSOsize${LYSOsize}_md
		#git clone git@github.com:zhangzc11/LYSOSiPM.git LYSOSiPM_LYSOsize${LYSOsize}_md
		cp -r LYSOSiPM_ref LYSOSiPM_LYSOsize${LYSOsize}_md
		cd LYSOSiPM_LYSOsize${LYSOsize}_md
		sed  "s/LYSO_sizeX = 8/LYSO_sizeX = ${LYSOsize}/g" include/LYSOSiPMDetectorConstruction.hh > new.hh
		sed  "s/LYSO_sizeY = 8/LYSO_sizeY = ${LYSOsize}/g" new.hh > new2.hh
		cp new2.hh include/LYSOSiPMDetectorConstruction.hh
		rm new.hh
		rm new2.hh
		cd ..
		mkdir LYSOSiPM_LYSOsize${LYSOsize}_md-build
		cd LYSOSiPM_LYSOsize${LYSOsize}_md-build
		cmake ../LYSOSiPM_LYSOsize${LYSOsize}_md
		make -j8
		if [ -f ../ntuples/ntuple_LYSOsizeScan_size${LYSOsize}_center_md.root ]
        then
            echo "size${LYSOsize}_center already done, skipping"
        else
			./LYSOSiPM -m run_x0_md.mac
			mv ntuple.root ../ntuples/ntuple_LYSOsizeScan_size${LYSOsize}_center_md.root
		fi
		if [ -f ../ntuples/ntuple_LYSOsizeScan_size${LYSOsize}_edge_md.root ]
		then
			echo "size${LYSOsize}_edge already done, skipping"
		else
			./LYSOSiPM -m run_edge_s${LYSOsize}_md.mac
			mv ntuple.root ../ntuples/ntuple_LYSOsizeScan_size${LYSOsize}_edge_md.root
		fi
		cd ../
		rm -rf LYSOSiPM_LYSOsize${LYSOsize}_md
		rm -rf LYSOSiPM_LYSOsize${LYSOsize}_md-build
	fi
done
