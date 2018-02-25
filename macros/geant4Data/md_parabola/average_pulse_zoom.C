
void average_pulse_zoom()
{

	const double normNphoton0 = 31890.0;
    const double normNphoton2 = 68900.0;
    const double normNphoton5 = 5571.0;
    const int nDigi = 1024;

    TFile *f0 = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/ntuple_x0_4mm_md_ps_parabola_withWL.root");
    TFile *f2 = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/ntuple_x2.root");
    TFile *f5 = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/ntuple_x5_4mm_md_ps_parabola_withWL.root");
    TTree *tree0 = (TTree*)f0->Get("tree");
    TTree *tree2 = (TTree*)f2->Get("tree");
    TTree *tree5 = (TTree*)f5->Get("tree");


	std::vector<double> * time1 = 0;
	std::vector<double> * amp1 = 0;
	Int_t nPhotons;
	tree0->SetBranchAddress("nPhotons", &nPhotons);
	tree0->SetBranchAddress("time2", &time1);
	tree0->SetBranchAddress("amp2", &amp1);

	tree2->SetBranchAddress("nPhotons", &nPhotons);
	tree2->SetBranchAddress("time2", &time1);
	tree2->SetBranchAddress("amp2", &amp1);

	tree5->SetBranchAddress("nPhotons", &nPhotons);
	tree5->SetBranchAddress("time2", &time1);
	tree5->SetBranchAddress("amp2", &amp1);

	int NEntries0 = tree0->GetEntries();
	int NEntries2 = tree2->GetEntries();
	int NEntries5 = tree5->GetEntries();

	tree0->GetEntry(1);

	double average_amp0[nDigi];
	double average_amp2[nDigi];
	double average_amp5[nDigi];
	double ex[nDigi];
	double average_time0[nDigi];
	double average_time2[nDigi];
	double average_time5[nDigi];
	double ey[nDigi];

	for(int i=0;i<nDigi;i++)
	{
		average_amp0[i] = 0.0;
		average_amp2[i] = 0.0;
		average_amp5[i] = 0.0;
		average_time0[i] = 0.0;
		average_time2[i] = 0.0;
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
			else average_amp0[j] += amp1->at(j) * normNphoton0 / nPhotons;
		}
	}

	for(int i=1;i<=NEntries2;i++)
	{
		tree2->GetEntry(i);
		for(int j=0;j < amp1->size();j++)
		{
			if(j>=nDigi) break;
			else average_amp2[j] += amp1->at(j) * normNphoton2 / nPhotons;
		}
	}

	for(int i=1;i<=NEntries5;i++)
	{
		tree5->GetEntry(i);
		for(int j=0;j < amp1->size();j++)
		{
			if(j>=nDigi) break;
			else average_amp5[j] += amp1->at(j) * normNphoton5 / nPhotons;
		}
	}



	for(int i=0;i<nDigi;i++)
	{
		if(i<amp1->size())
		{
			average_amp0[i] = average_amp0[i]/NEntries0;
			average_amp2[i] = average_amp2[i]/NEntries2;
			average_amp5[i] = average_amp5[i]/NEntries5;
			average_time0[i] = time1->at(i);
			average_time2[i] = time1->at(i);
			average_time5[i] = time1->at(i);
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

	TGraphErrors *gr0 = new TGraphErrors(nDigi, average_time0, average_amp0, ex, ey);
	gr0->SetMarkerStyle(20);
    gr0->SetMarkerSize(0.6);
    gr0->SetMarkerColor(kBlue);
    gr0->SetLineColor(kBlue);

	TGraphErrors *gr2 = new TGraphErrors(nDigi, average_time2, average_amp2, ex, ey);
	gr2->SetMarkerStyle(20);
    gr2->SetMarkerSize(0.6);
    gr2->SetMarkerColor(kRed);
    gr2->SetLineColor(kRed);

	TGraphErrors *gr5 = new TGraphErrors(nDigi, average_time5, average_amp5, ex, ey);
	gr5->SetMarkerStyle(20);
    gr5->SetMarkerSize(0.6);
    gr5->SetMarkerColor(kViolet);
    gr5->SetLineColor(kViolet);


	mg->Add(gr0);
	//mg->Add(gr2);
	mg->Add(gr5);

	mg->Draw("AL");
	//mg->GetHistogram()->GetXaxis()->SetRangeUser(time->at(0), time->at(time->size()-1));
	mg->GetHistogram()->GetXaxis()->SetTitle("time [ns]");
	mg->GetHistogram()->GetXaxis()->SetTitleSize(0.06);
	mg->GetHistogram()->GetXaxis()->SetTitleOffset(0.9);
	mg->GetHistogram()->GetYaxis()->SetTitleSize(0.05);
	mg->GetHistogram()->GetYaxis()->SetTitleOffset(1.1);
	//mg->GetHistogram()->GetYaxis()->SetRangeUser(-1.2,0.5);
	mg->GetHistogram()->GetYaxis()->SetTitle("photon current [ns^{-1}]");
	gPad->Modified();
	gPad->Update();


    TLegend * leg = new TLegend(0.5,0.5,0.6,0.7);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.03);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(0);
    leg->SetFillStyle(1001);

    leg->AddEntry(gr0, "x = 0mm", "l");
    //leg->AddEntry(gr2, "x = 2mm", "l");
    leg->AddEntry(gr5, "x = 5mm", "l");
    leg->Draw();

	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_parabola_average_pulses_zoom.pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_parabola_average_pulses_zoom.png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_parabola_average_pulses_zoom.C");

	}
