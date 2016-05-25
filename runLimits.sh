#!/bin/bash

postfix=(
    `cat inputs_to_process.txt`
)

debug=$1
mass=$2


for name in ${postfix[@]}
do
    echo running asymptotic limits for $name
    dirName="info_${mass}_${name}"    
    dcardName="datacard_${mass}_${name}"
    logName="asymp_${mass}_${name}.log"

    pushd $dirName > /dev/null
    text2workspace.py ${dcardName}.txt -o ${dcardName}.root >& /dev/null
    #combine -M Asymptotic -m ${mass} ${dcardName}.txt -t -1 --rMax 2.0 -L libdiphotonsUtils | tee ${logName}
    combine -M Asymptotic -m ${mass} ${dcardName}.txt -L libdiphotonsUtils | tee ${logName}
    #combine -M HybridNew -H ProfileLikelihood -m ${mass} -t -1 --rMax=0.05 --frequentist --fork 8 ${dcardName}.txt -L libdiphotonsUtils | tee ${logName}
    if [ $debug -eq 1 ]; then
        mkdir -p sig
        #combine -M MaxLikelihoodFit -m ${mass} --robustFit=1 --rMin=-5 --rMax=5 -t -1 --plots --out sig ${dcardName}.txt -L libdiphotonsUtils | tee debug_${logName}
        combine -M MaxLikelihoodFit -m ${mass} --robustFit=1 --rMin=-5 --rMax=5 --plots --out sig ${dcardName}.txt -L libdiphotonsUtils | tee debug_${logName}
    fi
    popd > /dev/null
done

#combine -M Asymptotic -m ${mass} -t -1 --rMax 2.0 -L libdiphotonsUtils datacard_qqg_${mass}_combined.txt | tee asymp_${mass}_combo.log
combine -M Asymptotic -m ${mass} -L libdiphotonsUtils datacard_qqg_${mass}_combined.txt | tee asymp_${mass}_combo.log
#combine -M HybridNew -H ProfileLikelihood -m ${mass} -t -1 --rMax=0.05 --frequentist --fork 8 -L libdiphotonsUtils datacard_qqg_${mass}_combined.txt | tee asymp_${mass}_combo.log
