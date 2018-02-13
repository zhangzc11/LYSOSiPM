

void pulses_UV_bias()
{
	TFile * f1 =  new TFile("~/LabData/Zhicai_Spring2018/data/1084.root");//65
	TTree * t1 = (TTree*)f1->Get("T");

	TFile * f2 =  new TFile("~/LabData/Zhicai_Spring2018/data/1086.root");//66
	TTree * t2 = (TTree*)f2->Get("T");

	TFile * f3 =  new TFile("~/LabData/Zhicai_Spring2018/data/1088.root");//67
	TTree * t3 = (TTree*)f3->Get("T");

	TFile * f4 =  new TFile("~/LabData/Zhicai_Spring2018/data/1090.root");//68
	TTree * t4 = (TTree*)f4->Get("T");

	TFile * f5 =  new TFile("~/LabData/Zhicai_Spring2018/data/1092.root");//69
	TTree * t5 = (TTree*)f5->Get("T");

	TFile * f6 =  new TFile("~/LabData/Zhicai_Spring2018/data/1094.root");//70
	TTree * t6 = (TTree*)f6->Get("T");

	TFile * f7 =  new TFile("~/LabData/Zhicai_Spring2018/data/1096.root");//71
	TTree * t7 = (TTree*)f7->Get("T");

	TFile * f8 =  new TFile("~/LabData/Zhicai_Spring2018/data/1098.root");//72
	TTree * t8 = (TTree*)f8->Get("T");



	float pulse1[1024];
	float time1[1024];

	float pulse2[1024];
	float time2[1024];
	
	float pulse3[1024];
	float time3[1024];
	
	float pulse4[1024];
	float time4[1024];

	float pulse5[1024];
	float time5[1024];
	
	float pulse6[1024];
	float time6[1024];
	
	float pulse7[1024];
	float time7[1024];
	
	float pulse8[1024];
	float time8[1024];
	
	t1->SetBranchAddress("c2",pulse1);
	t1->SetBranchAddress("t2",time1);

	t2->SetBranchAddress("c2",pulse2);
	t2->SetBranchAddress("t2",time2);

	t3->SetBranchAddress("c2",pulse3);
	t3->SetBranchAddress("t2",time3);

	t4->SetBranchAddress("c2",pulse4);
	t4->SetBranchAddress("t2",time4);

	t5->SetBranchAddress("c2",pulse5);
	t5->SetBranchAddress("t2",time5);

	t6->SetBranchAddress("c2",pulse6);
	t6->SetBranchAddress("t2",time6);
	
	t7->SetBranchAddress("c2",pulse7);
	t7->SetBranchAddress("t2",time7);
	
	t8->SetBranchAddress("c2",pulse8);
	t8->SetBranchAddress("t2",time8);

	t1->GetEntry(3);
	t2->GetEntry(3);
	t3->GetEntry(21);
	t4->GetEntry(63);
	t5->GetEntry(65);
	t6->GetEntry(85);
	t7->GetEntry(2);
	t8->GetEntry(46);
	
	float ex[1024] = {0.0};
	float ey[1024] = {0.0};
	
	TGraphErrors *gr1 = new TGraphErrors(1024, time1, pulse1, ex, ey);
	TGraphErrors *gr2 = new TGraphErrors(1024, time2, pulse2, ex, ey);
	TGraphErrors *gr3 = new TGraphErrors(1024, time3, pulse3, ex, ey);
	TGraphErrors *gr4 = new TGraphErrors(1024, time4, pulse4, ex, ey);
	TGraphErrors *gr5 = new TGraphErrors(1024, time5, pulse5, ex, ey);
	TGraphErrors *gr6 = new TGraphErrors(1024, time6, pulse6, ex, ey);
	TGraphErrors *gr7 = new TGraphErrors(1024, time7, pulse7, ex, ey);
	TGraphErrors *gr8 = new TGraphErrors(1024, time8, pulse8, ex, ey);
	
	gr1->SetMarkerStyle(20);
	gr1->SetMarkerColor(1);
	gr1->SetLineColor(1);

	gr2->SetMarkerStyle(20);
	gr2->SetMarkerColor(2);
	gr2->SetLineColor(2);

	gr3->SetMarkerStyle(20);
	gr3->SetMarkerColor(3);
	gr3->SetLineColor(3);

	gr4->SetMarkerStyle(20);
	gr4->SetMarkerColor(4);
	gr4->SetLineColor(4);

	gr5->SetMarkerStyle(20);
	gr5->SetMarkerColor(5);
	gr5->SetLineColor(5);

	gr6->SetMarkerStyle(20);
	gr6->SetMarkerColor(6);
	gr6->SetLineColor(6);

	gr7->SetMarkerStyle(20);
	gr7->SetMarkerColor(7);
	gr7->SetLineColor(7);
	
	gr8->SetMarkerStyle(20);
	gr8->SetMarkerColor(8);
	gr8->SetLineColor(8);


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
	mg->Add(gr4);
	mg->Add(gr5);
	mg->Add(gr6);
	mg->Add(gr7);
	mg->Add(gr8);
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

	TLegend * leg = new TLegend(0.70,0.15,0.92,0.7);
	leg->SetBorderSize(0);
	leg->SetTextSize(0.03);
	leg->SetLineColor(1);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetFillStyle(1001);
	
	leg->AddEntry(gr1, "bias = 65V", "lp");
	leg->AddEntry(gr2, "bias = 66V", "lp");
	leg->AddEntry(gr3, "bias = 67V", "lp");
	leg->AddEntry(gr4, "bias = 68V", "lp");
	leg->AddEntry(gr5, "bias = 69V", "lp");
	leg->AddEntry(gr6, "bias = 70V", "lp");
	leg->AddEntry(gr7, "bias = 71V", "lp");
	leg->AddEntry(gr8, "bias = 72V", "lp");
	leg->Draw();

	myC->SaveAs("~/LabData/Zhicai_Spring2018/plots/pulses_373nm_bias.pdf");
	myC->SaveAs("~/LabData/Zhicai_Spring2018/plots/pulses_373nm_bias.png");
	myC->SaveAs("~/LabData/Zhicai_Spring2018/plots/pulses_373nm_bias.C");

}
