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




void Labels(TString pol, TString cat, TString quality){
  QQBARLabel(0.86,0.952,"");
  // QQBARLabel2(0.3,0.97, "e^{-}e^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 250fb^{-1}",kGray+2);
  if(pol=="eL")
    QQBARLabel2(0.3,0.965, "e^{-}e^{+} #rightarrow c#bar{c} mc-2020",kGray+2);
  else 
    if(pol=="eR")
      QQBARLabel2(0.3,0.965, "e_{R}^{-}e_{L}^{+} #rightarrow c#bar{c} mc-2020",kGray+2);
    else 
      QQBARLabel2(0.2,0.965, "e^{-}e^{+} #rightarrow q#bar{q} mc-2022 (500 GeV)",kGray+2);

  TString cat_string;
  if(cat=="all")cat_string="All Categories";
  else if(cat=="catA")cat_string="Category A";
  else if(cat=="catB")cat_string="Category B";
  else if(cat=="catC")cat_string="Category C";
  else if(cat=="catD")cat_string="Category D";
  
  if(cat=="all")QQBARLabel2(0.4,0.55,cat_string ,kGray+4);
  else QQBARLabel2(0.7,0.65,cat_string ,kGray+4);
  //if(cat == "all") leg_b= new TLegend(0.4,0.3,0.6,0.5);
  //if(cat != "all") leg_b= new TLegend(0.7,0.4,0.9,0.6);

  TString quality_string;
  if(quality=="Old")quality_string="Previous weights: 2f250";
  else if(quality=="FullOpt")quality_string="New weights: 2f500 (PSO-Opt)";
  QQBARLabel2(0.1,0.075,quality_string ,kGray+4);
  
  QQBARLabel2(0.6,0.965, "Work in progress",kRed+2);
}


