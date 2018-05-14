
void tracks_x0()
{

	TString x_s = "0";
	TFile *f = new TFile("/Users/zhicai/cernbox/TestBeam/geant4/ntuples/ntuple_x0_4mm_md_ps_withWL_newAbs_sptr.root");
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

	TH2F * h2_allPhoTrackVertexR_sptr_vs_phoIndex = new TH2F("h2_allPhoTrackVertexR_sptr_vs_phoIndex","h2_allPhoTrackVertexR_sptr_vs_phoIndex", 200, 0, 200, 100, 0.0, 6.0);
	tree->Draw("allPhoTrackVertexR_sptr:allPhoIndex_sptr>>h2_allPhoTrackVertexR_sptr_vs_phoIndex");
	h2_allPhoTrackVertexR_sptr_vs_phoIndex->SetTitle("");
	h2_allPhoTrackVertexR_sptr_vs_phoIndex->GetXaxis()->SetTitle("photon index");
    h2_allPhoTrackVertexR_sptr_vs_phoIndex->GetYaxis()->SetTitle("vertex distance to SiPM [mm]");
	h2_allPhoTrackVertexR_sptr_vs_phoIndex->GetXaxis()->SetTitleSize(0.06);
    h2_allPhoTrackVertexR_sptr_vs_phoIndex->GetXaxis()->SetTitleOffset(0.9);
    h2_allPhoTrackVertexR_sptr_vs_phoIndex->GetYaxis()->SetTitleSize(0.05);
    h2_allPhoTrackVertexR_sptr_vs_phoIndex->GetYaxis()->SetTitleOffset(1.0);
	h2_allPhoTrackVertexR_sptr_vs_phoIndex->SetMarkerStyle(6);
	h2_allPhoTrackVertexR_sptr_vs_phoIndex->SetMarkerColor(kRed);
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackVertexR_sptr_vs_phoIndex_x"+x_s+"_newAbs_sptr.pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackVertexR_sptr_vs_phoIndex_x"+x_s+"_newAbs_sptr.png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackVertexR_sptr_vs_phoIndex_x"+x_s+"_newAbs_sptr.C");


	TH2F * h2_allPhoTrackLength_sptr_vs_phoIndex = new TH2F("h2_allPhoTrackLength_sptr_vs_phoIndex","h2_allPhoTrackLength_sptr_vs_phoIndex", 200, 0, 200, 100, 0, 50.0);
	tree->Draw("allPhoTrackLength_sptr:allPhoIndex_sptr>>h2_allPhoTrackLength_sptr_vs_phoIndex");
	h2_allPhoTrackLength_sptr_vs_phoIndex->SetTitle("");
	h2_allPhoTrackLength_sptr_vs_phoIndex->GetXaxis()->SetTitle("photon index");
    h2_allPhoTrackLength_sptr_vs_phoIndex->GetYaxis()->SetTitle("photon track length [mm]");
	h2_allPhoTrackLength_sptr_vs_phoIndex->GetXaxis()->SetTitleSize(0.06);
    h2_allPhoTrackLength_sptr_vs_phoIndex->GetXaxis()->SetTitleOffset(0.9);
    h2_allPhoTrackLength_sptr_vs_phoIndex->GetYaxis()->SetTitleSize(0.05);
    h2_allPhoTrackLength_sptr_vs_phoIndex->GetYaxis()->SetTitleOffset(1.0);
	h2_allPhoTrackLength_sptr_vs_phoIndex->SetMarkerStyle(6);
	h2_allPhoTrackLength_sptr_vs_phoIndex->SetMarkerColor(kRed);
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackLength_sptr_vs_phoIndex_x"+x_s+"_newAbs_sptr.pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackLength_sptr_vs_phoIndex_x"+x_s+"_newAbs_sptr.png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTrackLength_sptr_vs_phoIndex_x"+x_s+"_newAbs_sptr.C");

	TH2F * h2_allPhoTime_sptr_vs_phoIndex = new TH2F("h2_allPhoTime_sptr_vs_phoIndex","h2_allPhoTime_sptr_vs_phoIndex", 200, 0, 200, 100, 0, 0.4);
	tree->Draw("allPhoTime_sptr:allPhoIndex_sptr>>h2_allPhoTime_sptr_vs_phoIndex");
	h2_allPhoTime_sptr_vs_phoIndex->SetTitle("");
	h2_allPhoTime_sptr_vs_phoIndex->GetXaxis()->SetTitle("photon index");
    h2_allPhoTime_sptr_vs_phoIndex->GetYaxis()->SetTitle("photon time [ns]");
	h2_allPhoTime_sptr_vs_phoIndex->GetXaxis()->SetTitleSize(0.06);
    h2_allPhoTime_sptr_vs_phoIndex->GetXaxis()->SetTitleOffset(0.9);
    h2_allPhoTime_sptr_vs_phoIndex->GetYaxis()->SetTitleSize(0.05);
    h2_allPhoTime_sptr_vs_phoIndex->GetYaxis()->SetTitleOffset(1.0);
	h2_allPhoTime_sptr_vs_phoIndex->SetMarkerStyle(6);
	h2_allPhoTime_sptr_vs_phoIndex->SetMarkerColor(kRed);
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTime_sptr_vs_phoIndex_x"+x_s+"_newAbs_sptr.pdf");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTime_sptr_vs_phoIndex_x"+x_s+"_newAbs_sptr.png");
	myC->SaveAs("/Users/zhicai/cernbox/TestBeam/geant4/plots/md_tracks_allPhoTime_sptr_vs_phoIndex_x"+x_s+"_newAbs_sptr.C");

	}
