#!/bin/sh

for LYSOthick in 2.5 3.0 3.5 4.0 4.5
do
	if [ -f ntuples/ntuple_LYSOthickScan_thick${LYSOthick}_edge_md.root ]
    then
        echo "thick ${LYSOthick} already done, skipping"
    else
		echo "working on thick ${LYSOthick}"
		rm -rf LYSOSiPM_LYSOthick${LYSOthick}_md
		#git clone git@github.com:zhangzc11/LYSOSiPM.git LYSOSiPM_LYSOthick${LYSOthick}_md
		cp -r LYSOSiPM_ref LYSOSiPM_LYSOthick${LYSOthick}_md
		cd LYSOSiPM_LYSOthick${LYSOthick}_md
		sed  "s/crystal_thick = 4\.0/crystal_thick = ${LYSOthick}/g" include/LYSOSiPMDetectorConstruction.hh > new.hh
		cp new.hh include/LYSOSiPMDetectorConstruction.hh
		rm new.hh 
		cd ..
		mkdir LYSOSiPM_LYSOthick${LYSOthick}_md-build
		cd LYSOSiPM_LYSOthick${LYSOthick}_md-build
		cmake ../LYSOSiPM_LYSOthick${LYSOthick}_md
		make -j8
		if [ -f ../ntuples/ntuple_LYSOthickScan_thick${LYSOthick}_center_md.root ]
        then
            echo "thick${LYSOthick}_center already done, skipping"
        else
			./LYSOSiPM -m run_x0_md.mac
			mv ntuple.root ../ntuples/ntuple_LYSOthickScan_thick${LYSOthick}_center_md.root
		fi
		if [ -f ../ntuples/ntuple_LYSOthickScan_thick${LYSOthick}_edge_md.root ]
		then
			echo "thick${LYSOthick}_edge already done, skipping"
		else
			./LYSOSiPM -m run_edge_s8_md.mac
			mv ntuple.root ../ntuples/ntuple_LYSOthickScan_thick${LYSOthick}_edge_md.root
		fi
		cd ../
		rm -rf LYSOSiPM_LYSOthick${LYSOthick}_md
		rm -rf LYSOSiPM_LYSOthick${LYSOthick}_md-build
	fi
done
