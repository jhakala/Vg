#!/bin/bash

function show_help { 
    echo "./doLimits.sh [-c to clean up] -r [rebin] [-d debug combine]" 
}

masses=(
    750 1000 2000 3000
)
cleanUp=0
rebin=10
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
        ./buildInputs.sh $rebin $m 4
        ./buildDatacards.sh $m
        ./runLimits.sh $debug $m
    fi
    
    if [ $cleanUp -eq 1 ]; then
        ./cleanUp.sh $m
    fi
done
