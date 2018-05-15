
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

float nPhotons_x0 = 1.0;
float nPhotons_x5 = 1.0;

float axisTitleSizeX = 0.06;
float axisTitleSizeY = 0.05;
float axisTitleOffsetX = 0.9;
float axisTitleOffsetY = 1.2;

float axisTitleSizeRatioX   = 0.18;
float axisLabelSizeRatioX   = 0.12;
float axisTitleOffsetRatioX = 0.94;
float axisTitleSizeRatioY   = 0.15;
float axisLabelSizeRatioY   = 0.108;
float axisTitleOffsetRatioY = 0.32;

float leftMargin   = 0.12;
float rightMargin  = 0.14;
float topMargin    = 0.07;
float bottomMargin = 0.12;

void drawTracks(TTree * tree, std::string& inFileName, std::string& plotDir)
{
        TCanvas *myC = new TCanvas( "myC", "myC", 200, 10, 800, 600 );
        myC->SetHighLightColor(2);
        myC->SetFillColor(0);
        myC->SetBorderMode(0);
        myC->SetBorderSize(2);
        myC->SetLeftMargin( leftMargin );
        myC->SetRightMargin( rightMargin );
        myC->SetTopMargin( topMargin );
        myC->SetBottomMargin( bottomMargin );
        myC->SetFrameBorderMode(0);
        myC->SetFrameBorderMode(0);


	TH2F * h2_allPhoTrackVertexR_vs_phoIndex = new TH2F("h2_allPhoTrackVertexR_vs_phoIndex","h2_allPhoTrackVertexR_vs_phoIndex", 200, 0, 200, 200, 0.0, 10.0);
	tree->Draw("allPhoTrackVertexR_sptr:allPhoIndex_sptr>>h2_allPhoTrackVertexR_vs_phoIndex");
	h2_allPhoTrackVertexR_vs_phoIndex->SetTitle("");
	h2_allPhoTrackVertexR_vs_phoIndex->GetXaxis()->SetTitle("photon index");
    	h2_allPhoTrackVertexR_vs_phoIndex->GetYaxis()->SetTitle("vertex distance to SiPM [mm]");
	h2_allPhoTrackVertexR_vs_phoIndex->GetXaxis()->SetTitleSize( axisTitleSizeX );
    	h2_allPhoTrackVertexR_vs_phoIndex->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
    	h2_allPhoTrackVertexR_vs_phoIndex->GetYaxis()->SetTitleSize( axisTitleSizeY );
    	h2_allPhoTrackVertexR_vs_phoIndex->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_allPhoTrackVertexR_vs_phoIndex->SetMarkerStyle(6);
	h2_allPhoTrackVertexR_vs_phoIndex->SetMarkerColor(kRed);
	myC->SaveAs((plotDir+inFileName+"_tracks_allPhoTrackVertexR_vs_phoIndex.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_tracks_allPhoTrackVertexR_vs_phoIndex.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_tracks_allPhoTrackVertexR_vs_phoIndex.C").c_str());

	delete h2_allPhoTrackVertexR_vs_phoIndex;

	TH2F * h2_allPhoTrackLength_vs_phoIndex = new TH2F("h2_allPhoTrackLength_vs_phoIndex","h2_allPhoTrackLength_vs_phoIndex", 200, 0, 200, 100, 0, 50.0);
	tree->Draw("allPhoTrackLength_sptr:allPhoIndex_sptr>>h2_allPhoTrackLength_vs_phoIndex");
	h2_allPhoTrackLength_vs_phoIndex->SetTitle("");
	h2_allPhoTrackLength_vs_phoIndex->GetXaxis()->SetTitle("photon index");
    	h2_allPhoTrackLength_vs_phoIndex->GetYaxis()->SetTitle("photon track length [mm]");
	h2_allPhoTrackLength_vs_phoIndex->GetXaxis()->SetTitleSize( axisTitleSizeX );
    	h2_allPhoTrackLength_vs_phoIndex->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
    	h2_allPhoTrackLength_vs_phoIndex->GetYaxis()->SetTitleSize( axisTitleSizeY );
    	h2_allPhoTrackLength_vs_phoIndex->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_allPhoTrackLength_vs_phoIndex->SetMarkerStyle(6);
	h2_allPhoTrackLength_vs_phoIndex->SetMarkerColor(kRed);
	myC->SaveAs((plotDir+inFileName+"_tracks_allPhoTrackLength_vs_phoIndex.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_tracks_allPhoTrackLength_vs_phoIndex.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_tracks_allPhoTrackLength_vs_phoIndex.C").c_str());
	
	delete h2_allPhoTrackLength_vs_phoIndex;

	TH2F * h2_allPhoTime_vs_phoIndex = new TH2F("h2_allPhoTime_vs_phoIndex","h2_allPhoTime_vs_phoIndex", 200, 0, 200, 100, 0, 0.4);
	tree->Draw("allPhoTime_sptr:allPhoIndex_sptr>>h2_allPhoTime_vs_phoIndex");
	h2_allPhoTime_vs_phoIndex->SetTitle("");
	h2_allPhoTime_vs_phoIndex->GetXaxis()->SetTitle("photon index");
    	h2_allPhoTime_vs_phoIndex->GetYaxis()->SetTitle("photon time [ns]");
	h2_allPhoTime_vs_phoIndex->GetXaxis()->SetTitleSize( axisTitleSizeX );
    	h2_allPhoTime_vs_phoIndex->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
    	h2_allPhoTime_vs_phoIndex->GetYaxis()->SetTitleSize( axisTitleSizeY );
    	h2_allPhoTime_vs_phoIndex->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_allPhoTime_vs_phoIndex->SetMarkerStyle(6);
	h2_allPhoTime_vs_phoIndex->SetMarkerColor(kRed);
	myC->SaveAs((plotDir+inFileName+"_tracks_allPhoTime_vs_phoIndex.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_tracks_allPhoTime_vs_phoIndex.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_tracks_allPhoTime_vs_phoIndex.C").c_str());
	
	delete h2_allPhoTime_vs_phoIndex;
		
	delete myC; 

}


