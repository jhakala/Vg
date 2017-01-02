#!/bin/bash

postfix=(
    `cat inputs_to_process.txt`
)

rebin=$1
mass=$2
proc=$3

for name in ${postfix[@]}
do
    ./prepArea.sh ${name} ${proc}
    mkdir info_${mass}_${name}
    rm -f info_${mass}_${name}/bg_${name}.root
    ln -s /home/hakala/cmssw/CMSSW_7_1_5/src/Vg_1/bg_${name}.root info_${mass}_${name}/bg_${name}.root
    if [ "$proc" == "bias" ]; then
      rm -f info_780_${name}/bg_alt_${name}.root
      ln -s /home/hakala/cmssw/CMSSW_7_1_5/src/Vg_1/bg_alt_${name}.root info_${mass}_${name}/bg_alt_${name}.root
    fi
    echo "FROM $PWD"
    echo cp ../dataFiles/w_data_${name}.root info_${mass}_${name}/w_data_${name}.root
    rm -f info_780_${name}/w_data_${name}.root
    ln -s /home/hakala/cmssw/CMSSW_7_1_5/src/dataFiles/w_data_${name}.root info_${mass}_${name}/w_data_${name}.root
    echo $name
    echo
    echo "root -x -b -l -q Display_SignalFits.cc\(\"${name}\"\,\"../fitFilesBtagSF/\",\"\",\"histos_flatTuple_m\",${mass},${rebin}\) > info_${mass}_${name}/signal${mass}_${name}_sig.log"
    echo
    root -x -b -l -q Display_SignalFits.cc\(\"${name}\"\,\"../fitFilesBtagSF/\",\"\",\"histos_flatTuple_m\",${mass},${rebin}\) > info_${mass}_${name}/signal${mass}_${name}_sig.log
    echo
    #echo "root -x -b -l -q BackgroundPrediction.c\(\"${name}\",${rebin},${fitModel},${mass}\) > info_${mass}_${name}/data_${name}_bkg.log"
    echo
    #root -x -b -l -q BackgroundPrediction.c\(\"${name}\",${rebin},${fitModel},${mass}\) > info_${mass}_${name}/data_${name}_bkg.log
    #root -x -b -l -q BackgroundPrediction.c\(\"${name}\",${rebin},${fitModel},${mass}\) > info_${mass}_${name}/data_${name}_bkg.log 
done

