void test()
{
//=========Macro generated from canvas: myC2/myC2
//=========  (Tue May 15 11:43:46 2018) by ROOT version6.08/05
   TCanvas *myC2 = new TCanvas("myC2", "myC2",0,22,800,800);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   myC2->SetHighLightColor(2);
   myC2->Range(0,0,1,1);
   myC2->SetFillColor(0);
   myC2->SetBorderMode(0);
   myC2->SetBorderSize(2);
   myC2->SetLeftMargin(0.12);
   myC2->SetRightMargin(0.05);
   myC2->SetTopMargin(0.07);
   myC2->SetBottomMargin(0.12);
   myC2->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: pad1
   TPad *pad1 = new TPad("pad1", "pad1",0.05,0.3,0.95,0.97);
   pad1->Draw();
   pad1->cd();
   pad1->Range(1.536747,28.635,10.81386,392.0017);
   pad1->SetFillColor(0);
   pad1->SetBorderMode(0);
   pad1->SetBorderSize(2);
   pad1->SetLeftMargin(0.12);
   pad1->SetRightMargin(0.05);
   pad1->SetBottomMargin(0);
   pad1->SetFrameBorderMode(0);
   pad1->SetFrameBorderMode(0);
   
   TMultiGraph *multigraph = new TMultiGraph();
   multigraph->SetName("");
   multigraph->SetTitle("");
   
   Double_t Graph_fx1001[4] = {
   3,
   4,
   6,
   10};
   Double_t Graph_fy1001[4] = {
   56.3,
   79.4,
   143,
   340.8};
   Double_t Graph_fex1001[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph_fey1001[4] = {
   0,
   0,
   0,
   0};
   TGraphErrors *gre = new TGraphErrors(4,Graph_fx1001,Graph_fy1001,Graph_fex1001,Graph_fey1001);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(2);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph_Graph_Graph100210051001 = new TH1F("Graph_Graph_Graph_Graph100210051001","Graph",100,2.3,10.7);
   Graph_Graph_Graph_Graph100210051001->SetMinimum(27.85);
   Graph_Graph_Graph_Graph100210051001->SetMaximum(369.25);
   Graph_Graph_Graph_Graph100210051001->SetDirectory(0);
   Graph_Graph_Graph_Graph100210051001->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_Graph100210051001->SetLineColor(ci);
   Graph_Graph_Graph_Graph100210051001->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph100210051001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_Graph100210051001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_Graph100210051001->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph100210051001->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph100210051001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_Graph100210051001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_Graph100210051001->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph100210051001->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph100210051001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_Graph100210051001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_Graph100210051001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph_Graph100210051001);
   
   multigraph->Add(gre,"");
   
   Double_t Graph_fx1002[4] = {
   3,
   4,
   6,
   10};
   Double_t Graph_fy1002[4] = {
   43.5,
   66.6,
   130.2,
   329.4};
   Double_t Graph_fex1002[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph_fey1002[4] = {
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(4,Graph_fx1002,Graph_fy1002,Graph_fex1002,Graph_fey1002);
   gre->SetName("Graph");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(4);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(21);
   
   TH1F *Graph_Graph_Graph_Graph100410061002 = new TH1F("Graph_Graph_Graph_Graph100410061002","Graph",100,2.3,10.7);
   Graph_Graph_Graph_Graph100410061002->SetMinimum(14.91);
   Graph_Graph_Graph_Graph100410061002->SetMaximum(357.99);
   Graph_Graph_Graph_Graph100410061002->SetDirectory(0);
   Graph_Graph_Graph_Graph100410061002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_Graph100410061002->SetLineColor(ci);
   Graph_Graph_Graph_Graph100410061002->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph100410061002->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_Graph100410061002->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_Graph100410061002->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph100410061002->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph100410061002->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_Graph100410061002->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_Graph100410061002->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph100410061002->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph100410061002->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph_Graph100410061002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph_Graph100410061002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph_Graph100410061002);
   
   multigraph->Add(gre,"");
   multigraph->Draw("AP");
   multigraph->GetXaxis()->SetTitle("SiPM size [mm]");
   multigraph->GetXaxis()->SetLabelFont(42);
   multigraph->GetXaxis()->SetLabelSize(0.035);
   multigraph->GetXaxis()->SetTitleSize(0.06);
   multigraph->GetXaxis()->SetTitleOffset(0.9);
   multigraph->GetXaxis()->SetTitleFont(42);
   multigraph->GetYaxis()->SetTitle("charge [a.u.]");
   multigraph->GetYaxis()->SetLabelFont(42);
   multigraph->GetYaxis()->SetLabelSize(0.035);
   multigraph->GetYaxis()->SetTitleSize(0.05);
   multigraph->GetYaxis()->SetTitleOffset(1.1);
   multigraph->GetYaxis()->SetTitleFont(42);
   
   TLegend *leg = new TLegend(0.2,0.65,0.6,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph","LYSO (3mm) center (0mm)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","LYSO (3mm) edge (5mm)","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   pad1->Modified();
   myC2->cd();
  
// ------------>Primitives in pad: pad2
   TPad *pad2 = new TPad("pad2", "pad2",0.05,0.02,0.95,0.29);
   pad2->Draw();
   pad2->cd();
   pad2->Range(1.085542,0.1621622,11.20602,1.006757);
   pad2->SetFillColor(0);
   pad2->SetBorderMode(0);
   pad2->SetBorderSize(2);
   pad2->SetLeftMargin(0.12);
   pad2->SetRightMargin(0.05);
   pad2->SetTopMargin(0.008);
   pad2->SetBottomMargin(0.4);
   pad2->SetFrameBorderMode(0);
   pad2->SetFrameBorderMode(0);
   
   Double_t Graph0_fx1003[4] = {
   3,
   4,
   6,
   10};
   Double_t Graph0_fy1003[4] = {
   0.7726465,
   0.8387909,
   0.9104895,
   0.9665493};
   Double_t Graph0_fex1003[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph0_fey1003[4] = {
   0,
   0,
   0,
   0};
   gre = new TGraphErrors(4,Graph0_fx1003,Graph0_fy1003,Graph0_fex1003,Graph0_fey1003);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");
   gre->SetFillColor(1);
   gre->SetLineColor(4);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(20);
   
   TH1F *Graph_Graph_Graph10071003 = new TH1F("Graph_Graph_Graph10071003","",100,2.3,10.7);
   Graph_Graph_Graph10071003->SetMinimum(0.5);
   Graph_Graph_Graph10071003->SetMaximum(1);
   Graph_Graph_Graph10071003->SetDirectory(0);
   Graph_Graph_Graph10071003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph10071003->SetLineColor(ci);
   Graph_Graph_Graph10071003->GetXaxis()->SetTitle("SiPM size [mm]");
   Graph_Graph_Graph10071003->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph10071003->GetXaxis()->SetLabelSize(0.12);
   Graph_Graph_Graph10071003->GetXaxis()->SetTitleSize(0.14);
   Graph_Graph_Graph10071003->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph_Graph10071003->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph10071003->GetYaxis()->SetTitle("edge / center");
   Graph_Graph_Graph10071003->GetYaxis()->CenterTitle(true);
   Graph_Graph_Graph10071003->GetYaxis()->SetNdivisions(-5);
   Graph_Graph_Graph10071003->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph10071003->GetYaxis()->SetLabelSize(0.1);
   Graph_Graph_Graph10071003->GetYaxis()->SetTitleSize(0.1);
   Graph_Graph_Graph10071003->GetYaxis()->SetTitleOffset(0.5);
   Graph_Graph_Graph10071003->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph10071003->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph10071003->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_Graph10071003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_Graph10071003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph10071003);
   
   gre->Draw("ap");
   pad2->Modified();
   myC2->cd();
   myC2->Modified();
   myC2->cd();
   myC2->SetSelected(myC2);
}
