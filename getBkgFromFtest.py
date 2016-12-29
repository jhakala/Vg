from os import symlink, path
from optparse import OptionParser

####
# Script for getting a background prediction pdf from the results of the fTest
# It has an interactive mode where you can look at the pdfs in the multipdf
# as well as a mode where you can pick one without seeing the prompt.
# For help on the command line options, do
# python getBkgFromFtest.py --help
#
# John Hakala 12/28/2016
####

parser = OptionParser()
#parser.add_option("-i", "--inFtest", dest="inFtest", 
#                  help = "the input mlfit rootfile")
parser.add_option("-o", "--outSuffix" , dest="outSuffix", default="tmp",
                  help = "the suffix for the of the output : blahblahPdf_OUTSUFFIX.root" )
parser.add_option("-c", "--category"  , dest="category",
                  help = "either 'btag' or 'antibtag'"                                   )
parser.add_option("-n", "--pdfIndex"   , dest="pdfIndex",
                  help = "the index of the desired pdf in the multipdf"                  )
parser.add_option("-b", action="store_true", dest="batch"    , default=False,
                  help = "turn on batch mode"                                            )
parser.add_option("-p", action="store_true", dest="makePlot" , default=False,
                  help = "toggle generating a plot in pdf form"                          )
parser.add_option("-l", action="store_true", dest="makeLink" , default=False,
                  help = "make symlink 'bkg_CATEGORY.root' to the output file"           )
parser.add_option("-d", action="store_true", dest="linkData" , default=False,
                  help = "make symlink 'w_data_CATEGORY.root' to w_data in fitFiles dir" )
(options, args) = parser.parse_args()
if options.outSuffix is None:
  parser.error("output histogram filename not given")

from ROOT import *
if options.batch:
  gROOT.SetBatch()

if options.category == "antibtag" :
   inFtest = "newMultiPdf_antibtag.root"
   capName = "AntiBtag"
elif options.category == "btag" :
   inFtest = "newMultiPdf_btag.root"
   capName = "Btag"
else:
  exit("something went wrong with the categories! \n%s" %
       ("... you picked '%s' but it has to be 'antibtag' or 'btag'" % options.category)
      )
gSystem.Load("libdiphotonsUtils")
gSystem.Load("libHiggsAnalysisCombinedLimit")
inFile = TFile(inFtest)
wtemplates = inFile.Get("wtemplates")
multipdf = wtemplates.pdf("model_bkg_%s" % capName)
if options.pdfIndex is None:
  nPdfs = multipdf.getNumPdfs()
  pdfNames = []
  for i in range(0, nPdfs):
    pdfNames.append( multipdf.getPdf(i).GetName() )
  ans=True
  selectedPdf=""
  while ans:
    print "please pick a pdf:"
    for i in range( 0, len(pdfNames) ):
      print "  %i. %s " % (i, pdfNames[i])
    pdfIndex = raw_input()
    if int(pdfIndex) in range(0, len(pdfNames)): 
      selectedPdf = pdfNames[int(pdfIndex)]
      ans=False
else:
  pdfIndex = options.pdfIndex
  selectedPdf = multipdf.getPdf(int(pdfIndex)).GetName()

var = wtemplates.var("x")
frame = var.frame()

rooWS = RooWorkspace("Vg")
pdfFromMultiPdf = multipdf.getPdf(int(pdfIndex))
outFileName = "%s_%s.root" % (pdfFromMultiPdf.GetName(), options.outSuffix)
outFile = TFile(outFileName, "RECREATE")
outFile.cd()
data = wtemplates.data("data_%s" % capName)
pdfFromMultiPdf.SetName("bg_%s" % options.category)

nBackground=RooRealVar("bg_%s_norm" % options.category, "nbkg", data.sumEntries())


getattr(rooWS, 'import')(pdfFromMultiPdf)
getattr(rooWS, 'import')(data)
getattr(rooWS, 'import')(nBackground)

varset   = pdfFromMultiPdf.getVariables()
varIt    = varset.iterator()
paramVar = varIt.Next()
while paramVar:
  if paramVar.GetName() != var.GetName(): # don't remove the range from the "x" variable
    rooWS.var(paramVar.GetName()).removeRange()
    print "removed range from pdf %s with name %s" % (selectedPdf, paramVar.GetName())
  paramVar = varIt.Next()

result = pdfFromMultiPdf.fitTo(data, RooFit.Minimizer("Minuit2"), RooFit.Range(700, 4700), RooFit.SumW2Error(kTRUE), RooFit.Save())
data.plotOn(frame)
pdfFromMultiPdf.plotOn(frame)
can = TCanvas()
can.cd()
frame.Draw()
if options.makePlot:
  can.Print("fitFromFtest_%s.pdf" % options.outSuffix)

rooWS.Write()
if options.makeLink:
  bkgLinkName = "bg_%s.root" % options.category
  if not path.isfile(bkgLinkName):
    symlink(outFileName, bkgLinkName)

if options.linkData:
  dataLinkName = "w_data_%s.root" % options.category
  if not path.isfile(dataLinkName):
    symlink("../dataFiles/w_data_%s.root" % options.category, dataLinkName)
