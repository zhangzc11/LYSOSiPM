
void wavelength()
{

	TString x_s = "5";
	TFile *f = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/ntuple_x"+x_s+"_4mm_md_ps_withWL.root");
	TTree *tree = (TTree*)f->Get("tree");


	gStyle->SetOptStat(0);
	gStyle->SetOptFit(111);

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

	TH1F *h1_wavelength_cerenkov = new TH1F("h1_wavelength_cerenkov","h1_wavelength_cerenkov", 400, 300, 700);
	TH1F *h1_wavelength_NOcerenkov = new TH1F("h1_wavelength_NOcerenkov","h1_wavelength_cerenkov", 400, 300, 700);
	tree->Draw("allPhoWaveLength>>h1_wavelength_cerenkov","allPhoIsCerenkov==1");
	tree->Draw("allPhoWaveLength>>h1_wavelength_NOcerenkov","allPhoIsCerenkov==0");


	std::cout<<"Average total number of Cerenkov photons: "<<h1_wavelength_cerenkov->Integral()/(1.0*tree->GetEntries())<<std::endl;
    std::cout<<"Average total number of scintillation photons: "<<h1_wavelength_NOcerenkov->Integral()/(1.0*tree->GetEntries())<<std::endl;
    std::cout<<"Cerenkov/Scintillation ratio = "<<h1_wavelength_cerenkov->Integral()/(1.0*h1_wavelength_NOcerenkov->Integral())<<std::endl;

	h1_wavelength_cerenkov->Scale(1.0/h1_wavelength_cerenkov->Integral());
	h1_wavelength_NOcerenkov->Scale(1.0/h1_wavelength_NOcerenkov->Integral());

	float max_Y = std::max(h1_wavelength_cerenkov->GetBinContent(h1_wavelength_cerenkov->GetMaximumBin()), h1_wavelength_NOcerenkov->GetBinContent(h1_wavelength_NOcerenkov->GetMaximumBin()));

	h1_wavelength_cerenkov->SetTitle("");
	h1_wavelength_cerenkov->GetXaxis()->SetTitle("photon wavelength [nm]");
    h1_wavelength_cerenkov->GetYaxis()->SetTitle("Events");
	h1_wavelength_cerenkov->GetXaxis()->SetTitleSize(0.06);
    h1_wavelength_cerenkov->GetXaxis()->SetTitleOffset(0.9);
    h1_wavelength_cerenkov->GetYaxis()->SetTitleSize(0.05);
    h1_wavelength_cerenkov->GetYaxis()->SetTitleOffset(1.0);
    h1_wavelength_cerenkov->GetYaxis()->SetRangeUser(0.0, 1.2*max_Y);
	h1_wavelength_cerenkov->SetLineWidth(2);
	h1_wavelength_cerenkov->SetLineColor(kRed);
	h1_wavelength_NOcerenkov->SetLineWidth(2);
	h1_wavelength_NOcerenkov->SetLineColor(kBlue);

	h1_wavelength_cerenkov->Draw();
	h1_wavelength_NOcerenkov->Draw("same");
	
	TLegend * leg = new TLegend(0.7,0.7,0.9,0.9);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.03);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(1);
    leg->SetFillColor(0);
    leg->SetFillStyle(1001);

	leg->AddEntry(h1_wavelength_NOcerenkov,"scintillation light","l");
	leg->AddEntry(h1_wavelength_cerenkov,"Cherenkov light","l");
	leg->Draw();

	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_photonWaveLength_x"+x_s+".pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_photonWaveLength_x"+x_s+".png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_photonWaveLength_x"+x_s+".C");

}

