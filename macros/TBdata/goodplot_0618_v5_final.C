
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


void goodplot_0618_v5_final(const std::string& inFileName, const std::string& ch2  = "0", const std::string& ch1  = "16", const std::string& ch1_tl  = "16", const std::string& time_ch1  = "LP2_10", float amp_low_ch2 = 20.0, float amp_high_ch2 = 300.0, float amp_low = 200.0, float amp_high = 850.0, float x_tile_low = 20.0, float x_tile_high = 30.0, float y_tile_low = 5.0, float y_tile_high = 12.0, float x_sipm_low = 23.0, float x_sipm_high = 27.0, float y_sipm_low = 7.0, float y_sipm_high = 10.0, const std::string& analysis_tag="")
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
	string inputDir = "/eos/uscms/store/user/cmstestbeam/BTL_ETL/2018_06/data/VME/RECO/v5_noMeas/";
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

	//baseline_RMS
	myC->SetGridy(0);
	myC->SetGridx(0);
	TH1F * h_ch1baseline_RMS = new TH1F("h_ch1baseline_RMS","h_ch1baseline_RMS", 1000, 0.0, 10.0);

	tree->Draw(("baseline_RMS["+ch1+"]>>h_ch1baseline_RMS").c_str(), cut.c_str());	
	
	h_ch1baseline_RMS->SetTitle("");
	float maxY_baseline_RMS = 1.2*h_ch1baseline_RMS->GetMaximum();

	float maxX_ch1baseline_RMS = h_ch1baseline_RMS->GetBinCenter(h_ch1baseline_RMS->GetMaximumBin());
	float highch1baseline_RMS=h_ch1baseline_RMS->GetBinCenter(h_ch1baseline_RMS->FindLastBinAbove(int(0.1*h_ch1baseline_RMS->GetMaximum())));
	float max_ch1baseline_RMS = std::max(2.0*maxX_ch1baseline_RMS, highch1baseline_RMS+1.0);


	h_ch1baseline_RMS->SetMarkerStyle( 20 );
	h_ch1baseline_RMS->SetMarkerColor( 2 );
	h_ch1baseline_RMS->SetLineColor( 2 );
	h_ch1baseline_RMS->GetXaxis()->SetTitle("baseline RMS [mV]");
	h_ch1baseline_RMS->GetYaxis()->SetTitle("Events");
	h_ch1baseline_RMS->SetTitle("");
	h_ch1baseline_RMS->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_ch1baseline_RMS->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_ch1baseline_RMS->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_ch1baseline_RMS->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h_ch1baseline_RMS->GetYaxis()->SetRangeUser(0.0,maxY_baseline_RMS);
	h_ch1baseline_RMS->GetXaxis()->SetRangeUser(0.0,3.0);//max_ch1baseline_RMS );
        h_ch1baseline_RMS->Draw("histE");
	
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_baseline_RMS_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_baseline_RMS_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_baseline_RMS_ch"+ch1+analysis_tag+".C").c_str());


	//time resolution in xy bins
	myC->SetGridy(0);
	myC->SetGridx(0);

	TH2F * h2_reso_vs_xy =  new TH2F("h2_reso_vs_xy","h2_reso_vs_xy", 9, x_low, x_high, 9, y_low, y_high);
	TH2F * h2_meanAmp_vs_xy =  new TH2F("h2_meanAmp_vs_xy","h2_meanAmp_vs_xy", 9, x_low, x_high, 9, y_low, y_high);
	TH2F * h2_meanAmp_fit_vs_xy =  new TH2F("h2_meanAmp_fit_vs_xy","h2_meanAmp_fit_vs_xy", 9, x_low, x_high, 9, y_low, y_high);
	TH2F * h2_meanRisetime_vs_xy =  new TH2F("h2_meanRisetime_vs_xy","h2_meanRisetime_vs_xy", 9, x_low, x_high, 9, y_low, y_high);
	TH2F * h2_meanT_vs_xy =  new TH2F("h2_meanT_vs_xy","h2_meanT_vs_xy", 9, x_low, x_high, 9, y_low, y_high);
	
	float maxY_t_2D_mean = -9999.9;//50.0+h2_meanT_vs_xy->GetMaximum(); 
	float minY_t_2D_mean = 9999.9;//h2_meanT_vs_xy->GetMinimum()-50.0; 
	
	int N_usefulbins_XY_noCorr = 0;

	for(int ix = 1; ix<=9; ix++)
	{
		for(int iy=1;iy<=9;iy++)
		{
			float thisX_low = x_low + 2.0*(ix-1);
			float thisX_high = x_low + 2.0*ix;
			float thisY_low = y_low + 2.0*(iy-1);
			float thisY_high = y_low + 2.0*iy;
			
			TH1F * h_deltaT = new TH1F(("h_deltaT_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),("h_deltaT_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),100000, -1000.0, 1000.0);
			TH1F * h_meanAmp = new TH1F(("h_meanAmp_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),("h_meanAmp_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),400, amp_low-100.0, amp_high+200.0);
			TH1F * h_meanRisetime = new TH1F(("h_meanRisetime_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),("h_meanRisetime_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),100, 1.0, 3.0);
			tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]>>h_deltaT_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),(cut_noPos+" && x_dut[0]>"+std::to_string(thisX_low)+" && x_dut[0]<"+std::to_string(thisX_high) +" && y_dut[0]>"+std::to_string(thisY_low)+" && y_dut[0]<"+std::to_string(thisY_high)).c_str());

			tree->Draw(("amp["+ch1+"]>>h_meanAmp_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),(cut_noPos+" && x_dut[0]>"+std::to_string(thisX_low)+" && x_dut[0]<"+std::to_string(thisX_high) +" && y_dut[0]>"+std::to_string(thisY_low)+" && y_dut[0]<"+std::to_string(thisY_high)).c_str());

			tree->Draw(("(LP2_30["+ch1+"]-LP2_10["+ch1+"])*4.0 >> h_meanRisetime_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),(cut_noPos+" && x_dut[0]>"+std::to_string(thisX_low)+" && x_dut[0]<"+std::to_string(thisX_high) +" && y_dut[0]>"+std::to_string(thisY_low)+" && y_dut[0]<"+std::to_string(thisY_high)+" && (LP2_30["+ch1+"]-LP2_10["+ch1+"])*4.0 <3.0 && (LP2_30["+ch1+"]-LP2_10["+ch1+"])*4.0 >1.0").c_str());
			//if(h_deltaT->Integral() < 10.0) 
			if(thisX_high < x_tile_low || thisX_low > x_tile_high || thisY_high < y_tile_low || thisY_low > y_tile_high || h_deltaT->Integral() < 100.0)
			{
				h2_reso_vs_xy->SetBinContent(ix,iy,-999.9);
				h2_meanAmp_vs_xy->SetBinContent(ix,iy,-999.9);
				h2_meanAmp_fit_vs_xy->SetBinContent(ix,iy,-999.9);
				h2_meanRisetime_vs_xy->SetBinContent(ix,iy,-999.9);
				h2_meanT_vs_xy->SetBinContent(ix,iy,-99999.9);
				continue;	
			}	
			
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

			float highDeltaT=maxX_t+fit_range_right_noRes;//+0.02;//h_deltaT->GetBinCenter(h_deltaT->FindLastBinAbove(int(0.3*maxY_t)));
			float lowDeltaT=maxX_t-fit_range_left_noRes;//-0.08;//h_deltaT->GetBinCenter(h_deltaT->FindFirstBinAbove(int(0.1*maxY_t)));
			//if(highDeltaT - maxX_t > 2.0*(maxX_t-lowDeltaT)) highDeltaT = maxX_t + (maxX_t - lowDeltaT);
			TF1 * tf1_gaus = new TF1("tf1_gaus","gaus", maxX_t - 1.0, maxX_t + 1.0);
			tf1_gaus->SetParameter(1, h_deltaT->GetMean());
			h_deltaT->Fit("tf1_gaus","","",lowDeltaT, highDeltaT);
	
			//amplitude, landau fit
			float low40ch1E=h_meanAmp->GetBinCenter(h_meanAmp->FindFirstBinAbove(int(0.4*h_meanAmp->GetMaximum())));
			TF1 * flandau_amp_temp = new TF1("flandau_amp_temp","[0]*TMath::Landau(x,[1],[2])", low40ch1E, amp_high+200.0);
			flandau_amp_temp->SetParameters(h_meanAmp->GetMaximum(), h_meanAmp->GetBinCenter(h_meanAmp->GetMaximumBin()), 10.0);
			h_meanAmp->Fit("flandau_amp_temp","Q","",low40ch1E,amp_high+200.0);
			float meanAmp_fit = flandau_amp_temp->GetParameter(1);
			float meanAmperror_fit = flandau_amp_temp->GetParError(1);
				
			N_usefulbins_XY_noCorr ++;
			
			float sigmaT = tf1_gaus->GetParameter(2);	
			float meanT = tf1_gaus->GetParameter(1);	
			sigmaT_XYaverage_noCorr += 1000.0*sigmaT;
			float meanAmp = h_meanAmp->GetMean();
			float meanRisetime = h_meanRisetime->GetMean();
			float sigmaTerror = tf1_gaus->GetParError(2);	
			e_sigmaT_XYaverage_noCorr += 1000.0*sigmaTerror*1000.0*sigmaTerror;
			float meanTerror = tf1_gaus->GetParError(1);	
			float meanAmperror = h_meanAmp->GetMeanError();
			float meanRisetimeerror = h_meanRisetime->GetMeanError();

			h2_reso_vs_xy->SetBinContent(ix,iy,1000.0*sigmaT);
			h2_reso_vs_xy->SetBinError(ix,iy,1000.0*sigmaTerror);

			h2_meanT_vs_xy->SetBinContent(ix,iy,1000.0*meanT);
			h2_meanT_vs_xy->SetBinError(ix,iy,1000.0*meanTerror);

			h2_meanAmp_vs_xy->SetBinContent(ix,iy,meanAmp);
			h2_meanAmp_fit_vs_xy->SetBinContent(ix,iy,meanAmp_fit);
			h2_meanAmp_vs_xy->SetBinError(ix,iy,meanAmperror);
			h2_meanAmp_fit_vs_xy->SetBinError(ix,iy,meanAmperror_fit);

			h2_meanRisetime_vs_xy->SetBinContent(ix,iy,meanRisetime);
			h2_meanRisetime_vs_xy->SetBinError(ix,iy,meanRisetimeerror);



			if(1000.0*meanT > maxY_t_2D_mean) maxY_t_2D_mean = 1000.0*meanT;
			if(1000.0*meanT < minY_t_2D_mean) minY_t_2D_mean = 1000.0*meanT;
	
			gPad->Modified();
			gPad->Update();

			myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_x"+std::to_string(thisX_low)+"_y"+std::to_string(thisY_low)+"_deltaT_ch"+ch1+analysis_tag+".pdf").c_str());
			myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_x"+std::to_string(thisX_low)+"_y"+std::to_string(thisY_low)+"_deltaT_ch"+ch1+analysis_tag+".png").c_str());
			myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_x"+std::to_string(thisX_low)+"_y"+std::to_string(thisY_low)+"_deltaT_ch"+ch1+analysis_tag+".C").c_str());
			
		}
	}	
	for(int ix = 1; ix<=9; ix++)
	{
		for(int iy=1;iy<=9;iy++)
		{
			h2_meanT_vs_xy->SetBinContent(ix,iy,h2_meanT_vs_xy->GetBinContent(ix,iy)-minY_t_2D_mean + 0.01);
		}
	}
	
	sigmaT_XYaverage_noCorr = sigmaT_XYaverage_noCorr/(1.0*N_usefulbins_XY_noCorr);
	e_sigmaT_XYaverage_noCorr = sqrt(e_sigmaT_XYaverage_noCorr)/(1.0*N_usefulbins_XY_noCorr);

	
	myC->SetGridy(1);
	myC->SetGridx(1);


	//gStyle->SetPalette(104);
	gStyle->SetPaintTextFormat( "3.0f" );	
	h2_reso_vs_xy->Draw("COLZ,TEXT,ERROR");
	h2_reso_vs_xy->GetXaxis()->SetTitle("beam position X [mm]");
	h2_reso_vs_xy->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_reso_vs_xy->GetZaxis()->SetTitle("time resolution [ps]");
	float maxY_t_2D = std::min(200.0, 5.0+h2_reso_vs_xy->GetMaximum()); 
	h2_reso_vs_xy->GetZaxis()->SetRangeUser(20.0,80.0);//maxY_t_2D);
	h2_reso_vs_xy->SetTitle("");
	h2_reso_vs_xy->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_reso_vs_xy->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_reso_vs_xy->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_reso_vs_xy->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_reso_vs_xy->GetXaxis()->SetRangeUser(x_low+2.0, x_high-2.0);
	h2_reso_vs_xy->GetYaxis()->SetRangeUser(y_low+2.0, y_high-2.0);
	h2_reso_vs_xy->SetMarkerSize(2);
	
	TLatex *tlatex_xybins_noCorr =  new TLatex();
        tlatex_xybins_noCorr->SetNDC();
        tlatex_xybins_noCorr->SetTextAngle(0);
        tlatex_xybins_noCorr->SetTextColor(kBlack);
        tlatex_xybins_noCorr->SetTextFont(63);
        tlatex_xybins_noCorr->SetTextAlign(11);
        tlatex_xybins_noCorr->SetTextSize(30);
        tlatex_xybins_noCorr->DrawLatex(0.3, 0.95, ("average #sigma = "+std::to_string(int(ceil(sigmaT_XYaverage_noCorr))) +"#pm "+std::to_string(int(ceil(e_sigmaT_XYaverage_noCorr))) + " ps").c_str());

 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2Dtimereso_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2Dtimereso_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2Dtimereso_ch"+ch1+analysis_tag+".C").c_str());

	gStyle->SetPaintTextFormat( "4.0f" );	
	h2_meanT_vs_xy->Draw("COLZ,TEXT,ERROR");
	h2_meanT_vs_xy->GetXaxis()->SetTitle("beam position X [mm]");
	h2_meanT_vs_xy->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_meanT_vs_xy->GetZaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ps").c_str() );
	//float maxY_t_2D = std::min(200.0, 5.0+h2_meanT_vs_xy->GetMaximum()); 
	//h2_meanT_vs_xy->GetZaxis()->SetRangeUser(minY_t_2D_mean-50.0,maxY_t_2D_mean+50.0);
	h2_meanT_vs_xy->GetZaxis()->SetRangeUser(-10.0,300.0);//maxY_t_2D_mean-minY_t_2D_mean+50.0);
	h2_meanT_vs_xy->SetTitle("");
	h2_meanT_vs_xy->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_meanT_vs_xy->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_meanT_vs_xy->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_meanT_vs_xy->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_meanT_vs_xy->GetZaxis()->SetTitleOffset( 1.2 );
	h2_meanT_vs_xy->GetXaxis()->SetRangeUser(x_low+2.0, x_high-2.0 );
	h2_meanT_vs_xy->GetYaxis()->SetRangeUser(y_low+2.0, y_high-2.0 );
	h2_meanT_vs_xy->SetMarkerSize(2);
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DtimemeanT_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DtimemeanT_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DtimemeanT_ch"+ch1+analysis_tag+".C").c_str());

	gStyle->SetPaintTextFormat( "4.0f" );	
	h2_meanAmp_vs_xy->Draw("COLZ,TEXT,ERROR");
	h2_meanAmp_vs_xy->GetXaxis()->SetTitle("beam position X [mm]");
	h2_meanAmp_vs_xy->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_meanAmp_vs_xy->GetZaxis()->SetTitle("amplitude [mV]");
	h2_meanAmp_vs_xy->GetZaxis()->SetRangeUser(amp_low,amp_high);
	h2_meanAmp_vs_xy->SetTitle("");
	h2_meanAmp_vs_xy->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_meanAmp_vs_xy->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_meanAmp_vs_xy->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_meanAmp_vs_xy->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_meanAmp_vs_xy->GetZaxis()->SetTitleOffset( 1.2 );
	h2_meanAmp_vs_xy->GetXaxis()->SetRangeUser(x_low+2.0, x_high-2.0);
	h2_meanAmp_vs_xy->GetYaxis()->SetRangeUser(y_low+2.0, y_high-2.0);
	h2_meanAmp_vs_xy->SetMarkerSize(2);
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DmeanAmp_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DmeanAmp_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DmeanAmp_ch"+ch1+analysis_tag+".C").c_str());


	h2_meanAmp_fit_vs_xy->Draw("COLZ,TEXT,ERROR");
	h2_meanAmp_fit_vs_xy->GetXaxis()->SetTitle("beam position X [mm]");
	h2_meanAmp_fit_vs_xy->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_meanAmp_fit_vs_xy->GetZaxis()->SetTitle("amplitude [mV]");
	h2_meanAmp_fit_vs_xy->GetZaxis()->SetRangeUser(amp_low,amp_high);
	h2_meanAmp_fit_vs_xy->SetTitle("");
	h2_meanAmp_fit_vs_xy->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_meanAmp_fit_vs_xy->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_meanAmp_fit_vs_xy->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_meanAmp_fit_vs_xy->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_meanAmp_fit_vs_xy->GetZaxis()->SetTitleOffset( 1.2 );
	h2_meanAmp_fit_vs_xy->GetXaxis()->SetRangeUser(x_low+2.0, x_high-2.0);
	h2_meanAmp_fit_vs_xy->GetYaxis()->SetRangeUser(y_low+2.0, y_high-2.0);
	h2_meanAmp_fit_vs_xy->SetMarkerSize(2);
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DmeanAmp_Landau_fit_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DmeanAmp_Landau_fit_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DmeanAmp_Landau_fit_ch"+ch1+analysis_tag+".C").c_str());


	gStyle->SetPaintTextFormat( "4.2f" );	
	h2_meanRisetime_vs_xy->Draw("COLZ,TEXT,ERROR");
	h2_meanRisetime_vs_xy->GetXaxis()->SetTitle("beam position X [mm]");
	h2_meanRisetime_vs_xy->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_meanRisetime_vs_xy->GetZaxis()->SetTitle("risetime [ns]");
	h2_meanRisetime_vs_xy->GetZaxis()->SetRangeUser(1.4,2.5);
	h2_meanRisetime_vs_xy->SetTitle("");
	h2_meanRisetime_vs_xy->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_meanRisetime_vs_xy->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_meanRisetime_vs_xy->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_meanRisetime_vs_xy->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_meanRisetime_vs_xy->GetZaxis()->SetTitleOffset( 1.2 );
	h2_meanRisetime_vs_xy->GetXaxis()->SetRangeUser(x_low+2.0, x_high-2.0);
	h2_meanRisetime_vs_xy->GetYaxis()->SetRangeUser(y_low+2.0, y_high-2.0);
	h2_meanRisetime_vs_xy->SetMarkerSize(2);
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DmeanRisetime_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DmeanRisetime_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_2DmeanRisetime_ch"+ch1+analysis_tag+".C").c_str());



	//time resolution in amplitude bins
	gStyle->SetPalette(1);
	myC->SetGridy(0);
	myC->SetGridx(0);

	TH1F * h1_reso_vs_amp =  new TH1F("h1_reso_vs_amp","h1_reso_vs_amp", 10, amp_low, amp_high);
	
	for(int iamp = 1; iamp<=10; iamp++)
	{
		float thisAmp_low = amp_low + (iamp-1)*(amp_high-amp_low)/10;
		float thisAmp_high = amp_low + iamp*(amp_high-amp_low)/10;
		
		TH1F * h_deltaT = new TH1F(("h_deltaT_amp"+std::to_string(iamp)).c_str(),("h_deltaT_amp"+std::to_string(iamp)).c_str(),100000, -1000.0, 1000.0);
		tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]>>h_deltaT_amp"+std::to_string(iamp)).c_str(),(cut_sipm+" && amp["+ch1+"]>"+std::to_string(thisAmp_low)+" && amp["+ch1+"]<"+std::to_string(thisAmp_high)).c_str());

		if(h_deltaT->Integral() < 100.0) 
		{
			h1_reso_vs_amp->SetBinContent(iamp,-999.9);
			continue;	
		}	
		
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

		float highDeltaT=maxX_t+fit_range_right_noRes;//+0.02;//h_deltaT->GetBinCenter(h_deltaT->FindLastBinAbove(int(0.3*maxY_t)));
		float lowDeltaT=maxX_t-fit_range_left_noRes;//-0.08;//h_deltaT->GetBinCenter(h_deltaT->FindFirstBinAbove(int(0.1*maxY_t)));
		//if(highDeltaT - maxX_t > 2.0*(maxX_t-lowDeltaT)) highDeltaT = maxX_t + (maxX_t - lowDeltaT);
		TF1 * tf1_gaus = new TF1("tf1_gaus","gaus", maxX_t - 1.0, maxX_t + 1.0);
		tf1_gaus->SetParameter(1, h_deltaT->GetMean());
		h_deltaT->Fit("tf1_gaus","","",lowDeltaT, highDeltaT);
		
		float sigmaT = tf1_gaus->GetParameter(2);	
		float sigmaTerror = tf1_gaus->GetParError(2);	
		h1_reso_vs_amp->SetBinContent(iamp,sigmaT);
		h1_reso_vs_amp->SetBinError(iamp,sigmaTerror);

		gPad->Modified();
		gPad->Update();

		myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins"+std::to_string(thisAmp_low)+"_deltaT_ch"+ch1+analysis_tag+".pdf").c_str());
		myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins"+std::to_string(thisAmp_low)+"_deltaT_ch"+ch1+analysis_tag+".png").c_str());
		myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins"+std::to_string(thisAmp_low)+"_deltaT_ch"+ch1+analysis_tag+".C").c_str());
		
	}	

	h1_reso_vs_amp->SetMarkerStyle( 20 );
	h1_reso_vs_amp->SetMarkerColor( 1 );
	h1_reso_vs_amp->SetLineColor( 1 );
	h1_reso_vs_amp->Draw("E");
	h1_reso_vs_amp->GetXaxis()->SetTitle("Amplitude [mV]");
	h1_reso_vs_amp->GetYaxis()->SetTitle("time resolution [ns]");
	float maxY_t_ampbin = std::min(0.2, 0.01+h1_reso_vs_amp->GetMaximum()); 
	h1_reso_vs_amp->GetYaxis()->SetRangeUser(0.02,maxY_t_ampbin);
	h1_reso_vs_amp->SetTitle("");
	h1_reso_vs_amp->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h1_reso_vs_amp->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h1_reso_vs_amp->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h1_reso_vs_amp->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins_timereso_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins_timereso_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins_timereso_ch"+ch1+analysis_tag+".C").c_str());


	//time resolution in effective amplitude bins
	myC->SetGridy(0);
	myC->SetGridx(0);

	float effamp_low = 100.0*(int(0.01*amp_low/maxX_ch1baseline_RMS)-1);
	if(effamp_low < 0.0) effamp_low = 0.0;

	float effamp_high = 100.0*(int(0.01*amp_high/maxX_ch1baseline_RMS)+1);

	TH1F * h1_reso_vs_effamp =  new TH1F("h1_reso_vs_effamp","h1_reso_vs_effamp", 10, effamp_low, effamp_high);
	
	for(int ieffamp = 1; ieffamp<=10; ieffamp++)
	{
		float thisAmp_low = effamp_low + (ieffamp-1)*(effamp_high-effamp_low)/10.0;
		float thisAmp_high = effamp_low + ieffamp*(effamp_high-effamp_low)/10.0;
		
		TH1F * h_deltaT = new TH1F(("h_deltaT_effamp"+std::to_string(ieffamp)).c_str(),("h_deltaT_effamp"+std::to_string(ieffamp)).c_str(),100000, -1000.0, 1000.0);
		tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]>>h_deltaT_effamp"+std::to_string(ieffamp)).c_str(),(cut_sipm+" && amp["+ch1+"]/baseline_RMS["+ch1+"]>"+std::to_string(thisAmp_low)+" && amp["+ch1+"]/baseline_RMS["+ch1+"]<"+std::to_string(thisAmp_high)).c_str());

		if(h_deltaT->Integral() < 100.0) 
		{
			h1_reso_vs_effamp->SetBinContent(ieffamp,-999.9);
			continue;	
		}	
		
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

		float highDeltaT=maxX_t+fit_range_right;//+0.02;//h_deltaT->GetBinCenter(h_deltaT->FindLastBinAbove(int(0.3*maxY_t)));
		float lowDeltaT=maxX_t-fit_range_left;//-0.08;//h_deltaT->GetBinCenter(h_deltaT->FindFirstBinAbove(int(0.1*maxY_t)));
		//if(highDeltaT - maxX_t > 2.0*(maxX_t-lowDeltaT)) highDeltaT = maxX_t + (maxX_t - lowDeltaT);
		TF1 * tf1_gaus = new TF1("tf1_gaus","gaus", maxX_t - 1.0, maxX_t + 1.0);
		tf1_gaus->SetParameter(1, h_deltaT->GetMean());
		h_deltaT->Fit("tf1_gaus","","",lowDeltaT, highDeltaT);
		
		float sigmaT = tf1_gaus->GetParameter(2);	
		float sigmaTerror = tf1_gaus->GetParError(2);	
		h1_reso_vs_effamp->SetBinContent(ieffamp,sigmaT);
		h1_reso_vs_effamp->SetBinError(ieffamp,sigmaTerror);

		gPad->Modified();
		gPad->Update();

		myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins"+std::to_string(thisAmp_low)+"_deltaT_ch"+ch1+analysis_tag+".pdf").c_str());
		myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins"+std::to_string(thisAmp_low)+"_deltaT_ch"+ch1+analysis_tag+".png").c_str());
		myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins"+std::to_string(thisAmp_low)+"_deltaT_ch"+ch1+analysis_tag+".C").c_str());
		
	}	

	h1_reso_vs_effamp->SetMarkerStyle( 20 );
	h1_reso_vs_effamp->SetMarkerColor( 1 );
	h1_reso_vs_effamp->SetLineColor( 1 );
	h1_reso_vs_effamp->Draw("E");
	h1_reso_vs_effamp->GetXaxis()->SetTitle("A/#sigma");
	h1_reso_vs_effamp->GetYaxis()->SetTitle("time resolution [ns]");
	float maxY_t_effampbin = std::min(0.2, 0.01+h1_reso_vs_effamp->GetMaximum()); 
	h1_reso_vs_effamp->GetYaxis()->SetRangeUser(0.02,maxY_t_effampbin);
	h1_reso_vs_effamp->SetTitle("");
	h1_reso_vs_effamp->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h1_reso_vs_effamp->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h1_reso_vs_effamp->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h1_reso_vs_effamp->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins_timereso_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins_timereso_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins_timereso_ch"+ch1+analysis_tag+".C").c_str());


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
	h2_beamSpotch1->GetZaxis()->SetRangeUser(amp_low, amp_high );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch1+analysis_tag+".C").c_str());

	h2_beamSpotch1Num->Draw("colz");
	
	h2_beamSpotch1Num->GetXaxis()->SetTitle("beam position X [mm]");
	h2_beamSpotch1Num->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_beamSpotch1Num->GetZaxis()->SetTitle("Events");
	h2_beamSpotch1Num->SetTitle("");
	h2_beamSpotch1Num->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_beamSpotch1Num->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_beamSpotch1Num->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_beamSpotch1Num->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_Num_withCut_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_Num_withCut_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_Num_withCut_ch"+ch1+analysis_tag+".C").c_str());

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

	/*
	//risetime vs. x and y
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_risetimeVsXYch1 = new TH2F("h2_risetimeVsXYch1","h2_risetimeVsXYch1",50,x_low, x_high,50,y_low, y_high);
	TH2F * h2_risetimeVsXYch1Num = new TH2F("h2_risetimeVsXYch1Num","h2_risetimeVsXYch1Num",50,x_low, x_high,50,y_low,y_high);
	tree->Draw("y_dut[0]:x_dut[0]>>h2_risetimeVsXYch1Num",cut_noPos.c_str());

	tree->Draw("y_dut[0]:x_dut[0]>>h2_risetimeVsXYch1",("(LP2_30["+ch1+"]-LP2_10["+ch1+"])*4.0 *("+cut_noPos+")").c_str());
	h2_risetimeVsXYch1->Divide(h2_risetimeVsXYch1Num);
	h2_risetimeVsXYch1->Draw("colz");
	
	h2_risetimeVsXYch1->GetXaxis()->SetTitle("beam position X [mm]");
	h2_risetimeVsXYch1->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_risetimeVsXYch1->GetZaxis()->SetTitle("risetime [ns]");
	h2_risetimeVsXYch1->GetZaxis()->SetRangeUser(1.0,3.0);
	h2_risetimeVsXYch1->SetTitle("");
	h2_risetimeVsXYch1->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_risetimeVsXYch1->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_risetimeVsXYch1->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_risetimeVsXYch1->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetimeVsXY_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetimeVsXY_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetimeVsXY_ch"+ch1+analysis_tag+".C").c_str());
	*/

	//chi2 vs. x and y
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_chi2VsXYch1 = new TH2F("h2_chi2VsXYch1","h2_chi2VsXYch1",50,x_low, x_high,50,y_low, y_high);
	TH2F * h2_chi2VsXYch1Num = new TH2F("h2_chi2VsXYch1Num","h2_chi2VsXYch1Num",50,x_low, x_high,50,y_low,y_high);
	tree->Draw("y_dut[0]:x_dut[0]>>h2_chi2VsXYch1Num",cut_noPos.c_str());

	tree->Draw("y_dut[0]:x_dut[0]>>h2_chi2VsXYch1",("chi2*("+cut_noPos+")").c_str());
	h2_chi2VsXYch1->Divide(h2_chi2VsXYch1Num);
	h2_chi2VsXYch1->Draw("colz");
	
	h2_chi2VsXYch1->GetXaxis()->SetTitle("beam position X [mm]");
	h2_chi2VsXYch1->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_chi2VsXYch1->GetZaxis()->SetTitle("#chi^{2}");
	//h2_chi2VsXYch1->GetZaxis()->SetRangeUser(0.0,20.0);
	h2_chi2VsXYch1->SetTitle("");
	h2_chi2VsXYch1->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_chi2VsXYch1->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_chi2VsXYch1->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_chi2VsXYch1->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_chi2VsXY_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_chi2VsXY_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_chi2VsXY_ch"+ch1+analysis_tag+".C").c_str());


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

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch1+analysis_tag+".C").c_str());


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

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch1+analysis_tag+".C").c_str());

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
 
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch2+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch2+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_beamSpot_ch"+ch2+analysis_tag+".C").c_str());

	
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

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch2+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch2+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_x_ch"+ch2+analysis_tag+".C").c_str());

	//ch2 amp vs y position
	TH2F * h2_amp_vs_y_ch2 = new TH2F("h2_amp_vs_y_ch2","h2_amp_vs_y_ch2",72,x_low, x_high,100,0.0, 600.0);
	tree->Draw(("amp["+ch2+"]:y_dut[0]>>h2_amp_vs_y_ch2").c_str(),cut_shower.c_str());

	TProfile * p_amp_vs_y_ch2 = h2_amp_vs_y_ch2->ProfileX(); 
	p_amp_vs_y_ch2->GetXaxis()->SetTitle("beam position Y [mm]");
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

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch2+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch2+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amp_vs_y_ch"+ch2+analysis_tag+".C").c_str());


	//amplitude
	
	gStyle->SetOptFit(0);

	myC->SetGridy(0);
	myC->SetGridx(0);
	TH1F * h_ch1E = new TH1F("h_ch1E","h_ch1E",200,30, 900.0);
	TH1F * h_ch2E = new TH1F("h_ch2E","h_ch2E",200,30, 900.0);

	tree->Draw(("amp["+ch1+"]>>h_ch1E").c_str(), cut1.c_str());	
	tree->Draw(("amp["+ch2+"]>>h_ch2E").c_str(), cut2.c_str());	
	

	float maxX_ch1E = h_ch1E->GetBinCenter(h_ch1E->GetMaximumBin());
	float highch1E=h_ch1E->GetBinCenter(h_ch1E->FindLastBinAbove(int(0.1*h_ch1E->GetMaximum())));
	float low40ch1E=h_ch1E->GetBinCenter(h_ch1E->FindFirstBinAbove(int(0.4*h_ch1E->GetMaximum())));
	//float maxX_ch1 = std::max(2.0*maxX_ch1E, highch1E+200.0);
	float maxX_ch1 = std::max(amp_high+200.0, highch1E+200.0);

	float maxX_ch2E = h_ch2E->GetBinCenter(h_ch2E->GetMaximumBin());
	float highch2E=h_ch2E->GetBinCenter(h_ch2E->FindLastBinAbove(int(0.1*h_ch2E->GetMaximum())));
	float low40ch2E=h_ch2E->GetBinCenter(h_ch2E->FindFirstBinAbove(int(0.4*h_ch2E->GetMaximum())));
	float high40ch2E = maxX_ch2E+(maxX_ch2E-low40ch2E);
	float maxX_ch2 = std::max(2.0*maxX_ch2E, highch2E+200.0);

	float maxX_E = std::max(maxX_ch1, maxX_ch2);


	//scale
	h_ch1E->Scale(1.0/h_ch1E->GetMaximum());
	h_ch2E->Scale(1.0/h_ch2E->GetMaximum());

	h_ch1E->SetTitle("");
	float maxY_E = 1.5*std::max(h_ch1E->GetMaximum(), h_ch2E->GetMaximum());


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
        h_ch1E->Draw("E");
	
	h_ch2E->Draw("sameE");

	TF1 * flandau_ch1E = new TF1("flandau_ch1E","[0]*TMath::Landau(x,[1],[2])", low40ch1E, amp_high);
	//TF1 * flandau_ch2E = new TF1("flandau_ch2E","[0]*TMath::Landau(x,[1],[2])", low40ch2E, amp_high_ch2);
	TF1 * fgaus_ch2E = new TF1("fgaus_ch2E","gaus",low40ch2E , high40ch2E);
	flandau_ch1E->SetParameters(h_ch1E->GetMaximum(), maxX_ch1E, 1.0);
	//flandau_ch2E->SetParameters(h_ch2E->GetMaximum(), maxX_ch2E, 1.0);
	fgaus_ch2E->SetParameter(1, maxX_ch2E);
	
	flandau_ch1E->SetLineColor(1);
	//flandau_ch2E->SetLineColor(1);
	fgaus_ch2E->SetLineColor(1);

	h_ch1E->Fit("flandau_ch1E", "Q", "", low40ch1E, amp_high);	
	//h_ch2E->Fit("flandau_ch2E", "Q", "", lowch2E, amp_high_ch2);	
	h_ch2E->Fit("fgaus_ch2E", "Q", "", low40ch2E, high40ch2E);

	gPad->Modified();
        gPad->Update();
	
	float peak_amp_ch1 = flandau_ch1E->GetParameter(1);	
	//float peak_amp_ch2 = flandau_ch2E->GetParameter(1);	
	float peak_amp_ch2 = fgaus_ch2E->GetParameter(1);	
	
	TLegend * leg_E  = new TLegend (0.4,0.7,0.85,0.9);
	leg_E->SetBorderSize(0);
	leg_E->SetTextSize(0.06);
	leg_E->SetLineColor(1);
	leg_E->SetLineStyle(1);
	leg_E->SetLineWidth(1);
	leg_E->SetFillColor(0);
	leg_E->SetFillStyle(1001);
		
	leg_E->AddEntry(h_ch1E, ("ch"+ch1+", A="+std::to_string(int(peak_amp_ch1))+"mV").c_str(), "lp");
	leg_E->AddEntry(h_ch2E, ("ch"+ch2+", A="+std::to_string(int(peak_amp_ch2))+"mV").c_str(), "lp");
	leg_E->Draw();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_amplitude_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amplitude_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amplitude_ch"+ch1+analysis_tag+".C").c_str());

	gStyle->SetOptFit(111);
	//amplitude scatter plot
	TH2F * h2_amp_2D = new TH2F("h2_amp_2D","h2_amp_2D", 400, 0,1000,400,0,600);
	tree->Draw(("amp["+ch2+"]:amp["+ch1+"]>>h2_amp_2D").c_str(), (cut1+"&&"+cut2).c_str());	
	h2_amp_2D->GetXaxis()->SetTitle(("ch"+ch1+" amplitude [mV]").c_str());
	h2_amp_2D->GetYaxis()->SetTitle(("ch"+ch2+" amplitude [mV]").c_str());
	h2_amp_2D->SetTitle("");
	h2_amp_2D->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_amp_2D->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_amp_2D->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_amp_2D->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_amp_2D->Draw();
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amplitude_scatter_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amplitude_scatter_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_amplitude_scatter_ch"+ch1+analysis_tag+".C").c_str());

	//risetime
	myC->SetGridy(0);
	myC->SetGridx(0);
	TH1F * h_ch1Risetime = new TH1F("h_ch1Risetime","h_ch1Risetime", 2000, 0.0, 10.0);

	tree->Draw(("(LP2_30["+ch1+"]-LP2_10["+ch1+"])*4.0 >>h_ch1Risetime").c_str(), cut.c_str());	
	
	h_ch1Risetime->SetTitle("");
	float maxY_Risetime = 1.2*h_ch1Risetime->GetMaximum();

	float maxX_ch1Risetime = h_ch1Risetime->GetBinCenter(h_ch1Risetime->GetMaximumBin());
	float highch1Risetime=h_ch1Risetime->GetBinCenter(h_ch1Risetime->FindLastBinAbove(int(0.1*h_ch1Risetime->GetMaximum())));
	float max_ch1Risetime = std::max(2.0*maxX_ch1Risetime, highch1Risetime+1.0);


	h_ch1Risetime->SetMarkerStyle( 20 );
	h_ch1Risetime->SetMarkerColor( 2 );
	h_ch1Risetime->SetLineColor( 2 );
	h_ch1Risetime->GetXaxis()->SetTitle("risetime [ns]");
	h_ch1Risetime->GetYaxis()->SetTitle("Events");
	h_ch1Risetime->SetTitle("");
	h_ch1Risetime->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_ch1Risetime->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_ch1Risetime->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_ch1Risetime->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h_ch1Risetime->GetYaxis()->SetRangeUser(0.0,maxY_Risetime);
	h_ch1Risetime->GetXaxis()->SetRangeUser(0.0,4.0);//max_ch1Risetime );
        h_ch1Risetime->Draw("histE");
	
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_ch"+ch1+analysis_tag+".C").c_str());



	// time resolution, LYSO area
	TH1F * h_deltaT = new TH1F("h_deltaT","h_deltaT",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]>>h_deltaT").c_str(), cut.c_str());	
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
	sigmaTerr_noCor = tf1_gaus->GetParError(2);	
	if(sigmaT_noCor <  sigmaT_best) sigmaT_best = sigmaT_noCor;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_ch"+ch1+analysis_tag+".C").c_str());

	//amplitude dependency of the deltaT
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_vs_amp = new TH2F("h2_deltaT_vs_amp","h2_deltaT_vs_amp", 100, amp_low, amp_high, 100, maxX_t-0.6, maxX_t+0.6);
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]:amp["+ch1+"]>>h2_deltaT_vs_amp").c_str(),cut.c_str());
	h2_deltaT_vs_amp->GetXaxis()->SetTitle("amplitude [mV]");
	h2_deltaT_vs_amp->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_vs_amp->SetTitle("");
	h2_deltaT_vs_amp->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_vs_amp->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_vs_amp->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_vs_amp->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_vs_amp->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_ch"+ch1+analysis_tag+".C").c_str());

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
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_profile_ch"+ch1+analysis_tag+".C").c_str());

	//time resolution after time walk correction
	myC->SetGridy(0);
	myC->SetGridx(0);
	
	TH1F * h_deltaT_TWcorr = new TH1F("h_deltaT_TWcorr","h_deltaT_TWcorr",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_p0)+" + "+std::to_string(amp_cor_p1)+"*amp["+ch1+"])>>h_deltaT_TWcorr").c_str(), cut.c_str());	

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
	sigmaTerr_TWCor = tf1_gaus_TWcorr->GetParError(2);	
	if(sigmaT_TWCor <  sigmaT_best) sigmaT_best = sigmaT_TWCor;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TWcorr_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TWcorr_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TWcorr_ch"+ch1+analysis_tag+".C").c_str());


	// impact point dependency of the risetime, for visual effects
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_risetime_vs_x = new TH2F("h2_risetime_vs_x","h2_risetime_vs_x", 72, x_low, x_high, 100, maxX_ch1Risetime-0.5, maxX_ch1Risetime+0.5);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] : x_dut[0]>>h2_risetime_vs_x").c_str(),cut_noPos.c_str());
	tree->Draw(("(LP2_30["+ch1+"]-LP2_10["+ch1+"])*4.0 : x_dut[0]>>h2_risetime_vs_x").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	h2_risetime_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	h2_risetime_vs_x->GetYaxis()->SetTitle("risetime [ns]");
	h2_risetime_vs_x->SetTitle("");
	h2_risetime_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_risetime_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_risetime_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_risetime_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_risetime_vs_x->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamX_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamX_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamX_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_risetime_vs_x = h2_risetime_vs_x->ProfileX(); 
	p_risetime_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	p_risetime_vs_x->GetYaxis()->SetTitle("risetime [ns]");
	p_risetime_vs_x->SetTitle("");
	
	p_risetime_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_risetime_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_risetime_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_risetime_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_risetime_vs_x->GetYaxis()->SetRangeUser(maxX_ch1Risetime-0.5, maxX_ch1Risetime+0.5);
       	p_risetime_vs_x->GetXaxis()->SetRangeUser(x_tile_low, x_tile_high);
        p_risetime_vs_x->SetMarkerStyle( 20 );
        p_risetime_vs_x->SetMarkerColor( 1 );
        p_risetime_vs_x->SetLineColor( 1 );
	p_risetime_vs_x->Draw();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamX_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamX_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamX_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_risetime_vs_x->Draw();
	p_risetime_vs_x->SetMarkerColor( 4 );
        p_risetime_vs_x->SetLineColor( 4 );
	p_risetime_vs_x->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	
	TH2F * h2_risetime_vs_y = new TH2F("h2_risetime_vs_y","h2_risetime_vs_y", 72, y_low, y_high, 100, maxX_ch1Risetime-0.5, maxX_ch1Risetime+0.5);
	tree->Draw(("(LP2_30["+ch1+"]-LP2_10["+ch1+"])*4.0 : y_dut[0]>>h2_risetime_vs_y").c_str(), (cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	h2_risetime_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	h2_risetime_vs_y->GetYaxis()->SetTitle("risetime [ns]");
	h2_risetime_vs_y->SetTitle("");
	h2_risetime_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_risetime_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_risetime_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_risetime_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_risetime_vs_y->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamY_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamY_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamY_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_risetime_vs_y = h2_risetime_vs_y->ProfileX(); //new ("p_risetime_vs_y","p_risetime_vs_y",72, y_low, y_high);
	p_risetime_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	p_risetime_vs_y->GetYaxis()->SetTitle("risetime [ns]");
	p_risetime_vs_y->SetTitle("");
	
	p_risetime_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_risetime_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_risetime_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_risetime_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_risetime_vs_y->GetYaxis()->SetRangeUser(maxX_ch1Risetime-0.5, maxX_ch1Risetime+0.5);
       	p_risetime_vs_y->GetXaxis()->SetRangeUser(y_tile_low, y_tile_high);
        p_risetime_vs_y->SetMarkerStyle( 20 );
        p_risetime_vs_y->SetMarkerColor( 1 );
        p_risetime_vs_y->SetLineColor( 1 );
	p_risetime_vs_y->Draw();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamY_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamY_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamY_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_risetime_vs_y->Draw();
	p_risetime_vs_y->SetMarkerColor( 4 );
        p_risetime_vs_y->SetLineColor( 4 );
	p_risetime_vs_y->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_risetime_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	
	
	// impact point dependency of the deltaT, without TW correction, for visual effects
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_vs_x = new TH2F("h2_deltaT_vs_x","h2_deltaT_vs_x", 72, x_low, x_high, 100, maxX_t-0.2, maxX_t+0.3);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] : x_dut[0]>>h2_deltaT_vs_x").c_str(),cut_noPos.c_str());
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] : x_dut[0]>>h2_deltaT_vs_x").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	h2_deltaT_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_vs_x->SetTitle("");
	h2_deltaT_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_vs_x->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_ch"+ch1+analysis_tag+".C").c_str());

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
		if (dt_this < maxX_t-0.2 || dt_this > maxX_t+0.3) continue;
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
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_vs_x->Draw();
	p_deltaT_vs_x->SetMarkerColor( 4 );
        p_deltaT_vs_x->SetLineColor( 4 );
	p_deltaT_vs_x->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	
	TH2F * h2_deltaT_vs_y = new TH2F("h2_deltaT_vs_y","h2_deltaT_vs_y", 72, y_low, y_high, 100, maxX_t-0.2, maxX_t+0.3);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] : y_dut[0]>>h2_deltaT_vs_y").c_str(),cut_noPos.c_str());
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] : y_dut[0]>>h2_deltaT_vs_y").c_str(), (cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	h2_deltaT_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	h2_deltaT_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_vs_y->SetTitle("");
	h2_deltaT_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_vs_y->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_ch"+ch1+analysis_tag+".C").c_str());

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
		if (dt_this < maxX_t-0.2 || dt_this > maxX_t+0.3) continue;
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
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_vs_y->Draw();
	p_deltaT_vs_y->SetMarkerColor( 4 );
        p_deltaT_vs_y->SetLineColor( 4 );
	p_deltaT_vs_y->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	
	// impact point dependency of the deltaT, after TW correction, for visual effects

	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_afterTW_vs_x = new TH2F("h2_deltaT_afterTW_vs_x","h2_deltaT_afterTW_vs_x", 72, x_low, x_high, 100, maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]:x_dut[0]>>h2_deltaT_afterTW_vs_x").c_str(),cut_noPos.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterTW_vs_x").c_str(),cut_noPos.c_str());
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterTW_vs_x").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	h2_deltaT_afterTW_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_afterTW_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterTW_vs_x->SetTitle("");
	h2_deltaT_afterTW_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterTW_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterTW_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterTW_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterTW_vs_x->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_ch"+ch1+analysis_tag+".C").c_str());

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
		if (dt_this < maxX_t_TWcorr-0.2 || dt_this > maxX_t_TWcorr+0.3) continue;
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
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_afterTW_vs_x->Draw();
	p_deltaT_afterTW_vs_x->SetMarkerColor( 4 );
        p_deltaT_afterTW_vs_x->SetLineColor( 4 );
	p_deltaT_afterTW_vs_x->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	

	TH2F * h2_deltaT_afterTW_vs_y = new TH2F("h2_deltaT_afterTW_vs_y","h2_deltaT_afterTW_vs_y", 72, y_low, y_high, 100, maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterTW_vs_y").c_str(),cut_noPos.c_str());
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterTW_vs_y").c_str(),(cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	h2_deltaT_afterTW_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	h2_deltaT_afterTW_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterTW_vs_y->SetTitle("");
	h2_deltaT_afterTW_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterTW_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterTW_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterTW_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterTW_vs_y->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_ch"+ch1+analysis_tag+".C").c_str());

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
		if (dt_this < maxX_t_TWcorr-0.2 || dt_this > maxX_t_TWcorr+0.3) continue;
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
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_afterTW_vs_y->Draw();
	p_deltaT_afterTW_vs_y->SetMarkerColor( 4 );
        p_deltaT_afterTW_vs_y->SetLineColor( 4 );
	p_deltaT_afterTW_vs_y->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());


	// impact point dependency of the deltaT, without TW correction, for real correction
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_vs_x_forCorr = new TH2F("h2_deltaT_vs_x_forCorr","h2_deltaT_vs_x_forCorr", 72, x_low, x_high, 100, maxX_t-0.2, maxX_t+0.3);
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] : x_dut[0]>>h2_deltaT_vs_x_forCorr").c_str(),cut.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] : x_dut[0]>>h2_deltaT_vs_x_forCorr").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	h2_deltaT_vs_x_forCorr->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_vs_x_forCorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_vs_x_forCorr->SetTitle("");
	h2_deltaT_vs_x_forCorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_vs_x_forCorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_vs_x_forCorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_vs_x_forCorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_vs_x_forCorr->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_forCorr_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_forCorr_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_forCorr_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_deltaT_vs_x_forCorr = h2_deltaT_vs_x_forCorr->ProfileX(); 
	p_deltaT_vs_x_forCorr->GetXaxis()->SetTitle("beam position X [mm]");
	p_deltaT_vs_x_forCorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_vs_x_forCorr->SetTitle("");
	
	p_deltaT_vs_x_forCorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_vs_x_forCorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_vs_x_forCorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_vs_x_forCorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_vs_x_forCorr->GetYaxis()->SetRangeUser(maxX_t-0.2, maxX_t+0.3);
       	p_deltaT_vs_x_forCorr->GetXaxis()->SetRangeUser(x_tile_low, x_tile_high);
        p_deltaT_vs_x_forCorr->SetMarkerStyle( 20 );
        p_deltaT_vs_x_forCorr->SetMarkerColor( 1 );
        p_deltaT_vs_x_forCorr->SetLineColor( 1 );
	p_deltaT_vs_x_forCorr->Draw();

	averageT_center = (p_deltaT_vs_x_forCorr->GetBinContent(x_bin_center) + p_deltaT_vs_x_forCorr->GetBinContent(x_bin_center-1) + p_deltaT_vs_x_forCorr->GetBinContent(x_bin_center+1))/3.0;
	averageT_left = (p_deltaT_vs_x_forCorr->GetBinContent(x_bin_left) + p_deltaT_vs_x_forCorr->GetBinContent(x_bin_left+1) + p_deltaT_vs_x_forCorr->GetBinContent(x_bin_left+1))/3.0;
	averageT_right = (p_deltaT_vs_x_forCorr->GetBinContent(x_bin_right) + p_deltaT_vs_x_forCorr->GetBinContent(x_bin_right-1) + p_deltaT_vs_x_forCorr->GetBinContent(x_bin_right-1))/3.0;

	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_vs_x_forCorr->GetBinContent(i);
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
	//offsetXT_noCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;


	//offsetXT_noCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetXT_noCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 
	
	TF1 * tf1_xyonly_pol4_forCorr_x = new TF1("tf1_xyonly_pol4_forCorr_x","pol4", x_tile_low-1, x_tile_high+1.0);
	p_deltaT_vs_x_forCorr->Fit("tf1_xyonly_pol4_forCorr_x","","",x_tile_low_fit, x_tile_high_fit);
	x_cor_xyonly_p0 = tf1_xyonly_pol4_forCorr_x->GetParameter(0);
	x_cor_xyonly_p1 = tf1_xyonly_pol4_forCorr_x->GetParameter(1);
	x_cor_xyonly_p2 = tf1_xyonly_pol4_forCorr_x->GetParameter(2);
	x_cor_xyonly_p3 = tf1_xyonly_pol4_forCorr_x->GetParameter(3);
	x_cor_xyonly_p4 = tf1_xyonly_pol4_forCorr_x->GetParameter(4);

	cout<<"p0: "<<x_cor_xyonly_p0<<" ;  p1: "<<x_cor_xyonly_p1<<" ;  p2: "<<x_cor_xyonly_p2<<" ;  p3: "<<x_cor_xyonly_p3<<" ;  p4: "<<x_cor_xyonly_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_forCorr_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_forCorr_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_forCorr_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_vs_x_forCorr->Draw();
	p_deltaT_vs_x_forCorr->SetMarkerColor( 4 );
        p_deltaT_vs_x_forCorr->SetLineColor( 4 );
	p_deltaT_vs_x_forCorr->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamX_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	
	TH2F * h2_deltaT_vs_y_forCorr = new TH2F("h2_deltaT_vs_y_forCorr","h2_deltaT_vs_y_forCorr", 72, y_low, y_high, 100, maxX_t-0.2, maxX_t+0.3);
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] : y_dut[0]>>h2_deltaT_vs_y_forCorr").c_str(),cut.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] : y_dut[0]>>h2_deltaT_vs_y_forCorr").c_str(), (cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	h2_deltaT_vs_y_forCorr->GetXaxis()->SetTitle("beam position Y [mm]");
	h2_deltaT_vs_y_forCorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_vs_y_forCorr->SetTitle("");
	h2_deltaT_vs_y_forCorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_vs_y_forCorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_vs_y_forCorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_vs_y_forCorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_vs_y_forCorr->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_forCorr_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_forCorr_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_forCorr_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_deltaT_vs_y_forCorr = h2_deltaT_vs_y_forCorr->ProfileX(); //new ("p_deltaT_vs_y_forCorr","p_deltaT_vs_y_forCorr",72, y_low, y_high);
	p_deltaT_vs_y_forCorr->GetXaxis()->SetTitle("beam position Y [mm]");
	p_deltaT_vs_y_forCorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_vs_y_forCorr->SetTitle("");
	
	p_deltaT_vs_y_forCorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_vs_y_forCorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_vs_y_forCorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_vs_y_forCorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_vs_y_forCorr->GetYaxis()->SetRangeUser(maxX_t-0.2, maxX_t+0.3);
       	p_deltaT_vs_y_forCorr->GetXaxis()->SetRangeUser(y_tile_low, y_tile_high);
        p_deltaT_vs_y_forCorr->SetMarkerStyle( 20 );
        p_deltaT_vs_y_forCorr->SetMarkerColor( 1 );
        p_deltaT_vs_y_forCorr->SetLineColor( 1 );
	p_deltaT_vs_y_forCorr->Draw();

	averageT_center = (p_deltaT_vs_y_forCorr->GetBinContent(y_bin_center) + p_deltaT_vs_y_forCorr->GetBinContent(y_bin_center-1) + p_deltaT_vs_y_forCorr->GetBinContent(y_bin_center+1))/3.0;
	averageT_left = (p_deltaT_vs_y_forCorr->GetBinContent(y_bin_left) + p_deltaT_vs_y_forCorr->GetBinContent(y_bin_left+1) + p_deltaT_vs_y_forCorr->GetBinContent(y_bin_left+1))/3.0;
	averageT_right = (p_deltaT_vs_y_forCorr->GetBinContent(y_bin_right) + p_deltaT_vs_y_forCorr->GetBinContent(y_bin_right-1) + p_deltaT_vs_y_forCorr->GetBinContent(y_bin_right-1))/3.0;

	//offsetYT_noCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetYT_noCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 
	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_vs_y_forCorr->GetBinContent(i);
		if (dt_this < maxX_t-0.2 || dt_this > maxX_t+0.3) continue;
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
	//offsetYT_noCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;



	TF1 * tf1_xyonly_pol4_forCorr_y = new TF1("tf1_xyonly_pol4_forCorr_y","pol4", y_tile_low-1, y_tile_high+1.0);
	p_deltaT_vs_y_forCorr->Fit("tf1_xyonly_pol4_forCorr_y","","",y_tile_low_fit, y_tile_high_fit);
	y_cor_xyonly_p0 = tf1_xyonly_pol4_forCorr_y->GetParameter(0);
	y_cor_xyonly_p1 = tf1_xyonly_pol4_forCorr_y->GetParameter(1);
	y_cor_xyonly_p2 = tf1_xyonly_pol4_forCorr_y->GetParameter(2);
	y_cor_xyonly_p3 = tf1_xyonly_pol4_forCorr_y->GetParameter(3);
	y_cor_xyonly_p4 = tf1_xyonly_pol4_forCorr_y->GetParameter(4);

	cout<<"p0: "<<y_cor_xyonly_p0<<" ;  p1: "<<y_cor_xyonly_p1<<" ;  p2: "<<y_cor_xyonly_p2<<" ;  p3: "<<y_cor_xyonly_p3<<" ;  p4: "<<y_cor_xyonly_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_forCorr_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_forCorr_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_forCorr_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_vs_y_forCorr->Draw();
	p_deltaT_vs_y_forCorr->SetMarkerColor( 4 );
        p_deltaT_vs_y_forCorr->SetLineColor( 4 );
	p_deltaT_vs_y_forCorr->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_beamY_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	
	// impact point dependency of the deltaT, after TW correction, for real correction 

	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_afterTW_vs_x_forCorr = new TH2F("h2_deltaT_afterTW_vs_x_forCorr","h2_deltaT_afterTW_vs_x_forCorr", 72, x_low, x_high, 100, maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]:x_dut[0]>>h2_deltaT_afterTW_vs_x_forCorr").c_str(),cut_noPos.c_str());
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterTW_vs_x_forCorr").c_str(),cut.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterTW_vs_x_forCorr").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	h2_deltaT_afterTW_vs_x_forCorr->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_afterTW_vs_x_forCorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterTW_vs_x_forCorr->SetTitle("");
	h2_deltaT_afterTW_vs_x_forCorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterTW_vs_x_forCorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterTW_vs_x_forCorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterTW_vs_x_forCorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterTW_vs_x_forCorr->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_forCorr_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_forCorr_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_forCorr_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_deltaT_afterTW_vs_x_forCorr = h2_deltaT_afterTW_vs_x_forCorr->ProfileX(); //new ("p_deltaT_afterTW_vs_x_forCorr","p_deltaT_afterTW_vs_x_forCorr",72, x_low, x_high);
	p_deltaT_afterTW_vs_x_forCorr->GetXaxis()->SetTitle("beam position X [mm]");
	p_deltaT_afterTW_vs_x_forCorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_afterTW_vs_x_forCorr->SetTitle("");
	
	p_deltaT_afterTW_vs_x_forCorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_afterTW_vs_x_forCorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_afterTW_vs_x_forCorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_afterTW_vs_x_forCorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	//p_deltaT_afterTW_vs_x_forCorr->GetYaxis()->SetRangeUser(maxX_t-0.2, maxX_t+0.3);
       	p_deltaT_afterTW_vs_x_forCorr->GetYaxis()->SetRangeUser(maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
       	p_deltaT_afterTW_vs_x_forCorr->GetXaxis()->SetRangeUser(x_tile_low, x_tile_high);
        p_deltaT_afterTW_vs_x_forCorr->SetMarkerStyle( 20 );
        p_deltaT_afterTW_vs_x_forCorr->SetMarkerColor( 1 );
        p_deltaT_afterTW_vs_x_forCorr->SetLineColor( 1 );
	p_deltaT_afterTW_vs_x_forCorr->Draw();

	averageT_center = (p_deltaT_afterTW_vs_x_forCorr->GetBinContent(x_bin_center) + p_deltaT_afterTW_vs_x_forCorr->GetBinContent(x_bin_center-1) + p_deltaT_afterTW_vs_x_forCorr->GetBinContent(x_bin_center+1))/3.0;
	averageT_left = (p_deltaT_afterTW_vs_x_forCorr->GetBinContent(x_bin_left) + p_deltaT_afterTW_vs_x_forCorr->GetBinContent(x_bin_left+1) + p_deltaT_afterTW_vs_x_forCorr->GetBinContent(x_bin_left+1))/3.0;
	averageT_right = (p_deltaT_afterTW_vs_x_forCorr->GetBinContent(x_bin_right) + p_deltaT_afterTW_vs_x_forCorr->GetBinContent(x_bin_right-1) + p_deltaT_afterTW_vs_x_forCorr->GetBinContent(x_bin_right-1))/3.0;

	//offsetXT_TWCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetXT_TWCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 

	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_afterTW_vs_x_forCorr->GetBinContent(i);
		if (dt_this < maxX_t_TWcorr-0.2 || dt_this > maxX_t_TWcorr+0.3) continue;
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
	//offsetXT_TWCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;




	TF1 * tf1_pol4_forCorr_x = new TF1("tf1_pol4_forCorr_x","pol4", x_tile_low-1, x_tile_high+1.0);
	p_deltaT_afterTW_vs_x_forCorr->Fit("tf1_pol4_forCorr_x","","",x_tile_low_fit, x_tile_high_fit);
	x_cor_p0 = tf1_pol4_forCorr_x->GetParameter(0);
	x_cor_p1 = tf1_pol4_forCorr_x->GetParameter(1);
	x_cor_p2 = tf1_pol4_forCorr_x->GetParameter(2);
	x_cor_p3 = tf1_pol4_forCorr_x->GetParameter(3);
	x_cor_p4 = tf1_pol4_forCorr_x->GetParameter(4);

	cout<<"p0: "<<x_cor_p0<<" ;  p1: "<<x_cor_p1<<" ;  p2: "<<x_cor_p2<<" ;  p3: "<<x_cor_p3<<" ;  p4: "<<x_cor_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_forCorr_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_forCorr_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_forCorr_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_afterTW_vs_x_forCorr->Draw();
	p_deltaT_afterTW_vs_x_forCorr->SetMarkerColor( 4 );
        p_deltaT_afterTW_vs_x_forCorr->SetLineColor( 4 );
	p_deltaT_afterTW_vs_x_forCorr->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamX_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	

	TH2F * h2_deltaT_afterTW_vs_y_forCorr = new TH2F("h2_deltaT_afterTW_vs_y_forCorr","h2_deltaT_afterTW_vs_y_forCorr", 72, y_low, y_high, 100, maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterTW_vs_y_forCorr").c_str(),cut.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterTW_vs_y_forCorr").c_str(),(cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	h2_deltaT_afterTW_vs_y_forCorr->GetXaxis()->SetTitle("beam position Y [mm]");
	h2_deltaT_afterTW_vs_y_forCorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterTW_vs_y_forCorr->SetTitle("");
	h2_deltaT_afterTW_vs_y_forCorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterTW_vs_y_forCorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterTW_vs_y_forCorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterTW_vs_y_forCorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterTW_vs_y_forCorr->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_forCorr_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_forCorr_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_forCorr_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_deltaT_afterTW_vs_y_forCorr = h2_deltaT_afterTW_vs_y_forCorr->ProfileX(); //new ("p_deltaT_afterTW_vs_y_forCorr","p_deltaT_afterTW_vs_y_forCorr",72, y_low, y_high);
	p_deltaT_afterTW_vs_y_forCorr->GetXaxis()->SetTitle("beam position Y [mm]");
	p_deltaT_afterTW_vs_y_forCorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_afterTW_vs_y_forCorr->SetTitle("");
	
	p_deltaT_afterTW_vs_y_forCorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_afterTW_vs_y_forCorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_afterTW_vs_y_forCorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_afterTW_vs_y_forCorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_afterTW_vs_y_forCorr->GetYaxis()->SetRangeUser(maxX_t_TWcorr-0.2, maxX_t_TWcorr+0.3);
       	p_deltaT_afterTW_vs_y_forCorr->GetXaxis()->SetRangeUser(y_tile_low, y_tile_high);
        p_deltaT_afterTW_vs_y_forCorr->SetMarkerStyle( 20 );
        p_deltaT_afterTW_vs_y_forCorr->SetMarkerColor( 1 );
        p_deltaT_afterTW_vs_y_forCorr->SetLineColor( 1 );
	p_deltaT_afterTW_vs_y_forCorr->Draw();

	averageT_center = (p_deltaT_afterTW_vs_y_forCorr->GetBinContent(y_bin_center) + p_deltaT_afterTW_vs_y_forCorr->GetBinContent(y_bin_center-1) + p_deltaT_afterTW_vs_y_forCorr->GetBinContent(y_bin_center+1))/3.0;
	averageT_left = (p_deltaT_afterTW_vs_y_forCorr->GetBinContent(y_bin_left) + p_deltaT_afterTW_vs_y_forCorr->GetBinContent(y_bin_left+1) + p_deltaT_afterTW_vs_y_forCorr->GetBinContent(y_bin_left+1))/3.0;
	averageT_right = (p_deltaT_afterTW_vs_y_forCorr->GetBinContent(y_bin_right) + p_deltaT_afterTW_vs_y_forCorr->GetBinContent(y_bin_right-1) + p_deltaT_afterTW_vs_y_forCorr->GetBinContent(y_bin_right-1))/3.0;

	//offsetYT_TWCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetYT_TWCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 
	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_afterTW_vs_y_forCorr->GetBinContent(i);
		if (dt_this < maxX_t_TWcorr-0.2 || dt_this > maxX_t_TWcorr+0.3) continue;
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
	//offsetYT_TWCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;



	TF1 * tf1_pol4_forCorr_y = new TF1("tf1_pol4_forCorr_y","pol4", y_tile_low-1, y_tile_high+1.0);
	p_deltaT_afterTW_vs_y_forCorr->Fit("tf1_pol4_forCorr_y","","",y_tile_low_fit, y_tile_high_fit);
	y_cor_p0 = tf1_pol4_forCorr_y->GetParameter(0);
	y_cor_p1 = tf1_pol4_forCorr_y->GetParameter(1);
	y_cor_p2 = tf1_pol4_forCorr_y->GetParameter(2);
	y_cor_p3 = tf1_pol4_forCorr_y->GetParameter(3);
	y_cor_p4 = tf1_pol4_forCorr_y->GetParameter(4);

	cout<<"p0: "<<y_cor_p0<<" ;  p1: "<<y_cor_p1<<" ;  p2: "<<y_cor_p2<<" ;  p3: "<<y_cor_p3<<" ;  p4: "<<y_cor_p4<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_forCorr_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_forCorr_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_forCorr_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_afterTW_vs_y_forCorr->Draw();
	p_deltaT_afterTW_vs_y_forCorr->SetMarkerColor( 4 );
        p_deltaT_afterTW_vs_y_forCorr->SetLineColor( 4 );
	p_deltaT_afterTW_vs_y_forCorr->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTW_vs_beamY_forCorr_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());


	//time resolution with impact point correction only
	
	myC->SetGridy(0);
	myC->SetGridx(0);

        TH1F * h_deltaT_XYcorr = new TH1F("h_deltaT_XYcorr","h_deltaT_XYcorr",100000, -1000.0, 1000.0);

        tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- (" + std::to_string(x_cor_xyonly_p0)+" + "
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
	sigmaTerr_XYCor = tf1_gaus_XYcorr->GetParError(2);	
	if(sigmaT_XYCor <  sigmaT_best) sigmaT_best = sigmaT_XYCor;

        gPad->Modified();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XYcorr_ch"+ch1+analysis_tag+".pdf").c_str());
        myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XYcorr_ch"+ch1+analysis_tag+".png").c_str());
        myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XYcorr_ch"+ch1+analysis_tag+".C").c_str());

	//amplitude dependency of the deltaT, after XY corr
	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_vs_amp_afterXYcorr = new TH2F("h2_deltaT_vs_amp_afterXYcorr","h2_deltaT_vs_amp_afterXYcorr", 100, amp_low, amp_high, 100, maxX_t_XYcorr-0.6, maxX_t_XYcorr+0.6);

        tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- (" + std::to_string(x_cor_xyonly_p0)+" + "
+std::to_string(x_cor_xyonly_p1)+"*x_dut[0] + "+std::to_string(x_cor_xyonly_p2)+"*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p3)+"*x_dut[0]*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0]+"
+std::to_string(y_cor_xyonly_p0)+" + "
+std::to_string(y_cor_xyonly_p1)+"*y_dut[0] + "+std::to_string(y_cor_xyonly_p2)+"*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p3)+"*y_dut[0]*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0]"
+"):amp["+ch1+"]>>h2_deltaT_vs_amp_afterXYcorr").c_str(),cut.c_str());




	h2_deltaT_vs_amp_afterXYcorr->GetXaxis()->SetTitle("amplitude [mV]");
	h2_deltaT_vs_amp_afterXYcorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_vs_amp_afterXYcorr->SetTitle("");
	h2_deltaT_vs_amp_afterXYcorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_vs_amp_afterXYcorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_vs_amp_afterXYcorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_vs_amp_afterXYcorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_vs_amp_afterXYcorr->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_afterXYcorr_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_afterXYcorr_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_afterXYcorr_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_deltaT_vs_amp_afterXYcorr = h2_deltaT_vs_amp_afterXYcorr->ProfileX(); 
	p_deltaT_vs_amp_afterXYcorr->GetXaxis()->SetTitle("amplitude [mV]");
	p_deltaT_vs_amp_afterXYcorr->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_vs_amp_afterXYcorr->SetTitle("");
	
	p_deltaT_vs_amp_afterXYcorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_vs_amp_afterXYcorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_vs_amp_afterXYcorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_vs_amp_afterXYcorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_vs_amp_afterXYcorr->GetYaxis()->SetRangeUser(maxX_t_XYcorr-0.2, maxX_t_XYcorr+0.3);
       	p_deltaT_vs_amp_afterXYcorr->GetXaxis()->SetRangeUser(amp_low, amp_high);
        p_deltaT_vs_amp_afterXYcorr->SetMarkerStyle( 20 );
        p_deltaT_vs_amp_afterXYcorr->SetMarkerColor( 1 );
        p_deltaT_vs_amp_afterXYcorr->SetLineColor( 1 );
	p_deltaT_vs_amp_afterXYcorr->Draw();


	TF1 * tf1_pol1_afterXYcorr_amp = new TF1("tf1_pol1_afterXYcorr_amp","pol1", amp_low, amp_high);
	p_deltaT_vs_amp_afterXYcorr->Fit("tf1_pol1_afterXYcorr_amp","","",amp_low_fit, amp_high_fit);
	float amp_cor_afterXYcorr_p0 = tf1_pol1_afterXYcorr_amp->GetParameter(0);
	float amp_cor_afterXYcorr_p1 = tf1_pol1_afterXYcorr_amp->GetParameter(1);

	cout<<"p0: "<<amp_cor_afterXYcorr_p0<<" ;  p1: "<<amp_cor_afterXYcorr_p1<<endl;

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_afterXYcorr_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_afterXYcorr_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_vs_amp_afterXYcorr_profile_ch"+ch1+analysis_tag+".C").c_str());


	
	//time resolution with TW+impact point correction
	myC->SetGridy(0);
	myC->SetGridx(0);
	
	TH1F * h_deltaT_TWXYcorr = new TH1F("h_deltaT_TWXYcorr","h_deltaT_TWXYcorr",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_p0)+" + "+std::to_string(amp_cor_p1)+"*amp["+ch1+"] + "
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
	sigmaTerr_TWXYCor = tf1_gaus_TWXYcorr->GetParError(2);	
	if(sigmaT_TWXYCor <  sigmaT_best) sigmaT_best = sigmaT_TWXYCor;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TW_then_XYcorr_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TW_then_XYcorr_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_TW_then_XYcorr_ch"+ch1+analysis_tag+".C").c_str());


	//time resolution with impact point + TW correction
	myC->SetGridy(0);
	myC->SetGridx(0);
	
	TH1F * h_deltaT_XYTWcorr = new TH1F("h_deltaT_XYTWcorr","h_deltaT_XYTWcorr",100000, -1000.0, 1000.0);
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_afterXYcorr_p0)+" + "+std::to_string(amp_cor_afterXYcorr_p1)+"*amp["+ch1+"] + "
+std::to_string(x_cor_xyonly_p0)+ "+" +std::to_string(x_cor_xyonly_p1)+"*x_dut[0] + "+std::to_string(x_cor_xyonly_p2)+"*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_xyonly_p3)+"*x_dut[0]*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_xyonly_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0] + "
+std::to_string(y_cor_xyonly_p0) + " + " + std::to_string(y_cor_xyonly_p1)+"*y_dut[0] + "+std::to_string(y_cor_xyonly_p2)+"*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_xyonly_p3)+"*y_dut[0]*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_xyonly_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0] "
+")>>h_deltaT_XYTWcorr").c_str(), cut.c_str());	

	h_deltaT_XYTWcorr->SetTitle("");
	h_deltaT_XYTWcorr->SetMarkerStyle( 20 );
	h_deltaT_XYTWcorr->SetMarkerColor( 1 );
	h_deltaT_XYTWcorr->SetLineColor( 1 );
	h_deltaT_XYTWcorr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h_deltaT_XYTWcorr->GetYaxis()->SetTitle("Events");
	h_deltaT_XYTWcorr->SetTitle("");
	h_deltaT_XYTWcorr->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_deltaT_XYTWcorr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_deltaT_XYTWcorr->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_deltaT_XYTWcorr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	float maxY_t_XYTWcorr = h_deltaT_XYTWcorr->GetMaximum();
	float maxX_t_XYTWcorr = h_deltaT_XYTWcorr->GetBinCenter(h_deltaT_XYTWcorr->GetMaximumBin());
       	h_deltaT_XYTWcorr->GetXaxis()->SetRangeUser(maxX_t_XYTWcorr-0.6, maxX_t_XYTWcorr+0.6);
        h_deltaT_XYTWcorr->Draw("E");

	float highDeltaT_XYTWcorr=maxX_t_XYTWcorr + fit_range_right + 0.02;//h_deltaT_XYTWcorr->GetBinCenter(h_deltaT_XYTWcorr->FindLastBinAbove(int(0.3*maxY_t)));
	float lowDeltaT_XYTWcorr=maxX_t_XYTWcorr - fit_range_left - 0.04;//h_deltaT_XYTWcorr->GetBinCenter(h_deltaT_XYTWcorr->FindFirstBinAbove(int(0.1*maxY_t)));
	//if(highDeltaT_XYTWcorr - maxX_t_XYTWcorr > 2.0*(maxX_t_XYTWcorr-lowDeltaT_XYTWcorr)) highDeltaT_XYTWcorr = maxX_t_XYTWcorr + (maxX_t_XYTWcorr - lowDeltaT_XYTWcorr);
	TF1 * tf1_gaus_XYTWcorr = new TF1("tf1_gaus_XYTWcorr","gaus", maxX_t_XYTWcorr - 1.0, maxX_t_XYTWcorr + 1.0);
	tf1_gaus_XYTWcorr->SetParameter(1, h_deltaT_XYTWcorr->GetMean());
	h_deltaT_XYTWcorr->Fit("tf1_gaus_XYTWcorr","","",lowDeltaT_XYTWcorr, highDeltaT_XYTWcorr);

	sigmaT_XYTWCor = tf1_gaus_XYTWcorr->GetParameter(2);	
	sigmaTerr_XYTWCor = tf1_gaus_XYTWcorr->GetParError(2);	
	if(sigmaT_XYTWCor <  sigmaT_best) sigmaT_best = sigmaT_XYTWCor;

	gPad->Modified();
	gPad->Update();

	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XY_then_TWcorr_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XY_then_TWcorr_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_XY_then_TWcorr_ch"+ch1+analysis_tag+".C").c_str());

	// impact point dependency of the deltaT, after XY correction, for visual effects

	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_afterXY_vs_x = new TH2F("h2_deltaT_afterXY_vs_x","h2_deltaT_afterXY_vs_x", 72, x_low, x_high, 100, maxX_t_XYcorr-0.2, maxX_t_XYcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]:x_dut[0]>>h2_deltaT_afterXY_vs_x").c_str(),cut_noPos.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterXY_vs_x").c_str(),cut_noPos.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterXY_vs_x").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());

        tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- (" + std::to_string(x_cor_xyonly_p0)+" + "
+std::to_string(x_cor_xyonly_p1)+"*x_dut[0] + "+std::to_string(x_cor_xyonly_p2)+"*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p3)+"*x_dut[0]*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0]+"
+std::to_string(y_cor_xyonly_p0)+" + "
+std::to_string(y_cor_xyonly_p1)+"*y_dut[0] + "+std::to_string(y_cor_xyonly_p2)+"*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p3)+"*y_dut[0]*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0]"
+") : x_dut[0]>>h2_deltaT_afterXY_vs_x").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());


	h2_deltaT_afterXY_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_afterXY_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterXY_vs_x->SetTitle("");
	h2_deltaT_afterXY_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterXY_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterXY_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterXY_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterXY_vs_x->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamX_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamX_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamX_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_deltaT_afterXY_vs_x = h2_deltaT_afterXY_vs_x->ProfileX(); //new ("p_deltaT_afterXY_vs_x","p_deltaT_afterXY_vs_x",72, x_low, x_high);
	p_deltaT_afterXY_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	p_deltaT_afterXY_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_afterXY_vs_x->SetTitle("");
	
	p_deltaT_afterXY_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_afterXY_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_afterXY_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_afterXY_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	//p_deltaT_afterXY_vs_x->GetYaxis()->SetRangeUser(maxX_t-0.2, maxX_t+0.3);
       	p_deltaT_afterXY_vs_x->GetYaxis()->SetRangeUser(maxX_t_XYcorr-0.2, maxX_t_XYcorr+0.3);
       	p_deltaT_afterXY_vs_x->GetXaxis()->SetRangeUser(x_tile_low, x_tile_high);
        p_deltaT_afterXY_vs_x->SetMarkerStyle( 20 );
        p_deltaT_afterXY_vs_x->SetMarkerColor( 1 );
        p_deltaT_afterXY_vs_x->SetLineColor( 1 );
	p_deltaT_afterXY_vs_x->Draw();

	averageT_center = (p_deltaT_afterXY_vs_x->GetBinContent(x_bin_center) + p_deltaT_afterXY_vs_x->GetBinContent(x_bin_center-1) + p_deltaT_afterXY_vs_x->GetBinContent(x_bin_center+1))/3.0;
	averageT_left = (p_deltaT_afterXY_vs_x->GetBinContent(x_bin_left) + p_deltaT_afterXY_vs_x->GetBinContent(x_bin_left+1) + p_deltaT_afterXY_vs_x->GetBinContent(x_bin_left+1))/3.0;
	averageT_right = (p_deltaT_afterXY_vs_x->GetBinContent(x_bin_right) + p_deltaT_afterXY_vs_x->GetBinContent(x_bin_right-1) + p_deltaT_afterXY_vs_x->GetBinContent(x_bin_right-1))/3.0;

	//offsetXT_XYCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetXT_XYCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 

	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_afterXY_vs_x->GetBinContent(i);
		if (dt_this < maxX_t_XYcorr-0.2 || dt_this > maxX_t_XYcorr+0.3) continue;
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
	offsetXT_XYCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;




	TF1 * tf1_pol4_afterXY_x = new TF1("tf1_pol4_afterXY_x","pol4", x_tile_low-1, x_tile_high+1.0);
	p_deltaT_afterXY_vs_x->Fit("tf1_pol4_afterXY_x","","",x_tile_low_fit, x_tile_high_fit);


	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamX_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamX_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamX_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_afterXY_vs_x->Draw();
	p_deltaT_afterXY_vs_x->SetMarkerColor( 4 );
        p_deltaT_afterXY_vs_x->SetLineColor( 4 );
	p_deltaT_afterXY_vs_x->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	

	TH2F * h2_deltaT_afterXY_vs_y = new TH2F("h2_deltaT_afterXY_vs_y","h2_deltaT_afterXY_vs_y", 72, y_low, y_high, 100, maxX_t_XYcorr-0.2, maxX_t_XYcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterXY_vs_y").c_str(),cut_noPos.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterXY_vs_y").c_str(),(cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());

        tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- (" + std::to_string(x_cor_xyonly_p0)+" + "
+std::to_string(x_cor_xyonly_p1)+"*x_dut[0] + "+std::to_string(x_cor_xyonly_p2)+"*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p3)+"*x_dut[0]*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0]+"
+std::to_string(y_cor_xyonly_p0)+" + "
+std::to_string(y_cor_xyonly_p1)+"*y_dut[0] + "+std::to_string(y_cor_xyonly_p2)+"*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p3)+"*y_dut[0]*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0]"
+") : y_dut[0]>>h2_deltaT_afterXY_vs_y").c_str(),(cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());



	h2_deltaT_afterXY_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	h2_deltaT_afterXY_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterXY_vs_y->SetTitle("");
	h2_deltaT_afterXY_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterXY_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterXY_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterXY_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterXY_vs_y->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamY_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamY_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamY_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_deltaT_afterXY_vs_y = h2_deltaT_afterXY_vs_y->ProfileX(); 
	p_deltaT_afterXY_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	p_deltaT_afterXY_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_afterXY_vs_y->SetTitle("");
	
	p_deltaT_afterXY_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_afterXY_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_afterXY_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_afterXY_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_afterXY_vs_y->GetYaxis()->SetRangeUser(maxX_t_XYcorr-0.2, maxX_t_XYcorr+0.3);
       	p_deltaT_afterXY_vs_y->GetXaxis()->SetRangeUser(y_tile_low, y_tile_high);
        p_deltaT_afterXY_vs_y->SetMarkerStyle( 20 );
        p_deltaT_afterXY_vs_y->SetMarkerColor( 1 );
        p_deltaT_afterXY_vs_y->SetLineColor( 1 );
	p_deltaT_afterXY_vs_y->Draw();

	averageT_center = (p_deltaT_afterXY_vs_y->GetBinContent(y_bin_center) + p_deltaT_afterXY_vs_y->GetBinContent(y_bin_center-1) + p_deltaT_afterXY_vs_y->GetBinContent(y_bin_center+1))/3.0;
	averageT_left = (p_deltaT_afterXY_vs_y->GetBinContent(y_bin_left) + p_deltaT_afterXY_vs_y->GetBinContent(y_bin_left+1) + p_deltaT_afterXY_vs_y->GetBinContent(y_bin_left+1))/3.0;
	averageT_right = (p_deltaT_afterXY_vs_y->GetBinContent(y_bin_right) + p_deltaT_afterXY_vs_y->GetBinContent(y_bin_right-1) + p_deltaT_afterXY_vs_y->GetBinContent(y_bin_right-1))/3.0;

	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_afterXY_vs_y->GetBinContent(i);
		if (dt_this < maxX_t_XYcorr-0.2 || dt_this > maxX_t_XYcorr+0.3) continue;
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
	offsetYT_XYCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;



	TF1 * tf1_pol4_afterXY_y = new TF1("tf1_pol4_afterXY_y","pol4", y_tile_low-1, y_tile_high+1.0);
	p_deltaT_afterXY_vs_y->Fit("tf1_pol4_afterXY_y","","",y_tile_low_fit, y_tile_high_fit);

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamY_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamY_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamY_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_afterXY_vs_y->Draw();
	p_deltaT_afterXY_vs_y->SetMarkerColor( 4 );
        p_deltaT_afterXY_vs_y->SetLineColor( 4 );
	p_deltaT_afterXY_vs_y->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterXY_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());




	// impact point dependency of the deltaT, after TWXY correction, for visual effects

	myC->SetGridy(1);
	myC->SetGridx(1);
	TH2F * h2_deltaT_afterTWXY_vs_x = new TH2F("h2_deltaT_afterTWXY_vs_x","h2_deltaT_afterTWXY_vs_x", 72, x_low, x_high, 100, maxX_t_TWXYcorr-0.2, maxX_t_TWXYcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]:x_dut[0]>>h2_deltaT_afterTWXY_vs_x").c_str(),cut_noPos.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterTWXY_vs_x").c_str(),cut_noPos.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+ std::to_string(amp_cor_p0) + " + " + std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : x_dut[0]>>h2_deltaT_afterTWXY_vs_x").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_p0)+" + "+std::to_string(amp_cor_p1)+"*amp["+ch1+"] + "