void drawT100(TTree * tree0, TTree * tree5, std::string& inFileName, std::string& plotDir)
{
        TCanvas *myC = new TCanvas( "myC", "myC", 200, 10, 800, 600 );
        myC->SetHighLightColor(2);
        myC->SetFillColor(0);
        myC->SetBorderMode(0);
        myC->SetBorderSize(2);
        myC->SetLeftMargin( leftMargin );
        myC->SetRightMargin( rightMargin );
        myC->SetTopMargin( topMargin );
        myC->SetBottomMargin( bottomMargin );
        myC->SetFrameBorderMode(0);
        myC->SetFrameBorderMode(0);

	
	myC->SetGridx(1);
	
	TH1F * h100_x0 = new TH1F("h100_x0","h100_x0",100,0,0.5);
	TH1F * h100_x5 = new TH1F("h100_x5","h100_x5",100,0,0.5);
        tree0->Draw("allPhoTime_sptr>>h100_x0","allPhoIndex==100");
        tree5->Draw("allPhoTime_sptr>>h100_x5","allPhoIndex==100");

        h100_x0->SetTitle("");
        h100_x0->GetXaxis()->SetTitle("t_{100} [ns]");
    	h100_x0->GetYaxis()->SetTitle("Events");
        h100_x0->GetXaxis()->SetTitleSize( axisTitleSizeX );
    	h100_x0->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
    	h100_x0->GetYaxis()->SetTitleSize( axisTitleSizeY );
    	h100_x0->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
        h100_x0->SetLineWidth(4);
        h100_x0->SetLineColor(kRed);
	h100_x0->Draw("hist");
	myC->SaveAs((plotDir+inFileName+"_time_photon100_x0.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_x0.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_x0.C").c_str());

	h100_x5->SetTitle("");
        h100_x5->GetXaxis()->SetTitle("t_{100} [ns]");
    	h100_x5->GetYaxis()->SetTitle("Events");
        h100_x5->GetXaxis()->SetTitleSize( axisTitleSizeX );
    	h100_x5->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
    	h100_x5->GetYaxis()->SetTitleSize( axisTitleSizeY );
    	h100_x5->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
        h100_x5->SetLineWidth(4);
        h100_x5->SetLineColor(kBlue);
	h100_x5->Draw("hist");
	myC->SaveAs((plotDir+inFileName+"_time_photon100_x5.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_x5.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_x5.C").c_str());

	h100_x0->Scale(1.0/h100_x0->Integral());
	h100_x5->Scale(1.0/h100_x5->Integral());

	float maxY = 1.5*std::max(h100_x0->GetMaximum(), h100_x5->GetMaximum());
	h100_x0->GetYaxis()->SetRangeUser(0.0, maxY);

	h100_x0->Draw("hist");
	h100_x5->Draw("histsame");

	TLegend * leg  = new TLegend (0.45,0.77,0.80,0.92);
        leg->SetBorderSize(0);
        leg->SetTextSize(0.06);
        leg->SetLineColor(1);
        leg->SetLineStyle(1);
        leg->SetLineWidth(1);
        leg->SetFillColor(0);
        leg->SetFillStyle(1001);

        leg->AddEntry(h100_x0, "center (x = 0mm)", "l");
        leg->AddEntry(h100_x5, "edge (x = 5mm)", "l");
        leg->Draw();		
	
	int deltaT = int(1000.0*(h100_x5->GetBinCenter(h100_x5->GetMaximumBin()) - h100_x0->GetBinCenter(h100_x0->GetMaximumBin())));

	       	
	TLatex *tlatex =  new TLatex();
        tlatex->SetNDC();
        tlatex->SetTextAngle(0);
        tlatex->SetTextColor(kBlack);
        tlatex->SetTextFont(63);
        tlatex->SetTextAlign(11);
        tlatex->SetTextSize(45);
       	tlatex->DrawLatex(0.51, 0.70, ("#Delta T = "+std::to_string(deltaT) +" ps").c_str());
	
		
	myC->SaveAs((plotDir+inFileName+"_time_photon100_x05.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_x05.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_x05.C").c_str());

	delete myC;
	delete h100_x0;
	delete h100_x5;
	delete leg;
	delete tlatex;

}

