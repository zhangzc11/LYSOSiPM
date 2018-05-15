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

LYSO3mm_x0 = [56.3, 79.4, 143.0, 340.8]
eLYSO3mm_x0 = [0.0,0.0,0.0,0.0]

LYSO3mm_x5 = [43.5, 66.6, 130.2, 329.4]
eLYSO3mm_x5 = [0.0,0.0,0.0,0.0]

ratio_3mm = [a/b for a, b in zip(LYSO3mm_x5,LYSO3mm_x0)]
eratio_3mm = [0.0,0.0,0.0,0.0]


LYSO4mm_x0 = [62.9, 88.7, 154.8, 351.6]
eLYSO4mm_x0 = [0.0,0.0,0.0,0.0]

LYSO4mm_x5 = [48.1, 73.9, 138.8, 349.8]
eLYSO4mm_x5 = [0.0,0.0,0.0,0.0]

ratio_4mm = [a/b for a, b in zip(LYSO4mm_x5,LYSO4mm_x0)]
eratio_4mm = [0.0,0.0,0.0,0.0]


plot_name = "charge_upstream"
plot_title = "charge [a.u.]"


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

gr_LYSO4mm_x0_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(LYSO4mm_x0), np.array(esipmsize), np.array(eLYSO4mm_x0))
gr_LYSO4mm_x5_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(LYSO4mm_x5), np.array(esipmsize), np.array(eLYSO4mm_x5))

gr_LYSO3mm_x0_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(LYSO3mm_x0), np.array(esipmsize), np.array(eLYSO3mm_x0))
gr_LYSO3mm_x5_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(LYSO3mm_x5), np.array(esipmsize), np.array(eLYSO3mm_x5))


gr_ratio_3mm_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(ratio_3mm), np.array(esipmsize), np.array(eratio_3mm))
gr_ratio_4mm_vs_sipmsize = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(ratio_4mm), np.array(esipmsize), np.array(eratio_4mm))

gr_ratio_3mm_vs_sipmsize.SetMarkerStyle( 20 )
gr_ratio_3mm_vs_sipmsize.SetMarkerColor( ROOT.kBlue )
gr_ratio_3mm_vs_sipmsize.SetLineWidth( 2 )
gr_ratio_3mm_vs_sipmsize.SetLineColor( ROOT.kBlue ) 

gr_ratio_4mm_vs_sipmsize.SetMarkerStyle( 20 )
gr_ratio_4mm_vs_sipmsize.SetMarkerColor( ROOT.kBlue )
gr_ratio_4mm_vs_sipmsize.SetLineWidth( 2 )
gr_ratio_4mm_vs_sipmsize.SetLineColor( ROOT.kBlue ) 


gr_LYSO4mm_x0_vs_sipmsize.SetMarkerStyle( 20 )
gr_LYSO4mm_x0_vs_sipmsize.SetMarkerColor( ROOT.kRed )
gr_LYSO4mm_x0_vs_sipmsize.SetLineWidth( 2 )
gr_LYSO4mm_x0_vs_sipmsize.SetLineColor( ROOT.kRed ) 

gr_LYSO4mm_x5_vs_sipmsize.SetMarkerStyle( 20 )
gr_LYSO4mm_x5_vs_sipmsize.SetMarkerColor( ROOT.kBlue )
gr_LYSO4mm_x5_vs_sipmsize.SetLineWidth( 2 )
gr_LYSO4mm_x5_vs_sipmsize.SetLineColor( ROOT.kBlue ) 

gr_LYSO3mm_x0_vs_sipmsize.SetMarkerStyle( 21 )
gr_LYSO3mm_x0_vs_sipmsize.SetMarkerColor( ROOT.kRed )
gr_LYSO3mm_x0_vs_sipmsize.SetLineWidth( 2 )
gr_LYSO3mm_x0_vs_sipmsize.SetLineColor( ROOT.kRed ) 

gr_LYSO3mm_x5_vs_sipmsize.SetMarkerStyle( 21 )
gr_LYSO3mm_x5_vs_sipmsize.SetMarkerColor( ROOT.kBlue )
gr_LYSO3mm_x5_vs_sipmsize.SetLineWidth( 2 )
gr_LYSO3mm_x5_vs_sipmsize.SetLineColor( ROOT.kBlue ) 


gr_LYSO3mm_x0_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
gr_LYSO3mm_x5_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
gr_LYSO4mm_x0_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
gr_LYSO4mm_x5_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)

mg_vs_sipmsize = ROOT.TMultiGraph()
mg_LYSO3mmvs_sipmsize = ROOT.TMultiGraph()
mg_LYSO4mmvs_sipmsize = ROOT.TMultiGraph()

