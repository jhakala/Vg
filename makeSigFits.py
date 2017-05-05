import os
from time import sleep
from subprocess import Popen
import shlex
from optparse import OptionParser
from getMasses import getMasses
parser = OptionParser()
parser.add_option("-c", "--category"  ,       dest="category",
                  help = "either 'btag' or 'antibtag'"              )
parser.add_option("-s", "--step"  ,       dest="step",
                  help = "either 'fullsim' or 'interpolated'"       )
(options, args) = parser.parse_args()

if not options.category in ["antibtag", "btag"]:
  print "invalid category given, must be either 'btag' or 'antibtag'."
  exit(1)

cmsenv = os.environ

dirName = "signalFits_%s_%s" % (options.category, options.step)
if not os.path.exists(dirName):
  os.makedirs(dirName)
masses = []
inputDir = ""
if options.step == "interpolated":
  masses=getMasses("all")
  inputDir = "GenSignal"
elif options.step == "fullsim":
  masses=getMasses("fullsim")
  inputDir = "../../btagselection"
else:
  print "please use the -s option and pick step 'interpolated' or 'fullsim'"
  exit(1)
for mass in masses:
  incantation = shlex.split("root -x -b -l -q 'Display_SignalFits.cc(\"%s\",\"%s\",\"\",\"histos_sig_m\",%i,1,%s)'" % 
                             (options.category, inputDir, mass, '"'+dirName+'"')
                           )
  print incantation
  Popen(incantation, env=cmsenv)
  sleep(0.3)
  
  mass += 10
