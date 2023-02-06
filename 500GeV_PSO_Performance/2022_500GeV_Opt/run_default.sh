#!/bin/bash
# file name: kt_xNAMEfile.sh

path="/lhome/ific/m/marherje/ParticleSwarmOptimization/500GeV_PSO_Performance/2022_500GeV_Opt"
source ${path}/init_ilcsoft.sh
cp -r ${path}/data $PWD/.
cp -r ${path}/lib $PWD/.
cp -r ${path}/lcfiweights $PWD/.
cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_xPROD_xFPROD_xNAMEfile.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libQQbarProcessor.so"
echo $PWD
Marlin ${PWD}/test_xPROD_xFPROD_xNAMEfile.xml

