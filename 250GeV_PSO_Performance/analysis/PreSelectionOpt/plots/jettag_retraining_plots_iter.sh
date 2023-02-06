mkdir testplots/
mkdir testplots/JetTagAnalysis/Retraining
for process in 2f250 vvH250 2q500
do
    for cut in {0..7}
    do
	root -l -q JetTag_Retraining.C\($cut,\"$process\",\"50\"\)
	mv c_eff_c.png testplots/JetTagAnalysis/Retraining/JetTag_c_vtx_${process}_Cut${cut}_Kgamma50.png	
	mv c_eff_b.png testplots/JetTagAnalysis/Retraining/JetTag_b_vtx_${process}_Cut${cut}_Kgamma50.png
    done
done
