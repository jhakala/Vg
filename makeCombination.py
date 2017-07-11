from os import path, chmod, makedirs, environ
from optparse import OptionParser
from modelNames import getGoodModelNames
from getMasses import getMasses
from condorFactory import *
from subprocess import Popen, PIPE
import shlex
from makeDatacards import makeScript

def getDir(category, model):
  return "datacards_%s_%s" % (category, model)

def getModelsKey(antibtagModel, btagModel):
  return "a-%s_b-%s" % (antibtagModel.replace("bkg_",""), btagModel.replace("bkg_",""))

def makeCardsAndScripts(antibtagModel, btagModel, makeCards, makeScripts):
  outDirName = "datacards_combined_%s" % getModelsKey(antibtagModel, btagModel)
  if not path.exists(outDirName):
    makedirs(outDirName)

  cmsenv = environ
  processes = []
  outfiles  = []
  antibtagDir = getDir("antibtag" ,  antibtagModel )
  btagDir     = getDir("btag"     ,  btagModel     )
  for mass in getMasses():
    antibtagCardName = "datacard_antibtag_%s_%i.txt" % (antibtagModel , mass)
    btagCardName     = "datacard_btag_%s_%i.txt"     % (btagModel     , mass)
    combineCardName  = "datacard_combined_%s_%i.txt" % (getModelsKey(antibtagModel, btagModel), mass)

    if makeCards:
      print "Making combined category datacards"
      incantation = "combineCards.py %s %s" % (
                      path.join(antibtagDir ,  antibtagCardName) ,
                      path.join(btagDir     ,  btagCardName    ) ,
                    )
      print incantation
      processes.append(Popen(shlex.split(incantation), env=cmsenv, stdout=PIPE, stderr=PIPE))
      outfiles.append(open(path.join(outDirName, combineCardName), "w"))
      for line in processes[-1].stdout:
        # combine has a bug: this will print something like
        # shapes data_obs    ch2         datacards_btag_bkg_vvdijet2/../w_data_btag.root Vg:data_obs for the shapes lines.... ugh
        if "shapes" in line:
          outfiles[-1].write(line.replace("datacards_antibtag_%s/" % antibtagModel, "").replace("datacards_btag_%s/" % btagModel, ""))
        else:
          outfiles[-1].write(line)
      processes[-1].wait()
    if makeScripts:
      print "Making condor scripts"
      makeScript(combineCardName, outDirName, mass)
      

if __name__ == "__main__":
  parser = OptionParser()
  parser.add_option("-c", action="store_true", dest="makeCards"  , default=False,
                    help = "toggle making the combined datacards [default=False]" )
  parser.add_option("-s", action="store_true", dest="makeScripts", default=False,
                    help = "toggle making the condor scripts [default=False]"     )
  parser.add_option("-a", "--antibtagModel", dest="antibtagModel", type="string",
                    help = "model name for antibtag fit [ex: bkg_dijetsimple2]"                         )
  parser.add_option("-b", "--btagModel", dest="btagModel"        , type="string", 
                    help = "model name for btag fit [ex: bkg_dijetsimple2]"                             )
  (options, args) = parser.parse_args()                 
  
  if not options.makeCards and not options.makeScripts:
    print "neither making cards nor making scripts, that means this script does nothing."
    exit(2)

  makeCardsAndScripts(options.antibtagModel, options.btagModel, options.makeCards, options.makeScripts)
