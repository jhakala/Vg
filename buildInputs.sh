#!/bin/bash

postfix=(
    `cat inputs_to_process.txt`
)

rebin=$1
mass=$2
fitModel=$3

for name in ${postfix[@]}
do
    ./prepArea.sh ${name}
    mkdir info_${mass}_${name}
    ln -s ../bg_antibtag.root info_${mass}_${name}/bg_antibtag.root
    echo "FROM $PWD"
    ln -s ../../dataFiles/w_data_${name}.root info_${mass}_${name}/w_data_${name}.root
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

