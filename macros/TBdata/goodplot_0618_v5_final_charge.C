
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
#include "TText.h"
#include "TLatex.h"


void goodplot_0618_v5_final_charge(const std::string& inFileName, const std::string& ch2  = "0", const std::string& ch1  = "16", const std::string& ch1_tl  = "16", const std::string& time_ch1  = "LP2_10", float amp_low_ch2 = 20.0, float amp_high_ch2 = 300.0, float amp_low = 200.0, float amp_high = 850.0, float x_tile_low = 20.0, float x_tile_high = 30.0, float y_tile_low = 5.0, float y_tile_high = 12.0, float x_sipm_low = 23.0, float x_sipm_high = 27.0, float y_sipm_low = 7.0, float y_sipm_high = 10.0, const std::string& analysis_tag="")
{
	//string ch1 = "15";
	//string ch2 = "9";
	
	//string time_ch1 = "LP2_10";
	string time_ch2 = "gaus_mean";

	float fit_range_left = 0.09;
	float fit_range_left_noRes = 0.3;
	float fit_range_right = 0.09;
	float fit_range_right_noRes = 0.3;

	float amp_low_fit = amp_low;
	float amp_high_fit = amp_high;

	//float amp_low_ch2 = 20.0;
	//float amp_high_ch2 = 300.0;

	//float x_center = 2.0*((int(0.5*(x_sipm_low+x_sipm_high)))/2)+1.0;
	float x_center = 2.0*((int(0.5*(x_tile_low+x_tile_high)))/2)+1.0;
	//float y_center = 2.0*((int(0.5*(y_sipm_low+y_sipm_high)))/2)+1.0;
	float y_center = 2.0*((int(0.5*(y_tile_low+y_tile_high)))/2)+1.0;

	float x_sample_low = x_center - 1.0;
	float x_sample_high = x_center + 1.0;
	float y_sample_low = y_center - 1.0;
	float y_sample_high = y_center + 1.0;
	
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


	//string inputDir = "/eos/cms/store/group/phys_susy/razor/Timing/Mar2018FNAL/OTSDAQ/CMSTiming/RECO/V3/combine";
	//string inputDir = "/eos/cms/store/group/phys_susy/razor/Timing/2018_06/data/VME/RECO/v3/combine/";
	//string inputDir = "/eos/uscms/store/user/cmstestbeam/BTL_ETL/2018_06/data/VME/RECO/v5_noMeas/";
	string inputDir = "/eos/cms/store/group/phys_susy/razor/Timing/2018_06/data/VME/RECO/v5_combine/";
	string plotDir = "plots_0618_v5_final/";
	//string plotDir = "/afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_June2018/";

	mkdir(plotDir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);


	float sigmaT_XYaverage_noCorr = 0.0;
	float e_sigmaT_XYaverage_noCorr = 0.0;
        float sigmaT_XYaverage_afterTW = 0.0;
        float e_sigmaT_XYaverage_afterTW = 0.0;

	
	float sigmaT_best = 9999.9;
	float sigmaT_best_sipm = 9999.9;

	float sigmaT_noCor = 0.0;
	float sigmaT_TWCor = 0.0;
	float sigmaT_XYCor = 0.0;
	float sigmaT_TWXYCor = 0.0;
	float sigmaT_XYTWCor = 0.0;

	float sigmaT_noCor_sipm = 0.0;
	float sigmaT_TWCor_sipm = 0.0;
	float sigmaT_XYCor_sipm = 0.0;
	float sigmaT_TWXYCor_sipm = 0.0;
	float sigmaT_XYTWCor_sipm = 0.0;

	float sigmaTerr_noCor = 0.0;
	float sigmaTerr_TWCor = 0.0;
	float sigmaTerr_XYCor = 0.0;
	float sigmaTerr_TWXYCor = 0.0;
	float sigmaTerr_XYTWCor = 0.0;

	float sigmaTerr_noCor_sipm = 0.0;
	float sigmaTerr_TWCor_sipm = 0.0;
	float sigmaTerr_XYCor_sipm = 0.0;
	float sigmaTerr_TWXYCor_sipm = 0.0;
	float sigmaTerr_XYTWCor_sipm = 0.0;


	float offsetXT_noCor = 0.0;
	float offsetYT_noCor = 0.0;
	float offsetXT_TWCor = 0.0;
	float offsetXT_XYCor = 0.0;
	float offsetXT_TWXYCor = 0.0;
	float offsetYT_TWCor = 0.0;
	float offsetYT_XYCor = 0.0;
	float offsetYT_TWXYCor = 0.0;

	float offsetXT_noCor_sipm = 0.0;
	float offsetYT_noCor_sipm = 0.0;
	float offsetXT_TWCor_sipm = 0.0;
	float offsetXT_XYCor_sipm = 0.0;
	float offsetXT_TWXYCor_sipm = 0.0;
	float offsetYT_TWCor_sipm = 0.0;
	float offsetYT_XYCor_sipm = 0.0;
	float offsetYT_TWXYCor_sipm = 0.0;


	cout<<"plotting run:"<<inFileName<<endl;
	
	string cut_noPos = "amp["+ch1+"]>"+std::to_string(amp_low)+" && amp["+ch1+"] < "+std::to_string(amp_high)+" && amp["+ch2+"]>"+std::to_string(amp_low_ch2)+" && amp["+ch2+"]<"+std::to_string(amp_high_ch2)+" && gaus_mean["+ch2+"]>1 && gaus_mean["+ch2+"]<100 && ntracks == 1 && chi2 > -0.1 && chi2 < 50.0";

        string cut = "amp["+ch1+"]>"+std::to_string(amp_low)+" && amp["+ch1+"] < "+std::to_string(amp_high)+" && amp["+ch2+"]>"+std::to_string(amp_low_ch2)+" && amp["+ch2+"]<"+std::to_string(amp_high_ch2)+" && x_dut[0] > "+std::to_string(x_tile_low)+" && x_dut[0]<"+std::to_string(x_tile_high)+" && y_dut[0]>"+std::to_string(y_tile_low)+" && y_dut[0]<"+std::to_string(y_tile_high)+"&& gaus_mean["+ch2+"]>1 && gaus_mean["+ch2+"]<100  && ntracks == 1 && chi2 > -0.1 && chi2 < 50.0";
        string cut_sample = "amp["+ch1+"]>"+std::to_string(amp_low)+" && amp["+ch1+"] < "+std::to_string(amp_high)+" && amp["+ch2+"]>"+std::to_string(amp_low_ch2)+" && amp["+ch2+"]<"+std::to_string(amp_high_ch2)+" && x_dut[0] > "+std::to_string(x_sample_low)+" && x_dut[0]<"+std::to_string(x_sample_high)+" && y_dut[0]>"+std::to_string(y_sample_low)+" && y_dut[0]<"+std::to_string(y_sample_high)+"&& gaus_mean["+ch2+"]>1 && gaus_mean["+ch2+"]<100  && ntracks == 1 && chi2 > -0.1 && chi2 < 50.0";
        string cut_sipm = "amp["+ch1+"]>"+std::to_string(amp_low)+" && amp["+ch1+"] < "+std::to_string(amp_high)+" && amp["+ch2+"]>"+std::to_string(amp_low_ch2)+" && amp["+ch2+"]<"+std::to_string(amp_high_ch2)+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)+"&& gaus_mean["+ch2+"]>1 && gaus_mean["+ch2+"]<100  && ntracks == 1 && chi2 > -0.1 && chi2 < 50.0";


	cout<<"cut --->  "<<cut<<endl;
	cout<<"cut_sample --->  "<<cut_sample<<endl;
	cout<<"cut_sipm --->  "<<cut_sipm<<endl;
	//ch1 and ch2 very basic cut
	string cut1 = "amp["+ch1+"]>10  && amp["+ch1+"] <900 && ntracks == 1 && chi2 > -0.1 && chi2 < 50.0 ";
	string cut2 = "amp["+ch2+"]>10  && amp["+ch2+"] <900 && ntracks == 1 && chi2 > -0.1 && chi2 < 50.0 ";
	string cut_shower = "amp["+ch1+"]>10 && amp["+ch1+"]<"+std::to_string(amp_high)+" && amp["+ch2+"]>10 && amp["+ch2+"]<250  && ntracks == 1 && chi2 > -0.1 && chi2 < 50.0";
 	
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);
	gStyle->SetPalette(1);

	TFile* inFile = TFile::Open((inputDir+"/DataVMETiming_Run"+inFileName+".root").c_str(),"READ");
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
	gStyle->SetOptFit(0);



	//intfull
	gStyle->SetOptStat(0);
        gStyle->SetOptFit(111);
        gStyle->SetPalette(1);

	myC->SetGridy(0);
	myC->SetGridx(0);
	TH1F * h_ch1_intfull = new TH1F("h_ch1_intfull","h_ch1_intfull",200,30, 900.0);
	tree->Draw(("-1.0*intfull["+ch1+"]>>h_ch1_intfull").c_str(), cut1.c_str());	
	float maxX_ch1_intfull = h_ch1_intfull->GetBinCenter(h_ch1_intfull->GetMaximumBin());
	float highch1_intfull=h_ch1_intfull->GetBinCenter(h_ch1_intfull->FindLastBinAbove(int(0.1*h_ch1_intfull->GetMaximum())));
	float low40ch1_intfull=h_ch1_intfull->GetBinCenter(h_ch1_intfull->FindFirstBinAbove(int(0.4*h_ch1_intfull->GetMaximum())));
	float maxX_intfull = highch1_intfull +200.0;
	h_ch1_intfull->SetTitle("");
	float maxY_intfull = 1.5*h_ch1_intfull->GetMaximum();
	h_ch1_intfull->SetMarkerStyle( 20 );
	h_ch1_intfull->SetMarkerColor( 2 );
	h_ch1_intfull->SetLineColor( 2 );
	h_ch1_intfull->GetXaxis()->SetTitle("Charge [pC]");
	h_ch1_intfull->GetYaxis()->SetTitle("Events");
	h_ch1_intfull->SetTitle("");
	h_ch1_intfull->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_ch1_intfull->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_ch1_intfull->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_ch1_intfull->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h_ch1_intfull->GetYaxis()->SetRangeUser(0.0,maxY_intfull  );
	h_ch1_intfull->GetXaxis()->SetRangeUser(0.0,maxX_intfull );
        h_ch1_intfull->Draw("E");
	
	TF1 * flandau_ch1_intfull = new TF1("flandau_ch1_intfull","[0]*TMath::Landau(x,[1],[2])", low40ch1_intfull, highch1_intfull);
	flandau_ch1_intfull->SetParameters(h_ch1_intfull->GetMaximum(), maxX_ch1_intfull, 1.0);
	
	flandau_ch1_intfull->SetLineColor(1);

	h_ch1_intfull->Fit("flandau_ch1_intfull", "Q", "", low40ch1_intfull, highch1_intfull);	

	gPad->Modified();
        gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_intfull_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_intfull_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_intfull_ch"+ch1+analysis_tag+".C").c_str());

	myC->SetGridy(0);
	myC->SetGridx(0);
	TH1F * h_ch1_integral = new TH1F("h_ch1_integral","h_ch1_integral",200,30, 900.0);
	tree->Draw(("-1.0*integral["+ch1+"]>>h_ch1_integral").c_str(), cut1.c_str());	
	float maxX_ch1_integral = h_ch1_integral->GetBinCenter(h_ch1_integral->GetMaximumBin());
	float highch1_integral=h_ch1_integral->GetBinCenter(h_ch1_integral->FindLastBinAbove(int(0.1*h_ch1_integral->GetMaximum())));
	float low40ch1_integral=h_ch1_integral->GetBinCenter(h_ch1_integral->FindFirstBinAbove(int(0.4*h_ch1_integral->GetMaximum())));
	float maxX_integral = highch1_integral +200.0;
	h_ch1_integral->SetTitle("");
	float maxY_integral = 1.5*h_ch1_integral->GetMaximum();
	h_ch1_integral->SetMarkerStyle( 20 );
	h_ch1_integral->SetMarkerColor( 2 );
	h_ch1_integral->SetLineColor( 2 );
	h_ch1_integral->GetXaxis()->SetTitle("Charge [pC]");
	h_ch1_integral->GetYaxis()->SetTitle("Events");
	h_ch1_integral->SetTitle("");
	h_ch1_integral->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_ch1_integral->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_ch1_integral->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_ch1_integral->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h_ch1_integral->GetYaxis()->SetRangeUser(0.0,maxY_integral  );
	h_ch1_integral->GetXaxis()->SetRangeUser(0.0,maxX_integral );
        h_ch1_integral->Draw("E");
	
	TF1 * flandau_ch1_integral = new TF1("flandau_ch1_integral","[0]*TMath::Landau(x,[1],[2])", low40ch1_integral, highch1_integral);
	flandau_ch1_integral->SetParameters(h_ch1_integral->GetMaximum(), maxX_ch1_integral, 1.0);
	
	flandau_ch1_integral->SetLineColor(1);

	h_ch1_integral->Fit("flandau_ch1_integral", "Q", "", low40ch1_integral, highch1_integral);	

	gPad->Modified();
        gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_integral_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_integral_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_integral_ch"+ch1+analysis_tag+".C").c_str());



}
