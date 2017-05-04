from ROOT import *

biasPlotFileNames = ["biasPlot_antibtag_dijet2.root", "biasPlot_btag_dijet2.root"]

for biasPlotFileName in biasPlotFileNames:
  outFileName = "lineAdded_%s" % biasPlotFileName

  biasPlotFile = TFile(biasPlotFileName)
  biasPlotFile.ls()
  
  cans = []
  lines = []
  for canKey in biasPlotFile.GetListOfKeys():
    if biasPlotFile.Get(canKey.GetName()).IsA().GetName():
      print canKey.GetName()
      cans.append(biasPlotFile.Get(canKey.GetName()))

  for can in cans:
    can.cd()
    can.Draw()
    print "looking at can %s" % can.GetName()
    for prim in can.GetListOfPrimitives():
      print "can %s has primitive %s with type %s" % (can.GetName(), prim.GetName(), prim.IsA().GetName())
      if "TH1F" in prim.IsA().GetName():
        lowEdge = prim.GetXaxis().GetBinLowEdge(1)
        upEdge  = prim.GetXaxis().GetBinUpEdge(prim.GetXaxis().GetNbins())
    for val in [-0.5, 0.5]:
      lines.append(TLine(lowEdge, val, upEdge, val))
      lines[-1].Draw("SAME")
      lines[-1].SetLineStyle(2)
    for prim in can.GetListOfPrimitives():
      if "TLegend" in prim.IsA().GetName():
        prim.Draw("SAME")
    

  outFile = TFile(outFileName, "RECREATE")
  for can in cans:
    can.Write()
  outFile.Close()
