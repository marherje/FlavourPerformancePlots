#!/bin/bash

for pol in eL_pR eR_pL
do
    hadd mergedfile_${pol}.root *${pol}*root
done

root -l -q SelectCategoryA.C
