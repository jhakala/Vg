	#!/bin/bash

	function usage() {
	    echo "sh SubmitCMSSW.sh <massMin> <massMax> <stepSize> <model[0_9]>"
	    exit;
    }

	if [ ! -n "$1" ] || [ ! -n "$2" ]  || [ ! -n "$3" ] || [ ! -n "$4" ] ; then usage; fi;

    model=$4
    JOB=1
    for i in `seq $1 $3 $2`;
    do

    mass=$i
    fileSi=../fitFilesBtagSF/btag/histos_signal-${mass}.root
    if [ -a "$fileSi" ]
    then
	./doOneMassPoint.sh ${mass} ${model}
    fi
    JOB=`expr $JOB + 1`

    done


