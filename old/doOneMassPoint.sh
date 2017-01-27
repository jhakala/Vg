#!/bin/bash
cleanUp=0
rebin=10
debug=0
m=$1

models=(
    "env_pdf_0_13TeV_dijet2" "env_pdf_0_13TeV_exp1" "env_pdf_0_13TeV_expow1" "env_pdf_0_13TeV_pow1" "env_pdf_0_13TeV_lau1" "env_pdf_0_13TeV_atlas1" "env_pdf_0_13TeV_vvdijet1"
)


./buildInputs.sh $rebin $m 0
./buildDatacards.sh $m
./runLimits.sh $debug $m