void JetTag(int cut,TString kvalue, TString cat, TString quality) {

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
  TString filename = "../results/jettag_"+cutname+"_2f_hadronic_sample_"+cat+"_BDT_"+quality+"_eL_pR_Kgamma"+kvalue+"_500GeV.root";
  TFile *f = new TFile(filename);
  TH1F*  btag[40][2];
  TH1F*  ctag[40][2];
  for(int i=0; i<40; i++) {
    btag[i][0]= (TH1F*)f->Get(TString::Format("h_jet_btag_%i",i));
    ctag[i][0]= (TH1F*)f->Get(TString::Format("h_jet_ctag_%i",i));
  }
  TString filename2 = "../results/jettag_"+cutname+"_2f_hadronic_sample_"+cat+"_BDT_"+quality+"_eR_pL_Kgamma"+kvalue+"_500GeV.root";
  TFile *f2 = new TFile(filename2);

  for(int i=0; i<40; i++) {
    btag[i][1]= (TH1F*)f2->Get(TString::Format("h_jet_btag_%i",i));
    ctag[i][1]= (TH1F*)f2->Get(TString::Format("h_jet_ctag_%i",i));
  }

  float x[40], eff_b[2][3][40], eff_c[2][3][40];
  float eff2_b[2][3][40], eff2_c[2][3][40];
  float pur_b[2][3][40], pur_c[2][3][40];
  float f1score_b[2][3][40], f1score_c[2][3][40];

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
	pur_b[ipol][iflav][i]=100.*(nb[iflav]/(nb[0]+nb[1]+nb[2]));
	pur_c[ipol][iflav][i]=100.*(nc[iflav]/(nc[0]+nc[1]+nc[2]));
	//F1Score 
	float FP_b; //False Positive b
	float FN_b; //False Negative b
	FN_b=ntotal[iflav]-nb[iflav];
	if(iflav==0)FP_b=nb[1]+nb[2];
	else if(iflav==1)FP_b=nb[0]+nb[2];
	else if(iflav==2)FP_b=nb[0]+nb[1];
	f1score_b[ipol][iflav][i]=nb[iflav]/(nb[iflav]+0.5*(FP_b+FN_b));
	float FP_c; //False Positive c
        float FN_c; //False Negative c
        FN_c=ntotal[iflav]-nc[iflav];
        if(iflav==0)FP_c=nc[1]+nc[2];
        else if(iflav==1)FP_c=nc[0]+nc[2];
        else if(iflav==2)FP_c=nc[0]+nc[1];
        f1score_c[ipol][iflav][i]=nc[iflav]/(nc[iflav]+0.5*(FP_c+FN_c));
      }
    }
    n++;
  }
 
  TGraph* efficiency_b_b_eL = new TGraph(n,x,eff_b[0][2]);
  TGraph* efficiency_c_b_eL = new TGraph(n,x,eff2_b[0][1]);
  TGraph* efficiency_uds_b_eL = new TGraph(n,x,eff2_b[0][0]);

  TGraph* efficiency_b_b_eR = new TGraph(n,x,eff_b[1][2]);
  TGraph* efficiency_c_b_eR = new TGraph(n,x,eff2_b[1][1]);
  TGraph* efficiency_uds_b_eR = new TGraph(n,x,eff2_b[1][0]);

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
  
  
  Labels("",cat,quality);
  
  TLegend *leg_b;
  if(cat == "all") leg_b= new TLegend(0.4,0.3,0.6,0.5);
  if(cat != "all") leg_b= new TLegend(0.7,0.4,0.9,0.6);
  
  //0.7,0.4,0.9,0.6);
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

  //c_eff_b->SaveAs("c_eff_b.png");

  ///---------------------------------------------
  TGraph* efficiency_c_c_eL = new TGraph(n,x,eff_c[0][1]);
  TGraph* efficiency_b_c_eL = new TGraph(n,x,eff2_c[0][2]);
  TGraph* efficiency_uds_c_eL = new TGraph(n,x,eff2_c[0][0]);

  TGraph* efficiency_c_c_eR = new TGraph(n,x,eff_c[1][1]);
  TGraph* efficiency_b_c_eR = new TGraph(n,x,eff2_c[1][2]);
  TGraph* efficiency_uds_c_eR = new TGraph(n,x,eff2_c[1][0]);

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
  
  
  Labels("",cat,quality);
  
  TLegend *leg_c;
  if(cat == "all") leg_c= new TLegend(0.4,0.3,0.6,0.5);
  if(cat != "all") leg_c= new TLegend(0.7,0.4,0.9,0.6);
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

  
  //c_eff_c->SaveAs("c_eff_c.png");

  //--------------
  //Purity

  TGraph* purity_b_b_eL = new TGraph(n,eff_b[0][2],pur_b[0][2]);
  TGraph* purity_b_b_eR = new TGraph(n,eff_b[1][2],pur_b[1][2]);
  TCanvas* c_pur_b = new TCanvas("c_pur_b","c_pur_b",800,800);
  c_pur_b->cd(1);
  c_pur_b->SetGrid();
  purity_b_b_eL->GetXaxis()->SetTitle("b-quark efficiency (%)");
  purity_b_b_eL->GetYaxis()->SetTitle("b-quark purity (%)");
  purity_b_b_eL->GetYaxis()->SetTitleOffset(1.25);
  purity_b_b_eL->GetXaxis()->SetTitleOffset(1.);
  purity_b_b_eL->GetYaxis()->SetRangeUser(0,100);
  purity_b_b_eL->SetLineColor(4);
  purity_b_b_eL->SetLineWidth(2);
  purity_b_b_eL->SetLineStyle(1);
  purity_b_b_eL->Draw("alp");
  purity_b_b_eR->SetLineColor(3);
  purity_b_b_eR->SetLineWidth(2);
  purity_b_b_eR->SetLineStyle(2);
  purity_b_b_eR->Draw("lp");

  Labels("",cat,quality);
  TLegend *leg_pb;
  leg_pb= new TLegend(0.4,0.3,0.6,0.4);
  leg_pb->SetTextSize(0.035);
  leg_pb->SetTextFont(42);
  leg_pb->AddEntry(purity_b_b_eL,"Left Pol","lp");
  leg_pb->AddEntry(purity_b_b_eR,"Right Pol","lp");
  leg_pb->SetFillColor(0);
  leg_pb->SetLineColor(0);
  leg_pb->SetShadowColor(0);
  leg_pb->Draw();
  
  TGraph* purity_c_c_eL = new TGraph(n,eff_c[0][1],pur_c[0][1]);
  TGraph* purity_c_c_eR = new TGraph(n,eff_c[1][1],pur_c[1][1]);
  TCanvas* c_pur_c = new TCanvas("c_pur_c","c_pur_c",800,800);
  c_pur_c->cd(1);
  c_pur_c->SetGrid();
  purity_c_c_eL->GetXaxis()->SetTitle("c-quark efficiency (%)");
  purity_c_c_eL->GetYaxis()->SetTitle("c-quark purity (%)");
  purity_c_c_eL->GetYaxis()->SetTitleOffset(1.25);
  purity_c_c_eL->GetXaxis()->SetTitleOffset(1.);
  purity_c_c_eL->GetYaxis()->SetRangeUser(0,100);
  purity_c_c_eL->SetLineColor(4);
  purity_c_c_eL->SetLineWidth(2);
  purity_c_c_eL->SetLineStyle(1);
  purity_c_c_eL->Draw("alp");
  purity_c_c_eR->SetLineColor(3);
  purity_c_c_eR->SetLineWidth(2);
  purity_c_c_eR->SetLineStyle(2);
  purity_c_c_eR->Draw("lp");

  Labels("",cat,quality);
  TLegend *leg_pc;
  leg_pc= new TLegend(0.4,0.3,0.6,0.4);
  leg_pc->SetTextSize(0.035);
  leg_pc->SetTextFont(42);
  leg_pc->AddEntry(purity_c_c_eL,"Left Pol","lp");
  leg_pc->AddEntry(purity_c_c_eR,"Right Pol","lp");
  leg_pc->SetFillColor(0);
  leg_pc->SetLineColor(0);
  leg_pc->SetShadowColor(0);
  leg_pc->Draw();


  //-----------
  //F1Score
  
  TGraph* f1score_b_b_eL = new TGraph(n,x,f1score_b[0][2]);
  TGraph* f1score_b_b_eR = new TGraph(n,x,f1score_b[1][2]);
  TCanvas* c_f1score_b = new TCanvas("c_f1score_b","c_f1score_b",800,800);
  c_f1score_b->cd(1);
  c_f1score_b->SetGrid();
  f1score_b_b_eL->GetXaxis()->SetTitle("btag_{cut}");
  f1score_b_b_eL->GetYaxis()->SetTitle("F1-Score");
  f1score_b_b_eL->GetYaxis()->SetTitleOffset(1.25);
  f1score_b_b_eL->GetXaxis()->SetTitleOffset(1.);
  f1score_b_b_eL->GetYaxis()->SetRangeUser(0,1);
  f1score_b_b_eL->SetLineColor(4);
  f1score_b_b_eL->SetLineWidth(2);
  f1score_b_b_eL->SetLineStyle(1);
  f1score_b_b_eL->Draw("alp");
  f1score_b_b_eR->SetLineColor(3);
  f1score_b_b_eR->SetLineWidth(2);
  f1score_b_b_eR->SetLineStyle(1);
  f1score_b_b_eR->Draw("lp");

  Labels("",cat,quality);
  TLegend *leg_fb;
  leg_fb= new TLegend(0.4,0.3,0.6,0.4);
  leg_fb->SetTextSize(0.035);
  leg_fb->SetTextFont(42);
  leg_fb->AddEntry(f1score_b_b_eL,"Left Pol","lp");
  leg_fb->AddEntry(f1score_b_b_eR,"Right Pol","lp");
  leg_fb->SetFillColor(0);
  leg_fb->SetLineColor(0);
  leg_fb->SetShadowColor(0);
  leg_fb->Draw();

  TGraph* f1score_c_c_eL = new TGraph(n,x,f1score_c[0][1]);
  TGraph* f1score_c_c_eR = new TGraph(n,x,f1score_c[1][1]);
  TCanvas* c_f1score_c = new TCanvas("c_f1score_c","c_f1score_c",800,800);
  c_f1score_c->cd(1);
  c_f1score_c->SetGrid();
  f1score_c_c_eL->GetXaxis()->SetTitle("ctag_{cut}");
  f1score_c_c_eL->GetYaxis()->SetTitle("F1-Score");
  f1score_c_c_eL->GetYaxis()->SetTitleOffset(1.25);
  f1score_c_c_eL->GetXaxis()->SetTitleOffset(1.);
  f1score_c_c_eL->GetYaxis()->SetRangeUser(0,1);
  f1score_c_c_eL->SetLineColor(4);
  f1score_c_c_eL->SetLineWidth(2);
  f1score_c_c_eL->SetLineStyle(1);
  f1score_c_c_eL->Draw("alp");
  f1score_c_c_eR->SetLineColor(3);
  f1score_c_c_eR->SetLineWidth(2);
  f1score_c_c_eR->SetLineStyle(1);
  f1score_c_c_eR->Draw("lp");

  Labels("",cat,quality);
  TLegend *leg_fc;
  leg_fc= new TLegend(0.4,0.3,0.6,0.4);
  leg_fc->SetTextSize(0.035);
  leg_fc->SetTextFont(42);
  leg_fc->AddEntry(f1score_c_c_eL,"Left Pol","lp");
  leg_fc->AddEntry(f1score_c_c_eR,"Right Pol","lp");
  leg_fc->SetFillColor(0);
  leg_fc->SetLineColor(0);
  leg_fc->SetShadowColor(0);
  leg_fc->Draw();
}
