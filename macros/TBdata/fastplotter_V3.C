#include <iostream>
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
#include "TStyle.h"
#include "TF1.h"
#include "TPad.h"

void fastplotter_V3(const std::string& inFileName)
{
	string ch1 = "16";
	string ch2 = "9";
	string inputDir = "/eos/uscms/store/group/cmstestbeam/BTL/March2018/OTSDAQ/CMSTiming/RECO/V3/";
	string plotDir = "/eos/uscms/store/group/cmstestbeam/BTL/March2018/OTSDAQ/CMSTiming/RECO/V3//DQM/";

	mkdir(plotDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	mkdir((plotDir+"/png").c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
	mkdir((plotDir+"/C").c_str(), S_IRWXU | S_IRWXG | S_IRWXO);

	cout<<"plotting run:"<<inFileName<<endl;

	string cut = "amp["+ch1+"]>100.0 && amp["+ch1+"] < 450.0 && amp["+ch2+"]>10.0 && amp["+ch2+"]<450.0 && x_dut[0] > 5 && x_dut[0]<35";
	string cut1 = "amp["+ch1+"]>0.02 && x_dut[0] > 5 && x_dut[0]<35";
	string cut2 = "amp["+ch2+"]>0.02 && x_dut[0] > 5 && x_dut[0]<35";// && amp["+ch1+"]>100.0";
 	
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);

	TFile* inFile = TFile::Open((inputDir+"/DataCMSVMETiming_Run"+inFileName+".root").c_str(),"READ");
	TTree* tree = (TTree*)( inFile->Get("pulse") );

	Int_t NEntries = tree->GetEntries();
        Int_t NEntries_cut = tree->GetEntries(cut.c_str());
        Int_t NEntries_cut1 = tree->GetEntries(cut1.c_str());
        Int_t NEntries_cut2 = tree->GetEntries(cut2.c_str());

        cout<<"[tot]: "<<NEntries<<"   [cut]: "<<NEntries_cut<<"   [cut"+ch1+"]: "<<NEntries_cut1<<"   [cut"+ch2+"]"<<NEntries_cut2<<endl;


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
	float rightMargin  = 0.05;
	float topMargin    = 0.07;
	float bottomMargin = 0.12;


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

	//amplitude
	TH1F * h_ch1E = new TH1F("h_ch1E","h_ch1E",400,15, 2000.0);
	TH1F * h_ch2E = new TH1F("h_ch2E","h_ch2E",400,15,2000.0);

	tree->Draw(("amp["+ch1+"]>>h_ch1E").c_str(), cut1.c_str());	
	tree->Draw(("amp["+ch2+"]>>h_ch2E").c_str(), cut2.c_str());	
	
	h_ch1E->SetTitle("");
	float maxY_E = 1.2*std::max(h_ch1E->GetMaximum(), h_ch2E->GetMaximum());

	float maxX_ch1E = h_ch1E->GetBinCenter(h_ch1E->GetMaximumBin());
	float highch1E=h_ch1E->GetBinCenter(h_ch1E->FindLastBinAbove(int(0.1*h_ch1E->GetMaximum())));
	float maxX_ch1 = std::max(2.0*maxX_ch1E, highch1E+200.0);

	float maxX_ch2E = h_ch2E->GetBinCenter(h_ch2E->GetMaximumBin());
	float highch2E=h_ch2E->GetBinCenter(h_ch2E->FindLastBinAbove(int(0.1*h_ch2E->GetMaximum())));
	float maxX_ch2 = std::max(2.0*maxX_ch2E, highch2E+200.0);

	float maxX_E = std::max(maxX_ch1, maxX_ch2);

	h_ch1E->SetMarkerStyle( 20 );
	h_ch1E->SetMarkerColor( 2 );
	h_ch1E->SetLineColor( 2 );
	h_ch2E->SetMarkerStyle( 20 );
	h_ch2E->SetMarkerColor( 4 );
	h_ch2E->SetLineColor( 4 );
	h_ch1E->GetXaxis()->SetTitle("Amplitude [mV]");
	h_ch1E->GetYaxis()->SetTitle("Events");
	h_ch1E->SetTitle("");
	h_ch1E->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_ch1E->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_ch1E->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_ch1E->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h_ch1E->GetYaxis()->SetRangeUser(0.0,maxY_E  );
	h_ch1E->GetXaxis()->SetRangeUser(0.0,maxX_E );
        h_ch1E->Draw("histE");
	
	h_ch2E->Draw("samehistE");
	
	TLegend * leg_E  = new TLegend (0.7,0.7,0.9,0.9);
	leg_E->SetBorderSize(0);
	leg_E->SetTextSize(0.03);
	leg_E->SetLineColor(1);
	leg_E->SetLineStyle(1);
	leg_E->SetLineWidth(1);
	leg_E->SetFillColor(0);
	leg_E->SetFillStyle(1001);
		
	leg_E->AddEntry(h_ch1E, ("ch "+ch1).c_str(), "lp");
	leg_E->AddEntry(h_ch2E, ("ch "+ch2).c_str(), "lp");
	leg_E->Draw();

	myC->SaveAs((plotDir+inFileName+"_amplitude.pdf").c_str());
	myC->SaveAs((plotDir+"/png/"+inFileName+"_amplitude.png").c_str());
	myC->SaveAs((plotDir+"/C/"+inFileName+"_amplitude.C").c_str());

	// time resolution
	TH1F * h_deltaT = new TH1F("h_deltaT","h_deltaT",8000,-50.0, 50.0);
	tree->Draw(("LP2_10["+ch1+"]-gaus_mean["+ch2+"]>>h_deltaT").c_str(), cut.c_str());	
	h_deltaT->SetTitle("");
	h_deltaT->SetMarkerStyle( 20 );
	h_deltaT->SetMarkerColor( 1 );
	h_deltaT->SetLineColor( 1 );
	h_deltaT->GetXaxis()->SetTitle(("#Delta t ("+ch1+", "+ch2+") / ps").c_str());
	h_deltaT->GetYaxis()->SetTitle("Events");
	h_deltaT->SetTitle("");
	h_deltaT->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_deltaT->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_deltaT->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_deltaT->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	float maxY_t = h_deltaT->GetMaximum();
	float maxX_t = h_deltaT->GetBinCenter(h_deltaT->GetMaximumBin());
       	h_deltaT->GetXaxis()->SetRangeUser(maxX_t-0.6, maxX_t+0.6);
        h_deltaT->Draw("E");

	float highDeltaT=h_deltaT->GetBinCenter(h_deltaT->FindLastBinAbove(int(0.1*maxY_t)));
	float lowDeltaT=h_deltaT->GetBinCenter(h_deltaT->FindFirstBinAbove(int(0.1*maxY_t)));
	TF1 * tf1_gaus = new TF1("tf1_gaus","gaus", maxX_t - 1.0, maxX_t + 1.0);
	tf1_gaus->SetParameter(1, h_deltaT->GetMean());
	h_deltaT->Fit("tf1_gaus","","",lowDeltaT, highDeltaT);

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+inFileName+"_deltaT.pdf").c_str());
	myC->SaveAs((plotDir+"/png/"+inFileName+"_deltaT.png").c_str());
	myC->SaveAs((plotDir+"/C/"+inFileName+"_deltaT.C").c_str());

}
