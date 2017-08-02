from sys import argv
from getMasses import getMasses
from optparse import OptionParser
from os import path, makedirs
from datetime import datetime


def Plot(files, label, obs, cat, inDir):

    radmasses = []
    for f in files:
        radmasses.append(int(f.GetName().replace("higgsCombineTest.Asymptotic.mH", "").replace(".root","").replace("%s/"%inDir, "")))
    print "files is:"
    print files
    print "radmasses is:" 

    print radmasses
    #radmasses = [750, 850, 1000, 1150, 1750, 2050, 2450, 3250]

    efficiencies={}
    for mass in radmasses:
        efficiencies[mass]=1. # to convert from fb to fb

    fChain = []
    for onefile in files:
        print "for fchain[%i]: %s " % (len(fChain), onefile.GetName())
        #fileIN = TFile(onefile)
        fChain.append(onefile.Get("limit;1"))  
        print "fchain[%i]: %s" % (len(fChain)-1, fChain[-1])

        rt.gROOT.ProcessLine("struct limit_t {Double_t limit;};")
        from ROOT import limit_t
        limit_branch = rt.limit_t()

        for j in range(0,len(fChain)):
            chain = fChain[j]
            print "Setting branch address for: fChain[%i]" % j
            chain.SetBranchAddress("limit", rt.AddressOf(limit_branch,'limit'))
    print "done setting branch addresses."

    rad = []
    for j in range(0,len(fChain)):
        chain = fChain[j]
        thisrad = []
        for  i in range(0,6):
            chain.GetTree().GetEntry(i)
            thisrad.append(limit_branch.limit)
            #print "limit = %f" %limit_branch.limit
        #print thisrad
        rad.append(thisrad)
    print "   >>> done getting all the files. About to make plot..."

    # we do a plot r*MR
    mg = rt.TMultiGraph()
    mg.SetTitle("X -> ZZ")
    c1 = rt.TCanvas("c1","A Simple Graph Example",200,10,600,600)
    x = []
    yobs = []
    y2up = []
    y1up = []
    y1down = []
    y2down = []
    ymean = []

    for i in range(0,len(fChain)):
        y2up.append(rad[i][0]  *efficiencies[radmasses[j]])
        y1up.append(rad[i][1]  *efficiencies[radmasses[j]])
        ymean.append(rad[i][2] *efficiencies[radmasses[j]])
        y1down.append(rad[i][3]*efficiencies[radmasses[j]])
        y2down.append(rad[i][4]*efficiencies[radmasses[j]])
        yobs.append(rad[i][5]  *efficiencies[radmasses[j]])

    grobs = rt.TGraphErrors(1)
    grobs.SetMarkerStyle(rt.kFullDotLarge)
    grobs.SetLineColor(rt.kBlack)
    grobs.SetLineWidth(3)
    gr2up = rt.TGraphErrors(1)
    gr2up.SetMarkerColor(0)
    gr1up = rt.TGraphErrors(1)
    gr1up.SetMarkerColor(0)
    grmean = rt.TGraphErrors(1)
    grmean.SetLineColor(1)
    grmean.SetLineWidth(2)
    grmean.SetLineStyle(3)
    gr1down = rt.TGraphErrors(1)
    gr1down.SetMarkerColor(0)
    gr2down = rt.TGraphErrors(1)
    gr2down.SetMarkerColor(0)
  
    for j in range(0,len(fChain)):
        grobs.SetPoint(j, radmasses[j], yobs[j])
        gr2up.SetPoint(j, radmasses[j], y2up[j])
        gr1up.SetPoint(j, radmasses[j], y1up[j])
        grmean.SetPoint(j, radmasses[j], ymean[j])
        print(radmasses[j], ymean[j], yobs[j])
        gr1down.SetPoint(j, radmasses[j], y1down[j])    
        gr2down.SetPoint(j, radmasses[j], y2down[j])
        #print " observed %f %f" %(radmasses[j],yobs[j])
    
    mg.Add(gr2up)#.Draw("same")
    mg.Add(gr1up)#.Draw("same")
    mg.Add(grmean,"L")#.Draw("same,AC*")
    mg.Add(gr1down)#.Draw("same,AC*")
    mg.Add(gr2down)#.Draw("same,AC*")
    if obs: mg.Add(grobs,"L")#.Draw("AC*")
 
    c1.SetLogy(1)
    mg.SetTitle("")
    mg.Draw("AP")
    mg.GetXaxis().SetTitle("Resonance mass (GeV)")
    resonance="G"
        #resonance="G_{Bulk}"
    if withAcceptance:
        mg.GetYaxis().SetTitle("#sigma #times B("+resonance+" #rightarrow "+label.split("_")[0].replace("RS1","").replace("Bulk","")+") #times A (fb)")
    else:
        mg.GetYaxis().SetTitle("95% CL UL on #sigma #times B(X#rightarrowH#gamma) (fb)")
    mg.GetYaxis().SetRangeUser(10,5000)
    mg.GetXaxis().SetNdivisions(605)

    if "qW" in label.split("_")[0] or "qZ" in label.split("_")[0]:
        mg.GetXaxis().SetLimits(500,4100)
    else:
        mg.GetXaxis().SetLimits(500,4100)

    # histo to shade
    n=len(fChain)

    grgreen = rt.TGraph(2*n)
    for i in range(0,n):
        grgreen.SetPoint(i,radmasses[i],y2up[i])
        grgreen.SetPoint(n+i,radmasses[n-i-1],y2down[n-i-1])

    grgreen.SetFillColor(rt.kOrange)
    grgreen.Draw("f") 


    gryellow = rt.TGraph(2*n)
    for i in range(0,n):
        gryellow.SetPoint(i,radmasses[i],y1up[i])
        gryellow.SetPoint(n+i,radmasses[n-i-1],y1down[n-i-1])

    gryellow.SetFillColor(rt.kGreen+1)
    gryellow.Draw("f,same") 

    grmean.Draw("L")
    if obs: grobs.Draw("L")

    gtheory = rt.TGraphErrors(1)
    gtheory.SetLineColor(rt.kBlack)
    gtheory.SetLineWidth(4)

    leg = rt.TLegend(0.5,0.65,0.95,0.89,"H(b#bar{b})#gamma: %s category" % cat)
    leg2 = rt.TLegend(0.49,0.55,0.95,0.89)
    leg.SetFillColor(rt.kWhite)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.04)
    leg.SetTextFont(42)
    leg.SetBorderSize(0)
    leg2.SetFillColor(rt.kWhite)
    leg2.SetFillStyle(0)
    leg2.SetTextSize(0.04)
    leg2.SetBorderSize(0)

    if obs: leg.AddEntry(grobs, "Observed limit", "L")
    leg.AddEntry(grmean, "Expected limit", "L")
    leg.AddEntry(gryellow, "Expected limit #pm 1#sigma", "f")
    leg.AddEntry(grgreen, "Expected limit #pm 2#sigma", "f")
    #leg.AddEntry(gtheory, ltheory, "L")

    if obs: leg2.AddEntry(grobs, " ", "")
    #leg2.AddEntry(grmean, " ", "L")
    #leg2.AddEntry(grmean, " ", "L")
    #leg2.AddEntry(gtheory, " ", "")

    leg.Draw()
    #leg2.Draw("same")

    CMS_lumi.CMS_lumi(c1, iPeriod, iPos)
    c1.cd()
    c1.Update()
    
    print "   >>> Done drawing plots. About to save plots..."
   
    today = '{:%Y-%m-%d}'.format(datetime.now())
    outDir = "brazilianFlags_%s" % today
    if not path.exists(outDir):
      makedirs(outDir)
  
    if withAcceptance:
        c1.SaveAs(path.join(outDir, "brazilianFlag_acc_%s_%s_13TeV.root" % (cat, inDir)))
        c1.SaveAs(path.join(outDir,"brazilianFlag_acc_%s_%s_13TeV.pdf" % (cat, inDir)))
    else:
        c1.SaveAs(path.join(outDir, "brazilianFlag_%s_%s_13TeV.root" % (cat, inDir)))
        c1.SaveAs(path.join(outDir, "brazilianFlag_%s_%s_13TeV.pdf" % (cat, inDir)))
        grobs.SaveAs(path.join(outDir, "brazilianFlag_observed_%s_%s_13TeV.root" % (cat, inDir)))
        grmean.SaveAs(path.join(outDir, "brazilianFlag_expected_%s_%s_13TeV.root" % (cat, inDir)))


