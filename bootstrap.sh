#!/bin/bash
pushd ../
git clone git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit -b v5.0.1
pushd HiggsAnalysis/CombinedLimit 
git remote add musella https://github.com/musella/HiggsAnalysis-CombinedLimit.git
git fetch musella slc6-root5.34.17:slc6-root5.34.17
git checkout slc6-root5.34.17
popd
git clone https://github.com/pandolf/diphotons.git
rm -rf diphotons/Analysis
rm -rf diphotons/FWLiteAlgos
rm -rf SCFootprintRemoval
rm -rf fullAnalysisRoma
git clone https://github.com/quittnat/flashggFinalFit.git -b topic-EXO-envelope-method
popd