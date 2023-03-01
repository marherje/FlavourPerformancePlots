#!/bin/bash

path="../../../../FlavourTagExtension/ReTraining500NewSamples/lcfiplus_dataset/"

cp ${path}/Train_2f500_eL_ParticleSwarmTest_catA/* .
cp ${path}/Train_2f500_eL_ParticleSwarmTest_catB/2f500_eL_ParticleSwarmTest_c0_bdt.class.C 2f500_eL_ParticleSwarmTest_c1_bdt.class.C
cp ${path}/Train_2f500_eL_ParticleSwarmTest_catB/2f500_eL_ParticleSwarmTest_c0_bdt.weights.xml 2f500_eL_ParticleSwarmTest_c1_bdt.weights.xml
cp ${path}/Train_2f500_eL_ParticleSwarmTest_catC/2f500_eL_ParticleSwarmTest_c0_bdt.class.C 2f500_eL_ParticleSwarmTest_c2_bdt.class.C
cp ${path}/Train_2f500_eL_ParticleSwarmTest_catC/2f500_eL_ParticleSwarmTest_c0_bdt.weights.xml 2f500_eL_ParticleSwarmTest_c2_bdt.weights.xml
cp ${path}/Train_2f500_eL_ParticleSwarmTest_catD/2f500_eL_ParticleSwarmTest_c0_bdt.class.C 2f500_eL_ParticleSwarmTest_c3_bdt.class.C
cp ${path}/Train_2f500_eL_ParticleSwarmTest_catD/2f500_eL_ParticleSwarmTest_c0_bdt.weights.xml 2f500_eL_ParticleSwarmTest_c3_bdt.weights.xml
