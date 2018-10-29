#!/bin/sh

for LYSOpolish in 20 40 60 80 90 100 
do
	if [ -f ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_edge_md.root ]
	then
		echo "polish ${LYSOpolish} already done, skipping"
	else
		echo "working on polish ${LYSOpolish}"
		rm -rf LYSOSiPM_LYSOpolish${LYSOpolish}_md
		#git clone git@github.com:zhangzc11/LYSOSiPM.git LYSOSiPM_LYSOpolish${LYSOpolish}
		cp -r LYSOSiPM_ref LYSOSiPM_LYSOpolish${LYSOpolish}_md
		cd LYSOSiPM_LYSOpolish${LYSOpolish}_md
		sed  "s/99000/${LYSOpolish}/g" src/LYSOSiPMDetectorConstruction.cc > new.cc
		cp new.cc src/LYSOSiPMDetectorConstruction.cc
		rm new.cc
		cd ..
		mkdir LYSOSiPM_LYSOpolish${LYSOpolish}_md-build
		cd LYSOSiPM_LYSOpolish${LYSOpolish}_md-build
		cmake ../LYSOSiPM_LYSOpolish${LYSOpolish}_md
		make -j8
		if [ -f ../ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_center_md.root ]
		then
			echo "polish${LYSOpolish}_center already done, skipping"
		else
			./LYSOSiPM -m run_x0_md.mac
			mv ntuple.root ../ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_center_md.root
		fi
		if [ -f ../ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_edge_md.root ]
		then
			echo "polish${LYSOpolish}_edge already done, skipping"
		else
			./LYSOSiPM -m run_edge_s8_md.mac
			mv ntuple.root ../ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_edge_md.root
		fi
		cd ../
		rm -rf LYSOSiPM_LYSOpolish${LYSOpolish}_md
		rm -rf LYSOSiPM_LYSOpolish${LYSOpolish}_md-build
	fi
done
