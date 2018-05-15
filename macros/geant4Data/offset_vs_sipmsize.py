import ROOT
import array
import itertools
import os
import numpy as np

ROOT.gROOT.SetBatch(True)

ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(111)
#################plot settings###########################
axisTitleSizeX = 0.06
axisTitleSizeY = 0.05
axisTitleOffsetX = 0.9
axisTitleOffsetY = 1.1

axisTitleSizeRatioX   = 0.18
axisLabelSizeRatioX   = 0.12
axisTitleOffsetRatioX = 0.94
axisTitleSizeRatioY   = 0.15
axisLabelSizeRatioY   = 0.108
axisTitleOffsetRatioY = 0.32

leftMargin   = 0.12
rightMargin  = 0.05
topMargin    = 0.07
bottomMargin = 0.12
########################################################

#################input parameters#######################
outputDir = "/afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/geant4/"

os.system("mkdir -p "+outputDir)


########################################################

sipmsize = [3.0, 4.0, 6.0, 10.0]
esipmsize = [0.0,0.0,0.0,0.0,0.0]

LYSO3mm_upstream = [285.0, 190.0, 120.0, 15.0]
eLYSO3mm_upstream = [0.0,0.0,0.0,0.0]

LYSO3mm_downstream = [200.0, 119.0, 44.0, 4.0]
eLYSO3mm_downstream = [0.0,0.0,0.0,0.0]

LYSO4mm_upstream = [280.0, 189.9, 95.0, 19.0]
eLYSO4mm_upstream = [0.0,0.0,0.0,0.0]

LYSO4mm_downstream = [200.0, 129.0, 54.0, 9.0]
eLYSO4mm_downstream = [0.0,0.0,0.0,0.0]


plot_name = "timeoffset"
plot_title = "time offset [ns]"


myC = ROOT.TCanvas( "myC", "myC", 200, 10, 800, 600 )
myC.SetHighLightColor(2)
myC.SetFillColor(0)
myC.SetBorderMode(0)
myC.SetBorderSize(2)
myC.SetLeftMargin( leftMargin )
myC.SetRightMargin( rightMargin )
myC.SetTopMargin( topMargin )
myC.SetBottomMargin( bottomMargin )
myC.SetFrameBorderMode(0)
myC.SetFrameBorderMode(0)

gr_LYSO4mm_upstream_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(LYSO4mm_upstream), np.array(esipmsize), np.array(eLYSO4mm_upstream))
gr_LYSO4mm_downstream_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(LYSO4mm_downstream), np.array(esipmsize), np.array(eLYSO4mm_downstream))

gr_LYSO3mm_upstream_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(LYSO3mm_upstream), np.array(esipmsize), np.array(eLYSO3mm_upstream))
gr_LYSO3mm_downstream_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(LYSO3mm_downstream), np.array(esipmsize), np.array(eLYSO3mm_downstream))



gr_LYSO4mm_upstream_vs_sipmsize.SetMarkerStyle( 20 )
gr_LYSO4mm_upstream_vs_sipmsize.SetMarkerColor( ROOT.kRed )
gr_LYSO4mm_upstream_vs_sipmsize.SetLineWidth( 2 )
gr_LYSO4mm_upstream_vs_sipmsize.SetLineColor( ROOT.kRed ) 

gr_LYSO4mm_downstream_vs_sipmsize.SetMarkerStyle( 20 )
gr_LYSO4mm_downstream_vs_sipmsize.SetMarkerColor( ROOT.kBlue )
gr_LYSO4mm_downstream_vs_sipmsize.SetLineWidth( 2 )
gr_LYSO4mm_downstream_vs_sipmsize.SetLineColor( ROOT.kBlue ) 

gr_LYSO3mm_upstream_vs_sipmsize.SetMarkerStyle( 21 )
gr_LYSO3mm_upstream_vs_sipmsize.SetMarkerColor( ROOT.kRed )
gr_LYSO3mm_upstream_vs_sipmsize.SetLineWidth( 2 )
gr_LYSO3mm_upstream_vs_sipmsize.SetLineColor( ROOT.kRed ) 

