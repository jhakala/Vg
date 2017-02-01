from os import path, chmod, makedirs
from optparse import OptionParser
from modelNames import getGoodModelNames
from condorFactory import *
from getMasses import getMasses
from condorFactory import *


def makeToysScripts(model, nToys, seed, category):
  print "making toys scripts for %s model" % model
  outDir = "toys_%s" % category
  if not path.exists(outDir):
    makedirs(outDir)
  #toysName = "cat-%s_mod-%s_n-%i_seed_%i.root" % (category, model, nToys, seed)
  
  dcardDir = "datacards_%s_%s" % (category, model)
  pName     =  "%s_%s_1010.txt" % (category, model)
  dcardName =  "datacard_%s" % pName
  
  incantation = "combine %s -M GenerateOnly -m 1337 -t %i  --saveToys -s %i --expectSignal=0.0 -n BiasTest_%s_%s" % (
    path.join(path.dirname(path.realpath(__file__)), dcardDir, dcardName), 
    nToys, 
    seed, 
    category, 
    model
  )
  scriptName = path.join(outDir, "toys_%s.sh"    % pName)
  jdlName    = path.join(outDir, "condor_%s.jdl" % pName)
  script = open(scriptName, "w")
  script.write(simpleScript(incantation, path.join(path.dirname(path.realpath(__file__)), outDir)))
  chmod(script.name, 0o777)
  jdl = open(jdlName, "w")
  jdl.write(simpleJdl(script.name.replace("%s/" % outDir, "")))
  logsDir = path.join(outDir, "condorLogs")
  if not path.exists(logsDir):
    makedirs(logsDir)
  print "finished making toys scripts for %s model." % model
  print "script is:     %s" % script.name
  print "condor jdl is: %s" % jdl.name

def makeBiasScripts(model, alternative, category, nToys):
  #combine datacard_qqg_${m}_combined.txt -M MaxLikelihoodFit -m $m --expectSignal=0.0 --rMin=-10000 --rMax=10000 -t $nToys --toysFile=higgsCombinebiasTest.GenerateOnly.mH${m}.123321.root -s 123321 --toysFrequentist --noErrors --minos none -n output${m} 
 #higgsCombineBiasTest_antibtag_bkg_exp1.GenerateOnly.mH1337.501337.root
  print "making bias scripts for %s model versus alternative model %s" % (model, alternative)
  outDir = "bias_%s_nom-%s_alt-%s" % (category, model, alternative)
  if not path.exists(outDir):
    makedirs(outDir)
  dcardDir = "datacards_%s_%s" % (category, model)
  toysName = "higgsCombineBiasTest_%s_%s.GenerateOnly.mH1337.501337.root" % (category, alternative)
  print "masses:" 
  print getMasses()
  for mass in getMasses():
    print "working on scripts for mass %i" % mass
    pName    = "%s_%s_%s.txt" % (category, model, mass)
    dcardName = "datacard_%s" % pName
    incantation = "combine %s -M MaxLikelihoodFit -m %i --expectSignal=0.0 --rMin=-10000 --rMax=10000 -t %i --toysFile=%s --minos none -n biasStudy-%i" % (
      path.join(path.dirname(path.realpath(__file__)), dcardDir, dcardName), 
      mass, 
      nToys,
      path.join(path.dirname(path.realpath(__file__)), "toys_%s" % category, toysName),
      mass
    )
    scriptName = path.join(outDir, "bias_%s.sh"    % pName)
    jdlName    = path.join(outDir, "condor_%s.jdl" % pName)
    script = open(scriptName, "w")
    script.write(simpleScript(incantation, path.join(path.dirname(path.realpath(__file__)), outDir)))
    chmod(script.name, 0o777)
    jdl = open(jdlName, "w")
    jdl.write(simpleJdl(script.name.replace("%s/" % outDir, "")))
    logsDir = path.join(outDir, "condorLogs")
    if not path.exists(logsDir):
      makedirs(logsDir)
    print "finished making bias studies scripts for %s model vs. %s alternative." % (model, alternative)
    print "script is:     %s" % script.name
    print "condor jdl is: %s" % jdl.name
  

if __name__=="__main__":
  parser = OptionParser()
  parser.add_option("-n", "--nominalModel"   ,  dest="nominalModel"                     ,
                    help = "the name of the nominal model"                              )
  parser.add_option("-a", "--alternateModel" ,  dest="alternateModel"                   ,
                    help = "the name of the alternate model"                            )
  parser.add_option("-c", "--category"       ,  dest="category"                         , 
                    help = "the category to perform the bias study on"                  )
  parser.add_option("-t", "--nToys"          ,  dest="nToys", type="int"                , 
                    help = "the number of toys to be generated"                         )
  parser.add_option("-s", "--seed"           ,  dest="seed",  type="int"                ,
                    help = "the random number seed",  default = 501337                  )
  parser.add_option("-g", action="store_true",  dest="makeToys",          default=False ,
                    help = "toggle making toys [default=False]"                         )
  parser.add_option("-x", action="store_true",  dest="makeBiasScripts",   default=False ,
                    help = "toggle making bias study scripts [default=False]"           )
  (options, args) = parser.parse_args()


  if options.category == "all":
    categories = ["antibtag", "btag"]
  elif options.category in ["antibtag", "btag"]:
    categories = [options.category]
  else:
    print "invalid category given with -c option or not specified, must be either 'antibtag' or 'btag'"
    exit(1)
  if options.nToys <= 0 or options.nToys is None:
    print "must supply the number of toys with the -t option"
    exit(1)


  for category in categories: 
    if options.makeToys:
      if options.nToys is not None and options.nToys <= 0:
        print "invalid number of toys given with -t: %i" % options.nToys
      elif options.nToys > 0:
        if options.alternateModel is None:
          print "alternate model must be given with -a for generating toys."
        elif options.alternateModel == "all":
          for model in getGoodModelNames(category):
            makeToysScripts(model, options.nToys, options.seed, category)
        elif options.alternateModel not in getGoodModelNames(category):
          print "alternate model not valid. options for %s category are:" % category
          print getGoodModelNames(category)
        else:
          makeToysScripts(options.alternateModel, options.nToys, options.seed, category)

    if options.makeBiasScripts: 
      if options.nominalModel is None:
        print "nominal model must be given with -n for making bias scripts."
      elif options.nominalModel not in getGoodModelNames(category):
        print "nominal model not valid. options for %s category are:" % category
        print getGoodModelNames(category)
      if options.alternateModel is None:
        print "alternate model must be given with -n for making bias scripts."
      elif options.alternateModel not in getGoodModelNames(category):
        print "alternate model not valid. options for %s category are:" % category
        print getGoodModelNames(category)
      else:
        makeBiasScripts(options.nominalModel, options.alternateModel , category, options.nToys)
        
    
