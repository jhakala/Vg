from os import path, chmod, makedirs
from optparse import OptionParser
from modelNames import getGoodModelNames
from condorFactory import *
from getMasses import getMasses

def makeScript(dCardName, outDir, mass):
  incantation = "combine -M Asymptotic -m %i %s" % (mass, dCardName)
  pName = "asymp_%s" % dCardName
  pName = pName.replace(".txt","").replace("datacard_", "")
  scriptName = "%s/combine_%s.sh" % (outDir, pName)
  jdlName    = "%s/condor_%s.jdl" % (outDir, pName)
  script = open(scriptName, "w")
  script.write(simpleScript(incantation, "%s/%s" % (path.dirname(path.realpath(__file__)), outDir)))
  chmod(script.name, 0o777)
  jdl = open(jdlName, "w")
  jdl.write(simpleJdl(script.name.replace("%s/" % outDir, "")))
  logsDir = path.join(outDir, "condorLogs")
  if not path.exists(logsDir):
    makedirs(logsDir)
  
def buildOneDatacard(category, mass, fitModel, template, outDir):
  fitHTML = open("signalFits_%s/fit_%i.html" % (category, mass))
  for line in fitHTML:
    if "norm = " in line:
      norm = line.split()[2]
  outDcardName = "datacard_%s_%s_%i.txt" % (category, fitModel, mass)
  outDcard = open("%s/%s" % (outDir, outDcardName), "w")
  template.seek(0)
  for line in template:
    if "shapes signal" in line:
      outDcard.write(line.replace("w_signal_780", "../signalFits_%s/w_signal_%i" % (category, mass)))
    elif "shapes background" in line:
      outDcard.write(line.replace("cat-%s_model-bkg" % category , "../../HgammaFit/gof_saturated_%s/cat-%s_model-bkg" % (category, category)))
    elif "shapes data_obs" in line:
      outDcard.write(line.replace("w_data_%s" % category , "../w_data_%s" % category))
    elif "rate" in line:
      outDcard.write(line.replace("2.94084", norm))
    else:
      outDcard.write(line)
  return outDcardName
      
def buildCatForModel(category, fitmodel, makeScripts):
  if not category in ["btag", "antibtag"]:
    print "error: invalid model called for buildCatForModel"
  templateName = "../HgammaFit/gof_saturated_%s/datacard_%s_%s.txt" % (category, category, fitModel)
  template = open(templateName)
  outDirName   = "datacards_%s_%s" % (category, fitModel)
  if not path.exists(outDirName):
    makedirs(outDirName)
  
  for mass in getMasses():
    dCardName = buildOneDatacard(category, mass, fitModel, template, outDirName)
    if makeScripts:
      makeScript(dCardName, outDirName, mass)
     
def buildAllForModel(fitModel):
  cats = ["btag", "antibtag"]
  print "building model %s for categories:" % fitModel
  print cats
  for cat in cats:
    buildCatForModel("btag", fitModel)
  

if __name__ == "__main__":

  parser = OptionParser()
  parser.add_option("-f", "--fitModel", dest="fitModel",
                    help = "the name of the fit model to build a datacard for."                   )
  parser.add_option("-c", "--category", dest="category",
                    help = "the category: eithe 'btag' or 'antibtag'."                            )
  parser.add_option("-s", action="store_true", dest="makeScripts", default=False,
                    help = "toggle making condor scripts [default=False]."                        )
  (options, args) = parser.parse_args()
  
  if not options.category in ["antibtag", "btag", "all"]:
    print "error: invalid category"
    print "please pick 'btag', 'antibtag', or 'all' with the -c option."
    exit(1)
  elif options.category == "all":
    categories = ["btag", "antibtag"]
  else:
    categories = [options.category]

  if options.fitModel is None:
    print "please pick a fitModel, either one of the ones from HgammaFit or 'all'"
   
  print "doing categories: ",
  print categories

  for category in categories:
    if not options.fitModel == "all":
      fitModels = [options.fitModel]
    else:
      fitModels = getGoodModelNames(category)
    for fitModel in fitModels:
      buildCatForModel(category, fitModel, options.makeScripts)
        
  
  
  
  
    
