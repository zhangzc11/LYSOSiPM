
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

void goodplot_all(const std::string& inFileName, const std::string& ch1  = "16", float amp_low = 200.0, float amp_high = 850.0, float x_tile_low = 20.0, float x_tile_high = 30.0, float y_tile_low = 5.0, float y_tile_high = 12.0, float x_sipm_low = 23.0, float x_sipm_high = 27.0, float y_sipm_low = 7.0, float y_sipm_high = 10.0)
{
	//string ch1 = "15";
	string ch2 = "9";
	
	string time_ch1 = "LP2_10";
	string time_ch2 = "gaus_mean";

	float fit_range_left = 0.09;
	float fit_range_right = 0.09;

	float amp_low_fit = amp_low;
	float amp_high_fit = amp_high;

	float amp_low_ch2 = 40.0;
	float amp_high_ch2 = 150.0;

	float x_center = 2.0*((int(0.5*(x_sipm_low+x_sipm_high)))/2)+1.0;
	float y_center = 2.0*((int(0.5*(y_sipm_low+y_sipm_high)))/2)+1.0;
	
	float x_low = x_center - 9.0;
	float x_high = x_center + 9.0;
	float y_low = y_center - 9.0;
	float y_high = y_center + 9.0;
	
	float x_tile_low_fit = x_tile_low + 1.0;
	float x_tile_high_fit = x_tile_high - 1.0 ;
	float y_tile_low_fit = y_tile_low + 1.0;
	float y_tile_high_fit = y_tile_high - 1.0;
	
	float x_sipm_low_fit = x_sipm_low + 0.0;
	float x_sipm_high_fit = x_sipm_high - 0.0 ;
	float y_sipm_low_fit = y_sipm_low + 0.0;
	float y_sipm_high_fit = y_sipm_high - 0.0;
	
	int x_bin_center = int((0.5*(x_sipm_low+x_sipm_high) - x_low)/0.25);
	int x_bin_left = int((x_tile_low- x_low)/0.25) + 1; 
	int x_bin_left_sipm = int((x_sipm_low- x_low)/0.25) + 1; 
	int x_bin_right = int((x_tile_high- x_low)/0.25) - 1; 
	int x_bin_right_sipm = int((x_sipm_high- x_low)/0.25) - 1; 

	int y_bin_center = int((0.5*(y_sipm_low+y_sipm_high) - y_low)/0.25);
	int y_bin_left = int((y_tile_low- y_low)/0.25) + 1; 
	int y_bin_left_sipm = int((y_sipm_low- y_low)/0.25) + 1; 
	int y_bin_right = int((y_tile_high- y_low)/0.25) - 1; 
	int y_bin_right_sipm = int((y_sipm_high- y_low)/0.25) - 1; 
	
	int all_xybin_min = 50;
	float all_xydt_min = 999999.9;
	int all_xybin_max = 50;
	float all_xydt_max = -999999.9;


	string inputDir = "/eos/cms/store/group/phys_susy/razor/Timing/Mar2018FNAL/OTSDAQ/CMSTiming/RECO/V3/combine";
	string plotDir = "plots_V2/";

	mkdir(plotDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);

	
	float sigmaT_best = 9999.9;
	float sigmaT_best_sipm = 9999.9;

	float sigmaT_noCor = 0.0;
	float sigmaT_TWCor = 0.0;
	float sigmaT_XYCor = 0.0;
	float sigmaT_TWXYCor = 0.0;

	float sigmaT_noCor_sipm = 0.0;
	float sigmaT_TWCor_sipm = 0.0;
	float sigmaT_XYCor_sipm = 0.0;
	float sigmaT_TWXYCor_sipm = 0.0;

	float offsetXT_noCor = 0.0;
	float offsetYT_noCor = 0.0;
	float offsetXT_TWCor = 0.0;
	float offsetYT_TWCor = 0.0;

	float offsetXT_noCor_sipm = 0.0;
	float offsetYT_noCor_sipm = 0.0;
	float offsetXT_TWCor_sipm = 0.0;
	float offsetYT_TWCor_sipm = 0.0;


	cout<<"plotting run:"<<inFileName<<endl;
	
	string cut_noPos = "amp["+ch1+"]>"+std::to_string(amp_low)+" && amp["+ch1+"] < "+std::to_string(amp_high)+" && amp["+ch2+"]>"+std::to_string(amp_low_ch2)+" && amp["+ch2+"]<"+std::to_string(amp_high_ch2)+" && gaus_mean["+ch2+"]>1 && gaus_mean["+ch2+"]<100";

        string cut = "amp["+ch1+"]>"+std::to_string(amp_low)+" && amp["+ch1+"] < "+std::to_string(amp_high)+" && amp["+ch2+"]>"+std::to_string(amp_low_ch2)+" && amp["+ch2+"]<"+std::to_string(amp_high_ch2)+" && x_dut[0] > "+std::to_string(x_tile_low)+" && x_dut[0]<"+std::to_string(x_tile_high)+" && y_dut[0]>"+std::to_string(y_tile_low)+" && y_dut[0]<"+std::to_string(y_tile_high)+"&& gaus_mean["+ch2+"]>1 && gaus_mean["+ch2+"]<100";
        string cut_sipm = "amp["+ch1+"]>"+std::to_string(amp_low)+" && amp["+ch1+"] < "+std::to_string(amp_high)+" && amp["+ch2+"]>"+std::to_string(amp_low_ch2)+" && amp["+ch2+"]<"+std::to_string(amp_high_ch2)+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)+"&& gaus_mean["+ch2+"]>1 && gaus_mean["+ch2+"]<100";


	cout<<"cut --->  "<<cut<<endl;
	cout<<"cut_sipm --->  "<<cut_sipm<<endl;
	//ch1 and ch2 very basic cut
	string cut1 = "amp["+ch1+"]>10";
	string cut2 = "amp["+ch2+"]>10";
	string cut_shower = "amp["+ch1+"]>10 && amp["+ch1+"]<"+std::to_string(amp_high)+" && amp["+ch2+"]>10 && amp["+ch2+"]<250";
 	
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);
	gStyle->SetPalette(1);

	TFile* inFile = TFile::Open((inputDir+"/DataCMSVMETiming_Run"+inFileName+".root").c_str(),"READ");
	TTree* tree = (TTree*)( inFile->Get("pulse") );

	Int_t NEntries = tree->GetEntries();
        Int_t NEntries_cut_noPos = tree->GetEntries(cut_noPos.c_str());
        Int_t NEntries_cut = tree->GetEntries(cut.c_str());
        Int_t NEntries_cut_sipm = tree->GetEntries(cut_sipm.c_str());
        //Int_t NEntries_cut1 = tree->GetEntries(cut1.c_str());
        //Int_t NEntries_cut2 = tree->GetEntries(cut2.c_str());

        cout<<"[tot]: "<<NEntries<<"   [cut_noPos]: "<<NEntries_cut_noPos<<"   [cut]: "<<NEntries_cut<<"   [cut_sipm]: "<<NEntries_cut_sipm<<endl;

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


	// beam spot selection
	myC->SetGridy(1);
	myC->SetGridx(1);
	// ch1
	TH2F * h2_beamSpotch1 = new TH2F("h2_beamSpotch1","h2_beamSpotch1",100,x_low, x_high,100,y_low, y_high);
	TH2F * h2_beamSpotch1Num = new TH2F("h2_beamSpotch1Num","h2_beamSpotch1Num",100,x_low, x_high,100,y_low,y_high);
	TH2F * h2_beamSpotch1NumNoCut = new TH2F("h2_beamSpotch1NumNoCut","h2_beamSpotch1Num",100,x_low, x_high,100,y_low,y_high);
	tree->Draw("y_dut[0]:x_dut[0]>>h2_beamSpotch1Num",cut_shower.c_str());
	tree->Draw("y_dut[0]:x_dut[0]>>h2_beamSpotch1NumNoCut","");

	tree->Draw("y_dut[0]:x_dut[0]>>h2_beamSpotch1",("amp["+ch1+"]*("+cut_shower+")").c_str());
	h2_beamSpotch1->Divide(h2_beamSpotch1Num);
	h2_beamSpotch1->Draw("colz");
	
	h2_beamSpotch1->GetXaxis()->SetTitle("beam position X [mm]");
	h2_beamSpotch1->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_beamSpotch1->GetZaxis()->SetTitle("amplitude [mV]");
	h2_beamSpotch1->SetTitle("");
	h2_beamSpotch1->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_beamSpotch1->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_beamSpotch1->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_beamSpotch1->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch1+".C").c_str());

	h2_beamSpotch1Num->Draw("colz");
	
	h2_beamSpotch1Num->GetXaxis()->SetTitle("beam position X [mm]");
	h2_beamSpotch1Num->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_beamSpotch1Num->GetZaxis()->SetTitle("Events");
	h2_beamSpotch1Num->SetTitle("");
	h2_beamSpotch1Num->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_beamSpotch1Num->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_beamSpotch1Num->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_beamSpotch1Num->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_Num_withCut_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_Num_withCut_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_Num_withCut_ch"+ch1+".C").c_str());

	h2_beamSpotch1NumNoCut->Draw("colz");
	
	h2_beamSpotch1NumNoCut->GetXaxis()->SetTitle("beam position X [mm]");
	h2_beamSpotch1NumNoCut->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_beamSpotch1NumNoCut->GetZaxis()->SetTitle("Events");
	h2_beamSpotch1NumNoCut->SetTitle("");
	h2_beamSpotch1NumNoCut->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_beamSpotch1NumNoCut->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_beamSpotch1NumNoCut->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_beamSpotch1NumNoCut->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_NumNoCut.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_NumNoCut.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_NumNoCut.C").c_str());


	//ch1 amp vs x position
	TH2F * h2_amp_vs_x_ch1 = new TH2F("h2_amp_vs_x_ch1","h2_amp_vs_x_ch1",72,x_low, x_high,100, 0.0, 600.0);
	tree->Draw(("amp["+ch1+"]:x_dut[0]>>h2_amp_vs_x_ch1").c_str(),cut_shower.c_str());

	TProfile * p_amp_vs_x_ch1 = h2_amp_vs_x_ch1->ProfileX(); 
	p_amp_vs_x_ch1->GetXaxis()->SetTitle("beam position X [mm]");
	p_amp_vs_x_ch1->GetYaxis()->SetTitle(("amplitude (ch"+ch1+") / mV").c_str());
	p_amp_vs_x_ch1->SetTitle("");
	
	p_amp_vs_x_ch1->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_amp_vs_x_ch1->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_amp_vs_x_ch1->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_amp_vs_x_ch1->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_amp_vs_x_ch1->GetXaxis()->SetRangeUser(x_low, x_high);
       	p_amp_vs_x_ch1->GetYaxis()->SetRangeUser(0.0, 600.0);
        p_amp_vs_x_ch1->SetMarkerStyle( 20 );
        p_amp_vs_x_ch1->SetMarkerColor( 1 );
        p_amp_vs_x_ch1->SetLineColor( 1 );
	p_amp_vs_x_ch1->Draw();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch1+".C").c_str());


	//ch1 amp vs y position
	TH2F * h2_amp_vs_y_ch1 = new TH2F("h2_amp_vs_y_ch1","h2_amp_vs_y_ch1",100,y_low, y_high,100,0.0, 600.0);
	tree->Draw(("amp["+ch1+"]:y_dut[0]>>h2_amp_vs_y_ch1").c_str(),cut_shower.c_str());

	TProfile * p_amp_vs_y_ch1 = h2_amp_vs_y_ch1->ProfileX(); 
	p_amp_vs_y_ch1->GetXaxis()->SetTitle("beam position Y [mm]");
	p_amp_vs_y_ch1->GetYaxis()->SetTitle(("amplitude (ch"+ch1+") / mV").c_str());
	p_amp_vs_y_ch1->SetTitle("");
	
	p_amp_vs_y_ch1->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_amp_vs_y_ch1->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_amp_vs_y_ch1->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_amp_vs_y_ch1->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_amp_vs_y_ch1->GetXaxis()->SetRangeUser(y_low, y_high);
       	p_amp_vs_y_ch1->GetYaxis()->SetRangeUser(0.0, 600.0);
        p_amp_vs_y_ch1->SetMarkerStyle( 20 );
        p_amp_vs_y_ch1->SetMarkerColor( 1 );
        p_amp_vs_y_ch1->SetLineColor( 1 );
	p_amp_vs_y_ch1->Draw();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch1+".C").c_str());

	// ch2
	TH2F * h2_beamSpotch2 = new TH2F("h2_beamSpotch2","h2_beamSpotch2",100,x_low, x_high,100,y_low,y_high);
	TH2F * h2_beamSpotch2Num = new TH2F("h2_beamSpotch2Num","h2_beamSpotch2Num",100,x_low, x_high,100,y_low,y_high);
	tree->Draw("y_dut[0]:x_dut[0]>>h2_beamSpotch2Num",cut_shower.c_str());
	tree->Draw("y_dut[0]:x_dut[0]>>h2_beamSpotch2",("amp["+ch2+"]*("+cut_shower+")").c_str());
	h2_beamSpotch2->Divide(h2_beamSpotch2Num);
	h2_beamSpotch2->Draw("colz");
	
	h2_beamSpotch2->GetXaxis()->SetTitle("beam position X [mm]");
	h2_beamSpotch2->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_beamSpotch2->GetZaxis()->SetTitle("amplitude [mV]");
	h2_beamSpotch2->GetZaxis()->SetRangeUser(0.0, 300.0);
	h2_beamSpotch2->SetTitle("");
	h2_beamSpotch2->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_beamSpotch2->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_beamSpotch2->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_beamSpotch2->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch2+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch2+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch2+".C").c_str());

	
	//ch2 amp vs x position
	TH2F * h2_amp_vs_x_ch2 = new TH2F("h2_amp_vs_x_ch2","h2_amp_vs_x_ch2",72,x_low, x_high,100, 0.0, 600.0);
	tree->Draw(("amp["+ch2+"]:x_dut[0]>>h2_amp_vs_x_ch2").c_str(),cut_shower.c_str());

	TProfile * p_amp_vs_x_ch2 = h2_amp_vs_x_ch2->ProfileX(); 
	p_amp_vs_x_ch2->GetXaxis()->SetTitle("beam position X [mm]");
	p_amp_vs_x_ch2->GetYaxis()->SetTitle(("amplitude (ch"+ch2+") / mV").c_str());
	p_amp_vs_x_ch2->SetTitle("");
	
	p_amp_vs_x_ch2->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_amp_vs_x_ch2->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_amp_vs_x_ch2->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_amp_vs_x_ch2->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_amp_vs_x_ch2->GetXaxis()->SetRangeUser(x_low, x_high);
       	p_amp_vs_x_ch2->GetYaxis()->SetRangeUser(0.0, 600.0);
        p_amp_vs_x_ch2->SetMarkerStyle( 20 );
        p_amp_vs_x_ch2->SetMarkerColor( 1 );
        p_amp_vs_x_ch2->SetLineColor( 1 );
	p_amp_vs_x_ch2->Draw();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch2+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch2+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch2+".C").c_str());

	//ch2 amp vs y position
	TH2F * h2_amp_vs_y_ch2 = new TH2F("h2_amp_vs_y_ch2","h2_amp_vs_y_ch2",72,x_low, x_high,100,0.0, 600.0);
	tree->Draw(("amp["+ch2+"]:y_dut[0]>>h2_amp_vs_y_ch2").c_str(),cut_shower.c_str());

	TProfile * p_amp_vs_y_ch2 = h2_amp_vs_y_ch2->ProfileX(); 
	p_amp_vs_y_ch2->GetXaxis()->SetTitle("beam position X [mm]");
	p_amp_vs_y_ch2->GetYaxis()->SetTitle(("amplitude (ch"+ch2+") / mV").c_str());
	p_amp_vs_y_ch2->SetTitle("");
	
	p_amp_vs_y_ch2->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_amp_vs_y_ch2->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_amp_vs_y_ch2->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_amp_vs_y_ch2->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_amp_vs_y_ch2->GetXaxis()->SetRangeUser(x_low, x_high);
       	p_amp_vs_y_ch2->GetYaxis()->SetRangeUser(0.0, 600.0);
        p_amp_vs_y_ch2->SetMarkerStyle( 20 );
        p_amp_vs_y_ch2->SetMarkerColor( 1 );
        p_amp_vs_y_ch2->SetLineColor( 1 );
	p_amp_vs_y_ch2->Draw();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch2+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch2+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch2+".C").c_str());


	//amplitude
	myC->SetGridy(0);
	myC->SetGridx(0);
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
	
	TLegend * leg_E  = new TLegend (0.45,0.6,0.85,0.9);
	leg_E->SetBorderSize(0);
	leg_E->SetTextSize(0.06);
	leg_E->SetLineColor(1);
	leg_E->SetLineStyle(1);
	leg_E->SetLineWidth(1);
	leg_E->SetFillColor(0);
	leg_E->SetFillStyle(1001);
		
	leg_E->AddEntry(h_ch1E, ("ch "+ch1).c_str(), "lp");
	leg_E->AddEntry(h_ch2E, ("ch "+ch2).c_str(), "lp");
	leg_E->Draw();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amplitude_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amplitude_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amplitude_ch"+ch1+".C").c_str());


	// time resolution, LYSO area
	TH1F * h_deltaT = new TH1F("h_deltaT","h_deltaT",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]>>h_deltaT").c_str(), cut.c_str());	
	h_deltaT->SetTitle("");
	h_deltaT->SetMarkerStyle( 20 );
	h_deltaT->SetMarkerColor( 1 );
	h_deltaT->SetLineColor( 1 );
	h_deltaT->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
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

	float highDeltaT=maxX_t+fit_range_right+0.02;//h_deltaT->GetBinCenter(h_deltaT->FindLastBinAbove(int(0.3*maxY_t)));
	float lowDeltaT=maxX_t-fit_range_left-0.08;//h_deltaT->GetBinCenter(h_deltaT->FindFirstBinAbove(int(0.1*maxY_t)));
	//if(highDeltaT - maxX_t > 2.0*(maxX_t-lowDeltaT)) highDeltaT = maxX_t + (maxX_t - lowDeltaT);
	TF1 * tf1_gaus = new TF1("tf1_gaus","gaus", maxX_t - 1.0, maxX_t + 1.0);
	tf1_gaus->SetParameter(1, h_deltaT->GetMean());
	h_deltaT->Fit("tf1_gaus","","",lowDeltaT, highDeltaT);
	
	sigmaT_noCor = tf1_gaus->GetParameter(2);	
	if(sigmaT_noCor <  sigmaT_best) sigmaT_best = sigmaT_noCor;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_ch"+ch1+".C").c_str());


	// time resolution, SiPM area
	TH1F * h_deltaT_sipm = new TH1F("h_deltaT_sipm","h_deltaT_sipm",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]>>h_deltaT_sipm").c_str(), cut_sipm.c_str());	
	h_deltaT_sipm->SetTitle("");
	h_deltaT_sipm->SetMarkerStyle( 20 );
	h_deltaT_sipm->SetMarkerColor( 1 );
	h_deltaT_sipm->SetLineColor( 1 );
	h_deltaT_sipm->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h_deltaT_sipm->GetYaxis()->SetTitle("Events");
	h_deltaT_sipm->SetTitle("");
	h_deltaT_sipm->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_deltaT_sipm->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_deltaT_sipm->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_deltaT_sipm->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	float maxY_t_sipm = h_deltaT_sipm->GetMaximum();
	float maxX_t_sipm = h_deltaT_sipm->GetBinCenter(h_deltaT_sipm->GetMaximumBin());
       	h_deltaT_sipm->GetXaxis()->SetRangeUser(maxX_t_sipm-0.6, maxX_t_sipm+0.6);
        h_deltaT_sipm->Draw("E");

	float highDeltaT_sipm=maxX_t_sipm+fit_range_right;//h_deltaT_sipm->GetBinCenter(h_deltaT_sipm->FindLastBinAbove(int(0.3*maxY_t_sipm)));
	float lowDeltaT_sipm=maxX_t_sipm-fit_range_left;//h_deltaT_sipm->GetBinCenter(h_deltaT_sipm->FindFirstBinAbove(int(0.1*maxY_t_sipm)));
	//if(highDeltaT_sipm - maxX_t_sipm > 2.0*(maxX_t_sipm-lowDeltaT_sipm)) highDeltaT_sipm = maxX_t_sipm + (maxX_t_sipm - lowDeltaT_sipm);
	TF1 * tf1_gaus_sipm = new TF1("tf1_gaus_sipm","gaus", maxX_t_sipm - 1.0, maxX_t_sipm + 1.0);
	tf1_gaus_sipm->SetParameter(1, h_deltaT_sipm->GetMean());
	h_deltaT_sipm->Fit("tf1_gaus_sipm","","",lowDeltaT_sipm, highDeltaT_sipm);

	sigmaT_noCor_sipm = tf1_gaus_sipm->GetParameter(2);	
	if(sigmaT_noCor_sipm < sigmaT_best_sipm) sigmaT_best_sipm=sigmaT_noCor_sipm;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_ch"+ch1+"_sipm.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_ch"+ch1+"_sipm.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_ch"+ch1+"_sipm.C").c_str());

	//amplitude dependency of the deltaT
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_vs_amp = new TH2F("h2_deltaT_vs_amp","h2_deltaT_vs_amp", 100, amp_low, amp_high, 100, maxX_t-0.6, maxX_t+0.6);
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]:amp["+ch1+"]>>h2_deltaT_vs_amp").c_str(),cut.c_str());
	h2_deltaT_vs_amp->GetXaxis()->SetTitle("amplitude [mV]");
	h2_deltaT_vs_amp->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_vs_amp->SetTitle("");
	h2_deltaT_vs_amp->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_vs_amp->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_vs_amp->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_vs_amp->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_vs_amp->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_ch"+ch1+".C").c_str());

	TProfile * p_deltaT_vs_amp = h2_deltaT_vs_amp->ProfileX(); 
	p_deltaT_vs_amp->GetXaxis()->SetTitle("amplitude [mV]");
	p_deltaT_vs_amp->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_vs_amp->SetTitle("");
	
	p_deltaT_vs_amp->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_vs_amp->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_vs_amp->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_vs_amp->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_vs_amp->GetYaxis()->SetRangeUser(maxX_t-0.2, maxX_t+0.3);
       	p_deltaT_vs_amp->GetXaxis()->SetRangeUser(amp_low, amp_high);
        p_deltaT_vs_amp->SetMarkerStyle( 20 );
        p_deltaT_vs_amp->SetMarkerColor( 1 );
        p_deltaT_vs_amp->SetLineColor( 1 );
	p_deltaT_vs_amp->Draw();


	TF1 * tf1_pol1_amp = new TF1("tf1_pol1_amp","pol1", amp_low, amp_high);
	p_deltaT_vs_amp->Fit("tf1_pol1_amp","","",amp_low_fit, amp_high_fit);
	float amp_cor_p0 = tf1_pol1_amp->GetParameter(0);
	float amp_cor_p1 = tf1_pol1_amp->GetParameter(1);

	cout<<"p0: "<<amp_cor_p0<<" ;  p1: "<<amp_cor_p1<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_profile_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_profile_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_profile_ch"+ch1+".C").c_str());


	//amplitude dependency of the deltaT_sipm
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_sipm_vs_amp = new TH2F("h2_deltaT_sipm_vs_amp","h2_deltaT_sipm_vs_amp", 100, amp_low, amp_high, 100, maxX_t_sipm-0.6, maxX_t_sipm+0.6);
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]:amp["+ch1+"]>>h2_deltaT_sipm_vs_amp").c_str(),cut_sipm.c_str());
	h2_deltaT_sipm_vs_amp->GetXaxis()->SetTitle("amplitude [mV]");
	h2_deltaT_sipm_vs_amp->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_sipm_vs_amp->SetTitle("");
	h2_deltaT_sipm_vs_amp->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_sipm_vs_amp->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_sipm_vs_amp->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_sipm_vs_amp->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_sipm_vs_amp->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_ch"+ch1+"_sipm.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_ch"+ch1+"_sipm.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_ch"+ch1+"_sipm.C").c_str());

	TProfile * p_deltaT_sipm_vs_amp = h2_deltaT_sipm_vs_amp->ProfileX(); 
	p_deltaT_sipm_vs_amp->GetXaxis()->SetTitle("amplitude [mV]");
	p_deltaT_sipm_vs_amp->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_sipm_vs_amp->SetTitle("");
	
	p_deltaT_sipm_vs_amp->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_sipm_vs_amp->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_sipm_vs_amp->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_sipm_vs_amp->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_sipm_vs_amp->GetYaxis()->SetRangeUser(maxX_t_sipm-0.2, maxX_t_sipm+0.3);
       	p_deltaT_sipm_vs_amp->GetXaxis()->SetRangeUser(amp_low, amp_high);
        p_deltaT_sipm_vs_amp->SetMarkerStyle( 20 );
        p_deltaT_sipm_vs_amp->SetMarkerColor( 1 );
        p_deltaT_sipm_vs_amp->SetLineColor( 1 );
	p_deltaT_sipm_vs_amp->Draw();


	TF1 * tf1_pol1_amp_sipm = new TF1("tf1_pol1_amp_sipm","pol1", amp_low, amp_high);
	p_deltaT_sipm_vs_amp->Fit("tf1_pol1_amp_sipm","","",amp_low_fit, amp_high_fit);
	float amp_cor_sipm_p0 = tf1_pol1_amp_sipm->GetParameter(0);
	float amp_cor_sipm_p1 = tf1_pol1_amp_sipm->GetParameter(1);

	cout<<"p0: "<<amp_cor_sipm_p0<<" ;  p1: "<<amp_cor_sipm_p1<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_profile_ch"+ch1+"_sipm.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_profile_ch"+ch1+"_sipm.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_profile_ch"+ch1+"_sipm.C").c_str());

	//time resolution after time walk correction
	myC->SetGridy(0);
	myC->SetGridx(0);
	
	TH1F * h_deltaT_TWcorr = new TH1F("h_deltaT_TWcorr","h_deltaT_TWcorr",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_p0)+" + "+std::to_string(amp_cor_p1)+"*amp["+ch1+"])>>h_deltaT_TWcorr").c_str(), cut.c_str());	

	h_deltaT_TWcorr->SetTitle("");
	h_deltaT_TWcorr->SetMarkerStyle( 20 );
	h_deltaT_TWcorr->SetMarkerColor( 1 );
	h_deltaT_TWcorr->SetLineColor( 1 );
	h_deltaT_TWcorr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h_deltaT_TWcorr->GetYaxis()->SetTitle("Events");
	h_deltaT_TWcorr->SetTitle("");
	h_deltaT_TWcorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_deltaT_TWcorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_deltaT_TWcorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_deltaT_TWcorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	float maxY_t_TWcorr = h_deltaT_TWcorr->GetMaximum();
	float maxX_t_TWcorr = h_deltaT_TWcorr->GetBinCenter(h_deltaT_TWcorr->GetMaximumBin());
       	h_deltaT_TWcorr->GetXaxis()->SetRangeUser(maxX_t_TWcorr-0.6, maxX_t_TWcorr+0.6);
        h_deltaT_TWcorr->Draw("E");

	float highDeltaT_TWcorr=maxX_t_TWcorr + fit_range_right + 0.02;//h_deltaT_TWcorr->GetBinCenter(h_deltaT_TWcorr->FindLastBinAbove(int(0.3*maxY_t)));
	float lowDeltaT_TWcorr=maxX_t_TWcorr - fit_range_left - 0.04;//h_deltaT_TWcorr->GetBinCenter(h_deltaT_TWcorr->FindFirstBinAbove(int(0.1*maxY_t)));
	//if(highDeltaT_TWcorr - maxX_t_TWcorr > 2.0*(maxX_t_TWcorr-lowDeltaT_TWcorr)) highDeltaT_TWcorr = maxX_t_TWcorr + (maxX_t_TWcorr - lowDeltaT_TWcorr);
	TF1 * tf1_gaus_TWcorr = new TF1("tf1_gaus_TWcorr","gaus", maxX_t_TWcorr - 1.0, maxX_t_TWcorr + 1.0);
	tf1_gaus_TWcorr->SetParameter(1, h_deltaT_TWcorr->GetMean());
	h_deltaT_TWcorr->Fit("tf1_gaus_TWcorr","","",lowDeltaT_TWcorr, highDeltaT_TWcorr);

	sigmaT_TWCor = tf1_gaus_TWcorr->GetParameter(2);	
	if(sigmaT_TWCor <  sigmaT_best) sigmaT_best = sigmaT_TWCor;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TWcorr_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TWcorr_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TWcorr_ch"+ch1+".C").c_str());

	
	//time resolution after time walk correction, sipm area
	myC->SetGridy(0);
	myC->SetGridx(0);
	TH1F * h_deltaT_sipm_TWcorr = new TH1F("h_deltaT_sipm_TWcorr","h_deltaT_sipm_TWcorr",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_sipm_p0)+" + "+std::to_string(amp_cor_sipm_p1)+"*amp["+ch1+"])>>h_deltaT_sipm_TWcorr").c_str(), cut_sipm.c_str());	

	h_deltaT_sipm_TWcorr->SetTitle("");
	h_deltaT_sipm_TWcorr->SetMarkerStyle( 20 );
	h_deltaT_sipm_TWcorr->SetMarkerColor( 1 );
	h_deltaT_sipm_TWcorr->SetLineColor( 1 );
	h_deltaT_sipm_TWcorr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h_deltaT_sipm_TWcorr->GetYaxis()->SetTitle("Events");
	h_deltaT_sipm_TWcorr->SetTitle("");
	h_deltaT_sipm_TWcorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_deltaT_sipm_TWcorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_deltaT_sipm_TWcorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_deltaT_sipm_TWcorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	float maxY_t_sipm_TWcorr = h_deltaT_sipm_TWcorr->GetMaximum();
	float maxX_t_sipm_TWcorr = h_deltaT_sipm_TWcorr->GetBinCenter(h_deltaT_sipm_TWcorr->GetMaximumBin());
       	h_deltaT_sipm_TWcorr->GetXaxis()->SetRangeUser(maxX_t_sipm_TWcorr-0.6, maxX_t_sipm_TWcorr+0.6);
        h_deltaT_sipm_TWcorr->Draw("E");

	float highDeltaT_sipm_TWcorr=maxX_t_sipm_TWcorr + fit_range_right;//h_deltaT_sipm_TWcorr->GetBinCenter(h_deltaT_sipm_TWcorr->FindLastBinAbove(int(0.3*maxY_t_sipm)));
	float lowDeltaT_sipm_TWcorr=maxX_t_sipm_TWcorr - fit_range_left;//h_deltaT_sipm_TWcorr->GetBinCenter(h_deltaT_sipm_TWcorr->FindFirstBinAbove(int(0.1*maxY_t_sipm)));
	//if(highDeltaT_sipm_TWcorr - maxX_t_sipm_TWcorr > 2.0*(maxX_t_sipm_TWcorr-lowDeltaT_sipm_TWcorr)) highDeltaT_sipm_TWcorr = maxX_t_sipm_TWcorr + (maxX_t_sipm_TWcorr - lowDeltaT_sipm_TWcorr);
	TF1 * tf1_gaus_sipm_TWcorr = new TF1("tf1_gaus_sipm_TWcorr","gaus", maxX_t_sipm_TWcorr - 1.0, maxX_t_sipm_TWcorr + 1.0);
	tf1_gaus_sipm_TWcorr->SetParameter(1, h_deltaT_sipm_TWcorr->GetMean());
	h_deltaT_sipm_TWcorr->Fit("tf1_gaus_sipm_TWcorr","","",lowDeltaT_sipm_TWcorr, highDeltaT_sipm_TWcorr);

	sigmaT_TWCor_sipm = tf1_gaus_sipm_TWcorr->GetParameter(2);	
	if(sigmaT_TWCor_sipm <  sigmaT_best_sipm) sigmaT_best_sipm = sigmaT_TWCor_sipm;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TWcorr_ch"+ch1+"_sipm.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TWcorr_ch"+ch1+"_sipm.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TWcorr_ch"+ch1+"_sipm.C").c_str());

	
	// impact point dependency of the deltaT, without TW correction
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_vs_x = new TH2F("h2_deltaT_vs_x","h2_deltaT_vs_x", 72, x_low, x_high, 100, maxX_t-0.2, maxX_t+0.3);
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] : x_dut[0]>>h2_deltaT_vs_x").c_str(),cut_noPos.c_str());
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] : x_dut[0]>>h2_deltaT_vs_x").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	h2_deltaT_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_vs_x->SetTitle("");
	h2_deltaT_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_vs_x->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_ch"+ch1+".C").c_str());

	TProfile * p_deltaT_vs_x = h2_deltaT_vs_x->ProfileX(); 
	p_deltaT_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	p_deltaT_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_vs_x->SetTitle("");
	
	p_deltaT_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_vs_x->GetYaxis()->SetRangeUser(maxX_t-0.2, maxX_t+0.3);
       	p_deltaT_vs_x->GetXaxis()->SetRangeUser(x_tile_low, x_tile_high);
        p_deltaT_vs_x->SetMarkerStyle( 20 );
        p_deltaT_vs_x->SetMarkerColor( 1 );
        p_deltaT_vs_x->SetLineColor( 1 );
	p_deltaT_vs_x->Draw();

	float averageT_center = (p_deltaT_vs_x->GetBinContent(x_bin_center) + p_deltaT_vs_x->GetBinContent(x_bin_center-1) + p_deltaT_vs_x->GetBinContent(x_bin_center+1))/3.0;
	float averageT_left = (p_deltaT_vs_x->GetBinContent(x_bin_left) + p_deltaT_vs_x->GetBinContent(x_bin_left+1) + p_deltaT_vs_x->GetBinContent(x_bin_left+1))/3.0;
	float averageT_right = (p_deltaT_vs_x->GetBinContent(x_bin_right) + p_deltaT_vs_x->GetBinContent(x_bin_right-1) + p_deltaT_vs_x->GetBinContent(x_bin_right-1))/3.0;

	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_vs_x->GetBinContent(i);
		if(dt_this < all_xydt_min) 
		{
			all_xydt_min = dt_this;
			all_xybin_min = i;
		}
		
		if(dt_this > all_xydt_max) 
		{
			all_xydt_max = dt_this;
			all_xybin_max = i;
		}

	}
	offsetXT_noCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;


	//offsetXT_noCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetXT_noCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 
	
	TF1 * tf1_xyonly_pol4_x = new TF1("tf1_xyonly_pol4_x","pol4", x_tile_low-1, x_tile_high+1.0);
	p_deltaT_vs_x->Fit("tf1_xyonly_pol4_x","","",x_tile_low_fit, x_tile_high_fit);
	float x_cor_xyonly_p0 = tf1_xyonly_pol4_x->GetParameter(0);
	float x_cor_xyonly_p1 = tf1_xyonly_pol4_x->GetParameter(1);
	float x_cor_xyonly_p2 = tf1_xyonly_pol4_x->GetParameter(2);
	float x_cor_xyonly_p3 = tf1_xyonly_pol4_x->GetParameter(3);
	float x_cor_xyonly_p4 = tf1_xyonly_pol4_x->GetParameter(4);

	cout<<"p0: "<<x_cor_xyonly_p0<<" ;  p1: "<<x_cor_xyonly_p1<<" ;  p2: "<<x_cor_xyonly_p2<<" ;  p3: "<<x_cor_xyonly_p3<<" ;  p4: "<<x_cor_xyonly_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_profile_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_profile_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_profile_ch"+ch1+".C").c_str());

	h2_deltaT_vs_x->Draw();
	p_deltaT_vs_x->SetMarkerColor( 4 );
        p_deltaT_vs_x->SetLineColor( 4 );
	p_deltaT_vs_x->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_scatter_and_profile_ch"+ch1+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_scatter_and_profile_ch"+ch1+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_scatter_and_profile_ch"+ch1+".C").c_str());
	
	TH2F * h2_deltaT_vs_y = new TH2F("h2_deltaT_vs_y","h2_deltaT_vs_y", 72, y_low, y_high, 100, maxX_t-0.2, maxX_t+0.3);
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] : y_dut[0]>>h2_deltaT_vs_y").c_str(),cut_noPos.c_str());
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] : y_dut[0]>>h2_deltaT_vs_y").c_str(), (cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	h2_deltaT_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	h2_deltaT_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_vs_y->SetTitle("");
	h2_deltaT_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_vs_y->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_ch"+ch1+".C").c_str());

	TProfile * p_deltaT_vs_y = h2_deltaT_vs_y->ProfileX(); //new ("p_deltaT_vs_y","p_deltaT_vs_y",72, y_low, y_high);
	p_deltaT_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	p_deltaT_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_vs_y->SetTitle("");
	
	p_deltaT_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_vs_y->GetYaxis()->SetRangeUser(maxX_t-0.2, maxX_t+0.3);
       	p_deltaT_vs_y->GetXaxis()->SetRangeUser(y_tile_low, y_tile_high);
        p_deltaT_vs_y->SetMarkerStyle( 20 );
        p_deltaT_vs_y->SetMarkerColor( 1 );
        p_deltaT_vs_y->SetLineColor( 1 );
	p_deltaT_vs_y->Draw();

	averageT_center = (p_deltaT_vs_y->GetBinContent(y_bin_center) + p_deltaT_vs_y->GetBinContent(y_bin_center-1) + p_deltaT_vs_y->GetBinContent(y_bin_center+1))/3.0;
	averageT_left = (p_deltaT_vs_y->GetBinContent(y_bin_left) + p_deltaT_vs_y->GetBinContent(y_bin_left+1) + p_deltaT_vs_y->GetBinContent(y_bin_left+1))/3.0;
	averageT_right = (p_deltaT_vs_y->GetBinContent(y_bin_right) + p_deltaT_vs_y->GetBinContent(y_bin_right-1) + p_deltaT_vs_y->GetBinContent(y_bin_right-1))/3.0;

	//offsetYT_noCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetYT_noCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 
	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_vs_y->GetBinContent(i);
		if(dt_this < all_xydt_min) 
		{
			all_xydt_min = dt_this;
			all_xybin_min = i;
		}
		
		if(dt_this > all_xydt_max) 
		{
			all_xydt_max = dt_this;
			all_xybin_max = i;
		}

	}
	offsetYT_noCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;



	TF1 * tf1_xyonly_pol4_y = new TF1("tf1_xyonly_pol4_y","pol4", y_tile_low-1, y_tile_high+1.0);
	p_deltaT_vs_y->Fit("tf1_xyonly_pol4_y","","",y_tile_low_fit, y_tile_high_fit);
	float y_cor_xyonly_p0 = tf1_xyonly_pol4_y->GetParameter(0);
	float y_cor_xyonly_p1 = tf1_xyonly_pol4_y->GetParameter(1);
	float y_cor_xyonly_p2 = tf1_xyonly_pol4_y->GetParameter(2);
	float y_cor_xyonly_p3 = tf1_xyonly_pol4_y->GetParameter(3);
	float y_cor_xyonly_p4 = tf1_xyonly_pol4_y->GetParameter(4);

	cout<<"p0: "<<y_cor_xyonly_p0<<" ;  p1: "<<y_cor_xyonly_p1<<" ;  p2: "<<y_cor_xyonly_p2<<" ;  p3: "<<y_cor_xyonly_p3<<" ;  p4: "<<y_cor_xyonly_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_profile_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_profile_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_profile_ch"+ch1+".C").c_str());

	h2_deltaT_vs_y->Draw();
	p_deltaT_vs_y->SetMarkerColor( 4 );
        p_deltaT_vs_y->SetLineColor( 4 );
	p_deltaT_vs_y->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_scatter_and_profile_ch"+ch1+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_scatter_and_profile_ch"+ch1+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_scatter_and_profile_ch"+ch1+".C").c_str());
	
	// impact point dependency of the deltaT, after TW correction

	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_afterTW_vs_x = new TH2F("h2_deltaT_afterTW_vs_x","h2_deltaT_afterTW_vs_x", 72, x_low, x_high, 100, maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]:x_dut[0]>>h2_deltaT_afterTW_vs_x").c_str(),cut_noPos.c_str());
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterTW_vs_x").c_str(),cut_noPos.c_str());
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterTW_vs_x").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	h2_deltaT_afterTW_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_afterTW_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterTW_vs_x->SetTitle("");
	h2_deltaT_afterTW_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterTW_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterTW_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterTW_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterTW_vs_x->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_ch"+ch1+".C").c_str());

	TProfile * p_deltaT_afterTW_vs_x = h2_deltaT_afterTW_vs_x->ProfileX(); //new ("p_deltaT_afterTW_vs_x","p_deltaT_afterTW_vs_x",72, x_low, x_high);
	p_deltaT_afterTW_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	p_deltaT_afterTW_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_afterTW_vs_x->SetTitle("");
	
	p_deltaT_afterTW_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_afterTW_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_afterTW_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_afterTW_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	//p_deltaT_afterTW_vs_x->GetYaxis()->SetRangeUser(maxX_t-0.2, maxX_t+0.3);
       	p_deltaT_afterTW_vs_x->GetYaxis()->SetRangeUser(maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
       	p_deltaT_afterTW_vs_x->GetXaxis()->SetRangeUser(x_tile_low, x_tile_high);
        p_deltaT_afterTW_vs_x->SetMarkerStyle( 20 );
        p_deltaT_afterTW_vs_x->SetMarkerColor( 1 );
        p_deltaT_afterTW_vs_x->SetLineColor( 1 );
	p_deltaT_afterTW_vs_x->Draw();

	averageT_center = (p_deltaT_afterTW_vs_x->GetBinContent(x_bin_center) + p_deltaT_afterTW_vs_x->GetBinContent(x_bin_center-1) + p_deltaT_afterTW_vs_x->GetBinContent(x_bin_center+1))/3.0;
	averageT_left = (p_deltaT_afterTW_vs_x->GetBinContent(x_bin_left) + p_deltaT_afterTW_vs_x->GetBinContent(x_bin_left+1) + p_deltaT_afterTW_vs_x->GetBinContent(x_bin_left+1))/3.0;
	averageT_right = (p_deltaT_afterTW_vs_x->GetBinContent(x_bin_right) + p_deltaT_afterTW_vs_x->GetBinContent(x_bin_right-1) + p_deltaT_afterTW_vs_x->GetBinContent(x_bin_right-1))/3.0;

	//offsetXT_TWCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetXT_TWCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 

	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_afterTW_vs_x->GetBinContent(i);
		if(dt_this < all_xydt_min) 
		{
			all_xydt_min = dt_this;
			all_xybin_min = i;
		}
		
		if(dt_this > all_xydt_max) 
		{
			all_xydt_max = dt_this;
			all_xybin_max = i;
		}

	}
	offsetXT_TWCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;




	TF1 * tf1_pol4_x = new TF1("tf1_pol4_x","pol4", x_tile_low-1, x_tile_high+1.0);
	p_deltaT_afterTW_vs_x->Fit("tf1_pol4_x","","",x_tile_low_fit, x_tile_high_fit);
	float x_cor_p0 = tf1_pol4_x->GetParameter(0);
	float x_cor_p1 = tf1_pol4_x->GetParameter(1);
	float x_cor_p2 = tf1_pol4_x->GetParameter(2);
	float x_cor_p3 = tf1_pol4_x->GetParameter(3);
	float x_cor_p4 = tf1_pol4_x->GetParameter(4);

	cout<<"p0: "<<x_cor_p0<<" ;  p1: "<<x_cor_p1<<" ;  p2: "<<x_cor_p2<<" ;  p3: "<<x_cor_p3<<" ;  p4: "<<x_cor_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_profile_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_profile_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_profile_ch"+ch1+".C").c_str());

	h2_deltaT_afterTW_vs_x->Draw();
	p_deltaT_afterTW_vs_x->SetMarkerColor( 4 );
        p_deltaT_afterTW_vs_x->SetLineColor( 4 );
	p_deltaT_afterTW_vs_x->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_scatter_and_profile_ch"+ch1+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_scatter_and_profile_ch"+ch1+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_scatter_and_profile_ch"+ch1+".C").c_str());
	

	TH2F * h2_deltaT_afterTW_vs_y = new TH2F("h2_deltaT_afterTW_vs_y","h2_deltaT_afterTW_vs_y", 72, y_low, y_high, 100, maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterTW_vs_y").c_str(),cut_noPos.c_str());
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterTW_vs_y").c_str(),(cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	h2_deltaT_afterTW_vs_y->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_afterTW_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterTW_vs_y->SetTitle("");
	h2_deltaT_afterTW_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterTW_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterTW_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterTW_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterTW_vs_y->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_ch"+ch1+".C").c_str());

	TProfile * p_deltaT_afterTW_vs_y = h2_deltaT_afterTW_vs_y->ProfileX(); //new ("p_deltaT_afterTW_vs_y","p_deltaT_afterTW_vs_y",72, y_low, y_high);
	p_deltaT_afterTW_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	p_deltaT_afterTW_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_afterTW_vs_y->SetTitle("");
	
	p_deltaT_afterTW_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_afterTW_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_afterTW_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_afterTW_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_afterTW_vs_y->GetYaxis()->SetRangeUser(maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
       	p_deltaT_afterTW_vs_y->GetXaxis()->SetRangeUser(y_tile_low, y_tile_high);
        p_deltaT_afterTW_vs_y->SetMarkerStyle( 20 );
        p_deltaT_afterTW_vs_y->SetMarkerColor( 1 );
        p_deltaT_afterTW_vs_y->SetLineColor( 1 );
	p_deltaT_afterTW_vs_y->Draw();

	averageT_center = (p_deltaT_afterTW_vs_y->GetBinContent(y_bin_center) + p_deltaT_afterTW_vs_y->GetBinContent(y_bin_center-1) + p_deltaT_afterTW_vs_y->GetBinContent(y_bin_center+1))/3.0;
	averageT_left = (p_deltaT_afterTW_vs_y->GetBinContent(y_bin_left) + p_deltaT_afterTW_vs_y->GetBinContent(y_bin_left+1) + p_deltaT_afterTW_vs_y->GetBinContent(y_bin_left+1))/3.0;
	averageT_right = (p_deltaT_afterTW_vs_y->GetBinContent(y_bin_right) + p_deltaT_afterTW_vs_y->GetBinContent(y_bin_right-1) + p_deltaT_afterTW_vs_y->GetBinContent(y_bin_right-1))/3.0;

	//offsetYT_TWCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetYT_TWCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 
	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_afterTW_vs_y->GetBinContent(i);
		if(dt_this < all_xydt_min) 
		{
			all_xydt_min = dt_this;
			all_xybin_min = i;
		}
		
		if(dt_this > all_xydt_max) 
		{
			all_xydt_max = dt_this;
			all_xybin_max = i;
		}

	}
	offsetYT_TWCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;



	TF1 * tf1_pol4_y = new TF1("tf1_pol4_y","pol4", y_tile_low-1, y_tile_high+1.0);
	p_deltaT_afterTW_vs_y->Fit("tf1_pol4_y","","",y_tile_low_fit, y_tile_high_fit);
	float y_cor_p0 = tf1_pol4_y->GetParameter(0);
	float y_cor_p1 = tf1_pol4_y->GetParameter(1);
	float y_cor_p2 = tf1_pol4_y->GetParameter(2);
	float y_cor_p3 = tf1_pol4_y->GetParameter(3);
	float y_cor_p4 = tf1_pol4_y->GetParameter(4);

	cout<<"p0: "<<y_cor_p0<<" ;  p1: "<<y_cor_p1<<" ;  p2: "<<y_cor_p2<<" ;  p3: "<<y_cor_p3<<" ;  p4: "<<y_cor_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_profile_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_profile_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_profile_ch"+ch1+".C").c_str());

	h2_deltaT_afterTW_vs_y->Draw();
	p_deltaT_afterTW_vs_y->SetMarkerColor( 4 );
        p_deltaT_afterTW_vs_y->SetLineColor( 4 );
	p_deltaT_afterTW_vs_y->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_scatter_and_profile_ch"+ch1+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_scatter_and_profile_ch"+ch1+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_scatter_and_profile_ch"+ch1+".C").c_str());


	// impact point dependency of the deltaT_sipm, without TW correction, sipm
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_sipm_vs_x = new TH2F("h2_deltaT_sipm_vs_x","h2_deltaT_sipm_vs_x", 72, x_low, x_high, 100, maxX_t_sipm-0.2, maxX_t_sipm+0.3);
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] : x_dut[0]>>h2_deltaT_sipm_vs_x").c_str(),cut_sipm.c_str());
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] : x_dut[0]>>h2_deltaT_sipm_vs_x").c_str(),(cut_sipm+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	h2_deltaT_sipm_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_sipm_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_sipm_vs_x->SetTitle("");
	h2_deltaT_sipm_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_sipm_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_sipm_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_sipm_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_sipm_vs_x->Draw();
	
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_ch"+ch1+"_sipm.pdf").c_str());
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_ch"+ch1+"_sipm.png").c_str());
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_ch"+ch1+"_sipm.C").c_str());

	TProfile * p_deltaT_sipm_vs_x = h2_deltaT_sipm_vs_x->ProfileX(); 
	p_deltaT_sipm_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	p_deltaT_sipm_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_sipm_vs_x->SetTitle("");
	
	p_deltaT_sipm_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_sipm_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_sipm_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_sipm_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_sipm_vs_x->GetYaxis()->SetRangeUser(maxX_t_sipm-0.2, maxX_t_sipm+0.3);
       	p_deltaT_sipm_vs_x->GetXaxis()->SetRangeUser(x_sipm_low, x_sipm_high);
        p_deltaT_sipm_vs_x->SetMarkerStyle( 20 );
        p_deltaT_sipm_vs_x->SetMarkerColor( 1 );
        p_deltaT_sipm_vs_x->SetLineColor( 1 );
	p_deltaT_sipm_vs_x->Draw();

	TF1 * tf1_xyonly_pol4_sipm_x = new TF1("tf1_xyonly_pol4_sipm_x","pol4", x_sipm_low-1, x_sipm_high+1.0);
	p_deltaT_sipm_vs_x->Fit("tf1_xyonly_pol4_sipm_x","","",x_sipm_low_fit, x_sipm_high_fit);
	float x_cor_sipm_xyonly_p0 = tf1_xyonly_pol4_sipm_x->GetParameter(0);
	float x_cor_sipm_xyonly_p1 = tf1_xyonly_pol4_sipm_x->GetParameter(1);
	float x_cor_sipm_xyonly_p2 = tf1_xyonly_pol4_sipm_x->GetParameter(2);
	float x_cor_sipm_xyonly_p3 = tf1_xyonly_pol4_sipm_x->GetParameter(3);
	float x_cor_sipm_xyonly_p4 = tf1_xyonly_pol4_sipm_x->GetParameter(4);

	cout<<"p0: "<<x_cor_sipm_xyonly_p0<<" ;  p1: "<<x_cor_sipm_xyonly_p1<<" ;  p2: "<<x_cor_sipm_xyonly_p2<<" ;  p3: "<<x_cor_sipm_xyonly_p3<<" ;  p4: "<<x_cor_sipm_xyonly_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_profile_ch"+ch1+"_sipm.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_profile_ch"+ch1+"_sipm.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_profile_ch"+ch1+"_sipm.C").c_str());

	h2_deltaT_sipm_vs_x->GetXaxis()->SetRangeUser(x_sipm_low, x_sipm_high);
	h2_deltaT_sipm_vs_x->Draw();
	p_deltaT_sipm_vs_x->SetMarkerColor( 4 );
        p_deltaT_sipm_vs_x->SetLineColor( 4 );
	p_deltaT_sipm_vs_x->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_scatter_and_profile_ch"+ch1+"_sipm.pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_scatter_and_profile_ch"+ch1+"_sipm.png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_scatter_and_profile_ch"+ch1+"_sipm.C").c_str());
	
	TH2F * h2_deltaT_sipm_vs_y = new TH2F("h2_deltaT_sipm_vs_y","h2_deltaT_sipm_vs_y", 72, y_low, y_high, 100, maxX_t_sipm-0.2, maxX_t_sipm+0.3);
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] : y_dut[0]>>h2_deltaT_sipm_vs_y").c_str(),cut_sipm.c_str());
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] : y_dut[0]>>h2_deltaT_sipm_vs_y").c_str(), (cut_sipm+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	h2_deltaT_sipm_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	h2_deltaT_sipm_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_sipm_vs_y->SetTitle("");
	h2_deltaT_sipm_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_sipm_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_sipm_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_sipm_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_sipm_vs_y->Draw();
	
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_ch"+ch1+"_sipm.pdf").c_str());
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_ch"+ch1+"_sipm.png").c_str());
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_ch"+ch1+"_sipm.C").c_str());

	TProfile * p_deltaT_sipm_vs_y = h2_deltaT_sipm_vs_y->ProfileX(); //new ("p_deltaT_sipm_vs_y","p_deltaT_sipm_vs_y",72, y_low, y_high);
	p_deltaT_sipm_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	p_deltaT_sipm_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_sipm_vs_y->SetTitle("");
	
	p_deltaT_sipm_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_sipm_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_sipm_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_sipm_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_sipm_vs_y->GetYaxis()->SetRangeUser(maxX_t_sipm-0.2, maxX_t_sipm+0.3);
       	p_deltaT_sipm_vs_y->GetXaxis()->SetRangeUser(y_sipm_low, y_sipm_high);
        p_deltaT_sipm_vs_y->SetMarkerStyle( 20 );
        p_deltaT_sipm_vs_y->SetMarkerColor( 1 );
        p_deltaT_sipm_vs_y->SetLineColor( 1 );
	p_deltaT_sipm_vs_y->Draw();

	TF1 * tf1_xyonly_pol4_sipm_y = new TF1("tf1_xyonly_pol4_sipm_y","pol4", y_sipm_low-1, y_sipm_high+1.0);
	p_deltaT_sipm_vs_y->Fit("tf1_xyonly_pol4_sipm_y","","",y_sipm_low_fit, y_sipm_high_fit);
	float y_cor_sipm_xyonly_p0 = tf1_xyonly_pol4_sipm_y->GetParameter(0);
	float y_cor_sipm_xyonly_p1 = tf1_xyonly_pol4_sipm_y->GetParameter(1);
	float y_cor_sipm_xyonly_p2 = tf1_xyonly_pol4_sipm_y->GetParameter(2);
	float y_cor_sipm_xyonly_p3 = tf1_xyonly_pol4_sipm_y->GetParameter(3);
	float y_cor_sipm_xyonly_p4 = tf1_xyonly_pol4_sipm_y->GetParameter(4);

	cout<<"p0: "<<y_cor_sipm_xyonly_p0<<" ;  p1: "<<y_cor_sipm_xyonly_p1<<" ;  p2: "<<y_cor_sipm_xyonly_p2<<" ;  p3: "<<y_cor_sipm_xyonly_p3<<" ;  p4: "<<y_cor_sipm_xyonly_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_profile_ch"+ch1+"_sipm.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_profile_ch"+ch1+"_sipm.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_profile_ch"+ch1+"_sipm.C").c_str());

	h2_deltaT_sipm_vs_y->GetXaxis()->SetRangeUser(y_sipm_low, y_sipm_high);
	h2_deltaT_sipm_vs_y->Draw();
	p_deltaT_sipm_vs_y->SetMarkerColor( 4 );
        p_deltaT_sipm_vs_y->SetLineColor( 4 );
	p_deltaT_sipm_vs_y->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_scatter_and_profile_ch"+ch1+"_sipm.pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_scatter_and_profile_ch"+ch1+"_sipm.png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_scatter_and_profile_ch"+ch1+"_sipm.C").c_str());
	
	// impact point dependency of the deltaT_sipm, after TW correction, sipm

	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_sipm_afterTW_vs_x = new TH2F("h2_deltaT_sipm_afterTW_vs_x","h2_deltaT_sipm_afterTW_vs_x", 72, x_low, x_high, 100, maxX_t_sipm_TWcorr-0.2, maxX_t_sipm_TWcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]:x_dut[0]>>h2_deltaT_sipm_afterTW_vs_x").c_str(),cut_sipm.c_str());
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_sipm_afterTW_vs_x").c_str(),cut_sipm.c_str());
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_sipm_afterTW_vs_x").c_str(),(cut_sipm+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	h2_deltaT_sipm_afterTW_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_sipm_afterTW_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_sipm_afterTW_vs_x->SetTitle("");
	h2_deltaT_sipm_afterTW_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_sipm_afterTW_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_sipm_afterTW_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_sipm_afterTW_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_sipm_afterTW_vs_x->Draw();
	
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_ch"+ch1+"_sipm.pdf").c_str());
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_ch"+ch1+"_sipm.png").c_str());
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_ch"+ch1+"_sipm.C").c_str());

	TProfile * p_deltaT_sipm_afterTW_vs_x = h2_deltaT_sipm_afterTW_vs_x->ProfileX(); //new ("p_deltaT_sipm_afterTW_vs_x","p_deltaT_sipm_afterTW_vs_x",72, x_low, x_high);
	p_deltaT_sipm_afterTW_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	p_deltaT_sipm_afterTW_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_sipm_afterTW_vs_x->SetTitle("");
	
	p_deltaT_sipm_afterTW_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_sipm_afterTW_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_sipm_afterTW_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_sipm_afterTW_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	//p_deltaT_sipm_afterTW_vs_x->GetYaxis()->SetRangeUser(maxX_t_sipm-0.2, maxX_t_sipm+0.3);
       	p_deltaT_sipm_afterTW_vs_x->GetYaxis()->SetRangeUser(maxX_t_sipm_TWcorr-0.2, maxX_t_sipm_TWcorr+0.3);
       	p_deltaT_sipm_afterTW_vs_x->GetXaxis()->SetRangeUser(x_sipm_low, x_sipm_high);
        p_deltaT_sipm_afterTW_vs_x->SetMarkerStyle( 20 );
        p_deltaT_sipm_afterTW_vs_x->SetMarkerColor( 1 );
        p_deltaT_sipm_afterTW_vs_x->SetLineColor( 1 );
	p_deltaT_sipm_afterTW_vs_x->Draw();

	TF1 * tf1_pol4_sipm_x = new TF1("tf1_pol4_sipm_x","pol4", x_sipm_low-1, x_sipm_high+1.0);
	p_deltaT_sipm_afterTW_vs_x->Fit("tf1_pol4_sipm_x","","",x_sipm_low_fit, x_sipm_high_fit);
	float x_cor_sipm_p0 = tf1_pol4_sipm_x->GetParameter(0);
	float x_cor_sipm_p1 = tf1_pol4_sipm_x->GetParameter(1);
	float x_cor_sipm_p2 = tf1_pol4_sipm_x->GetParameter(2);
	float x_cor_sipm_p3 = tf1_pol4_sipm_x->GetParameter(3);
	float x_cor_sipm_p4 = tf1_pol4_sipm_x->GetParameter(4);

	cout<<"p0: "<<x_cor_sipm_p0<<" ;  p1: "<<x_cor_sipm_p1<<" ;  p2: "<<x_cor_sipm_p2<<" ;  p3: "<<x_cor_sipm_p3<<" ;  p4: "<<x_cor_sipm_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_profile_ch"+ch1+"_sipm.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_profile_ch"+ch1+"_sipm.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_profile_ch"+ch1+"_sipm.C").c_str());

	h2_deltaT_sipm_afterTW_vs_x->GetXaxis()->SetRangeUser(x_sipm_low, x_sipm_high);
	h2_deltaT_sipm_afterTW_vs_x->Draw();
	p_deltaT_sipm_afterTW_vs_x->SetMarkerColor( 4 );
        p_deltaT_sipm_afterTW_vs_x->SetLineColor( 4 );
	p_deltaT_sipm_afterTW_vs_x->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_scatter_and_profile_ch"+ch1+"_sipm.pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_scatter_and_profile_ch"+ch1+"_sipm.png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_scatter_and_profile_ch"+ch1+"_sipm.C").c_str());
	

	TH2F * h2_deltaT_sipm_afterTW_vs_y = new TH2F("h2_deltaT_sipm_afterTW_vs_y","h2_deltaT_sipm_afterTW_vs_y", 72, y_low, y_high, 100, maxX_t_sipm_TWcorr-0.2, maxX_t_sipm_TWcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_sipm_afterTW_vs_y").c_str(),cut_sipm.c_str());
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_sipm_afterTW_vs_y").c_str(),(cut_sipm+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	h2_deltaT_sipm_afterTW_vs_y->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_sipm_afterTW_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_sipm_afterTW_vs_y->SetTitle("");
	h2_deltaT_sipm_afterTW_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_sipm_afterTW_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_sipm_afterTW_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_sipm_afterTW_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_sipm_afterTW_vs_y->Draw();
	
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_ch"+ch1+"_sipm.pdf").c_str());
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_ch"+ch1+"_sipm.png").c_str());
	//myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_ch"+ch1+"_sipm.C").c_str());

	TProfile * p_deltaT_sipm_afterTW_vs_y = h2_deltaT_sipm_afterTW_vs_y->ProfileX(); //new ("p_deltaT_sipm_afterTW_vs_y","p_deltaT_sipm_afterTW_vs_y",72, y_low, y_high);
	p_deltaT_sipm_afterTW_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	p_deltaT_sipm_afterTW_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_sipm_afterTW_vs_y->SetTitle("");
	
	p_deltaT_sipm_afterTW_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_sipm_afterTW_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_sipm_afterTW_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_sipm_afterTW_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_sipm_afterTW_vs_y->GetYaxis()->SetRangeUser(maxX_t_sipm_TWcorr-0.2, maxX_t_sipm_TWcorr+0.3);
       	p_deltaT_sipm_afterTW_vs_y->GetXaxis()->SetRangeUser(y_sipm_low, y_sipm_high);
        p_deltaT_sipm_afterTW_vs_y->SetMarkerStyle( 20 );
        p_deltaT_sipm_afterTW_vs_y->SetMarkerColor( 1 );
        p_deltaT_sipm_afterTW_vs_y->SetLineColor( 1 );
	p_deltaT_sipm_afterTW_vs_y->Draw();

	TF1 * tf1_pol4_sipm_y = new TF1("tf1_pol4_sipm_y","pol4", y_sipm_low-1, y_sipm_high+1.0);
	p_deltaT_sipm_afterTW_vs_y->Fit("tf1_pol4_sipm_y","","",y_sipm_low_fit, y_sipm_high_fit);
	float y_cor_sipm_p0 = tf1_pol4_sipm_y->GetParameter(0);
	float y_cor_sipm_p1 = tf1_pol4_sipm_y->GetParameter(1);
	float y_cor_sipm_p2 = tf1_pol4_sipm_y->GetParameter(2);
	float y_cor_sipm_p3 = tf1_pol4_sipm_y->GetParameter(3);
	float y_cor_sipm_p4 = tf1_pol4_sipm_y->GetParameter(4);

	cout<<"p0: "<<y_cor_sipm_p0<<" ;  p1: "<<y_cor_sipm_p1<<" ;  p2: "<<y_cor_sipm_p2<<" ;  p3: "<<y_cor_sipm_p3<<" ;  p4: "<<y_cor_sipm_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_profile_ch"+ch1+"_sipm.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_profile_ch"+ch1+"_sipm.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_profile_ch"+ch1+"_sipm.C").c_str());

	h2_deltaT_sipm_afterTW_vs_y->GetXaxis()->SetRangeUser(y_sipm_low, y_sipm_high);
	h2_deltaT_sipm_afterTW_vs_y->Draw();
	p_deltaT_sipm_afterTW_vs_y->SetMarkerColor( 4 );
        p_deltaT_sipm_afterTW_vs_y->SetLineColor( 4 );
	p_deltaT_sipm_afterTW_vs_y->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_scatter_and_profile_ch"+ch1+"_sipm.pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_scatter_and_profile_ch"+ch1+"_sipm.png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_scatter_and_profile_ch"+ch1+"_sipm.C").c_str());
	

	//time resolution with impact point correction only
        TH1F * h_deltaT_XYcorr = new TH1F("h_deltaT_XYcorr","h_deltaT_XYcorr",100000, -1000.0, 1000.0);

        tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]- (" + std::to_string(x_cor_xyonly_p0)+" + "
+std::to_string(x_cor_xyonly_p1)+"*x_dut[0] + "+std::to_string(x_cor_xyonly_p2)+"*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p3)+"*x_dut[0]*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0]+"
+std::to_string(y_cor_xyonly_p0)+" + "
+std::to_string(y_cor_xyonly_p1)+"*y_dut[0] + "+std::to_string(y_cor_xyonly_p2)+"*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p3)+"*y_dut[0]*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0]"
+")>>h_deltaT_XYcorr").c_str(), cut.c_str());

        h_deltaT_XYcorr->SetTitle("");
        h_deltaT_XYcorr->SetMarkerStyle( 20 );
        h_deltaT_XYcorr->SetMarkerColor( 1 );
        h_deltaT_XYcorr->SetLineColor( 1 );
        h_deltaT_XYcorr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
        h_deltaT_XYcorr->GetYaxis()->SetTitle("Events");
        h_deltaT_XYcorr->SetTitle("");
        h_deltaT_XYcorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
        h_deltaT_XYcorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
        h_deltaT_XYcorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
        h_deltaT_XYcorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
        float maxY_t_XYcorr = h_deltaT_XYcorr->GetMaximum();
        float maxX_t_XYcorr = h_deltaT_XYcorr->GetBinCenter(h_deltaT_XYcorr->GetMaximumBin());
        h_deltaT_XYcorr->GetXaxis()->SetRangeUser(maxX_t_XYcorr-0.6, maxX_t_XYcorr+0.6);
        h_deltaT_XYcorr->Draw("E");

        float highDeltaT_XYcorr=maxX_t_XYcorr + fit_range_right + 0.02;//h_deltaT_XYcorr->GetBinCenter(h_deltaT_XYcorr->FindLastBinAbove(int(0.3*maxY_t)));
        float lowDeltaT_XYcorr=maxX_t_XYcorr - fit_range_left - 0.04;//h_deltaT_XYcorr->GetBinCenter(h_deltaT_XYcorr->FindFirstBinAbove(int(0.1*maxY_t)));
        //if(highDeltaT_XYcorr - maxX_t_XYcorr > 2.0*(maxX_t_XYcorr-lowDeltaT_XYcorr)) highDeltaT_XYcorr = maxX_t_XYcorr + (maxX_t_XYcorr - lowDeltaT_XYcorr);
        TF1 * tf1_gaus_XYcorr = new TF1("tf1_gaus_XYcorr","gaus", maxX_t_XYcorr - 1.0, maxX_t_XYcorr + 1.0);
        tf1_gaus_XYcorr->SetParameter(1, h_deltaT_XYcorr->GetMean());
        h_deltaT_XYcorr->Fit("tf1_gaus_XYcorr","","",lowDeltaT_XYcorr, highDeltaT_XYcorr);

	sigmaT_XYCor = tf1_gaus_XYcorr->GetParameter(2);	
	if(sigmaT_XYCor <  sigmaT_best) sigmaT_best = sigmaT_XYCor;

        gPad->Modified();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XYcorr_ch"+ch1+".pdf").c_str());
        myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XYcorr_ch"+ch1+".png").c_str());
        myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XYcorr_ch"+ch1+".C").c_str());


	//time resolution with impact point correction only, sipm
        TH1F * h_deltaT_sipm_XYcorr = new TH1F("h_deltaT_sipm_XYcorr","h_deltaT_sipm_XYcorr",100000, -1000.0, 1000.0);

        tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]- (" + std::to_string(x_cor_sipm_xyonly_p0)+" + "
+std::to_string(x_cor_sipm_xyonly_p1)+"*x_dut[0] + "+std::to_string(x_cor_sipm_xyonly_p2)+"*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_sipm_xyonly_p3)+"*x_dut[0]*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_sipm_xyonly_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0]+"
+std::to_string(y_cor_sipm_xyonly_p0)+" + "
+std::to_string(y_cor_sipm_xyonly_p1)+"*y_dut[0] + "+std::to_string(y_cor_sipm_xyonly_p2)+"*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_sipm_xyonly_p3)+"*y_dut[0]*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_sipm_xyonly_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0]"
+")>>h_deltaT_sipm_XYcorr").c_str(), cut_sipm.c_str());

        h_deltaT_sipm_XYcorr->SetTitle("");
        h_deltaT_sipm_XYcorr->SetMarkerStyle( 20 );
        h_deltaT_sipm_XYcorr->SetMarkerColor( 1 );
        h_deltaT_sipm_XYcorr->SetLineColor( 1 );
        h_deltaT_sipm_XYcorr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
        h_deltaT_sipm_XYcorr->GetYaxis()->SetTitle("Events");
        h_deltaT_sipm_XYcorr->SetTitle("");
        h_deltaT_sipm_XYcorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
        h_deltaT_sipm_XYcorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
        h_deltaT_sipm_XYcorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
        h_deltaT_sipm_XYcorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
        float maxY_t_sipm_XYcorr = h_deltaT_sipm_XYcorr->GetMaximum();
        float maxX_t_sipm_XYcorr = h_deltaT_sipm_XYcorr->GetBinCenter(h_deltaT_sipm_XYcorr->GetMaximumBin());
        h_deltaT_sipm_XYcorr->GetXaxis()->SetRangeUser(maxX_t_sipm_XYcorr-0.6, maxX_t_sipm_XYcorr+0.6);
        h_deltaT_sipm_XYcorr->Draw("E");

        float highDeltaT_sipm_XYcorr=maxX_t_sipm_XYcorr + fit_range_right; //h_deltaT_sipm_XYcorr->GetBinCenter(h_deltaT_sipm_XYcorr->FindLastBinAbove(int(0.3*maxY_t_sipm)));
        float lowDeltaT_sipm_XYcorr=maxX_t_sipm_XYcorr - fit_range_left;//h_deltaT_sipm_XYcorr->GetBinCenter(h_deltaT_sipm_XYcorr->FindFirstBinAbove(int(0.1*maxY_t_sipm)));
        //if(highDeltaT_sipm_XYcorr - maxX_t_sipm_XYcorr > 2.0*(maxX_t_sipm_XYcorr-lowDeltaT_sipm_XYcorr)) highDeltaT_sipm_XYcorr = maxX_t_sipm_XYcorr + (maxX_t_sipm_XYcorr - lowDeltaT_sipm_XYcorr);
        TF1 * tf1_gaus_sipm_XYcorr = new TF1("tf1_gaus_sipm_XYcorr","gaus", maxX_t_sipm_XYcorr - 1.0, maxX_t_sipm_XYcorr + 1.0);
        tf1_gaus_sipm_XYcorr->SetParameter(1, h_deltaT_sipm_XYcorr->GetMean());
        h_deltaT_sipm_XYcorr->Fit("tf1_gaus_sipm_XYcorr","","",lowDeltaT_sipm_XYcorr, highDeltaT_sipm_XYcorr);

	sigmaT_XYCor_sipm = tf1_gaus_sipm_XYcorr->GetParameter(2);	
	if(sigmaT_XYCor_sipm <  sigmaT_best_sipm) sigmaT_best_sipm = sigmaT_XYCor_sipm;

        gPad->Modified();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XYcorr_ch"+ch1+"_sipm.pdf").c_str());
        myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XYcorr_ch"+ch1+"_sipm.png").c_str());
        myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XYcorr_ch"+ch1+"_sipm.C").c_str());
	
	
	//time resolution with TW+impact point correction
	myC->SetGridy(0);
	myC->SetGridx(0);
	
	TH1F * h_deltaT_TWXYcorr = new TH1F("h_deltaT_TWXYcorr","h_deltaT_TWXYcorr",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_p0)+" + "+std::to_string(amp_cor_p1)+"*amp["+ch1+"] + "
