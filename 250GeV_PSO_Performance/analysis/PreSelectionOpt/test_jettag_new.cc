#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int test_jettag_new(TString pol, int type, float Kv, TString cat, TString quality){
  int bkg=0;
  int selection_type=type;
  TString process="2f_hadronic_sample_"+cat+"_BDT_"+quality+"_";
  TString s_type=TString::Format("cuts%i_",type);
  TString kvalue=TString::Format("_Kgamma%i",int(Kv));
  
    
  TString file = "DataCat/"+quality+"_"+pol+".root";
  
  QQbarAnalysisClass ss3(file);
  ss3.process=s_type+process+pol+kvalue;

  ss3.JetTag(-1,type,Kv,cat);
  gSystem->Exit(0);

  return 0;
}
