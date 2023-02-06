#!/bin/sh
for pol in eL_pR eR_pL
do
    for quality in Old OptA FullOpt
    do
	for cat in all catA catB catC catD
	do
	    for cut in {0..9}
	    do
		for k in 35 #90
		do
		    root -l -q analysis250GeV.cc\($cut,\"$pol\",\"$k\",\"$cat\",\"$quality\"\)
		    mv efficiency*png selection_plots/.
		done		 
	    done
	done
    done
done