void draw_average_pulse(TTree * tree0, TTree * tree5, std::string& inFileName, std::string& plotDir, std::string timetag)
{
	const int nDigi = 1024;

	std::vector<double> * time1 = 0;
        std::vector<double> * amp1 = 0;
        Int_t nPhotons;
	
	tree0->SetBranchAddress("nPhotons", &nPhotons);
        tree0->SetBranchAddress(("time"+timetag).c_str(), &time1);
        tree0->SetBranchAddress(("amp"+timetag+"_sptr").c_str(), &amp1);	
	
	tree5->SetBranchAddress("nPhotons", &nPhotons);
        tree5->SetBranchAddress(("time"+timetag).c_str(), &time1);
        tree5->SetBranchAddress(("amp"+timetag+"_sptr").c_str(), &amp1);

	int NEntries0 = tree0->GetEntries();
	int NEntries5 = tree5->GetEntries();
	
	tree0->GetEntry(1);

        double average_amp0[nDigi];
        double average_amp5[nDigi];
        double ex[nDigi];
        double average_time0[nDigi];
        double average_time5[nDigi];
        double ey[nDigi];

	for(int i=0;i<nDigi;i++)
        {
                average_amp0[i] = 0.0;
                average_amp5[i] = 0.0;
                average_time0[i] = 0.0;
                average_time5[i] = 0.0;
                ex[i] = 0.0;
                ey[i] = 0.0;
        }	
	
	for(int i=1;i<=NEntries0;i++)
        {
                tree0->GetEntry(i);
                for(int j=0;j < amp1->size();j++)
                {
                        if(j>=nDigi) break;
                        else average_amp0[j] += amp1->at(j) * nPhotons_x0 / nPhotons;
                }
        }
        for(int i=1;i<=NEntries5;i++)
        {
                tree5->GetEntry(i);
                for(int j=0;j < amp1->size();j++)
                {
                        if(j>=nDigi) break;
                        else average_amp5[j] += amp1->at(j) * nPhotons_x5 / nPhotons;
                }
        }	

	for(int i=0;i<nDigi;i++)
        {
                if(i<amp1->size())
                {
                        average_amp0[i] = average_amp0[i]/NEntries0;
                        average_amp5[i] = average_amp5[i]/NEntries5;
                        average_time0[i] = time1->at(i);
                        average_time5[i] = time1->at(i);
                }
        }	
		
	TCanvas *myC = new TCanvas( "myC", "myC", 200, 10, 800, 600 );
        myC->SetHighLightColor(2);
        myC->SetFillColor(0);
        myC->SetBorderMode(0);
        myC->SetBorderSize(2);
        myC->SetLeftMargin( leftMargin );
        myC->SetRightMargin( rightMargin );
        myC->SetTopMargin( topMargin );
        myC->SetBottomMargin( bottomMargin );
        myC->SetFrameBorderMode(0);
        myC->SetFrameBorderMode(0);

	TMultiGraph *mg = new TMultiGraph();
	
	TGraphErrors *gr0 = new TGraphErrors(nDigi, average_time0, average_amp0, ex, ey);
        gr0->SetMarkerStyle(20);
    	gr0->SetMarkerSize(0.6);
    	gr0->SetMarkerColor(kBlue);
    	gr0->SetLineColor(kBlue);
	
	TGraphErrors *gr5 = new TGraphErrors(nDigi, average_time5, average_amp5, ex, ey);
        gr5->SetMarkerStyle(20);
    	gr5->SetMarkerSize(0.6);
    	gr5->SetMarkerColor(kRed);
    	gr5->SetLineColor(kRed);
	
	mg->Add(gr0);
	mg->Add(gr5);
        mg->Draw("AL");
	mg->GetHistogram()->GetXaxis()->SetTitle("time [ns]");
        mg->GetHistogram()->GetXaxis()->SetTitleSize( axisTitleSizeX );
        mg->GetHistogram()->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
        mg->GetHistogram()->GetYaxis()->SetTitleSize( axisTitleSizeY );
        mg->GetHistogram()->GetYaxis()->SetTitleOffset( axisTitleOffsetY );

	mg->GetHistogram()->GetYaxis()->SetTitle("photon current [ns^{-1}]");
        gPad->Modified();
        gPad->Update();

		
	TLegend * leg  = new TLegend (0.45,0.77,0.80,0.92);
        leg->SetBorderSize(0);
        leg->SetTextSize(0.06);
        leg->SetLineColor(1);
        leg->SetLineStyle(1);
        leg->SetLineWidth(1);
        leg->SetFillColor(0);
        leg->SetFillStyle(1001);

        leg->AddEntry(gr0, "center (x = 0mm)", "l");
        leg->AddEntry(gr5, "edge (x = 5mm)", "l");
        leg->Draw();		

	if(timetag == "1")
	{
	myC->SaveAs((plotDir+inFileName+"_average_pulses_x05.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_average_pulses_x05.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_average_pulses_x05.C").c_str());
	}
	else
	{
	myC->SaveAs((plotDir+inFileName+"_average_pulses_zoom_x05.pdf").c_str());
        myC->SaveAs((plotDir+inFileName+"_average_pulses_zoom_x05.png").c_str());
        myC->SaveAs((plotDir+inFileName+"_average_pulses_zoom_x05.C").c_str());
	}
	
	delete myC;
	delete gr0;
	delete gr5;
	delete leg;	
	delete amp1;
	delete time1;
}