gr_LYSO3mm_downstream_vs_sipmsize.SetMarkerStyle( 21 )
gr_LYSO3mm_downstream_vs_sipmsize.SetMarkerColor( ROOT.kBlue )
gr_LYSO3mm_downstream_vs_sipmsize.SetLineWidth( 2 )
gr_LYSO3mm_downstream_vs_sipmsize.SetLineColor( ROOT.kBlue ) 

mg_vs_sipmsize = ROOT.TMultiGraph()
mg_LYSO3mmvs_sipmsize = ROOT.TMultiGraph()
mg_LYSO4mmvs_sipmsize = ROOT.TMultiGraph()

mg_LYSO3mmvs_sipmsize.Add(gr_LYSO3mm_upstream_vs_sipmsize)
mg_LYSO3mmvs_sipmsize.Add(gr_LYSO3mm_downstream_vs_sipmsize)

mg_LYSO4mmvs_sipmsize.Add(gr_LYSO4mm_upstream_vs_sipmsize)
mg_LYSO4mmvs_sipmsize.Add(gr_LYSO4mm_downstream_vs_sipmsize)


mg_vs_sipmsize.Add(gr_LYSO4mm_upstream_vs_sipmsize)
mg_vs_sipmsize.Add(gr_LYSO3mm_upstream_vs_sipmsize)
mg_vs_sipmsize.Add(gr_LYSO4mm_downstream_vs_sipmsize)
mg_vs_sipmsize.Add(gr_LYSO3mm_downstream_vs_sipmsize)

mg_vs_sipmsize.Draw("AP")


mg_vs_sipmsize.GetHistogram().GetXaxis().SetTitle("SiPM size [mm]")
mg_vs_sipmsize.GetHistogram().GetYaxis().SetTitle(plot_title)
mg_vs_sipmsize.GetHistogram().SetTitle("")
mg_vs_sipmsize.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_vs_sipmsize.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_vs_sipmsize.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_vs_sipmsize.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
#mg_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(55.0,61.0)
mg_vs_sipmsize.GetHistogram().GetYaxis().SetRangeUser(-200.0,300.0)

ROOT.gPad.Modified()
ROOT.gPad.Update()

leg_vs_sipmsize = ROOT.TLegend(0.15,0.15,0.9,0.4)
leg_vs_sipmsize.SetBorderSize(0)
leg_vs_sipmsize.SetNColumns(2)
leg_vs_sipmsize.SetTextSize(0.03)
leg_vs_sipmsize.SetLineColor(1)
leg_vs_sipmsize.SetLineStyle(1)
leg_vs_sipmsize.SetLineWidth(1)
leg_vs_sipmsize.SetFillColor(0)
leg_vs_sipmsize.SetFillStyle(1001)

leg_vs_sipmsize.AddEntry(gr_LYSO3mm_upstream_vs_sipmsize, "LYSO (3mm) upstream", "p");
leg_vs_sipmsize.AddEntry(gr_LYSO3mm_downstream_vs_sipmsize, "LYSO (3mm) downstream", "p");
leg_vs_sipmsize.AddEntry(gr_LYSO4mm_upstream_vs_sipmsize, "LYSO (4mm) upstream", "p");
leg_vs_sipmsize.AddEntry(gr_LYSO4mm_downstream_vs_sipmsize, "LYSO (4mm) downstream", "p");
leg_vs_sipmsize.Draw()


myC.SaveAs(outputDir+plot_name+"_vs_sipmsize.pdf")
myC.SaveAs(outputDir+plot_name+"_vs_sipmsize.png")
myC.SaveAs(outputDir+plot_name+"_vs_sipmsize.C")



mg_LYSO3mmvs_sipmsize.Draw("AP")

