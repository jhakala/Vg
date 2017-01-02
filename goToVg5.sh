#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ $# -ne 1 ]
then
  echo "no mass supplied!"
  return 1
fi
cd /home/hakala/cmssw/CMSSW_7_1_5/src/Vg_5
modelNo=`echo ${PWD##*/} | sed 's/Vg_//g'`
masses=( `i="650"; while [ $i -lt 3226 ]; do echo $i; i=$[$i + 10]; done | xargs` )
mass=${masses[$1]}
eval `scramv1 runtime -sh`
echo source doBiasOneMassPoint.sh $mass $modelNo
source doBiasOneMassPoint.sh $mass $modelNo
