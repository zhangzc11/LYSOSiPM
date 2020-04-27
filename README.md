# LYSOSiPM

Geant4 simulation of 12x12x3mm LYSO + SiPM response to MIP particles

=============================
-----------------------------
setup
-----------------------------
```
cd ..
mkdir LYSOSiPM-build
cd LYSOSiPM-build
cmake ../LYSOSiPM
make -j8
./LYSOSiPM
```

-----------------------------
How to install Geant4
-----------------------------
1. download the source files and unzip to /YourPath/geant4_10_04
http://geant4.web.cern.ch/geant4/support/download.shtml (ZIP format)

2. do the following:

```
cd /YourPath/
mkdir geant4_10_04-build
mkdir geant4_10_04-install
cd geant4_10_04-build
cmake -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_GDML=ON -DGEANT4_USE_QT=ON -DGEANT4_INSTALL_DATA=ON -DCMAKE_INSTALL_PREFIX=/YourPath/geant4_10_04-install /YourPath/geant4_10_04
make -j8 
make install
```

most likely it will complain about some missing libraries, for example `exerces`, for ubuntu, i do this:
```
sudo apt-get install libxerces-c-dev
sudo apt-get install libxerces-c-doc
sudo apt-get install libxerces-c-samples
```

3. then you should be able to use your geant4 by source the following file:

  /YourPath/geant4_10_04-install/share/Geant4-10.4.0/geant4make/geant4make.sh

  Good Luck!


