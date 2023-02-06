#!/bin/bash

for pol in eL eR
do
    cp ../../ReTraining500_CatA/lcfiplus_dataset/Train_2f500_${pol}_ParticleSwarmTest_catA/2f500_${pol}_ParticleSwarmTest_c0_bdt.class.C 2f500_${pol}_ParticleSwarmTest_c0_bdt.class.C
    cp ../../ReTraining500_CatA/lcfiplus_dataset/Train_2f500_${pol}_ParticleSwarmTest_catA/2f500_${pol}_ParticleSwarmTest_c0_bdt.weights.xml 2f500_${pol}_ParticleSwarmTest_c0_bdt.weights.xml
    cp ../../ReTraining500_CatB/lcfiplus_dataset/Train_2f500_${pol}_ParticleSwarmTest_catB/2f500_${pol}_ParticleSwarmTest_c0_bdt.class.C 2f500_${pol}_ParticleSwarmTest_c1_bdt.class.C
    cp ../../ReTraining500_CatB/lcfiplus_dataset/Train_2f500_${pol}_ParticleSwarmTest_catB/2f500_${pol}_ParticleSwarmTest_c0_bdt.weights.xml 2f500_${pol}_ParticleSwarmTest_c1_bdt.weights.xml
    cp ../../ReTraining500_CatC/lcfiplus_dataset/Train_2f500_${pol}_ParticleSwarmTest_catC/2f500_${pol}_ParticleSwarmTest_c0_bdt.class.C 2f500_${pol}_ParticleSwarmTest_c2_bdt.class.C
    cp ../../ReTraining500_CatC/lcfiplus_dataset/Train_2f500_${pol}_ParticleSwarmTest_catC/2f500_${pol}_ParticleSwarmTest_c0_bdt.weights.xml 2f500_${pol}_ParticleSwarmTest_c2_bdt.weights.xml
    cp ../../ReTraining500_CatD/lcfiplus_dataset/Train_2f500_${pol}_ParticleSwarmTest_catD/2f500_${pol}_ParticleSwarmTest_c0_bdt.class.C 2f500_${pol}_ParticleSwarmTest_c3_bdt.class.C
    cp ../../ReTraining500_CatD/lcfiplus_dataset/Train_2f500_${pol}_ParticleSwarmTest_catD/2f500_${pol}_ParticleSwarmTest_c0_bdt.weights.xml 2f500_${pol}_ParticleSwarmTest_c3_bdt.weights.xml
done
