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

	TH2F * h2_allPhoTime_vs_phoIndex = new TH2F("h2_allPhoTime_vs_phoIndex","h2_allPhoTime_vs_phoIndex", 200, 0, 200, 100, 0, 1.5);
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


float drawT100(TTree * tree_center, TTree * tree_edge, std::string& inFileName, std::string& plotDir)
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
	
	TH1F * h100_center = new TH1F("h100_center","h100_center",150,0,2.5);
	TH1F * h100_edge = new TH1F("h100_edge","h100_edge",150,0,2.5);
	tree_center->Draw("allPhoTime_sptr>>h100_center","allPhoIndex==100");
	tree_edge->Draw("allPhoTime_sptr>>h100_edge","allPhoIndex==100");

	h100_center->SetTitle("");
	h100_center->GetXaxis()->SetTitle("t_{100} [ns]");
	h100_center->GetYaxis()->SetTitle("Events");
	h100_center->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h100_center->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h100_center->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h100_center->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h100_center->SetLineWidth(4);
	h100_center->SetLineColor(kRed);
	h100_center->Draw("hist");
	myC->SaveAs((plotDir+inFileName+"_time_photon100_center.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_center.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_center.C").c_str());

	h100_edge->SetTitle("");
	h100_edge->GetXaxis()->SetTitle("t_{100} [ns]");
	h100_edge->GetYaxis()->SetTitle("Events");
	h100_edge->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h100_edge->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h100_edge->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h100_edge->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h100_edge->SetLineWidth(4);
	h100_edge->SetLineColor(kBlue);
	h100_edge->Draw("hist");
	myC->SaveAs((plotDir+inFileName+"_time_photon100_edge.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_edge.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_edge.C").c_str());

	h100_center->Scale(1.0/h100_center->Integral());
	h100_edge->Scale(1.0/h100_edge->Integral());

	float maxY = 1.5*h100_center->GetMaximum();
	if(1.5*h100_edge->GetMaximum() > 1.5*h100_center->GetMaximum()) maxY =1.5*h100_edge->GetMaximum();
	h100_center->GetYaxis()->SetRangeUser(0.0, maxY);

	h100_center->Draw("hist");
	h100_edge->Draw("histsame");

	TLegend * leg  = new TLegend (0.25,0.77,0.80,0.92);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.06);
	leg->SetLineColor(1);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetFillStyle(1001);

	leg->AddEntry(h100_center, "center impact point", "l");
	leg->AddEntry(h100_edge, "edge impact point", "l");
	leg->Draw();		
	
	float deltaT_f = 1000.0*(h100_edge->GetBinCenter(h100_edge->GetMaximumBin()) - h100_center->GetBinCenter(h100_center->GetMaximumBin()));
	int deltaT = int(deltaT_f);

	       	
	TLatex *tlatex =  new TLatex();
	tlatex->SetNDC();
	tlatex->SetTextAngle(0);
	tlatex->SetTextColor(kBlack);
	tlatex->SetTextFont(63);
	tlatex->SetTextAlign(11);
	tlatex->SetTextSize(45);
	TString ts_dt;
	ts_dt.Form("%d",deltaT);
	tlatex->DrawLatex(0.40, 0.68, "#Delta T = "+ ts_dt +" ps");

		
	myC->SaveAs((plotDir+inFileName+"_time_photon100_centerEdge.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_centerEdge.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon100_centerEdge.C").c_str());

	delete myC;
	delete h100_center;
	delete h100_edge;
	delete leg;
	delete tlatex;
	return deltaT_f;

}

