#!/bin/bash
mkdir DataCat
for pol in eL_pR #eR_pL
do
    for cat in catA #catB catC catD
    do
        for quality in Good #Medium Bad 
	do
	    #cuts=5
	    echo "sel:" $pol $cat $quality
	    root -l SelectCategory.cc\(\"$pol\",\"$quality\",\"$cat\"\) > log_catsel_${pol}_${cat}_bdt_${quality}
	    mv log_catsel* DataCat/.
	    #mv catsel* DataCat/${quality}_${pol}_${cat}.root	    
	done
    done
done
