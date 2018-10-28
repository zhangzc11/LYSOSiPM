#!/bin/sh

for LYSOpolish in 20 40 60 80 90 100 
do
	if [ -f ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_edge.root ]
	then
		echo "polish ${LYSOpolish} already done, skipping"
	else
		echo "working on polish ${LYSOpolish}"
		rm -rf LYSOSiPM_LYSOpolish${LYSOpolish}
		#git clone git@github.com:zhangzc11/LYSOSiPM.git LYSOSiPM_LYSOpolish${LYSOpolish}
		cp -r LYSOSiPM_ref LYSOSiPM_LYSOpolish${LYSOpolish}
		cd LYSOSiPM_LYSOpolish${LYSOpolish}
		sed  "s/99000/${LYSOpolish}/g" src/LYSOSiPMDetectorConstruction.cc > new.cc
		cp new.cc src/LYSOSiPMDetectorConstruction.cc
		rm new.cc
		cd ..
		mkdir LYSOSiPM_LYSOpolish${LYSOpolish}-build
		cd LYSOSiPM_LYSOpolish${LYSOpolish}-build
		cmake ../LYSOSiPM_LYSOpolish${LYSOpolish}
		make -j8
		if [ -f ../ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_center.root ]
		then
			echo "polish${LYSOpolish}_center already done, skipping"
		else
			./LYSOSiPM -m run_x0.mac
			mv ntuple.root ../ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_center.root
		fi
		if [ -f ../ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_edge.root ]
		then
			echo "polish${LYSOpolish}_edge already done, skipping"
		else
			./LYSOSiPM -m run_edge_s8.mac
			mv ntuple.root ../ntuples/ntuple_LYSOpolishScan_polish${LYSOpolish}_edge.root
		fi
		cd ../
		rm -rf LYSOSiPM_LYSOpolish${LYSOpolish}
		rm -rf LYSOSiPM_LYSOpolish${LYSOpolish}-build
	fi
done