float drawT60(TTree * tree_center, TTree * tree_edge, std::string& inFileName, std::string& plotDir)
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
	
	TH1F * h20_center = new TH1F("h20_center","h20_center",140,0,2.0);
	TH1F * h20_edge = new TH1F("h20_edge","h20_edge",140,0,2.0);
	tree_center->Draw("allPhoTime_sptr>>h20_center","allPhoIndex==60");
	tree_edge->Draw("allPhoTime_sptr>>h20_edge","allPhoIndex==60");

	h20_center->SetTitle("");
	h20_center->GetXaxis()->SetTitle("t_{60} [ns]");
	h20_center->GetYaxis()->SetTitle("Events");
	h20_center->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h20_center->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h20_center->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h20_center->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h20_center->SetLineWidth(4);
	h20_center->SetLineColor(kRed);
	h20_center->Draw("hist");
	myC->SaveAs((plotDir+inFileName+"_time_photon60_center.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon60_center.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon60_center.C").c_str());

	h20_edge->SetTitle("");
	h20_edge->GetXaxis()->SetTitle("t_{20} [ns]");
	h20_edge->GetYaxis()->SetTitle("Events");
	h20_edge->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h20_edge->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h20_edge->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h20_edge->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h20_edge->SetLineWidth(4);
	h20_edge->SetLineColor(kBlue);
	h20_edge->Draw("hist");
	myC->SaveAs((plotDir+inFileName+"_time_photon60_edge.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon60_edge.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon60_edge.C").c_str());

	h20_center->Scale(1.0/h20_center->Integral());
	h20_edge->Scale(1.0/h20_edge->Integral());

	float maxY = 1.5*h20_center->GetMaximum();
	if(1.5*h20_edge->GetMaximum() > 1.5*h20_center->GetMaximum()) maxY =1.5*h20_edge->GetMaximum();
	h20_center->GetYaxis()->SetRangeUser(0.0, maxY);

	h20_center->Draw("hist");
	h20_edge->Draw("histsame");

	TLegend * leg  = new TLegend (0.25,0.77,0.80,0.92);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.06);
	leg->SetLineColor(1);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetFillStyle(201);

	leg->AddEntry(h20_center, "center impact point", "l");
	leg->AddEntry(h20_edge, "edge impact point", "l");
	leg->Draw();		
	
	float deltaT_f = 200.0*(h20_edge->GetBinCenter(h20_edge->GetMaximumBin()) - h20_center->GetBinCenter(h20_center->GetMaximumBin()));
	int deltaT = int(deltaT_f);

	       	
	TLatex *tlatex =  new TLatex();
	tlatex->SetNDC();
	tlatex->SetTextAngle(0);
	tlatex->SetTextColor(kBlack);
	tlatex->SetTextFont(63);
	tlatex->SetTextAlign(11);
	tlatex->SetTextSize(45);
	TString ts_dt;
	ts_dt.Form("%d",deltaT);
	tlatex->DrawLatex(0.40, 0.68, "#Delta T = "+ ts_dt +" ps");
		
	myC->SaveAs((plotDir+inFileName+"_time_photon60_centerEdge.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon60_centerEdge.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_time_photon60_centerEdge.C").c_str());

	delete myC;
	delete h20_center;
	delete h20_edge;
	delete leg;
	delete tlatex;
	return deltaT_f;

}

