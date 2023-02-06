#!/bin/sh
mkdir ROC_plots
for cut in {0..9}
do
    for cat in all catA catB catC catD
    do
	for quality in Old OptA FullOpt
	do
	    root -l -q JetTag.C\(${cut},\"35\",\"${cat}\",\"${quality}\"\)
	    mv c_eff_c.png ROC_plots/JetTag_c_Cut${cut}_${cat}_bdt_${quality}.png
	    mv c_eff_b.png ROC_plots/JetTag_b_Cut${cut}_${cat}_bdt_${quality}.png
	done
    done
done
