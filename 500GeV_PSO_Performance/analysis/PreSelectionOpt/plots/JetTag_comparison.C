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




void Labels(TString pol, TString cat, int cut){
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
  
  TString cut_string;
  if(cut==0)cut_string="No ISR removal";
  if(cut==7)cut_string="With ISR removal";
  QQBARLabel2(0.1,0.05,cut_string ,kGray+4);
	      
  QQBARLabel2(0.6,0.965, "Work in progress",kRed+2);
}


void JetTag_comparison(int cut,TString kvalue, TString cat, TString OldTag, TString NewTag) {

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
  TString filename_old = "../results/jettag_"+cutname+"_2f_hadronic_sample_"+cat+"_BDT_"+OldTag+"_eL_pR_Kgamma"+kvalue+"_500GeV.root";
  TFile *f_old = new TFile(filename_old);
  TString filename2_old = "../results/jettag_"+cutname+"_2f_hadronic_sample_"+cat+"_BDT_"+OldTag+"_eR_pL_Kgamma"+kvalue+"_500GeV.root";
  TFile *f2_old = new TFile(filename2_old);
  TString filename_new = "../results/jettag_"+cutname+"_2f_hadronic_sample_"+cat+"_BDT_"+NewTag+"_eL_pR_Kgamma"+kvalue+"_500GeV.root";
  TFile *f_new = new TFile(filename_new);
  TString filename2_new = "../results/jettag_"+cutname+"_2f_hadronic_sample_"+cat+"_BDT_"+NewTag+"_eR_pL_Kgamma"+kvalue+"_500GeV.root";
  TFile *f2_new = new TFile(filename2_new);

  // For legends:
  TString oldtag;
  if(OldTag=="Old")oldtag="2f250";
  else if(OldTag=="FullOpt")oldtag="2f500-PSO";
  else if(OldTag=="dEdx")oldtag="2f500-dEdx";
  TString newtag;
  if(NewTag=="Old")newtag="2f250";
  else if(NewTag=="FullOpt")newtag="2f500-PSO";
  else if(NewTag=="dEdx")newtag="2f500-dEdx";
  
  TString leftpol_old="Left Pol ("+oldtag+")";
  TString leftpol_new="Left Pol ("+newtag+")";
  TString rightpol_old="Right Pol ("+oldtag+")";
  TString rightpol_new="Right Pol ("+newtag+")";

  TH1F*  btag_old[40][2];
  TH1F*  ctag_old[40][2];
  TH1F*  btag_new[40][2];
  TH1F*  ctag_new[40][2];

  for(int i=0; i<40; i++) {
    btag_old[i][0]= (TH1F*)f_old->Get(TString::Format("h_jet_btag_%i",i));
    ctag_old[i][0]= (TH1F*)f_old->Get(TString::Format("h_jet_ctag_%i",i));
    btag_old[i][1]= (TH1F*)f2_old->Get(TString::Format("h_jet_btag_%i",i));
    ctag_old[i][1]= (TH1F*)f2_old->Get(TString::Format("h_jet_ctag_%i",i));
    btag_new[i][0]= (TH1F*)f_new->Get(TString::Format("h_jet_btag_%i",i));
    ctag_new[i][0]= (TH1F*)f_new->Get(TString::Format("h_jet_ctag_%i",i));
    btag_new[i][1]= (TH1F*)f2_new->Get(TString::Format("h_jet_btag_%i",i));
    ctag_new[i][1]= (TH1F*)f2_new->Get(TString::Format("h_jet_ctag_%i",i));
  }

  float x[40], eff_b_old[2][3][40], eff_c_old[2][3][40], eff_b_new[2][3][40], eff_c_new[2][3][40];
  float eff2_b_old[2][3][40], eff2_c_old[2][3][40], eff2_b_new[2][3][40], eff2_c_new[2][3][40];
  float pur_b_old[2][3][40], pur_c_old[2][3][40], pur_b_new[2][3][40], pur_c_new[2][3][40];
  float f1score_b_old[2][3][40], f1score_c_old[2][3][40], f1score_b_new[2][3][40], f1score_c_new[2][3][40];
  float f1integral_b_old[2], f1integral_c_old[2], f1integral_b_new[2], f1integral_c_new[2];
  //float ROC_b_old[2][3][40], ROC_c_old[2][3][40], ROC_b_new[2][3][40], ROC_c_new[2][3][40];
  //float ROC_integral_b_old[2], ROC_integral_c_old[2], ROC_integral_b_new[2], ROC_integral_c_new[2];
  float TruePositive_b_old[2][40],TruePositive_c_old[2][40],FalsePositive_b_old[2][40],FalsePositive_c_old[2][40];
  float TruePositive_b_new[2][40],TruePositive_c_new[2][40],FalsePositive_b_new[2][40],FalsePositive_c_new[2][40];
  float ROCintegral_b_old[2], ROCintegral_c_old[2], ROCintegral_b_new[2], ROCintegral_c_new[2];

  int n_old=0;
  for(int i=0;i<40; i++) {
    x[i]=i*0.025;
    float ntotal[3]={0};
    float nb[3]={0};
    float nc[3]={0};
    //float f1sum[3];
    for(int iflav=0;iflav<3; iflav++){
      int quark=0;
      if(iflav==1) quark=4;
      if(iflav==2) quark=5;

      for(int ipol=0; ipol<2; ipol++){
	ntotal[iflav]=btag_old[0][ipol]->GetBinContent(quark+1);	
	nb[iflav]=btag_old[i][ipol]->GetBinContent(quark+1);
	nc[iflav]=ctag_old[i][ipol]->GetBinContent(quark+1);
	if(ntotal[iflav]==0){
	eff_b_old[ipol][iflav][i]=0;
	eff_c_old[ipol][iflav][i]=0;
	eff2_b_old[ipol][iflav][i]=100;
	eff2_c_old[ipol][iflav][i]=100;
	}
	else{
	  eff_b_old[ipol][iflav][i]=100.*nb[iflav]/ntotal[iflav];
	  eff_c_old[ipol][iflav][i]=100.*nc[iflav]/ntotal[iflav];
	  eff2_b_old[ipol][iflav][i]=100.-100.*nb[iflav]/ntotal[iflav];
	  eff2_c_old[ipol][iflav][i]=100.-100.*nc[iflav]/ntotal[iflav];
	}
	pur_b_old[ipol][iflav][i]=100.*(nb[iflav]/(nb[0]+nb[1]+nb[2]));
	pur_c_old[ipol][iflav][i]=100.*(nc[iflav]/(nc[0]+nc[1]+nc[2]));
	//F1Score 
	float FP_b=0; //False Positive b
	float FN_b=0; //False Negative b
	FN_b=ntotal[iflav]-nb[iflav];
	FP_b=nb[0]+nb[1]+nb[2]-nb[iflav];
	f1score_b_old[ipol][iflav][i]=nb[iflav]/(nb[iflav]+0.5*(FP_b+FN_b));
	if(iflav==2){
	  if(ntotal[iflav]==0){
	    TruePositive_b_old[ipol][i]=0;
	  }
	  else{
	    TruePositive_b_old[ipol][i]=nb[iflav]/ntotal[iflav];
	  }
	  if(ntotal[0]+ntotal[1]+ntotal[2]-ntotal[iflav]==0){
	    FalsePositive_b_old[ipol][i]=0;
	  }
	  else{
	    FalsePositive_b_old[ipol][i]=FP_b/(ntotal[0]+ntotal[1]+ntotal[2]-ntotal[iflav]);
	  }
	}
	
	float FP_c=0; //False Positive c
        float FN_c=0; //False Negative c
        FN_c=ntotal[iflav]-nc[iflav];
        FP_c=nc[0]+nc[1]+nc[2]-nc[iflav];
        f1score_c_old[ipol][iflav][i]=nc[iflav]/(nc[iflav]+0.5*(FP_c+FN_c));
	if(iflav==1){

	  if(ntotal[iflav]==0){
	    TruePositive_c_old[ipol][i]=0;
	  }
	  else{
	    TruePositive_c_old[ipol][i]=nc[iflav]/ntotal[iflav];
	  }
	  
	  if(ntotal[0]+ntotal[1]+ntotal[2]-ntotal[iflav]==0){
	    FalsePositive_c_old[ipol][i]=0;
	  }
	  else{
	    FalsePositive_c_old[ipol][i]=FP_c/(ntotal[0]+ntotal[1]+ntotal[2]-ntotal[iflav]);
	  }

	  cout<<"(Debug roc_C|old) TP: "<<TruePositive_c_old[ipol][i]<<", FP: "<<FalsePositive_c_old[ipol][i] <<endl;
	  //	  TruePositive_c_old[ipol][i]=1;
	  //	  FalsePositive_c_old[ipol][i]=1;
	}
      }
    }
    n_old++;
  }
  
  int n_new=0;
  for(int i=0;i<40; i++) {
    //x[i]=i*0.025;
    float ntotal[3]={0};
    float nb[3]={0};
    float nc[3]={0};
    for(int iflav=0;iflav<3; iflav++){
      int quark=0;
      if(iflav==1) quark=4;
      if(iflav==2) quark=5;

      for(int ipol=0; ipol<2; ipol++){
        ntotal[iflav]=btag_new[0][ipol]->GetBinContent(quark+1);

        nb[iflav]=btag_new[i][ipol]->GetBinContent(quark+1);
        nc[iflav]=ctag_new[i][ipol]->GetBinContent(quark+1);
	if(ntotal[iflav]==0){
	  eff_b_new[ipol][iflav][i]=0;
	  eff_c_new[ipol][iflav][i]=0;
	  eff2_b_new[ipol][iflav][i]=100;
	  eff2_c_new[ipol][iflav][i]=100;
	}
	else{
        eff_b_new[ipol][iflav][i]=100.*nb[iflav]/ntotal[iflav];
        eff_c_new[ipol][iflav][i]=100.*nc[iflav]/ntotal[iflav];
        eff2_b_new[ipol][iflav][i]=100.-100.*nb[iflav]/ntotal[iflav];
        eff2_c_new[ipol][iflav][i]=100.-100.*nc[iflav]/ntotal[iflav];
        }
	pur_b_new[ipol][iflav][i]=100.*(nb[iflav]/(nb[0]+nb[1]+nb[2]));
        pur_c_new[ipol][iflav][i]=100.*(nc[iflav]/(nc[0]+nc[1]+nc[2]));
        //F1Score                                                                                             
        float FP_b=0; //False Positive b                                                                                                
        float FN_b=0; //False Negative b                                                                              
        FN_b=ntotal[iflav]-nb[iflav];
        if(iflav==0)FP_b=nb[1]+nb[2];
        else if(iflav==1)FP_b=nb[0]+nb[2];
        else if(iflav==2)FP_b=nb[0]+nb[1];
        f1score_b_new[ipol][iflav][i]=nb[iflav]/(nb[iflav]+0.5*(FP_b+FN_b));
        if(iflav==2){
	  if(ntotal[iflav]==0){
	    TruePositive_b_new[ipol][i]=0;
	  }
	  else{
	    TruePositive_b_new[ipol][i]=nb[iflav]/ntotal[iflav];
          }
	  if(ntotal[0]+ntotal[1]==0){
	    FalsePositive_b_new[ipol][i]=0;
	  }
	  else{
	    FalsePositive_b_new[ipol][i]=FP_b/(ntotal[0]+ntotal[1]);
	  }
        }
	float FP_c=0; //False Positive c                                                                                                                        
        float FN_c=0; //False Negative c                                                                                                                     
        FN_c=ntotal[iflav]-nc[iflav];
        if(iflav==0)FP_c=nc[1]+nc[2];
        else if(iflav==1)FP_c=nc[0]+nc[2];
        else if(iflav==2)FP_c=nc[0]+nc[1];
        f1score_c_new[ipol][iflav][i]=nc[iflav]/(nc[iflav]+0.5*(FP_c+FN_c));
	if(iflav==1){
	  if(ntotal[iflav]==0){
	    TruePositive_c_new[ipol][i]=0;
	  }
	  else{
	    TruePositive_c_new[ipol][i]=nc[iflav]/ntotal[iflav];
          }
	  if(ntotal[0]+ntotal[2]==0){
	    FalsePositive_c_new[ipol][i]=0;
	  }
	  else{
	    FalsePositive_c_new[ipol][i]=FP_c/(ntotal[0]+ntotal[2]);
	  }        
	  cout<<"(Debug roc_C) TP: "<<TruePositive_c_new[ipol][i]<<", FP: "<<FalsePositive_c_new[ipol][i] <<endl;
	}
      }
    }
    n_new++;
  }

  
  f1integral_b_old[0]=0;
  f1integral_c_old[0]=0;
  f1integral_b_new[0]=0;
  f1integral_c_new[0]=0;
  f1integral_b_old[1]=0;
  f1integral_c_old[1]=0;
  f1integral_b_new[1]=0;
  f1integral_c_new[1]=0;

  ROCintegral_b_old[0]=0;
  ROCintegral_c_old[0]=0;
  ROCintegral_b_new[0]=0;
  ROCintegral_c_new[0]=0;
  ROCintegral_b_old[1]=0;
  ROCintegral_c_old[1]=0;
  ROCintegral_b_new[1]=0;
  ROCintegral_c_new[1]=0;

  int firstnumber=0;
  int lastnumber=40;

  float fnum=firstnumber*1000;
  float lnum=lastnumber*1000;
  float divisor=1000/(lnum-fnum);

  float fn_hp=lastnumber-12; //High purity                                                                    
  float ln_hp=lastnumber-4;
  float fnum_hp=fn_hp*1000;
  float lnum_hp=ln_hp*1000;
  float divisor_hp=1000/(lnum_hp-fnum_hp);

  // High Purity range: 0.7<tag<0.9                                                                                                                           
  // HP: lastnumber-12, lastnumber-4                                                                                                                          
  for(int i=fn_hp;i<ln_hp; i++) {
    for(int ipol=0; ipol<2; ipol++){
      f1integral_b_old[ipol]+=divisor_hp*0.5*(f1score_b_old[ipol][2][i]+f1score_b_old[ipol][2][i+1]);
      f1integral_c_old[ipol]+=divisor_hp*0.5*(f1score_c_old[ipol][1][i]+f1score_c_old[ipol][1][i+1]);
      f1integral_b_new[ipol]+=divisor_hp*0.5*(f1score_b_new[ipol][2][i]+f1score_b_new[ipol][2][i+1]);
      f1integral_c_new[ipol]+=divisor_hp*0.5*(f1score_c_new[ipol][1][i]+f1score_c_new[ipol][1][i+1]);
    }
  }

  for(int i=0;i<39; i++) {
    for(int ipol=0; ipol<2; ipol++){
 
      ROCintegral_b_old[ipol]+=0.5*(TruePositive_b_old[ipol][i+1]+TruePositive_b_old[ipol][i])*abs(FalsePositive_b_old[ipol][i+1]-FalsePositive_b_old[ipol][i]);
      ROCintegral_c_old[ipol]+=0.5*(TruePositive_c_old[ipol][i+1]+TruePositive_c_old[ipol][i])*abs(FalsePositive_c_old[ipol][i+1]-FalsePositive_c_old[ipol][i]);
      ROCintegral_b_new[ipol]+=0.5*(TruePositive_b_new[ipol][i+1]+TruePositive_b_new[ipol][i])*abs(FalsePositive_b_new[ipol][i+1]-FalsePositive_b_new[ipol][i]);
      ROCintegral_c_new[ipol]+=0.5*(TruePositive_c_new[ipol][i+1]+TruePositive_c_new[ipol][i])*abs(FalsePositive_c_new[ipol][i+1]-FalsePositive_c_new[ipol][i]);
    }
  }

  cout<<"[OLD] F_integral_eL(b): "<<f1integral_b_old[0]<<", F_integral_eL(c): "<<f1integral_c_old[0]<<endl;
  cout<<"[NEW] F_integral_eL(b): "<<f1integral_b_new[0]<<", F_integral_eL(c): "<<f1integral_c_new[0]<<endl;
  cout<<"[OLD] F_integral_eR(b): "<<f1integral_b_old[1]<<", F_integral_eR(c): "<<f1integral_c_old[1]<<endl;
  cout<<"[NEW] F_integral_eR(b): "<<f1integral_b_new[1]<<", F_integral_eR(c): "<<f1integral_c_new[1]<<endl;
  cout<<"------------------------------------------------"<<endl;
  cout<<"[OLD] ROC_integral_eL(b): "<<ROCintegral_b_old[0]<<", ROC_integral_eL(c): "<<ROCintegral_c_old[0]<<endl;
  cout<<"[NEW] ROC_integral_eL(b): "<<ROCintegral_b_new[0]<<", ROC_integral_eL(c): "<<ROCintegral_c_new[0]<<endl;
  cout<<"[OLD] ROC_integral_eR(b): "<<ROCintegral_b_old[1]<<", ROC_integral_eR(c): "<<ROCintegral_c_old[1]<<endl;
  cout<<"[NEW] ROC_integral_eR(b): "<<ROCintegral_b_new[1]<<", ROC_integral_eR(c): "<<ROCintegral_c_new[1]<<endl;


  //--------------
  //Purity

  TGraph* purity_b_b_eL = new TGraph(n_old,eff_b_old[0][2],pur_b_old[0][2]);
  TGraph* purity_b_b_eR = new TGraph(n_old,eff_b_old[1][2],pur_b_old[1][2]);
  TGraph* purity_b_b_eL_new = new TGraph(n_new,eff_b_new[0][2],pur_b_new[0][2]);
  TGraph* purity_b_b_eR_new = new TGraph(n_new,eff_b_new[1][2],pur_b_new[1][2]);


  TCanvas* c_pur_b = new TCanvas("c_pur_b","c_pur_b",800,800);
  c_pur_b->cd(1);
  c_pur_b->SetGrid();
  purity_b_b_eL->GetXaxis()->SetTitle("b-quark efficiency (%)");
  purity_b_b_eL->GetYaxis()->SetTitle("b-quark purity (%)");
  purity_b_b_eL->GetYaxis()->SetTitleOffset(1.25);
  purity_b_b_eL->GetXaxis()->SetTitleOffset(1.);
  purity_b_b_eL->GetYaxis()->SetRangeUser(0,100);
  purity_b_b_eL->SetLineColor(2);
  purity_b_b_eL->SetLineWidth(2);
  purity_b_b_eL->SetLineStyle(1);
  purity_b_b_eL->Draw("alp");
  purity_b_b_eR->SetLineColor(4);
  purity_b_b_eR->SetLineWidth(2);
  purity_b_b_eR->SetLineStyle(2);
  purity_b_b_eR->Draw("lp");
  purity_b_b_eL_new->SetLineColor(94);
  purity_b_b_eL_new->SetLineWidth(2);
  purity_b_b_eL_new->SetLineStyle(1);
  purity_b_b_eL_new->Draw("lp");
  purity_b_b_eR_new->SetLineColor(64);
  purity_b_b_eR_new->SetLineWidth(2);
  purity_b_b_eR_new->SetLineStyle(2);
  purity_b_b_eR_new->Draw("lp");

  Labels("",cat,cut);
  TLegend *leg_pb;
  leg_pb= new TLegend(0.4,0.3,0.6,0.5);
  leg_pb->SetTextSize(0.035);
  leg_pb->SetTextFont(42);
  leg_pb->AddEntry(purity_b_b_eL,leftpol_old,"lp");
  leg_pb->AddEntry(purity_b_b_eL_new,leftpol_new,"lp");
  leg_pb->AddEntry(purity_b_b_eR,rightpol_old,"lp");
  leg_pb->AddEntry(purity_b_b_eR_new,rightpol_new,"lp");
  leg_pb->SetFillColor(0);
  leg_pb->SetLineColor(0);
  leg_pb->SetShadowColor(0);
  leg_pb->Draw();
  
  TGraph* purity_c_c_eL = new TGraph(n_old,eff_c_old[0][1],pur_c_old[0][1]);
  TGraph* purity_c_c_eR = new TGraph(n_old,eff_c_old[1][1],pur_c_old[1][1]);
  TGraph* purity_c_c_eL_new = new TGraph(n_new,eff_c_new[0][1],pur_c_new[0][1]);
  TGraph* purity_c_c_eR_new = new TGraph(n_new,eff_c_new[1][1],pur_c_new[1][1]);

  TCanvas* c_pur_c = new TCanvas("c_pur_c","c_pur_c",800,800);
  c_pur_c->cd(1);
  c_pur_c->SetGrid();
  purity_c_c_eL->GetXaxis()->SetTitle("c-quark efficiency (%)");
  purity_c_c_eL->GetYaxis()->SetTitle("c-quark purity (%)");
  purity_c_c_eL->GetYaxis()->SetTitleOffset(1.25);
  purity_c_c_eL->GetXaxis()->SetTitleOffset(1.);
  purity_c_c_eL->GetYaxis()->SetRangeUser(20,100);
  purity_c_c_eL->GetXaxis()->SetRangeUser(10,100);
  purity_c_c_eL->SetLineColor(2);
  purity_c_c_eL->SetLineWidth(2);
  purity_c_c_eL->SetLineStyle(1);
  purity_c_c_eL->Draw("alp");
  purity_c_c_eR->SetLineColor(4);
  purity_c_c_eR->SetLineWidth(2);
  purity_c_c_eR->SetLineStyle(2);
  purity_c_c_eR->Draw("lp");
  purity_c_c_eL_new->SetLineColor(94);
  purity_c_c_eL_new->SetLineWidth(2);
  purity_c_c_eL_new->SetLineStyle(1);
  purity_c_c_eL_new->Draw("lp");
  purity_c_c_eR_new->SetLineColor(64);
  purity_c_c_eR_new->SetLineWidth(2);
  purity_c_c_eR_new->SetLineStyle(2);
  purity_c_c_eR_new->Draw("lp");

  Labels("",cat,cut);
  TLegend *leg_pc;
  leg_pc= new TLegend(0.4,0.3,0.6,0.5);
  leg_pc->SetTextSize(0.035);
  leg_pc->SetTextFont(42);
  leg_pc->AddEntry(purity_c_c_eL,leftpol_old,"lp");
  leg_pc->AddEntry(purity_c_c_eL_new,leftpol_new,"lp");
  leg_pc->AddEntry(purity_c_c_eR,rightpol_old,"lp");
  leg_pc->AddEntry(purity_c_c_eR_new,rightpol_new,"lp");
  leg_pc->SetFillColor(0);
  leg_pc->SetLineColor(0);
  leg_pc->SetShadowColor(0);
  leg_pc->Draw();

  
  //-----------
  //F1Score
  
  TGraph* f1score_b_b_eL = new TGraph(n_old,x,f1score_b_old[0][2]);
  TGraph* f1score_b_b_eR = new TGraph(n_old,x,f1score_b_old[1][2]);
  TGraph* f1score_b_b_eL_new = new TGraph(n_new,x,f1score_b_new[0][2]);
  TGraph* f1score_b_b_eR_new = new TGraph(n_new,x,f1score_b_new[1][2]);
  TCanvas* c_f1score_b = new TCanvas("c_f1score_b","c_f1score_b",800,800);
  c_f1score_b->cd(1);
  c_f1score_b->SetGrid();
  f1score_b_b_eL->GetXaxis()->SetTitle("btag_{cut}");
  f1score_b_b_eL->GetYaxis()->SetTitle("F1-Score");
  f1score_b_b_eL->GetYaxis()->SetTitleOffset(1.25);
  f1score_b_b_eL->GetXaxis()->SetTitleOffset(1.);
  f1score_b_b_eL->GetYaxis()->SetRangeUser(0,1);
  f1score_b_b_eL->SetLineColor(2);
  f1score_b_b_eL->SetLineWidth(2);
  f1score_b_b_eL->SetLineStyle(1);
  f1score_b_b_eL->Draw("alp");
  f1score_b_b_eR->SetLineColor(4);
  f1score_b_b_eR->SetLineWidth(2);
  f1score_b_b_eR->SetLineStyle(2);
  f1score_b_b_eR->Draw("lp");
  f1score_b_b_eL_new->SetLineColor(94);
  f1score_b_b_eL_new->SetLineWidth(2);
  f1score_b_b_eL_new->SetLineStyle(1);
  f1score_b_b_eL_new->Draw("lp");
  f1score_b_b_eR_new->SetLineColor(64);
  f1score_b_b_eR_new->SetLineWidth(2);
  f1score_b_b_eR_new->SetLineStyle(2);
  f1score_b_b_eR_new->Draw("lp");

  Labels("",cat,cut);
  TLegend *leg_fb;
  leg_fb= new TLegend(0.4,0.3,0.6,0.5);
  leg_fb->SetTextSize(0.035);
  leg_fb->SetTextFont(42);
  leg_fb->AddEntry(f1score_b_b_eL,leftpol_old,"lp");
  leg_fb->AddEntry(f1score_b_b_eL_new,leftpol_new,"lp");
  leg_fb->AddEntry(f1score_b_b_eR,rightpol_old,"lp");
  leg_fb->AddEntry(f1score_b_b_eR_new,rightpol_new,"lp");
  leg_fb->SetFillColor(0);
  leg_fb->SetLineColor(0);
  leg_fb->SetShadowColor(0);
  leg_fb->Draw();

  TGraph* f1score_c_c_eL = new TGraph(n_old,x,f1score_c_old[0][1]);
  TGraph* f1score_c_c_eR = new TGraph(n_old,x,f1score_c_old[1][1]);
  TGraph* f1score_c_c_eL_new = new TGraph(n_new,x,f1score_c_new[0][1]);
  TGraph* f1score_c_c_eR_new = new TGraph(n_new,x,f1score_c_new[1][1]);
  TCanvas* c_f1score_c = new TCanvas("c_f1score_c","c_f1score_c",800,800);
  c_f1score_c->cd(1);
  c_f1score_c->SetGrid();
  f1score_c_c_eL->GetXaxis()->SetTitle("ctag_{cut}");
  f1score_c_c_eL->GetYaxis()->SetTitle("F1-Score");
  f1score_c_c_eL->GetYaxis()->SetTitleOffset(1.25);
  f1score_c_c_eL->GetXaxis()->SetTitleOffset(1.);
  f1score_c_c_eL->GetYaxis()->SetRangeUser(0,1);
  f1score_c_c_eL->SetLineColor(2);
  f1score_c_c_eL->SetLineWidth(2);
  f1score_c_c_eL->SetLineStyle(1);
  f1score_c_c_eL->Draw("alp");
  f1score_c_c_eR->SetLineColor(4);
  f1score_c_c_eR->SetLineWidth(2);
  f1score_c_c_eR->SetLineStyle(2);
  f1score_c_c_eR->Draw("lp");
  f1score_c_c_eL_new->SetLineColor(94);
  f1score_c_c_eL_new->SetLineWidth(2);
  f1score_c_c_eL_new->SetLineStyle(1);
  f1score_c_c_eL_new->Draw("lp");
  f1score_c_c_eR_new->SetLineColor(64);
  f1score_c_c_eR_new->SetLineWidth(2);
  f1score_c_c_eR_new->SetLineStyle(2);
  f1score_c_c_eR_new->Draw("lp");

  Labels("",cat,cut);
  TLegend *leg_fc;
  leg_fc= new TLegend(0.4,0.3,0.6,0.5);
  leg_fc->SetTextSize(0.035);
  leg_fc->SetTextFont(42);
  leg_fc->AddEntry(f1score_c_c_eL,leftpol_old,"lp");
  leg_fc->AddEntry(f1score_c_c_eL_new,leftpol_new,"lp");
  leg_fc->AddEntry(f1score_c_c_eR,rightpol_old,"lp");
  leg_fc->AddEntry(f1score_c_c_eR_new,rightpol_new,"lp");
  leg_fc->SetFillColor(0);
  leg_fc->SetLineColor(0);
  leg_fc->SetShadowColor(0);
  leg_fc->Draw();
  

  //-----------                                                                                                                                                                                      
  //ROC                                                                                                                                                                                          

  TGraph* ROC_b_b_eL = new TGraph(n_old,FalsePositive_b_old[0],TruePositive_b_old[0]);
  TGraph* ROC_b_b_eR = new TGraph(n_old,FalsePositive_b_old[1],TruePositive_b_old[1]);
  TGraph* ROC_b_b_eL_new = new TGraph(n_new,FalsePositive_b_new[0],TruePositive_b_new[0]);
  TGraph* ROC_b_b_eR_new = new TGraph(n_new,FalsePositive_b_new[1],TruePositive_b_new[1]);
  TCanvas* c_ROC_b = new TCanvas("c_ROC_b","c_ROC_b",800,800);
  c_ROC_b->cd();
  c_ROC_b->SetGrid();
  ROC_b_b_eL->GetXaxis()->SetTitle("False Positive rate (b-quark)");
  ROC_b_b_eL->GetYaxis()->SetTitle("True Positive rate (b-quark)");
  ROC_b_b_eL->GetYaxis()->SetTitleOffset(1.25);
  ROC_b_b_eL->GetXaxis()->SetTitleOffset(1.);
  ROC_b_b_eL->GetYaxis()->SetRangeUser(0,1);
  ROC_b_b_eL->SetLineColor(2);
  ROC_b_b_eL->SetLineWidth(2);
  ROC_b_b_eL->SetLineStyle(1);
  ROC_b_b_eL->Draw("alp");
  ROC_b_b_eR->SetLineColor(4);
  ROC_b_b_eR->SetLineWidth(2);
  ROC_b_b_eR->SetLineStyle(2);
  ROC_b_b_eR->Draw("lp");
  ROC_b_b_eL_new->SetLineColor(94);
  ROC_b_b_eL_new->SetLineWidth(2);
  ROC_b_b_eL_new->SetLineStyle(1);
  ROC_b_b_eL_new->Draw("lp");
  ROC_b_b_eR_new->SetLineColor(64);
  ROC_b_b_eR_new->SetLineWidth(2);
  ROC_b_b_eR_new->SetLineStyle(2);
  ROC_b_b_eR_new->Draw("lp");

  Labels("",cat,cut);
  TLegend *leg_fb_roc;
  leg_fb_roc= new TLegend(0.4,0.3,0.6,0.5);
  leg_fb_roc->SetTextSize(0.035);
  leg_fb_roc->SetTextFont(42);
  leg_fb_roc->AddEntry(ROC_b_b_eL,leftpol_old,"lp");
  leg_fb_roc->AddEntry(ROC_b_b_eL_new,leftpol_new,"lp");
  leg_fb_roc->AddEntry(ROC_b_b_eR,rightpol_old,"lp");
  leg_fb_roc->AddEntry(ROC_b_b_eR_new,rightpol_new,"lp");
  leg_fb_roc->SetFillColor(0);
  leg_fb_roc->SetLineColor(0);
  leg_fb_roc->SetShadowColor(0);
  leg_fb_roc->Draw();

  TGraph* ROC_c_c_eL = new TGraph(n_old,FalsePositive_c_old[0],TruePositive_c_old[0]);
  TGraph* ROC_c_c_eR = new TGraph(n_old,FalsePositive_c_old[1],TruePositive_c_old[1]);
  TGraph* ROC_c_c_eL_new = new TGraph(n_new,FalsePositive_c_new[0],TruePositive_c_new[0]);
  TGraph* ROC_c_c_eR_new = new TGraph(n_new,FalsePositive_c_new[1],TruePositive_c_new[1]);
  TCanvas* c_ROC_c = new TCanvas("c_ROC_c","c_ROC_c",800,800);
  c_ROC_c->cd();
  c_ROC_c->SetGrid();
  ROC_c_c_eL->GetXaxis()->SetTitle("False Positive rate (c-quark)");
  ROC_c_c_eL->GetYaxis()->SetTitle("True Positive rate (c-quark)");
  ROC_c_c_eL->GetYaxis()->SetTitleOffset(1.25);
  ROC_c_c_eL->GetXaxis()->SetTitleOffset(1.);
  ROC_c_c_eL->GetYaxis()->SetRangeUser(0,1);
  ROC_c_c_eL->SetLineColor(2);
  ROC_c_c_eL->SetLineWidth(2);
  ROC_c_c_eL->SetLineStyle(1);
  ROC_c_c_eL->Draw("alp");
  ROC_c_c_eR->SetLineColor(4);
  ROC_c_c_eR->SetLineWidth(2);
  ROC_c_c_eR->SetLineStyle(2);
  ROC_c_c_eR->Draw("lp");
  ROC_c_c_eL_new->SetLineColor(94);
  ROC_c_c_eL_new->SetLineWidth(2);
  ROC_c_c_eL_new->SetLineStyle(1);
  ROC_c_c_eL_new->Draw("lp");
  ROC_c_c_eR_new->SetLineColor(64);
  ROC_c_c_eR_new->SetLineWidth(2);
  ROC_c_c_eR_new->SetLineStyle(2);
  ROC_c_c_eR_new->Draw("lp");
  
  Labels("",cat,cut);
  TLegend *leg_fc_roc;
  leg_fc_roc= new TLegend(0.4,0.3,0.6,0.5);
  leg_fc_roc->SetTextSize(0.035);
  leg_fc_roc->SetTextFont(42);
  leg_fc_roc->AddEntry(ROC_c_c_eL,leftpol_old,"lp");
  leg_fc_roc->AddEntry(ROC_c_c_eL_new,leftpol_new,"lp");
  leg_fc_roc->AddEntry(ROC_c_c_eR,rightpol_old,"lp");
  leg_fc_roc->AddEntry(ROC_c_c_eR_new,rightpol_new,"lp");
  leg_fc_roc->SetFillColor(0);
  leg_fc_roc->SetLineColor(0);
  leg_fc_roc->SetShadowColor(0);
  leg_fc_roc->Draw();
  

  //----------                                                        
  //F1_pur
  
  TGraph* F1_pur_b_eL = new TGraph(n_old,pur_b_old[0][2],f1score_b_old[0][2]);
  TGraph* F1_pur_b_eR = new TGraph(n_old,pur_b_old[1][2],f1score_b_old[1][2]);
  TGraph* F1_pur_b_eL_new = new TGraph(n_new,pur_b_new[0][2],f1score_b_new[0][2]);
  TGraph* F1_pur_b_eR_new = new TGraph(n_new,pur_b_new[1][2],f1score_b_new[1][2]);
  TCanvas* c_f1pur_b = new TCanvas("c_f1pur_b","c_f1pur_b",800,800);
  c_f1pur_b->cd(1);
  c_f1pur_b->SetGrid();
  F1_pur_b_eL->GetXaxis()->SetTitle("b-quark purity (%)");
  F1_pur_b_eL->GetYaxis()->SetTitle("b-tag F1 score");
  F1_pur_b_eL->GetYaxis()->SetTitleOffset(1.25);
  F1_pur_b_eL->GetXaxis()->SetTitleOffset(1.);
  F1_pur_b_eL->GetYaxis()->SetRangeUser(0,1);
  F1_pur_b_eL->SetLineColor(2);
  F1_pur_b_eL->SetLineWidth(2);
  F1_pur_b_eL->SetLineStyle(1);
  F1_pur_b_eL->Draw("alp");
  F1_pur_b_eR->SetLineColor(4);
  F1_pur_b_eR->SetLineWidth(2);
  F1_pur_b_eR->SetLineStyle(2);
  F1_pur_b_eR->Draw("lp");
  F1_pur_b_eL_new->SetLineColor(94);
  F1_pur_b_eL_new->SetLineWidth(2);
  F1_pur_b_eL_new->SetLineStyle(1);
  F1_pur_b_eL_new->Draw("lp");
  F1_pur_b_eR_new->SetLineColor(64);
  F1_pur_b_eR_new->SetLineWidth(2);
  F1_pur_b_eR_new->SetLineStyle(2);
  F1_pur_b_eR_new->Draw("lp");

  Labels("",cat,cut);
  TLegend *leg_f1pur_b;
  leg_f1pur_b= new TLegend(0.4,0.3,0.6,0.5);
  leg_f1pur_b->SetTextSize(0.035);
  leg_f1pur_b->SetTextFont(42);
  leg_f1pur_b->AddEntry(F1_pur_b_eL,leftpol_old,"lp");
  leg_f1pur_b->AddEntry(F1_pur_b_eL_new,leftpol_new,"lp");
  leg_f1pur_b->AddEntry(F1_pur_b_eR,rightpol_old,"lp");
  leg_f1pur_b->AddEntry(F1_pur_b_eR_new,rightpol_new,"lp");
  leg_f1pur_b->SetFillColor(0);
  leg_f1pur_b->SetLineColor(0);
  leg_f1pur_b->SetShadowColor(0);
  leg_f1pur_b->Draw();

  TGraph* F1_pur_c_eL = new TGraph(n_old,pur_c_old[0][1],f1score_c_old[0][1]);
  TGraph* F1_pur_c_eR = new TGraph(n_old,pur_c_old[1][1],f1score_c_old[1][1]);
  TGraph* F1_pur_c_eL_new = new TGraph(n_new,pur_c_new[0][1],f1score_c_new[0][1]);
  TGraph* F1_pur_c_eR_new = new TGraph(n_new,pur_c_new[1][1],f1score_c_new[1][1]);
  TCanvas* c_f1pur_c = new TCanvas("c_f1pur_c","c_f1pur_c",800,800);
  c_f1pur_c->cd(1);
  c_f1pur_c->SetGrid();
  F1_pur_c_eL->GetXaxis()->SetTitle("c-quark purity (%)");
  F1_pur_c_eL->GetYaxis()->SetTitle("c-tag F1 score");
  F1_pur_c_eL->GetYaxis()->SetTitleOffset(1.25);
  F1_pur_c_eL->GetXaxis()->SetTitleOffset(1.);
  F1_pur_c_eL->GetYaxis()->SetRangeUser(0,1);
  F1_pur_c_eL->SetLineColor(2);
  F1_pur_c_eL->SetLineWidth(2);
  F1_pur_c_eL->SetLineStyle(1);
  F1_pur_c_eL->Draw("alp");
  F1_pur_c_eR->SetLineColor(4);
  F1_pur_c_eR->SetLineWidth(2);
  F1_pur_c_eR->SetLineStyle(2);
  F1_pur_c_eR->Draw("lp");
  F1_pur_c_eL_new->SetLineColor(94);
  F1_pur_c_eL_new->SetLineWidth(2);
  F1_pur_c_eL_new->SetLineStyle(1);
  F1_pur_c_eL_new->Draw("lp");
  F1_pur_c_eR_new->SetLineColor(64);
  F1_pur_c_eR_new->SetLineWidth(2);
  F1_pur_c_eR_new->SetLineStyle(2);
  F1_pur_c_eR_new->Draw("lp");

  Labels("",cat,cut);
  TLegend *leg_f1pur_c;
  leg_f1pur_c= new TLegend(0.4,0.3,0.6,0.5);
  leg_f1pur_c->SetTextSize(0.035);
  leg_f1pur_c->SetTextFont(42);
  leg_f1pur_c->AddEntry(F1_pur_c_eL,leftpol_old,"lp");
  leg_f1pur_c->AddEntry(F1_pur_c_eL_new,leftpol_new,"lp");
  leg_f1pur_c->AddEntry(F1_pur_c_eR,rightpol_old,"lp");
  leg_f1pur_c->AddEntry(F1_pur_c_eR_new,rightpol_new,"lp");
  leg_f1pur_c->SetFillColor(0);
  leg_f1pur_c->SetLineColor(0);
  leg_f1pur_c->SetShadowColor(0);
  leg_f1pur_c->Draw();


  //pur_cut

  TGraph* pur_cut_b_eL = new TGraph(n_old,x,pur_b_old[0][2]);
  TGraph* pur_cut_b_eR = new TGraph(n_old,x,pur_b_old[1][2]);
  TGraph* pur_cut_b_eL_new = new TGraph(n_new,x,pur_b_new[0][2]);
  TGraph* pur_cut_b_eR_new = new TGraph(n_new,x,pur_b_new[1][2]);
  TCanvas* c_pur_cut_b = new TCanvas("c_pur_cut_b","c_pur_cut_b",800,800);
  c_pur_cut_b->cd(1);
  c_pur_cut_b->SetGrid();
  pur_cut_b_eL->GetXaxis()->SetTitle("b-tag cut");
  pur_cut_b_eL->GetYaxis()->SetTitle("purity (%)");
  pur_cut_b_eL->GetYaxis()->SetTitleOffset(1.25);
  pur_cut_b_eL->GetXaxis()->SetTitleOffset(1.);
  pur_cut_b_eL->GetYaxis()->SetRangeUser(0,100);
  pur_cut_b_eL->SetLineColor(2);
  pur_cut_b_eL->SetLineWidth(2);
  pur_cut_b_eL->SetLineStyle(1);
  pur_cut_b_eL->Draw("alp");
  pur_cut_b_eR->SetLineColor(4);
  pur_cut_b_eR->SetLineWidth(2);
  pur_cut_b_eR->SetLineStyle(2);
  pur_cut_b_eR->Draw("lp");
  pur_cut_b_eL_new->SetLineColor(94);
  pur_cut_b_eL_new->SetLineWidth(2);
  pur_cut_b_eL_new->SetLineStyle(1);
  pur_cut_b_eL_new->Draw("lp");
  pur_cut_b_eR_new->SetLineColor(64);
  pur_cut_b_eR_new->SetLineWidth(2);
  pur_cut_b_eR_new->SetLineStyle(2);
  pur_cut_b_eR_new->Draw("lp");

  Labels("",cat,cut);
  TLegend *leg_pur_cut_b;
  leg_pur_cut_b= new TLegend(0.4,0.3,0.6,0.5);
  leg_pur_cut_b->SetTextSize(0.035);
  leg_pur_cut_b->SetTextFont(42);
  leg_pur_cut_b->AddEntry(pur_cut_b_eL,leftpol_old,"lp");
  leg_pur_cut_b->AddEntry(pur_cut_b_eL_new,leftpol_new,"lp");
  leg_pur_cut_b->AddEntry(pur_cut_b_eR,rightpol_old,"lp");
  leg_pur_cut_b->AddEntry(pur_cut_b_eR_new,rightpol_new,"lp");
  leg_pur_cut_b->SetFillColor(0);
  leg_pur_cut_b->SetLineColor(0);
  leg_pur_cut_b->SetShadowColor(0);
  leg_pur_cut_b->Draw();
			
	   
  TGraph* pur_cut_c_eL = new TGraph(n_old,x,pur_c_old[0][1]);
  TGraph* pur_cut_c_eR = new TGraph(n_old,x,pur_c_old[1][1]);
  TGraph* pur_cut_c_eL_new = new TGraph(n_new,x,pur_c_new[0][1]);
  TGraph* pur_cut_c_eR_new = new TGraph(n_new,x,pur_c_new[1][1]);
  TCanvas* c_pur_cut_c = new TCanvas("c_pur_cut_c","c_pur_cut_c",800,800);
  c_pur_cut_c->cd(1);
  c_pur_cut_c->SetGrid();
  pur_cut_c_eL->GetXaxis()->SetTitle("c-tag cut");
  pur_cut_c_eL->GetYaxis()->SetTitle("purity (%)");
  pur_cut_c_eL->GetYaxis()->SetTitleOffset(1.25);
  pur_cut_c_eL->GetXaxis()->SetTitleOffset(1.);
  pur_cut_c_eL->GetYaxis()->SetRangeUser(0,100);
  pur_cut_c_eL->SetLineColor(2);
  pur_cut_c_eL->SetLineWidth(2);
  pur_cut_c_eL->SetLineStyle(1);
  pur_cut_c_eL->Draw("alp");
  pur_cut_c_eR->SetLineColor(4);
  pur_cut_c_eR->SetLineWidth(2);
  pur_cut_c_eR->SetLineStyle(2);
  pur_cut_c_eR->Draw("lp");
  pur_cut_c_eL_new->SetLineColor(94);
  pur_cut_c_eL_new->SetLineWidth(2);
  pur_cut_c_eL_new->SetLineStyle(1);
  pur_cut_c_eL_new->Draw("lp");
  pur_cut_c_eR_new->SetLineColor(64);
  pur_cut_c_eR_new->SetLineWidth(2);
  pur_cut_c_eR_new->SetLineStyle(2);
  pur_cut_c_eR_new->Draw("lp");

  Labels("",cat,cut);
  TLegend *leg_pur_cut_c;
  leg_pur_cut_c= new TLegend(0.4,0.3,0.6,0.5);
  leg_pur_cut_c->SetTextSize(0.035);
  leg_pur_cut_c->SetTextFont(42);
  leg_pur_cut_c->AddEntry(pur_cut_c_eL,leftpol_old,"lp");
  leg_pur_cut_c->AddEntry(pur_cut_c_eL_new,leftpol_new,"lp");
  leg_pur_cut_c->AddEntry(pur_cut_c_eR,rightpol_old,"lp");
  leg_pur_cut_c->AddEntry(pur_cut_c_eR_new,rightpol_new,"lp");
  leg_pur_cut_c->SetFillColor(0);
  leg_pur_cut_c->SetLineColor(0);
  leg_pur_cut_c->SetShadowColor(0);
  leg_pur_cut_c->Draw();

}