void draw_average_pulse(TTree * tree_center, TTree * tree_edge, std::string& inFileName, std::string& plotDir, std::string & timetag)
{
	const int nDigi = 1024;

	std::vector<double> * time1 = 0;
	std::vector<double> * time2 = 0;
	std::vector<double> * amp1 = 0;
	std::vector<double> * amp2 = 0;
	Int_t nPhotons;
	
	tree_center->SetBranchAddress("nPhotons", &nPhotons);
	tree_center->SetBranchAddress("time1", &time1);
	tree_center->SetBranchAddress("time2", &time2);
	tree_center->SetBranchAddress("amp1_sptr", &amp1);
	tree_center->SetBranchAddress("amp2_sptr", &amp2);
	//tree_center->SetBranchAddress(("time"+timetag).c_str(), &time1);
	//tree_center->SetBranchAddress(("amp"+timetag+"_sptr").c_str(), &amp1);	
	
	tree_edge->SetBranchAddress("nPhotons", &nPhotons);
	tree_edge->SetBranchAddress("time1", &time1);
	tree_edge->SetBranchAddress("time2", &time2);
	tree_edge->SetBranchAddress("amp1_sptr", &amp1);
	tree_edge->SetBranchAddress("amp2_sptr", &amp2);

	//tree_edge->SetBranchAddress(("time"+timetag).c_str(), &time1);
	//tree_edge->SetBranchAddress(("amp"+timetag+"_sptr").c_str(), &amp1);

	int NEntries_center = tree_center->GetEntries();
	int NEntries_edge = tree_edge->GetEntries();
	
	tree_center->GetEntry(1);

	double average_amp_center[nDigi];
	double average_amp_edge[nDigi];
	double ex[nDigi];
	double average_time_center[nDigi];
	double average_time_edge[nDigi];
	double ey[nDigi];

	for(int i=0;i<nDigi;i++)
        {
                average_amp_center[i] = 0.0;
                average_amp_edge[i] = 0.0;
                average_time_center[i] = 0.0;
                average_time_edge[i] = 0.0;
                ex[i] = 0.0;
                ey[i] = 0.0;
        }	
	
	for(int i=1;i<=NEntries_center;i++)
        {
                tree_center->GetEntry(i);
				if(timetag == "1")
				{
                for(int j=0;j < amp1->size();j++)
                {
                        if(j>=nDigi) break;
                        else average_amp_center[j] += amp1->at(j);
                }
				}
				if(timetag == "2")
				{
				for(int j=0;j < amp2->size();j++)
                {
                        if(j>=nDigi) break;
                        else average_amp_center[j] += amp2->at(j);
                }
				}

        }
        for(int i=1;i<=NEntries_edge;i++)
        {
                tree_edge->GetEntry(i);
				if(timetag == "1")	
				{
                for(int j=0;j < amp1->size();j++)
                {
                        if(j>=nDigi) break;
                        else average_amp_edge[j] += amp1->at(j);// * nPhotons_edge / nPhotons;
                }
				}
				if(timetag == "2")
				{
				for(int j=0;j < amp2->size();j++)
                {
                        if(j>=nDigi) break;
                        else average_amp_edge[j] += amp2->at(j);// * nPhotons_edge / nPhotons;
                }

				}
        }	

	for(int i=0;i<nDigi;i++)
        {
				if(timetag == "1")
				{
                if(i<amp1->size())
                {
                        average_amp_center[i] = average_amp_center[i]/NEntries_center;
                        average_amp_edge[i] = average_amp_edge[i]/NEntries_edge;
                        average_time_center[i] = time1->at(i);
                        average_time_edge[i] = time1->at(i);
                }
				}
				if(timetag == "2")
				{
				 if(i<amp2->size())
                {
                        average_amp_center[i] = average_amp_center[i]/NEntries_center;
                        average_amp_edge[i] = average_amp_edge[i]/NEntries_edge;
                        average_time_center[i] = time2->at(i);
                        average_time_edge[i] = time2->at(i);
                }

				}

        }	
		
	TCanvas *myC = new TCanvas( "myC", "myC", 200, 10, 1000, 700 );
	myC->SetHighLightColor(2);
	myC->SetFillColor(0);
	myC->SetBorderMode(0);
	myC->SetBorderSize(2);
	myC->SetLeftMargin( 0.12 );
	myC->SetRightMargin( 0.05 );
	myC->SetTopMargin( 0.07 );
	myC->SetBottomMargin( 0.12 );
	myC->SetFrameBorderMode(0);
	myC->SetFrameBorderMode(0);

	TMultiGraph *mg = new TMultiGraph();
	
	TGraphErrors *gr_center = new TGraphErrors(nDigi, average_time_center, average_amp_center, ex, ey);
	gr_center->SetMarkerStyle(20);
	gr_center->SetMarkerSize(0.6);
	gr_center->SetMarkerColor(kBlue);
	gr_center->SetLineColor(kBlue);
	
	TGraphErrors *gr_edge = new TGraphErrors(nDigi, average_time_edge, average_amp_edge, ex, ey);
	gr_edge->SetMarkerStyle(20);
	gr_edge->SetMarkerSize(0.6);
	gr_edge->SetMarkerColor(kRed);
	gr_edge->SetLineColor(kRed);
	
	mg->Add(gr_center);
	mg->Add(gr_edge);
	mg->Draw("AL");
	mg->GetHistogram()->GetXaxis()->SetTitle("time [ns]");
	mg->GetHistogram()->GetXaxis()->SetTitleSize( axisTitleSizeX );
	mg->GetHistogram()->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	mg->GetHistogram()->GetYaxis()->SetTitleSize( axisTitleSizeY );
	mg->GetHistogram()->GetYaxis()->SetTitleOffset( axisTitleOffsetY );

	mg->GetHistogram()->GetYaxis()->SetTitle("photon current [ns^{-1}]");
	gPad->Modified();
	gPad->Update();

		
	TLegend * leg;
	if(timetag == "1") leg = new TLegend(0.55,0.75,0.85,0.9);
	else leg = new TLegend(0.55,0.2,0.85,0.35);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.06);
	leg->SetLineColor(1);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetFillStyle(1001);

	leg->AddEntry(gr_center, "center impact point", "l");
	leg->AddEntry(gr_edge, "edge impact point", "l");
	leg->Draw();		

	if(timetag == "1")
	{
	myC->SaveAs((plotDir+inFileName+"_average_pulses_centerEdge.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_average_pulses_centerEdge.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_average_pulses_centerEdge.C").c_str());
	}
	else
	{
	myC->SaveAs((plotDir+inFileName+"_average_pulses_zoom_centerEdge.pdf").c_str());
        myC->SaveAs((plotDir+inFileName+"_average_pulses_zoom_centerEdge.png").c_str());
        myC->SaveAs((plotDir+inFileName+"_average_pulses_zoom_centerEdge.C").c_str());
	}
	
	delete myC;
	delete gr_center;
	delete gr_edge;
	delete leg;	
	delete amp1;
	delete amp2;
	delete time1;
	delete time2;
}

