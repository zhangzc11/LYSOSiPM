#include <sstream>
#include <string>
#include <sys/stat.h>
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TF1.h"
#include "TPad.h"
#include "TProfile.h"
#include "TColor.h"
#include "TText.h"
#include "TLatex.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TString.h"

const int nDigi = 1024;
std::vector<double> * time1 = 0;
std::vector<double> * amp1 = 0;
std::vector<double> * time2 = 0;
std::vector<double> * amp2 = 0;
std::vector<double> * allPhoTime_sptr = 0;

int firstPhoAboveZero = 0;

int findMaxLoc()
{
	float maxAmp = -9999.9;
	int maxLoc = 0;
	for(int i=0; i< amp1->size(); i++)
	{
		if(i>nDigi) break;
		if(amp1->at(i) > maxAmp)
		{
			maxAmp = amp1->at(i);
			maxLoc = i;
		}	
	}
		
	return maxLoc;

}

float getIntegral(float time)
{
	float integral = 0.0;	
	float bin_size1 = time1->at(1) - time1->at(0);
	float bin_size2 = time2->at(1) - time2->at(0);

	if(time > time2->at(time2->size()-1))
	{
	integral = firstPhoAboveZero;
	for(int i=1; i< amp1->size(); i++)
	{
		if(i>nDigi) break;
		if(time1->at(i) > time) break;
		integral += amp1->at(i)	* bin_size1;
	}
	}

	else
	{
	integral = firstPhoAboveZero;
	for(int i=1; i< amp2->size(); i++)
	{
		if(i>nDigi) break;
		if(time2->at(i) > time) break;
		integral += amp2->at(i)	* bin_size2;
	}
	}
	
	return integral;
}

float RisingEdgeFitPoly2(TGraphErrors * pulse, const int index_max, float fraction) {
	double x_low, x_high, x_peak, y, x_frac = 0.0;
	int x_frac_ind=0;
  	double ymax;
  	pulse->GetPoint(index_max, x_peak, ymax);
		
	for ( int i = 1; i < 600; i++ )
    	{
      		pulse->GetPoint(index_max-i, x_low, y);
      		if ( y < fraction*ymax ) 
		{	
			x_frac_ind = index_max - i;
			x_frac = x_low;
			break;
		}
    	}
		
	
	if(x_frac_ind < 7) pulse->GetPoint(0, x_low, y);
	else pulse->GetPoint(x_frac_ind-7, x_low, y);
	pulse->GetPoint(x_frac_ind+7, x_high, y);
	
	TF1* fpoly2 = new TF1("fpoly2","[0]+[1]*x+[2]*x*x", x_low, x_high );	
	pulse->Fit("fpoly2","Q","", x_low, x_high );	
	double a = fpoly2->GetParameter(2);
	double b = fpoly2->GetParameter(1);
	double c = fpoly2->GetParameter(0);
	
	//solve equation: fraction*ymax=y0 = a*x^2 + b*x + c
	if(b*b >= 4*a*(c-fraction*ymax))
	{
		double x1 = (sqrt(b*b-4*a*(c-fraction*ymax))+b)/(2.0*a);
		double x2 = (sqrt(b*b-4*a*(c-fraction*ymax))-b)/(2.0*a);
		if(x1>x_low && x1<x_high) return x1;
		if(x2>x_low && x2<x_high) return x2;
		else return x_frac;
	}
	else return x_frac;
	
}

