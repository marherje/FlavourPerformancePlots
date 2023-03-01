#!/bin/bash

path=$PWD
path_lustre=/lustre/ific.uv.es/prj/ific/flc/ntuples-2022/250/Old

for slp in 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m
do
    sleep ${slp}
    mv ${path}/*root ${path_lustre}/.
done