+std::to_string(x_cor_p0)+ "+" +std::to_string(x_cor_p1)+"*x_dut[0] + "+std::to_string(x_cor_p2)+"*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_p3)+"*x_dut[0]*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0] + "
+std::to_string(y_cor_p0) + " + " + std::to_string(y_cor_p1)+"*y_dut[0] + "+std::to_string(y_cor_p2)+"*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_p3)+"*y_dut[0]*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0] "
+")>>h_deltaT_TWXYcorr").c_str(), cut.c_str());	

	h_deltaT_TWXYcorr->SetTitle("");
	h_deltaT_TWXYcorr->SetMarkerStyle( 20 );
	h_deltaT_TWXYcorr->SetMarkerColor( 1 );
	h_deltaT_TWXYcorr->SetLineColor( 1 );
	h_deltaT_TWXYcorr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h_deltaT_TWXYcorr->GetYaxis()->SetTitle("Events");
	h_deltaT_TWXYcorr->SetTitle("");
	h_deltaT_TWXYcorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_deltaT_TWXYcorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_deltaT_TWXYcorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_deltaT_TWXYcorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	float maxY_t_TWXYcorr = h_deltaT_TWXYcorr->GetMaximum();
	float maxX_t_TWXYcorr = h_deltaT_TWXYcorr->GetBinCenter(h_deltaT_TWXYcorr->GetMaximumBin());
       	h_deltaT_TWXYcorr->GetXaxis()->SetRangeUser(maxX_t_TWXYcorr-0.6, maxX_t_TWXYcorr+0.6);
        h_deltaT_TWXYcorr->Draw("E");

	float highDeltaT_TWXYcorr=maxX_t_TWXYcorr + fit_range_right + 0.02;//h_deltaT_TWXYcorr->GetBinCenter(h_deltaT_TWXYcorr->FindLastBinAbove(int(0.3*maxY_t)));
	float lowDeltaT_TWXYcorr=maxX_t_TWXYcorr - fit_range_left - 0.04;//h_deltaT_TWXYcorr->GetBinCenter(h_deltaT_TWXYcorr->FindFirstBinAbove(int(0.1*maxY_t)));
	//if(highDeltaT_TWXYcorr - maxX_t_TWXYcorr > 2.0*(maxX_t_TWXYcorr-lowDeltaT_TWXYcorr)) highDeltaT_TWXYcorr = maxX_t_TWXYcorr + (maxX_t_TWXYcorr - lowDeltaT_TWXYcorr);
	TF1 * tf1_gaus_TWXYcorr = new TF1("tf1_gaus_TWXYcorr","gaus", maxX_t_TWXYcorr - 1.0, maxX_t_TWXYcorr + 1.0);
	tf1_gaus_TWXYcorr->SetParameter(1, h_deltaT_TWXYcorr->GetMean());
	h_deltaT_TWXYcorr->Fit("tf1_gaus_TWXYcorr","","",lowDeltaT_TWXYcorr, highDeltaT_TWXYcorr);

	sigmaT_TWXYCor = tf1_gaus_TWXYcorr->GetParameter(2);	
	if(sigmaT_TWXYCor <  sigmaT_best) sigmaT_best = sigmaT_TWXYCor;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TW_then_XYcorr_ch"+ch1+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TW_then_XYcorr_ch"+ch1+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TW_then_XYcorr_ch"+ch1+".C").c_str());


	//time resolution with TW+impact point correction, sipm
	myC->SetGridy(0);
	myC->SetGridx(0);
	
	TH1F * h_deltaT_sipm_TWXYcorr = new TH1F("h_deltaT_sipm_TWXYcorr","h_deltaT_sipm_TWXYcorr",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_sipm_p0)+" + "+std::to_string(amp_cor_sipm_p1)+"*amp["+ch1+"] + "
