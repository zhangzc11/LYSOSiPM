
void average_pulse()
{
	const double normNphoton = 100000.0;
	const int nDigi = 1024;

	TFile *fin = new TFile("ntuple.root");
	TTree *tree = (TTree*)fin->Get("tree");
	

	std::vector<double> * time = 0;
	std::vector<double> * amp = 0;
	Double_t nPhotons;
	tree->SetBranchAddress("nPhotons", &nPhotons);
	tree->SetBranchAddress("time", &time);
	tree->SetBranchAddress("amp", &amp);

	int NEntries = tree->GetEntries();

	tree->GetEntry(1);

	double average_amp1[nDigi];
	double ex[nDigi];
	double average_time1[nDigi];
	double ey[nDigi];

	for(int i=0;i<nDigi;i++)
	{
		average_amp1[i] = 0.0;
		average_time1[i] = 0.0;
		ex[i] = 0.0;
		ey[i] = 0.0;
	}

	int totalCount1 = 0;

	for(int i=1;i<=NEntries;i++)
	{
		tree->GetEntry(i);
		//cout<<"nPhotons = "<<nPhotons<<"  time[500] = "<<time->at(500)<<"  amp[500] = "<<amp->at(500)<<endl;
		totalCount1 ++;

		for(int j=0;j < amp->size();j++)
		{
			if(j>=nDigi) break;
			if(j<6 && amp->at(j)>1000) average_amp1[j] += 0.0;//0.5*(amp->at(j-1)+amp->at(j+1)) * normNphoton / nPhotons;

			else average_amp1[j] += amp->at(j) * normNphoton / nPhotons;
		}
	}

	cout<<"totalCount1 = "<<totalCount1<<endl;
	for(int i=0;i<nDigi;i++)
	{
		if(i<amp->size())
		{
			average_amp1[i] = average_amp1[i]/totalCount1;
			average_time1[i] = time->at(i);
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

	TGraphErrors *gr1 = new TGraphErrors(nDigi, average_time1, average_amp1, ex, ey);

	gr1->SetMarkerStyle(20);
    gr1->SetMarkerSize(0.6);
    gr1->SetMarkerColor(kBlue);
    gr1->SetLineColor(kBlue);

	mg->Add(gr1);

	mg->Draw("AL");
	//mg->GetHistogram()->GetXaxis()->SetRangeUser(time->at(0), time->at(time->size()-1));
	mg->GetHistogram()->GetXaxis()->SetTitle("time [ns]");
	mg->GetHistogram()->GetXaxis()->SetTitleSize(0.06);
	mg->GetHistogram()->GetXaxis()->SetTitleOffset(0.9);
	mg->GetHistogram()->GetYaxis()->SetTitleSize(0.05);
	mg->GetHistogram()->GetYaxis()->SetTitleOffset(1.1);
	//mg->GetHistogram()->GetYaxis()->SetRangeUser(-1.2,0.5);
	mg->GetHistogram()->GetYaxis()->SetTitle("photon current");
	gPad->Modified();
	gPad->Update();

	myC->SaveAs("plots/average_pulses.pdf");
	myC->SaveAs("plots/average_pulses.png");
	myC->SaveAs("plots/average_pulses.C");

	}
