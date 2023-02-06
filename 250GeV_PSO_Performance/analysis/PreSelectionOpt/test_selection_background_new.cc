#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int test_selection_background_new(int G, int R, TString pol, int type, float Kvcut, TString process, int bkg=0){
  int selection_type=type;
  TString s_type=TString::Format("cuts%i_",type);
  TString kvalue=TString::Format("_Kgamma%i",int(Kvcut));
  
  TString fileaux1=TString::Format("../../../../Data/ntuples/1/%i", int(G));
  TString fileaux2=TString::Format("/%i/", int(R));
  TString file = fileaux1+fileaux2+process+pol+".root";
  
  QQbarAnalysisClass ss3(file);

  ss3.process=s_type+process+pol+kvalue;

  ss3.Selection(-1,type,Kvcut,bkg);
  gSystem->Exit(0);

  return 0;
}