float draw_nPhotons(TTree * tree, std::string& inFileName, std::string& plotDir)
{
        TCanvas *myC = new TCanvas( "myC", "myC", 200, 10, 800, 600 );
        myC->SetHighLightColor(2);
        myC->SetFillColor(0);
        myC->SetBorderMode(0);
        myC->SetBorderSize(2);
        myC->SetLeftMargin( leftMargin );
        myC->SetRightMargin( rightMargin );
        myC->SetTopMargin( topMargin );
        myC->SetBottomMargin( bottomMargin );
        myC->SetFrameBorderMode(0);
        myC->SetFrameBorderMode(0);


	TH1F * h1_np = new TH1F("h1_np","h1_np", 400, 0, 600000.0);
	tree->Draw("nPhotons>>h1_np");
	TF1 * f1_landau = new TF1("flandau","[0]*TMath::Landau(x,[1],[2])", 0, 600000.0);	
	f1_landau->SetParameters(h1_np->GetMaximum(), h1_np->GetBinCenter(h1_np->GetMaximumBin()), 1000.0);

	h1_np->SetMarkerStyle( 20 );
        h1_np->SetMarkerColor( kBlack );
        h1_np->SetLineColor( kBlack );
	
	h1_np->GetXaxis()->SetTitle("number of photons");
        h1_np->GetYaxis()->SetTitle("Events");
        h1_np->SetTitle("");
        h1_np->GetXaxis()->SetTitleSize( axisTitleSizeX );
        h1_np->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
        h1_np->GetYaxis()->SetTitleSize( axisTitleSizeY );
        h1_np->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
        h1_np->Draw("E");
	h1_np->Fit("flandau", "", "", 0, 600000.0);
	float nphotons_this = f1_landau->GetParameter(1);
	
	gPad->Modified();
        gPad->Update();
	
	
	myC->SaveAs((plotDir+inFileName+"_nphotons.pdf").c_str());	
	myC->SaveAs((plotDir+inFileName+"_nphotons.png").c_str());	
	myC->SaveAs((plotDir+inFileName+"_nphotons.C").c_str());	
	
	delete myC;
	delete h1_np;
	delete f1_landau;
	
	return nphotons_this;
	
}

