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

void ttbarluminositycheck() {
  
  double cross_section[2][4]={
    {166.6,164.4,165.5,163.3},
    {65.5,64.4,64.1,60.7}
  };
  double events[2][4]={
    {605254,630682,662820,643092},
    {272570,269688,280522,241118}
  };

  
  double luminosity[2][4];
  luminosity[0][0]=events[0][0]/cross_section[0][0];
  luminosity[0][1]=events[0][1]/cross_section[0][1];
  luminosity[0][2]=events[0][2]/cross_section[0][2];
  luminosity[0][3]=events[0][3]/cross_section[0][3];
  luminosity[1][0]=events[1][0]/cross_section[1][0];
  luminosity[1][1]=events[1][1]/cross_section[1][1];
  luminosity[1][2]=events[1][2]/cross_section[1][2];
  luminosity[1][3]=events[1][3]/cross_section[1][3];
  
  cout<<"eL"<<endl;
  cout<<luminosity[0][0]<<" "<<luminosity[0][1]<<" "<<luminosity[0][2]<<" "<<luminosity[0][3]<<endl;
  
  cout<<"eR"<<endl;
  cout<<luminosity[1][0]<<" "<<luminosity[1][1]<<" "<<luminosity[1][2]<<" "<<luminosity[1][3]<<endl;
  
}
