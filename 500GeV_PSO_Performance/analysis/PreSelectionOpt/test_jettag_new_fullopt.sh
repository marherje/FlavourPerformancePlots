#!/bin/bash
mkdir results/
for pol in eL_pR eR_pL
do
    for cuts in 0 7 #{0..7}
    do
	for quality in FullOpt #FullOpt Old OptA
	do
	    for k in 50
	    do
		for cat in all catA catB catC catD
		do
		    #cuts=5
		    echo "jet:" $pol $cat $quality $cuts
		    root -l test_jettag_new.cc\(\"$pol\",$cuts,$k,\"$cat\",\"$quality\"\) > log_jet_bkg_${k}_${pol}_${cat}_bdt_${quality}_genkt_restorer_cuts${cuts}
		    mv log_jet_bkg_${k}_${pol}_${cat}_bdt_${quality}_genkt_restorer_cuts${cuts} results/.
		    mv jettag_cuts${cuts}_2f_hadronic_sample_${cat}_BDT_${quality}_${pol}_Kgamma50_500GeV.root results/.
		done
	    done
	done
    done
done
