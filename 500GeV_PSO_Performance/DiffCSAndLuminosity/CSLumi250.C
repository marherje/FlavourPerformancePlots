
void CSLumi250(TString pol){
  // polarisation selection 
  //TString folder="/Users/marherje/Trabajo/Analisis/QQbarAnalysis/scripts/2021_350GeV_R100/";
  
  TString folder="../../../QQbarAnalysis500/scripts/ReTraining250/";

  float CS;
  TString file;
  if (pol=="eL_pR"){
    CS=127966; // Remember we get this from dumping lcio events Old_350GeV-> CS=32470.5;
  }
  if (pol=="eR_pL"){
    CS=70416.7; // Old_350GeV-> CS=17994.7;
  }
  file=folder+"merged_"+pol+".root"; 


  // eL_pR case:
  TFile f1(file);
  auto tree = f1.Get<TTree>("ntp");
  Long64_t Nraw = tree->GetEntries();
  Long64_t N_signal_allq = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<35");
  //Long64_t N_signal_t = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<35 && fabs(mc_quark_pdg[0])==6 && fabs(mc_quark_pdg[1])==6 ");
  Long64_t N_signal_b = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<35 && fabs(mc_quark_pdg[0])==5 && fabs(mc_quark_pdg[1])==5 ");
  Long64_t N_signal_c = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<35 && fabs(mc_quark_pdg[0])==4 && fabs(mc_quark_pdg[1])==4 ");
  Long64_t N_signal_s = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<35 && fabs(mc_quark_pdg[0])==3 && fabs(mc_quark_pdg[1])==3 ");
  Long64_t N_signal_u = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<35 && fabs(mc_quark_pdg[0])==2 && fabs(mc_quark_pdg[1])==2 ");
  Long64_t N_signal_d = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<35 && fabs(mc_quark_pdg[0])==1 && fabs(mc_quark_pdg[1])==1 ");

  
  Long64_t N_ISR_allq = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])>35");
  //Long64_t N_ISR_t = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])>35 && fabs(mc_quark_pdg[0])==6 && fabs(mc_quark_pdg[1])==6 ");
  Long64_t N_ISR_b = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])>35 && fabs(mc_quark_pdg[0])==5 && fabs(mc_quark_pdg[1])==5 ");
  Long64_t N_ISR_c = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])>35 && fabs(mc_quark_pdg[0])==4 && fabs(mc_quark_pdg[1])==4 ");
  Long64_t N_ISR_s = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])>35 && fabs(mc_quark_pdg[0])==3 && fabs(mc_quark_pdg[1])==3 ");
  Long64_t N_ISR_u = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])>35 && fabs(mc_quark_pdg[0])==2 && fabs(mc_quark_pdg[1])==2 ");
  Long64_t N_ISR_d = tree->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])>35 && fabs(mc_quark_pdg[0])==1 && fabs(mc_quark_pdg[1])==1 ");

  float_t LSample=Nraw/CS;


  //Signal and ISR for all flavours
  float_t CS_signal_allq=N_signal_allq/LSample;  
  float_t CS_ISR_allq=N_ISR_allq/LSample;

  //Signal for each flavour
  //float_t CS_signal_t=N_signal_t/LSample;
  float_t CS_signal_b=N_signal_b/LSample;
  float_t CS_signal_c=N_signal_c/LSample;
  float_t CS_signal_s=N_signal_s/LSample;
  float_t CS_signal_u=N_signal_u/LSample;
  float_t CS_signal_d=N_signal_d/LSample;

  //ISR for each flavour
  //float_t CS_ISR_t=N_ISR_t/LSample;
  float_t CS_ISR_b=N_ISR_b/LSample;
  float_t CS_ISR_c=N_ISR_c/LSample;
  float_t CS_ISR_s=N_ISR_s/LSample;
  float_t CS_ISR_u=N_ISR_u/LSample;
  float_t CS_ISR_d=N_ISR_d/LSample;

  
  cout<<"Results in the "<<pol<<" case:"<<endl;
  cout<<"Luminosity: "<<LSample<<endl;
  cout<<"Total cross-sections (sample): "<<CS<<endl;
  cout<<"All flavours CS: "<<CS_signal_allq<<endl;
  cout<<"Total ISR CS: "<<CS_ISR_allq<<endl;
  cout<<"All flavours events: "<<N_signal_allq <<endl;
  cout<< "ISR events: "<<N_ISR_allq<<endl;
  
  cout<<"Quark CS |   b   |   c   |   s   |   u   |   d   |"<<endl;
  cout<<"         |"<<CS_signal_b<<"|"<<CS_signal_c<<"|"<<CS_signal_s<<"|"<<CS_signal_u<<"|"<<CS_signal_d<<"|"<<endl;
  cout<<"Quark ISR|   b   |   c   |   s   |   u   |   d   |"<<endl;
  cout<<"         |"<<CS_ISR_b<<"|"<<CS_ISR_c<<"|"<<CS_ISR_s<<"|"<<CS_ISR_u<<"|"<<CS_ISR_d<<"|"<<endl;
  cout<<"Events  |   b   |   c   |   s   |   u   |   d   |"<<endl;
  cout<<"        |"<<N_signal_b<<"|"<<N_signal_c<<"|"<<N_signal_s<<"|"<<N_signal_u<<"|"<<N_signal_d<<"|"<<endl;
  
  cout<<"Events ISR  |   b   |   c   |   s   |   u   |   d   |"<<endl;
  cout<<"        |"<<N_ISR_b<<"|"<<N_ISR_c<<"|"<<N_ISR_s<<"|"<<N_ISR_u<<"|"<<N_ISR_d<<"|"<<endl;
  


}
