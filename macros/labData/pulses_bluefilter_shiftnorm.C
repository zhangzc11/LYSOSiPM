

void pulses_bluefilter_shiftnorm()
{
	TFile * f1 =  new TFile("~/LabData/Zhicai_Spring2018/data/1175_ana_withpulse.root");
	TTree * t1 = (TTree*)f1->Get("tree");

	TFile * f2 =  new TFile("~/LabData/Zhicai_Spring2018/data/1177_ana_withpulse.root");
	TTree * t2 = (TTree*)f2->Get("tree");

	TFile * f3 =  new TFile("~/LabData/Zhicai_Spring2018/data/1179_ana_withpulse.root");
	TTree * t3 = (TTree*)f3->Get("tree");

	time_left = 40.5;
	time_right = 44.5;

	float pulse1[1024];
	float time1[1024];

	float pulse2[1024];
	float time2[1024];
	
	float pulse3[1024];
	float time3[1024];

	float t1gausroot1;
	float t1gausroot2;
	float t1gausroot3;
	float ch2LinearTime601;
	float ch2LinearTime602;
	float ch2LinearTime603;
	
	float ch2Amp1;
	float ch2Amp2;
	float ch2Amp3;
	
	t1->SetBranchAddress("c2norm",pulse1);
	t1->SetBranchAddress("tishift2",time1);

	t2->SetBranchAddress("c2norm",pulse2);
	t2->SetBranchAddress("tishift2",time2);

	t3->SetBranchAddress("c2norm",pulse3);
	t3->SetBranchAddress("tishift2",time3);
	
	t1->SetBranchAddress("t1gausroot",&t1gausroot1);
	t1->SetBranchAddress("ch2LinearTime60",&ch2LinearTime601);

	t2->SetBranchAddress("t1gausroot",&t1gausroot2);
	t2->SetBranchAddress("ch2LinearTime60",&ch2LinearTime602);

	t3->SetBranchAddress("t1gausroot",&t1gausroot3);
	t3->SetBranchAddress("ch2LinearTime60",&ch2LinearTime603);

	
	t1->SetBranchAddress("ch2Amp",&ch2Amp1);
	t2->SetBranchAddress("ch2Amp",&ch2Amp2);
	t3->SetBranchAddress("ch2Amp",&ch2Amp3);

	float ex[1024] = {0.0};
	float ey[1024] = {0.0};

	TMultiGraph *mg = new TMultiGraph();

	for(int i=1;i<100;i++)
	{
	
	t1->GetEntry(i);
	t2->GetEntry(i);
	t3->GetEntry(i);

	if(ch2LinearTime601-t1gausroot1 > time_right-2 || ch2LinearTime601-t1gausroot1 < time_left ) continue;
	if(ch2LinearTime602-t1gausroot2 > time_right-2 || ch2LinearTime602-t1gausroot2 < time_left ) continue;
	if(ch2LinearTime603-t1gausroot3 > time_right-2 || ch2LinearTime603-t1gausroot3 < time_left ) continue;
	
	if(ch2Amp1 < 0.005) continue;
	if(ch2Amp2 < 0.005) continue;
	if(ch2Amp3 < 0.005) continue;
	
	TGraphErrors *gr1 = new TGraphErrors(1024, time1, pulse1, ex, ey);
	TGraphErrors *gr2 = new TGraphErrors(1024, time2, pulse2, ex, ey);
	TGraphErrors *gr3 = new TGraphErrors(1024, time3, pulse3, ex, ey);
	gr1->SetMarkerStyle(20);
	gr1->SetMarkerSize(0.6);
	gr1->SetMarkerColor(kBlue);
	gr1->SetLineColor(kBlue);

	gr2->SetMarkerStyle(20);
	gr2->SetMarkerSize(0.6);
	gr2->SetMarkerColor(kRed);
	gr2->SetLineColor(kRed);

	gr3->SetMarkerStyle(20);
	gr3->SetMarkerSize(0.6);
	gr3->SetMarkerColor(kViolet);
	gr3->SetLineColor(kViolet);

	mg->Add(gr1);	
	mg->Add(gr2);
	mg->Add(gr3);
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
	myC->SetGridx();
	myC->SetGridy();

	mg->Draw("APL");	
	mg->GetHistogram()->GetXaxis()->SetRangeUser(time_left, time_right);
	mg->GetHistogram()->GetXaxis()->SetTitle("time [ns]");
	mg->GetHistogram()->GetXaxis()->SetTitleSize(0.06);
	mg->GetHistogram()->GetXaxis()->SetTitleOffset(0.9);
	mg->GetHistogram()->GetYaxis()->SetTitleSize(0.05);
	mg->GetHistogram()->GetYaxis()->SetTitleOffset(1.1);
	mg->GetHistogram()->GetYaxis()->SetRangeUser(-1.2,0.5);
	mg->GetHistogram()->GetYaxis()->SetTitle("normlized amplitude");
	gPad->Modified();
   	gPad->Update();

	TLegend * leg = new TLegend(0.5,0.7,0.6,0.9);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.03);
	leg->SetLineColor(1);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetFillStyle(1001);
	
	leg->AddEntry(gr1, "x = 3mm", "lp");
	leg->AddEntry(gr2, "x = 5mm", "lp");
	leg->AddEntry(gr3, "x = 7mm", "lp");
	leg->Draw();

	myC->SaveAs("~/LabData/Zhicai_Spring2018/plots/pulses_407nmfilter_norm.pdf");
	myC->SaveAs("~/LabData/Zhicai_Spring2018/plots/pulses_407nmfilter_norm.png");
	myC->SaveAs("~/LabData/Zhicai_Spring2018/plots/pulses_407nmfilter_norm.C");

}