void goodplot(std::string inFileName)
{

	std::string inFileName0 = inFileName;
	
	std::string inFileName5 = inFileName.replace(inFileName.find("x0"), 2, "x5");
	std::string inFileName05 = inFileName.replace(inFileName.find("_x5"), 3, "");

	//string plotDir = "/afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/geant4/"+inFileName05+"/";
	string plotDir = "/afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/geant4/";

	mkdir(plotDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);

	TFile *f0 = new TFile(("/eos/user/z/zhicaiz/TestBeam/geant4/ntuples/"+inFileName0+".root").c_str(), "READ");
	TTree *tree0 = (TTree*)f0->Get("tree");
	TFile *f5 = new TFile(("/eos/user/z/zhicaiz/TestBeam/geant4/ntuples/"+inFileName5+".root").c_str(), "READ");
	TTree *tree5 = (TTree*)f5->Get("tree");

	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);

	drawTracks(tree0, inFileName0, plotDir);
	drawTracks(tree5, inFileName5, plotDir);
	drawT100(tree0, tree5, inFileName05, plotDir);
	nPhotons_x0 = draw_nPhotons(tree0, inFileName0, plotDir);
	nPhotons_x5 = draw_nPhotons(tree5, inFileName5, plotDir);
	draw_average_pulse(tree0, tree5, inFileName05, plotDir, "1");		
	draw_average_pulse(tree0, tree5, inFileName05, plotDir, "2");		
	
}
