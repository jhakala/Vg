#include "TROOT.h"
//#include "tdrstyle.C"
#include "TCanvas.h"
#include "TFile.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TGraphAsymmErrors.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TTree.h"
#include "TSystem.h"
#include "TPad.h"


void drawBias () {
    
    //setTDRStyle();
    //gStyle->SetOptStat(1);
    //gStyle->SetOptTitle(1);
    //gStyle->SetFitFormat("2.2g");
    //gStyle->SetPadBottomMargin(0.2);
    
    
    //const int nDirs = 6;
    //Color_t cols[nDirs] = {kBlack, kRed+1, kOrange-3, kGreen+1, kAzure+7 , kMagenta};
    
    const int nDirs = 3;
    //Color_t cols[nDirs] = {kRed, kRed+2, kOrange+7, kRed-8, kGreen+2, kCyan+1, kAzure};
    Color_t cols[nDirs] = {kGreen+2, kCyan+1, kAzure};
    
    //const int nDirs = 1;
    //Color_t cols[nDirs] = {kBlack};
    
    //const int nDirs = 2;
    //Color_t cols[nDirs] = {kBlack, kRed+1};

    //TFile* outfile = new TFile("biasPlot_antibtag_dijet2_test.root", "RECREATE");
    //TString dirNames[nDirs] = {
    //  //"bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_atlas1",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_vvdijet1",
    //  //"bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_exp1",
    //  //"bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_expow1",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_expow3",
    //  //"bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_atlas2"
    //};
    //
    // TString names[nDirs] = {
    //   //"atlas1",
    //   "vvdijet1",
    //   //"exp1",
    //   //"expow1",
    //   "expow3",
    //   //"atlas2"
    // };
    //TFile* outfile = new TFile("biasPlot_btag_dijet2.root", "RECREATE");
    

    //TFile* outfile = new TFile("biasPlot_antibtag_dijet2_new2.root", "RECREATE");
    //TString dirNames[nDirs] = {
    //  //"bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_atlas1",
    //  //"bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_vvdijet1",
    //  //"bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_exp1",
    //  //"bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_expow1",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_expow2",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_vvdijet2",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_dijet3"
    //};
    //
    // TString names[nDirs] = {
    //   //"atlas1",
    //   //"vvdijet1",
    //   //"exp1",
    //   //"expow1",
    //   "expow2",
    //   "vvdijet2",
    //   "dijet3"
    // };
    
    //TFile* outfile = new TFile("biasPlot_antibtag_vvdijet1.root", "RECREATE");
    //TString dirNames[nDirs] = {
    //  "bias_antibtag_nom-bkg_vvdijet1_alt-bkg_dijetsimple2",
    //  //"bias_antibtag_nom-bkg_vvdijet1_alt-bkg_atlas1",
    //  //"bias_antibtag_nom-bkg_vvdijet1_alt-bkg_pow1",
    //  "bias_antibtag_nom-bkg_vvdijet1_alt-bkg_exp1",
    //  "bias_antibtag_nom-bkg_vvdijet1_alt-bkg_expow1",
    //  "bias_antibtag_nom-bkg_vvdijet1_alt-bkg_expow2",
    //  "bias_antibtag_nom-bkg_vvdijet1_alt-bkg_expow3",
    //  "bias_antibtag_nom-bkg_vvdijet1_alt-bkg_vvdijet2"
    //  //"bias_antibtag_nom-bkg_vvdijet1_alt-bkg_atlas2"
    //};
    //
    // TString names[nDirs] = {
    //   "dijet2",
    //   //"atlas1",
    //   //"pow1",
    //   "exp1",
    //   "expow1",
    //   "expow2",
    //   "expow3",
    //   "vvdijet2"
    //   //"atlas2"
    // };


    //TFile* outfile = new TFile("biasPlot_btag_vvdijet1.root", "RECREATE");
    //TString dirNames[nDirs] = {
    //  "bias_btag_nom-bkg_vvdijet1_alt-bkg_atlas1",
    //  "bias_btag_nom-bkg_vvdijet1_alt-bkg_pow1",
    //  "bias_btag_nom-bkg_vvdijet1_alt-bkg_exp1",
    //  "bias_btag_nom-bkg_vvdijet1_alt-bkg_expow1",
    //  "bias_btag_nom-bkg_vvdijet1_alt-bkg_vvdijet2",
    //  "bias_btag_nom-bkg_vvdijet1_alt-bkg_atlas2"
    //};
    //
    // TString names[nDirs] = {
    //   "atlas1",
    //   "pow1",
    //   "exp1",
    //   "expow1",
    //   "vvdijet2",
    //   "atlas2"
    // };

    //TFile* outfile = new TFile("biasPlot_antibtag_dijet2_new.root", "RECREATE");
    //TString dirNames[nDirs] = {
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_atlas1",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_vvdijet1",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_exp1",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_expow1",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_expow3",
    //  "bias_antibtag_nom-bkg_dijetsimple2_alt-bkg_atlas2"
    //};
    //
    // TString names[nDirs] = {
    //   "atlas1",
    //   "vvdijet1",
    //   "exp1",
    //   "expow1",
    //   "expow3",
    //   "atlas2"
    // };
    TFile* outfile = new TFile("biasPlot_btag_dijet2_new2.root", "RECREATE");
    TString dirNames[nDirs] = {
      "bias_btag_nom-bkg_dijetsimple2_alt-bkg_atlas1",
      //"bias_btag_nom-bkg_dijetsimple2_alt-bkg_exp1",
      "bias_btag_nom-bkg_dijetsimple2_alt-bkg_vvdijet2",
      //"bias_btag_nom-bkg_dijetsimple2_alt-bkg_expow1",
      "bias_btag_nom-bkg_dijetsimple2_alt-bkg_expow2"
      //"bias_btag_nom-bkg_dijetsimple2_alt-bkg_atlas2"
    };
    
    TString names[nDirs] = {
      "atlas1",
      //"exp1",
      "vvdijet2",
      //"expow1",
      "expow2"
      //"expow3",
      //"atlas2"
    };
    
    
    const int nPoints = 80;//46;

    TCanvas* c1[nDirs][nPoints];
    TFile * f[nDirs][nPoints];
    TTree* tree_fit_sb[nDirs][nPoints];
    
    TH1D* hists[nDirs][nPoints];
    
    TGraphErrors* biasG[nDirs];
    TGraphErrors* biasG2[nDirs];
    
    TCanvas* c2 = new TCanvas("p2","p2",700,700);
    TH1F *hr = c2->DrawFrame(500,-1,4100,1);
    hr->SetXTitle("m_{X} (GeV)");
    hr->SetYTitle("mean");

    TCanvas* c2a = new TCanvas("c2a","c2a",700,700);
    TH1F *hra = c2a->DrawFrame(500,-1,4100,1);
    hra->SetXTitle("m_{X} (GeV)");
    hra->SetYTitle("medians");
    
    TLegend* leg = new TLegend(0.7,0.895,0.895,0.705,"means","NDC");
    leg->SetTextFont(42);
    TLegend* leg2 = new TLegend(0.7,0.895,0.895,0.705,"medians","NDC");
    leg2->SetTextFont(42);
    
    for (int dd=0; dd!=nDirs; ++dd) {
        biasG[dd] = new TGraphErrors(nPoints);
        biasG2[dd] = new TGraphErrors(nPoints);
        biasG[dd]->SetMarkerColor(cols[dd]);
        biasG[dd]->SetMarkerStyle(20);
        biasG[dd]->SetMarkerSize(.3);
        biasG[dd]->SetLineColor(cols[dd]);
        biasG2[dd]->SetMarkerColor(cols[dd]);
        biasG2[dd]->SetMarkerStyle(20);
        biasG2[dd]->SetMarkerSize(.3);
        biasG2[dd]->SetLineColor(cols[dd]);
        
        
        leg->AddEntry(biasG[dd],names[dd],"p");
        leg2->AddEntry(biasG2[dd],names[dd],"p");
        
        Double_t quantile,prob;
        prob = 0.5;
        //int masses[] = {650, 710, 750, 810, 850, 900, 930, 1010, 1030, 1110, 1160, 1210, 1250, 1300, 1350, 1410, 1460, 1510};
        for (int i=0; i!=nPoints; ++i) {
            //std::cout<< "starting masses[i]: " << masses[i] << std::endl;
            //std::cout<< "dirNames[dd]: " << dirNames[dd] << std::endl ;
            //if (650+i*100 == 1750) continue;
            //std::printf("\nForm... =  /mlfitoutput%d.root\n", masses[i]);
            int mass = 700+30*i;
            //TString nameF = dirNames[dd]+Form("/mlfitoutput%d.root",masses[i]);
            //TString nameF = Form("./mlfitoutput%d.root",masses[i]);
            //higgsCombinebiasStudy-920.MaxLikelihoodFit.mH920.123456.root    mlfitbiasStudy-930.root
            TString nameF = dirNames[dd]+Form("/mlfitbiasStudy-%d.root",mass);
            if (gSystem->AccessPathName(nameF)) continue;
            c1[dd][i] = new TCanvas(Form("c_%d_%d",dd,i),Form("c_%d_%d",dd,i), 700, 700);
            f[dd][i] = new TFile(nameF);
            if(!f[dd][i]) continue;
            std::cout << "found f[dd][i]: " << nameF << std::endl;
            
            if (f[dd][i]->Get("tree_fit_sb")==0) continue;
            tree_fit_sb[dd][i] = static_cast<TTree*>(f[dd][i]->Get("tree_fit_sb"));
            std::cout << "  got tree from " << nameF << std::endl;
            
            //TString name = Form("bias_%d_GeV-",masses[i])+dirNames[dd];
            TString name = Form("bias_%d_GeV-",mass)+dirNames[dd];
            //TString title = Form("bias at %d GeV for ",masses[i])+dirNames[dd];
            TString title = Form("bias at %d GeV for ",mass)+dirNames[dd];
            hists[dd][i] = new TH1D(name,title+";#frac{#mu_{fit}-0.0}{#sigma_{fit}};entries/0.25",100,-10,10);

           
            std::cout << "  made histogram " << hists[dd][i]->GetName() << std::endl;
            
            tree_fit_sb[dd][i]->Draw("(mu>0)*mu/muHiErr + (mu<=0)*mu/muLoErr >>"+name,"fit_status == 0","pe");
            //tree_fit_sb[dd][i]->Draw("mu/muErr >>"+name,"fit_status == 0","pe");
            //std::cout << "   drew tree (mu-0)/muErr>>" << name << std::endl;
            hists[dd][i]->Fit("gaus","LM");
            //hists[dd][i]->Fit("gaus");
            std::cout << "   Fit the tree" << std::endl;
            hists[dd][i]->GetXaxis()->SetTitleOffset(1.2);
            std::cout << "   Formatting the hist " << std::endl;
            //c1[dd][i]->SaveAs(dirNames[dd]+Form("_%d.pdf",masses[i]));
            //c1[dd][i]->SaveAs(dirNames[dd]+Form("biasPdfs/_%d.pdf",mass));
            
            //std::cout << "  saved file " << dirNames[dd]+Form("_%d.pdf",masses[i]) << std::endl;
            
            
            //biasG[dd]->SetPoint(i,masses[i],hists[dd][i]->GetFunction("gaus")->GetParameter(1));
            std::cout << "   adding point with value " << hists[dd][i]->GetFunction("gaus")->GetParameter(1) << " at mass " << mass << std::endl;
            biasG[dd]->SetPoint(i,mass,hists[dd][i]->GetFunction("gaus")->GetParameter(1));
            biasG[dd]->SetPointError(i,0,hists[dd][i]->GetFunction("gaus")->GetParError(1));
            
            hists[dd][i]->GetQuantiles(1,&quantile,&prob);
            std::cout << "   got quantiles from " << hists[dd][i]->GetName() << std::endl;
            //biasG2[dd]->SetPoint(i,masses[i],quantile); // //GetMean
            biasG2[dd]->SetPoint(i,mass,quantile); // //GetMean
            //biasG2[dd]->SetPoint(i,650+i*100,hists[dd][i]->GetMean()); // //GetMean
            biasG2[dd]->SetPointError(i,0,hists[dd][i]->GetRMS()/sqrt(hists[dd][i]->GetEntries()));
            //std::cout<< "done with masses[i]: " << masses[i] << std::endl;
            
            
        }
        c2->cd();
        biasG[dd]->Draw("pe same");
        c2a->cd();
        biasG2[dd]->Draw("pe same");
    }

    c2->cd();
    leg->Draw("same");
    c2a->cd();
    leg2->Draw("same");
    outfile->cd();
    c2->Write();
    c2a->Write();
    outfile->Close();
    
}
