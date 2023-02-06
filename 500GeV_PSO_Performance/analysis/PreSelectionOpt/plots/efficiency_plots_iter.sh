#mkdir testplots/
#mkdir mc_study/
#mkdir testplots/FinalCutAnalysis/
mkdir testplots/StatsUsingOldWeights/
for pol in eL_pR eR_pL
do
    #mkdir testplots/${pol}/
    #mkdir mc_study/${pol}/
    #mkdir testplots/FinalCutAnalysis/${pol}/
    for k in 50 #10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160 170 180 190 200
    do
	for cut in {0..9}
	do
	    #mkdir testplots/${pol}/${k}/
	    #mkdir mc_study/${pol}/${k}
	    mkdir testplots/StatsUsingOldWeights/${pol}/
	    root -l -q analysis500GeV.cc\($cut,\"$pol\",\"$k\"\) > st\
ats_cut${cut}_Kgamma${k}.txt
            mv stats* testplots/StatsUsingOldWeights/${pol}/.

	    mv hist.png testplots/StatsUsingOldWeights/${pol}/.

            #mv hist.png testplots/FinalCutAnalysis/${pol}/efficiency_cut${cut}_${pol}_kgamma${k}.png
	    
	    #mv hist.png testplots/${pol}/${k}/cut${cut}.png	    
	    #mv bb_mc_hist.png  mc_study/${pol}/${k}/bb_mc_cut${cut}_${pol}_K${k}.png
	    #mv cc_mc_hist.png  mc_study/${pol}/${k}/cc_mc_cut${cut}_${pol}_K${k}.png
	    #mv bb_mc_com_hist.png  mc_study/${pol}/${k}/bb_mc_com_cut${cut}_${pol}_K${k}.png
	    #mv cc_mc_com_hist.png  mc_study/${pol}/${k}/cc_mc_com_cut${cut}_${pol}_K${k}.png
	done
    done
done