float  * draw_nPhotons(TTree * tree, std::string& inFileName, std::string& plotDir, std::string varName, std::string varTitle, float maxValue)
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


	TH1F * h1_np = new TH1F("h1_np","h1_np", 30, 0, maxValue);
	tree->Draw((varName+">>h1_np").c_str());
	TF1 * f1_landau = new TF1("flandau","[0]*TMath::Landau(x,[1],[2])", 0, maxValue);	
	f1_landau->SetParameters(h1_np->GetMaximum(), h1_np->GetBinCenter(h1_np->GetMaximumBin()), 10.0);

	h1_np->SetMarkerStyle( 20 );
        h1_np->SetMarkerColor( kBlack );
        h1_np->SetLineColor( kBlack );
	
	h1_np->GetXaxis()->SetTitle(varTitle.c_str());
        h1_np->GetYaxis()->SetTitle("Events");
        h1_np->SetTitle("");
        h1_np->GetXaxis()->SetTitleSize( axisTitleSizeX );
        h1_np->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
        h1_np->GetYaxis()->SetTitleSize( axisTitleSizeY );
        h1_np->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
        h1_np->Draw("E");
	h1_np->Fit("flandau", "Q", "", 0, maxValue);
	float nphotons_this = f1_landau->GetParameter(1);
	float enphotons_this = f1_landau->GetParError(1);
	
	gPad->Modified();
        gPad->Update();
	
	
	myC->SaveAs((plotDir+inFileName+"_nphotons_"+varName+".pdf").c_str());	
	myC->SaveAs((plotDir+inFileName+"_nphotons_"+varName+".png").c_str());	
	myC->SaveAs((plotDir+inFileName+"_nphotons_"+varName+".C").c_str());	
	
	delete myC;
	delete h1_np;
	delete f1_landau;
	
	float result[2] = {nphotons_this, enphotons_this};
	float * pointer = new float[2];
	pointer[0] = result[0];
	pointer[1] = result[1];
	return pointer;
	
}


float * drawRisetime(TTree * tree, std::string& inFileName, std::string& plotDir)
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

	TH1F * h_Risetime = new TH1F("h_Risetime","h_Risetime", 20, 0.0, 3.0);
	tree->Draw("risetime>>h_Risetime");
	h_Risetime->SetTitle("");
	float maxY_Risetime = 1.2*h_Risetime->GetMaximum();

	float maxX_ch1Risetime = h_Risetime->GetBinCenter(h_Risetime->GetMaximumBin());
	float highch1Risetime=h_Risetime->GetBinCenter(h_Risetime->FindLastBinAbove(int(0.5*h_Risetime->GetMaximum())));
	float lowch1Risetime=0.0;//h_Risetime->GetBinCenter(h_Risetime->FindFirstBinAbove(int(0.1*h_Risetime->GetMaximum())));

	float max_ch1Risetime = 2.0*maxX_ch1Risetime;
	if(highch1Risetime+1.0 > 2.0*maxX_ch1Risetime ) max_ch1Risetime = highch1Risetime+1.0;

	h_Risetime->SetMarkerStyle( 20 );
	h_Risetime->SetMarkerColor( kBlack );
	h_Risetime->SetLineColor( kBlack );
	h_Risetime->GetXaxis()->SetTitle("risetime [ns]");
	h_Risetime->GetYaxis()->SetTitle("Events");
	h_Risetime->SetTitle("");
h_Risetime->GetXaxis()->SetTitleSize( axisTitleSizeX );
	h_Risetime->GetXaxis()->SetTitleOffset( axisTitleOffsetX );
	h_Risetime->GetYaxis()->SetTitleSize( axisTitleSizeY );
	h_Risetime->GetYaxis()->SetTitleOffset( axisTitleOffsetY );
	h_Risetime->GetYaxis()->SetRangeUser(0.0,maxY_Risetime);
	//h_Risetime->GetXaxis()->SetRangeUser(0.0,6.0);//max_ch1Risetime );
	h_Risetime->Draw("E");

	TF1 * tf1_gaus = new TF1("tf1_gaus","gaus",lowch1Risetime, highch1Risetime);
	tf1_gaus->SetParameter(1,h_Risetime->GetMean());
	h_Risetime->Fit("tf1_gaus","Q","",lowch1Risetime, highch1Risetime);

	gPad->Modified();
	gPad->Update();
	myC->SaveAs((plotDir+inFileName+"_risetime.pdf").c_str());
	myC->SaveAs((plotDir+inFileName+"_risetime.png").c_str());
	myC->SaveAs((plotDir+inFileName+"_risetime.C").c_str());
	
	delete myC; 
	float risetime_this =  tf1_gaus->GetParameter(1);
	float erisetime_this =  tf1_gaus->GetParError(1);
	
	float result[2] = {risetime_this, erisetime_this};
    float * pointer = new float[2];
    pointer[0] = result[0];
    pointer[1] = result[1];
    return pointer;

}



