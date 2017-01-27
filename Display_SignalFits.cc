// Creates the images and HTML
// for displaying changes in Signal MC
// due to JEC+1-1, and JER+1-1

#include <TH1D.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TFractionFitter.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TArrow.h>
#include <TColor.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "CMS_lumi.C"
#include "tdrstyle.C"

//#include "RooRealVar.h"
//#include "RooArgList.h"
//#include "RooChebychev.h"
/*#include "RooDataHist.h"
 #include "RooAbsPdf.h"
 #include "RooWorkspace.h"
 #include "RooPlot.h"
 #include "RooFitResult.h"
 #include "RooCBShape.h"
 #include "RooGaussian.h"
 */
int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV
int iPos =11;

int rebin=1;
ofstream outfile;

std::string tostr(float t, int precision=0)
{
    std::ostringstream os;
    os<<std::setprecision(precision)<<t;
    return os.str();
}

double quad(double a, double b, double c=0, double d=0, double e=0, double f=0, double g=0, double h=0, double i=0, double j=0, double k=0)
{
    return pow(a*a+b*b+c*c+d*d+e*e+f*f+g*g+h*h+i*i+j*j+k*k, 0.5);
}

struct Params
{
    double sg_p0;
    double sg_p1;
    double sg_p2;
    double sg_p3;
    double sg_p4;
    double sg_p5;
    double sg_p6;
    double sg_p0_err;
    double sg_p1_err;
    double sg_p2_err;
    double sg_p3_err;
    double sg_p4_err;
    double sg_p5_err;
    double sg_p6_err;
};


