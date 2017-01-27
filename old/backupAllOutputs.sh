#!/bin/bash

DATE=$(date +%h%d_%R)
BACKUPDIR="/home/hakala/VgCache/${DATE}"
mkdir $BACKUPDIR

mv datacards $BACKUPDIR
mv infos_antibtag $BACKUPDIR
mv infos_btag $BACKUPDIR
mv pdfs $BACKUPDIR
mv higgsCombineoutputs $BACKUPDIR
mv workspaces $BACKUPDIR
mv higgsCombineTests $BACKUPDIR
mv higgsCombineBiases $BACKUPDIR
mv comboLogs $BACKUPDIR
mv brazilianFlags $BACKUPDIR
mv mlfitoutputs $BACKUPDIR
mv condorLogs $BACKUPDIR
mv garbage $BACKUPDIR
./setupOutputCleaning.sh
