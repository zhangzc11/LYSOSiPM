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
outputDir = "./plots_V3/"

os.system("mkdir -p "+outputDir)


########################################################

bias = [56.0,57.0,58.0,59.0,60.0]
ebias = [0.0,0.0,0.0,0.0,0.0]

NoCorr_upstream = [0.1007, 0.07326, 0.118152, 0.105294, 0.08998]
TWCorr_upstream = [0.0926635, 0.06362, 0.0937857, 0.0970922, 0.088]
XYCorr_upstream = [0.0736697, 0.05999, 0.0646211, 0.0686308, 0.0589993]
TWXYCorr_upstream = [0.0608826, 0.05999, 0.0563221, 0.0634529, 0.0541822]
eNoCorr_upstream = [0.0021,0.0014,0.0027,0.0025,0.0012]
eXYCorr_upstream = [0.00181,0.001,0.0007,0.0011,0.001]
eTWCorr_upstream = [0.00324,0.00194,0.00197,0.0029,0.0016]

NoCorr_downstream = [0.074832, 0.0695512, 0.07107, 0.0617718, 0.0519748]
TWCorr_downstream = [0.0594212, 0.0576024, 0.0580889, 0.057026, 0.0509644]
XYCorr_downstream = [0.0581958, 0.045809, 0.0462676, 0.0606943, 0.05096]
TWXYCorr_downstream = [ 0.0564232, 0.0447148, 0.0454185, 0.057026, 0.0509644]
eNoCorr_downstream = [0.0009,0.0008,0.0007,0.0006,0.0005]
eXYCorr_downstream = [0.0007,0.0005,0.0004,0.0008,0.0005]
eTWCorr_downstream = [0.0007,0.0007,0.0006,0.0006,0.0005]


plot_name = "timeresolution_tw"
plot_title = "time resolution [ns]"


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

gr_XYCorr_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(XYCorr_upstream), np.array(ebias), np.array(eXYCorr_upstream))
gr_XYCorr_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(XYCorr_downstream), np.array(ebias), np.array(eXYCorr_downstream))

gr_NoCorr_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(NoCorr_upstream), np.array(ebias), np.array(eNoCorr_upstream))
gr_NoCorr_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(NoCorr_downstream), np.array(ebias), np.array(eNoCorr_downstream))

gr_TWXYCorr_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(TWXYCorr_upstream), np.array(ebias), np.array(eXYCorr_upstream))
gr_TWXYCorr_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(TWXYCorr_downstream), np.array(ebias), np.array(eXYCorr_downstream))

gr_TWCorr_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(TWCorr_upstream), np.array(ebias), np.array(eTWCorr_upstream))
gr_TWCorr_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(TWCorr_downstream), np.array(ebias), np.array(eTWCorr_downstream))



gr_XYCorr_upstream_vs_bias.SetMarkerStyle( 20 )
gr_XYCorr_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_XYCorr_upstream_vs_bias.SetLineWidth( 2 )
gr_XYCorr_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_XYCorr_downstream_vs_bias.SetMarkerStyle( 20 )
gr_XYCorr_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_XYCorr_downstream_vs_bias.SetLineWidth( 2 )
gr_XYCorr_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_NoCorr_upstream_vs_bias.SetMarkerStyle( 21 )
gr_NoCorr_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_NoCorr_upstream_vs_bias.SetLineWidth( 2 )
gr_NoCorr_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_NoCorr_downstream_vs_bias.SetMarkerStyle( 21 )
gr_NoCorr_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_NoCorr_downstream_vs_bias.SetLineWidth( 2 )
gr_NoCorr_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_TWXYCorr_upstream_vs_bias.SetMarkerStyle( 24 )
gr_TWXYCorr_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_TWXYCorr_upstream_vs_bias.SetLineWidth( 2 )
gr_TWXYCorr_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_TWXYCorr_downstream_vs_bias.SetMarkerStyle( 24 )
gr_TWXYCorr_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_TWXYCorr_downstream_vs_bias.SetLineWidth( 2 )
gr_TWXYCorr_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_TWCorr_upstream_vs_bias.SetMarkerStyle( 25 )
gr_TWCorr_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_TWCorr_upstream_vs_bias.SetLineWidth( 2 )
gr_TWCorr_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_TWCorr_downstream_vs_bias.SetMarkerStyle( 25 )
gr_TWCorr_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_TWCorr_downstream_vs_bias.SetLineWidth( 2 )
gr_TWCorr_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 


mg_vs_bias = ROOT.TMultiGraph()

#mg_vs_bias.Add(gr_XYCorr_upstream_vs_bias)
mg_vs_bias.Add(gr_NoCorr_upstream_vs_bias)
#mg_vs_bias.Add(gr_XYCorr_downstream_vs_bias)
mg_vs_bias.Add(gr_NoCorr_downstream_vs_bias)
#mg_vs_bias.Add(gr_TWXYCorr_upstream_vs_bias)
mg_vs_bias.Add(gr_TWCorr_upstream_vs_bias)
#mg_vs_bias.Add(gr_TWXYCorr_downstream_vs_bias)
mg_vs_bias.Add(gr_TWCorr_downstream_vs_bias)

mg_vs_bias.Draw("AP")


mg_vs_bias.GetHistogram().GetXaxis().SetTitle("bias voltage [V]")
mg_vs_bias.GetHistogram().GetYaxis().SetTitle(plot_title)
mg_vs_bias.GetHistogram().SetTitle("")
mg_vs_bias.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_vs_bias.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_vs_bias.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_vs_bias.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
mg_vs_bias.GetHistogram().GetXaxis().SetRangeUser(55.0,61.0)
mg_vs_bias.GetHistogram().GetYaxis().SetRangeUser(-0.020,0.1200)

ROOT.gPad.Modified()
ROOT.gPad.Update()

leg_vs_bias = ROOT.TLegend(0.15,0.15,0.9,0.4)
leg_vs_bias.SetBorderSize(0)
leg_vs_bias.SetNColumns(2)
leg_vs_bias.SetTextSize(0.025)
leg_vs_bias.SetLineColor(1)
leg_vs_bias.SetLineStyle(1)
leg_vs_bias.SetLineWidth(1)
leg_vs_bias.SetFillColor(0)
leg_vs_bias.SetFillStyle(1001)

leg_vs_bias.AddEntry(gr_NoCorr_upstream_vs_bias, "LYSO upstream, no corr", "lp");
leg_vs_bias.AddEntry(gr_NoCorr_downstream_vs_bias, "LYSO downstream, no corr", "lp");
leg_vs_bias.AddEntry(gr_TWCorr_upstream_vs_bias, "LYSO upstream, TW corr", "lp");
leg_vs_bias.AddEntry(gr_TWCorr_downstream_vs_bias, "LYSO downstream, TW corr", "lp");
#leg_vs_bias.AddEntry(gr_XYCorr_upstream_vs_bias, "LYSO upstream, XY corr", "lp");
#leg_vs_bias.AddEntry(gr_XYCorr_downstream_vs_bias, "LYSO downstream, XY corr", "lp");
#leg_vs_bias.AddEntry(gr_TWXYCorr_upstream_vs_bias, "LYSO upstream, TW+XY corr", "lp");
#leg_vs_bias.AddEntry(gr_TWXYCorr_downstream_vs_bias, "LYSO downstream, TW+XY corr", "lp");
leg_vs_bias.Draw()


myC.SaveAs(outputDir+plot_name+"_vs_bias.pdf")
myC.SaveAs(outputDir+plot_name+"_vs_bias.png")
myC.SaveAs(outputDir+plot_name+"_vs_bias.C")