RooPlot* fitSignal(std::string dirName, TH1D *h, int massNum, std::string mass, int color, TLegend *leg, Params &params, std::string postfix, bool kinFit=false)
{
    
    RooRealVar *x, *sg_p0, *sg_p1, *sg_p2, *sg_p3, *sg_p4, *sg_p5, *sg_p6, *sg_p7, *sg_p8;
    //x=new RooRealVar("x", "m_{X} (GeV)", 600., 3200.);
    
    double massL = double(massNum);
    double rangeLo=TMath::Max(700., massL-0.3*massL), rangeHi=TMath::Min(4700., massL+0.3*massL);
    
    // for antibtag 650-750
    // original
    //sg_p2=new RooRealVar((std::string("sg_p2")+postfix).c_str(), "sg_p2", 1.3, 0., 200.);
    //sg_p3=new RooRealVar((std::string("sg_p3")+postfix).c_str(), "sg_p3", 5, 0., 300.); 
    // all besides antibtag 650-750
    //sg_p2=new RooRealVar((std::string("sg_p2")+postfix).c_str(), "sg_p2", 1.3, 0.1, 200.);
    //sg_p3=new RooRealVar((std::string("sg_p3")+postfix).c_str(), "sg_p3", 5, 0.1, 300.);
    //sg_p6=new RooRealVar((std::string("sg_p6")+postfix).c_str(), "sg_p6", 0.99, 0.,1.);
    if (postfix == "btag") {
      sg_p6=new RooRealVar((std::string("sg_p6")+postfix).c_str(), "sg_p6", 1., 0.,1.);
      sg_p6->setConstant(kTRUE);
      sg_p0=new RooRealVar((std::string("sg_p0")+postfix).c_str(), "sg_p0", massL, massL-0.1*massL, massL+0.1*massL);
      sg_p1=new RooRealVar((std::string("sg_p1")+postfix).c_str(), "sg_p1", 0.03*massL, 5., 400.);
      if (massL<750) {
        sg_p2=new RooRealVar((std::string("sg_p2")+postfix).c_str(), "sg_p2", 1.3, 5, 200.);
        sg_p3=new RooRealVar((std::string("sg_p3")+postfix).c_str(), "sg_p3", 5, 3, 300.);
      }
      else {
        sg_p2=new RooRealVar((std::string("sg_p2")+postfix).c_str(), "sg_p2", 1.3, 0.25, 200.);
        sg_p3=new RooRealVar((std::string("sg_p3")+postfix).c_str(), "sg_p3", 5, 0.15, 300.);
      }
      sg_p4=new RooRealVar((std::string("sg_p4")+postfix).c_str(), "sg_p4", massL, 500., 800.);
      sg_p5=new RooRealVar((std::string("sg_p5")+postfix).c_str(), "sg_p5", 150, 0., 3000.);
    } 
    else {
        if (massL<750) {
          sg_p0=new RooRealVar((std::string("sg_p0")+postfix).c_str(), "sg_p0", massL, massL-0.1*massL, massL+0.1*massL);
          sg_p1=new RooRealVar((std::string("sg_p1")+postfix).c_str(), "sg_p1", 0.03*massL, 5., 400.);
          sg_p2=new RooRealVar((std::string("sg_p2")+postfix).c_str(), "sg_p2", 1.3, 5, 200.);
          sg_p3=new RooRealVar((std::string("sg_p3")+postfix).c_str(), "sg_p3", 5, 3, 300.);
          sg_p4=new RooRealVar((std::string("sg_p4")+postfix).c_str(), "sg_p4", massL, 500., 800.);
          sg_p5=new RooRealVar((std::string("sg_p5")+postfix).c_str(), "sg_p5", 150, 0., 3000.);
        }
        else if (massL > 2850) { 
          sg_p0=new RooRealVar((std::string("sg_p0")+postfix).c_str(), "sg_p0", massL, massL-0.5*massL, massL+0.1*massL);
          sg_p1=new RooRealVar((std::string("sg_p1")+postfix).c_str(), "sg_p1", 0.01*massL, 5., 400.); 
          sg_p2=new RooRealVar((std::string("sg_p2")+postfix).c_str(), "sg_p2", 1.3, 0.25, 200.);
          sg_p3=new RooRealVar((std::string("sg_p3")+postfix).c_str(), "sg_p3", 5, 0.15, 300.);
          sg_p4=new RooRealVar((std::string("sg_p4")+postfix).c_str(), "sg_p4", massL-0.5*massL, 500., 800.);
          sg_p5=new RooRealVar((std::string("sg_p5")+postfix).c_str(), "sg_p5", 100, 0., 3000.);
        }
        else {
          sg_p0=new RooRealVar((std::string("sg_p0")+postfix).c_str(), "sg_p0", massL, massL-0.1*massL, massL+0.1*massL);
          sg_p1=new RooRealVar((std::string("sg_p1")+postfix).c_str(), "sg_p1", 0.03*massL, 5., 400.);
          sg_p2=new RooRealVar((std::string("sg_p2")+postfix).c_str(), "sg_p2", 1.3, 0.25, 200.);
          sg_p3=new RooRealVar((std::string("sg_p3")+postfix).c_str(), "sg_p3", 5, 0.15, 300.);
          sg_p4=new RooRealVar((std::string("sg_p4")+postfix).c_str(), "sg_p4", massL, 500., 800.);
          sg_p5=new RooRealVar((std::string("sg_p5")+postfix).c_str(), "sg_p5", 150, 0., 3000.);
        }
        sg_p6=new RooRealVar((std::string("sg_p6")+postfix).c_str(), "sg_p6", 0.99, 0.,1.);
    }
    
    x=new RooRealVar("x", "m_{X} (GeV)", 700., 4700.);
    RooCBShape signalCore((std::string("signalCore")+postfix).c_str(), "signalCore", *x, *sg_p0, *sg_p1,*sg_p2, *sg_p3);
    RooGaussian signalComb((std::string("signalComb")+postfix).c_str(), "Combinatoric", *x, *sg_p0, *sg_p5);
    RooAddPdf signal((std::string("signal")+postfix).c_str(), "signal", RooArgList(signalCore, signalComb), *sg_p6);
    
    RooDataHist signalHistogram((std::string("signalHistogram")+postfix).c_str(), "Signal Histogram", RooArgList(*x), h);
    //signal.fitTo(signalHistogram, RooFit::Range(rangeLo, rangeHi), RooFit::Save());
    signal.fitTo(signalHistogram, RooFit::Hesse(false), RooFit::Range(rangeLo, rangeHi), RooFit::Save());

    params.sg_p0=sg_p0->getVal(); params.sg_p0_err=sg_p0->getError();
    params.sg_p1=sg_p1->getVal(); params.sg_p1_err=sg_p1->getError();
    params.sg_p2=sg_p2->getVal(); params.sg_p2_err=sg_p2->getError();
    params.sg_p3=sg_p3->getVal(); params.sg_p3_err=sg_p3->getError();
    params.sg_p4=sg_p0->getVal(); params.sg_p4_err=sg_p0->getError();
    params.sg_p5=sg_p5->getVal(); params.sg_p5_err=sg_p5->getError();
    params.sg_p6=sg_p6->getVal(); params.sg_p6_err=sg_p6->getError();
    RooPlot *plot=x->frame();
    if (color==kBlack)
    {
        signalHistogram.plotOn(plot, RooFit::MarkerColor(color), RooFit::MarkerSize(1.2));
        signal.plotOn(plot, RooFit::LineColor(color), RooFit::LineWidth(3));
    }
    else
    {
        signalHistogram.plotOn(plot, RooFit::MarkerColor(color));
        signal.plotOn(plot, RooFit::LineColor(color), RooFit::LineWidth(0));
    }
    leg->AddEntry((TObject*)0, ("#mu_{CB}= "+tostr(sg_p0->getVal(),4)+" #pm "+tostr(sg_p0->getError(),2)+" GeV").c_str(), "");
    leg->AddEntry((TObject*)0, ("#sigma_{CB}= "+tostr(sg_p1->getVal(),2)+" #pm "+tostr(sg_p1->getError(),2)+" GeV").c_str(), "");
    
    // std::cout<<"chi2/dof = "<<plot->chiSquare()<<std::endl;
    
    if (color==kBlack)
    {
        RooRealVar signal_p0((std::string("signal_p0_")+postfix).c_str(), "signal_p0", sg_p0->getVal());
        RooRealVar signal_p1((std::string("signal_p1_")+postfix).c_str(), "signal_p1", sg_p1->getVal());
        RooRealVar signal_p2((std::string("signal_p2_")+postfix).c_str(), "signal_p2", sg_p2->getVal());
        RooRealVar signal_p3((std::string("signal_p3_")+postfix).c_str(), "signal_p3", sg_p3->getVal());
        RooRealVar signal_p4((std::string("signal_p4_")+postfix).c_str(), "signal_p4", sg_p0->getVal());
        RooRealVar signal_p5((std::string("signal_p5_")+postfix).c_str(), "signal_p5", sg_p5->getVal());
        RooRealVar signal_p6((std::string("signal_p6_")+postfix).c_str(), "signal_p6", sg_p6->getVal());
        //RooGaussian signal_fixed("signal_fixed", "Signal Prediction", *x, signal_p0, signal_p1);
        RooCBShape signalCore_fixed((std::string("signalCore_fixed_")+postfix).c_str(), "signalCore", *x, signal_p0, signal_p1,signal_p2, signal_p3);
        RooGaussian signalComb_fixed((std::string("signalComb_fixed_")+postfix).c_str(), "Combinatoric", *x, signal_p0, signal_p5);
        RooAddPdf signal_fixed((std::string("signal_fixed_")+postfix).c_str(), "signal", RooArgList(signalCore_fixed, signalComb_fixed), signal_p6);
        RooWorkspace *w=new RooWorkspace("Vg");
        w->import(signal_fixed);
        w->SaveAs((dirName+"/w_signal_"+mass+".root").c_str());
    }
    return plot;
}

