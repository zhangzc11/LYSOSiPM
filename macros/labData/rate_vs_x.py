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
axisTitleOffsetY = 1.2

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
outputDir = "~/LabData/Zhicai_Spring2018/plots/"

os.system("mkdir -p "+outputDir)


########################################################

x = [1.0,5.0,10.0,15.0,20.0,25.0]
ex = [0.1,0.1,0.1,0.1,0.1,0.1]

rate_72V = [721.0, 700., 675., 640., 610., 590.]
erate_72V = [5.0, 5., 5., 5., 5., 5.]

rate_70V = [602., 482., 350., 190., 95., 55.]
erate_70V = [5.0, 5., 5., 5., 5., 5.]

y = []
ey = []

for i in range(0,6):
	print i
	y.append(1.0/(x[i]*x[i]))
	ey.append(0.1*2/(x[i]*x[i]))

myC = ROOT.TCanvas( "myC", "myC", 200, 10, 800, 800 )
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

gr_rate_72V_vs_x = ROOT.TGraphErrors(6, np.array(x), np.array(rate_72V), np.array(ex), np.array(erate_72V))
gr_rate_70V_vs_x = ROOT.TGraphErrors(6, np.array(x), np.array(rate_70V), np.array(ex), np.array(erate_70V))

gr_rate_72V_vs_x.SetMarkerStyle( 20 )
gr_rate_72V_vs_x.SetMarkerColor( ROOT.kBlack )
gr_rate_72V_vs_x.SetLineWidth( 2 )
gr_rate_72V_vs_x.SetLineColor( ROOT.kBlack ) 

gr_rate_70V_vs_x.SetMarkerStyle( 20 )
gr_rate_70V_vs_x.SetMarkerColor( ROOT.kRed )
gr_rate_70V_vs_x.SetLineWidth( 2 )
gr_rate_70V_vs_x.SetLineColor( ROOT.kRed ) 

mg_vs_x = ROOT.TMultiGraph()

mg_vs_x.Add(gr_rate_72V_vs_x)
mg_vs_x.Add(gr_rate_70V_vs_x)

mg_vs_x.Draw("AP")


mg_vs_x.GetHistogram().GetXaxis().SetTitle("distance (Cs137, LYSO) [mm]")
mg_vs_x.GetHistogram().GetYaxis().SetTitle("rate [Hz]")
mg_vs_x.GetHistogram().SetTitle("")
mg_vs_x.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_vs_x.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_vs_x.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_vs_x.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
mg_vs_x.GetHistogram().GetYaxis().SetRangeUser(0.0,800.0)

ROOT.gPad.Modified()
ROOT.gPad.Update()

leg_vs_x = ROOT.TLegend(0.7,0.4,0.9,0.6)
leg_vs_x.SetBorderSize(0)
leg_vs_x.SetTextSize(0.03)
leg_vs_x.SetLineColor(1)
leg_vs_x.SetLineStyle(1)
leg_vs_x.SetLineWidth(1)
leg_vs_x.SetFillColor(0)
leg_vs_x.SetFillStyle(1001)

leg_vs_x.AddEntry(gr_rate_72V_vs_x, "bias = 72V", "lp");
leg_vs_x.AddEntry(gr_rate_70V_vs_x, "bias = 70V", "lp");
leg_vs_x.Draw()


myC.SaveAs(outputDir+"rate_vs_x.pdf")
myC.SaveAs(outputDir+"rate_vs_x.png")
myC.SaveAs(outputDir+"rate_vs_x.C")

gr_rate_72V_vs_y = ROOT.TGraphErrors(6, np.array(y), np.array(rate_72V), np.array(ey), np.array(erate_72V))
gr_rate_70V_vs_y = ROOT.TGraphErrors(6, np.array(y), np.array(rate_70V), np.array(ey), np.array(erate_70V))

gr_rate_72V_vs_y.SetMarkerStyle( 20 )
gr_rate_72V_vs_y.SetMarkerColor( ROOT.kBlack )
gr_rate_72V_vs_y.SetLineWidth( 2 )
gr_rate_72V_vs_y.SetLineColor( ROOT.kBlack ) 

gr_rate_70V_vs_y.SetMarkerStyle( 20 )
gr_rate_70V_vs_y.SetMarkerColor( ROOT.kRed )
gr_rate_70V_vs_y.SetLineWidth( 2 )
gr_rate_70V_vs_y.SetLineColor( ROOT.kRed ) 

mg_vs_y = ROOT.TMultiGraph()

mg_vs_y.Add(gr_rate_72V_vs_y)
mg_vs_y.Add(gr_rate_70V_vs_y)

mg_vs_y.Draw("AP")


mg_vs_y.GetHistogram().GetXaxis().SetTitle("1/d^{2} [mm^{-2}]")
mg_vs_y.GetHistogram().GetYaxis().SetTitle("rate [Hz]")
mg_vs_y.GetHistogram().SetTitle("")
mg_vs_y.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_vs_y.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_vs_y.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_vs_y.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
mg_vs_y.GetHistogram().GetYaxis().SetRangeUser(0.0,800.0)
mg_vs_y.GetHistogram().GetXaxis().SetRangeUser(0.0,0.05)

ROOT.gPad.Modified()
ROOT.gPad.Update()

leg_vs_y = ROOT.TLegend(0.7,0.4,0.9,0.6)
leg_vs_y.SetBorderSize(0)
leg_vs_y.SetTextSize(0.03)
leg_vs_y.SetLineColor(1)
leg_vs_y.SetLineStyle(1)
leg_vs_y.SetLineWidth(1)
leg_vs_y.SetFillColor(0)
leg_vs_y.SetFillStyle(1001)

leg_vs_y.AddEntry(gr_rate_72V_vs_y, "bias = 72V", "lp");
leg_vs_y.AddEntry(gr_rate_70V_vs_y, "bias = 70V", "lp");
leg_vs_y.Draw()


myC.SaveAs(outputDir+"rate_vs_y.pdf")
myC.SaveAs(outputDir+"rate_vs_y.png")
myC.SaveAs(outputDir+"rate_vs_y.C")

