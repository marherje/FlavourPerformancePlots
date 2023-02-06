#include <TPaveStats.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
#include "../../../style/Style.C"
#include "../../../style/Labels.C"




void Labels(TString pol){
  QQBARLabel(0.86,0.952,"");
  QQBARLabel2(0.3,0.965, "Retraining with 500 GeV samples",kGray+2);

}


void JetTag_Retraining(int cut,TString process,TString kvalue) {

  
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.2);
  gStyle->SetMarkerSize(0.2);
  // TGaxis::SetMaxDigits(2);

  TString cutname=TString::Format("cuts%i",cut);
  TString filename = "../Retraining_Results/jettag_"+cutname+"_"+process+"_eL_pR_"+kvalue+"_500GeV.root";
  TFile *f = new TFile(filename);
  TH1F*  btag[40][2];
  TH1F*  ctag[40][2];
  for(int i=0; i<40; i++) {
    btag[i][0]= (TH1F*)f->Get(TString::Format("h_jet_btag_%i",i));
    ctag[i][0]= (TH1F*)f->Get(TString::Format("h_jet_ctag_%i",i));
  }

  TString filename2 = "../Retraining_Results/jettag_"+cutname+"_"+process+"_eR_pL_"+kvalue+"_500GeV.root";
  TFile *f2 = new TFile(filename2);

  for(int i=0; i<40; i++) {
    btag[i][1]= (TH1F*)f2->Get(TString::Format("h_jet_btag_%i",i));
    ctag[i][1]= (TH1F*)f2->Get(TString::Format("h_jet_ctag_%i",i));
  }

  float x[40], eff_b[2][3][40], eff_c[2][3][40];
  float eff2_b[2][3][40], eff2_c[2][3][40];
  
  float eff_b_error[2][3][40], eff_c_error[2][3][40];
  float pur_b_error[2][40], pur_c_error[2][40], pur_b_error2[2][40], pur_c_error2[2][40];
  
  int n=0;
  for(int i=0;i<40; i++) {
    x[i]=i*0.025;
    float ntotal[3];
    float nb[3];
    float nc[3];
    for(int iflav=0;iflav<3; iflav++){
      int quark=0;
      if(iflav==1) quark=4;
      if(iflav==2) quark=5;

      for(int ipol=0; ipol<2; ipol++){
	ntotal[iflav]=btag[0][ipol]->GetBinContent(quark+1);
	
	nb[iflav]=btag[i][ipol]->GetBinContent(quark+1);
	nc[iflav]=ctag[i][ipol]->GetBinContent(quark+1);

	eff_b[ipol][iflav][i]=100.*nb[iflav]/ntotal[iflav];
	eff_c[ipol][iflav][i]=100.*nc[iflav]/ntotal[iflav];
	eff2_b[ipol][iflav][i]=100.-100.*nb[iflav]/ntotal[iflav];
	eff2_c[ipol][iflav][i]=100.-100.*nc[iflav]/ntotal[iflav];
	
	eff_b_error[ipol][iflav][i]=(100./ntotal[iflav])*pow(nb[iflav]+(nb[iflav]*nb[iflav])/ntotal[iflav],0.5);
	eff_c_error[ipol][iflav][i]=(100./ntotal[iflav])*pow(nc[iflav]+(nc[iflav]*nc[iflav])/ntotal[iflav],0.5);
      }
    }
    n++;
  }
 
  TGraph* efficiency_b_b_eL = new TGraphErrors(n,x,eff_b[0][2],0,eff_b_error[0][2]);
  TGraph* efficiency_c_b_eL = new TGraphErrors(n,x,eff2_b[0][1],0,eff_b_error[0][1]);
  TGraph* efficiency_uds_b_eL = new TGraphErrors(n,x,eff2_b[0][0],0,eff_b_error[0][0]);

  TGraph* efficiency_b_b_eR = new TGraphErrors(n,x,eff_b[1][2],0,eff_b_error[1][2]);
  TGraph* efficiency_c_b_eR = new TGraphErrors(n,x,eff2_b[1][1],0,eff_b_error[1][1]);
  TGraph* efficiency_uds_b_eR = new TGraphErrors(n,x,eff2_b[1][0],0,eff_b_error[1][0]);

  TCanvas* c_eff_b = new TCanvas("c_eff_b","c_eff_b",800,800);
  c_eff_b->cd(1);
  c_eff_b->SetGrid();
  efficiency_b_b_eL->GetXaxis()->SetTitle("btag_{cut}");
  efficiency_b_b_eL->GetYaxis()->SetTitle("[%]");
  efficiency_b_b_eL->GetYaxis()->SetTitleOffset(1.25);
  efficiency_b_b_eL->GetXaxis()->SetTitleOffset(1.);
  efficiency_b_b_eL->GetYaxis()->SetRangeUser(0,100);

  efficiency_b_b_eL->SetLineColor(4);
  efficiency_b_b_eL->SetLineWidth(2);
  efficiency_b_b_eL->SetLineStyle(1);
  efficiency_b_b_eL->Draw("alp");

  efficiency_c_b_eL->SetLineColor(1);
  efficiency_c_b_eL->SetLineWidth(2);
  efficiency_c_b_eL->SetLineStyle(1);
  efficiency_c_b_eL->Draw("lp");

  efficiency_uds_b_eL->SetLineColor(2);
  efficiency_uds_b_eL->SetLineWidth(2);
  efficiency_uds_b_eL->SetLineStyle(1);
  efficiency_uds_b_eL->Draw("lp");

  efficiency_b_b_eR->SetLineColor(4);
  efficiency_b_b_eR->SetLineWidth(3);
  efficiency_b_b_eR->SetLineStyle(2);
  efficiency_b_b_eR->Draw("lp");

  efficiency_c_b_eR->SetLineColor(1);
  efficiency_c_b_eR->SetLineWidth(3);
  efficiency_c_b_eR->SetLineStyle(2);
  efficiency_c_b_eR->Draw("lp");

  efficiency_uds_b_eR->SetLineColor(2);
  efficiency_uds_b_eR->SetLineWidth(3);
  efficiency_uds_b_eR->SetLineStyle(2);
  efficiency_uds_b_eR->Draw("lp");
  
  
  Labels("");
  
  TLegend *leg_b = new TLegend(0.4,0.25,0.6,0.45);
  leg_b->SetTextSize(0.035);
  leg_b->SetTextFont(42);
  leg_b->AddEntry(efficiency_b_b_eL,"#varepsilon_{b}","lp");
  leg_b->AddEntry(efficiency_c_b_eL,"1-#varepsilon_{c}","lp");
  leg_b->AddEntry(efficiency_uds_b_eL,"1-#varepsilon_{uds}","lp");
  leg_b->AddEntry(efficiency_c_b_eL,"Left Pol","lp");
  leg_b->AddEntry(efficiency_c_b_eR,"Right Pol","lp");
  leg_b->SetFillColor(0);
  leg_b->SetLineColor(0);
  leg_b->SetShadowColor(0);
  leg_b->Draw();

  c_eff_b->SaveAs("c_eff_b.png");

  ///---------------------------------------------
  TGraph* efficiency_c_c_eL = new TGraphErrors(n,x,eff_c[0][1],0,eff_c_error[0][1]);
  TGraph* efficiency_b_c_eL = new TGraphErrors(n,x,eff2_c[0][2],0,eff_c_error[0][2]);
  TGraph* efficiency_uds_c_eL = new TGraphErrors(n,x,eff2_c[0][0],0,eff_c_error[0][0]);

  TGraph* efficiency_c_c_eR = new TGraphErrors(n,x,eff_c[1][1],0,eff_c_error[1][1]);
  TGraph* efficiency_b_c_eR = new TGraphErrors(n,x,eff2_c[1][2],0,eff_c_error[1][2]);
  TGraph* efficiency_uds_c_eR = new TGraphErrors(n,x,eff2_c[1][0],0,eff_c_error[1][0]);
  

  TCanvas* c_eff_c = new TCanvas("c_eff_c","c_eff_c",800,800);
  c_eff_c->cd(1);
  c_eff_c->SetGrid();
  efficiency_c_c_eL->GetXaxis()->SetTitle("ctag_{cut}");
  efficiency_c_c_eL->GetYaxis()->SetTitle("[%]");
  efficiency_c_c_eL->GetYaxis()->SetTitleOffset(1.25);
  efficiency_c_c_eL->GetXaxis()->SetTitleOffset(1.);
  efficiency_c_c_eL->GetYaxis()->SetRangeUser(0,100);

  efficiency_c_c_eL->SetLineColor(4);
  efficiency_c_c_eL->SetLineWidth(2);
  efficiency_c_c_eL->SetLineStyle(1);
  efficiency_c_c_eL->Draw("alp");

  efficiency_b_c_eL->SetLineColor(1);
  efficiency_b_c_eL->SetLineWidth(2);
  efficiency_b_c_eL->SetLineStyle(1);
  efficiency_b_c_eL->Draw("lp");

  efficiency_uds_c_eL->SetLineColor(2);
  efficiency_uds_c_eL->SetLineWidth(2);
  efficiency_uds_c_eL->SetLineStyle(1);
  efficiency_uds_c_eL->Draw("lp");

  efficiency_c_c_eR->SetLineColor(4);
  efficiency_c_c_eR->SetLineWidth(3);
  efficiency_c_c_eR->SetLineStyle(2);
  efficiency_c_c_eR->Draw("lp");

  efficiency_b_c_eR->SetLineColor(1);
  efficiency_b_c_eR->SetLineWidth(3);
  efficiency_b_c_eR->SetLineStyle(2);
  efficiency_b_c_eR->Draw("lp");

  efficiency_uds_c_eR->SetLineColor(2);
  efficiency_uds_c_eR->SetLineWidth(3);
  efficiency_uds_c_eR->SetLineStyle(2);
  efficiency_uds_c_eR->Draw("lp");
  
  
  Labels("");
  
  TLegend *leg_c = new TLegend(0.4,0.25,0.6,0.45);
  leg_c->SetTextSize(0.035);
  leg_c->SetTextFont(42);
  leg_c->AddEntry(efficiency_c_c_eL,"#varepsilon_{c}","lp");
  leg_c->AddEntry(efficiency_b_c_eL,"1-#varepsilon_{b}","lp");
  leg_c->AddEntry(efficiency_uds_c_eL,"1-#varepsilon_{uds}","lp");
  leg_c->AddEntry(efficiency_b_c_eL,"Left Pol","lp");
  leg_c->AddEntry(efficiency_b_c_eR,"Right Pol","lp");
  leg_c->SetFillColor(0);
  leg_c->SetLineColor(0);
  leg_c->SetShadowColor(0);
  leg_c->Draw();

  
  c_eff_c->SaveAs("c_eff_c.png");
}
