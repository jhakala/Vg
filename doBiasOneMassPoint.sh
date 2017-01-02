#!/bin/bash
cleanUp=0
rebin=1

debug=0
nToys=500
m=$1
#model=$2

postfix=(
    `cat inputs_to_process.txt`
)

#models=(
#    "env_pdf_0_13TeV_dijet2" "env_pdf_0_13TeV_exp1"  "env_pdf_0_13TeV_expow1" "env_pdf_0_13TeV_expow2" "env_pdf_0_13TeV_pow1" "env_pdf_0_13TeV_lau1" "env_pdf_0_13TeV_atlas1" "env_pdf_0_13TeV_atlas2" "env_pdf_0_13TeV_vvdijet1"
#)
#models=(
#    "env_pdf_0_13TeV_dijet2" "env_pdf_0_13TeV_exp1"  "env_pdf_0_13TeV_expow1" "env_pdf_0_13TeV_pow1" "env_pdf_0_13TeV_lau1" "env_pdf_0_13TeV_atlas1" "env_pdf_0_13TeV_atlas2" "env_pdf_0_13TeV_vvdijet1"
#)

seeds=123321


./buildInputs.sh $rebin $m bias
./buildDatacards_alt.sh $m
./buildDatacards.sh $m

##echo "datacard_qqg_${m}_combined_alt.txt"
for name in ${postfix[@]}
do
    echo building datacard for $name
    dirName="info_${m}_${name}"
    dcardName="datacard_${m}_${name}.txt"
    dcardNameAlt="datacard_${m}_${name}_alt.txt"
    combine ${dirName}/${dcardNameAlt} -M GenerateOnly -m $m -t $nToys  --saveToys -s $seeds --expectSignal=0.0 -n biasTest
    combine ${dirName}/${dcardName} -M MaxLikelihoodFit -m $m --expectSignal=0.0  --rMin=-100000 --rMax=100000 -t $nToys --toysFile=higgsCombinebiasTest.GenerateOnly.mH${m}.${seeds}.root -s $seeds -n output${m}_${name}
    seeds=123321
done

combine datacard_qqg_${m}_combined_alt.txt -M GenerateOnly -m $m -t $nToys  --saveToys -s 123321 --expectSignal=0.0 -n biasTest 
#combine datacard_qqg_${m}_combined_alt.txt -M GenerateOnly -m $m -t $nToys  --saveToys -s 123321 --expectSignal=0.0 -n biasTest 

#combine datacard_qqg_${m}_combined.txt -M MaxLikelihoodFit -m $m --expectSignal=0.0 --rMin=-10000 --rMax=10000 -t $nToys --toysFile=higgsCombinebiasTest.GenerateOnly.mH${m}.123321.root -s 123321 --toysFrequentist --noErrors --minos none -n output${m} --saveShapes --saveWithUncertainties --out plotDir_new --plots
combine datacard_qqg_${m}_combined.txt -M MaxLikelihoodFit -m $m --expectSignal=0.0 --rMin=-10000 --rMax=10000 -t $nToys --toysFile=higgsCombinebiasTest.GenerateOnly.mH${m}.123321.root -s 123321 --toysFrequentist --noErrors --minos none -n output${m} 

#combine datacard_qqg_${m}_combined.txt -M MaxLikelihoodFit -m $m --expectSignal=0.0 --rMin=-10000 --rMax=10000 -t $nToys --toysFile=higgsCombinebiasTest.GenerateOnly.mH${m}.123321.root -s 123321 --toysFrequentist --noErrors --minos none -n output${m}

