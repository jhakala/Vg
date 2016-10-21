#!/bin/bash

function show_help { 
    echo "./doLimits.sh [-c to clean up] -r [rebin] [-d debug combine]" 
}

#masses=(
#      1000
#)
#prepare for interpolation:
#masses=(
#    650 750 850 1000 1150 1300 1450 1600 1750 1900 2050 2450 2850 3250
#)
#masses=( 650 750 )
#masses=( `i="650"; while [ $i -lt 3251 ]; do echo $i; i=$[$i + 10]; done | xargs` )

#batch:
masses=( `echo $1` )

cleanUp=0
rebin=20
debug=0

while getopts "h?cr:d" opt; do
    case "$opt" in
    h|\?)
        show_help
        exit 0
        ;;
    r)
        rebin=$OPTARG
        ;;
    d) 
        debug=1
        ;;
    c)  cleanUp=1
        ;;
    esac
done

for m in ${masses[@]}
do
    if [ $cleanUp -eq 0 ]; then
        #BATCH:
        ./buildInputs.sh $rebin $m $2
        #prepare for interpolation
        #./buildInputs.sh $rebin $m $1
        ./buildDatacards.sh $m
        ./runLimits.sh $debug $m
    fi
    
    if [ $cleanUp -eq 1 ]; then
        ./cleanUp.sh $m
    fi
done
