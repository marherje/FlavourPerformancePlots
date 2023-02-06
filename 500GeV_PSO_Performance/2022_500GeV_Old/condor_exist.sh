#!/bin/bash

#eL_pR: 00015908, 00015920, 00015922, 00015928, 00015938, 00015942, 00015947, 00015951
#eR_pL: 00015930, 00015932, 00015934, 00015936, 00015954, 00015956, 00015958, 00015960
path=$PWD
path_lustre=/lustre/ific.uv.es/prj/ific/flc/ntuples-2022/Old

for prod in "eL_pR" "eR_pL"
do
    if [ "$prod" = "eL_pR" ]
    then
	for fprod in "00015908" "00015920" "00015922" "00015928" "00015938" "00015942" "00015947" "00015951"
	do
	    folder_name="/lustre/ific.uv.es/prj/ific/flc/500-TDR_ws/2f_Z_hadronic/ILD_l5_o1_v02/v02-02-03/"${fprod}"/000"
	    cd $folder_name
	    echo $folder_name
	    echo $fprod
	    
	    FILES=*
	    
	    i=0
	    for f in $FILES
	    do
		name="00"$i
		if [ $i -gt 9 ]; then
		    name="0"$i
		fi
		
		if [ $i -gt 99 ]; then
		    name=$i
		fi
		#if [ -f ${path}/${prod}_${name}.root ];
		if [ -f ${path}/${prod}_${fprod}_${name}.root ] || [ -f ${path_lustre}/${prod}_${fprod}_${name}.root ];
		then
		    echo "Skip "${name}
		else
		    cp ${path}/test_default.xml ${path}/test_${prod}_${fprod}_${name}.xml
		    sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/test_${prod}_${fprod}_${name}.xml
		    sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${fprod}_${name}.xml
		    sed -i -e 's/NFile/'${f}'/g' ${path}/test_${prod}_${fprod}_${name}.xml
		    sed -i -e 's/newFileN/'${name}'/g' ${path}/test_${prod}_${fprod}_${name}.xml
		    
		    cp ${path}/run_default.sh ${path}/run_${prod}_${fprod}_${name}.sh
		    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${fprod}_${name}.sh
		    sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/run_${prod}_${fprod}_${name}.sh
		    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${fprod}_${name}.sh
		    cp ${path}/run_default.sub ${path}/run_${prod}_${fprod}_${name}.sub
		    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${fprod}_${name}.sub
		    sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/run_${prod}_${fprod}_${name}.sub
		    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${fprod}_${name}.sub
		    
		    echo "Submit --- > " ${prod} ${fprod} ${name}   
		    cd -
		    condor_submit run_${prod}_${fprod}_${name}.sub
		    sleep 0.1s 
		    cd -
		fi    
		#rm ${path}/run_${prod}_${name}.sub
		#rm ${path}/run_${prod}_${name}.sh
		i=$((i+1))
	    done
	    cd -
	    mv ${path}/*${prod}*root ${path_lustre}/.
	done
    elif [ "$prod" = "eR_pL" ]
    then
	for fprod in "00015930" "00015932" "00015934" "00015936" "00015954" "00015956" "00015958" "00015960"
        do
            folder_name="/lustre/ific.uv.es/prj/ific/flc/500-TDR_ws/2f_Z_hadronic/ILD_l5_o1_v02/v02-02-03/"${fprod}"/000"
            cd $folder_name
            echo $folder_name
            echo $fprod

            FILES=*

            i=0
            for f in $FILES
            do
                name="00"$i
                if [ $i -gt 9 ]; then
                    name="0"$i
                fi

                if [ $i -gt 99 ]; then
                    name=$i
                fi
                #if [ -f ${path}/${prod}_${name}.root ];
                if [ -f ${path}/${prod}_${fprod}_${name}.root ] || [ -f ${path_lustre}/${prod}_${fprod}_${name}.root ];
		then
                    echo "Skip "${name}
                else
                    cp ${path}/test_default.xml ${path}/test_${prod}_${fprod}_${name}.xml
                    sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/test_${prod}_${fprod}_${name}.xml
                    sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${fprod}_${name}.xml
                    sed -i -e 's/NFile/'${f}'/g' ${path}/test_${prod}_${fprod}_${name}.xml
                    sed -i -e 's/newFileN/'${name}'/g' ${path}/test_${prod}_${fprod}_${name}.xml

                    cp ${path}/run_default.sh ${path}/run_${prod}_${fprod}_${name}.sh
                    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${fprod}_${name}.sh
                    sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/run_${prod}_${fprod}_${name}.sh
		    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${fprod}_${name}.sh
                    cp ${path}/run_default.sub ${path}/run_${prod}_${fprod}_${name}.sub
                    sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/run_${prod}_${fprod}_${name}.sub
		    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${fprod}_${name}.sub
                    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${fprod}_${name}.sub

                    echo "Submit --- > " ${prod} ${fprod} ${name}
                    cd -
                    condor_submit run_${prod}_${fprod}_${name}.sub
                    #sleep 0.1s                                                                                                                                                                          
                    cd -
                fi
                #rm ${path}/run_${prod}_${name}.sub                                                                                                                                                      
                #rm ${path}/run_${prod}_${name}.sh                                                                                                                                                       
                i=$((i+1))
            done
            cd -
	    mv ${path}/*${prod}*root ${path_lustre}/.
        done
    fi
done

for slp in 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m
do
    sleep ${slp}
    mv ${path}/*root ${path_lustre}/.
done