mg_LYSO3mmvs_sipmsize.Add(gr_LYSO3mm_x0_vs_sipmsize)
mg_LYSO3mmvs_sipmsize.Add(gr_LYSO3mm_x5_vs_sipmsize)

mg_LYSO4mmvs_sipmsize.Add(gr_LYSO4mm_x0_vs_sipmsize)
mg_LYSO4mmvs_sipmsize.Add(gr_LYSO4mm_x5_vs_sipmsize)


mg_vs_sipmsize.Add(gr_LYSO4mm_x0_vs_sipmsize)
mg_vs_sipmsize.Add(gr_LYSO3mm_x0_vs_sipmsize)
mg_vs_sipmsize.Add(gr_LYSO4mm_x5_vs_sipmsize)
mg_vs_sipmsize.Add(gr_LYSO3mm_x5_vs_sipmsize)

mg_vs_sipmsize.Draw("AP")


mg_vs_sipmsize.GetHistogram().GetXaxis().SetTitle("SiPM size [mm]")
mg_vs_sipmsize.GetHistogram().GetYaxis().SetTitle(plot_title)
mg_vs_sipmsize.GetHistogram().SetTitle("")
mg_vs_sipmsize.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_vs_sipmsize.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_vs_sipmsize.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_vs_sipmsize.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
mg_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
mg_vs_sipmsize.GetHistogram().GetYaxis().SetRangeUser(-200.0,400.0)

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

leg_vs_sipmsize.AddEntry(gr_LYSO3mm_x0_vs_sipmsize, "LYSO (3mm) center (0mm)", "p");
leg_vs_sipmsize.AddEntry(gr_LYSO3mm_x5_vs_sipmsize, "LYSO (3mm) edge (5mm)", "p");
leg_vs_sipmsize.AddEntry(gr_LYSO4mm_x0_vs_sipmsize, "LYSO (4mm) center (0mm)", "p");
leg_vs_sipmsize.AddEntry(gr_LYSO4mm_x5_vs_sipmsize, "LYSO (4mm) edge (5mm)", "p");
leg_vs_sipmsize.Draw()


myC.SaveAs(outputDir+plot_name+"_vs_sipmsize.pdf")
myC.SaveAs(outputDir+plot_name+"_vs_sipmsize.png")
myC.SaveAs(outputDir+plot_name+"_vs_sipmsize.C")

myC2 = ROOT.TCanvas( "myC2", "myC2", 200, 10, 800, 800 )
myC2.SetHighLightColor(2)
myC2.SetFillColor(0)
myC2.SetBorderMode(0)
myC2.SetBorderSize(2)
myC2.SetLeftMargin( leftMargin )
myC2.SetRightMargin( rightMargin )
myC2.SetTopMargin( topMargin )
myC2.SetBottomMargin( bottomMargin )
myC2.SetFrameBorderMode(0)
myC2.SetFrameBorderMode(0)

pad1 = ROOT.TPad("pad1","pad1", 0.05, 0.3,0.95, 0.97)
pad1.SetBottomMargin(0)
pad1.SetRightMargin( rightMargin )
pad1.SetLeftMargin( leftMargin )
pad1.Draw()

pad2 = ROOT.TPad("pad2","pad2", 0.05, 0.02, 0.95, 0.29)
pad2.SetTopMargin(0.04)
pad2.SetTopMargin(0.008)
pad2.SetBottomMargin(0.4)
pad2.SetRightMargin( rightMargin )
pad2.SetLeftMargin( leftMargin )
pad2.Draw()

pad1.cd()
mg_LYSO3mmvs_sipmsize.Draw("AP")

mg_LYSO3mmvs_sipmsize.GetHistogram().GetXaxis().SetTitle("SiPM size [mm]")
mg_LYSO3mmvs_sipmsize.GetHistogram().GetYaxis().SetTitle(plot_title)
mg_LYSO3mmvs_sipmsize.GetHistogram().SetTitle("")
mg_LYSO3mmvs_sipmsize.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_LYSO3mmvs_sipmsize.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_LYSO3mmvs_sipmsize.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_LYSO3mmvs_sipmsize.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
mg_LYSO3mmvs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
mg_LYSO3mmvs_sipmsize.GetHistogram().GetYaxis().SetRangeUser(0.0,400.0)

pad1.Modified()
pad1.Update()

leg_LYSO3mm_vs_sipmsize = ROOT.TLegend(0.2,0.65,0.6,0.85)
leg_LYSO3mm_vs_sipmsize.SetBorderSize(0)
leg_LYSO3mm_vs_sipmsize.SetTextSize(0.04)
leg_LYSO3mm_vs_sipmsize.SetLineColor(1)
leg_LYSO3mm_vs_sipmsize.SetLineStyle(1)
leg_LYSO3mm_vs_sipmsize.SetLineWidth(1)
leg_LYSO3mm_vs_sipmsize.SetFillColor(0)
leg_LYSO3mm_vs_sipmsize.SetFillStyle(1001)