+std::to_string(x_cor_p0)+ "+" +std::to_string(x_cor_p1)+"*x_dut[0] + "+std::to_string(x_cor_p2)+"*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_p3)+"*x_dut[0]*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0] + "
+std::to_string(y_cor_p0) + " + " + std::to_string(y_cor_p1)+"*y_dut[0] + "+std::to_string(y_cor_p2)+"*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_p3)+"*y_dut[0]*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0] "
+") : x_dut[0]>>h2_deltaT_afterTWXY_vs_x").c_str(),(cut_noPos+" && y_dut[0]>"+std::to_string(y_sipm_low)+" && y_dut[0]<"+std::to_string(y_sipm_high)).c_str());


	h2_deltaT_afterTWXY_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	h2_deltaT_afterTWXY_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterTWXY_vs_x->SetTitle("");
	h2_deltaT_afterTWXY_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterTWXY_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterTWXY_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterTWXY_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterTWXY_vs_x->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamX_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamX_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamX_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_deltaT_afterTWXY_vs_x = h2_deltaT_afterTWXY_vs_x->ProfileX(); //new ("p_deltaT_afterTWXY_vs_x","p_deltaT_afterTWXY_vs_x",72, x_low, x_high);
	p_deltaT_afterTWXY_vs_x->GetXaxis()->SetTitle("beam position X [mm]");
	p_deltaT_afterTWXY_vs_x->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_afterTWXY_vs_x->SetTitle("");
	
	p_deltaT_afterTWXY_vs_x->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_afterTWXY_vs_x->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_afterTWXY_vs_x->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_afterTWXY_vs_x->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	//p_deltaT_afterTWXY_vs_x->GetYaxis()->SetRangeUser(maxX_t-0.2, maxX_t+0.3);
       	p_deltaT_afterTWXY_vs_x->GetYaxis()->SetRangeUser(maxX_t_TWXYcorr-0.2, maxX_t_TWXYcorr+0.3);
       	p_deltaT_afterTWXY_vs_x->GetXaxis()->SetRangeUser(x_tile_low, x_tile_high);
        p_deltaT_afterTWXY_vs_x->SetMarkerStyle( 20 );
        p_deltaT_afterTWXY_vs_x->SetMarkerColor( 1 );
        p_deltaT_afterTWXY_vs_x->SetLineColor( 1 );
	p_deltaT_afterTWXY_vs_x->Draw();

	averageT_center = (p_deltaT_afterTWXY_vs_x->GetBinContent(x_bin_center) + p_deltaT_afterTWXY_vs_x->GetBinContent(x_bin_center-1) + p_deltaT_afterTWXY_vs_x->GetBinContent(x_bin_center+1))/3.0;
	averageT_left = (p_deltaT_afterTWXY_vs_x->GetBinContent(x_bin_left) + p_deltaT_afterTWXY_vs_x->GetBinContent(x_bin_left+1) + p_deltaT_afterTWXY_vs_x->GetBinContent(x_bin_left+1))/3.0;
	averageT_right = (p_deltaT_afterTWXY_vs_x->GetBinContent(x_bin_right) + p_deltaT_afterTWXY_vs_x->GetBinContent(x_bin_right-1) + p_deltaT_afterTWXY_vs_x->GetBinContent(x_bin_right-1))/3.0;

	//offsetXT_TWXYCor = 0.5*(averageT_left + averageT_right) - averageT_center;
	//offsetXT_TWXYCor = (averageT_left > averageT_right) ? (averageT_left - averageT_center) : (averageT_right - averageT_center) ; 

	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_afterTWXY_vs_x->GetBinContent(i);
		if (dt_this < maxX_t_TWXYcorr-0.2 || dt_this > maxX_t_TWXYcorr+0.3) continue;
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
	offsetXT_TWXYCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;




	TF1 * tf1_pol4_afterTWXY_x = new TF1("tf1_pol4_afterTWXY_x","pol4", x_tile_low-1, x_tile_high+1.0);
	p_deltaT_afterTWXY_vs_x->Fit("tf1_pol4_afterTWXY_x","","",x_tile_low_fit, x_tile_high_fit);


	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamX_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamX_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamX_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_afterTWXY_vs_x->Draw();
	p_deltaT_afterTWXY_vs_x->SetMarkerColor( 4 );
        p_deltaT_afterTWXY_vs_x->SetLineColor( 4 );
	p_deltaT_afterTWXY_vs_x->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamX_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());
	

	TH2F * h2_deltaT_afterTWXY_vs_y = new TH2F("h2_deltaT_afterTWXY_vs_y","h2_deltaT_afterTWXY_vs_y", 72, y_low, y_high, 100, maxX_t_TWXYcorr-0.2, maxX_t_TWXYcorr+0.3);
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterTWXY_vs_y").c_str(),cut_noPos.c_str());
	//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"] - ("+std::to_string(amp_cor_p0) + " + " +std::to_string(amp_cor_p1)+"*amp["+ch1+"]) : y_dut[0]>>h2_deltaT_afterTWXY_vs_y").c_str(),(cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str());
	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_p0)+" + "+std::to_string(amp_cor_p1)+"*amp["+ch1+"] + "
