mkdir mc_study/
for pol in eL_pR eR_pL
do
    for k in 50 90
    do
	for cut in {0..7}
	do
	    root -l -q analysis500GeV.cc\($cut,\"$pol\",\"$k\"\)
	    mv bb_mc_hist.png  mc_study/bb_mc_cut${cut}_${pol}_K${k}.png
	    mv cc_mc_hist.png  mc_study/cc_mc_cut${cut}_${pol}_K${k}.png
	done
    done
done
