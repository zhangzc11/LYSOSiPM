

void pulses_UV()
{
	TFile * f1 =  new TFile("~/LabData/Zhicai_Spring2018/data/1024.root");
	TTree * t1 = (TTree*)f1->Get("T");

	TFile * f2 =  new TFile("~/LabData/Zhicai_Spring2018/data/1030.root");
	TTree * t2 = (TTree*)f2->Get("T");

	TFile * f3 =  new TFile("~/LabData/Zhicai_Spring2018/data/1039.root");
	TTree * t3 = (TTree*)f3->Get("T");


	float pulse1[1024];
	float time1[1024];

	float pulse2[1024];
	float time2[1024];
	
	float pulse3[1024];
	float time3[1024];
	
	t1->SetBranchAddress("c2",pulse1);
	t1->SetBranchAddress("t2",time1);

	t2->SetBranchAddress("c2",pulse2);
	t2->SetBranchAddress("t2",time2);

	t3->SetBranchAddress("c2",pulse3);
	t3->SetBranchAddress("t2",time3);

	t1->GetEntry(2);
	t2->GetEntry(14);
	t3->GetEntry(22);
	
	float ex[1024] = {0.0};
	float ey[1024] = {0.0};
	
	for(int i=0;i<1024;i++)
	{
		pulse1[i] = pulse1[i]*1.0;
		pulse3[i] = pulse3[i]*1.0;
	}
	
	TGraphErrors *gr1 = new TGraphErrors(1024, time1, pulse1, ex, ey);
	TGraphErrors *gr2 = new TGraphErrors(1024, time2, pulse2, ex, ey);
	TGraphErrors *gr3 = new TGraphErrors(1024, time3, pulse3, ex, ey);
	
	gr1->SetMarkerStyle(20);
	gr1->SetMarkerColor(kBlue);
	gr1->SetLineColor(kBlue);

	gr2->SetMarkerStyle(20);
	gr2->SetMarkerColor(kRed);
	gr2->SetLineColor(kRed);

	gr3->SetMarkerStyle(20);
	gr3->SetMarkerColor(kViolet);
	gr3->SetLineColor(kViolet);


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

	TMultiGraph *mg = new TMultiGraph();
	mg->Add(gr1);	
	mg->Add(gr2);
	mg->Add(gr3);
	mg->Draw("APL");	
	mg->GetHistogram()->GetXaxis()->SetRangeUser(105.0,125.0);
	mg->GetHistogram()->GetXaxis()->SetTitle("time [ns]");
	mg->GetHistogram()->GetXaxis()->SetTitleSize(0.06);
	mg->GetHistogram()->GetXaxis()->SetTitleOffset(0.9);
	mg->GetHistogram()->GetYaxis()->SetTitleSize(0.05);
	mg->GetHistogram()->GetYaxis()->SetTitleOffset(1.1);
	mg->GetHistogram()->GetYaxis()->SetTitle("amplitude [V]");
	gPad->Modified();
   	gPad->Update();

	TLegend * leg = new TLegend(0.5,0.3,0.9,0.5);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.03);
	leg->SetLineColor(1);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetFillStyle(1001);
	
	leg->AddEntry(gr2, "w/o   LYSO", "lp");
	leg->AddEntry(gr1, "w/   LYSO, w/o grease", "lp");
	leg->AddEntry(gr3, "w/  LYSO, w/  grease", "lp");
	leg->Draw();

	myC->SaveAs("~/LabData/Zhicai_Spring2018/plots/pulses_373nm.pdf");
	myC->SaveAs("~/LabData/Zhicai_Spring2018/plots/pulses_373nm.png");
	myC->SaveAs("~/LabData/Zhicai_Spring2018/plots/pulses_373nm.C");

}
