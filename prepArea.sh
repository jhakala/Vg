#!/bin/bash
CATEGORY=$1
DATE=`date +%F`
IVGDIR=`echo -n $PWD | sed 's/ //g' | tail -c 1`
python getBkgFromFtest.py -o ${DATE} -c ${CATEGORY} -n ${IVGDIR} -l -d -b