+std::to_string(x_cor_p0)+ "+" +std::to_string(x_cor_p1)+"*x_dut[0] + "+std::to_string(x_cor_p2)+"*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_p3)+"*x_dut[0]*x_dut[0]*x_dut[0] + "+std::to_string(x_cor_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0] + "
+std::to_string(y_cor_p0) + " + " + std::to_string(y_cor_p1)+"*y_dut[0] + "+std::to_string(y_cor_p2)+"*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_p3)+"*y_dut[0]*y_dut[0]*y_dut[0] + "+std::to_string(y_cor_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0] "
+") : y_dut[0]>>h2_deltaT_afterTWXY_vs_y").c_str(),(cut_noPos+" && x_dut[0] > "+std::to_string(x_sipm_low)+" && x_dut[0]<"+std::to_string(x_sipm_high)).c_str()); 



	h2_deltaT_afterTWXY_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	h2_deltaT_afterTWXY_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	h2_deltaT_afterTWXY_vs_y->SetTitle("");
	h2_deltaT_afterTWXY_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_deltaT_afterTWXY_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_deltaT_afterTWXY_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_deltaT_afterTWXY_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	
	h2_deltaT_afterTWXY_vs_y->Draw();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamY_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamY_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamY_ch"+ch1+analysis_tag+".C").c_str());

	TProfile * p_deltaT_afterTWXY_vs_y = h2_deltaT_afterTWXY_vs_y->ProfileX(); 
	p_deltaT_afterTWXY_vs_y->GetXaxis()->SetTitle("beam position Y [mm]");
	p_deltaT_afterTWXY_vs_y->GetYaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
	p_deltaT_afterTWXY_vs_y->SetTitle("");
	
	p_deltaT_afterTWXY_vs_y->GetXaxis()->SetTitleSize( axisTitleSizeX );
	p_deltaT_afterTWXY_vs_y->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	p_deltaT_afterTWXY_vs_y->GetYaxis()->SetTitleSize( axisTitleSizeY );
	p_deltaT_afterTWXY_vs_y->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
       	p_deltaT_afterTWXY_vs_y->GetYaxis()->SetRangeUser(maxX_t_TWXYcorr-0.2, maxX_t_TWXYcorr+0.3);
       	p_deltaT_afterTWXY_vs_y->GetXaxis()->SetRangeUser(y_tile_low, y_tile_high);
        p_deltaT_afterTWXY_vs_y->SetMarkerStyle( 20 );
        p_deltaT_afterTWXY_vs_y->SetMarkerColor( 1 );
        p_deltaT_afterTWXY_vs_y->SetLineColor( 1 );
	p_deltaT_afterTWXY_vs_y->Draw();

	averageT_center = (p_deltaT_afterTWXY_vs_y->GetBinContent(y_bin_center) + p_deltaT_afterTWXY_vs_y->GetBinContent(y_bin_center-1) + p_deltaT_afterTWXY_vs_y->GetBinContent(y_bin_center+1))/3.0;
	averageT_left = (p_deltaT_afterTWXY_vs_y->GetBinContent(y_bin_left) + p_deltaT_afterTWXY_vs_y->GetBinContent(y_bin_left+1) + p_deltaT_afterTWXY_vs_y->GetBinContent(y_bin_left+1))/3.0;
	averageT_right = (p_deltaT_afterTWXY_vs_y->GetBinContent(y_bin_right) + p_deltaT_afterTWXY_vs_y->GetBinContent(y_bin_right-1) + p_deltaT_afterTWXY_vs_y->GetBinContent(y_bin_right-1))/3.0;

	for(int i=x_bin_left;i<=x_bin_right;i++)
	{
		float dt_this = p_deltaT_afterTWXY_vs_y->GetBinContent(i);
		if (dt_this < maxX_t_TWXYcorr-0.2 || dt_this > maxX_t_TWXYcorr+0.3) continue;
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
	offsetYT_TWXYCor = all_xydt_max - all_xydt_min;
	all_xydt_min = 99999.9;	
	all_xydt_max = -99999.9;



	TF1 * tf1_pol4_afterTWXY_y = new TF1("tf1_pol4_afterTWXY_y","pol4", y_tile_low-1, y_tile_high+1.0);
	p_deltaT_afterTWXY_vs_y->Fit("tf1_pol4_afterTWXY_y","","",y_tile_low_fit, y_tile_high_fit);

	gPad->Modified();
	gPad->Update();
	
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamY_profile_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamY_profile_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamY_profile_ch"+ch1+analysis_tag+".C").c_str());

	h2_deltaT_afterTWXY_vs_y->Draw();
	p_deltaT_afterTWXY_vs_y->SetMarkerColor( 4 );
        p_deltaT_afterTWXY_vs_y->SetLineColor( 4 );
	p_deltaT_afterTWXY_vs_y->Draw("same");
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".pdf").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".png").c_str());
 	myC->SaveAs((plotDir+"/Run"+inFileName+"_deltaT_afterTWXY_vs_beamY_scatter_and_profile_ch"+ch1+analysis_tag+".C").c_str());


	//time resolution in xy bins, after time walk correction
	
	myC->SetGridy(0);
	myC->SetGridx(0);

	TH2F * h2_reso_vs_xy_afterTW =  new TH2F("h2_reso_vs_xy_afterTW","h2_reso_vs_xy_afterTW", 9, x_low, x_high, 9, y_low, y_high);
	TH2F * h2_meanT_vs_xy_afterTW =  new TH2F("h2_meanT_vs_xy_afterTW","h2_meanT_vs_xy_afterTW", 9, x_low, x_high, 9, y_low, y_high);
	
	float maxY_t_2D_mean_afterTW = -9999.9;//50.0+h2_meanT_vs_xy_afterTW->GetMaximum(); 
	float minY_t_2D_mean_afterTW = 9999.9;//h2_meanT_vs_xy_afterTW->GetMinimum()-50.0; 
	
	int N_usefulbins_XY_afterTW = 0;	
	
	for(int ix = 1; ix<=9; ix++)
	{
		for(int iy=1;iy<=9;iy++)
		{
			float thisX_low = x_low + 2.0*(ix-1);
			float thisX_high = x_low + 2.0*ix;
			float thisY_low = y_low + 2.0*(iy-1);
			float thisY_high = y_low + 2.0*iy;
			
			TH1F * h_deltaT_corr = new TH1F(("h_deltaT_corr_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),("h_deltaT_corr_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),100000, -1000.0, 1000.0);
			//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]>>h_deltaT_corr_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),(cut_noPos+" && x_dut[0]>"+std::to_string(thisX_low)+" && x_dut[0]<"+std::to_string(thisX_high) +" && y_dut[0]>"+std::to_string(thisY_low)+" && y_dut[0]<"+std::to_string(thisY_high)).c_str());

			tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- ("+std::to_string(amp_cor_p0)+" + "+std::to_string(amp_cor_p1)+"*amp["+ch1+"])>>h_deltaT_corr_x"+std::to_string(ix)+"_y"+std::to_string(iy)).c_str(),(cut_noPos+" && x_dut[0]>"+std::to_string(thisX_low)+" && x_dut[0]<"+std::to_string(thisX_high) +" && y_dut[0]>"+std::to_string(thisY_low)+" && y_dut[0]<"+std::to_string(thisY_high)).c_str());

			//if(h_deltaT_corr->Integral() < 10.0) 
			if(thisX_high < x_tile_low || thisX_low > x_tile_high || thisY_high < y_tile_low || thisY_low > y_tile_high || h_deltaT_corr->Integral() < 100.0)
			{
				h2_reso_vs_xy_afterTW->SetBinContent(ix,iy,-999.9);
				h2_meanT_vs_xy_afterTW->SetBinContent(ix,iy,-9999.9);
				continue;	
			}	
			
			h_deltaT_corr->SetTitle("");
			h_deltaT_corr->SetMarkerStyle( 20 );
			h_deltaT_corr->SetMarkerColor( 1 );
			h_deltaT_corr->SetLineColor( 1 );
			h_deltaT_corr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
			h_deltaT_corr->GetYaxis()->SetTitle("Events");
			h_deltaT_corr->SetTitle("");
			h_deltaT_corr->GetXaxis()->SetTitleSize( axisTitleSizeX );
			h_deltaT_corr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
			h_deltaT_corr->GetYaxis()->SetTitleSize( axisTitleSizeY );
			h_deltaT_corr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
			float maxY_t = h_deltaT_corr->GetMaximum();
			float maxX_t = h_deltaT_corr->GetBinCenter(h_deltaT_corr->GetMaximumBin());
			h_deltaT_corr->GetXaxis()->SetRangeUser(maxX_t-0.6, maxX_t+0.6);
			h_deltaT_corr->Draw("E");

			float highDeltaT=maxX_t+fit_range_right_noRes;//+0.02;//h_deltaT_corr->GetBinCenter(h_deltaT_corr->FindLastBinAbove(int(0.3*maxY_t)));
			float lowDeltaT=maxX_t-fit_range_left_noRes;//-0.08;//h_deltaT_corr->GetBinCenter(h_deltaT_corr->FindFirstBinAbove(int(0.1*maxY_t)));
			//if(highDeltaT - maxX_t > 2.0*(maxX_t-lowDeltaT)) highDeltaT = maxX_t + (maxX_t - lowDeltaT);
			TF1 * tf1_gaus = new TF1("tf1_gaus","gaus", maxX_t - 1.0, maxX_t + 1.0);
			tf1_gaus->SetParameter(1, h_deltaT_corr->GetMean());
			h_deltaT_corr->Fit("tf1_gaus","","",lowDeltaT, highDeltaT);
	
			N_usefulbins_XY_afterTW ++;		
			float sigmaT = tf1_gaus->GetParameter(2);	
			float meanT = tf1_gaus->GetParameter(1);	
			float sigmaTerror = tf1_gaus->GetParError(2);	
			float meanTerror = tf1_gaus->GetParError(1);	

			if(1000.0*sigmaT < h2_reso_vs_xy->GetBinContent(ix,iy))
			{
			h2_reso_vs_xy_afterTW->SetBinContent(ix,iy,1000.0*sigmaT);
			h2_reso_vs_xy_afterTW->SetBinError(ix,iy,1000.0*sigmaTerror);
			sigmaT_XYaverage_afterTW += 1000.0*sigmaT;
			e_sigmaT_XYaverage_afterTW += 1000.0*sigmaTerror*1000.0*sigmaTerror;
			}
			else
			{
			h2_reso_vs_xy_afterTW->SetBinContent(ix,iy,h2_reso_vs_xy->GetBinContent(ix,iy));
			h2_reso_vs_xy_afterTW->SetBinError(ix,iy,h2_reso_vs_xy->GetBinError(ix,iy));
			sigmaT_XYaverage_afterTW += h2_reso_vs_xy->GetBinContent(ix,iy);
			e_sigmaT_XYaverage_afterTW += h2_reso_vs_xy->GetBinError(ix,iy) * h2_reso_vs_xy->GetBinError(ix,iy);
			}

			h2_meanT_vs_xy_afterTW->SetBinContent(ix,iy,1000.0*meanT);
			h2_meanT_vs_xy_afterTW->SetBinError(ix,iy,1000.0*meanTerror);

			if(1000.0*meanT > maxY_t_2D_mean_afterTW) maxY_t_2D_mean_afterTW = 1000.0*meanT;
			if(1000.0*meanT < minY_t_2D_mean_afterTW) minY_t_2D_mean_afterTW = 1000.0*meanT;
	
			gPad->Modified();
			gPad->Update();

			myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_afterTW_x"+std::to_string(thisX_low)+"_y"+std::to_string(thisY_low)+"_deltaT_corr_ch"+ch1+analysis_tag+".pdf").c_str());
			myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_afterTW_x"+std::to_string(thisX_low)+"_y"+std::to_string(thisY_low)+"_deltaT_corr_ch"+ch1+analysis_tag+".png").c_str());
			myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_afterTW_x"+std::to_string(thisX_low)+"_y"+std::to_string(thisY_low)+"_deltaT_corr_ch"+ch1+analysis_tag+".C").c_str());
			
		}
	}	
	for(int ix = 1; ix<=9; ix++)
	{
		for(int iy=1;iy<=9;iy++)
		{
			h2_meanT_vs_xy_afterTW->SetBinContent(ix,iy,h2_meanT_vs_xy_afterTW->GetBinContent(ix,iy)-minY_t_2D_mean_afterTW + 0.01);
		}
	}

	sigmaT_XYaverage_afterTW = sigmaT_XYaverage_afterTW/(1.0*N_usefulbins_XY_afterTW);
	e_sigmaT_XYaverage_afterTW = sqrt(e_sigmaT_XYaverage_afterTW)/(1.0*N_usefulbins_XY_afterTW);

	myC->SetGridy(1);
	myC->SetGridx(1);


	//gStyle->SetPalette(104);
	gStyle->SetPaintTextFormat( "3.0f" );	
	h2_reso_vs_xy_afterTW->Draw("COLZ,TEXT,ERROR");
	h2_reso_vs_xy_afterTW->GetXaxis()->SetTitle("beam position X [mm]");
	h2_reso_vs_xy_afterTW->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_reso_vs_xy_afterTW->GetZaxis()->SetTitle("time resolution [ps]");
	float maxY_t_2D_afterTW = std::min(200.0, 5.0+h2_reso_vs_xy_afterTW->GetMaximum()); 
	h2_reso_vs_xy_afterTW->GetZaxis()->SetRangeUser(20.0,80.0);//maxY_t_2D_afterTW);
	h2_reso_vs_xy_afterTW->SetTitle("");
	h2_reso_vs_xy_afterTW->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_reso_vs_xy_afterTW->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_reso_vs_xy_afterTW->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_reso_vs_xy_afterTW->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_reso_vs_xy_afterTW->GetXaxis()->SetRangeUser(x_low+2.0, x_high-2.0);
	h2_reso_vs_xy_afterTW->GetYaxis()->SetRangeUser(y_low+2.0, y_high-2.0);
	h2_reso_vs_xy_afterTW->SetMarkerSize(2);

	TLatex *tlatex_xybins_afterTW =  new TLatex();
        tlatex_xybins_afterTW->SetNDC();
        tlatex_xybins_afterTW->SetTextAngle(0);
        tlatex_xybins_afterTW->SetTextColor(kBlack);
        tlatex_xybins_afterTW->SetTextFont(63);
        tlatex_xybins_afterTW->SetTextAlign(11);
        tlatex_xybins_afterTW->SetTextSize(30);
        tlatex_xybins_afterTW->DrawLatex(0.5, 0.95, ("average #sigma = "+std::to_string(int(ceil(sigmaT_XYaverage_afterTW))) +" #pm "+std::to_string(int(ceil(e_sigmaT_XYaverage_afterTW))) +" ps").c_str());

	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_afterTW_2Dtimereso_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_afterTW_2Dtimereso_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_afterTW_2Dtimereso_ch"+ch1+analysis_tag+".C").c_str());

	gStyle->SetPaintTextFormat( "4.0f" );	
	h2_meanT_vs_xy_afterTW->Draw("COLZ,TEXT,ERROR");
	h2_meanT_vs_xy_afterTW->GetXaxis()->SetTitle("beam position X [mm]");
	h2_meanT_vs_xy_afterTW->GetYaxis()->SetTitle("beam position Y [mm]");
	h2_meanT_vs_xy_afterTW->GetZaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ps").c_str() );
	//float maxY_t_2D = std::min(200.0, 5.0+h2_meanT_vs_xy->GetMaximum()); 
	//h2_meanT_vs_xy_afterTW->GetZaxis()->SetRangeUser(minY_t_2D_mean_afterTW-50.0,maxY_t_2D_mean_afterTW+50.0);
	h2_meanT_vs_xy_afterTW->GetZaxis()->SetRangeUser(-10.0,300.0);//maxY_t_2D_mean_afterTW-minY_t_2D_mean_afterTW+50.0);

	h2_meanT_vs_xy_afterTW->SetTitle("");
	h2_meanT_vs_xy_afterTW->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h2_meanT_vs_xy_afterTW->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h2_meanT_vs_xy_afterTW->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h2_meanT_vs_xy_afterTW->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h2_meanT_vs_xy_afterTW->GetZaxis()->SetTitleOffset( 1.2 );
	h2_meanT_vs_xy_afterTW->GetXaxis()->SetRangeUser(x_low+2.0, x_high-2.0);
	h2_meanT_vs_xy_afterTW->GetYaxis()->SetRangeUser(y_low+2.0, y_high-2.0);
	h2_meanT_vs_xy_afterTW->SetMarkerSize(2);
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_afterTW_2DtimemeanT_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_afterTW_2DtimemeanT_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_xybins_afterTW_2DtimemeanT_ch"+ch1+analysis_tag+".C").c_str());


	gStyle->SetPalette(1);
	//time resolution in amplitude bins
	myC->SetGridy(0);
	myC->SetGridx(0);

	TH1F * h1_reso_vs_amp_afterXY =  new TH1F("h1_reso_vs_amp_afterXY","h1_reso_vs_amp_afterXY", 10, amp_low, amp_high);
	
	for(int iamp = 1; iamp<=10; iamp++)
	{
		float thisAmp_low = amp_low + (iamp-1)*(amp_high-amp_low)/10;
		float thisAmp_high = amp_low + iamp*(amp_high-amp_low)/10;
		
		TH1F * h_deltaT_corr = new TH1F(("h_deltaT_corr_amp"+std::to_string(iamp)).c_str(),("h_deltaT_corr_amp"+std::to_string(iamp)).c_str(),100000, -1000.0, 1000.0);
		//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]>>h_deltaT_corr_amp"+std::to_string(iamp)).c_str(),(cut+" && amp["+ch1+"]>"+std::to_string(thisAmp_low)+" && amp["+ch1+"]<"+std::to_string(thisAmp_high)).c_str());

        	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- (" + std::to_string(x_cor_xyonly_p0)+" + "
+std::to_string(x_cor_xyonly_p1)+"*x_dut[0] + "+std::to_string(x_cor_xyonly_p2)+"*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p3)+"*x_dut[0]*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0]+"
+std::to_string(y_cor_xyonly_p0)+" + "
+std::to_string(y_cor_xyonly_p1)+"*y_dut[0] + "+std::to_string(y_cor_xyonly_p2)+"*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p3)+"*y_dut[0]*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0]"
+")>>h_deltaT_corr_amp"+std::to_string(iamp)).c_str(),(cut_sipm+" && amp["+ch1+"]>"+std::to_string(thisAmp_low)+"&& amp["+ch1+"]<"+std::to_string(thisAmp_high)).c_str());




		if(h_deltaT_corr->Integral() < 100.0) 
		{
			h1_reso_vs_amp_afterXY->SetBinContent(iamp,-999.9);
			continue;	
		}	
		
		h_deltaT_corr->SetTitle("");
		h_deltaT_corr->SetMarkerStyle( 20 );
		h_deltaT_corr->SetMarkerColor( 1 );
		h_deltaT_corr->SetLineColor( 1 );
		h_deltaT_corr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
		h_deltaT_corr->GetYaxis()->SetTitle("Events");
		h_deltaT_corr->SetTitle("");
		h_deltaT_corr->GetXaxis()->SetTitleSize( axisTitleSizeX );
		h_deltaT_corr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
		h_deltaT_corr->GetYaxis()->SetTitleSize( axisTitleSizeY );
		h_deltaT_corr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
		float maxY_t = h_deltaT_corr->GetMaximum();
		float maxX_t = h_deltaT_corr->GetBinCenter(h_deltaT_corr->GetMaximumBin());
		h_deltaT_corr->GetXaxis()->SetRangeUser(maxX_t-0.6, maxX_t+0.6);
		h_deltaT_corr->Draw("E");

		float highDeltaT=maxX_t+fit_range_right_noRes;//+0.02;//h_deltaT_corr->GetBinCenter(h_deltaT_corr->FindLastBinAbove(int(0.3*maxY_t)));
		float lowDeltaT=maxX_t-fit_range_left_noRes;//-0.08;//h_deltaT_corr->GetBinCenter(h_deltaT_corr->FindFirstBinAbove(int(0.1*maxY_t)));
		//if(highDeltaT - maxX_t > 2.0*(maxX_t-lowDeltaT)) highDeltaT = maxX_t + (maxX_t - lowDeltaT);
		TF1 * tf1_gaus = new TF1("tf1_gaus","gaus", maxX_t - 1.0, maxX_t + 1.0);
		tf1_gaus->SetParameter(1, h_deltaT_corr->GetMean());
		h_deltaT_corr->Fit("tf1_gaus","","",lowDeltaT, highDeltaT);
		
		float sigmaT = tf1_gaus->GetParameter(2);	
		float sigmaTerror = tf1_gaus->GetParError(2);	
		if(sigmaT < h1_reso_vs_amp->GetBinContent(iamp))
		{
		h1_reso_vs_amp_afterXY->SetBinContent(iamp,sigmaT);
		h1_reso_vs_amp_afterXY->SetBinError(iamp,sigmaTerror);
		}

		else
		{
		h1_reso_vs_amp_afterXY->SetBinContent(iamp,h1_reso_vs_amp->GetBinContent(iamp));
		h1_reso_vs_amp_afterXY->SetBinError(iamp,h1_reso_vs_amp->GetBinError(iamp));
		}
		gPad->Modified();
		gPad->Update();

		myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins_afterXY"+std::to_string(thisAmp_low)+"_deltaT_corr_ch"+ch1+analysis_tag+".pdf").c_str());
		myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins_afterXY"+std::to_string(thisAmp_low)+"_deltaT_corr_ch"+ch1+analysis_tag+".png").c_str());
		myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins_afterXY"+std::to_string(thisAmp_low)+"_deltaT_corr_ch"+ch1+analysis_tag+".C").c_str());
		
	}	

	h1_reso_vs_amp_afterXY->SetMarkerStyle( 20 );
	h1_reso_vs_amp_afterXY->SetMarkerColor( 1 );
	h1_reso_vs_amp_afterXY->SetLineColor( 1 );
	h1_reso_vs_amp_afterXY->Draw("E");
	h1_reso_vs_amp_afterXY->GetXaxis()->SetTitle("Amplitude [mV]");
	h1_reso_vs_amp_afterXY->GetYaxis()->SetTitle("time resolution [ns]");
	float maxY_t_ampbins_afterXY = std::min(0.2, 0.01+h1_reso_vs_amp_afterXY->GetMaximum()); 
	h1_reso_vs_amp_afterXY->GetYaxis()->SetRangeUser(0.02,maxY_t_ampbins_afterXY);
	h1_reso_vs_amp_afterXY->SetTitle("");
	h1_reso_vs_amp_afterXY->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h1_reso_vs_amp_afterXY->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h1_reso_vs_amp_afterXY->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h1_reso_vs_amp_afterXY->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins_afterXY_timereso_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins_afterXY_timereso_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_ampbins_afterXY_timereso_ch"+ch1+analysis_tag+".C").c_str());


	//time resolution in effective amplitude bins
	myC->SetGridy(0);
	myC->SetGridx(0);

	float effamp_low_afterXY = effamp_low;
	float effamp_high_afterXY = effamp_high;

	TH1F * h1_reso_vs_effamp_afterXY =  new TH1F("h1_reso_vs_effamp_afterXY","h1_reso_vs_effamp_afterXY", 10, effamp_low_afterXY, effamp_high_afterXY);
	
	for(int ieffamp = 1; ieffamp<=10; ieffamp++)
	{
		float thisAmp_low = effamp_low_afterXY + (ieffamp-1)*(effamp_high_afterXY-effamp_low_afterXY)/10.0;
		float thisAmp_high = effamp_low_afterXY + ieffamp*(effamp_high_afterXY-effamp_low_afterXY)/10.0;
		
		TH1F * h_deltaT_corr = new TH1F(("h_deltaT_corr_effamp"+std::to_string(ieffamp)).c_str(),("h_deltaT_corr_effamp"+std::to_string(ieffamp)).c_str(),100000, -1000.0, 1000.0);
		//tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]>>h_deltaT_corr_effamp"+std::to_string(ieffamp)).c_str(),(cut_sipm+" && amp["+ch1+"]/baseline_RMS["+ch1+"]>"+std::to_string(thisAmp_low)+" && amp["+ch1+"]/baseline_RMS["+ch1+"]<"+std::to_string(thisAmp_high)).c_str());

        	tree->Draw((time_ch1+"["+ch1_tl+"]-"+time_ch2+"["+ch2+"]- (" + std::to_string(x_cor_xyonly_p0)+" + "
+std::to_string(x_cor_xyonly_p1)+"*x_dut[0] + "+std::to_string(x_cor_xyonly_p2)+"*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p3)+"*x_dut[0]*x_dut[0]*x_dut[0]+"+std::to_string(x_cor_xyonly_p4)+"*x_dut[0]*x_dut[0]*x_dut[0]*x_dut[0]+"
+std::to_string(y_cor_xyonly_p0)+" + "
+std::to_string(y_cor_xyonly_p1)+"*y_dut[0] + "+std::to_string(y_cor_xyonly_p2)+"*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p3)+"*y_dut[0]*y_dut[0]*y_dut[0]+"+std::to_string(y_cor_xyonly_p4)+"*y_dut[0]*y_dut[0]*y_dut[0]*y_dut[0]"
+")>>h_deltaT_corr_effamp"+std::to_string(ieffamp)).c_str(),(cut_sipm+" && amp["+ch1+"]/baseline_RMS["+ch1+"]>"+std::to_string(thisAmp_low)+" && amp["+ch1+"]/baseline_RMS["+ch1+"]<"+std::to_string(thisAmp_high)).c_str());


		if(h_deltaT_corr->Integral() < 100.0) 
		{
			h1_reso_vs_effamp_afterXY->SetBinContent(ieffamp,-999.9);
			continue;	
		}	
		
		h_deltaT_corr->SetTitle("");
		h_deltaT_corr->SetMarkerStyle( 20 );
		h_deltaT_corr->SetMarkerColor( 1 );
		h_deltaT_corr->SetLineColor( 1 );
		h_deltaT_corr->GetXaxis()->SetTitle(("#Delta T (ch"+ch1+", ch"+ch2+") / ns").c_str());
		h_deltaT_corr->GetYaxis()->SetTitle("Events");
		h_deltaT_corr->SetTitle("");
		h_deltaT_corr->GetXaxis()->SetTitleSize( axisTitleSizeX );
		h_deltaT_corr->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
		h_deltaT_corr->GetYaxis()->SetTitleSize( axisTitleSizeY );
		h_deltaT_corr->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
		float maxY_t = h_deltaT_corr->GetMaximum();
		float maxX_t = h_deltaT_corr->GetBinCenter(h_deltaT_corr->GetMaximumBin());
		h_deltaT_corr->GetXaxis()->SetRangeUser(maxX_t-0.6, maxX_t+0.6);
		h_deltaT_corr->Draw("E");

		float highDeltaT=maxX_t+fit_range_right_noRes;//+0.02;//h_deltaT_corr->GetBinCenter(h_deltaT_corr->FindLastBinAbove(int(0.3*maxY_t)));
		float lowDeltaT=maxX_t-fit_range_left_noRes;//-0.08;//h_deltaT_corr->GetBinCenter(h_deltaT_corr->FindFirstBinAbove(int(0.1*maxY_t)));
		//if(highDeltaT - maxX_t > 2.0*(maxX_t-lowDeltaT)) highDeltaT = maxX_t + (maxX_t - lowDeltaT);
		TF1 * tf1_gaus = new TF1("tf1_gaus","gaus", maxX_t - 1.0, maxX_t + 1.0);
		tf1_gaus->SetParameter(1, h_deltaT_corr->GetMean());
		h_deltaT_corr->Fit("tf1_gaus","","",lowDeltaT, highDeltaT);
		
		float sigmaT = tf1_gaus->GetParameter(2);	
		float sigmaTerror = tf1_gaus->GetParError(2);	
		if(sigmaT < h1_reso_vs_effamp->GetBinContent(ieffamp))
		{
		h1_reso_vs_effamp_afterXY->SetBinContent(ieffamp,sigmaT);
		h1_reso_vs_effamp_afterXY->SetBinError(ieffamp,sigmaTerror);
		}
		else
		{
		h1_reso_vs_effamp_afterXY->SetBinContent(ieffamp,h1_reso_vs_effamp->GetBinContent(ieffamp));
		h1_reso_vs_effamp_afterXY->SetBinError(ieffamp,h1_reso_vs_effamp->GetBinError(ieffamp));
		}

		gPad->Modified();
		gPad->Update();

		myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins_afterXY"+std::to_string(thisAmp_low)+"_deltaT_corr_ch"+ch1+analysis_tag+".pdf").c_str());
		myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins_afterXY"+std::to_string(thisAmp_low)+"_deltaT_corr_ch"+ch1+analysis_tag+".png").c_str());
		myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins_afterXY"+std::to_string(thisAmp_low)+"_deltaT_corr_ch"+ch1+analysis_tag+".C").c_str());
		
	}	

	h1_reso_vs_effamp_afterXY->SetMarkerStyle( 20 );
	h1_reso_vs_effamp_afterXY->SetMarkerColor( 1 );
	h1_reso_vs_effamp_afterXY->SetLineColor( 1 );
	h1_reso_vs_effamp_afterXY->Draw("E");
	h1_reso_vs_effamp_afterXY->GetXaxis()->SetTitle("A/#sigma");
	h1_reso_vs_effamp_afterXY->GetYaxis()->SetTitle("time resolution [ns]");
	float maxY_t_effampbins_afterXY = std::min(0.2, 0.01+h1_reso_vs_effamp_afterXY->GetMaximum()); 
	h1_reso_vs_effamp_afterXY->GetYaxis()->SetRangeUser(0.02,maxY_t_effampbins_afterXY);
	h1_reso_vs_effamp_afterXY->SetTitle("");
	h1_reso_vs_effamp_afterXY->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h1_reso_vs_effamp_afterXY->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h1_reso_vs_effamp_afterXY->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h1_reso_vs_effamp_afterXY->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
 
	myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins_afterXY_timereso_ch"+ch1+analysis_tag+".pdf").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins_afterXY_timereso_ch"+ch1+analysis_tag+".png").c_str());
	myC->SaveAs((plotDir+"/Run"+inFileName+"_effampbins_afterXY_timereso_ch"+ch1+analysis_tag+".C").c_str());


	/////////////summary output///////////
	cout<<"[tot]:  [sigmaT_noCor=] "<<sigmaT_noCor<<"   [sigmaT_TWCor=] "<<sigmaT_TWCor<<"   [sigmaT_XYCor=] "<<sigmaT_XYCor<<"   [sigmaT_TWXYCor=] "<<sigmaT_TWXYCor<<"   [sigmaT_XYTWCor=] "<<sigmaT_XYTWCor<<endl;

	cout<<"[tot]:  [offsetXT_noCor=] "<<offsetXT_noCor<<"   [offsetYT_noCor=] "<<offsetYT_noCor<<"   [offsetXT_TWCor=] "<<offsetXT_TWCor<<"   [offsetYT_TWCor] "<<offsetYT_TWCor<<endl;
	
	cout<<inFileName<<" totTable  "<<offsetXT_noCor<<" "<<offsetXT_TWCor<<" "<<offsetYT_noCor<<" "<<offsetYT_TWCor<<" "<<sigmaT_noCor<<" "<<sigmaT_TWCor<<" "<<sigmaT_XYCor<<" "<<sigmaT_TWXYCor<<" "<<sigmaT_XYTWCor<<endl;
	cout<<inFileName<<" totError "<<offsetXT_noCor<<" "<<offsetXT_TWCor<<" "<<offsetYT_noCor<<" "<<offsetYT_TWCor<<" "<<sigmaT_noCor<<" \\pm "<<sigmaTerr_noCor<<" "<<sigmaT_TWCor<<" \\pm "<<sigmaTerr_TWCor<<" "<<sigmaT_XYCor<<" \\pm "<<sigmaTerr_XYCor<<" "<<sigmaT_TWXYCor<<" \\pm "<<sigmaTerr_TWXYCor<<" "<<sigmaT_XYTWCor<<" \\pm "<<sigmaTerr_XYTWCor<<endl;

}
