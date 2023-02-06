#!/bin/sh
mkdir ROC_plots
for cut in 0 7
do
    for cat in all catA catB catC catD
    do
	root -l -q root JetTag_comparison.C\(${cut},\"50\",\"${cat}\"\)
	    mv c_eff_c.png ROC_plots/JetTag_c_Cut${cut}_${cat}_bdt_${quality}.png
	    mv c_eff_b.png ROC_plots/JetTag_b_Cut${cut}_${cat}_bdt_${quality}.png
    done
done
