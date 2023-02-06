
#define QQbarAnalysisClass_cxx
#include "QQbarAnalysisClass.h"
#include "TPad.h"

#include "TLorentzVector.h"


void QQbarAnalysisClass::JetTag(int n_entries=-1, int selection_type=0, float Kvcut=30, TString cat="all")
{
  
  TFile *MyFile = new TFile(TString::Format("jettag_%s_500GeV.root",process.Data()),"RECREATE");
  MyFile->cd();

 
  TH1F * h_jet_btag[40];
  TH1F * h_jet_ctag[40];

  for(int i=0; i<40;i++) {
    h_jet_btag[i]= new TH1F(TString::Format("h_jet_btag_%i",i),TString::Format("h_jet_btag_%i",i),6,-0.5,5.5);
    h_jet_ctag[i]= new TH1F(TString::Format("h_jet_ctag_%i",i),TString::Format("h_jet_ctag_%i",i),6,-0.5,5.5);
  }

 Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();


  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

   
    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;

    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    float Kv=Kreco();
    //parte importante
    bool selection=PreSelection(selection_type,Kvcut);
    if(selection==false) continue;
    if(gamma_e>Kvcut) continue;


    // Category selection
        
    for(int ijet=0; ijet<2; ijet++) {  
      Int_t jetvtx=0;
      Int_t pseudovtx=0;
      Int_t totalvtx=0;
      Int_t pfo_vtx_jet_counts[2];
      pfo_vtx_jet_counts[0]=0;
      pfo_vtx_jet_counts[1]=0;
      for(int ipfo=0; ipfo<pfo_n; ipfo++) {
	if(pfo_match[ipfo]<0) continue;
	if(pfo_E[ipfo]<1) continue;
	if(pfo_match[ipfo]>1) continue;

	if(pfo_match[ipfo]==ijet) {
	  if(pfo_vtx[ipfo]==1) pfo_vtx_jet_counts[0]++;
	  else if(pfo_vtx[ipfo]==2) pfo_vtx_jet_counts[1]++;
	}	
      } //ipfo
      for(int ivtx=0;ivtx<2;ivtx++){
	if(pfo_vtx_jet_counts[ivtx]==1)pseudovtx++;
	if(pfo_vtx_jet_counts[ivtx]>1)jetvtx++;
      }
      cout<<"jetvtx: "<<jetvtx<<", pseudovtx: "<<pseudovtx<<endl;
      totalvtx=jetvtx+pseudovtx;
      
      // Now we filter
      if(cat=="catA"){
	if(jetvtx != 0)continue;
      }
      else if(cat=="catB"){
	if(jetvtx != 1) continue;
	else if (totalvtx !=1) continue;
      }
      else if(cat=="catC"){
	if(jetvtx != 1)continue;
	else if(totalvtx !=2) continue;
      }
      else if(cat=="catD"){
	if(jetvtx != 2)continue;
        else if(totalvtx !=2) continue;
      }
    
      for(int j=0; j<40;j++) {
	double tag=j*0.025;
	if(jet_btag[ijet]>tag) {
	  if(fabs(mc_quark_pdg[0])<4) h_jet_btag[j]->Fill(0);
	  h_jet_btag[j]->Fill(fabs(mc_quark_pdg[0]));
	}
	if(jet_ctag[ijet]>tag) {
	  if(fabs(mc_quark_pdg[0])<4) h_jet_ctag[j]->Fill(0);
	  h_jet_ctag[j]->Fill(fabs(mc_quark_pdg[0]));
	}
      }//for tag
    }//for ijet

  }//jentry
  
  for(int i=0; i<40;i++) {
    h_jet_btag[i]->Write();
    h_jet_ctag[i]->Write();
  }

}

