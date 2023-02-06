

void CrossSectionScript(int process=0, int pol=1) {


  float cross_section[2][2];
  cross_section[0][0]=127966;//qq eL                                                                                                                                                                      
  cross_section[1][0]=70416.7;//qq eR                                                                                                                                                                     
  cross_section[0][1]=18217.6;//qq eL + rad ret cut (35GeV)  
  cross_section[1][1]=10633.8;//qq eR + rad ret cut (35GeV)                                                                                                                                               

  float luminosity[100]={0};
  //eR_pL                                                                                                                                                                                                 
  TString folder="/lustre/ific.uv.es/prj/ific/flc/ntuples-2020/2f_hadronic_sample_eR_pL/";

  TString file=folder+"15164_eR_pL.root";
  TFile f1(file);
  auto tree = f1.Get<TTree>("Stats");
  Long64_t nentries = tree->GetEntries();
  luminosity[0]=nentries/cross_section[pol][process];
  std::cout<<file<<" Entries: "<<nentries<<" cross: "<<cross_section[pol][process]<<" Lum (fb-1): "<<luminosity[0]<<endl;

  for(int i=0; i<5; i++) {
    file=TString::Format(folder+"15165_%i_eR_pL.root",i);
    TFile f2(file);
    auto tree2 = f2.Get<TTree>("Stats");
    Long64_t nentries2 = tree2->GetEntries();
    luminosity[i+1]=nentries2/cross_section[pol][process];

    std::cout<<file<<" Entries: "<<nentries2<<" cross: "<<cross_section[pol][process]<<" Lum (fb-1): "<<luminosity[i+1]<<endl;
  }

  std::cout<<""<<endl;
  std::cout<<" Radiative_Return_Cut_(E_ISR1+E_ISR2<35)"<<endl;



  file=folder+"15164_eR_pL.root";
  TFile f3(file);
  auto tree3 = f3.Get<TTree>("Stats");
  Long64_t nentries3 = tree3->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<35");
  std::cout<<file<<" Entries: "<<nentries3<<" cross: "<<nentries3/luminosity[0]<<" Lum (fb-1): "<<luminosity[0]<<endl;

  for(int i=0; i<5; i++) {
    file=TString::Format(folder+"15165_%i_eR_pL.root",i);
    TFile f4(file);
    auto tree4 = f4.Get<TTree>("Stats");
    Long64_t nentries4 = tree4->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<35");
    std::cout<<file<<" Entries: "<<nentries4<<" cross: "<<nentries4/luminosity[i+1]<<" Lum (fb-1): "<<luminosity[i+1]<<endl;
  }

  std::cout<<""<<endl;
  std::cout<<" Radiative_Return_Cut_(E_ISR1+E_ISR2<50)"<<endl;

  file=folder+"15164_eR_pL.root";
  TFile f5(file);
  auto tree5 = f5.Get<TTree>("Stats");
  Long64_t nentries5 = tree5->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<50");
  std::cout<<file<<" Entries: "<<nentries5<<" cross: "<<nentries5/luminosity[0]<<" Lum (fb-1): "<<luminosity[0]<<endl;

  for(int i=0; i<5; i++) {
    file=TString::Format(folder+"15165_%i_eR_pL.root",i);
    TFile f4(file);
    auto tree4 = f4.Get<TTree>("Stats");
    Long64_t nentries4 = tree4->GetEntries("(mc_ISR_E[0]+mc_ISR_E[1])<50");
    std::cout<<file<<" Entries: "<<nentries4<<" cross: "<<nentries4/luminosity[i+1]<<" Lum (fb-1): "<<luminosity[i+1]<<endl;
  }


}