void goodplot_nocompile()
{
	std::string inFileName = "ntuple_ref_center";

	std::string inFileName_center = inFileName;
	
	std::string inFileName_edge = inFileName.replace(inFileName.find("center"), 6, "edge");
	std::string inFileName_centerEdge = inFileName.replace(inFileName.find("_edge"), 5, "");
	std::string plotDir = "/Users/zhicai/cernbox/TestBeam/geant4/plots/";


	TFile *f_center = new TFile(("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/"+inFileName_center+"_rereco.root").c_str(), "READ");
	TTree *tree_center = (TTree*)f_center->Get("tree");
	TFile *f_edge = new TFile(("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/"+inFileName_edge+"_rereco.root").c_str(), "READ");
	TTree *tree_edge = (TTree*)f_edge->Get("tree");

	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);

	draw_average_pulse(tree_center, tree_edge, inFileName_centerEdge, plotDir, "2");		
	draw_average_pulse(tree_center, tree_edge, inFileName_centerEdge, plotDir, "1");		
	//drawTracks(tree_center, inFileName_center, plotDir);
	//drawTracks(tree_edge, inFileName_edge, plotDir);

	float * risetime_center = drawRisetime(tree_center, inFileName_center, plotDir);
	float * risetime_edge = drawRisetime(tree_edge, inFileName_edge, plotDir);

	float deltaT_centerEdge = drawT60(tree_center, tree_edge, inFileName_centerEdge, plotDir);

	float * nPhotons_center = draw_nPhotons(tree_center, inFileName_center, plotDir, "nPhotons", "NPE", 15000.0);

	float * nPhotons_edge = draw_nPhotons(tree_edge, inFileName_edge, plotDir, "nPhotons", "NPE", 15000.0);

	float * nPhotons_peak_center = draw_nPhotons(tree_center, inFileName_center, plotDir, "int_peak", "NPE to peak", 10000.0);

	float nPhotons_peak_edge = draw_nPhotons(tree_edge, inFileName_edge, plotDir, "int_peak", "NPE to peak", 10000.0);

	float * nPhotons_full_center = draw_nPhotons(tree_center, inFileName_center, plotDir, "int_full", "NPE", 15000.0);

	float * nPhotons_full_edge = draw_nPhotons(tree_edge, inFileName_edge, plotDir, "int_full", "NPE", 15000.0);

	float  * nPhotons_amp_center = draw_nPhotons(tree_center, inFileName_center, plotDir, "amp", "amplitude [ns^{-1}]", 600.0);
	float * nPhotons_amp_edge = draw_nPhotons(tree_edge, inFileName_edge, plotDir, "amp", "amplitude [ns^{-1}]" ,600.0);
	float * nPhotons_firstbin_center = draw_nPhotons(tree_center, inFileName_center, plotDir, "int_firstbin", "NPE to first bin", 10.0);
	float * nPhotons_firstbin_edge = draw_nPhotons(tree_edge, inFileName_edge, plotDir, "int_firstbin", "NPE to first bin",10.0);
	
	FILE * m_outfile = fopen("table.tex","a");	

	fprintf(m_outfile, "%s  &  %.0f$\\pm$%.0f  &  %.0f$\\pm$ %.0f  &  %.1f$\\pm$%.1f  &  %.1f$\\pm$%.1f  &  %.2f$\\pm$%.2f  &  %.2f$\\pm$%.2f  &  %.0f \\\\ \n", inFileName_centerEdge.c_str(), nPhotons_center[0], nPhotons_center[1], nPhotons_edge[0], nPhotons_edge[1], nPhotons_amp_center[0], nPhotons_amp_center[1], nPhotons_amp_edge[0], nPhotons_amp_edge[1], risetime_center[0], risetime_center[1], risetime_edge[0], risetime_edge[1], deltaT_centerEdge);

}
