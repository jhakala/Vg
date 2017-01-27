from os import path, makedirs
from optparse import OptionParser

def buildOneDatacard(category, mass, fitModel, template, outDir):
  fitHTML = open("signalFits_%s/fit_%i.html" % (category, mass))
  for line in fitHTML:
    if "norm = " in line:
      norm = line.split()[2]

  outDcard = open("%s/datacard_%s_%s_%i.txt" % (outDir, category, fitModel, mass), "w")
  template.seek(0)
  for line in template:
    if "shapes signal" in line:
      outDcard.write(line.replace("w_signal_780", "../signalFits_%s/w_signal_%i" % (category, mass)))
    elif "shapes background" in line:
      outDcard.write(line.replace("cat-%s_model-bkg" % category , "../../HgammaFit/gofCondor/cat-%s_model-bkg" % category))
    elif "shapes data_obs" in line:
      outDcard.write(line.replace("w_data_%s" % category , "../w_data_%s" % category))
    elif "rate" in line:
      outDcard.write(line.replace("2.94084", norm))
    else:
      outDcard.write(line)
      
     
  

if __name__ == "__main__":

  parser = OptionParser()
  parser.add_option("-f", "--fitModel", dest="fitModel",
                    help = "the name of the fit model to build a datacard for."                   )
  parser.add_option("-c", "--category", dest="category",
                    help = "the category: eithe 'btag' or 'antibtag'."                            )
  (options, args) = parser.parse_args()
  
  if not options.category in ["antibtag", "btag"]:
    "error: invalid category"
    exit(1)
  
  
  templateName = "../HgammaFit/gofCondor/datacard_%s_bkg_%s.txt" % (options.category, options.fitModel)
  template = open(templateName)
  outDirName   = "datacards_%s_%s" % (options.category, options.fitModel)
  if not path.exists(outDirName):
    makedirs(outDirName)
  
  masses=[]
  mass = 710
  while mass <=3250:
    masses.append(mass)
    buildOneDatacard(options.category, mass, options.fitModel, template, outDirName)
    mass+=10
  
  
    
