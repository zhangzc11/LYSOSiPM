
void tracks_x5()
{

	TString x_s = "5";
	TFile *f = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/ntuple_x5_4mm_md_ps_withWL.root");
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

	TH2F * h2_allPhoTrackVertexR_vs_phoIndex = new TH2F("h2_allPhoTrackVertexR_vs_phoIndex","h2_allPhoTrackVertexR_vs_phoIndex", 200, 0, 200, 100, 4.0, 10.0);
	tree->Draw("allPhoTrackVertexR:allPhoIndex>>h2_allPhoTrackVertexR_vs_phoIndex");
	h2_allPhoTrackVertexR_vs_phoIndex->SetTitle("");
	h2_allPhoTrackVertexR_vs_phoIndex->GetXaxis()->SetTitle("photon index");
    h2_allPhoTrackVertexR_vs_phoIndex->GetYaxis()->SetTitle("vertex distance to SiPM [mm]");
	h2_allPhoTrackVertexR_vs_phoIndex->GetXaxis()->SetTitleSize(0.06);
    h2_allPhoTrackVertexR_vs_phoIndex->GetXaxis()->SetTitleOffset(0.9);
    h2_allPhoTrackVertexR_vs_phoIndex->GetYaxis()->SetTitleSize(0.05);
    h2_allPhoTrackVertexR_vs_phoIndex->GetYaxis()->SetTitleOffset(1.0);
	h2_allPhoTrackVertexR_vs_phoIndex->SetMarkerStyle(6);
	h2_allPhoTrackVertexR_vs_phoIndex->SetMarkerColor(kRed);
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackVertexR_vs_phoIndex_x"+x_s+".pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackVertexR_vs_phoIndex_x"+x_s+".png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackVertexR_vs_phoIndex_x"+x_s+".C");


	TH2F * h2_allPhoTrackLength_vs_phoIndex = new TH2F("h2_allPhoTrackLength_vs_phoIndex","h2_allPhoTrackLength_vs_phoIndex", 200, 0, 200, 100, 0, 100.0);
	tree->Draw("allPhoTrackLength:allPhoIndex>>h2_allPhoTrackLength_vs_phoIndex");
	h2_allPhoTrackLength_vs_phoIndex->SetTitle("");
	h2_allPhoTrackLength_vs_phoIndex->GetXaxis()->SetTitle("photon index");
    h2_allPhoTrackLength_vs_phoIndex->GetYaxis()->SetTitle("photon track length [mm]");
	h2_allPhoTrackLength_vs_phoIndex->GetXaxis()->SetTitleSize(0.06);
    h2_allPhoTrackLength_vs_phoIndex->GetXaxis()->SetTitleOffset(0.9);
    h2_allPhoTrackLength_vs_phoIndex->GetYaxis()->SetTitleSize(0.05);
    h2_allPhoTrackLength_vs_phoIndex->GetYaxis()->SetTitleOffset(1.0);
	h2_allPhoTrackLength_vs_phoIndex->SetMarkerStyle(6);
	h2_allPhoTrackLength_vs_phoIndex->SetMarkerColor(kRed);
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackLength_vs_phoIndex_x"+x_s+".pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackLength_vs_phoIndex_x"+x_s+".png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackLength_vs_phoIndex_x"+x_s+".C");

	TH2F * h2_allPhoTime_vs_phoIndex = new TH2F("h2_allPhoTime_vs_phoIndex","h2_allPhoTime_vs_phoIndex", 200, 0, 200, 100, 0, 0.4);
	tree->Draw("allPhoTime:allPhoIndex>>h2_allPhoTime_vs_phoIndex");
	h2_allPhoTime_vs_phoIndex->SetTitle("");
	h2_allPhoTime_vs_phoIndex->GetXaxis()->SetTitle("photon index");
    h2_allPhoTime_vs_phoIndex->GetYaxis()->SetTitle("photon time [ns]");
	h2_allPhoTime_vs_phoIndex->GetXaxis()->SetTitleSize(0.06);
    h2_allPhoTime_vs_phoIndex->GetXaxis()->SetTitleOffset(0.9);
    h2_allPhoTime_vs_phoIndex->GetYaxis()->SetTitleSize(0.05);
    h2_allPhoTime_vs_phoIndex->GetYaxis()->SetTitleOffset(1.0);
	h2_allPhoTime_vs_phoIndex->SetMarkerStyle(6);
	h2_allPhoTime_vs_phoIndex->SetMarkerColor(kRed);
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTime_vs_phoIndex_x"+x_s+".pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTime_vs_phoIndex_x"+x_s+".png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTime_vs_phoIndex_x"+x_s+".C");

	}
