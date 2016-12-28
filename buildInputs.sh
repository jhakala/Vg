#!/bin/bash

postfix=(
    `cat inputs_to_process.txt`
)

rebin=$1
mass=$2
fitModel=$3

for name in ${postfix[@]}
do
    mkdir info_${mass}_${name}
    cp env_pdf_0_13TeV_atlas1_tmp.root info_${mass}_${name}
    cp w_data.root info_${mass}_${name}
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

