mkdir output/
for pol in eL_pR eR_pL 
do
    for gamma in 0
    do
	for erre in 100
	do  
	    for k in 10 #30 50 70 90 110 130 150 170 190 210
	    do
		for process in 6f_ttbar_yycyyc_ 6f_ttbar_yycyyu_ 6f_ttbar_yyuyyc_ 6f_ttbar_yyuyyu_ 4f_ZZ_hadronic_ 4f_WW_hadronic_ 2f_hadronic_sample_ 
		do    
		    for cuts in {8..9}
		    do
			if [ $process == 2f_hadronic_sample_ ]
			then
			    #cuts=5
			    echo $cuts
			    root -l test_selection_background_new.cc\($gamma,$erre,\"$pol\",$cuts,$k,\"$process\",0\) > log_sel_bkg_${k}_eL_genkt_restorer_cuts${cuts}
			    mv log_sel* output/
			    mv selection*root output/
			else
			    #cuts=5
			    echo $cuts
			    root -l test_selection_background_new.cc\($gamma,$erre,\"$pol\",$cuts,$k,\"$process\",1\) > log_sel_bkg_${k}_eL_genkt_restorer_cuts${cuts}
			    mv log_sel* output/
			    mv selection*root output/
			fi
		    done
		done
	    done
	done
    done
done