void QQbarAnalysisClass::Selection(int n_entries=-1, int selection_type=0, float Kvcut=30, int bkg=0, TString cat="all")
{
  
  TFile *MyFile = new TFile(TString::Format("selection_%s_500GeV.root",process.Data()),"RECREATE");
  MyFile->cd();

  
  float   bb_gen=0,  bb_radreturn_gen=0,  qq_gen=0,   qq_radreturn_gen=0,   cc_gen=0,   cc_radreturn_gen=0;
  float   bb_counter=0,  bb_radreturn_counter=0,  qq_counter=0,   qq_radreturn_counter=0,   cc_counter=0,   cc_radreturn_counter=0;

  //costheta_nocuts
  TH1F * h_costheta_nocuts = new TH1F("h_costheta_nocuts","h_costheta_nocuts",20,0,1);

  //costheta
  TH1F * h_costheta_th_vs_lab_bb = new TH1F("h_costheta_th_vs_lab_bb","h_costheta_th_vs_lab_bb",4000,-1,1);
  TH1F * h_costheta_th_vs_lab_qq = new TH1F("h_costheta_th_vs_lab_qq","h_costheta_th_vs_lab_qq",4000,-1,1);
  TH1F * h_costheta_th_vs_lab_cc = new TH1F("h_costheta_th_vs_lab_cc","h_costheta_th_vs_lab_cc",4000,-1,1);
  TH1F * h_costheta_th_vs_lab_radreturn = new TH1F("h_costheta_th_vs_lab_radreturn","h_costheta_th_vs_lab_radreturn",4000,-1,1);

  //costheta
  TH1F * h_costheta_bb = new TH1F("h_costheta_bb","h_costheta_bb",20,0,1);
  TH1F * h_costheta_qq = new TH1F("h_costheta_qq","h_costheta_qq",20,0,1);
  TH1F * h_costheta_cc = new TH1F("h_costheta_cc","h_costheta_cc",20,0,1);
  // Adition by Jesus
  TH1F * h_costheta_dd = new TH1F("h_costheta_dd","h_costheta_dd",20,0,1);
  TH1F * h_costheta_uu = new TH1F("h_costheta_uu","h_costheta_uu",20,0,1);
  TH1F * h_costheta_ss = new TH1F("h_costheta_ss","h_costheta_ss",20,0,1);
  // End of addition
  TH1F * h_costheta_radreturn = new TH1F("h_costheta_radreturn","h_costheta_radreturn",20,0,1);
  
  //mc_costheta
  TH1F * h_mc_costheta_bb = new TH1F("h_mc_costheta_bb","h_mc_costheta_bb",40,-1,1);
  TH1F * h_mc_costheta_bb_isr = new TH1F("h_mc_costheta_bb_isr","h_mc_costheta_bb_isr",40,-1,1);
  TH1F * h_mc_costheta_cc = new TH1F("h_mc_costheta_cc","h_mc_costheta_cc",40,-1,1);
  TH1F * h_mc_costheta_cc_isr = new TH1F("h_mc_costheta_cc_isr","h_mc_costheta_cc_isr",40,-1,1);
  TH1F * h_mc_costheta_qq = new TH1F("h_mc_costheta_qq","h_mc_costheta_qq",40,-1,1);
  TH1F * h_mc_costheta_dd = new TH1F("h_mc_costheta_dd","h_mc_costheta_dd",40,-1,1);
  TH1F * h_mc_costheta_uu = new TH1F("h_mc_costheta_uu","h_mc_costheta_uu",40,-1,1);
  TH1F * h_mc_costheta_ss = new TH1F("h_mc_costheta_ss","h_mc_costheta_ss",40,-1,1);
  TH1F * h_mc_costheta_radreturn = new TH1F("h_mc_costheta_radreturn","h_mc_costheta_radreturn",40,-1,1);

  
  //mc_com_costheta
  TH1F * h_mc_com_costheta_bb = new TH1F("h_mc_com_costheta_bb","h_mc_com_costheta_bb",40,-1,1);
  TH1F * h_mc_com_costheta_bb_isr = new TH1F("h_mc_com_costheta_bb_isr","h_mc_com_costheta_bb_isr",40,-1,1);
  TH1F * h_mc_com_costheta_cc = new TH1F("h_mc_com_costheta_cc","h_mc_com_costheta_cc",40,-1,1);
  TH1F * h_mc_com_costheta_cc_isr = new TH1F("h_mc_com_costheta_cc_isr","h_mc_com_costheta_cc_isr",40,-1,1);
  TH1F * h_mc_com_costheta_qq = new TH1F("h_mc_com_costheta_qq","h_mc_com_costheta_qq",40,-1,1);
  TH1F * h_mc_com_costheta_dd = new TH1F("h_mc_com_costheta_dd","h_mc_com_costheta_dd",40,-1,1);
  TH1F * h_mc_com_costheta_uu = new TH1F("h_mc_com_costheta_uu","h_mc_com_costheta_uu",40,-1,1);
  TH1F * h_mc_com_costheta_ss = new TH1F("h_mc_com_costheta_ss","h_mc_com_costheta_ss",40,-1,1);
  TH1F * h_mc_com_costheta_radreturn = new TH1F("h_mc_com_costheta_radreturn","h_mc_com_costheta_radreturn",40,-1,1);

  // Addition by Jesus
  //mass & momentum & angle
  TH2F * h_e_costheta_gamma_uu = new TH2F("h_e_costheta_gamma_uu","h_e_costheta_gamma_uu",80,-1,1,100,0,1000);
  TH2F * h_e_costheta_gamma_dd = new TH2F("h_e_costheta_gamma_dd","h_e_costheta_gamma_dd",80,-1,1,100,0,1000);
  TH2F * h_e_costheta_gamma_ss = new TH2F("h_e_costheta_gamma_ss","h_e_costheta_gamma_ss",80,-1,1,100,0,1000);
  TH2F * h_e_costheta_gamma_bb = new TH2F("h_e_costheta_gamma_bb","h_e_costheta_gamma_bb",80,-1,1,100,0,1000);
  TH2F * h_e_costheta_gamma_radreturn = new TH2F("h_e_costheta_gamma_radreturn","h_e_costheta_gamma_radreturn",80,-1,1,100,0,1000);
  TH2F * h_e_costheta_gamma_qq = new TH2F("h_e_costheta_gamma_qq","h_e_costheta_gamma_qq",80,-1,1,100,0,1000);
  TH2F * h_e_costheta_gamma_cc = new TH2F("h_e_costheta_gamma_cc","h_e_costheta_gamma_cc",80,-1,1,100,0,1000);
  // End of addition

  //invariant mass
  TH1F * h_mjj_bb = new TH1F("h_mjj_bb","h_mjj_bb",100,0,500);
  TH1F * h_mjj_radreturn = new TH1F("h_mjj_radreturn","h_mjj_radreturn",100,0,500);
  TH1F * h_mjj_qq = new TH1F("h_mjj_qq","h_mjj_qq",100,0,500);
  TH1F * h_mjj_cc = new TH1F("h_mjj_cc","h_mjj_cc",100,0,500);

  //K
  TH1F * h_K = new TH1F("h_K","h_K",2000,0,250);
  TH1F * h_K_bb = new TH1F("h_K_bb","h_K_bb",2000,0,250);
  TH1F * h_K_radreturn = new TH1F("h_K_radreturn","h_K_radreturn",2000,0,250);
  TH1F * h_K_qq = new TH1F("h_K_qq","h_K_qq",2000,0,250);
  TH1F * h_K_cc = new TH1F("h_K_cc","h_K_cc",2000,0,250);
  TH1F * h_K_uu = new TH1F("h_K_uu","h_K_uu",2000,0,250);
  TH1F * h_K_dd = new TH1F("h_K_dd","h_K_dd",2000,0,250);
  TH1F * h_K_ss = new TH1F("h_K_ss","h_K_ss",2000,0,250);

  TH1F * h_K_parton_bb = new TH1F("h_K_parton_bb","h_K_parton_bb",2000,0,250);
  TH1F * h_K_parton_radreturn = new TH1F("h_K_parton_radreturn","h_K_parton_radreturn",2000,0,250);
  TH1F * h_K_parton_qq = new TH1F("h_K_parton_qq","h_K_parton_qq",2000,0,250);
  TH1F * h_K_parton_cc = new TH1F("h_K_parton_cc","h_K_parton_cc",2000,0,250);
  TH1F * h_K_parton_uu = new TH1F("h_K_parton_uu","h_K_parton_uu",2000,0,250);
  TH1F * h_K_parton_dd = new TH1F("h_K_parton_dd","h_K_parton_dd",2000,0,250);
  TH1F * h_K_parton_ss = new TH1F("h_K_parton_ss","h_K_parton_ss",2000,0,250);

  TH2F * h_K_parton_K_bb = new TH2F("h_K_parton_K_bb","h_K_parton_K_bb",200,0,200,200,0,250);
  TH2F * h_K_parton_K_radreturn = new TH2F("h_K_parton_K_radreturn","h_K_parton_K_radreturn",200,0,200,200,0,250);
  TH2F * h_K_parton_K_qq = new TH2F("h_K_parton_K_qq","h_K_parton_K_qq",200,0,200,200,0,250);
  TH2F * h_K_parton_K_cc = new TH2F("h_K_parton_K_cc","h_K_parton_K_cc",200,0,200,200,0,250);
  TH2F * h_K_parton_K_uu = new TH2F("h_K_parton_K_uu","h_K_parton_K_uu",200,0,200,200,0,250);
  TH2F * h_K_parton_K_dd = new TH2F("h_K_parton_K_dd","h_K_parton_K_dd",200,0,200,200,0,250);
  TH2F * h_K_parton_K_ss = new TH2F("h_K_parton_K_ss","h_K_parton_K_ss",200,0,200,200,0,250);
  
  // NPFOs
  //------------------------
  TH2F * h_photon_npfos_qq = new TH2F("h_photon_npfos_qq","h_photon_npfos_qq",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_cc = new TH2F("h_photon_npfos_cc","h_photon_npfos_cc",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_bb = new TH2F("h_photon_npfos_bb","h_photon_npfos_bb",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_radreturn = new TH2F("h_photon_npfos_radreturn","h_photon_npfos_radreturn",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_uu = new TH2F("h_photon_npfos_uu","h_photon_npfos_uu",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_dd = new TH2F("h_photon_npfos_dd","h_photon_npfos_dd",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_photon_npfos_ss = new TH2F("h_photon_npfos_ss","h_photon_npfos_ss",51,-0.5,50.5,51,-0.5,50.5);

  TH2F * h_charge_npfos_qq = new TH2F("h_charge_npfos_qq","h_charge_npfos_qq",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_cc = new TH2F("h_charge_npfos_cc","h_charge_npfos_cc",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_bb = new TH2F("h_charge_npfos_bb","h_charge_npfos_bb",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_radreturn = new TH2F("h_charge_npfos_radreturn","h_charge_npfos_radreturn",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_uu = new TH2F("h_charge_npfos_uu","h_charge_npfos_uu",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_dd = new TH2F("h_charge_npfos_dd","h_charge_npfos_dd",51,-0.5,50.5,51,-0.5,50.5);
  TH2F * h_charge_npfos_ss = new TH2F("h_charge_npfos_ss","h_charge_npfos_ss",51,-0.5,50.5,51,-0.5,50.5);

  TH2F * h_npfos_bb = new TH2F("h_npfos_bb","h_npfos_bb",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_radreturn = new TH2F("h_npfos_radreturn","h_npfos_radreturn",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_qq = new TH2F("h_npfos_qq","h_npfos_qq",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_cc = new TH2F("h_npfos_cc","h_npfos_cc",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_uu = new TH2F("h_npfos_uu","h_npfos_uu",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_dd = new TH2F("h_npfos_dd","h_npfos_dd",101,-0.5,100.5,101,-0.5,100.5);
  TH2F * h_npfos_ss = new TH2F("h_npfos_ss","h_npfos_ss",101,-0.5,100.5,101,-0.5,100.5);
  

  //jet algorithm variables
  TH1F * h_y23_bb = new TH1F("h_y23_bb","h_y23_bb",4000,0,0.25);
  TH1F * h_y23_radreturn = new TH1F("h_y23_radreturn","h_y23_radreturn",4000,0,0.25);
  TH1F * h_y23_qq = new TH1F("h_y23_qq","h_y23_qq",4000,0,0.25);
  TH1F * h_y23_cc = new TH1F("h_y23_cc","h_y23_cc",4000,0,0.25);
  TH1F * h_y23_uu = new TH1F("h_y23_uu","h_y23_uu",4000,0,0.25);
  TH1F * h_y23_dd = new TH1F("h_y23_dd","h_y23_dd",4000,0,0.25);
  TH1F * h_y23_ss = new TH1F("h_y23_ss","h_y23_ss",4000,0,0.25);

  TH1F * h_d23_bb = new TH1F("h_d23_bb","h_d23_bb",5000,-0.5,4999.5);
  TH1F * h_d23_radreturn = new TH1F("h_d23_radreturn","h_d23_radreturn",5000,-0.5,4999.5);
  TH1F * h_d23_qq = new TH1F("h_d23_qq","h_d23_qq",5000,-0.5,4999.5);
  TH1F * h_d23_cc = new TH1F("h_d23_cc","h_d23_cc",5000,-0.5,4999.5);
  TH1F * h_d23_uu = new TH1F("h_d23_uu","h_d23_uu",5000,-0.5,4999.5);
  TH1F * h_d23_dd = new TH1F("h_d23_dd","h_d23_dd",5000,-0.5,4999.5);
  TH1F * h_d23_ss = new TH1F("h_d23_ss","h_d23_ss",5000,-0.5,4999.5);

  TH1F * h_thrust_bb = new TH1F("h_thrust_bb","h_thrust_bb",400,0.95,1);
  TH1F * h_thrust_radreturn = new TH1F("h_thrust_radreturn","h_thrust_radreturn",400,0.95,1);
  TH1F * h_thrust_qq = new TH1F("h_thrust_qq","h_thrust_qq",400,0.95,1);
  TH1F * h_thrust_cc = new TH1F("h_thrust_cc","h_thrust_cc",400,0.95,1);
  TH1F * h_thrust_uu = new TH1F("h_thrust_uu","h_thrust_uu",400,0.95,1);
  TH1F * h_thrust_dd = new TH1F("h_thrust_dd","h_thrust_dd",400,0.95,1);
  TH1F * h_thrust_ss = new TH1F("h_thrust_ss","h_thrust_ss",400,0.95,1);

   //mass of two jets
  TH1F * h_mj1_mj2_bb = new TH1F("h_mj1_mj2_bb","h_mj1_mj2_bb",400,0,250);
  TH1F * h_mj1_mj2_radreturn = new TH1F("h_mj1_mj2_radreturn","h_mj1_mj2_radreturn",400,0,250);
  TH1F * h_mj1_mj2_qq = new TH1F("h_mj1_mj2_qq","h_mj1_mj2_qq",400,0,250);
  TH1F * h_mj1_mj2_cc = new TH1F("h_mj1_mj2_cc","h_mj1_mj2_cc",400,0,250);
  TH1F * h_mj1_mj2_uu = new TH1F("h_mj1_mj2_uu","h_mj1_mj2_uu",400,0,250);
  TH1F * h_mj1_mj2_dd = new TH1F("h_mj1_mj2_dd","h_mj1_mj2_dd",400,0,250);
  TH1F * h_mj1_mj2_ss = new TH1F("h_mj1_mj2_ss","h_mj1_mj2_ss",400,0,250);

  
  TH1F * montecarlo_b1mass = new TH1F("montecarlo_b1mass","montecarlo_b1mass",400,0,0.1);
  TH1F * montecarlo_b2mass = new TH1F("montecarlo_b2mass","montecarlo_b2mass",400,0,0.1);

  
  TH1F * montecarlo_b1_velocity = new TH1F("montecarlo_b1_velocity","montecarlo_b1_velocity",1000,0.99999995,1.00000005);
  TH1F * montecarlo_b2_velocity = new TH1F("montecarlo_b2_velocity","montecarlo_b2_velocity",1000,0.99999995,1.00000005);


  TH1F * v_cm_bb = new TH1F("v_cm_bb","v_cm_bb",1000,0,1);  

  // New variables 22/12/21
  
  TH2F * h_photon_likeness_bb = new TH2F("h_photon_likeness_bb","h_photon_likeness_bb",200,0,1,200,0,1);
  TH2F * h_photon_likeness_cc = new TH2F("h_photon_likeness_cc","h_photon_likeness_cc",200,0,1,200,0,1);
  TH2F * h_photon_likeness_uu = new TH2F("h_photon_likeness_uu","h_photon_likeness_uu",200,0,1,200,0,1);
  TH2F * h_photon_likeness_dd = new TH2F("h_photon_likeness_dd","h_photon_likeness_dd",200,0,1,200,0,1);
  TH2F * h_photon_likeness_ss = new TH2F("h_photon_likeness_ss","h_photon_likeness_ss",200,0,1,200,0,1);
  TH2F * h_photon_likeness_qq = new TH2F("h_photon_likeness_qq","h_photon_likeness_qq",200,0,1,200,0,1);
  TH2F * h_photon_likeness_radreturn = new TH2F("h_photon_likeness_radreturn","h_photon_likeness_radreturn",200,0,1,200,0,1);

  
  TH2F * h_charge_likeness_bb = new TH2F("h_charge_likeness_bb","h_charge_likeness_bb",200,0,1,200,0,1);
  TH2F * h_charge_likeness_cc = new TH2F("h_charge_likeness_cc","h_charge_likeness_cc",200,0,1,200,0,1);
  TH2F * h_charge_likeness_uu = new TH2F("h_charge_likeness_uu","h_charge_likeness_uu",200,0,1,200,0,1);
  TH2F * h_charge_likeness_dd = new TH2F("h_charge_likeness_dd","h_charge_likeness_dd",200,0,1,200,0,1);
  TH2F * h_charge_likeness_ss = new TH2F("h_charge_likeness_ss","h_charge_likeness_ss",200,0,1,200,0,1);
  TH2F * h_charge_likeness_qq = new TH2F("h_charge_likeness_qq","h_charge_likeness_qq",200,0,1,200,0,1);
  TH2F * h_charge_likeness_radreturn = new TH2F("h_charge_likeness_radreturn","h_charge_likeness_radreturn",200,0,1,200,0,1);

  
  TH1F * h_oblateness_bb = new TH1F("h_oblateness_bb","h_oblateness_bb",100,0,0.8);
  TH1F * h_oblateness_qq = new TH1F("h_oblateness_qq","h_oblateness_qq",100,0,0.8);
  TH1F * h_oblateness_cc = new TH1F("h_oblateness_cc","h_oblateness_cc",100,0,0.8);
  TH1F * h_oblateness_uu = new TH1F("h_oblateness_uu","h_oblateness_uu",100,0,0.8);
  TH1F * h_oblateness_dd = new TH1F("h_oblateness_dd","h_oblateness_dd",100,0,0.8);
  TH1F * h_oblateness_ss = new TH1F("h_oblateness_ss","h_oblateness_ss",100,0,0.8);
  TH1F * h_oblateness_radreturn = new TH1F("h_oblateness_radreturn","h_oblateness_radreturn",100,0,0.8);

  TH1F * h_aplanarity_bb = new TH1F("h_aplanarity_bb","h_aplanarity_bb",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_qq = new TH1F("h_aplanarity_qq","h_aplanarity_qq",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_cc = new TH1F("h_aplanarity_cc","h_aplanarity_cc",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_uu = new TH1F("h_aplanarity_uu","h_aplanarity_uu",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_dd = new TH1F("h_aplanarity_dd","h_aplanarity_dd",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_ss = new TH1F("h_aplanarity_ss","h_aplanarity_ss",100,-0.4e-6,0.4e-6);
  TH1F * h_aplanarity_radreturn = new TH1F("h_aplanarity_radreturn","h_aplanarity_radreturn",100,-0.4e-6,0.4e-6);

  TH1F * h_sphericity_bb = new TH1F("h_sphericity_bb","h_sphericity_bb",2000,0,2);
  TH1F * h_sphericity_qq = new TH1F("h_sphericity_qq","h_sphericity_qq",2000,0,2);
  TH1F * h_sphericity_cc = new TH1F("h_sphericity_cc","h_sphericity_cc",2000,0,2);
  TH1F * h_sphericity_uu = new TH1F("h_sphericity_uu","h_sphericity_uu",2000,0,2);
  TH1F * h_sphericity_dd = new TH1F("h_sphericity_dd","h_sphericity_dd",2000,0,2);
  TH1F * h_sphericity_ss = new TH1F("h_sphericity_ss","h_sphericity_ss",2000,0,2);
  TH1F * h_sphericity_radreturn = new TH1F("h_sphericity_radreturn","h_sphericity_radreturn",2000,0,2);
  
  Long64_t nentries;
  if(n_entries>0) nentries= n_entries;
  else nentries= fChain->GetEntriesFast();


  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    // Category selection
    for(int ijet=0; ijet<2; ijet++) {
      Int_t jetvtx=0;
      Int_t pseudovtx=0;
      Int_t totalvtx=0;
      Int_t pfo_vtx_jet_counts[2];
      pfo_vtx_jet_counts[0]=0;
      pfo_vtx_jet_counts[1]=0;
      for(int ipfo=0; ipfo<pfo_n; ipfo++) {
        if(pfo_match[ipfo]<0) continue;
        if(pfo_E[ipfo]<1) continue;
        if(pfo_match[ipfo]>1) continue;

        if(pfo_match[ipfo]==ijet) {
          if(pfo_vtx[ipfo]==1) pfo_vtx_jet_counts[0]++;
          else if(pfo_vtx[ipfo]==2) pfo_vtx_jet_counts[1]++;
        }
      } //ipfo                                                                                                                                                                                                                                
      for(int ivtx=0;ivtx<2;ivtx++){
        if(pfo_vtx_jet_counts[ivtx]==1)pseudovtx++;
        if(pfo_vtx_jet_counts[ivtx]>1)jetvtx++;
      }
      cout<<"jetvtx: "<<jetvtx<<", pseudovtx: "<<pseudovtx<<endl;
      totalvtx=jetvtx+pseudovtx;

      // Now we filter                                                                                                                                                                                                                        
      if(cat=="catA"){
        if(jetvtx != 0)continue;
      }
      else if(cat=="catB"){
        if(jetvtx != 1) continue;
        else if (totalvtx !=1) continue;
      }
      else if(cat=="catC"){
        if(jetvtx != 1)continue;
        else if(totalvtx !=2) continue;
      }
      else if(cat=="catD"){
        if(jetvtx != 2)continue;
        else if(totalvtx !=2) continue;
      }
    }//for ijet 

    //-------------------
    //Kv parton
    float gamma0_e= mc_ISR_E[0];
    float gamma1_e= mc_ISR_E[1];
    float gamma_e = gamma0_e+gamma1_e;

    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
      bb_gen++;
    }
    if(gamma_e>Kvcut ) {
      if(fabs(mc_quark_pdg[0])==5) bb_radreturn_gen++;
      if(fabs(mc_quark_pdg[0])==4) cc_radreturn_gen++;
      if(fabs(mc_quark_pdg[0])<4) qq_radreturn_gen++;
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut){
      cc_gen++;
    }
    if(fabs(mc_quark_pdg[0])<5 && gamma_e<Kvcut) {
      qq_gen++;
    }


    if ( jentry > 100000 && jentry % 100000 ==0 ) std::cout << "Progress: " << 100.*jentry/nentries <<" %"<<endl;

    //reco stuff
    
    double reco_b1mass=sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass=sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    double reco_bbmass=sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

    double jet0_p = sqrt(pow(jet_px[0],2)+pow(jet_py[0],2)+pow(jet_pz[0],2));
    double jet1_p = sqrt(pow(jet_px[1],2)+pow(jet_py[1],2)+pow(jet_pz[1],2));

    double jj_pT= sqrt(pow(jet_px[0]+jet_px[1],2)+pow(jet_py[0]+jet_py[1],2));

    float costheta_bbbar;
    std::vector<float> p_bbbar;
    p_bbbar.push_back(jet_px[0]-jet_px[1]);
    p_bbbar.push_back(jet_py[0]-jet_py[1]);
    p_bbbar.push_back(jet_pz[0]-jet_pz[1]);
    costheta_bbbar=fabs(GetCostheta(p_bbbar));

    //------------------------------------------------------
    
    float mc_costheta_bbbar;
    std::vector<float> p_mc_bbbar;
    p_mc_bbbar.push_back(mc_quark_px[0]-mc_quark_px[1]);
    p_mc_bbbar.push_back(mc_quark_py[0]-mc_quark_py[1]);
    p_mc_bbbar.push_back(mc_quark_pz[0]-mc_quark_pz[1]);
    if(mc_quark_pdg[0]>0){mc_costheta_bbbar=GetCostheta(p_mc_bbbar);}
    if(mc_quark_pdg[0]<0){mc_costheta_bbbar=-1*GetCostheta(p_mc_bbbar);}

    // COM system:
    
    TVector3 trimomentum_q1(mc_quark_px[0],mc_quark_py[0],mc_quark_pz[0]);    
    TVector3 trimomentum_q2(mc_quark_px[1],mc_quark_py[1],mc_quark_pz[1]);
    double p1_mod=sqrt(abs(pow(mc_quark_px[0],2)+pow(mc_quark_py[0],2)+pow(mc_quark_pz[0],2)));
    double p2_mod=sqrt(abs(pow(mc_quark_px[1],2)+pow(mc_quark_py[1],2)+pow(mc_quark_pz[1],2)));
    TLorentzVector fourmomentum_q1(trimomentum_q1,mc_quark_E[0]); 
    TLorentzVector fourmomentum_q2(trimomentum_q2,mc_quark_E[1]);

    
    double E_q1=abs(mc_quark_E[0]);
    double E_q2=abs(mc_quark_E[1]);
    double mc_b1mass=sqrt(abs(pow(mc_quark_E[0],2)-pow(mc_quark_px[0],2)-pow(mc_quark_py[0],2)-pow(mc_quark_pz[0],2))); // abs()!?
    double mc_b2mass=sqrt(abs(pow(mc_quark_E[1],2)-pow(mc_quark_px[1],2)-pow(mc_quark_py[1],2)-pow(mc_quark_pz[1],2))); // abs()!?
   
    double gammafactor_q1;
    double gammafactor_q2;
    TVector3 velocity_q1;
    TVector3 velocity_q2;

    if(mc_b1mass==0){
      gammafactor_q1=1;
      velocity_q1[0]=trimomentum_q1[0]/p1_mod;
      velocity_q1[1]=trimomentum_q1[1]/p1_mod;
      velocity_q1[2]=trimomentum_q1[2]/p1_mod;}
    else{
      gammafactor_q1=abs(E_q1/mc_b1mass);
      velocity_q1[0]=trimomentum_q1[0]/(gammafactor_q1*mc_b1mass);
      velocity_q1[1]=trimomentum_q1[1]/(gammafactor_q1*mc_b1mass);
      velocity_q1[2]=trimomentum_q1[2]/(gammafactor_q1*mc_b1mass);}

    
    if(mc_b2mass==0){
      gammafactor_q2=1;
      velocity_q2[0]=trimomentum_q2[0]/p2_mod;
      velocity_q2[1]=trimomentum_q2[1]/p2_mod;
      velocity_q2[2]=trimomentum_q2[2]/p2_mod;}
    else{
      gammafactor_q2=abs(E_q2/mc_b2mass);
      velocity_q2[0]=trimomentum_q2[0]/(gammafactor_q2*mc_b2mass);
      velocity_q2[1]=trimomentum_q2[1]/(gammafactor_q2*mc_b2mass);
      velocity_q2[2]=trimomentum_q2[2]/(gammafactor_q2*mc_b2mass);}
    

    double v1_mod=sqrt(pow(velocity_q1[0],2)+pow(velocity_q1[1],2)+pow(velocity_q1[2],2));
    double v2_mod=sqrt(pow(velocity_q2[0],2)+pow(velocity_q2[1],2)+pow(velocity_q2[2],2));
    

     
    // Pure kinematic method
    /*
    TVector3 v_com;
    v_com[0]=(E_q1*velocity_q1[0]+E_q2*velocity_q2[0])/(E_q1+E_q2);
    v_com[1]=(E_q1*velocity_q1[1]+E_q2*velocity_q2[1])/(E_q1+E_q2);
    v_com[2]=(E_q1*velocity_q1[2]+E_q2*velocity_q2[2])/(E_q1+E_q2);
    double v_com_mod=sqrt(pow(v_com[0],2)+pow(v_com[1],2)+pow(v_com[2],2));
    */
    //----------------------
    //Alternative method:
    
    double mc_com_mass=sqrt(pow(mc_quark_E[0]+mc_quark_E[1],2)-pow(mc_quark_px[0]+mc_quark_px[1],2)-pow(mc_quark_py[0]+mc_quark_py[1],2)-pow(mc_quark_pz[0]+mc_quark_pz[1],2));
    double gamma_com=(mc_quark_E[0]+mc_quark_E[1])/mc_com_mass;
    TVector3 v_com;
    v_com[0]=(mc_quark_px[0]+mc_quark_px[1])/(gamma_com*mc_com_mass);
    v_com[1]=(mc_quark_py[0]+mc_quark_py[1])/(gamma_com*mc_com_mass);
    v_com[2]=(mc_quark_pz[0]+mc_quark_pz[1])/(gamma_com*mc_com_mass);
    double v_com_mod=sqrt(pow(v_com[0],2)+pow(v_com[1],2)+pow(v_com[2],2));

    //---------------------------------------------
    

    
    TVector3 beta_vector=v_com; //since we are using natural units this is v_com?
    double bx=beta_vector[0];
    double by=beta_vector[1];
    double bz=beta_vector[2];
    double gammafactor=pow(1-pow(v_com_mod,2),-0.5);
    double BoostMatrix[4][4];
    if(v_com_mod==0){
    BoostMatrix[0][0]=1;
    BoostMatrix[0][1]=0;
    BoostMatrix[0][2]=0;
    BoostMatrix[0][3]=0;
    BoostMatrix[1][0]=0;
    BoostMatrix[1][1]=1;
    BoostMatrix[1][2]=0;
    BoostMatrix[1][3]=0;
    BoostMatrix[2][0]=0;
    BoostMatrix[2][1]=0;
    BoostMatrix[2][2]=1;
    BoostMatrix[2][3]=0;    
    BoostMatrix[3][0]=0;
    BoostMatrix[3][1]=0;
    BoostMatrix[3][2]=0;
    BoostMatrix[3][3]=1;
    }
    else{
    BoostMatrix[0][0]=1+(gammafactor-1)*v_com[0]*v_com[0]*pow(v_com_mod,-2);
    BoostMatrix[0][1]=(gammafactor-1)*v_com[0]*v_com[1]*pow(v_com_mod,-2);
    BoostMatrix[0][2]=(gammafactor-1)*v_com[0]*v_com[2]*pow(v_com_mod,-2);
    BoostMatrix[0][3]=-gammafactor*v_com[0];
    BoostMatrix[1][0]=(gammafactor-1)*v_com[1]*v_com[0]*pow(v_com_mod,-2);
    BoostMatrix[1][1]=1+(gammafactor-1)*v_com[1]*v_com[1]*pow(v_com_mod,-2);
    BoostMatrix[1][2]=(gammafactor-1)*v_com[1]*v_com[2]*pow(v_com_mod,-2);
    BoostMatrix[1][3]=-gammafactor*v_com[1];
    BoostMatrix[2][0]=(gammafactor-1)*v_com[2]*v_com[0]*pow(v_com_mod,-2);
    BoostMatrix[2][1]=(gammafactor-1)*v_com[2]*v_com[1]*pow(v_com_mod,-2);
    BoostMatrix[2][2]=1+(gammafactor-1)*v_com[2]*v_com[2]*pow(v_com_mod,-2);
    BoostMatrix[2][3]=-gammafactor*v_com[2];    
    BoostMatrix[3][0]=-gammafactor*v_com[0];
    BoostMatrix[3][1]=-gammafactor*v_com[1];
    BoostMatrix[3][2]=-gammafactor*v_com[2];
    BoostMatrix[3][3]=gammafactor;
    }
    
    TLorentzVector fourmomentum_q1_com;
    fourmomentum_q1_com[0]=fourmomentum_q1[0]*BoostMatrix[0][0]+fourmomentum_q1[1]*BoostMatrix[0][1]+fourmomentum_q1[2]*BoostMatrix[0][2]+fourmomentum_q1[3]*BoostMatrix[0][3];
    fourmomentum_q1_com[1]=fourmomentum_q1[0]*BoostMatrix[1][0]+fourmomentum_q1[1]*BoostMatrix[1][1]+fourmomentum_q1[2]*BoostMatrix[1][2]+fourmomentum_q1[3]*BoostMatrix[1][3];
    fourmomentum_q1_com[2]=fourmomentum_q1[0]*BoostMatrix[2][0]+fourmomentum_q1[1]*BoostMatrix[2][1]+fourmomentum_q1[2]*BoostMatrix[2][2]+fourmomentum_q1[3]*BoostMatrix[2][3];
    fourmomentum_q1_com[3]=fourmomentum_q1[0]*BoostMatrix[3][0]+fourmomentum_q1[1]*BoostMatrix[3][1]+fourmomentum_q1[2]*BoostMatrix[3][2]+fourmomentum_q1[3]*BoostMatrix[3][3];

    
    TLorentzVector fourmomentum_q2_com;
    fourmomentum_q2_com[0]=fourmomentum_q2[0]*BoostMatrix[0][0]+fourmomentum_q2[1]*BoostMatrix[0][1]+fourmomentum_q2[2]*BoostMatrix[0][2]+fourmomentum_q2[3]*BoostMatrix[0][3];
    fourmomentum_q2_com[1]=fourmomentum_q2[0]*BoostMatrix[1][0]+fourmomentum_q2[1]*BoostMatrix[1][1]+fourmomentum_q2[2]*BoostMatrix[1][2]+fourmomentum_q2[3]*BoostMatrix[1][3];
    fourmomentum_q2_com[2]=fourmomentum_q2[0]*BoostMatrix[2][0]+fourmomentum_q2[1]*BoostMatrix[2][1]+fourmomentum_q2[2]*BoostMatrix[2][2]+fourmomentum_q2[3]*BoostMatrix[2][3];
    fourmomentum_q2_com[3]=fourmomentum_q2[0]*BoostMatrix[3][0]+fourmomentum_q2[1]*BoostMatrix[3][1]+fourmomentum_q2[2]*BoostMatrix[3][2]+fourmomentum_q2[3]*BoostMatrix[3][3];


    
    float mc_com_costheta_bbbar;
    std::vector<float> p_mc_com_bbbar;
    p_mc_com_bbbar.push_back(fourmomentum_q1_com[0]-fourmomentum_q2_com[0]);
    p_mc_com_bbbar.push_back(fourmomentum_q1_com[1]-fourmomentum_q2_com[1]);
    p_mc_com_bbbar.push_back(fourmomentum_q1_com[2]-fourmomentum_q2_com[2]);
    if(mc_quark_pdg[0]>0){mc_com_costheta_bbbar=GetCostheta(p_mc_com_bbbar);}
    if(mc_quark_pdg[0]<0){mc_com_costheta_bbbar=-1*GetCostheta(p_mc_com_bbbar);}
    
    //------------------------------------------------------
    
    float costheta_thrust;
    std::vector<float> p_thrust;
    p_thrust.push_back(principle_thrust_axis[0]);
    p_thrust.push_back(principle_thrust_axis[1]);
    p_thrust.push_back(principle_thrust_axis[2]);
    costheta_thrust=fabs(GetCostheta(p_thrust));
    
    h_costheta_nocuts->Fill(costheta_bbbar);

    // 22/12/21:

    double  E_total[2]={0};
    double  photonPFO_ratio[2]={0};

    double  photonjet_E[2]={0};
    double  photonjet_costheta[2];
    photonjet_costheta[0]=-2;
    photonjet_costheta[1]=-2;

   
    //---------------------
    //Radiative return cuts, photon INSIDE the detector
    double npfo[2]={-1};
    double npfo_photon[2]={-1};
    float costheta=-2;
    float energy=0;
    
    //  for(int ijet=0; ijet<2; ijet++) {
    float costheta_jet_0=0;
    float costheta_jet_1=0;
    std::vector<float> p_pfo_0;
    std::vector<float> p_pfo_1;
    float px_0=0, py_0=0, pz_0=0;
    float px_1=0, py_1=0, pz_1=0;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
      
      if(pfo_match[ipfo]<0) continue;
      if(pfo_E[ipfo]<1) continue;
      // Quitar si va mal
      if(pfo_match[ipfo]>1) continue;
      //-----------------------------
  
      npfo[pfo_match[ipfo]]++;
    
      E_total[pfo_match[ipfo]] += pfo_E[ipfo];
    
      if( pfo_type[ipfo]==22  || fabs(pfo_type[ipfo])==2112 ) {
      
	npfo_photon[pfo_match[ipfo]]++;

	if(pfo_match[ipfo]==0) {
	  px_0+=pfo_px[ipfo];
	  py_0+=pfo_py[ipfo];
	  pz_0+=pfo_pz[ipfo];
	}
	if(pfo_match[ipfo]==1) {
	  px_1+=pfo_px[ipfo];
	  py_1+=pfo_py[ipfo];
	  pz_1+=pfo_pz[ipfo];
	}
	photonjet_E[pfo_match[ipfo]] += pfo_E[ipfo];
      }
    }//ipfo
  
    p_pfo_0.push_back(px_0);
    p_pfo_0.push_back(py_0);
    p_pfo_0.push_back(pz_0);
    float costheta_pfo_0=GetCostheta(p_pfo_0);
    //changed to:
    costheta_jet_0= costheta_pfo_0;
    photonjet_costheta[0]=GetCostheta(p_pfo_0);
    //------------

    p_pfo_1.push_back(px_1);
    p_pfo_1.push_back(py_1);
    p_pfo_1.push_back(pz_1);
    float costheta_pfo_1=GetCostheta(p_pfo_1);
    //changed to:
    costheta_jet_1= costheta_pfo_1;
    photonjet_costheta[1]=costheta_pfo_1;
    //------------
  
  
    photonPFO_ratio[0]=photonjet_E[0]/E_total[0];
    photonPFO_ratio[1]=photonjet_E[1]/E_total[1];


       //charge
    
    double  chargePFO_ratio[2]={0};

    double  chargejet_E[2]={0};
    double  chargejet_costheta[2];
    chargejet_costheta[0]=-2;
    chargejet_costheta[1]=-2;
    
    // double npfo[2]={0};
    //double npfo_photon[2]={0};
    // float costheta=-2;
    //float energy=0;
    Int_t npfo_charge[2]={-1};
    
    //  for(int ijet=0; ijet<2; ijet++) {
    //float costheta_jet_0=0;
    //float costheta_jet_1=0;
    //std::vector<float> p_pfo_0;
    //std::vector<float> p_pfo_1;
    //float px_0=0, py_0=0, pz_0=0;
    //float px_1=0, py_1=0, pz_1=0;

    for(int ipfo=0; ipfo<pfo_n; ipfo++) {//jet_pfo_n[ijet]; ipfo++) {
      
      if(pfo_match[ipfo]<0) continue;
      if(pfo_E[ipfo]<1) continue; 
      if(pfo_match[ipfo]>1) continue;

      //17/01/21 quito esto (Se estaba contando dos veces lo mismo?)
      //npfo[pfo_match[ipfo]]++;
    
      E_total[pfo_match[ipfo]] += pfo_E[ipfo];
    
      if( pfo_charge[ipfo] != 0  ) {
      
	npfo_charge[pfo_match[ipfo]]++;

	if(pfo_match[ipfo]==0) {
	  px_0+=pfo_px[ipfo];
	  py_0+=pfo_py[ipfo];
	  pz_0+=pfo_pz[ipfo];
	}
	if(pfo_match[ipfo]==1) {
	  px_1+=pfo_px[ipfo];
	  py_1+=pfo_py[ipfo];
	  pz_1+=pfo_pz[ipfo];
	}
	chargejet_E[pfo_match[ipfo]] += pfo_E[ipfo];
      }
    }//ipfo
  
  
    chargePFO_ratio[0]=chargejet_E[0]/E_total[0];
    chargePFO_ratio[1]=chargejet_E[1]/E_total[1];

    //--------------------------------


    float Kv=Kreco();
    //parte importante
    bool selection=PreSelection(selection_type,Kvcut);
    if(selection==false) continue;

    //---------------------
    //Radiative return cuts, photon INSIDE the detector
    PFOphotonQuantities();
    // HASTA AQUI Las cosas de PFOs

    if(bkg==1)  {

      h_mc_costheta_bb->Fill(mc_costheta_bbbar);
      h_mc_com_costheta_bb->Fill(mc_com_costheta_bbbar);      
      
      h_costheta_th_vs_lab_bb->Fill(costheta_bbbar-costheta_thrust);
      h_costheta_bb->Fill(costheta_bbbar);
      h_mjj_bb->Fill(reco_bbmass);
      h_photon_npfos_bb->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_bb->Fill(npfo[0],npfo[1]);
      h_charge_npfos_bb->Fill(npfo_charge[0],npfo_charge[1]);

      
      //Addition by Jesus
      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_bb->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_bb->Fill(photonjet_costheta[1],photonjet_E[1]);
      //End of addition
      
      // -------------------------
     
      h_y23_bb->Fill(d23/pow(reco_bbmass,2));
      h_d23_bb->Fill(d23);
      h_thrust_bb->Fill(principle_thrust_value);
      h_mj1_mj2_bb->Fill(reco_b1mass+reco_b2mass);
      h_K_bb->Fill(Kv);
      h_K_parton_bb->Fill(gamma_e);
      h_K_parton_K_bb->Fill(gamma_e,Kv);

      // 22/12/21:
      h_photon_likeness_bb->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_charge_likeness_bb->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_oblateness_bb->Fill(oblateness);
      h_aplanarity_bb->Fill(aplanarity);
      h_sphericity_bb->Fill(sphericity);
      
    } else  {

    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
      bb_counter++;
    }
    if(gamma_e>Kvcut ) {
      if(fabs(mc_quark_pdg[0])==5) bb_radreturn_counter++;
      if(fabs(mc_quark_pdg[0])==4) cc_radreturn_counter++;
      if(fabs(mc_quark_pdg[0])<4)qq_radreturn_counter++;
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut){
      cc_counter++;
    }
    if(fabs(mc_quark_pdg[0])<5 && gamma_e<Kvcut) {
      qq_counter++;
    }
    
    if(gamma_e>Kvcut) {

      
      h_costheta_th_vs_lab_radreturn->Fill(costheta_bbbar-costheta_thrust);
      h_mc_costheta_radreturn->Fill(mc_costheta_bbbar);
      h_mc_com_costheta_radreturn->Fill(mc_com_costheta_bbbar);
      h_costheta_radreturn->Fill(costheta_bbbar);
      h_mjj_radreturn->Fill(reco_bbmass);

      h_photon_npfos_radreturn->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_radreturn->Fill(npfo[0],npfo[1]);
      h_charge_npfos_radreturn->Fill(npfo_charge[0],npfo_charge[1]);


      //Addition by Jesus
      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_radreturn->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_radreturn->Fill(photonjet_costheta[1],photonjet_E[1]);
      //End of addition
      
      // -------------------------
      h_y23_radreturn->Fill(d23/pow(reco_bbmass,2));
      h_d23_radreturn->Fill(d23);
      h_thrust_radreturn->Fill(principle_thrust_value);
      h_mj1_mj2_radreturn->Fill(reco_b1mass+reco_b2mass);
      h_K_radreturn->Fill(Kv);
      h_K_parton_radreturn->Fill(gamma_e);
      h_K_parton_K_radreturn->Fill(gamma_e,Kv);
      
      h_photon_likeness_radreturn->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_charge_likeness_radreturn->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_oblateness_radreturn->Fill(oblateness);
      h_aplanarity_radreturn->Fill(aplanarity);
      h_sphericity_radreturn->Fill(sphericity);
    }


    if(fabs(mc_quark_pdg[0])==5 && gamma_e>Kvcut) {
      h_mc_costheta_bb_isr->Fill(mc_costheta_bbbar);
      h_mc_com_costheta_bb_isr->Fill(mc_com_costheta_bbbar);
    }
    
    if(fabs(mc_quark_pdg[0])==5 && gamma_e<Kvcut) {
      v_cm_bb->Fill(v_com_mod);
      montecarlo_b1_velocity->Fill(v1_mod);
      montecarlo_b2_velocity->Fill(v2_mod);
      montecarlo_b1mass->Fill(mc_b1mass);
      montecarlo_b2mass->Fill(mc_b2mass);
      
      h_costheta_th_vs_lab_bb->Fill(costheta_bbbar-costheta_thrust);
      h_mc_costheta_bb->Fill(mc_costheta_bbbar);
      h_mc_com_costheta_bb->Fill(mc_com_costheta_bbbar);
      h_costheta_bb->Fill(costheta_bbbar);
      //Addition by Jesus
      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_bb->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_bb->Fill(photonjet_costheta[1],photonjet_E[1]);
      //End of addition
      h_mjj_bb->Fill(reco_bbmass);

      h_photon_npfos_bb->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_bb->Fill(npfo[0],npfo[1]);
      h_charge_npfos_bb->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
     
      h_y23_bb->Fill(d23/pow(reco_bbmass,2));
      h_d23_bb->Fill(d23);
      h_mj1_mj2_bb->Fill(reco_b1mass+reco_b2mass);
      h_thrust_bb->Fill(principle_thrust_value);
      h_K_bb->Fill(Kv);
      h_K_parton_bb->Fill(gamma_e);
      h_K_parton_K_bb->Fill(gamma_e,Kv);

      // 22/12/21:
      h_photon_likeness_bb->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_charge_likeness_bb->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_oblateness_bb->Fill(oblateness);
      h_aplanarity_bb->Fill(aplanarity);
      h_sphericity_bb->Fill(sphericity);
    }

    if(fabs(mc_quark_pdg[0])==4 && gamma_e>Kvcut) {
      h_mc_costheta_cc_isr->Fill(mc_costheta_bbbar);
      h_mc_com_costheta_cc_isr->Fill(mc_com_costheta_bbbar);
    }
    if(fabs(mc_quark_pdg[0])==4 && gamma_e<Kvcut) {
   
      h_costheta_th_vs_lab_cc->Fill(costheta_bbbar-costheta_thrust);
      h_mc_costheta_cc->Fill(mc_costheta_bbbar);
      h_mc_com_costheta_cc->Fill(mc_com_costheta_bbbar);
      h_costheta_cc->Fill(costheta_bbbar);
      h_mjj_cc->Fill(reco_bbmass);

      //Addition by Jesus
      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_cc->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_cc->Fill(photonjet_costheta[1],photonjet_E[1]);
      //End of addition
      h_photon_npfos_cc->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_cc->Fill(npfo[0],npfo[1]);
      h_charge_npfos_cc->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
    
      h_y23_cc->Fill(d23/pow(reco_bbmass,2));
      h_d23_cc->Fill(d23);
      h_mj1_mj2_cc->Fill(reco_b1mass+reco_b2mass);
      h_thrust_cc->Fill(principle_thrust_value);
      h_K_cc->Fill(Kv);
      h_K_parton_cc->Fill(gamma_e);
      h_K_parton_K_cc->Fill(gamma_e,Kv);

      // 22/12/21:
      h_photon_likeness_cc->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_charge_likeness_cc->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_oblateness_cc->Fill(oblateness);
      h_aplanarity_cc->Fill(aplanarity);
      h_sphericity_cc->Fill(sphericity);
    }

    // --Added by Jesus to study all flavours
    if(fabs(mc_quark_pdg[0])==1 && gamma_e<Kvcut) { 
      h_mc_costheta_dd->Fill(mc_costheta_bbbar); 
      h_mc_com_costheta_dd->Fill(mc_com_costheta_bbbar);  
      h_costheta_dd->Fill(costheta_bbbar);
      
      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_dd->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_dd->Fill(photonjet_costheta[1],photonjet_E[1]);
      // -------------------------
    
      h_y23_dd->Fill(d23/pow(reco_bbmass,2));
      h_d23_dd->Fill(d23);
      h_mj1_mj2_dd->Fill(reco_b1mass+reco_b2mass);
      h_thrust_dd->Fill(principle_thrust_value);
      h_K_dd->Fill(Kv);
      h_K_parton_dd->Fill(gamma_e);
      h_K_parton_K_dd->Fill(gamma_e,Kv);
      
      // 21/12/21:
      h_photon_likeness_dd->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_charge_likeness_dd->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_oblateness_dd->Fill(oblateness);
      h_aplanarity_dd->Fill(aplanarity);
      h_sphericity_dd->Fill(sphericity);
    }
    
    if(fabs(mc_quark_pdg[0])==2 && gamma_e<Kvcut) {
      
      h_costheta_uu->Fill(costheta_bbbar);
      h_mc_costheta_uu->Fill(mc_costheta_bbbar);
      h_mc_com_costheta_uu->Fill(mc_com_costheta_bbbar);
      
      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_uu->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_uu->Fill(photonjet_costheta[1],photonjet_E[1]);
      
      h_y23_uu->Fill(d23/pow(reco_bbmass,2));
      h_d23_uu->Fill(d23);
      h_mj1_mj2_uu->Fill(reco_b1mass+reco_b2mass);
      h_thrust_uu->Fill(principle_thrust_value);
      h_K_uu->Fill(Kv);
      h_K_parton_uu->Fill(gamma_e);
      h_K_parton_K_uu->Fill(gamma_e,Kv);
      
      // 21/12/21:
      h_photon_likeness_uu->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_charge_likeness_uu->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_oblateness_uu->Fill(oblateness);
      h_aplanarity_uu->Fill(aplanarity);
      h_sphericity_uu->Fill(sphericity);
    }
    
    if(fabs(mc_quark_pdg[0])==3 && gamma_e<Kvcut) {
      h_costheta_ss->Fill(costheta_bbbar);
      h_mc_costheta_ss->Fill(mc_costheta_bbbar); 
      h_mc_com_costheta_ss->Fill(mc_com_costheta_bbbar); 
      
      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_ss->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_ss->Fill(photonjet_costheta[1],photonjet_E[1]);
      // -------------------------
      h_y23_ss->Fill(d23/pow(reco_bbmass,2));
      h_d23_ss->Fill(d23);
      h_mj1_mj2_ss->Fill(reco_b1mass+reco_b2mass);
      h_thrust_ss->Fill(principle_thrust_value);
      h_K_ss->Fill(Kv);
      h_K_parton_ss->Fill(gamma_e);
      h_K_parton_K_ss->Fill(gamma_e,Kv);
      
      // 21/12/21:
      h_photon_likeness_ss->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_charge_likeness_ss->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_oblateness_ss->Fill(oblateness);
      h_aplanarity_ss->Fill(aplanarity);
      h_sphericity_ss->Fill(sphericity);
    }
    // --End of addition for flavours

    if(fabs(mc_quark_pdg[0])<4 && gamma_e<Kvcut) {
   
      h_costheta_th_vs_lab_qq->Fill(costheta_bbbar-costheta_thrust);
      h_mc_costheta_qq->Fill(mc_costheta_bbbar);
      h_mc_com_costheta_qq->Fill(mc_com_costheta_bbbar);
      h_costheta_qq->Fill(costheta_bbbar);
      h_mjj_qq->Fill(reco_bbmass);

      //Addition by Jesus
      if(photonjet_E[0]>photonjet_E[1]) h_e_costheta_gamma_qq->Fill(photonjet_costheta[0],photonjet_E[0]);
      else h_e_costheta_gamma_qq->Fill(photonjet_costheta[1],photonjet_E[1]);
      //End of addition
      // 21/12/21:
      h_photon_likeness_qq->Fill(photonPFO_ratio[0],photonPFO_ratio[1]);
      h_charge_likeness_qq->Fill(chargePFO_ratio[0],chargePFO_ratio[1]);
      h_oblateness_qq->Fill(oblateness);
      h_aplanarity_qq->Fill(aplanarity);
      h_sphericity_qq->Fill(sphericity);

      
      h_photon_npfos_qq->Fill(npfo_photon[0],npfo_photon[1]);
      h_npfos_qq->Fill(npfo[0],npfo[1]);
      h_charge_npfos_qq->Fill(npfo_charge[0],npfo_charge[1]);
      
      // -------------------------
    
      h_y23_qq->Fill(d23/pow(reco_bbmass,2));
      h_d23_qq->Fill(d23);
      h_mj1_mj2_qq->Fill(reco_b1mass+reco_b2mass);
      h_thrust_qq->Fill(principle_thrust_value);
      h_K_qq->Fill(Kv);
      h_K_parton_qq->Fill(gamma_e);
      h_K_parton_K_qq->Fill(gamma_e,Kv);
    }
    }
  }
  cout<<TString::Format("selection_%s_500GeV.root",process.Data())<<endl;
  cout<<" Total generated events: bb cc qq bb(rad) cc(rad) qq(rad)" <<endl;
  cout<<"                     "<<bb_gen<<" "<<cc_gen<<" "<<qq_gen<<" "<<bb_radreturn_gen<<" "<<cc_radreturn_gen<<" "<<qq_radreturn_gen<<endl;
  cout<<" aftercuts  "<<bb_counter<<" "<<cc_counter<<" "<<qq_counter<<" "<<bb_radreturn_counter<<" "<<cc_radreturn_counter<<" "<<qq_radreturn_counter<<endl;

  //  cout<<" Total generated Z-radreturn events: " <<radreturn_counter<<endl;
  //cout<<" Total generated qqbar events: " << qq_counter<<endl;
  //cout<<" Total generated ccbar events: " << cc_counter<<endl;

  // save histograms
  h_costheta_nocuts->Write();

  montecarlo_b1mass->Write();
  montecarlo_b2mass->Write();

  montecarlo_b1_velocity->Write();
  montecarlo_b2_velocity->Write();

  v_cm_bb->Write();
      
  h_mjj_bb->Write();
  h_mjj_qq->Write();
  h_mjj_cc->Write();
  h_mjj_radreturn->Write();

  h_costheta_bb->Write();
  h_costheta_qq->Write();
  h_costheta_cc->Write();
  // Adition by Jesus
  h_costheta_dd->Write();
  h_costheta_uu->Write();
  h_costheta_ss->Write();
  // End of addition
  h_costheta_radreturn->Write();

  
  h_mc_costheta_bb->Write();
  h_mc_costheta_bb_isr->Write();
  h_mc_costheta_qq->Write();
  h_mc_costheta_cc->Write();
  h_mc_costheta_cc_isr->Write();
  h_mc_costheta_dd->Write();
  h_mc_costheta_uu->Write();
  h_mc_costheta_ss->Write();
  h_mc_costheta_radreturn->Write();

  
  h_mc_com_costheta_bb->Write();
  h_mc_com_costheta_bb_isr->Write();
  h_mc_com_costheta_qq->Write();
  h_mc_com_costheta_cc->Write();
  h_mc_com_costheta_cc_isr->Write();
  h_mc_com_costheta_dd->Write();
  h_mc_com_costheta_uu->Write();
  h_mc_com_costheta_ss->Write();
  h_mc_com_costheta_radreturn->Write();
  
  h_costheta_th_vs_lab_bb->Write();
  h_costheta_th_vs_lab_qq->Write();
  h_costheta_th_vs_lab_cc->Write();
  h_costheta_th_vs_lab_radreturn->Write();

  h_photon_npfos_bb->Write();
  h_photon_npfos_cc->Write();
  h_photon_npfos_qq->Write();
  h_photon_npfos_radreturn->Write();
  
  h_charge_npfos_bb->Write();
  h_charge_npfos_cc->Write();
  h_charge_npfos_qq->Write();
  h_charge_npfos_radreturn->Write();

  h_npfos_bb->Write();
  h_npfos_cc->Write();
  h_npfos_qq->Write();
  h_npfos_radreturn->Write();

  h_y23_bb->Write();
  h_y23_qq->Write();
  h_y23_cc->Write();
  h_y23_uu->Write();
  h_y23_dd->Write();
  h_y23_ss->Write();
  h_y23_radreturn->Write();

  h_d23_bb->Write();
  h_d23_qq->Write();
  h_d23_cc->Write();
  h_d23_uu->Write();
  h_d23_dd->Write();
  h_d23_ss->Write();
  h_d23_radreturn->Write();

  //Addition by Jesus
  h_e_costheta_gamma_ss->Write();
  h_e_costheta_gamma_uu->Write();
  h_e_costheta_gamma_dd->Write();
  h_e_costheta_gamma_bb->Write();
  h_e_costheta_gamma_qq->Write();
  h_e_costheta_gamma_cc->Write();
  h_e_costheta_gamma_radreturn->Write();
  //End of addition
  
  h_thrust_bb->Write();
  h_thrust_qq->Write();
  h_thrust_cc->Write();
  h_thrust_uu->Write();
  h_thrust_dd->Write();
  h_thrust_ss->Write();
  h_thrust_radreturn->Write();

  h_mj1_mj2_bb->Write();
  h_mj1_mj2_qq->Write();
  h_mj1_mj2_cc->Write();
  h_mj1_mj2_uu->Write();
  h_mj1_mj2_dd->Write();
  h_mj1_mj2_ss->Write();
  h_mj1_mj2_radreturn->Write();

  h_K->Write();
  h_K_bb->Write();
  h_K_qq->Write();
  h_K_cc->Write();
  h_K_uu->Write();
  h_K_dd->Write();
  h_K_ss->Write();
  h_K_radreturn->Write();
  
  h_K_parton_bb->Write();
  h_K_parton_qq->Write();
  h_K_parton_cc->Write();
  h_K_parton_uu->Write();
  h_K_parton_dd->Write();
  h_K_parton_ss->Write();
  h_K_parton_radreturn->Write();

  h_K_parton_K_bb->Write();
  h_K_parton_K_qq->Write();
  h_K_parton_K_cc->Write();
  h_K_parton_K_uu->Write();
  h_K_parton_K_dd->Write();
  h_K_parton_K_ss->Write();
  h_K_parton_K_radreturn->Write();

  // Addition 22/12/21
  
      h_photon_likeness_qq->Write();
      h_photon_likeness_uu->Write();
      h_photon_likeness_dd->Write();
      h_photon_likeness_ss->Write();
      h_photon_likeness_bb->Write();
      h_photon_likeness_cc->Write();
      h_photon_likeness_radreturn->Write();
      
      h_charge_likeness_qq->Write();
      h_charge_likeness_uu->Write();
      h_charge_likeness_dd->Write();
      h_charge_likeness_ss->Write();
      h_charge_likeness_bb->Write();
      h_charge_likeness_cc->Write();
      h_charge_likeness_radreturn->Write();
      
      h_oblateness_qq->Write();
      h_oblateness_uu->Write();
      h_oblateness_dd->Write();
      h_oblateness_ss->Write();
      h_oblateness_bb->Write();
      h_oblateness_cc->Write();
      h_oblateness_radreturn->Write();
      
      h_aplanarity_qq->Write();
      h_aplanarity_uu->Write();
      h_aplanarity_dd->Write();
      h_aplanarity_ss->Write();
      h_aplanarity_bb->Write();
      h_aplanarity_cc->Write();
      h_aplanarity_radreturn->Write();
      
      h_sphericity_qq->Write();
      h_sphericity_uu->Write();
      h_sphericity_dd->Write();
      h_sphericity_ss->Write();
      h_sphericity_bb->Write();
      h_sphericity_cc->Write();
      h_sphericity_radreturn->Write();

  // End of addition 22/12/21   
}



