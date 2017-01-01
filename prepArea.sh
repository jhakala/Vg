#!/bin/bash
####
# Script for running the area prepping script to get background and/or alternative background pdfs
# John Hakala, 12/30/2016
####
if [ "$#" -ne "2" ]; then
  echo "you must supply two arguments to this script:"
  echo "the first is either 'btag',  'antibtag', or 'both'"
  echo "the second is either 'limit' or 'bias'"
  echo "example:"
  echo "./prepArea.sh btag limit"
  exit 1
fi
BIASMODELINDEX="1"
CATEGORY=$1
DATE=`date +%F`
IVGDIR=`echo -n $PWD | sed 's/ //g' | tail -c 1`
PYSCRIPT="getBkgFromFtest.py"
SHOWPYHELP="YES"
if [ "$1" == "btag" ]; then echo -e " \n\n >>> ----- prepping area for BTAG category -----"
elif [ "$1" == "antibtag" ]; then echo -e "\n\n >>> ----- prepping area for ANTIBTAG category -----"
else 
  echo "Something is wrong with the first argument! It should be either 'antibtag' or 'btag'."
  exit 1
fi;
CMD=$(echo python ${PYSCRIPT} -o ${DATE} -c ${CATEGORY} -n ${IVGDIR} -l -d -b)
if [ "$2" == "limit" ]; then
  echo -e " >>> the preparation being done is for calculating LIMITS\n\n"
elif [ "$2" == "bias" ]; then
  echo -e " >>> the preparation being done is for performing BIAS STUDIES\n\n"
  CMD=$(echo $CMD -a $BIASMODELINDEX)
else
  echo "Something is wrong with the second argument! It should be either 'limit' or 'bias'."
  exit 1
fi

echo -e "\n\n >>> ----- running the command: -----"
echo -e " >>>     $CMD"
if [ "$SHOWPYHELP" == "YES" ]; then
  echo " >>> see below for an explanation of these options: "
  python $PYSCRIPT --help
fi
echo -e " >>> -------------------------------- \n\n"
$CMD


echo -e " \n\n >>> ----- done prepping the area! ----- \n\n"
