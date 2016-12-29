#!/bin/bash

postfix=(
    `cat inputs_to_process.txt`
)

mass=$1
echo "0.12+${mass}*0.07*0.001" | bc -l
btagSys=$(bc <<< "scale=3;1+0.12+${mass}*0.07*0.001")
echo $btagSys
antibtagSys=$(bc <<< "scale=3;1/${btagSys}")
echo $antibtagSys
cards=""
for name in ${postfix[@]}
do
    echo building datacard for $name
    dirName="info_${mass}_${name}"
    dcardName="datacard_${mass}_${name}.txt"
    #bgLogName="data_${name}_bkg.log"
    sig_norm=`grep 'norm =' ${dirName}/index.html | awk '{print $3}'`    
    #bkg_norm=`grep ' Background number of events = ' ${dirName}/${bgLogName} | awk '{print $6}'`
    
    #let's build a datacard!
    cat > ${dirName}/${dcardName} <<EOF
imax 1 number of channels
jmax * number of backgrounds
kmax * number of systematic uncertainty sources
----------
shapes signal     Vg w_signal_${mass}.root      Vg:signal_fixed_${name}
shapes background Vg bg_${name}.root            Vg:bg_${name}
shapes data_obs   Vg w_data_${name}.root        Vg:data_obs
----------
## Observation
bin                     Vg
observation             -1
----------
bin                   Vg          Vg
process               signal      background
process               0           1
rate                  ${sig_norm} 1
cms_lumi_13TeV  lnN   1.027       -     
cms_btag_sf_13TeV       lnN              ${btagSys}       -         
cms_btag_sf_13TeV       lnN              ${antibtagSys}         -
cms_JES_13TeV           lnN              1.02        -         
cms_phoHLT_13TeV        lnN              1.02        -         
cms_pho_sf_13TeV        lnN              1.05        -         
cms_pileup_13TeV        lnN              1.01        -         
cms_xzg_pdf_13TeV       lnN              1.02        -         
cms_xzg_scale_13TeV     lnN              1.05        -        
EOF

    
    #now add the systematics to the card
    #grep 'signal_' ${dirName}/index.html | awk '{print $1 " " $2 " " $3 " " $4}' >>  ${dirName}/${dcardName}
    #grep 'bias_term_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
    #grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}
    if [[ $dcardName == *"anti"* ]]
    then
        if [[ ${mass} -gt 3300 ]] 
	then
           grep 'bias_term_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
	fi
	sed -i 's/WHATKIND/Anti/' ${dirName}/${dcardName}
	sed -i '/cms_btag_sf_13TeV.*'${btagSys}'.*/d' ${dirName}/${dcardName}
	#grep 'bg_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
    else
        if [[ ${mass} -gt 3800 ]]
        then
           grep 'bias_term_' ${dirName}/${bgLogName} | grep ' param ' >> ${dirName}/${dcardName}
        fi
	sed -i 's/WHATKIND//' ${dirName}/${dcardName}
	sed -i '/cms_btag_sf_13TeV.*'${antibtagSys}'.*/d' ${dirName}/${dcardName}
        #grep 'bg_' ${dirName}/${bgLogName} | grep 'param' >> ${dirName}/${dcardName}
    fi

    cards+="${dirName}/${dcardName} "
done

combineCards.py -S $cards > datacard_qqg_${mass}_combined.txt