double lnN(double b, double a, double c)
{
    // std::cout<<"a = "<<a<<", b = "<<b<<", c = "<<c<<std::endl;
    // std::cout<<"1.+(a-c)/(2.*b) = "<<1.+fabs(a-c)/(2.*b)<<std::endl;
    double err=0;
    if (b>0) err=1.+fabs(a-c)/(2.*b);
    return err;
}

int Display_SignalFits(std::string postfix,
                       std::string dir_preselection="/scratch/osg/lesya/CMSSW_7_1_5/src/GenSignal",
                       std::string dir_selection="",
                       //std::string file_histograms="histos_signal-",
                       std::string file_histograms="histos_flatTuple_m",
                       int imass=650,
                       int rebin_factor = 1,

                       bool focus=false)
{
    
    
    writeExtraText = true;       // if extra text
    extraText  = "Simulation";  // default extra text is "Preliminary"
    lumi_13TeV  = "36.42 fb^{-1}"; // default is "19.7 fb^{-1}"

    
    rebin = rebin_factor;
    
    std::vector<std::string> masses;
    std::cout<<" starting with "<<imass<<std::endl;
    stringstream iimass ;
    iimass << imass;
    masses.push_back(iimass.str());
    
    std::string dirName = "signalFits_"+postfix;
    
    std::string file_postfix = std::string(".root");
    std::cout<< " file input "<< file_postfix<<std::endl;
    
    //gROOT->SetStyle("Plain");
    gStyle->SetOptStat(000000000);
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    gStyle->SetOptStat(0000);
    setTDRStyle();
    
    // Calculate nSignal events given production cross section, branching fractions and efficiency
    double totalLumi=36.42; // /fb

    //double prodXsec_1=1; // fb
    
    // Interpolation Plots
    std::vector<double> v_sg_p0, v_sg_p0_err;
    std::vector<double> v_sg_p1, v_sg_p1_err;
    std::vector<double> v_sg_p2, v_sg_p2_err;
    std::vector<double> v_sg_p3, v_sg_p3_err;
    std::vector<double> v_sg_p4, v_sg_p4_err;
    std::vector<double> v_sg_p5, v_sg_p5_err;
    std::vector<double> v_sg_p6, v_sg_p6_err;
    
    // Write to an HTML File
    // outfile.open((dirName+"/index.html").c_str());
     outfile.open((dirName+"/fit_" + std::to_string(imass) + ".html").c_str());
    outfile<<"<html>"<<std::endl;
    outfile<<"<head>"<<std::endl;
    outfile<<"<script type=\"text/javascript\">"<<std::endl;
    outfile<<"function toggleMe(a){"<<std::endl;
    outfile<<"var e=document.getElementById(a);"<<std::endl;
    outfile<<"if(!e)return true;"<<std::endl;
    outfile<<"if(e.style.display==\"none\"){"<<std::endl;
    outfile<<"e.style.display=\"block\""<<std::endl;
    outfile<<"}"<<std::endl;
    outfile<<"else{"<<std::endl;
    outfile<<"e.style.display=\"none\""<<std::endl;
    outfile<<"}"<<std::endl;
    outfile<<"return true;"<<std::endl;
    outfile<<"}"<<std::endl;
    outfile<<"</script>"<<std::endl;
    outfile<<"</head>"<<std::endl;
    outfile<<"<body>"<<std::endl;
    
    for (unsigned int i=0; i<masses.size(); ++i) {
        std::string klj = "";
        std::string klj2 = "";
        std::cout<<" OPENING FILE: " << (dir_preselection+"/"+postfix+"/"+file_histograms+masses.at(i)+file_postfix).c_str() <<std::endl;
        if (masses.at(i) == "650" )       {klj = "0";  klj2 = "0"; }
        else if ( masses.at(i) == "750")  {klj = "1";  klj2 = "0"; }
        else if (masses.at(i) == "850" ) {klj = "2";  klj2 = "0"; }
        else if (masses.at(i) == "1000")  {klj = "3";  klj2 = "0"; }
        else if (masses.at(i) == "1150")  {klj = "4";  klj2 = "0"; }
        else if (masses.at(i) == "1300")  {klj = "5";  klj2 = "0"; }
        else if (masses.at(i) == "1450" ) {klj = "6";  klj2 = "0"; }
        else if (masses.at(i) == "1600" ) {klj = "7";  klj2 = "0"; }
        else if (masses.at(i) == "1750")  {klj = "8";  klj2 = "0"; }
        else if (masses.at(i) == "1900" ) {klj = "9";  klj2 = "0"; }
        else if (masses.at(i) == "2050" ) {klj = "10"; klj2 = "0"; }
        else if (masses.at(i) == "2450" ) {klj = "11"; klj2 = "0"; }
        else if (masses.at(i) == "2850" ) {klj = "12"; klj2 = "0"; }
        else if (masses.at(i) == "3250" ) {klj = "13"; klj2 = "0"; }
        else {klj = "5"; klj2="0__x";}
        //klj = "5"; klj2="0__x";
        
        std::cout<<"using mass "<<klj<<std::endl;
        TFile *file = new TFile((dir_preselection+"/"+postfix+"/"+file_histograms+masses.at(i)+file_postfix).c_str());
        char kljname [20];
        sprintf(kljname, "distribs_%s_10_%s", klj.c_str(), klj2.c_str());
        std::cout<< "kljname is" << kljname <<std::endl;
        TH1D *h_mX_SR=(TH1D*)file->Get(kljname);
        std::cout << "Debug step 1: GetSumOfWeights for " << kljname << " is " << h_mX_SR->GetSumOfWeights() << std::endl;
        
        double nSignal_init=1.0;

        double xPad = 0.3;
        TCanvas *c_mX_SR=new TCanvas(("c_mX_SR_"+masses.at(i)).c_str(), ("c_mX_SR_"+masses.at(i)).c_str(), 700*(1.-xPad), 700);
        TPad *p_1=new TPad("p_1", "p_1", 0, xPad, 1, 1);
        p_1->SetFillStyle(4000);
        p_1->SetFrameFillColor(0);
        p_1->SetBottomMargin(0.02);
        p_1->SetTopMargin(0.06);

        TPad* p_2 = new TPad("p_2", "p_2",0,0,1,xPad);
        p_2->SetBottomMargin((1.-xPad)/xPad*0.13);
        p_2->SetTopMargin(0.03);
        p_2->SetFillColor(0);
        p_2->SetBorderMode(0);
        p_2->SetBorderSize(2);
        p_2->SetFrameBorderMode(0);
        p_2->SetFrameBorderMode(0);
        
        p_1->Draw();
        p_2->Draw();
        p_1->cd();
        

        h_mX_SR->SetTitle(("m_{X} Peak in Signal MC (m_{X}="+masses.at(i)+" GeV); m_{X} (GeV)").c_str());
        h_mX_SR->Rebin(rebin);
        
        TLegend *leg = new TLegend(0.75,0.75,0.5,0.9,NULL,"brNDC");
        leg->SetBorderSize(0);
        leg->SetTextSize(0.035);
        leg->SetTextFont(42);
        leg->SetLineColor(1);
        leg->SetLineStyle(1);
        leg->SetLineWidth(2);
        leg->SetFillColor(0);
        leg->SetFillStyle(0);
        leg->SetTextFont(42);

        
        leg->AddEntry(h_mX_SR, "Signal MC");
        Params params_vg;
        h_mX_SR->Scale(36420.0);
        RooPlot *plot_vg=fitSignal(dirName,h_mX_SR, imass, masses.at(i), kBlack, leg, params_vg,postfix, true);
        h_mX_SR->Scale(1.0/36420.0);

        v_sg_p0.push_back(params_vg.sg_p0); v_sg_p0_err.push_back(params_vg.sg_p0_err);
        v_sg_p1.push_back(params_vg.sg_p1); v_sg_p1_err.push_back(params_vg.sg_p1_err);
        v_sg_p2.push_back(params_vg.sg_p2); v_sg_p2_err.push_back(params_vg.sg_p2_err);
        v_sg_p3.push_back(params_vg.sg_p3); v_sg_p3_err.push_back(params_vg.sg_p3_err);
        v_sg_p4.push_back(params_vg.sg_p4); v_sg_p4_err.push_back(params_vg.sg_p4_err);
        v_sg_p5.push_back(params_vg.sg_p5); v_sg_p5_err.push_back(params_vg.sg_p5_err);
        v_sg_p6.push_back(params_vg.sg_p6); v_sg_p6_err.push_back(params_vg.sg_p6_err);
        

        //double rangeLoLocal = 700;//750
        //double rangeHiLocal = 900;//750

        //double rangeLoLocal = 600;//750
        //double rangeHiLocal = 1000;//750
        //double rangeHiLocal = 1500;//1000
        //double rangeLoLocal = 1400;//2000
        //double rangeHiLocal = 2500;//2000

        //double rangeLoLocal = 2000;//750
        //double rangeHiLocal = 3500;//750
        
        plot_vg->SetTitle("");
        plot_vg->GetYaxis()->SetRangeUser(0.01, 100);
        plot_vg->GetXaxis()->SetRangeUser(imass-400, imass+400);
        //plot_vg->GetXaxis()->SetRangeUser(rangeLoLocal, rangeHiLocal);
        plot_vg->GetXaxis()->SetLabelOffset(0.03);
        plot_vg->GetXaxis()->SetNdivisions(505);

        /*plot_vg->GetXaxis()->SetTitleOffset(1.);
        plot_vg->GetXaxis()->SetLabelSize(0.03);
        plot_vg->GetYaxis()->SetLabelSize(0.05);
        plot_vg->GetYaxis()->SetTitleSize(0.04);
        plot_vg->GetXaxis()->SetTitleSize(0.04);
        plot_vg->GetYaxis()->SetLabelSize(.03);
        plot_vg->GetYaxis()->SetTitleOffset(1.2);*/
        
        plot_vg->Draw("same");
        leg->SetFillColor(0);
        leg->Draw();
        
        CMS_lumi(p_1, iPeriod, iPos );
        
        p_2->cd();
        RooHist* hpull;
        hpull = plot_vg->pullHist();
        RooRealVar* x=new RooRealVar("x", "m_{X} (GeV)", 700, 4700);
        x->setBins(4000);

        RooPlot* frameP = x->frame() ;
        frameP->SetTitle("");
        frameP->GetXaxis()->SetRangeUser(imass-400, imass+400);
        //frameP->GetXaxis()->SetRangeUser(rangeLoLocal, rangeHiLocal);

        frameP->addPlotable(hpull,"P");
        frameP->GetYaxis()->SetRangeUser(-5,5);
        frameP->GetYaxis()->SetNdivisions(505);
        frameP->GetXaxis()->SetNdivisions(505);
        frameP->GetYaxis()->SetTitle("Pull");
        
        frameP->GetYaxis()->SetTitleSize((1.-xPad)/xPad*0.06);
        frameP->GetYaxis()->SetTitleOffset(1.2/((1.-xPad)/xPad));
        frameP->GetXaxis()->SetTitleSize((1.-xPad)/xPad*0.06);
        //frameP->GetXaxis()->SetTitleOffset(1.0);
        frameP->GetXaxis()->SetLabelSize((1.-xPad)/xPad*0.05);
        frameP->GetYaxis()->SetLabelSize((1.-xPad)/xPad*0.05);
        
        
        frameP->Draw();
        
        
        c_mX_SR->SaveAs((dirName+"/c_mX_SR_"+masses.at(i)+".png").c_str());
        c_mX_SR->SaveAs((dirName+"/c_mX_SR_"+masses.at(i)+".root").c_str());
        p_1->SetLogy();
        
        c_mX_SR->SaveAs((dirName+"/c_mX_SR_"+masses.at(i)+"Log.png").c_str());
        c_mX_SR->SaveAs((dirName+"/c_mX_SR_"+masses.at(i)+"Log.root").c_str());
        
        outfile<<"<br/><hr/>"<<std::endl;
        outfile<<"<h2> mX = "<<masses.at(i)<<" </h2>"<<std::endl;
        outfile<<"<table border='1'>"<<std::endl;
        outfile<<" <tr>"<<std::endl;
        outfile<<"  <td>"<<std::endl;
        outfile<<"   <img src='"<<("c_mX_SR_"+masses.at(i)+".png")<<"'/><br/>"<<std::endl;
        outfile<<"   <h2 align='center'>Without Kin-Fit. Fitted to an Exp-Gauss-Exp function.</h2><br/>"<<std::endl;
        outfile<<"   === Baseline plot === </br>"<<std::endl;
        //outfile<<"   norm = "<<h_mX_SR->GetSumOfWeights()*totalLumi*prodXsec_1/nSignal_init<<" <br/>"<<std::endl;
        outfile<<"   norm = "<<h_mX_SR->GetSumOfWeights()*totalLumi<<" <br/>"<<std::endl; // weight has already been applied
        /*outfile<<"sg_p0     param   "<<params_vg.sg_p0<<" -"<<quad(sg_p0_errStat/2., sg_p0_errSyst_min)<<"/+"<<quad(sg_p0_errStat/2., sg_p0_errSyst_max)<<" <br/>"<<std::endl;
         outfile<<"sg_p1     param   "<<params_vg.sg_p1<<" -"<<quad(sg_p1_errStat/2., sg_p1_errSyst_min)<<"/+"<<quad(sg_p1_errStat/2., sg_p1_errSyst_max)<<" <br/>"<<std::endl;
         outfile<<"sg_p2     param   "<<params_vg.sg_p2<<"  -"<<quad(sg_p2_errStat/2., sg_p2_errSyst_min)<<"/+"<<quad(sg_p2_errStat/2., sg_p2_errSyst_max)<<" <br/>"<<std::endl;
         outfile<<"sg_p3     param   "<<params_vg.sg_p3<<"  -"<<quad(sg_p3_errStat/2., sg_p3_errSyst_min)<<"/+"<<quad(sg_p3_errStat/2., sg_p3_errSyst_max)<<" <br/>"<<std::endl;
         outfile<<"sg_p4     param   "<<params_vg.sg_p4<<"  -"<<quad(sg_p4_errStat/2., sg_p4_errSyst_min)<<"/+"<<quad(sg_p4_errStat/2., sg_p4_errSyst_max)<<" <br/>"<<std::endl;
         
         */
        
        outfile<<"   </div>"<<std::endl;
        outfile<<"  </td>"<<std::endl;
        
        outfile<<" </tr>"<<std::endl;
        outfile<<"</table>"<<std::endl;
        
        // Close all files
        //file->Close();
        /*	file_JECp1->Close();
         file_JECm1->Close();
         file_JERp1->Close();
         file_JERm1->Close();
         file_Trigm1->Close();
         file_bTagDown->Close();
         file_bTagUp->Close();
         */
    }
    
    
    return 0;
}

