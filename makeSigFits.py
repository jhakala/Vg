import os
from subprocess import Popen
import shlex
from optparse import OptionParser
parser = OptionParser()
parser.add_option("-c", "--category"  ,       dest="category",
                  help = "either 'btag' or 'antibtag'"                                          )
(options, args) = parser.parse_args()

if not options.category in ["antibtag", "btag"]:
  print "invalid category given, must be either 'btag' or 'antibtag'."
  exit(1)

cmsenv = os.environ

masses = []
mass = 700
while mass <= 3250:
  masses.append(mass)
  incantation = shlex.split("root -x -b -l -q 'Display_SignalFits.cc(\"%s\",\"../fitFilesBtagSF/\",\"\",\"histos_flatTuple_m\",%i,1)'" % (options.category, mass))
  print incantation
  Popen(incantation, env=cmsenv)
  mass += 10
