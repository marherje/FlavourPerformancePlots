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

void SelectCategory(TString pol, TString quality, TString category){

  TString filename = "DataCat/"+quality+"_"+pol+"_all.root";

  Int_t Load_jet_nvtx;
  Int_t Load_pfo_n;
  Int_t Load_pfo_match[165];
  Int_t Load_pfo_vtx[165];
  Float_t Load_pfo_E[165];
  
  //TBranch* b_Load_jet_nvtx;                                                                                                                                                                                                                                                      
  
  TFile *oldfile = new TFile(filename);
  TTree *oldtree = (TTree*)oldfile->Get("Stats");
  
  //oldtree->SetBranchAddress("jet_nvtx", &Load_jet_nvtx, &b_Load_jet_nvtx);                                                                                                                                                                                                       
  oldtree->SetBranchAddress("jet_nvtx",&Load_jet_nvtx);
  oldtree->SetBranchAddress("pfo_n", &Load_pfo_n);
  oldtree->SetBranchAddress("pfo_match", &Load_pfo_match);
  oldtree->SetBranchAddress("pfo_vtx",&Load_pfo_vtx);                                                                    
  oldtree->SetBranchAddress("pfo_E",&Load_pfo_E);
  
  //TTree *newtree = oldtree->CloneTree();                                                                                                                                                                                                                                         
  //newtree->Reset();                                                                                                                                                                                                                                                              
  
  //TFile *MyFile = new TFile(TString::Format("selection_%s_250GeV.root",process.Data()),"RECREATE");                                                                                                                                                                              
  //MyFile->cd();                                                                                                                                                                                                                                                                  
  
  TFile *MyFile = new TFile("DataCat/"+quality+"_"+pol+"_"+category+".root","recreate");
  //MyFile->cd();                                                                                                                                                                                                                                                                  
  TTree *newtree = oldtree->CloneTree();
  //newtree->Write();
  newtree->Reset();
  //Long64_t nentries;
  //  if(n_entries>0) nentries= n_entries;
  
  //else
  //nentries= fChain->GetEntriesFast();
  Int_t nentries = (Int_t)oldtree->GetEntries();
  
  for (Int_t jentry=0; jentry<nentries;jentry++) {
    //Long64_t ientry = LoadTree(jentry);
    oldtree->GetEntry(jentry);
    Int_t jetvtx=0;
    Int_t pseudovtx=0;
    Int_t totalvtx=0;
    Int_t pfo_vtx_j1_counts[4];
    pfo_vtx_j1_counts[0]=0;
    pfo_vtx_j1_counts[1]=0;
    pfo_vtx_j1_counts[2]=0;
    pfo_vtx_j1_counts[3]=0;
    
    Int_t pfo_vtx_j2_counts[4];
    pfo_vtx_j2_counts[0]=0;
    pfo_vtx_j2_counts[1]=0;
    pfo_vtx_j2_counts[2]=0;
    pfo_vtx_j2_counts[3]=0;
    
    if(jentry % 1000 == 0){
      Float_t current=jentry;
      Float_t total=nentries;
      Float_t percentage=(current/total)*100;
      cout<<"Progress %: "<<percentage<<endl;
    } 

    Int_t jetvtx_j1=0;
    Int_t jetvtx_j2=0;
    for(int ipfo=0; ipfo<Load_pfo_n; ipfo++) {
      if(Load_pfo_match[ipfo]<0) continue;
      if(Load_pfo_E[ipfo]<1) continue;
      if(Load_pfo_match[ipfo]>1) continue;                                                                                                                                                                                                                                                                                   
      if(Load_pfo_match[ipfo]==0) {
        if(Load_pfo_vtx[ipfo]==1) pfo_vtx_j1_counts[1]++;
        else if(Load_pfo_vtx[ipfo]==2) pfo_vtx_j1_counts[2]++;
        else if(Load_pfo_vtx[ipfo]==3) pfo_vtx_j1_counts[3]++;
      }                                                     
      if(Load_pfo_match[ipfo]==1) {
        if(Load_pfo_vtx[ipfo]==1) pfo_vtx_j2_counts[1]++;
        else if(Load_pfo_vtx[ipfo]==2) pfo_vtx_j2_counts[2]++;                                                          
        else if(Load_pfo_vtx[ipfo]==3) pfo_vtx_j2_counts[3]++;
      }                                                                                                                                                                                              
    } //ipfo
    
    for(int iv=1;iv<4;iv++){                                                                                                                                            
      if(pfo_vtx_j1_counts[iv]==1)pseudovtx++;
      if(pfo_vtx_j2_counts[iv]==1)pseudovtx++;
      if(pfo_vtx_j1_counts[iv]>1)jetvtx_j1++;
      if(pfo_vtx_j2_counts[iv]>1)jetvtx_j2++;
    }                                       
    jetvtx=jetvtx_j1+jetvtx_j2;
    totalvtx=jetvtx+pseudovtx;
    cout<<"jetvtx: "<<jetvtx<<", pseudovtx: "<<pseudovtx<<endl;                                                                                                                                                       
    if(category=="catA"){
      if (jetvtx == 0)newtree->Fill();
    } 
    else if(category=="catB"){
      if (jetvtx == 1 && totalvtx == 1)newtree->Fill();
    }
    else if(category=="catC"){
      if (jetvtx == 1 && totalvtx == 2)newtree->Fill();
    }
    else if(category=="catD"){
      if (jetvtx == 2 && totalvtx == 2)newtree->Fill();
    }
    
  } //entries
  Int_t entries_category=newtree->GetEntries();
  cout<<"Entries in this category: "<<entries_category<<endl;
  newtree->AutoSave();
  //newtree->Write();  
  
}
