#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooIntegralMorph.h"
#include "RooNLLVar.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"
using namespace RooFit ;
#include "CMS_lumi.C"
#include "tdrstyle.C"

void InterpolateSignal(TString postfix, float lowMass, float highMass, TString outDir = "GenSignal/") {
    setTDRStyle();

    // C r e a t e   e n d   p o i n t   p d f   s h a p e s
    // ------------------------------------------------------
    
    // Observable
    RooRealVar x("x","x",700,4700) ;
    
    const double step = 10;
    //const int nMCpoints = 13;
    const int nMCpoints = 2;

    //const int nMCpoints = 16; //W=0
    //const int nMCpoints = 14; //W=5
    //const int nMCpoints = 13; //W=5
    
    RooAbsPdf* gMass[nMCpoints];
    //const double masses[nMCpoints] = {300, 400, 500, 650, 740, 745, 750, 755, 760, 765, 850, 1000, 1150, 1300, 1450, 1600, 1750, 1900, 2050, 2450, 2850, 3250, 3650, 4050, 5000, 6000, 7000};
    //const double masses[nMCpoints] = {750, 850, 1000, 1150, 1300, 1450, 1600, 1750, 1900, 2050, 2450, 2850, 3250 };
    const double masses[nMCpoints] = {lowMass, highMass};

    //const double masses[nMCpoints] = {650, 740, 750, 760, 850, 1000, 1150, 1300, 1450, 1600, 1750, 1900, 2050, 2450, 3000, 3250}; //W=0

    //const double masses[nMCpoints] = {650, 740, 750, 760, 1000, 1150, 1300, 1450, 1600, 1750, 1900, 2450, 2850, 3250}; //W=5.6;
    
    //const double masses[nMCpoints] = {650, 740, 750, 850, 1150, 1450, 1600, 1750, 1900, 2050, 2450, 2850, 3250}; //W=10.0;

    
    TFile *f[nMCpoints];
    RooWorkspace* xf[nMCpoints];

    for (int i = 0; i!=nMCpoints; ++i ) {
        TString name = Form("signalFits_"+postfix+"_fullsim/w_signal_%d.root",int(masses[i]));
        if (!gSystem->AccessPathName(name)) {
            f[i] = new TFile(name);
            std::cout << "printing file with name: " << name << std::endl;
            f[i]->ls();
            xf[i] = (RooWorkspace*)f[i]->Get("Vg");
            std::cout << "printing workspace" << std::endl;
            xf[i]->Print();
            xf[i]->var("x")->setMin(700.);
            xf[i]->var("x")->setMax(4700.);
            gMass[i] = xf[i]->pdf("signal_fixed_"+postfix);
        } else {
            std::cout<<"File is not found: "<<name<<std::endl;
            return;
        }
    }
    
    RooWorkspace w("w");
    std::cout<<"blah: "<<std::endl;
    w.import(*gMass[0],RooFit::RenameVariable("signal_fixed_"+postfix,"signal_fixed_"+postfix+"_low"),RooFit::RenameAllVariablesExcept("low","x"));
    std::cout<<"blah2: "<<std::endl;
    gMass[0] = w.pdf("signal_fixed_"+postfix+"_low");
    for (int i = 1; i!=nMCpoints; ++i ) {
        TString name = Form("point_%d",i);
        w.import(*gMass[i],RooFit::RenameConflictNodes(name),RooFit::RenameAllVariablesExcept(name,"x"),RooFit::RenameVariable("signal_fixed_"+postfix,"signal_fixed_"+postfix+"_"+name));
        
        gMass[i] = w.pdf("signal_fixed_"+postfix+"_"+name);

        
    }
    
    TF1* funcEff;
    if (postfix == "antibtag") {

        std::cout << "got funceff for antibtag" << std::endl;
        funcEff = new TF1("fitFunctionAntiBtag", "[0]*TMath::TanH((x-[1])*[2])*TMath::Power(x,[3])+[4]", 650, 3250);//W=0
        funcEff->SetParameters(0.155540876641 , 464.483249363 , 0.00165214350276 , -0.000960109374091 , 0.00649591356139); //W=0

        //funcEff->SetParameters(-0.123432,0.000574454,-3.94051e-07,1.10552e-10,-1.13539e-14); //W=5.6 all range
        //funcEff->SetParameters(-0.174736,0.00069154,-4.90708e-07,1.42739e-10,-1.51912e-14); //W=5.6 600-3600
        //funcEff->SetParameters(-0.124845,0.000571665,-4.0269e-07,1.15632e-10,-1.20963e-14); //W=10.0 all range
        //funcEff->SetParameters(-0.204962,0.000752754,-5.49665e-07,1.63818e-10,-1.76895e-14); //W=10.0 600-3600
    } else if (postfix == "btag") {
        funcEff = new TF1("fitFunctionBtag", "[0]+[1]*TMath::ATan([2]*(x-[3]))*TMath::Exp([4]*TMath::Power(x-[5], [6]))", 650, 3250);
        funcEff->SetParameters(0.0164102690347 , 0.179684107425 , 0.00374967697452 , 684.190489303 , -2.30564873418e-07 , -7618.26703627 , 1.72754954338); //W=0

        //funcEff = new TF1("effFunc","pol4",0,10000);//W=5.6
        //funcEff->SetParameters(-0.0371581,0.000141343,-1.06872e-07,3.13078e-11,-3.1873e-15); //W=5.6 all range
        //funcEff->SetParameters(-0.0474795,0.000164342,-1.24851e-07,3.69595e-11,-3.82402e-15); //W=5.6 600-3600
        //funcEff->SetParameters(-0.0359695,0.000137542,-1.06553e-07,3.2496e-11,-3.48342e-15); //W=10.0 all range
        //funcEff->SetParameters(-0.0552242,0.000181586,-1.41894e-07,4.39839e-11,-4.80252e-15); //W=10.0 600-3600

    } else {
        std::cout<<"Unknown category: "<<postfix<<std::endl;
        return;
    }
    
    // C r e a t e   i n t e r p o l a t i n g   p d f
    // -----------------------------------------------
    
    // Create interpolation variable
    RooRealVar alpha("alpha","alpha",0,1.0) ;
    
    // Specify sampling density on observable and interpolation variable
    x.setBins(4000,"cache") ;
    alpha.setBins(2200,"cache") ;
    
    RooPlot* frame1[nMCpoints];
    RooPlot* frame2[nMCpoints];
    RooPlot* frame3[nMCpoints];
    TH1* hh[nMCpoints];
    
    TCanvas* c[nMCpoints];
    
    for (int iPoint = 0; iPoint!=nMCpoints-1; ++iPoint) {
    //for (int iPoint = 1; iPoint!=2; ++iPoint) {
            
        // Construct interpolating pdf in (x,a) represent g1(x) at a=a_min
        // and g2(x) at a=a_max
        RooIntegralMorph lmorph("lmorph","lmorph",*gMass[iPoint],*gMass[iPoint+1],x,alpha) ;
        
        // P l o t   i n t e r p o l a t i n g   p d f   a t   v a r i o u s   a l p h a
        // -----------------------------------------------------------------------------
        
        // Show end points as blue curves
        frame1[iPoint] = x.frame() ;
        gMass[iPoint]->plotOn(frame1[iPoint]) ;
        gMass[iPoint+1]->plotOn(frame1[iPoint]) ;
        
        int nPoints = int((masses[iPoint+1]-masses[iPoint])/step);
        for (int i=0; i!=nPoints+1; ++i) {
            //alpha=double(i)/double(nPoints);
            alpha.setVal(double(i)/double(nPoints)) ;
            lmorph.plotOn(frame1[iPoint],LineColor(kRed)) ;
            
            //RooDataSet* data2 = lmorph.generate(x,30000);
            
            double effcy = funcEff->Eval(masses[iPoint+1]-i*step);
            //double weight = effcy/30000.;
            double weight = effcy;
            //TH1D* distribs0 = new TH1D("distribs_5_10_0","",4000,0,4000);
            TH1D* distribs0 = (TH1D*)lmorph.createHistogram("distribs_X",x,Binning(4000,700,4700));

            
            //double effcy2 = distribs0->Integral(600,3600);
            
            //data2->fillHistogram(distribs0,x);
            //distribs0->Scale(weight/effcy2);
            distribs0->Scale(weight);
            //for (int k=0; k!=600; ++k)
            //    distribs0->SetBinContent(k+1,0);

            TFile* fileNew = new TFile(outDir+postfix+Form("/histos_sig_m%d.root",int(masses[iPoint+1]-i*step)),"RECREATE");
            distribs0->Write();
            std::cout << "wrote file " << fileNew->GetName() << std::endl;
            fileNew->Close();
            
            //delete data2;
            delete distribs0;
        }
        
        // S h o w   2 D   d i s t r i b u t i o n   o f   p d f ( x , a l p h a )
        // -----------------------------------------------------------------------
        
        // Create 2D histogram
        hh[iPoint] = lmorph.createHistogram("hh",x,Binning(40),YVar(alpha,Binning(40))) ;
        hh[iPoint]->SetLineColor(kBlue) ;
        
        
        // F i t   p d f   t o   d a t a s e t   w i t h   a l p h a = 0 . 8
        // -----------------------------------------------------------------
        
        // Generate a toy dataset at alpha = 0.8
        alpha=0.8 ;
        RooDataSet* data = lmorph.generate(x,1000) ;
        
        // Fit pdf to toy data
        lmorph.setCacheAlpha(kTRUE) ;
        lmorph.fitTo(*data,Verbose(kTRUE)) ;
        
        // Plot fitted pdf and data overlaid
        frame2[iPoint] = x.frame(Bins(1500)) ;
        data->plotOn(frame2[iPoint]) ;
        lmorph.plotOn(frame2[iPoint]) ;
        
        
        // S c a n   - l o g ( L )   v s   a l p h a
        // -----------------------------------------
        
        // Show scan -log(L) of dataset w.r.t alpha
        frame3[iPoint] = alpha.frame(Bins(100),Range(0.1,0.9)) ;
        
        // Make 2D pdf of histogram
        RooNLLVar nll("nll","nll",lmorph,*data) ;
        nll.plotOn(frame3[iPoint],ShiftToZero()) ;
        
        lmorph.setCacheAlpha(kFALSE) ;
        
        
        
        c[iPoint] = new TCanvas(Form("linearmorph_%d",iPoint),Form("linearmorph_%d",iPoint),700,700) ;
        c[iPoint]->Divide(2,2) ;
        c[iPoint]->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1[iPoint]->GetYaxis()->SetTitleOffset(1.6) ; frame1[iPoint]->Draw() ;
        c[iPoint]->cd(2) ; gPad->SetLeftMargin(0.20) ; hh[iPoint]->GetZaxis()->SetTitleOffset(2.5) ; hh[iPoint]->Draw("surf") ;
        c[iPoint]->cd(3) ; gPad->SetLeftMargin(0.15) ; frame3[iPoint]->GetYaxis()->SetTitleOffset(1.4) ; frame3[iPoint]->Draw() ;
        c[iPoint]->cd(4) ; gPad->SetLeftMargin(0.15) ; frame2[iPoint]->GetYaxis()->SetTitleOffset(1.4) ; frame2[iPoint]->Draw() ;
        c[iPoint]->Modified(); c[iPoint]->Update();
    }
    
    
    return ;
    
}
