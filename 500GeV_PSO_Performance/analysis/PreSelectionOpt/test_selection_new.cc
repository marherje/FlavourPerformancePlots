#include "TROOT.h"
#include "TFile.h"
#include "QQbarAnalysisClass.C"
#include "TApplication.h"

int test_selection_new(TString pol, int type, float Kv, TString cat, TString quality){
  int bkg=0;
  int selection_type=type;
  TString process="2f_hadronic_sample_"+cat+"_BDT_"+quality+"_";
  TString s_type=TString::Format("cuts%i_",type);
  TString kvalue=TString::Format("_Kgamma%i",int(Kv));


  //TString file = "DataCat/"+quality+"_"+pol+".root";
  TString file = "/lustre/ific.uv.es/prj/ific/flc/ntuples-2022/merged_small_"+pol+"_500GeV_"+quality+".root";

  QQbarAnalysisClass ss3(file);
  ss3.process=s_type+process+pol+kvalue;

  ss3.Selection(-1,type,Kv,bkg,cat);
  gSystem->Exit(0);

  return 0;
}