if __name__ == '__main__':

  parser = OptionParser()
  parser.add_option("-i", "--inDir", dest="inDir",
                    help = "the input directory"                                    )
  parser.add_option("-b", action="store_true", dest="batch"     , default=False,
                    help = "turn on batch mode"                                     )
  (options, args) = parser.parse_args()
  
  if options.inDir is None:
    print "please supply a valid input directory with the -i option"
    exit(1)
  if not path.exists(options.inDir):
    print "invalid input directory given: %s" % options.inDir
    exit(1)
  category = "not found!"
  if "_antibtag_" in options.inDir:
    category = "antibtag"
  if "_btag_" in options.inDir:
    category = "btag"
  if "_combined_" in options.inDir:
    category = "combined"
  if not category in ["antibtag", "btag", "combined"]:
    print "Please pick an input directory that specifies the category: either 'btag', 'antibtag', or 'combined'."
    exit(1)
  
  
  import ROOT as rt
  from ROOT import *
  if options.batch:
    gROOT.SetBatch()
  #set the tdr style
  import CMS_lumi, tdrstyle
  tdrstyle.setTDRStyle()
  
  #change the CMS_lumi variables (see CMS_lumi.py)
  CMS_lumi.lumi_13TeV = "35.9 fb^{-1}"
  
  CMS_lumi.writeExtraText = 1
  CMS_lumi.extraText = "Preliminary"
  CMS_lumi.lumi_sqrtS = "13 TeV" # used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
  
  iPos = 0
  if( iPos==0 ): CMS_lumi.relPosX = 0.12
  
  iPeriod =4
  
  
  withAcceptance=False
  unblind=True
  
  gStyle.SetPadRightMargin(0.06)
  gStyle.SetPadTopMargin(0.06)
  #channels=["RS1WW","RS1ZZ","WZ","qW","qZ","BulkWW","BulkZZ"]

  masses=getMasses()

  HPplots=[]
  LPplots=[]
  combinedplots=[]
  for mass in masses:
     HPplots+=[rt.TFile(path.join(options.inDir, "higgsCombineTest.Asymptotic.mH"+str(mass)+".root"))]
     print "added HPplot %s" % HPplots[-1]

  Plot(HPplots,category+"_Hgamma", unblind, category, options.inDir)