void RisingEdgeFitTime(TGraphErrors * pulse, const int index_max, const float fitLowEdge, const float fitHighEdge, float* tstamp, bool savePlot = false, TString plotName = "example") {
  double x_low, x_high, x_peak, y;
  double ymax;
  TCanvas *myC = new TCanvas( "myC", "myC", 200, 10, 800, 600 );


  pulse->GetPoint(index_max, x_peak, ymax);

  for ( int i = 1; i < 600; i++ )
    {
      //pulse->GetPoint(index_max-i, x_low, y);
      pulse->GetPoint(i, x_low, y);
      if ( y > fitLowEdge*ymax ) break;
    }
  for ( int i = 1; i < 600; i++ )
    {
      //pulse->GetPoint(index_max-i, x_high, y);
      pulse->GetPoint(i, x_high, y);
      if ( y > fitHighEdge*ymax ) break;
    }

  pulse->GetXaxis()->SetRangeUser(-1.0, 5.0); 

  pulse->Draw("AP");
  TF1* flinear = new TF1("flinear","[0]*x+[1]", x_low, x_high );
  float max = -9999;
  double* yy = pulse->GetY();

  for ( int i = 0; i < 1024; i++ )
    {
      if ( yy[i] > max ) max = yy[i];
    }

 pulse->Fit("flinear","Q","", x_low, x_high );
 //if(savePlot) myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/fits/"+plotName+".png");
 if(savePlot) myC->SaveAs("/eos/user/z/zhicaiz/www/sharebox/TestBeam/geant4/forDN/fits/"+plotName+".png");
  double slope = flinear->GetParameter(0);
  double b     = flinear->GetParameter(1);

tstamp[0] = (0.10*ymax-b)/slope;
  tstamp[1] = (0.60*ymax-b)/slope;
  tstamp[2] = (0.70*ymax-b)/slope;
  tstamp[3] = (0.80*ymax-b)/slope;
  tstamp[4] = (0.90*ymax-b)/slope;

  delete flinear;
  delete myC;
};


