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
#include "cross_sections_250GeV.h"


// Labels copiado de Adrián, tomar como referencia
// -----------------------------------------------
// -----------------------------------------------
void Labels(int i, TString pol, TString kvalue){
 
  QQBARLabel(0.86,0.952,"");
  if(i==0) QQBARLabel2(0.04,0.07, "[No Cuts]",kOrange+3);
  if(i==1) QQBARLabel2(0.04,0.07, " K_{reco}<"+kvalue+" GeV",kOrange+3);
  if(i==2) QQBARLabel2(0.04,0.07, "K_{reco}<"+kvalue+" GeV & m_{j_{1} j_{2}}>250 GeV",kOrange+3);
  if(i==3) {
    QQBARLabel2(0.04,0.082, "K_{reco}<"+kvalue+" GeV & m_{j_{1} j_{2}}>250 GeV & Npfos Veto",kOrange+3);
    QQBARLabel2(0.04,0.03, "",kOrange+3);
  }
  if(i==4) {
    QQBARLabel2(0.04,0.082, "K_{reco}<"+kvalue+" GeV & m_{j_{1} j_{2}}>250 GeV & Npfos Veto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cnpfos Veto ",kOrange+3);
  }
  if(i==5) {
    QQBARLabel2(0.04,0.082, "K_{reco}<"+kvalue+" GeV & m_{j_{1} j_{2}}>250 GeV & Npfos Veto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cnpfos Veto & Photon Veto ",kOrange+3);
  }
  if(i==6) {
    QQBARLabel2(0.04,0.082, "K_{reco}<"+kvalue+" GeV & m_{j_{1} j_{2}}>250 GeV & NpfosVeto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cnpfos Veto & Photon Veto & y_{23}<0.005 ",kOrange+3);
  }
  if(i==7) {
    QQBARLabel2(0.04,0.082, "K_{reco}<"+kvalue+" GeV & m_{j_{1} j_{2}}>250 GeV & NpfosVeto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cnpfos Veto & Photon Veto & y_{23}<0.005 & m_{j_{1}}+m_{j_{2}}<140 GeV  ",kOrange+3);
  }
 if(i==8) {
    QQBARLabel2(0.04,0.082, "K_{reco}<"+kvalue+" GeV & m_{j_{1} j_{2}}>250 GeV & NpfosVeto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cnpfos Veto & Photon Veto & y_{23}<0.005 & m_{j_{1}}+m_{j_{2}}<140 GeV & B-tag  ",kOrange+3);
  }
 if(i==9) {
    QQBARLabel2(0.04,0.082, "K_{reco}<"+kvalue+" GeV & m_{j_{1} j_{2}}>250 GeV & NpfosVeto",kOrange+3);
    QQBARLabel2(0.04,0.03, "& Cnpfos Veto & Photon Veto & y_{23}<0.005 & m_{j_{1}}+m_{j_{2}}<140 GeV & C-tag  ",kOrange+3);
  }
 if(pol=="eL_pR")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 46 fb^{-1}",kGray+2);
 if(pol=="eR_pL")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 250 GeV, 46 fb^{-1}",kGray+2);
 /*
 if(pol=="eL_pR")QQBARLabel2(0.3,0.97, "e_{L}^{-}e_{R}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 241.1 fb^{-1}",kGray+2);
 if(pol=="eR_pL")QQBARLabel2(0.3,0.97, "e_{R}^{-}e_{L}^{+} #rightarrow q#bar{q}, q=udscb, 500 GeV, 429.6 fb^{-1}",kGray+2);
 */
}


