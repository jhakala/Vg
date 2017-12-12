from sys import argv
from os import path
from ROOT import *

if not len(argv) == 2:
  print "Please enter the input filename."
  exit(1)
if not path.exists(argv[1]): 
  print "Input file not found."
  exit(1)
category = "antibtag" if "antibtag" in argv[1] else "btag"

inFile = TFile(argv[1])
cans=[]
cans.append(("means" , inFile.Get("p2")))
cans.append(("medians" , inFile.Get("c2a")))

outFile = TFile("lineAdded_%s" % argv[1], "RECREATE")
topLines = []
bottomLines = []
rangeHi = 3600
rangeLow = 500
for can in cans:
  can[1].Draw()
  can[1].cd()
  topLines.append(TLine(rangeLow, 0.5, rangeHi, 0.5))
  bottomLines.append(TLine(rangeLow, -0.5, rangeHi, -0.5))
  topLines[-1].SetLineStyle(2)
  topLines[-1].Draw()
  bottomLines[-1].SetLineStyle(2)
  bottomLines[-1].Draw()
  print "drew lines on canvas", can[1].GetName()
  can[1].GetPrimitive("hframe").GetXaxis().SetRangeUser(rangeLow, rangeHi)
  can[1].GetPrimitive("hframe").GetYaxis().SetTitleOffset(1.2)
  can[1].Print("bias_%s_%s.pdf" % (can[0], category))