void rereco(TString inFileName)
{
	

	//TString inFileName = "ntuple_ref_center";	
	//TFile *f_old = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/"+inFileName+".root", "READ");
	TFile *f_old = new TFile("/eos/cms/store/user/zhicaiz/geant4/ntuples/"+inFileName+".root", "READ");
	TTree *tree_old = (TTree*)f_old->Get("tree");
	
	//TFile *f_new = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/"+inFileName+"_rereco.root", "RECREATE");
	TFile *f_new = new TFile("/eos/cms/store/user/zhicaiz/geant4/ntuples/"+inFileName+"_rereco.root", "RECREATE");
	TTree *tree_new = tree_old->CloneTree();
	tree_new->Write();
	f_old->Close();
	f_new->Close();
		
	delete f_old;
	delete f_new;
	

	//TFile *f_add = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/"+inFileName+"_rereco.root", "update");
	TFile *f_add = new TFile("/eos/cms/store/user/zhicaiz/geant4/ntuples/"+inFileName+"_rereco.root", "update");
	TTree *tree_add = (TTree*)f_add->Get("tree");	
	
	float int_firstbin;
	float int_0p01;
	float int_0p1;
	float int_1;
	float int_2;
	float int_peak;
	float int_full;
	float risetime;	
	float amp;	
	float peak_time;
	float photon100_time;
	float photon10_time;
	float photon5_time;
	float frac_10;
	float frac_60;
	float frac_70;
	float frac_80;
	float frac_90;

	TBranch *b_int_firstbin = tree_add->Branch("int_firstbin",&int_firstbin,"int_firstbin/F");
	TBranch *b_int_0p01 = tree_add->Branch("int_0p01",&int_0p01,"int_0p01/F");
	TBranch *b_int_0p1 = tree_add->Branch("int_0p1",&int_0p1,"int_0p1/F");
	TBranch *b_int_1 = tree_add->Branch("int_1",&int_1,"int_1/F");
	TBranch *b_int_2 = tree_add->Branch("int_2",&int_2,"int_2/F");
	TBranch *b_int_peak = tree_add->Branch("int_peak",&int_peak,"int_peak/F");
	TBranch *b_int_full = tree_add->Branch("int_full",&int_full,"int_full/F");
	TBranch *b_risetime = tree_add->Branch("risetime",&risetime,"risetime/F");
	TBranch *b_amp = tree_add->Branch("amp",&amp,"amp/F");
	TBranch *b_peak_time = tree_add->Branch("peak_time",&peak_time,"peak_time/F");
	TBranch *b_photon100_time = tree_add->Branch("photon100_time",&photon100_time,"photon100_time/F");
	TBranch *b_photon10_time = tree_add->Branch("photon10_time",&photon10_time,"photon10_time/F");
	TBranch *b_photon5_time = tree_add->Branch("photon5_time",&photon5_time,"photon5_time/F");
	TBranch *b_frac_10 = tree_add->Branch("frac_10",&frac_10,"frac_10/F");
	TBranch *b_frac_60 = tree_add->Branch("frac_60",&frac_60,"frac_60/F");
	TBranch *b_frac_70 = tree_add->Branch("frac_70",&frac_70,"frac_70/F");
	TBranch *b_frac_80 = tree_add->Branch("frac_80",&frac_80,"frac_80/F");
	TBranch *b_frac_90 = tree_add->Branch("frac_90",&frac_90,"frac_90/F");
	
	
	tree_add->SetBranchAddress("time1", &time1);
	tree_add->SetBranchAddress("amp1_sptr", &amp1);
	tree_add->SetBranchAddress("time2", &time2);
	tree_add->SetBranchAddress("amp2_sptr", &amp2);
	tree_add->SetBranchAddress("allPhoTime_sptr", &allPhoTime_sptr);
		
	f_add->cd();

	int NEntries = tree_add->GetEntries();
	for(int ientry=1; ientry<=NEntries; ientry++)
	{
		tree_add->GetEntry(ientry);
	
		firstPhoAboveZero = 0;
		for(int i=0;i<allPhoTime_sptr->size();i++)
		{
			firstPhoAboveZero = i;
			if(allPhoTime_sptr->at(i)>0.0) break;
		}	

		int maxLoc = findMaxLoc();

		amp = amp1->at(maxLoc);
		peak_time = time1->at(maxLoc);
		int_peak = getIntegral(time1->at(maxLoc));
		int_full = getIntegral(100.0);
		int_0p01 = getIntegral(0.01);
		int_0p1 = getIntegral(0.1);
		int_1 = getIntegral(1.0);
		int_2 = getIntegral(2.0);

		float bin_size1 = time1->at(1) - time1->at(0);

		float time_reco[nDigi];
		float etime_reco[nDigi];
		float amp_reco[nDigi];
		float eamp_reco[nDigi];
		for(int i=0; i< amp1->size();i++)
		{
			if(i>nDigi) break;
			time_reco[i] = time1->at(i);
			amp_reco[i] = amp1->at(i);
			etime_reco[i] = 0.0;
			eamp_reco[i] = 0.0;
			if(amp_reco[i] > 0.0) eamp_reco[i] = amp_reco[i] / sqrt(bin_size1 * amp_reco[i]);
			
		}
		TGraphErrors* pulse = new TGraphErrors( nDigi, time_reco, amp_reco, etime_reco, eamp_reco);
		
		
		float fs[5];
		float cft_low_range  = 0.10;
		float cft_high_range = 0.70;
		TString plotName;
		plotName.Form("fit_%d",ientry);
		if(ientry < 10) RisingEdgeFitTime( pulse, maxLoc, cft_low_range, cft_high_range, fs, true,inFileName+"_"+plotName);
		else RisingEdgeFitTime( pulse, maxLoc, cft_low_range, cft_high_range, fs, false);
		frac_10 = fs[0];
		frac_60 = fs[1];
		frac_70 = fs[2];
		frac_80 = fs[3];
		frac_90 = fs[4];
		

		//risetime = RisingEdgeFitPoly2( pulse, maxLoc, 0.9) - RisingEdgeFitPoly2( pulse, maxLoc, 0.1);
		photon100_time = allPhoTime_sptr->at(100);
		photon10_time = allPhoTime_sptr->at(10);
		photon5_time = allPhoTime_sptr->at(5);
		cout<<"entry "<<ientry<<" peak_time "<<peak_time<<endl;			
		cout<<"entry "<<ientry<<" photon100_time "<<photon100_time<<endl;			
		cout<<"entry "<<ientry<<" photon10_time "<<photon10_time<<endl;			
		cout<<"entry "<<ientry<<" photon5_time "<<photon5_time<<endl;			
		
		
		int_firstbin = firstPhoAboveZero;
	
		risetime = frac_90 - frac_10;
	
		b_int_firstbin->Fill();
		b_int_0p01->Fill();
		b_int_0p1->Fill();
		b_int_1->Fill();
		b_int_2->Fill();
		b_int_peak->Fill();
		b_int_full->Fill();
		b_risetime->Fill();
		b_amp->Fill();
		b_peak_time->Fill();
		b_photon100_time->Fill();
		b_photon10_time->Fill();
		b_photon5_time->Fill();
		b_frac_80->Fill();
		b_frac_70->Fill();
		b_frac_10->Fill();
		b_frac_60->Fill();
		b_frac_90->Fill();
	}	
	
	tree_add->Write();
	delete f_add;
	
}
