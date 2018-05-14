
void t100()
{

	TString x_s = "0";
	TString p_d = "_md";
	TFile *f = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/ntuple_x"+x_s+"_4mm"+p_d+"_ps_withWL_newAbs_sptr.root");
	TTree *tree = (TTree*)f->Get("tree");


	gStyle->SetOptStat(0);
	//gStyle->SetOptFit(111);

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


	TH1F * h100 = new TH1F("h100","h100",100,0,0.4);
	tree->Draw("allPhoTime_sptr>>h100","allPhoIndex==100");

	h100->SetTitle("");
	h100->GetXaxis()->SetTitle("t_{100} [ns]");
    h100->GetYaxis()->SetTitle("Events");
	h100->GetXaxis()->SetTitleSize(0.06);
    h100->GetXaxis()->SetTitleOffset(0.9);
    h100->GetYaxis()->SetTitleSize(0.05);
    h100->GetYaxis()->SetTitleOffset(1.0);
	h100->SetLineWidth(2);
	h100->SetLineColor(kRed);
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/time_photon100_x"+x_s+p_d+"_newAbs_sptr.pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/time_photon100_x"+x_s+p_d+"_newAbs_sptr.png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/time_photon100_x"+x_s+p_d+"_newAbs_sptr.C");
	

}