+std::to_string(x_cor_sipm_p0)+ "+" +std::to_string(x_cor_sipm_p1)+"*x_dut[0] + "+std::to_string(x_cor_sipm_p2)+"*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_sipm_p3)+"*x_dut[0]*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_sipm_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0] + "
+std::to_string(y_cor_sipm_p0) + " + " + std::to_string(y_cor_sipm_p1)+"*y_dut[0] + "+std::to_string(y_cor_sipm_p2)+"*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_sipm_p3)+"*y_dut[0]*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_sipm_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0] "
+")>>h_deltaT_sipm_TWXYcorr").c_str(), cut_sipm.c_str());	

	h_deltaT_sipm_TWXYcorr->SetTitle("");
	h_deltaT_sipm_TWXYcorr->SetMarkerStyle( 20 );
	h_deltaT_sipm_TWXYcorr->SetMarkerColor( 1 );
	h_deltaT_sipm_TWXYcorr->SetLineColor( 1 );
	h_deltaT_sipm_TWXYcorr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h_deltaT_sipm_TWXYcorr->GetYaxis()->SetTitle("Events");
	h_deltaT_sipm_TWXYcorr->SetTitle("");
	h_deltaT_sipm_TWXYcorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_deltaT_sipm_TWXYcorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_deltaT_sipm_TWXYcorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_deltaT_sipm_TWXYcorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	float maxY_t_sipm_TWXYcorr = h_deltaT_sipm_TWXYcorr->GetMaximum();
	float maxX_t_sipm_TWXYcorr = h_deltaT_sipm_TWXYcorr->GetBinCenter(h_deltaT_sipm_TWXYcorr->GetMaximumBin());
       	h_deltaT_sipm_TWXYcorr->GetXaxis()->SetRangeUser(maxX_t_sipm_TWXYcorr-0.6, maxX_t_sipm_TWXYcorr+0.6);
        h_deltaT_sipm_TWXYcorr->Draw("E");

	float highDeltaT_sipm_TWXYcorr=maxX_t_sipm_TWXYcorr + fit_range_right;//h_deltaT_sipm_TWXYcorr->GetBinCenter(h_deltaT_sipm_TWXYcorr->FindLastBinAbove(int(0.3*maxY_t_sipm)));
	float lowDeltaT_sipm_TWXYcorr=maxX_t_sipm_TWXYcorr - fit_range_left;//h_deltaT_sipm_TWXYcorr->GetBinCenter(h_deltaT_sipm_TWXYcorr->FindFirstBinAbove(int(0.1*maxY_t_sipm)));
	//if(highDeltaT_sipm_TWXYcorr - maxX_t_sipm_TWXYcorr > 2.0*(maxX_t_sipm_TWXYcorr-lowDeltaT_sipm_TWXYcorr)) highDeltaT_sipm_TWXYcorr = maxX_t_sipm_TWXYcorr + (maxX_t_sipm_TWXYcorr - lowDeltaT_sipm_TWXYcorr);
	TF1 * tf1_gaus_sipm_TWXYcorr = new TF1("tf1_gaus_sipm_TWXYcorr","gaus", maxX_t_sipm_TWXYcorr - 1.0, maxX_t_sipm_TWXYcorr + 1.0);
	tf1_gaus_sipm_TWXYcorr->SetParameter(1, h_deltaT_sipm_TWXYcorr->GetMean());
	h_deltaT_sipm_TWXYcorr->Fit("tf1_gaus_sipm_TWXYcorr","","",lowDeltaT_sipm_TWXYcorr, highDeltaT_sipm_TWXYcorr);

	sigmaT_TWXYCor_sipm = tf1_gaus_sipm_TWXYcorr->GetParameter(2);	
	if(sigmaT_TWXYCor_sipm <  sigmaT_best_sipm) sigmaT_best_sipm = sigmaT_TWXYCor_sipm;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TW_then_XYcorr_ch"+ch1+"_sipm.pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TW_then_XYcorr_ch"+ch1+"_sipm.png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TW_then_XYcorr_ch"+ch1+"_sipm.C").c_str());


	cout<<"[tot]:  [sigmaT_noCor=] "<<sigmaT_noCor<<"   [sigmaT_TWCor=] "<<sigmaT_TWCor<<"   [sigmaT_XYCor=] "<<sigmaT_XYCor<<"   [sigmaT_TWXYCor=] "<<sigmaT_TWXYCor<<endl;
	cout<<"[tot]:  [sigmaT_noCor_sipm=] "<<sigmaT_noCor_sipm<<"   [sigmaT_TWCor_sipm=] "<<sigmaT_TWCor_sipm<<"   [sigmaT_XYCor_sipm=] "<<sigmaT_XYCor_sipm<<"   [sigmaT_TWXYCor_sipm=] "<<sigmaT_TWXYCor_sipm<<endl;

	cout<<"[tot]:  [offsetXT_noCor=] "<<offsetXT_noCor<<"   [offsetYT_noCor=] "<<offsetYT_noCor<<"   [offsetXT_TWCor=] "<<offsetXT_TWCor<<"   [offsetYT_TWCor] "<<offsetYT_TWCor<<endl;
	
	
	cout<<inFileName<<" totTable  "<<offsetXT_noCor<<" "<<offsetXT_TWCor<<" "<<offsetYT_noCor<<" "<<offsetYT_TWCor<<" "<<sigmaT_noCor<<" "<<sigmaT_TWCor<<" "<<sigmaT_XYCor<<" "<<sigmaT_TWXYCor<<" "<<sigmaT_noCor_sipm<<" "<<sigmaT_TWCor_sipm<<" "<<sigmaT_XYCor_sipm<<" "<<sigmaT_TWXYCor_sipm<<" "<<sigmaT_best<<" "<<sigmaT_best_sipm<<endl;
	//cout<<"[tot]:  [offsetXT_noCor_sipm=] "<<offsetXT_noCor_sipm<<"   [offsetYT_noCor_sipm=] "<<offsetYT_noCor_sipm<<"   [offsetXT_TWCor_sipm=] "<<offsetXT_TWCor_sipm<<"   [offsetYT_TWCor_sipm] "<<offsetYT_TWCor_sipm<<endl;

	//cout<<"[tot] [averageT_center=] "<<averageT_center<<"   [averageT_left=] "<<averageT_left<<"   [averageT_right=] "<<averageT_right<<endl;
}
