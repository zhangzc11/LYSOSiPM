# $Id: CMakeLists.txt 86065 2014-11-07 08:51:15Z gcosmo $

#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(LYSOSiPM)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(LYSOSiPM LYSOSiPM.cc ${sources} ${headers} include/LYSOSiPMPhysicsList.hh src/LYSOSiPMPhysicsList.cc)
target_link_libraries(LYSOSiPM ${Geant4_LIBRARIES})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build LYSOSiPM. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(LYSOSiPM_SCRIPTS
  LYSOSiPM.out
  LYSOSiPM.in
  icons.mac
  gui.mac
  run.png
  init_vis.mac
  run1.mac
  run2.mac
  run_x0.mac
  run_x0_md.mac
  run_x2.mac
  run_x2_md.mac
  run_x4.mac
  run_x4_md.mac
  run_x5.mac
  run_x5_md.mac
  vis.mac
  )

foreach(_script ${LYSOSiPM_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS LYSOSiPM DESTINATION bin)
