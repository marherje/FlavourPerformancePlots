#include "variables_dedx.h"

//Optimized cuts by Jesus
//----------------------------------------------------------  

//  bbmass:  
double bbmasscut=140;
// n charged_npfos:
double CNPFOS_cut=0.5;
//  npfos:  
double NPFOS_cut=1.5;
// LOS LIMITES DEL CORTE en h_e_costheta_gamma:cuts in energy and angle of detected photons
double costheta_isr=0.97;
double energy_isr_cut=110;
// cuts in y23
//double d23cut=3500;

/* // cuts in y23 */
double y23cut=0.015; 
// cuts in mj1_mj2
double mj1_mj2_cut=100;
// ----------------------------------


//flavour tagging
float btag1=0.7; //0.625 ai
float btag2=0.7;
//0.625 aiming for 10% b for Good BDT Testing


float ctag1=0.7; //
float ctag2=0.7;
//0.75 aiming for 10% c for Good BDT Testing

//K-reco
float Kreco() {


  // KRECO CALCULATION
  TVector3 v1(jet_px[0],jet_py[0],jet_pz[0]);
  TVector3 v2(jet_px[1],jet_py[1],jet_pz[1]);
  float acol=GetSinacol(v1,v2);
   
  float costheta_j0;
  std::vector<float> p_j0;
  p_j0.push_back(jet_px[0]);
  p_j0.push_back(jet_py[0]);
  p_j0.push_back(jet_pz[0]);
  costheta_j0=fabs(GetCostheta(p_j0));

  float costheta_j1;
  std::vector<float> p_j1;
  p_j1.push_back(jet_px[1]);
  p_j1.push_back(jet_py[1]);
  p_j1.push_back(jet_pz[1]);
  costheta_j1=fabs(GetCostheta(p_j1));
  
  float Kv=500.*acol/(acol+sqrt(1-costheta_j0*costheta_j0)+sqrt(1-costheta_j1*costheta_j1));
  return Kv;

}
// calculation of photon related quantities
double npfo[2]={-1}; // ponía -1
double npfo_photon[2]={-1}; // ponía -1
double npfo_charge[2]={-1}; // ponía -1
double photonjet_E[2]={0};
double photonjet_costheta[2]={-2};

void PFOphotonQuantities() {

  for(int i_=0; i_<2; i_++) {
    npfo[i_]=-1;
    npfo_photon[i_]=-1;
    npfo_charge[i_]=-1;
    photonjet_E[i_]=0;
    photonjet_costheta[i_]=-2;
  }

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
    if(pfo_match[ipfo]>1) continue;

    npfo[pfo_match[ipfo]]++;

    if( pfo_charge[ipfo] != 0  )npfo_charge[pfo_match[ipfo]]++;

    //pfo identified as photon or neutron
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
  photonjet_costheta[0]=GetCostheta(p_pfo_0);
  //Added:
  //float costheta_pfo_0=GetCostheta(p_pfo_0);
  //costheta_jet_0=costheta_pfo_0;
  //----------

  p_pfo_1.push_back(px_1);
  p_pfo_1.push_back(py_1);
  p_pfo_1.push_back(pz_1);
  photonjet_costheta[1]=GetCostheta(p_pfo_1);
  //Added:
  //float costheta_pfo_1=GetCostheta(p_pfo_1);
  //costheta_jet_1=costheta_pfo_1;
  //----------
  
}


bool PreSelection(int type=0,float Kvcut=35) {
  
  if(jet_E[0]<0.5 || jet_E[1]<0.5) return false;

  if(type == 0 ) return true;

    double reco_b1mass= sqrt(pow(jet_E[0],2)-pow(jet_px[0],2)-pow(jet_py[0],2)-pow(jet_pz[0],2));
    double reco_b2mass= sqrt(pow(jet_E[1],2)-pow(jet_px[1],2)-pow(jet_py[1],2)-pow(jet_pz[1],2));
    
  double bbmass= sqrt(pow(jet_E[0]+jet_E[1],2)-pow(jet_px[0]+jet_px[1],2)-pow(jet_py[0]+jet_py[1],2)-pow(jet_pz[0]+jet_pz[1],2));

  // KRECO CALCULATION
   float Kv=Kreco();

  //----------------------------------------------------------
  // IDENTIFICATION OF PFO's associated to photons, charged pfos, neutral pgos
  //Radiative return cuts, photon INSIDE the detector //NUEVO ADRIAN 2021 04 21
  //---------------------
   PFOphotonQuantities();
      
  //----------------------------------------------------------
   bool cut_[10]={false};
   cut_[1]=( Kv < Kvcut );
   cut_[2]=(cut_[1] && bbmass>bbmasscut ) ;
   cut_[3]=(cut_[2] && npfo_charge[0]>CNPFOS_cut && npfo_charge[1]>CNPFOS_cut);
   cut_[4]=(cut_[3] && npfo[0]>NPFOS_cut && npfo[1]>NPFOS_cut);

   if(type<5) {
     return cut_[type];
   } else {
     
     float photonjet_e_max=0;
     float photonjet_cos_max=-2;
     if(photonjet_E[0]>photonjet_E[1]) {
       photonjet_e_max=photonjet_E[0];
       photonjet_cos_max=photonjet_costheta[0];
     } else {
       photonjet_e_max=photonjet_E[1];
       photonjet_cos_max=photonjet_costheta[1];
     }
     cut_[5]=(cut_[4] && fabs(photonjet_cos_max)<costheta_isr && photonjet_e_max<energy_isr_cut ) ;
     cut_[6]=(cut_[5] && d23>0.5 && d23/pow(bbmass,2)<y23cut);
     cut_[7]=(cut_[6] && reco_b1mass+reco_b2mass < mj1_mj2_cut );
     
     cut_[8]=(cut_[7] && jet_btag[0]>btag1 && jet_btag[1]>btag2); 
     cut_[9]=(cut_[7] && jet_ctag[0]>ctag1 && jet_ctag[1]>ctag2);
     return cut_[type];
   }
       
  return false;
}
