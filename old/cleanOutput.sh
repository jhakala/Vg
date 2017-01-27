#!/bin/bash

TIME=$(date +%h-%d-%y_%H:%M)

DATACARDSDIR=datacards_${TIME}
ANTIBTAGINFOSDIR=infos_antibtag_${TIME}
BTAGINFOSDIR=infos_btag_${TIME}
PDFSDIR=pdfs_${TIME}
COMBINETESTDIR=higgsCombineTests_${TIME}
COMBINEOUTPUTSDIR=higgsCombineoutputs_${TIME}
COMBINEBIASDIR=higgsCombineBiases_${TIME}
WORKSPACESDIR=workspaces_${TIME}
COMBOLOGSDIR=comboLogs_${TIME}
BRAZILIANSDIR=brazilianFlags_${TIME}

mkdir datacards/${DATACARDSDIR}
mv datacard_qqg* datacards/${DATACARDSDIR}

mkdir infos_antibtag/${ANTIBTAGINFOSDIR}
mv info_*_antibtag infos_antibtag/${ANTIBTAGINFOSDIR}

mkdir infos_btag/${BTAGINFOSDIR}
mv info_*_btag infos_btag/${BTAGINFOSDIR}

mkdir pdfs/${PDFSDIR}
mv *.pdf pdfs/${PDFSDIR}

mkdir higgsCombineoutputs/${COMBINEOUTPUTSDIR}
mv higgsCombineoutput*.root higgsCombineoutputs/${COMBINEOUTPUTSDIR}

mkdir workspaces/${WORKSPACESDIR}
mv roostats-*.root workspaces/${WORKSPACESDIR}

mkdir higgsCombineTests/${COMBINETESTDIR}
mv higgsCombineTest.Asymptotic.*.root higgsCombineTests/${COMBINETESTDIR}

mkdir higgsCombineBiases/${COMBINEBIASDIR}
mv higgsCombinebiasTest.GenerateOnly.*.root higgsCombineBiases/${COMBINEBIASDIR}

mkdir comboLogs/${COMBOLOGSDIR}
mv asymp_*_combo.log comboLogs/${COMBOLOGSDIR}

mkdir brazilianFlags/brazilianFlags_${TIME}
mv brazilianFlag_*.root brazilianFlags/brazilianFlags_${TIME}

mkdir mlfitoutputs/mlfitoutputs_${TIME}
mv mlfitoutput*.root mlfitoutputs/mlfitoutputs_${TIME}
