from os import path, makedirs, chmod
from getMasses import getMasses
from condorFactory import *
from pprint import pprint

def getFullsimMCs():
  return getMasses("fullsim")

def getOmittedMCs():
  return [850, 1150, 1450, 1750, 2050, 2850]

if __name__ == "__main__":
  for cat in ["antibtag", "btag"]:
    masses = getFullsimMCs() 
    for omit in getOmittedMCs():
      masses.remove(omit) 
    print masses
    massRanges = []
    incantations = []
    for iRange in range(0, len(masses)-1):
      massRanges.append([masses[iRange], masses[iRange+1]])
      incantations.append('root -l -b -q \'InterpolateSignal.C("%s", %.1f, %.1f, "ClosureInterps/")\''% (cat, massRanges[-1][0], massRanges[-1][1]))
    pprint(incantations)
    
    condorDir = "interpClosure_condor"
    if not path.exists(condorDir):
      makedirs(condorDir)
    for iSetup in range(0, len(incantations)):
      jdl = open(path.join(condorDir, "c_%s_interp%.1f-%.1f.jdl"%(cat, massRanges[iSetup][0], massRanges[iSetup][1])), "w")
      script = open(path.join(condorDir, "h_%s_interp%.1f-%.1f.sh"%(cat, massRanges[iSetup][0], massRanges[iSetup][1])), "w")
      jdl.write(simpleJdl(path.basename(script.name)))
      script.write(simpleScript(incantations[iSetup], "/home/hakala/cmssw/CMSSW_7_4_7/src/HgammaDebug/Vg"))
      jdl.close()
      script.close()
      chmod(script.name, 0o744)
