
void average_pulse_zoom()
{
	//const double normNphoton0 = 118600.0;
	//const double normNphoton5 = 97100.0;
	const int nDigi = 1024;

	TFile *f_center = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/ntuple_ref_center.root");
	TFile *f_edge = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/ntuple_ref_edge.root");
	TTree *tree_center = (TTree*)f_center->Get("tree");
	TTree *tree_edge = (TTree*)f_edge->Get("tree");
	

	std::vector<double> * time1 = 0;
	std::vector<double> * amp1 = 0;
	Int_t nPhotons;
	tree_center->SetBranchAddress("nPhotons", &nPhotons);
	tree_center->SetBranchAddress("time2", &time1);
	tree_center->SetBranchAddress("amp2_sptr", &amp1);

	tree_edge->SetBranchAddress("nPhotons", &nPhotons);
	tree_edge->SetBranchAddress("time2", &time1);
	tree_edge->SetBranchAddress("amp2_sptr", &amp1);

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
		for(int j=0;j < amp1->size();j++)
		{
			if(j>=nDigi) break;
			else average_amp_center[j] += amp1->at(j);// * normNphoton0 / nPhotons;
		}
	}

	for(int i=1;i<=NEntries_edge;i++)
	{
		tree_edge->GetEntry(i);
		for(int j=0;j < amp1->size();j++)
		{
			if(j>=nDigi) break;
			else average_amp_edge[j] += amp1->at(j);// * normNphoton5 / nPhotons;
		}
	}



	for(int i=0;i<nDigi;i++)
	{
		if(i<amp1->size())
		{
			average_amp_center[i] = average_amp_center[i]/NEntries_center;
			average_amp_edge[i] = average_amp_edge[i]/NEntries_edge;
			average_time_center[i] = time1->at(i);
			average_time_edge[i] = time1->at(i);
		}
	}


	TCanvas * myC = new TCanvas( "myC", "myC", 200, 10, 1000, 700 );
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
	//myC->SetGridx();
	//myC->SetGridy();

	TMultiGraph *mg = new TMultiGraph();

	TGraphErrors *gr_center = new TGraphErrors(nDigi, average_time_center, average_amp_center, ex, ey);
	gr_center->SetMarkerStyle(20);
    gr_center->SetMarkerSize(0.6);
    gr_center->SetMarkerColor(kBlue);
    gr_center->SetLineColor(kBlue);

	TGraphErrors *gr_edge = new TGraphErrors(nDigi, average_time_edge, average_amp_edge, ex, ey);
	gr_edge->SetMarkerStyle(20);
    gr_edge->SetMarkerSize(0.6);
    gr_edge->SetMarkerColor(kViolet);
    gr_edge->SetLineColor(kViolet);


	mg->Add(gr_center);
	mg->Add(gr_edge);

	mg->Draw("AL");
	//mg->GetHistogram()->GetXaxis()->SetRangeUser(time->at(0), time->at(time->size()-1));
	mg->GetHistogram()->GetXaxis()->SetTitle("time [ns]");
	mg->GetHistogram()->GetXaxis()->SetTitleSize(0.06);
	mg->GetHistogram()->GetXaxis()->SetTitleOffset(0.9);
	mg->GetHistogram()->GetYaxis()->SetTitleSize(0.05);
	mg->GetHistogram()->GetYaxis()->SetTitleOffset(1.1);
	//mg->GetHistogram()->GetYaxis()->SetRangeUser(-1.2,0.5);
	mg->GetHistogram()->GetYaxis()->SetTitle("p.e. current [ns^{-1}]");
	gPad->Modified();
	gPad->Update();


    TLegend * leg = new TLegend(0.65,0.2,0.85,0.35);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.05);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(0);
    leg->SetFillStyle(1001);

    leg->AddEntry(gr_center, "center IP", "l");
    leg->AddEntry(gr_edge, "edge IP", "l");
    leg->Draw();

	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/average_pulses_ref_zoom.pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/average_pulses_ref_zoom.png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/average_pulses_ref_zoom.C");

	}
