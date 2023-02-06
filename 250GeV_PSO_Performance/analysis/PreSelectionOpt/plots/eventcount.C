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

void eventcount(int cut,TString pol, TString kvalue, TString quality) {

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
  TString filename[5];
  TString category[5]={"all","catA","catB","catC","catD"};
  TFile *f[5];
  TH1F*  btag[5][40]; //all, catA, catB, catC, catD
  TH1F*  ctag[5][40];

  for(int icat=0; icat<5; icat++) {
    filename[icat] = "../results/jettag_"+cutname+"_2f_hadronic_sample_"+category[icat]+"_BDT_"+quality+"_"+pol+"_Kgamma"+kvalue+"_250GeV.root";
    f[icat] = new TFile(filename[icat]);
    for(int i=0; i<1; i++) {
      btag[icat][i]= (TH1F*)f[icat]->Get(TString::Format("h_jet_btag_%i",i));
      ctag[icat][i]= (TH1F*)f[icat]->Get(TString::Format("h_jet_ctag_%i",i));
    }
  }

  float events_all[3], events_cat[5][3], percentage[5][3];
  for(int icat=0; icat<5; icat++) {
    for(int iflav=0;iflav<3; iflav++){
      int quark=0;
      if(iflav==1) quark=4;
      if(iflav==2) quark=5;
      
      events_all[iflav]=btag[0][0]->GetBinContent(quark+1);
      events_cat[icat][iflav]=btag[icat][0]->GetBinContent(quark+1);
      
      percentage[icat][iflav]=100*(events_cat[icat][iflav]/events_all[iflav]);
    }
  }

  cout<<"events | b jets | c jets | uds jets"<<endl;
  cout<<"all | "<<events_all[2]<<" | "<<events_all[1]<<" | "<<events_all[0]<<endl;
  cout<<"cat. A | "<<events_cat[1][2]<<" | "<<events_cat[1][1]<<" | "<<events_cat[1][0]<<endl;
  cout<<"cat. B | "<<events_cat[2][2]<<" | "<<events_cat[2][1]<<" | "<<events_cat[2][0]<<endl;
  cout<<"cat. C | "<<events_cat[3][2]<<" | "<<events_cat[3][1]<<" | "<<events_cat[3][0]<<endl;
  cout<<"cat. D | "<<events_cat[4][2]<<" | "<<events_cat[4][1]<<" | "<<events_cat[4][0]<<endl;
  /*
  cout<<"\begin{table}[]"<<endl;
  cout<<"\begin{tabular}{|cccc|}"<<endl;
  cout<<"\hline"<<endl;
  cout<<"\multicolumn{4}{|c|}{Events}     \\ \hline"<<endl;
  cout<<"\multicolumn{1}{|c|}{Cat.} & \multicolumn{1}{c|}{b jets} & \multicolumn{1}{c|}{c jets} & uds jets \\ \hline"<<endl;
  cout<<"\multicolumn{1}{|c|}{all}  & \multicolumn{1}{c|}{"<<events_cat[0][2]<<"} & \multicolumn{1}{c|}{"<<events_cat[0][1]<<"}  & "<<events_cat[0][0]<<" \\ \hline"<<endl;
  cout<<"\multicolumn{1}{|c|}{A}  & \multicolumn{1}{c|}{"<<events_cat[1][2]<<"} & \multicolumn{1}{c|}{"<<events_cat[1][1]<<"}  & "<<events_cat[1][0]<<" \\ \hline"<<endl;
  cout<<"\multicolumn{1}{|c|}{B}  & \multicolumn{1}{c|}{"<<events_cat[2][2]<<"} & \multicolumn{1}{c|}{"<<events_cat[2][1]<<"}  & "<<events_cat[2][0]<<" \\ \hline"<<endl;
  cout<<"\multicolumn{1}{|c|}{C}  & \multicolumn{1}{c|}{"<<events_cat[3][2]<<"} & \multicolumn{1}{c|}{"<<events_cat[3][1]<<"}  & "<<events_cat[3][0]<<" \\ \hline"<<endl;
  cout<<"\multicolumn{1}{|c|}{D}  & \multicolumn{1}{c|}{"<<events_cat[4][2]<<"} & \multicolumn{1}{c|}{"<<events_cat[4][1]<<"}  & "<<events_cat[4][0]<<" \\ \hline"<<endl;
  cout<<"\end{tabular}"<<endl;
  cout<<"\end{table}"<<endl;
  */


  //Percentage
  cout<<"(%) | b jets | c jets | uds jets"<<endl;
  cout<<"cat. A | "<<percentage[1][2]<<" | "<<percentage[1][1]<<" | "<<percentage[1][0]<<endl;
  cout<<"cat. B | "<<percentage[2][2]<<" | "<<percentage[2][1]<<" | "<<percentage[2][0]<<endl;
  cout<<"cat. C | "<<percentage[3][2]<<" | "<<percentage[3][1]<<" | "<<percentage[3][0]<<endl;
  cout<<"cat. D | "<<percentage[4][2]<<" | "<<percentage[4][1]<<" | "<<percentage[4][0]<<endl;
}