mg_LYSO3mmvs_sipmsize.GetHistogram().GetXaxis().SetTitle("SiPM size [mm]")
mg_LYSO3mmvs_sipmsize.GetHistogram().GetYaxis().SetTitle(plot_title)
mg_LYSO3mmvs_sipmsize.GetHistogram().SetTitle("")
mg_LYSO3mmvs_sipmsize.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_LYSO3mmvs_sipmsize.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_LYSO3mmvs_sipmsize.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_LYSO3mmvs_sipmsize.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
#mg_LYSO3mmvs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(55.0,61.0)
mg_LYSO3mmvs_sipmsize.GetHistogram().GetYaxis().SetRangeUser(0.0,300.0)

ROOT.gPad.Modified()
ROOT.gPad.Update()

leg_LYSO3mm_vs_sipmsize = ROOT.TLegend(0.5,0.65,0.9,0.85)
leg_LYSO3mm_vs_sipmsize.SetBorderSize(0)
leg_LYSO3mm_vs_sipmsize.SetTextSize(0.04)
leg_LYSO3mm_vs_sipmsize.SetLineColor(1)
leg_LYSO3mm_vs_sipmsize.SetLineStyle(1)
leg_LYSO3mm_vs_sipmsize.SetLineWidth(1)
leg_LYSO3mm_vs_sipmsize.SetFillColor(0)
leg_LYSO3mm_vs_sipmsize.SetFillStyle(1001)

leg_LYSO3mm_vs_sipmsize.AddEntry(gr_LYSO3mm_upstream_vs_sipmsize, "LYSO (3mm) upstream", "p");
leg_LYSO3mm_vs_sipmsize.AddEntry(gr_LYSO3mm_downstream_vs_sipmsize, "LYSO (3mm) downstream", "p");
leg_LYSO3mm_vs_sipmsize.Draw()

myC.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO3mm.pdf")
myC.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO3mm.png")
myC.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO3mm.C")



mg_LYSO4mmvs_sipmsize.Draw("AP")

mg_LYSO4mmvs_sipmsize.GetHistogram().GetXaxis().SetTitle("SiPM size [mm]")
mg_LYSO4mmvs_sipmsize.GetHistogram().GetYaxis().SetTitle(plot_title)
mg_LYSO4mmvs_sipmsize.GetHistogram().SetTitle("")
mg_LYSO4mmvs_sipmsize.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_LYSO4mmvs_sipmsize.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_LYSO4mmvs_sipmsize.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_LYSO4mmvs_sipmsize.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
#mg_LYSO4mmvs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(55.0,61.0)
mg_LYSO4mmvs_sipmsize.GetHistogram().GetYaxis().SetRangeUser(0.0,300.0)

ROOT.gPad.Modified()
ROOT.gPad.Update()

leg_LYSO4mm_vs_sipmsize = ROOT.TLegend(0.5,0.65,0.9,0.85)
leg_LYSO4mm_vs_sipmsize.SetBorderSize(0)
leg_LYSO4mm_vs_sipmsize.SetTextSize(0.04)
leg_LYSO4mm_vs_sipmsize.SetLineColor(1)
leg_LYSO4mm_vs_sipmsize.SetLineStyle(1)
leg_LYSO4mm_vs_sipmsize.SetLineWidth(1)
leg_LYSO4mm_vs_sipmsize.SetFillColor(0)
leg_LYSO4mm_vs_sipmsize.SetFillStyle(1001)

leg_LYSO4mm_vs_sipmsize.AddEntry(gr_LYSO4mm_upstream_vs_sipmsize, "LYSO (4mm) upstream", "p");
leg_LYSO4mm_vs_sipmsize.AddEntry(gr_LYSO4mm_downstream_vs_sipmsize, "LYSO (4mm) downstream", "p");
leg_LYSO4mm_vs_sipmsize.Draw()

myC.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO4mm.pdf")
myC.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO4mm.png")
myC.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO4mm.C")

