#!/bin/sh
for pol in eL_pR eR_pL
do
    for cat in all catA
    do
	for quality in Good Medium Bad
	do
	    for cut in {0..0}
	    do
		for k in 35 #90
		do
		    root -l -q analysis250GeV.cc\($cut,\"$pol\",\"$k\",\"$cat\",\"$quality\"\)
		done		 
	    done
	done
    done
done