leg_LYSO3mm_vs_sipmsize.AddEntry(gr_LYSO3mm_x0_vs_sipmsize, "LYSO (3mm) center (0mm)", "p");
leg_LYSO3mm_vs_sipmsize.AddEntry(gr_LYSO3mm_x5_vs_sipmsize, "LYSO (3mm) edge (5mm)", "p");
leg_LYSO3mm_vs_sipmsize.Draw()

pad2.cd()

gr_ratio_3mm_vs_sipmsize.GetHistogram().SetTitle("")
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetYaxis().SetTitle("edge / center")
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetYaxis().SetRangeUser(0.5,1.0)
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetYaxis().SetNdivisions( 5, False )
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetYaxis().CenterTitle( True )
gr_ratio_3mm_vs_sipmsize.GetHistogram().SetStats( 0 )
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetXaxis().SetTitle("SiPM size [mm]")
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetXaxis().SetTitleSize( 0.14 )
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetXaxis().SetLabelSize( 0.12 )
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetXaxis().SetTitleOffset( 0.9 )
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetYaxis().SetTitleSize( 0.1 )
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetYaxis().SetLabelSize( 0.1 )
gr_ratio_3mm_vs_sipmsize.GetHistogram().GetYaxis().SetTitleOffset( 0.5 )
gr_ratio_3mm_vs_sipmsize.Draw("AP")

pad1.Update()
pad2.Update()



myC2.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO3mm.pdf")
myC2.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO3mm.png")
myC2.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO3mm.C")



pad1.cd()
mg_LYSO4mmvs_sipmsize.Draw("AP")

mg_LYSO4mmvs_sipmsize.GetHistogram().GetXaxis().SetTitle("SiPM size [mm]")
mg_LYSO4mmvs_sipmsize.GetHistogram().GetYaxis().SetTitle(plot_title)
mg_LYSO4mmvs_sipmsize.GetHistogram().SetTitle("")
mg_LYSO4mmvs_sipmsize.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_LYSO4mmvs_sipmsize.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_LYSO4mmvs_sipmsize.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_LYSO4mmvs_sipmsize.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
mg_LYSO4mmvs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
mg_LYSO4mmvs_sipmsize.GetHistogram().GetYaxis().SetRangeUser(0.0,400.0)

pad1.Modified()
pad1.Update()


leg_LYSO4mm_vs_sipmsize = ROOT.TLegend(0.2,0.65,0.6,0.85)
leg_LYSO4mm_vs_sipmsize.SetBorderSize(0)
leg_LYSO4mm_vs_sipmsize.SetTextSize(0.04)
leg_LYSO4mm_vs_sipmsize.SetLineColor(1)
leg_LYSO4mm_vs_sipmsize.SetLineStyle(1)
leg_LYSO4mm_vs_sipmsize.SetLineWidth(1)
leg_LYSO4mm_vs_sipmsize.SetFillColor(0)
leg_LYSO4mm_vs_sipmsize.SetFillStyle(1001)

leg_LYSO4mm_vs_sipmsize.AddEntry(gr_LYSO4mm_x0_vs_sipmsize, "LYSO (4mm) center (0mm)", "p");
leg_LYSO4mm_vs_sipmsize.AddEntry(gr_LYSO4mm_x5_vs_sipmsize, "LYSO (4mm) edge (5mm)", "p");
leg_LYSO4mm_vs_sipmsize.Draw()


pad2.cd()

gr_ratio_4mm_vs_sipmsize.GetHistogram().SetTitle("")
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetYaxis().SetTitle("edge / center")
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetYaxis().SetRangeUser(0.5,1.0)
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetYaxis().SetNdivisions( 5, False )
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetYaxis().CenterTitle( True )
gr_ratio_4mm_vs_sipmsize.GetHistogram().SetStats( 0 )
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetXaxis().SetTitle("SiPM size [mm]")
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetXaxis().SetTitleSize( 0.14 )
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetXaxis().SetLabelSize( 0.12 )
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetXaxis().SetTitleOffset( 0.9 )
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetYaxis().SetTitleSize( 0.1 )
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetYaxis().SetLabelSize( 0.1 )
gr_ratio_4mm_vs_sipmsize.GetHistogram().GetYaxis().SetTitleOffset( 0.5 )
gr_ratio_4mm_vs_sipmsize.Draw("AP")

pad1.Update()
pad2.Update()


myC2.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO4mm.pdf")
myC2.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO4mm.png")
myC2.SaveAs(outputDir+plot_name+"_vs_sipmsize_LYSO4mm.C")

