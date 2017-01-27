#!/bin/bash
source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ $# -ne 1 ]
then
  echo "no mass supplied!"
else
  cd /home/hakala/cmssw/CMSSW_7_4_7/src/HgammaDebug/Vg/datacards_antibtag_exp1
  modelNo=`echo ${PWD##*/} | sed 's/Vg_//g'`
  masses=( `i="700"; while [ $i -lt 3250 ]; do echo $i; i=$[$i + 10]; done | xargs` )
  mass=${masses[$1]}
  eval `scramv1 runtime -sh`
  combine -M Asymptotic datacard_antibtag_exp1_${mass}.txt
fi