// ------------------------------------------------------------
// ------------------------------------------------------------
void analysis250GeV(int cut, TString pol, TString kvalue, TString cat, TString quality) {

    // No cut (100%):
    TString sel="_";//"_tight_";
    TString folder="../output/";
    TString cutname=TString::Format("selection_cuts%i_", int(cut));
    
    
    // TString folder=TString::Format("../output/selection_cuts%i_",cuts);
    TString filename = folder+"selection_cuts0_"+"2f_hadronic_sample_"+cat+"_BDT_"+quality+"_"+pol+"_Kgamma"+kvalue+"_250GeV.root";
    //TString filename = folder+"selection_cuts0_"+"qqbar_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filename = folder+"selection_cuts0_"+"2f_hadronic_sample_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenameWW = folder+"selection_cuts0_"+"4f_WW_hadronic_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenameZZ = folder+"selection_cuts0_"+"4f_ZZ_hadronic_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenameTT = folder+"selection_cuts0_"+"6f_ttbar_merged_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenameTT_yyuyyu = folder+"selection_cuts0_"+"6f_ttbar_yyuyyu_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenameTT_yyuyyc = folder+"selection_cuts0_"+"6f_ttbar_yyuyyc_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenameTT_yycyyu = folder+"selection_cuts0_"+"6f_ttbar_yycyyu_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenameTT_yycyyc = folder+"selection_cuts0_"+"6f_ttbar_yycyyc_"+pol+"_Kgamma"+kvalue+"_500GeV.root";

    TFile *f = new TFile(filename);  
    //TFile *fWW = new TFile(filenameWW);  
    //TFile *fZZ = new TFile(filenameZZ);  
    //TFile *fTT = new TFile(filenameTT);
    //TFile *fTT_yyuyyu = new TFile(filenameTT_yyuyyu);
    //TFile *fTT_yyuyyc = new TFile(filenameTT_yyuyyc);
    //TFile *fTT_yycyyu = new TFile(filenameTT_yycyyu);
    //TFile *fTT_yycyyc = new TFile(filenameTT_yycyyc);

    
    // All flavours:

    TH1F *h_costheta_uu = (TH1F*)f->Get("h_costheta_uu");
    TH1F *h_costheta_dd = (TH1F*)f->Get("h_costheta_dd");
    TH1F *h_costheta_ss = (TH1F*)f->Get("h_costheta_ss");
    TH1F *h_costheta_bb = (TH1F*)f->Get("h_costheta_bb");
    TH1F *h_costheta_cc = (TH1F*)f->Get("h_costheta_cc");
    TH1F *h_costheta_qq = (TH1F*)f->Get("h_costheta_qq");
    TH1F *h_costheta_radreturn = (TH1F*)f->Get("h_costheta_radreturn");
    //TH1F *h_costheta_WW_aux = (TH1F*)fWW->Get("h_costheta_bb");
    //TH1F *h_costheta_ZZ_aux = (TH1F*)fZZ->Get("h_costheta_bb");
    //TH1F *h_costheta_WW = (TH1F*)fWW->Get("h_costheta_bb")->Clone("h_costheta_WW");
    //TH1F *h_costheta_ZZ = (TH1F*)fZZ->Get("h_costheta_bb")->Clone("h_costheta_ZZ");
    //TH1F *h_costheta_TT_aux = (TH1F*)fTT->Get("h_costheta_bb");
    //TH1F *h_costheta_TT = (TH1F*)fTT->Get("h_costheta_bb")->Clone("h_costheta_TT");

    //TH1F *h_costheta_TT_yyuyyu_aux = (TH1F*)fTT_yyuyyu->Get("h_costheta_bb");
    //TH1F *h_costheta_TT_yyuyyu = (TH1F*)fTT_yyuyyu->Get("h_costheta_bb")->Clone("h_costheta_TT_yyuyyu");
    //TH1F *h_costheta_TT_yyuyyc_aux = (TH1F*)fTT_yyuyyc->Get("h_costheta_bb");
    //TH1F *h_costheta_TT_yyuyyc = (TH1F*)fTT_yyuyyc->Get("h_costheta_bb")->Clone("h_costheta_TT_yyuyyc");
    //TH1F *h_costheta_TT_yycyyu_aux = (TH1F*)fTT_yycyyu->Get("h_costheta_bb");
    //TH1F *h_costheta_TT_yycyyu = (TH1F*)fTT_yycyyu->Get("h_costheta_bb")->Clone("h_costheta_TT_yycyyu");
    //TH1F *h_costheta_TT_yycyyc_aux = (TH1F*)fTT_yycyyc->Get("h_costheta_bb");
    //TH1F *h_costheta_TT_yycyyc = (TH1F*)fTT_yycyyc->Get("h_costheta_bb")->Clone("h_costheta_TT_yycyyc");
    
    h_costheta_uu->Sumw2();
    h_costheta_dd->Sumw2();
    h_costheta_ss->Sumw2();
    h_costheta_bb->Sumw2();
    h_costheta_cc->Sumw2();
    h_costheta_qq->Sumw2();
    h_costheta_radreturn->Sumw2();
    
    // Ahora cargo el cut:

    //TString filenamecut = folder+cutname+"qqbar_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    TString filenamecut = folder+"selection_cuts"+cut+"_2f_hadronic_sample_"+cat+"_BDT_"+quality+"_"+pol+"_Kgamma"+kvalue+"_250GeV.root";
    //TString filenamecut = folder+cutname+"2f_hadronic_sample_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenamecutWW = folder+cutname+"4f_WW_hadronic_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenamecutZZ = folder+cutname+"4f_ZZ_hadronic_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenamecutTT = folder+cutname+"6f_ttbar_merged_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenamecutTT_yyuyyu = folder+cutname+"6f_ttbar_yyuyyu_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenamecutTT_yyuyyc = folder+cutname+"6f_ttbar_yyuyyc_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenamecutTT_yycyyu = folder+cutname+"6f_ttbar_yycyyu_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    //TString filenamecutTT_yycyyc = folder+cutname+"6f_ttbar_yycyyc_"+pol+"_Kgamma"+kvalue+"_500GeV.root";
    
    TFile *fcut = new TFile(filenamecut);
    //TFile *fcutWW = new TFile(filenamecutWW);
    //TFile *fcutZZ = new TFile(filenamecutZZ);
    //TFile *fcutTT = new TFile(filenamecutTT);
    //TFile *fcutTT_yyuyyu = new TFile(filenamecutTT_yyuyyu);
    //TFile *fcutTT_yyuyyc = new TFile(filenamecutTT_yyuyyc);
    //TFile *fcutTT_yycyyu = new TFile(filenamecutTT_yycyyu);
    //TFile *fcutTT_yycyyc = new TFile(filenamecutTT_yycyyc);

    
   
    TH1F *h_costheta_uu_cut = (TH1F*)fcut->Get("h_costheta_uu");
    TH1F *h_costheta_dd_cut = (TH1F*)fcut->Get("h_costheta_dd");
    TH1F *h_costheta_ss_cut = (TH1F*)fcut->Get("h_costheta_ss");
    TH1F *h_costheta_bb_cut = (TH1F*)fcut->Get("h_costheta_bb");
    TH1F *h_costheta_cc_cut = (TH1F*)fcut->Get("h_costheta_cc");
    TH1F *h_costheta_qq_cut = (TH1F*)fcut->Get("h_costheta_qq");
    TH1F *h_costheta_radreturn_cut = (TH1F*)fcut->Get("h_costheta_radreturn");
    //TH1F *h_costheta_WW_cut = (TH1F*)fcutWW->Get("h_costheta_bb");
    //TH1F *h_costheta_ZZ_cut = (TH1F*)fcutZZ->Get("h_costheta_bb");
    //TH1F *h_costheta_TT_cut = (TH1F*)fcutTT->Get("h_costheta_bb");
    
    //TH1F *h_costheta_TT_yyuyyu_cut = (TH1F*)fcutTT_yyuyyu->Get("h_costheta_bb");
    //TH1F *h_costheta_TT_yyuyyc_cut = (TH1F*)fcutTT_yyuyyc->Get("h_costheta_bb");
    //TH1F *h_costheta_TT_yycyyu_cut = (TH1F*)fcutTT_yycyyu->Get("h_costheta_bb");
    //TH1F *h_costheta_TT_yycyyc_cut = (TH1F*)fcutTT_yycyyc->Get("h_costheta_bb");
    h_costheta_uu_cut->Sumw2();
    h_costheta_dd_cut->Sumw2();
    h_costheta_ss_cut->Sumw2();
    h_costheta_bb_cut->Sumw2();
    h_costheta_cc_cut->Sumw2();
    h_costheta_qq_cut->Sumw2();
    h_costheta_radreturn_cut->Sumw2();

    
    // Total angular distribution:
   
    TH1F *h_mc_costheta_uu_cut = (TH1F*)fcut->Get("h_mc_costheta_uu");
    TH1F *h_mc_costheta_dd_cut = (TH1F*)fcut->Get("h_mc_costheta_dd");
    TH1F *h_mc_costheta_ss_cut = (TH1F*)fcut->Get("h_mc_costheta_ss");
    TH1F *h_mc_costheta_bb_cut = (TH1F*)fcut->Get("h_mc_costheta_bb");
    TH1F *h_mc_costheta_bb_isr_cut = (TH1F*)fcut->Get("h_mc_costheta_bb_isr");
    TH1F *h_mc_costheta_cc_cut = (TH1F*)fcut->Get("h_mc_costheta_cc");
    TH1F *h_mc_costheta_cc_isr_cut = (TH1F*)fcut->Get("h_mc_costheta_cc_isr");
    TH1F *h_mc_costheta_qq_cut = (TH1F*)fcut->Get("h_mc_costheta_qq");
    TH1F *h_mc_costheta_radreturn_cut = (TH1F*)fcut->Get("h_mc_costheta_radreturn");
    //TH1F *h_mc_costheta_WW_cut = (TH1F*)fcutWW->Get("h_mc_costheta_bb");
    //TH1F *h_mc_costheta_ZZ_cut = (TH1F*)fcutZZ->Get("h_mc_costheta_bb");
    //TH1F *h_mc_costheta_TT_cut = (TH1F*)fcutTT->Get("h_mc_costheta_bb");
    
    //TH1F *h_mc_costheta_TT_yyuyyu_cut = (TH1F*)fcutTT_yyuyyu->Get("h_mc_costheta_bb");
    //TH1F *h_mc_costheta_TT_yyuyyc_cut = (TH1F*)fcutTT_yyuyyc->Get("h_mc_costheta_bb");
    //TH1F *h_mc_costheta_TT_yycyyu_cut = (TH1F*)fcutTT_yycyyu->Get("h_mc_costheta_bb");
    //TH1F *h_mc_costheta_TT_yycyyc_cut = (TH1F*)fcutTT_yycyyc->Get("h_mc_costheta_bb");
    h_mc_costheta_uu_cut->Sumw2();
    h_mc_costheta_dd_cut->Sumw2();
    h_mc_costheta_ss_cut->Sumw2();
    h_mc_costheta_bb_cut->Sumw2();
    h_mc_costheta_bb_isr_cut->Sumw2();
    h_mc_costheta_cc_cut->Sumw2();
    h_mc_costheta_cc_isr_cut->Sumw2();
    h_mc_costheta_qq_cut->Sumw2();
    h_mc_costheta_radreturn_cut->Sumw2();
    
    
    // Total angular distribution com frame:
   
    TH1F *h_mc_com_costheta_uu_cut = (TH1F*)fcut->Get("h_mc_com_costheta_uu");
    TH1F *h_mc_com_costheta_dd_cut = (TH1F*)fcut->Get("h_mc_com_costheta_dd");
    TH1F *h_mc_com_costheta_ss_cut = (TH1F*)fcut->Get("h_mc_com_costheta_ss");
    TH1F *h_mc_com_costheta_bb_isr_cut = (TH1F*)fcut->Get("h_mc_com_costheta_bb_isr");
    TH1F *h_mc_com_costheta_bb_cut = (TH1F*)fcut->Get("h_mc_com_costheta_bb");
    TH1F *h_mc_com_costheta_cc_isr_cut = (TH1F*)fcut->Get("h_mc_com_costheta_cc_isr");
    TH1F *h_mc_com_costheta_cc_cut = (TH1F*)fcut->Get("h_mc_com_costheta_cc");
    TH1F *h_mc_com_costheta_qq_cut = (TH1F*)fcut->Get("h_mc_com_costheta_qq");
    TH1F *h_mc_com_costheta_radreturn_cut = (TH1F*)fcut->Get("h_mc_costheta_radreturn");
    //TH1F *h_mc_com_costheta_WW_cut = (TH1F*)fcutWW->Get("h_mc_costheta_bb");
    //TH1F *h_mc_com_costheta_ZZ_cut = (TH1F*)fcutZZ->Get("h_mc_costheta_bb");
    //TH1F *h_mc_com_costheta_TT_cut = (TH1F*)fcutTT->Get("h_mc_costheta_bb");
    
    //TH1F *h_mc_com_costheta_TT_yyuyyu_cut = (TH1F*)fcutTT_yyuyyu->Get("h_mc_costheta_bb");
    //TH1F *h_mc_com_costheta_TT_yyuyyc_cut = (TH1F*)fcutTT_yyuyyc->Get("h_mc_costheta_bb");
    //TH1F *h_mc_com_costheta_TT_yycyyu_cut = (TH1F*)fcutTT_yycyyu->Get("h_mc_costheta_bb");
    //TH1F *h_mc_com_costheta_TT_yycyyc_cut = (TH1F*)fcutTT_yycyyc->Get("h_mc_costheta_bb");
    h_mc_com_costheta_uu_cut->Sumw2();
    h_mc_com_costheta_dd_cut->Sumw2();
    h_mc_com_costheta_ss_cut->Sumw2();
    h_mc_com_costheta_bb_cut->Sumw2();
    h_mc_com_costheta_bb_isr_cut->Sumw2();
    h_mc_com_costheta_cc_cut->Sumw2();
    h_mc_com_costheta_cc_isr_cut->Sumw2();
    h_mc_com_costheta_qq_cut->Sumw2();
    h_mc_com_costheta_radreturn_cut->Sumw2();

    


    // Luminosity Balance:

    float countbb=h_costheta_bb->GetEntries();
    float countcc=h_costheta_cc->GetEntries();
    float countuds=h_costheta_qq->GetEntries();
    float countqq=countbb+countcc+countuds;
    //float countWW=h_costheta_WW_aux->GetEntries();
    //float countZZ=h_costheta_ZZ_aux->GetEntries();
    //float countTT=h_costheta_TT_aux->GetEntries();
    //float countTT_yyuyyu=h_costheta_TT_yyuyyu_aux->GetEntries();
    //float countTT_yyuyyc=h_costheta_TT_yyuyyc_aux->GetEntries();
    //float countTT_yycyyu=h_costheta_TT_yycyyu_aux->GetEntries();
    //float countTT_yycyyc=h_costheta_TT_yycyyc_aux->GetEntries();

    //-------
    int polarisation;
    if(pol=="eL_pR"){polarisation=0;};
    if(pol=="eR_pL"){polarisation=1;};
    
    //float luminosity=countqq/cross_section[polarisation][3];
    /*float luminosity=luminosity_2f_hadronic[polarisation];
    float luminosityWW=countWW/cross_section[polarisation][2];
    float luminosityZZ=countZZ/cross_section[polarisation][0];
    float luminosityTT_yyuyyu=countTT_yyuyyu/cross_section[polarisation][5];
    float luminosityTT_yyuyyc=countTT_yyuyyu/cross_section[polarisation][6];
    float luminosityTT_yycyyu=countTT_yyuyyu/cross_section[polarisation][7];
    float luminosityTT_yycyyc=countTT_yyuyyu/cross_section[polarisation][8];
    float luminosityTT=luminosityTT_yyuyyu+luminosityTT_yycyyu+luminosityTT_yyuyyc+luminosityTT_yycyyc;

    cout<<"luminosityqq: "<<luminosity<<endl;
    */
    //h_costheta_WW->Scale(luminosity/luminosityWW);
    //h_costheta_ZZ->Scale(luminosity/luminosityZZ);
    //h_costheta_TT->Scale(luminosity/luminosityTT);
    //h_costheta_TT_yyuyyu->Scale(luminosity/luminosityTT_yyuyyu);
    //h_costheta_TT_yyuyyc->Scale(luminosity/luminosityTT_yyuyyc);
    //h_costheta_TT_yycyyu->Scale(luminosity/luminosityTT_yycyyu);
    //h_costheta_TT_yycyyc->Scale(luminosity/luminosityTT_yycyyc);
    
    //h_costheta_WW_cut->Scale(luminosity/luminosityWW);
    //h_costheta_ZZ_cut->Scale(luminosity/luminosityZZ);    
    //h_costheta_TT_cut->Scale(luminosity/luminosityTT);
    //h_costheta_TT_yyuyyu_cut->Scale(luminosity/luminosityTT_yyuyyu);
    //h_costheta_TT_yyuyyc_cut->Scale(luminosity/luminosityTT_yyuyyc);
    //h_costheta_TT_yycyyu_cut->Scale(luminosity/luminosityTT_yycyyu);
    //h_costheta_TT_yycyyc_cut->Scale(luminosity/luminosityTT_yycyyc);

    //Total TT sum:
    //TH1F *h_costheta_TT_sum = (TH1F*)h_costheta_TT_yyuyyu->Clone();
    //h_costheta_TT_sum->Add(h_costheta_TT_yyuyyc);
    //h_costheta_TT_sum->Add(h_costheta_TT_yycyyu);
    //h_costheta_TT_sum->Add(h_costheta_TT_yycyyc);
    //TH1F *h_costheta_TT_sum_cut = (TH1F*)h_costheta_TT_yyuyyu_cut->Clone();
    //h_costheta_TT_sum_cut->Add(h_costheta_TT_yyuyyc_cut);    
    //h_costheta_TT_sum_cut->Add(h_costheta_TT_yycyyu_cut);
    //h_costheta_TT_sum_cut->Add(h_costheta_TT_yycyyc_cut);

    // Total angular distribution
    // h_mc_costheta_WW->Scale(luminosity/luminosityWW);
    // h_mc_costheta_ZZ->Scale(luminosity/luminosityZZ);
    // h_mc_costheta_TT->Scale(luminosity/luminosityTT);
    // h_mc_costheta_TT_yyuyyu->Scale(luminosity/luminosityTT_yyuyyu);
    // h_mc_costheta_TT_yyuyyc->Scale(luminosity/luminosityTT_yyuyyc);
    // h_mc_costheta_TT_yycyyu->Scale(luminosity/luminosityTT_yycyyu);
    // h_mc_costheta_TT_yycyyc->Scale(luminosity/luminosityTT_yycyyc);
    
    //h_mc_costheta_WW_cut->Scale(luminosity/luminosityWW);
    //h_mc_costheta_ZZ_cut->Scale(luminosity/luminosityZZ);    
    //h_mc_costheta_TT_cut->Scale(luminosity/luminosityTT);
    //h_mc_costheta_TT_yyuyyu_cut->Scale(luminosity/luminosityTT_yyuyyu);
    //h_mc_costheta_TT_yyuyyc_cut->Scale(luminosity/luminosityTT_yyuyyc);
    //h_mc_costheta_TT_yycyyu_cut->Scale(luminosity/luminosityTT_yycyyu);
    //h_mc_costheta_TT_yycyyc_cut->Scale(luminosity/luminosityTT_yycyyc);

    // Total TT sum:
    // TH1F *h_mc_costheta_TT_sum = (TH1F*)h_mc_costheta_TT_yyuyyu->Clone();
    // h_mc_costheta_TT_sum->Add(h_mc_costheta_TT_yyuyyc);
    // h_mc_costheta_TT_sum->Add(h_mc_costheta_TT_yycyyu);
    // h_mc_costheta_TT_sum->Add(h_mc_costheta_TT_yycyyc);
    //TH1F *h_mc_costheta_TT_sum_cut = (TH1F*)h_mc_costheta_TT_yyuyyu_cut->Clone();
    //h_mc_costheta_TT_sum_cut->Add(h_mc_costheta_TT_yyuyyc_cut);    
    //h_mc_costheta_TT_sum_cut->Add(h_mc_costheta_TT_yycyyu_cut);
    //h_mc_costheta_TT_sum_cut->Add(h_mc_costheta_TT_yycyyc_cut);

    // Calculating AFB:
    int bin_B = h_mc_costheta_bb_cut->GetXaxis()->FindBin(-0.99999999);
    int bin_0 = h_mc_costheta_bb_cut->GetXaxis()->FindBin(-0.00000001);
    int bin_F = h_mc_costheta_bb_cut->GetXaxis()->FindBin(+0.99999999);
    int NBIN_AFB= h_mc_costheta_bb_cut->GetNbinsX();
    int BinDifference_AFB=NBIN_AFB*0.1/2;

    float NF_b=h_mc_costheta_bb_cut->Integral(bin_0+1,bin_F);
    float NB_b=h_mc_costheta_bb_cut->Integral(bin_B,bin_0);
    float stat_error_AFB_b=pow(pow(pow(NF_b,0.5)*((2*NB_b)/(pow(NF_b+NB_b,2))),2)+pow(pow(NB_b,0.5)*((2*NF_b)/(pow(NF_b+NB_b,2))),2),0.5);
    float AFB_b=(NF_b-NB_b)/(NF_b+NB_b);
    float NF_c=h_mc_costheta_cc_cut->Integral(bin_0+1,bin_F);
    float NB_c=h_mc_costheta_cc_cut->Integral(bin_B,bin_0);
    float stat_error_AFB_c=pow(pow(pow(NF_c,0.5)*((2*NB_c)/(pow(NF_c+NB_c,2))),2)+pow(pow(NB_c,0.5)*((2*NF_c)/(pow(NF_c+NB_c,2))),2),0.5);
    float AFB_c=(NF_c-NB_c)/(NF_c+NB_c);
    //isr
    float NF_b_isr=h_mc_costheta_bb_isr_cut->Integral(bin_0+1,bin_F);
    float NB_b_isr=h_mc_costheta_bb_isr_cut->Integral(bin_B,bin_0);
    float stat_error_AFB_b_isr=pow(pow(pow(NF_b_isr,0.5)*((2*NB_b_isr)/(pow(NF_b_isr+NB_b_isr,2))),2)+pow(pow(NB_b_isr,0.5)*((2*NF_b_isr)/(pow(NF_b_isr+NB_b_isr,2))),2),0.5);
    float AFB_b_isr=(NF_b_isr-NB_b_isr)/(NF_b_isr+NB_b_isr);
    float NF_c_isr=h_mc_costheta_cc_isr_cut->Integral(bin_0+1,bin_F);
    float NB_c_isr=h_mc_costheta_cc_isr_cut->Integral(bin_B,bin_0);
    float stat_error_AFB_c_isr=pow(pow(pow(NF_c_isr,0.5)*((2*NB_c_isr)/(pow(NF_c_isr+NB_c_isr,2))),2)+pow(pow(NB_c_isr,0.5)*((2*NF_c_isr)/(pow(NF_c_isr+NB_c_isr,2))),2),0.5);
    float AFB_c_isr=(NF_c_isr-NB_c_isr)/(NF_c_isr+NB_c_isr);
    //cout<<"bins: "<<bin_B<<" "<<bin_0<<" "<<bin_F<<endl;
    //cout<<"bins Limited: "<<BinDifference_AFB<<" "<<bin_0<<" "<<bin_F-BinDifference_AFB<<endl;
    //cout<<"NF_b: "<<NF_b<<" NB_b: "<<NB_b <<endl;
    //cout<<"NF_c: "<<NF_c<<" NB_c: "<<NB_c <<endl;
    cout<<"AFB | b quark | c quark"<<endl;
    cout<<"    | "<<AFB_b<<" | "<<AFB_c<<endl;
    cout<<"    | "<<stat_error_AFB_b<<" | "<<stat_error_AFB_c<<endl;
    cout<<"AFB (isr) | b quark | c quark"<<endl;
    cout<<"          | "<<AFB_b_isr<<" | "<<AFB_c_isr<<endl;
    cout<<"    | "<<stat_error_AFB_b_isr<<" | "<<stat_error_AFB_c_isr<<endl;
    
    // Calculating AFB com frame:
    float NF_b_com=h_mc_com_costheta_bb_cut->Integral(bin_0+1,bin_F);
    float NB_b_com=h_mc_com_costheta_bb_cut->Integral(bin_B,bin_0);
    float stat_error_AFB_b_com=pow(pow(pow(NF_b_com,0.5)*((2*NB_b_com)/(pow(NF_b_com+NB_b_com,2))),2)+pow(pow(NB_b_com,0.5)*((2*NF_b_com)/(pow(NF_b_com+NB_b_com,2))),2),0.5);
    float AFB_b_com=(NF_b_com-NB_b_com)/(NF_b_com+NB_b_com);
    float NF_c_com=h_mc_com_costheta_cc_cut->Integral(bin_0+1,bin_F);
    float NB_c_com=h_mc_com_costheta_cc_cut->Integral(bin_B,bin_0);
    float stat_error_AFB_c_com=pow(pow(pow(NF_c_com,0.5)*((2*NB_c_com)/(pow(NF_c_com+NB_c_com,2))),2)+pow(pow(NB_c_com,0.5)*((2*NF_c_com)/(pow(NF_c_com+NB_c_com,2))),2),0.5);
    float AFB_c_com=(NF_c_com-NB_c_com)/(NF_c_com+NB_c_com);
    //isr
    float NF_b_isr_com=h_mc_com_costheta_bb_isr_cut->Integral(bin_0+1,bin_F);
    float NB_b_isr_com=h_mc_com_costheta_bb_isr_cut->Integral(bin_B,bin_0);
    float stat_error_AFB_b_isr_com=pow(pow(pow(NF_b_isr_com,0.5)*((2*NB_b_isr_com)/(pow(NF_b_isr_com+NB_b_isr_com,2))),2)+pow(pow(NB_b_isr_com,0.5)*((2*NF_b_isr_com)/(pow(NF_b_isr_com+NB_b_isr_com,2))),2),0.5);
    float AFB_b_isr_com=(NF_b_isr_com-NB_b_isr_com)/(NF_b_isr_com+NB_b_isr_com);
    float NF_c_isr_com=h_mc_com_costheta_cc_isr_cut->Integral(bin_0+1,bin_F);
    float NB_c_isr_com=h_mc_com_costheta_cc_isr_cut->Integral(bin_B,bin_0);
    float stat_error_AFB_c_isr_com=pow(pow(pow(NF_c_isr_com,0.5)*((2*NB_c_isr_com)/(pow(NF_c_isr_com+NB_c_isr_com,2))),2)+pow(pow(NB_c_isr_com,0.5)*((2*NF_c_isr_com)/(pow(NF_c_isr_com+NB_c_isr_com,2))),2),0.5);
    float AFB_c_isr_com=(NF_c_isr_com-NB_c_isr_com)/(NF_c_isr_com+NB_c_isr_com);
    cout<<"--Center-of-mass frame--"<<endl;
    //cout<<"NF_b_com: "<<NF_b_com<<" NB_b_com: "<<NB_b_com <<endl;
    //cout<<"NF_c_com: "<<NF_c_com<<" NB_c_com: "<<NB_c_com <<endl;
    cout<<"AFB (com) | b quark | c quark"<<endl;
    cout<<"          | "<<AFB_b_com<<" | "<<AFB_c_com<<endl;
    cout<<"          | "<<stat_error_AFB_b_com<<" | "<<stat_error_AFB_c_com<<endl;
    cout<<"AFB (com-isr) | b quark | c quark"<<endl;
    cout<<"              | "<<AFB_b_isr_com<<" | "<<AFB_c_isr_com<<endl;
    cout<<"              | "<<stat_error_AFB_b_isr_com<<" | "<<stat_error_AFB_c_isr_com<<endl;
    

    // Calculating AFB Limited:
    float NF_b_L=h_mc_costheta_bb_cut->Integral(bin_0+1,bin_F-BinDifference_AFB-1);
    float NB_b_L=h_mc_costheta_bb_cut->Integral(BinDifference_AFB+1,bin_0);
    float AFB_b_L=(NF_b_L-NB_b_L)/(NF_b_L+NB_b_L);
    float NF_c_L=h_mc_costheta_cc_cut->Integral(bin_0+1,bin_F-BinDifference_AFB-1);
    float NB_c_L=h_mc_costheta_cc_cut->Integral(BinDifference_AFB+1,bin_0);
    float AFB_c_L=(NF_c_L-NB_c_L)/(NF_c_L+NB_c_L);
    
      
    cout<<"---------------LIMITED---------------"<<endl;
    //cout<<"NF_b_L: "<<NF_b_L<<" NB_b_L: "<<NB_b_L<<endl;
    //cout<<"NF_c_L: "<<NF_c_L<<" NB_c_L: "<<NB_c_L<<endl;
    cout<<"AFB L | b quark | c quark"<<endl;
    cout<<"      | "<<AFB_b_L<<" | "<<AFB_c_L<<endl;
    
    // Calculating AFB com frame Limited:
    float NF_b_com_L=h_mc_com_costheta_bb_cut->Integral(bin_0+1,bin_F-BinDifference_AFB-1);
    float NB_b_com_L=h_mc_com_costheta_bb_cut->Integral(BinDifference_AFB+1,bin_0);
    float AFB_b_com_L=(NF_b_com_L-NB_b_com_L)/(NF_b_com_L+NB_b_com_L);
    float NF_c_com_L=h_mc_com_costheta_cc_cut->Integral(bin_0+1,bin_F-BinDifference_AFB-1);
    float NB_c_com_L=h_mc_com_costheta_cc_cut->Integral(BinDifference_AFB+1,bin_0);
    float AFB_c_com_L=(NF_c_com_L-NB_c_com_L)/(NF_c_com_L+NB_c_com_L);
    cout<<"--Center-of-mass frame--"<<endl;
    //cout<<"NF_b_com_L: "<<NF_b_com_L<<" NB_b_com_L: "<<NB_b_com_L<<endl;
    //cout<<"NF_c_com_L: "<<NF_c_com_L<<" NB_c_com_L: "<<NB_c_com_L<<endl;
    cout<<"AFB (com) L | b quark | c quark"<<endl;
    cout<<"            | "<<AFB_b_com_L<<" | "<<AFB_c_com_L<<endl;

    


    SetQQbarStyle();
    gStyle->SetOptFit(0); 
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
  
    gStyle->SetTitleBorderSize(0);
    gStyle->SetTitleStyle(0);
    gStyle->SetTitleX(0.2);
    gStyle->SetMarkerSize(1.5);
    
    // Monte-Carlo quark distribution  
    TCanvas *canvas_mc_bb_costheta = new TCanvas("mc_bb","mc_bb",800,800);
    canvas_mc_bb_costheta->cd(1);   
    h_mc_costheta_bb_cut->SetTitle("Monte-Carlo b #bar{b}");
    h_mc_costheta_bb_cut->GetYaxis()->SetTitle("Events");
    h_mc_costheta_bb_cut->GetXaxis()->SetTitle("cos #theta_{q}");
    h_mc_costheta_bb_cut->SetLineColor(4);
    h_mc_costheta_bb_cut->GetYaxis()->SetRangeUser(0,5000);
    h_mc_costheta_bb_cut->GetXaxis()->SetRangeUser(-1,1);
    h_mc_costheta_bb_cut->Draw("histo");
    Labels(int(cut),pol,kvalue);
    TLegend *mc_bb_leg = new TLegend(0.3,0.2,0.5,0.4);//(0.4,0.3,0.5,0.6);
    mc_bb_leg->SetTextSize(0.030);
    mc_bb_leg->AddEntry(h_mc_costheta_bb_cut,"#font[42]{b#bar{b}}","l");
    mc_bb_leg->SetFillStyle(0);
    mc_bb_leg->SetLineWidth(0);
    mc_bb_leg->SetLineColor(0);
    mc_bb_leg->SetBorderSize(0);
    mc_bb_leg->Draw();
    //canvas_mc_bb_costheta->SaveAs("bb_mc_hist.png");
    
    TCanvas *canvas_mc_cc_costheta = new TCanvas("mc_cc","mc_cc",800,800);
    canvas_mc_cc_costheta->cd(1); 
    h_mc_costheta_cc_cut->SetTitle("Monte-Carlo b #bar{b}");
    h_mc_costheta_cc_cut->GetYaxis()->SetTitle("Events");
    h_mc_costheta_cc_cut->GetXaxis()->SetTitle("cos #theta_{q}");
    h_mc_costheta_cc_cut->SetLineColor(4);
    h_mc_costheta_cc_cut->GetYaxis()->SetRangeUser(0,5000);
    h_mc_costheta_cc_cut->GetXaxis()->SetRangeUser(-1,1);
    h_mc_costheta_cc_cut->Draw("histo");
    Labels(int(cut),pol,kvalue);
    TLegend *mc_cc_leg = new TLegend(0.3,0.2,0.5,0.4);//(0.4,0.3,0.5,0.6);
    mc_cc_leg->SetTextSize(0.030);
    mc_cc_leg->AddEntry(h_mc_costheta_cc_cut,"#font[42]{c#bar{c}}","l");
    mc_cc_leg->SetFillStyle(0);
    mc_cc_leg->SetLineWidth(0);
    mc_cc_leg->SetLineColor(0);
    mc_cc_leg->SetBorderSize(0);
    mc_cc_leg->Draw();
    //canvas_mc_cc_costheta->SaveAs("cc_mc_hist.png");
    
    // Monte-Carlo quark distribution com 
    TCanvas *canvas_mc_com_bb_costheta = new TCanvas("mc_com_bb","mc_com_bb",800,800);
    canvas_mc_com_bb_costheta->cd(1);   
    h_mc_com_costheta_bb_cut->SetTitle("Monte-Carlo b #bar{b}");
    h_mc_com_costheta_bb_cut->GetYaxis()->SetTitle("Events");
    h_mc_com_costheta_bb_cut->GetXaxis()->SetTitle("cos #theta_{q}");
    h_mc_com_costheta_bb_cut->SetLineColor(4);
    h_mc_com_costheta_bb_cut->GetYaxis()->SetRangeUser(0,5000);
    h_mc_com_costheta_bb_cut->GetXaxis()->SetRangeUser(-1,1);
    h_mc_com_costheta_bb_cut->Draw("histo");
    Labels(int(cut),pol,kvalue);
    TLegend *mc_com_bb_leg = new TLegend(0.3,0.2,0.5,0.4);//(0.4,0.3,0.5,0.6);
    mc_com_bb_leg->SetTextSize(0.030);
    mc_com_bb_leg->AddEntry(h_mc_com_costheta_bb_cut,"#font[42]{b#bar{b}}","l");
    mc_com_bb_leg->SetFillStyle(0);
    mc_com_bb_leg->SetLineWidth(0);
    mc_com_bb_leg->SetLineColor(0);
    mc_com_bb_leg->SetBorderSize(0);
    mc_com_bb_leg->Draw();
    //canvas_mc_com_bb_costheta->SaveAs("bb_mc_com_hist.png");
    
    TCanvas *canvas_mc_com_cc_costheta = new TCanvas("mc_com_cc","mc_com_cc",800,800);
    canvas_mc_com_cc_costheta->cd(1); 
    h_mc_com_costheta_cc_cut->SetTitle("Monte-Carlo b #bar{b}");
    h_mc_com_costheta_cc_cut->GetYaxis()->SetTitle("Events");
    h_mc_com_costheta_cc_cut->GetXaxis()->SetTitle("cos #theta_{q}");
    h_mc_com_costheta_cc_cut->SetLineColor(4);
    h_mc_com_costheta_cc_cut->GetYaxis()->SetRangeUser(0,5000);
    h_mc_com_costheta_cc_cut->GetXaxis()->SetRangeUser(-1,1);
    h_mc_com_costheta_cc_cut->Draw("histo");
    Labels(int(cut),pol,kvalue);
    TLegend *mc_com_cc_leg = new TLegend(0.3,0.2,0.5,0.4);//(0.4,0.3,0.5,0.6);
    mc_com_cc_leg->SetTextSize(0.030);
    mc_com_cc_leg->AddEntry(h_mc_com_costheta_cc_cut,"#font[42]{c#bar{c}}","l");
    mc_com_cc_leg->SetFillStyle(0);
    mc_com_cc_leg->SetLineWidth(0);
    mc_com_cc_leg->SetLineColor(0);
    mc_com_cc_leg->SetBorderSize(0);
    mc_com_cc_leg->Draw();
    //canvas_mc_com_cc_costheta->SaveAs("cc_mc_com_hist.png");


    // Events:

    TString canvaslabel = TString::Format("Efficiency (Cut %i )",int(cut));
    TString canvaslabeldist = TString::Format("Events (Cut %i )",int(cut));

    TCanvas *canvascostheta = new TCanvas(canvaslabeldist,canvaslabeldist,800,800);
    canvascostheta->cd(1);
    TH1F *h_costheta_signal_cut = (TH1F*)h_costheta_bb_cut->Clone("h_costheta_signal_cut");
    h_costheta_signal_cut->Add(h_costheta_cc_cut);
    h_costheta_signal_cut->Add(h_costheta_uu_cut);
    h_costheta_signal_cut->Add(h_costheta_dd_cut);
    h_costheta_signal_cut->Add(h_costheta_ss_cut);
    h_costheta_signal_cut->SetTitle(canvaslabeldist);
    h_costheta_signal_cut->GetYaxis()->SetTitle("Events");
    h_costheta_signal_cut->GetXaxis()->SetTitle("|cos #theta_{q}|");
    h_costheta_signal_cut->SetLineColor(4);
    h_costheta_signal_cut->GetYaxis()->SetRangeUser(0,5000);
    h_costheta_signal_cut->GetXaxis()->SetRangeUser(0,1);
    h_costheta_signal_cut->Draw("histo");
    
    // h_costheta_bb_cut->SetTitle(canvaslabeldist);
    // h_costheta_bb_cut->GetYaxis()->SetTitle("Events");
    // h_costheta_bb_cut->GetXaxis()->SetTitle("|cos #theta_{q}|");
    // h_costheta_bb_cut->SetLineColor(4);
    // //h_costheta_bb_cut->GetYaxis()->SetRangeUser(0,1.5);
    // h_costheta_bb_cut->GetXaxis()->SetRangeUser(0,1);
    // h_costheta_bb_cut->Draw("histo");
    // h_costheta_uu_cut->SetLineColor(1);
    // h_costheta_uu_cut->Draw("histosame");
    // h_costheta_dd_cut->SetLineColor(8);
    // h_costheta_dd_cut->Draw("histosame");
    // h_costheta_ss_cut->SetLineColor(51);
    // h_costheta_ss_cut->Draw("histosame");
    // h_costheta_cc_cut->SetLineColor(91);
    // h_costheta_cc_cut->Draw("histosame");
    //h_costheta_WW_cut->SetLineStyle(7);
    //h_costheta_WW_cut->SetLineColor(2);
    //h_costheta_WW_cut->Draw("histosame");
    //h_costheta_ZZ_cut->SetLineColor(2);
    //h_costheta_ZZ_cut->SetLineStyle(10);
    //h_costheta_ZZ_cut->Draw("histosame");
    h_costheta_radreturn_cut->SetLineColor(2);
    h_costheta_radreturn_cut->Draw("histosame");
    //h_costheta_TT_sum_cut->SetLineColor(2);
    //h_costheta_TT_sum_cut->SetLineStyle(6);
    //h_costheta_TT_sum_cut->Draw("histosame");
    
    
    // LABEL
    // Copiado literalmente de Adrian, guardar como referencia
    // --------------------------------------------------------------
    // --------------------------------------------------------------
    Labels(int(cut),pol,kvalue);
  
    TLegend *distleg1 = new TLegend(0.3,0.2,0.5,0.4);//(0.4,0.3,0.5,0.6);
    distleg1->SetTextSize(0.030);
    /*distleg1->AddEntry(h_costheta_uu_cut,"#font[42]{u#bar{u}}","l");
    distleg1->AddEntry(h_costheta_dd_cut,"#font[42]{d#bar{d}}","l");
    distleg1->AddEntry(h_costheta_ss_cut,"#font[42]{s#bar{s}}","l");
    distleg1->AddEntry(h_costheta_bb_cut,"#font[42]{b#bar{b}}","l");
    distleg1->AddEntry(h_costheta_cc_cut,"#font[42]{c#bar{c}}","l");*/
    distleg1->AddEntry(h_costheta_signal_cut,"#font[42]{q#bar{q} (q=udscb)}","l");
    distleg1->SetFillStyle(0);
    distleg1->SetLineWidth(0);
    distleg1->SetLineColor(0);
    distleg1->SetBorderSize(0);
    distleg1->Draw();

    TLegend *distleg2 = new TLegend(0.5,0.4,0.75,0.5);//(0.4,0.3,0.5,0.6);
    distleg2->SetTextSize(0.030);
    distleg2->AddEntry(h_costheta_radreturn_cut,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
    /* distleg2->AddEntry(h_y23_hz,"#font[42]{HZ}","l");*/
    //distleg2->AddEntry(h_costheta_TT_sum_cut,"#font[42]{t#bar{t}}","l");
       //distleg2->AddEntry(h_costheta_ZZ_cut,"#font[42]{ZZ}","l");
       //distleg2->AddEntry(h_costheta_WW_cut,"#font[42]{WW}","l");
    distleg2->SetFillStyle(0);
    distleg2->SetLineWidth(0);
    distleg2->SetLineColor(0);
    distleg2->SetBorderSize(0);
    distleg2->Draw();


    // Efficiencies:
    
    // --------------------------------------------------------------
    
    TCanvas *canvascostheta_ratio = new TCanvas(canvaslabel,canvaslabel,800,800);
    canvascostheta_ratio->cd(1);

    TH1F *h_costheta_bb_ratio = (TH1F*)h_costheta_bb_cut->Clone("h_costheta_bb_ratio");
    h_costheta_bb_ratio->Divide(h_costheta_bb);
    h_costheta_bb_ratio->SetTitle(canvaslabel);
    h_costheta_bb_ratio->GetYaxis()->SetTitle("Efficiency");
    h_costheta_bb_ratio->GetXaxis()->SetTitle("|cos #theta_{q}|");
    h_costheta_bb_ratio->SetLineColor(91); //4
    h_costheta_bb_ratio->GetYaxis()->SetRangeUser(0,1.5);
    h_costheta_bb_ratio->GetXaxis()->SetRangeUser(0,1);
    h_costheta_bb_ratio->Draw("histo");

    TH1F *h_costheta_uu_ratio = (TH1F*)h_costheta_uu_cut->Clone("h_costheta_uu_ratio");
    h_costheta_uu_ratio->Divide(h_costheta_uu);
    h_costheta_uu_ratio->SetLineColor(1);
    h_costheta_uu_ratio->Draw("histosame");
    
    TH1F *h_costheta_dd_ratio = (TH1F*)h_costheta_dd_cut->Clone("h_costheta_dd_ratio");
    h_costheta_dd_ratio->Divide(h_costheta_dd);
    h_costheta_dd_ratio->SetLineColor(8);
    h_costheta_dd_ratio->Draw("histosame");

    TH1F *h_costheta_ss_ratio = (TH1F*)h_costheta_ss_cut->Clone("h_costheta_ss_ratio");
    h_costheta_ss_ratio->Divide(h_costheta_ss);
    h_costheta_ss_ratio->SetLineColor(51);
    h_costheta_ss_ratio->Draw("histosame");
    
    TH1F *h_costheta_qq_ratio = (TH1F*)h_costheta_qq_cut->Clone("h_costheta_qq_ratio");
    h_costheta_qq_ratio->Divide(h_costheta_qq);
    h_costheta_qq_ratio->SetLineColor(1);
    // h_costheta_qq_ratio->Draw("histosame");

    TH1F *h_costheta_cc_ratio = (TH1F*)h_costheta_cc_cut->Clone("h_costheta_cc_ratio");
    h_costheta_cc_ratio->Divide(h_costheta_cc);
    h_costheta_cc_ratio->SetLineColor(4); //91
    h_costheta_cc_ratio->Draw("histosame");
    /*    
    TH1F *h_costheta_WW_ratio = (TH1F*)h_costheta_WW_cut->Clone("h_costheta_WW_ratio");
    h_costheta_WW_ratio->Divide(h_costheta_WW);
    h_costheta_WW_ratio->SetLineColor(2);
    h_costheta_WW_ratio->SetLineStyle(7);
    h_costheta_WW_ratio->Draw("histosame");

    
    TH1F *h_costheta_ZZ_ratio = (TH1F*)h_costheta_ZZ_cut->Clone("h_costheta_ZZ_ratio");
    h_costheta_ZZ_ratio->Divide(h_costheta_ZZ);
    h_costheta_ZZ_ratio->SetLineColor(2);
    h_costheta_ZZ_ratio->SetLineStyle(10);
    h_costheta_ZZ_ratio->Draw("histosame");
    
    TH1F *h_costheta_TT_ratio = (TH1F*)h_costheta_TT_sum_cut->Clone("h_costheta_TT_ratio");
    h_costheta_TT_ratio->Divide(h_costheta_TT_sum);
    h_costheta_TT_ratio->SetLineColor(2);
    h_costheta_TT_ratio->SetLineStyle(6);
    h_costheta_TT_ratio->Draw("histosame");
    */
    TH1F *h_costheta_radreturn_ratio = (TH1F*)h_costheta_radreturn_cut->Clone("h_costheta_radreturn_ratio");
    h_costheta_radreturn_ratio->Divide(h_costheta_radreturn);
    h_costheta_radreturn_ratio->SetLineColor(2);
    h_costheta_radreturn_ratio->Draw("histosame");
    // LABEL
    // Copiado literalmente de Adrian, guardar como referencia
    // --------------------------------------------------------------
    // --------------------------------------------------------------
    Labels(int(cut),pol,kvalue);
  
    TLegend *leg1 = new TLegend(0.3,0.7,0.5,0.9);//(0.4,0.3,0.5,0.6);
    leg1->SetTextSize(0.030);
    leg1->AddEntry(h_costheta_uu_ratio,"#font[42]{u#bar{u}}","l");
    leg1->AddEntry(h_costheta_dd_ratio,"#font[42]{d#bar{d}}","l");
    leg1->AddEntry(h_costheta_ss_ratio,"#font[42]{s#bar{s}}","l");
    leg1->AddEntry(h_costheta_bb_ratio,"#font[42]{b#bar{b}}","l");
    leg1->AddEntry(h_costheta_cc_ratio,"#font[42]{c#bar{c}}","l");
    //leg1->AddEntry(h_costheta_qq_ratio,"#font[42]{q#bar{q} (q=uds)}","l");
    leg1->SetFillStyle(0);
    leg1->SetLineWidth(0);
    leg1->SetLineColor(0);
    leg1->SetBorderSize(0);
    leg1->Draw();

    TLegend *leg2 = new TLegend(0.5,0.7,0.75,0.86);//(0.4,0.3,0.5,0.6);
    leg2->SetTextSize(0.030);
    leg2->AddEntry(h_costheta_radreturn_ratio,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
    /* leg2->AddEntry(h_y23_hz,"#font[42]{HZ}","l");*/
    /*   leg2->AddEntry(h_costheta_TT_ratio,"#font[42]{t#bar{t}}","l");
       leg2->AddEntry(h_costheta_ZZ_ratio,"#font[42]{ZZ}","l");
       leg2->AddEntry(h_costheta_WW_ratio,"#font[42]{WW}","l");*/
    leg2->SetFillStyle(0);
    leg2->SetLineWidth(0);
    leg2->SetLineColor(0);
    leg2->SetBorderSize(0);
    leg2->Draw();

    TString cutstring=TString::Format("cut%i",cut);
    canvascostheta_ratio->SaveAs("efficiency_"+cutstring+"_"+pol+"_new.png");

    // --------------------------------------------------------------
    // --------------------------------------------------------------

    // Efficiencies:

    double  h_costheta_uu_cut_total=h_costheta_uu_cut->Integral("all");
    double  h_costheta_uu_total=h_costheta_uu->Integral("all");
    double  uu_ef_total=100*h_costheta_uu_cut_total/h_costheta_uu_total;
    
    double  h_costheta_dd_cut_total=h_costheta_dd_cut->Integral("all");
    double  h_costheta_dd_total=h_costheta_dd->Integral("all");
    double  dd_ef_total=100*h_costheta_dd_cut_total/h_costheta_dd_total;
    
    double  h_costheta_ss_cut_total=h_costheta_ss_cut->Integral("all");
    double  h_costheta_ss_total=h_costheta_ss->Integral("all");
    double  ss_ef_total=100*h_costheta_ss_cut_total/h_costheta_ss_total;
    
    double  h_costheta_bb_cut_total=h_costheta_bb_cut->Integral("all");
    double  h_costheta_bb_total=h_costheta_bb->Integral("all");
    double  bb_ef_total=100*h_costheta_bb_cut_total/h_costheta_bb_total;
    
    double  h_costheta_cc_cut_total=h_costheta_cc_cut->Integral("all");
    double  h_costheta_cc_total=h_costheta_cc->Integral("all");
    double  cc_ef_total=100*h_costheta_cc_cut_total/h_costheta_cc_total;
    
    double  h_costheta_qq_cut_total=h_costheta_qq_cut->Integral("all");
    double  h_costheta_qq_total=h_costheta_qq->Integral("all");
    double  qq_ef_total=100*h_costheta_qq_cut_total/h_costheta_qq_total;
    
    //double  h_costheta_WW_cut_total=h_costheta_WW_cut->Integral("all");
    //double  h_costheta_WW_total=h_costheta_WW->Integral("all");
    //double  WW_ef_total=100*h_costheta_WW_cut_total/h_costheta_WW_total;
    
    //double  h_costheta_ZZ_cut_total=h_costheta_ZZ_cut->Integral("all");
    //double  h_costheta_ZZ_total=h_costheta_ZZ->Integral("all");
    //double  ZZ_ef_total=100*h_costheta_ZZ_cut_total/h_costheta_ZZ_total;
    
    //double  h_costheta_TT_cut_total=h_costheta_TT_sum_cut->Integral("all");
    //double  h_costheta_TT_total=h_costheta_TT_sum->Integral("all");
    //double  TT_ef_total=100*h_costheta_TT_cut_total/h_costheta_TT_total;
    
    double  h_costheta_radreturn_cut_total=h_costheta_radreturn_cut->Integral("all");
    double  h_costheta_radreturn_total=h_costheta_radreturn->Integral("all");
    double  radreturn_ef_total=100*h_costheta_radreturn_cut_total/h_costheta_radreturn_total;


    // Efficiencies limited:
    double  NBIN=h_costheta_bb->GetNbinsX();
    double  LimitBin=NBIN*0.9;
    
    double  h_costheta_uu_cut_total_L=h_costheta_uu_cut->Integral(1,LimitBin);
    double  h_costheta_uu_total_L=h_costheta_uu->Integral(1,LimitBin);
    double  uu_ef_total_L=100*h_costheta_uu_cut_total_L/h_costheta_uu_total_L;
    
    double  h_costheta_dd_cut_total_L=h_costheta_dd_cut->Integral(1,LimitBin);
    double  h_costheta_dd_total_L=h_costheta_dd->Integral(1,LimitBin);
    double  dd_ef_total_L=100*h_costheta_dd_cut_total_L/h_costheta_dd_total_L;
    
    double  h_costheta_ss_cut_total_L=h_costheta_ss_cut->Integral(1,LimitBin);
    double  h_costheta_ss_total_L=h_costheta_ss->Integral(1,LimitBin);
    double  ss_ef_total_L=100*h_costheta_ss_cut_total_L/h_costheta_ss_total_L;
    
    double  h_costheta_bb_cut_total_L=h_costheta_bb_cut->Integral(1,LimitBin);
    double  h_costheta_bb_total_L=h_costheta_bb->Integral(1,LimitBin);
    double  bb_ef_total_L=100*h_costheta_bb_cut_total_L/h_costheta_bb_total_L;
    
    double  h_costheta_cc_cut_total_L=h_costheta_cc_cut->Integral(1,LimitBin);
    double  h_costheta_cc_total_L=h_costheta_cc->Integral(1,LimitBin);
    double  cc_ef_total_L=100*h_costheta_cc_cut_total_L/h_costheta_cc_total_L;
    
    double  h_costheta_qq_cut_total_L=h_costheta_qq_cut->Integral(1,LimitBin);
    double  h_costheta_qq_total_L=h_costheta_qq->Integral(1,LimitBin);
    double  qq_ef_total_L=100*h_costheta_qq_cut_total_L/h_costheta_qq_total_L;
    
    //double  h_costheta_WW_cut_total_L=h_costheta_WW_cut->Integral(1,LimitBin);
    //double  h_costheta_WW_total_L=h_costheta_WW->Integral(1,LimitBin);
    //double  WW_ef_total_L=100*h_costheta_WW_cut_total_L/h_costheta_WW_total_L;
    
    //double  h_costheta_ZZ_cut_total_L=h_costheta_ZZ_cut->Integral(1,LimitBin);
    //double  h_costheta_ZZ_total_L=h_costheta_ZZ->Integral(1,LimitBin);
    //double  ZZ_ef_total_L=100*h_costheta_ZZ_cut_total_L/h_costheta_ZZ_total_L;
    
    //double  h_costheta_TT_cut_total_L=h_costheta_TT_sum_cut->Integral(1,LimitBin);
    //double  h_costheta_TT_total_L=h_costheta_TT_sum->Integral(1,LimitBin);
    //double  TT_ef_total_L=100*h_costheta_TT_cut_total_L/h_costheta_TT_total_L;
    
    double  h_costheta_radreturn_cut_total_L=h_costheta_radreturn_cut->Integral(1,LimitBin);
    double  h_costheta_radreturn_total_L=h_costheta_radreturn->Integral(1,LimitBin);
    double  radreturn_ef_total_L=100*h_costheta_radreturn_cut_total_L/h_costheta_radreturn_total_L;
    



    
    // Table efficiencies:
    cout << "Efficiencies (%)" << endl;
    cout << "bb " << "cc " << "qq " << "radreturn" << endl;
    cout << bb_ef_total << " " <<  cc_ef_total << " " << qq_ef_total << " " << radreturn_ef_total<<endl;
    cout << bb_ef_total_L << " " <<  cc_ef_total_L << " " << qq_ef_total_L << " " << radreturn_ef_total_L <<endl; 
    
    
    // Table efficiencies all flavours:
    /*    cout << "Efficiencies (%)" << endl;
    cout << "uu " << "dd " << "ss " << "bb " << "cc " << "radreturn " << "WW " << "ZZ " << "tt " << endl;

    cout << uu_ef_total << " " << dd_ef_total << " " << ss_ef_total << " " << bb_ef_total << " " <<  cc_ef_total << " "  << radreturn_ef_total << " "  << WW_ef_total << " "  << ZZ_ef_total << " " << TT_ef_total << "|"<< endl;
    cout << uu_ef_total_L << " " << dd_ef_total_L << " " << ss_ef_total_L << " " << bb_ef_total_L << " " <<  cc_ef_total_L << " " << radreturn_ef_total_L << " " << WW_ef_total_L << " " << ZZ_ef_total_L << " " << TT_ef_total_L << "|"<< endl;

    */
    //-----------------------------------------------------------------------------

    
    //CUTS:  
    
    // K
    
    TCanvas *canvasK = new TCanvas("canvasK","canvasK",800,800);
    canvasK->cd(1);
    canvasK->SetLogy();
    TH1F *h_K_radreturn_cut = (TH1F*)fcut->Get("h_K_radreturn");
    //h_K_radreturn_cut->SetLogy();
    h_K_radreturn_cut->SetLineColor(2);
    h_K_radreturn_cut->Draw("histo");
    h_K_radreturn_cut->GetYaxis()->SetTitle("Entries/GeV");
    h_K_radreturn_cut->GetXaxis()->SetTitle("K_{reco} (GeV)");
    TH1F *h_K_bb_cut = (TH1F*)fcut->Get("h_K_bb");
    h_K_bb_cut->SetLineColor(4);
    //h_K_bb_cut->Draw("histosame");
    TH1F *h_K_cc_cut = (TH1F*)fcut->Get("h_K_cc");
    //h_K_cc_cut->SetLineStyle(2);
    //h_K_cc_cut->Draw("histosame");
    TH1F *h_K_qq_cut = (TH1F*)fcut->Get("h_K_qq");
    //h_K_qq_cut->SetLineColor(1);
    //h_K_qq_cut->Draw("histosame");
    /*TH1F *h_K_WW_cut = (TH1F*)fcutWW->Get("h_K_bb");
    h_K_WW_cut->Scale(luminosity/luminosityWW);
    h_K_WW_cut->SetLineStyle(7);
    h_K_WW_cut->SetLineColor(2);
    h_K_WW_cut->Draw("histosame");
    TH1F *h_K_ZZ_cut = (TH1F*)fcutZZ->Get("h_K_bb");
    h_K_ZZ_cut->Scale(luminosity/luminosityZZ);
    h_K_ZZ_cut->SetLineColor(2);
    h_K_ZZ_cut->SetLineStyle(10);
    h_K_ZZ_cut->Draw("histosame");
    */

    TH1F *signal_K_cut = (TH1F*)h_K_bb_cut->Clone("signal_K_cut");
    signal_K_cut->Add(h_K_cc_cut);
    signal_K_cut->Add(h_K_qq_cut);
    signal_K_cut->Draw("histosame");
     Labels(int(cut),pol,kvalue);
  
    TLegend *Kleg1 = new TLegend(0.5,0.3,0.3,0.4);//(0.4,0.3,0.5,0.6);
    Kleg1->SetTextSize(0.035);
    Kleg1->AddEntry(signal_K_cut,"#font[42]{Signal (q=udscb)}","l");
    //Kleg1->AddEntry(h_K_bb_cut,"#font[42]{b#bar{b}}","l");
    //Kleg1->AddEntry(h_K_cc_cut,"#font[42]{c#bar{c}}","l");
    //Kleg1->AddEntry(h_K_qq_cut,"#font[42]{q#bar{q} (q=uds)}","l");
    Kleg1->SetFillStyle(0);
    Kleg1->SetLineWidth(0);
    Kleg1->SetLineColor(0);
    Kleg1->SetBorderSize(0);
    Kleg1->Draw();

    TLegend *Kleg2 = new TLegend(0.5,0.4,0.75,0.5);//(0.4,0.3,0.5,0.6);
    Kleg2->SetTextSize(0.035);
    Kleg2->AddEntry(h_K_radreturn_cut,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
    /* Kleg2->AddEntry(h_y23_hz,"#font[42]{HZ}","l");*/
    //Kleg2->AddEntry(h_K_ZZ_cut,"#font[42]{ZZ}","l");
    //Kleg2->AddEntry(h_K_WW_cut,"#font[42]{WW}","l");
    Kleg2->SetFillStyle(0);
    Kleg2->SetLineWidth(0);
    Kleg2->SetLineColor(0);
    Kleg2->SetBorderSize(0);
    Kleg2->Draw();


    // mjj

    gStyle->SetLabelSize(.03, "XY");
    TCanvas *canvasmjj = new TCanvas("canvasmjj","canvasmjj",800,800);
    canvasmjj->cd(1);
    
    TH1F *h_mjj_qq_cut = (TH1F*)fcut->Get("h_mjj_qq");
    h_mjj_qq_cut->SetLineColor(4);
    //h_mjj_qq_cut->Draw("histo");
    h_mjj_qq_cut->GetYaxis()->SetTitle("Entries/ 5 GeV");
    h_mjj_qq_cut->GetYaxis()->SetTitleSize(.03);
    h_mjj_qq_cut->GetYaxis()->SetTitleOffset(2.23);
    h_mjj_qq_cut->GetXaxis()->SetTitle("m_{2jets} (GeV)"); 
    h_mjj_qq_cut->GetXaxis()->SetTitleSize(.03);  
    h_mjj_qq_cut->GetXaxis()->SetTitleOffset(1.53); 
    TH1F *h_mjj_bb_cut = (TH1F*)fcut->Get("h_mjj_bb");
    //h_mjj_bb_cut->SetLineColor(4);
    //h_mjj_bb_cut->Draw("histosame");
    TH1F *h_mjj_cc_cut = (TH1F*)fcut->Get("h_mjj_cc");
    //h_mjj_cc_cut->SetLineStyle(2);
    //h_mjj_cc_cut->Draw("histosame");
    
    
    TH1F *signal_mjj_cut = (TH1F*)h_mjj_qq_cut->Clone("signal_mjj_cut");
    signal_mjj_cut->Add(h_mjj_bb_cut);
    signal_mjj_cut->Add(h_mjj_cc_cut);
    signal_mjj_cut->Draw("histo");
    
    TH1F *h_mjj_radreturn_cut = (TH1F*)fcut->Get("h_mjj_radreturn");
    h_mjj_radreturn_cut->SetLineColor(2);
    h_mjj_radreturn_cut->Draw("histosame");
     Labels(int(cut),pol,kvalue);
  
    TLegend *mjjleg1 = new TLegend(0.5,0.3,0.3,0.4);//(0.4,0.3,0.5,0.6);
    mjjleg1->SetTextSize(0.035);
    mjjleg1->AddEntry(signal_mjj_cut,"Signal (q=udscb)","l");
    //mjjleg1->AddEntry(h_mjj_bb_cut,"#font[42]{b#bar{b}}","l");
    //mjjleg1->AddEntry(h_mjj_cc_cut,"#font[42]{c#bar{c}}","l");
    // mjjleg1->AddEntry(h_mjj_qq_cut,"#font[42]{q#bar{q} (q=uds)}","l");
    mjjleg1->SetFillStyle(0);
    mjjleg1->SetLineWidth(0);
    mjjleg1->SetLineColor(0);
    mjjleg1->SetBorderSize(0);
    mjjleg1->Draw();

    TLegend *mjjleg2 = new TLegend(0.5,0.25,0.75,0.5);//(0.4,0.3,0.5,0.6);
    mjjleg2->SetTextSize(0.035);
    mjjleg2->AddEntry(h_mjj_radreturn_cut,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
    /* mjjleg2->AddEntry(h_y23_hz,"#font[42]{HZ}","l");
       mjjleg2->AddEntry(h_y23_zz,"#font[42]{ZZ}","l");
       mjjleg2->AddEntry(h_y23_ww,"#font[42]{WW}","l");*/
    mjjleg2->SetFillStyle(0);
    mjjleg2->SetLineWidth(0);
    mjjleg2->SetLineColor(0);
    mjjleg2->SetBorderSize(0);
    mjjleg2->Draw();


    // Charged npfos

    TH2F *h_charge_npfos_bb = (TH2F*)fcut->Get("h_charge_npfos_bb");
    TH2F *h_charge_npfos_cc = (TH2F*)fcut->Get("h_charge_npfos_cc");
    TH2F *h_charge_npfos_qq = (TH2F*)fcut->Get("h_charge_npfos_qq");
    TH2F *h_charge_npfos_radreturn = (TH2F*)fcut->Get("h_charge_npfos_radreturn");
    
    TCanvas *canvascnpfosN = new TCanvas("canvascnpfosN","canvascnpfosN",1200,1200);
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    //gStyle->SetPalette(1,0);
    
  
    canvascnpfosN->Divide(2,2);

    canvascnpfosN->cd(1);
    h_charge_npfos_bb->GetYaxis()->SetRangeUser(0,35);
    h_charge_npfos_bb->GetXaxis()->SetRangeUser(0,35);
    //h_charge_npfos_bb->SetTitle("bb");
    h_charge_npfos_bb->Draw("COLZ");
    h_charge_npfos_bb->GetYaxis()->SetTitle("Jet_{1} charged pfos");
    h_charge_npfos_bb->GetXaxis()->SetTitle("Jet_{2} charged pfos");
    
    canvascnpfosN->cd(2);
    h_charge_npfos_cc->GetYaxis()->SetRangeUser(0,35);
    h_charge_npfos_cc->GetXaxis()->SetRangeUser(0,35);
    //h_charge_npfos_cc->SetTitle("cc");
    h_charge_npfos_cc->Draw("COLZ");
    h_charge_npfos_cc->GetYaxis()->SetTitle("Jet_{1} charged pfos");
    h_charge_npfos_cc->GetXaxis()->SetTitle("Jet_{2} charged pfos");
    
    canvascnpfosN->cd(3);
    h_charge_npfos_qq->GetYaxis()->SetRangeUser(0,35);
    h_charge_npfos_qq->GetXaxis()->SetRangeUser(0,35);
    //h_charge_npfos_qq->SetTitle("qq");
    h_charge_npfos_qq->Draw("COLZ");
    h_charge_npfos_qq->GetYaxis()->SetTitle("Jet_{1} charged pfos");
    h_charge_npfos_qq->GetXaxis()->SetTitle("Jet_{2} charged pfos");
    
    canvascnpfosN->cd(4);
    h_charge_npfos_radreturn->GetYaxis()->SetRangeUser(0,35);
    h_charge_npfos_radreturn->GetXaxis()->SetRangeUser(0,35);
    //h_charge_npfos_radreturn->SetTitle("rr");
    h_charge_npfos_radreturn->Draw("COLZ"); 
    h_charge_npfos_radreturn->GetYaxis()->SetTitle("Jet_{1} charged pfos");
    h_charge_npfos_radreturn->GetXaxis()->SetTitle("Jet_{2} charged pfos");

     

    // N pfos

    TH2F *h_npfos_bb = (TH2F*)fcut->Get("h_npfos_bb");
    TH2F *h_npfos_cc = (TH2F*)fcut->Get("h_npfos_cc");
    TH2F *h_npfos_qq = (TH2F*)fcut->Get("h_npfos_qq");
    TH2F *h_npfos_radreturn = (TH2F*)fcut->Get("h_npfos_radreturn");
    
    TCanvas *canvasnpfos = new TCanvas("canvasnpfos","canvasnpfos",1200,1000);
    gStyle->SetOptFit(0);
    gStyle->SetOptStat(0);
    //gStyle->SetPalette(1,0);
    canvasnpfos->Divide(2,2);

    canvasnpfos->cd(1);
    h_npfos_bb->GetYaxis()->SetRangeUser(0,50);
    h_npfos_bb->GetXaxis()->SetRangeUser(0,50);
    //h_npfos_bb->SetTitle("bb");
    h_npfos_bb->Draw("COLZ");
    h_npfos_bb->GetYaxis()->SetTitle("Jet_{1} pfos");
    h_npfos_bb->GetXaxis()->SetTitle("Jet_{2} pfos");
    
    canvasnpfos->cd(2);
    h_npfos_cc->GetYaxis()->SetRangeUser(0,50);
    h_npfos_cc->GetXaxis()->SetRangeUser(0,50);
    //h_npfos_cc->SetTitle("cc");
    h_npfos_cc->Draw("COLZ");
    h_npfos_cc->GetYaxis()->SetTitle("Jet_{1} pfos");
    h_npfos_cc->GetXaxis()->SetTitle("Jet_{2} pfos");
    
    canvasnpfos->cd(3);
    h_npfos_qq->GetYaxis()->SetRangeUser(0,50);
    h_npfos_qq->GetXaxis()->SetRangeUser(0,50);
    //h_npfos_qq->SetTitle("qq");
    h_npfos_qq->Draw("COLZ");
    h_npfos_qq->GetYaxis()->SetTitle("Jet_{1} pfos");
    h_npfos_qq->GetXaxis()->SetTitle("Jet_{2} pfos");
    
    canvasnpfos->cd(4);
    h_npfos_radreturn->GetYaxis()->SetRangeUser(0,50);
    h_npfos_radreturn->GetXaxis()->SetRangeUser(0,50);
    //h_npfos_radreturn->SetTitle("rr");
    h_npfos_radreturn->Draw("COLZ"); 
    h_npfos_radreturn->GetYaxis()->SetTitle("Jet_{1} pfos");
    h_npfos_radreturn->GetXaxis()->SetTitle("Jet_{2} pfos");


    // y23

    gStyle->SetLabelSize(.03, "XY");
    TCanvas *canvasy23 = new TCanvas("canvasy23","canvasy23",800,800);
    // canvasy23->cd(1);
    canvasy23->SetLogy();
    TH1F *h_y23_qq_cut = (TH1F*)fcut->Get("h_y23_qq");
    //h_y23_qq_cut->SetLineColor(1);
    //h_y23_qq_cut->Scale(1/h_y23_qq_cut->Integral());
    //h_y23_qq_cut->Draw("histo");
    h_y23_qq_cut->GetYaxis()->SetTitle("Entries");
    h_y23_qq_cut->GetXaxis()->SetTitle("y_{23}");
    TH1F *h_y23_bb_cut = (TH1F*)fcut->Get("h_y23_bb");
    //h_y23_bb_cut->SetLineColor(4);
    //h_y23_bb_cut->Scale(1/h_y23_bb_cut->Integral());
    //h_y23_bb_cut->Draw("histosame");
    TH1F *h_y23_cc_cut = (TH1F*)fcut->Get("h_y23_cc");
    //h_y23_cc_cut->SetLineStyle(2);
    //h_y23_cc_cut->Scale(1/h_y23_cc_cut->Integral());
    //h_y23_cc_cut->Draw("histosame");

    TH1F *signal_y23_cut = (TH1F*)h_y23_qq_cut->Clone("signal_y23_cut");
    signal_y23_cut->Add(h_y23_bb_cut);
    signal_y23_cut->Add(h_y23_cc_cut);
    signal_y23_cut->SetLineColor(4);
    //signal_y23_cut->Scale(1/signal_y23_cut->Integral());
    signal_y23_cut->GetXaxis()->SetRangeUser(0.0, 0.05);
    signal_y23_cut->Draw("histo");
    
    TH1F *h_y23_radreturn_cut = (TH1F*)fcut->Get("h_y23_radreturn");
    h_y23_radreturn_cut->SetLineColor(2);
    //h_y23_radreturn_cut->Scale(1/h_y23_radreturn_cut->Integral());
    h_y23_radreturn_cut->Draw("histosame");
    /*
    TH1F *h_y23_WW_cut = (TH1F*)fcutWW->Get("h_y23_bb");
    h_y23_WW_cut->Scale(luminosity/luminosityWW);
    h_y23_WW_cut->SetLineStyle(7);
    h_y23_WW_cut->SetLineColor(94);
    h_y23_WW_cut->Draw("histosame");
    
    TH1F *h_y23_ZZ_cut = (TH1F*)fcutZZ->Get("h_y23_bb");
    h_y23_ZZ_cut->Scale(luminosity/luminosityZZ);
    h_y23_ZZ_cut->SetLineStyle(2);
    h_y23_ZZ_cut->SetLineColor(51);
    h_y23_ZZ_cut->Draw("histosame");
    */ 

    Labels(int(cut),pol,kvalue);
  
    TLegend *y23leg1 = new TLegend(0.5,0.3,0.3,0.4);//(0.4,0.3,0.5,0.6);
    y23leg1->SetTextSize(0.035);
    y23leg1->AddEntry(signal_y23_cut,"Signal (q=udscb) ","l");
    /*
    y23leg1->AddEntry(h_y23_bb_cut,"#font[42]{b#bar{b}}","l");
    y23leg1->AddEntry(h_y23_cc_cut,"#font[42]{c#bar{c}}","l");
    y23leg1->AddEntry(h_y23_qq_cut,"#font[42]{q#bar{q} (q=uds)}","l");
    */
    y23leg1->SetFillStyle(0);
    y23leg1->SetLineWidth(0);
    y23leg1->SetLineColor(0);
    y23leg1->SetBorderSize(0);
    y23leg1->Draw();

    TLegend *y23leg2 = new TLegend(0.5,0.4,0.75,0.5);//(0.4,0.3,0.5,0.6);
    y23leg2->SetTextSize(0.035);
    y23leg2->AddEntry(h_y23_radreturn_cut,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
    /* y23leg2->AddEntry(h_y23_hz,"#font[42]{HZ}","l");*/
    /*   y23leg2->AddEntry(h_y23_ZZ_cut,"#font[42]{ZZ}","l");
	 y23leg2->AddEntry(h_y23_WW_cut,"#font[42]{WW}","l");*/
    y23leg2->SetFillStyle(0);
    y23leg2->SetLineWidth(0);
    y23leg2->SetLineColor(0);
    y23leg2->SetBorderSize(0);
    y23leg2->Draw();

    
    // d23

    TCanvas *canvasd23 = new TCanvas("canvasd23","canvasd23",800,800);
    // canvasd23->cd(1);
    // canvasd23->SetLogy();
    TH1F *h_d23_qq_cut = (TH1F*)fcut->Get("h_d23_qq");
    //h_d23_qq_cut->SetLineColor(1);
    //h_d23_qq_cut->Scale(1/h_d23_qq_cut->Integral());
    //h_d23_qq_cut->Draw("histo");
    h_d23_qq_cut->GetYaxis()->SetTitle("Entries");
    h_d23_qq_cut->GetXaxis()->SetTitle("d_{23}");
    TH1F *h_d23_bb_cut = (TH1F*)fcut->Get("h_d23_bb");
    //h_d23_bb_cut->SetLineColor(4);
    //h_d23_bb_cut->Scale(1/h_d23_bb_cut->Integral());
    //h_d23_bb_cut->Draw("histosame");
    TH1F *h_d23_cc_cut = (TH1F*)fcut->Get("h_d23_cc");
    //h_d23_cc_cut->SetLineStyle(2);
    //h_d23_cc_cut->Scale(1/h_d23_cc_cut->Integral());
    //h_d23_cc_cut->Draw("histosame");

    TH1F *signal_d23_cut = (TH1F*)h_d23_qq_cut->Clone("signal_d23_cut");
    signal_d23_cut->Add(h_d23_bb_cut);
    signal_d23_cut->Add(h_d23_cc_cut);
    signal_d23_cut->SetLineColor(4);
    //signal_d23_cut->Scale(1/signal_d23_cut->Integral());
    signal_d23_cut->GetYaxis()->SetRangeUser(0.0, 900);
    signal_d23_cut->GetXaxis()->SetRangeUser(0.0, 10000);
    signal_d23_cut->Draw("histo");
    
    TH1F *h_d23_radreturn_cut = (TH1F*)fcut->Get("h_d23_radreturn");
    h_d23_radreturn_cut->SetLineColor(2);
    //h_d23_radreturn_cut->Scale(1/h_d23_radreturn_cut->Integral());
    h_d23_radreturn_cut->Draw("histosame");
    /*
    TH1F *h_d23_WW_cut = (TH1F*)fcutWW->Get("h_d23_bb");
    h_d23_WW_cut->Scale(luminosity/luminosityWW);
    h_d23_WW_cut->SetLineStyle(7);
    h_d23_WW_cut->SetLineColor(94);
    h_d23_WW_cut->Draw("histosame");
    
    TH1F *h_d23_ZZ_cut = (TH1F*)fcutZZ->Get("h_d23_bb");
    h_d23_ZZ_cut->Scale(luminosity/luminosityZZ);
    h_d23_ZZ_cut->SetLineStyle(2);
    h_d23_ZZ_cut->SetLineColor(51);
    h_d23_ZZ_cut->Draw("histosame");
    */ 
    Labels(int(cut),pol,kvalue);
  
    TLegend *d23leg1 = new TLegend(0.5,0.3,0.3,0.4);//(0.4,0.3,0.5,0.6);
    d23leg1->SetTextSize(0.035);
    d23leg1->AddEntry(signal_d23_cut,"Signal (q=udscb) ","l");
    /*
    d23leg1->AddEntry(h_d23_bb_cut,"#font[42]{b#bar{b}}","l");
    d23leg1->AddEntry(h_d23_cc_cut,"#font[42]{c#bar{c}}","l");
    d23leg1->AddEntry(h_d23_qq_cut,"#font[42]{q#bar{q} (q=uds)}","l");
    */
    d23leg1->SetFillStyle(0);
    d23leg1->SetLineWidth(0);
    d23leg1->SetLineColor(0);
    d23leg1->SetBorderSize(0);
    d23leg1->Draw();

    TLegend *d23leg2 = new TLegend(0.5,0.4,0.75,0.5);//(0.4,0.3,0.5,0.6);
    d23leg2->SetTextSize(0.035);
    d23leg2->AddEntry(h_d23_radreturn_cut,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
    /* d23leg2->AddEntry(h_d23_hz,"#font[42]{HZ}","l");*/
    /*   d23leg2->AddEntry(h_d23_ZZ_cut,"#font[42]{ZZ}","l");
	 d23leg2->AddEntry(h_d23_WW_cut,"#font[42]{WW}","l");*/
    d23leg2->SetFillStyle(0);
    d23leg2->SetLineWidth(0);
    d23leg2->SetLineColor(0);
    d23leg2->SetBorderSize(0);
    d23leg2->Draw();

    // mj1_mj2

    TCanvas *canvasmj1_mj2 = new TCanvas("canvasmj1_mj2","canvasmj1_mj2",800,800);
    // canvasmj1_mj2->cd(1);
    //canvasmj1_mj2->SetLogy();
    TH1F *h_mj1_mj2_qq_cut = (TH1F*)fcut->Get("h_mj1_mj2_qq");
    //h_mj1_mj2_qq_cut->SetLineColor(1);
    //h_mj1_mj2_qq_cut->Scale(1/h_mj1_mj2_qq_cut->Integral());
    //h_mj1_mj2_qq_cut->Draw("histo");
    h_mj1_mj2_qq_cut->GetYaxis()->SetTitle("Entries");
    h_mj1_mj2_qq_cut->GetXaxis()->SetTitle("m_{j_{1}}+m_{j_{2}} (GeV)");
    TH1F *h_mj1_mj2_bb_cut = (TH1F*)fcut->Get("h_mj1_mj2_bb");
    //h_mj1_mj2_bb_cut->SetLineColor(4);
    //h_mj1_mj2_bb_cut->Scale(1/h_mj1_mj2_bb_cut->Integral());
    //h_mj1_mj2_bb_cut->Draw("histosame");
    TH1F *h_mj1_mj2_cc_cut = (TH1F*)fcut->Get("h_mj1_mj2_cc");
    //h_mj1_mj2_cc_cut->SetLineStyle(2);
    //h_mj1_mj2_cc_cut->Scale(1/h_mj1_mj2_cc_cut->Integral());
    //h_mj1_mj2_cc_cut->Draw("histosame");

    TH1F *signal_mj1_mj2_cut = (TH1F*)h_mj1_mj2_qq_cut->Clone("signal_mj1_mj2_cut");
    signal_mj1_mj2_cut->Add(h_mj1_mj2_bb_cut);
    signal_mj1_mj2_cut->Add(h_mj1_mj2_cc_cut);
    signal_mj1_mj2_cut->SetLineColor(4);
    //signal_mj1_mj2_cut->Scale(1/signal_mj1_mj2_cut->Integral());
    signal_mj1_mj2_cut->GetXaxis()->SetRangeUser(0.0, 250);
    signal_mj1_mj2_cut->Draw("histo");
    
    TH1F *h_mj1_mj2_radreturn_cut = (TH1F*)fcut->Get("h_mj1_mj2_radreturn");
    h_mj1_mj2_radreturn_cut->SetLineColor(2);
    //h_mj1_mj2_radreturn_cut->Scale(1/h_mj1_mj2_radreturn_cut->Integral());
    h_mj1_mj2_radreturn_cut->Draw("histosame");
    /*
    TH1F *h_mj1_mj2_WW_cut = (TH1F*)fcutWW->Get("h_mj1_mj2_bb");
    h_mj1_mj2_WW_cut->Scale(luminosity/luminosityWW);
    h_mj1_mj2_WW_cut->SetLineStyle(7);
    h_mj1_mj2_WW_cut->SetLineColor(94);
    h_mj1_mj2_WW_cut->Draw("histosame");
    
    TH1F *h_mj1_mj2_ZZ_cut = (TH1F*)fcutZZ->Get("h_mj1_mj2_bb");
    h_mj1_mj2_ZZ_cut->Scale(luminosity/luminosityZZ);
    h_mj1_mj2_ZZ_cut->SetLineStyle(2);
    h_mj1_mj2_ZZ_cut->SetLineColor(51);
    h_mj1_mj2_ZZ_cut->Draw("histosame");
    */
    Labels(int(cut),pol,kvalue);
  
    TLegend *mj1_mj2leg1 = new TLegend(0.5,0.3,0.3,0.4);//(0.4,0.3,0.5,0.6);
    mj1_mj2leg1->SetTextSize(0.035);
    mj1_mj2leg1->AddEntry(signal_mj1_mj2_cut,"Signal (q=udscb) ","l");
    /*
    mj1_mj2leg1->AddEntry(h_mj1_mj2_bb_cut,"#font[42]{b#bar{b}}","l");
    mj1_mj2leg1->AddEntry(h_mj1_mj2_cc_cut,"#font[42]{c#bar{c}}","l");
    mj1_mj2leg1->AddEntry(h_mj1_mj2_qq_cut,"#font[42]{q#bar{q} (q=uds)}","l");
    */
    mj1_mj2leg1->SetFillStyle(0);
    mj1_mj2leg1->SetLineWidth(0);
    mj1_mj2leg1->SetLineColor(0);
    mj1_mj2leg1->SetBorderSize(0);
    mj1_mj2leg1->Draw();

    TLegend *mj1_mj2leg2 = new TLegend(0.5,0.4,0.75,0.5);//(0.4,0.3,0.5,0.6);
    mj1_mj2leg2->SetTextSize(0.035);
    mj1_mj2leg2->AddEntry(h_mj1_mj2_radreturn_cut,"#font[42]{#gammaZ#rightarrow #gammaq#bar{q} (q=udscb)}","l");
    /* mj1_mj2leg2->AddEntry(h_mj1_mj2_hz,"#font[42]{HZ}","l");*/
    /*   mj1_mj2leg2->AddEntry(h_mj1_mj2_ZZ_cut,"#font[42]{ZZ}","l");
	 mj1_mj2leg2->AddEntry(h_mj1_mj2_WW_cut,"#font[42]{WW}","l");*/
    mj1_mj2leg2->SetFillStyle(0);
    mj1_mj2leg2->SetLineWidth(0);
    mj1_mj2leg2->SetLineColor(0);
    mj1_mj2leg2->SetBorderSize(0);
    mj1_mj2leg2->Draw();



    // Finding the cos90 or cos85:
    // double  qq_maxef_aux1=h_costheta_qq_cut->Integral(1,1);
    // double  qq_maxef_aux2=h_costheta_qq->Integral(1,1);
    // double  qq_maxef=qq_maxef_aux1/qq_maxef_aux2;
    // //cout << qq_maxef << endl;
    
    // for(int i=2;i<NBIN+1;i++) {
    // double  bin=i;
    // double  cosvalue=(1/NBIN)*(bin-1);
    // double  aux1=h_costheta_qq_cut->Integral(i,i);
    // double  aux2=h_costheta_qq->Integral(i,i);
    // double  qq_actualef=aux1/aux2;
    // double  efratio=qq_actualef/qq_maxef;
    
    // //cout << efratio<<" "<<qq_actualef <<" "<< cosvalue << endl;

    // if(efratio < 0.85){
    // cout << "cos85" <<" "<< cosvalue << endl;
    // //return;
    // 	}
    // else
      
    // if(efratio < 0.90){
    // 	cout << "cos90"<<" "<< cosvalue << endl;
    //        }
    // }
    
    // Calculating the S/B
    double signal = h_costheta_bb_cut_total+h_costheta_cc_cut_total+h_costheta_qq_cut_total;
    double background = h_costheta_radreturn_cut_total;
    // double SoB = signal/background;

    // cout << "S/B: " << SoB << endl;


    // Calculating the S/B Limited
    double signalL = h_costheta_bb_cut_total_L+h_costheta_cc_cut_total_L+h_costheta_qq_cut_total_L;
    double backgroundL = h_costheta_radreturn_cut_total_L;
    // double SoBL = signalL/backgroundL;

    // cout << "S/B Limited: " << SoBL << endl;
    
    //cout<< "Lumi qq & ISR" <<" - "<< "Lumi WW" <<" - "<< "Lumi ZZ"<<" - "<< "Lumi tt"  <<endl;
    //cout<< luminosity<<" - "<<luminosityWW<<" - "<<luminosityZZ<<" - "<<luminosityTT <<endl;
    
    // Calculating the B/S:
    /*
    double backgroundWW = h_costheta_WW_cut_total;
    double backgroundZZ = h_costheta_ZZ_cut_total;
    double backgroundTT = h_costheta_TT_cut_total;
    double BoS = background/signal;
    double WWoS = backgroundWW/signal;
    double ZZoS = backgroundZZ/signal;
    double TToS = backgroundTT/signal;
    
    cout << "B/S" << endl;
    cout << "radreturn "<< "WW " << "ZZ " << "tt " << endl;
    cout << BoS << " " << WWoS << " " << ZZoS << " " << TToS << "|"<< endl;

    // Calculating the B/S Limited:
    
    double backgroundWWL = h_costheta_WW_cut_total_L;
    double backgroundZZL = h_costheta_ZZ_cut_total_L; 
    double backgroundTTL = h_costheta_TT_cut_total_L;   
    double BoSL = backgroundL/signalL;
    double WWoSL = backgroundWWL/signalL;
    double ZZoSL = backgroundZZL/signalL;
    double TToSL = backgroundTTL/signalL;
    
    cout << BoSL << " " << WWoSL << " " << ZZoSL << " " << TToSL << "||"<< endl;
    */
    // Calculating b/c and c/b:

    double BoverC=h_costheta_bb_cut_total/h_costheta_cc_cut_total;
    double CoverB=h_costheta_cc_cut_total/h_costheta_bb_cut_total;

    cout<<"b/c: "<<BoverC<<endl;
    cout<<"c/b: "<<CoverB<<endl;


    
    // // Slope:
    // TF1 *fb = new TF1("fb","[0] +[1]*x",0,0.9);
    // TCanvas *canvascostheta_slope = new TCanvas("slope","slope",800,800);

    // // SetQQbarStyle();
    // // gStyle->SetOptFit(0); 
    // // gStyle->SetOptStat(0);
    // // gStyle->SetOptTitle(0);
  
    // // gStyle->SetTitleBorderSize(0);
    // // gStyle->SetTitleStyle(0);
    // // gStyle->SetTitleX(0.2);
    // // gStyle->SetMarkerSize(1.5);
    
    // // canvascostheta_slope->cd(1);
    // // h_costheta_bb_slope->Draw();
    // cout << "****************************************" <<endl; 
    // cout << "regression for bb" <<endl; 
    // h_costheta_bb_ratio->Fit("fb","EMR");

   
    // Slope radreturn:
    // TF1 *fr = new TF1("fr","[0] +[1]*x",0,0.9);
      
    // TCanvas *canvascostheta_sloperr = new TCanvas("slope-rr","slope-rr",800,800);    
    // // canvascostheta_slope->cd(1);
    // // h_costheta_bb_slope->Draw();  
    // cout << "****************************************" <<endl; 
    // cout << "regression for rr" <<endl; 
    // h_costheta_radreturn_ratio->Fit("fr","EMR"); 
    // cout << "****************************************" <<endl;  

    // Parte de los bins finales:
    // Integral de referencia:
    
    // double  qq_refef_cut=h_costheta_qq_cut->Integral(1,30);
    // double  qq_refef_0=h_costheta_qq->Integral(1,30);
    // double  qq_refef=qq_refef_cut/qq_refef_0;
     
    // for(int i=0;i<NBIN/2;i++) {
    // double  target=0.90;
    // double  neglected=10;
    // double  bin=i;  
    // double  qq_partial_cut=h_costheta_qq_cut->Integral(NBIN-neglected-i,NBIN-neglected);
    // double  qq_partial_0=h_costheta_qq->Integral(NBIN-neglected-i,NBIN-neglected);
    // double  qq_partial=qq_partial_cut/qq_partial_0;

    // double efratio=qq_partial/qq_refef;
    // if(efratio > target){
    //   cout << "nª of bins when ef. ~" << target << " of medium ef. (ommiting last " << neglected << " bins): " << bin << endl;
    // cout << "****************************************" <<endl;   
    // cout << "****************************************" <<endl; 
    // return;
    // 	}
    // }

}
