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
#include "TMultiGraph.h"

const int nDigi = 1024;
std::vector<double> * time1 = 0;
std::vector<double> * amp1 = 0;
std::vector<double> * time2 = 0;
std::vector<double> * amp2 = 0;

int findMaxLoc()
{
	float maxAmp = -9999.9;
	int maxLoc = 0;
	for(int i=0; i< amp1->size(); i++)
	{
		if(i>=nDigi) break;
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
	for(int i=0; i< amp1->size(); i++)
	{
		if(i>=nDigi) break;
		if(time1->at(i) > time) break;
		integral += amp1->at(i)	* bin_size1;
	}
	}

	else
	{
	for(int i=0; i< amp2->size(); i++)
	{
		if(i>=nDigi) break;
		if(time2->at(i) > time) break;
		integral += amp2->at(i)	* bin_size2;
	}
	}
}

void rereco(std::string inFileName)
{
	
	//std::filesystem::copy(("/eos/user/z/zhicaiz/TestBeam/geant4/ntuples/"+inFileName+".root").c_str(),("/eos/user/z/zhicaiz/TestBeam/geant4/ntuples/"+inFileName+"_rereco.root").c_str());

	
	TFile *f_old = new TFile(("/eos/user/z/zhicaiz/TestBeam/geant4/ntuples/"+inFileName+".root").c_str(), "READ");
        TTree *tree_old = (TTree*)f_old->Get("tree");
	
	TFile *f_new = new TFile(("/eos/user/z/zhicaiz/TestBeam/geant4/ntuples/"+inFileName+"_rereco.root").c_str(), "RECREATE");
	TTree *tree_new = tree_old->CloneTree();
	tree_new->Write();
	f_old->Close();
	f_new->Close();
		
	delete f_old;
	delete f_new;
	
	

	TFile *f_add = new TFile(("/eos/user/z/zhicaiz/TestBeam/geant4/ntuples/"+inFileName+"_rereco.root").c_str(), "update");
	TTree *tree_add = (TTree*)f_add->Get("tree");	
	
	float int_0p01;
	float int_0p1;
	float int_1;
	float int_2;
	float int_peak;
	float int_full;
	float risetime;	
	float amp;	

	TBranch *b_int_0p01 = tree_add->Branch("int_0p01",&int_0p01,"int_0p01/F");
	TBranch *b_int_0p1 = tree_add->Branch("int_0p1",&int_0p1,"int_0p1/F");
	TBranch *b_int_1 = tree_add->Branch("int_1",&int_1,"int_1/F");
	TBranch *b_int_2 = tree_add->Branch("int_2",&int_2,"int_2/F");
	TBranch *b_int_peak = tree_add->Branch("int_peak",&int_peak,"int_peak/F");
	TBranch *b_int_full = tree_add->Branch("int_full",&int_full,"int_full/F");
	TBranch *b_risetime = tree_add->Branch("risetime",&risetime,"risetime/F");
	TBranch *b_amp = tree_add->Branch("amp",&amp,"amp/F");
	
	
	tree_add->SetBranchAddress("time1", &time1);
        tree_add->SetBranchAddress("amp1", &amp1);
	tree_add->SetBranchAddress("time2", &time2);
        tree_add->SetBranchAddress("amp2", &amp2);
		

	int NEntries = tree_add->GetEntries();
	for(int i=1; i<=NEntries; i++)
	{
		tree_add->GetEntry(i);
		int maxLoc = findMaxLoc();
		amp = amp1->at(maxLoc);
		int_peak = getIntegral(time1->at(maxLoc));
		int_full = getIntegral(100.0);
		int_0p01 = getIntegral(100.0);
		int_0p1 = getIntegral(100.0);
		int_0p1 = getIntegral(100.0);
		int_0p1 = getIntegral(100.0);


		int_0p01 = 0.01;
		int_0p1 = 0.1;
		int_1 = 1.0;
		int_2 = 2.0;
		risetime = 10.0;
	
		b_int_0p01->Fill();
		b_int_0p1->Fill();
		b_int_1->Fill();
		b_int_2->Fill();
		b_int_peak->Fill();
		b_int_full->Fill();
		b_risetime->Fill();
		b_amp->Fill();
	}	
	
	tree_add->Write();
	delete f_add;
	
}
