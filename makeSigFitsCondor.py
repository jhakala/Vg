from os import path, makedirs, chmod, getcwd
from condorFactory import simpleScript, queueJdl

condorDir = "sigFits_condor"
if not path.exists(condorDir):
  makedirs(condorDir)
logDir = path.join(condorDir, "condorLogs")
if not path.exists(logDir):
  makedirs(logDir)

for cat in ["antibtag", "btag"]:
  for fits in [["fullsim", 14], ["interpolated", 260]]:
    scriptName = "h_%s_sigFit_%s.sh" % (cat, fits[0])
    outScript = open(path.join(condorDir, scriptName), "w")
    incantation = "python makeSigFits.py -c %s -s %s -i $1" % (cat, fits[0])
    for line in simpleScript(incantation, getcwd()):
      outScript.write(line)
    chmod(outScript.name, 0o744)
    outJdl = open(path.join(condorDir, "c_%s_sigFit_%s.jdl") % (cat, fits[0]), "w")
    for line in queueJdl(scriptName, fits[1]):
      outJdl.write(line)
  
  
  
