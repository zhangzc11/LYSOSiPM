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
ebias = [0.5,0.5,0.5,0.5,0.5]

LYSO_upstream = [0.0620566, 0.072818, 0.118152, 0.105294, 0.088945]
LYSOCorr_upstream = [0.0608826, 0.05999, 0.0563221, 0.0634529, 0.0541822]
eLYSO_upstream = [0.0,0.0,0.0,0.0,0.0]

LYSO_downstream = [0.074832, 0.0695512, 0.07107, 0.0617718, 0.0519748]
LYSOCorr_downstream = [0.0564232, 0.0447148, 0.0454185, 0.057026, 0.0509644]
eLYSO_downstream = [0.0,0.0,0.0,0.0,0.0]

SiPM_upstream = [0.0416443, 0.0461555, 0.0515907, 0.0541379, 0.0484847]
SiPMCorr_upstream = [0.0398975, 0.0423887, 0.0438585, 0.0470227, 0.0424589]
eSiPM_upstream = [0.0,0.0,0.0,0.0,0.0]

SiPM_downstream = [0.0438829, 0.0393404, 0.042408, 0.0457643, 0.0541969]
SiPMCorr_downstream = [0.0421058, 0.0392482, 0.0395618, 0.0406256, 0.0302152]
eSiPM_downstream = [0.0,0.0,0.0,0.0,0.0]


SiPM_name = "timeresolution"
SiPM_title = "time resolution [ns]"


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

gr_SiPM_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(SiPM_upstream), np.array(ebias), np.array(eSiPM_upstream))
gr_SiPM_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(SiPM_downstream), np.array(ebias), np.array(eSiPM_downstream))

gr_LYSO_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(LYSO_upstream), np.array(ebias), np.array(eLYSO_upstream))
gr_LYSO_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(LYSO_downstream), np.array(ebias), np.array(eLYSO_downstream))

gr_SiPMCorr_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(SiPMCorr_upstream), np.array(ebias), np.array(eSiPM_upstream))
gr_SiPMCorr_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(SiPMCorr_downstream), np.array(ebias), np.array(eSiPM_downstream))

gr_LYSOCorr_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(LYSOCorr_upstream), np.array(ebias), np.array(eLYSO_upstream))
gr_LYSOCorr_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(LYSOCorr_downstream), np.array(ebias), np.array(eLYSO_downstream))



gr_SiPM_upstream_vs_bias.SetMarkerStyle( 20 )
gr_SiPM_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_SiPM_upstream_vs_bias.SetLineWidth( 2 )
gr_SiPM_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_SiPM_downstream_vs_bias.SetMarkerStyle( 20 )
gr_SiPM_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_SiPM_downstream_vs_bias.SetLineWidth( 2 )
gr_SiPM_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_LYSO_upstream_vs_bias.SetMarkerStyle( 21 )
gr_LYSO_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_LYSO_upstream_vs_bias.SetLineWidth( 2 )
gr_LYSO_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_LYSO_downstream_vs_bias.SetMarkerStyle( 21 )
gr_LYSO_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_LYSO_downstream_vs_bias.SetLineWidth( 2 )
gr_LYSO_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_SiPMCorr_upstream_vs_bias.SetMarkerStyle( 24 )
gr_SiPMCorr_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_SiPMCorr_upstream_vs_bias.SetLineWidth( 2 )
gr_SiPMCorr_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_SiPMCorr_downstream_vs_bias.SetMarkerStyle( 24 )
gr_SiPMCorr_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_SiPMCorr_downstream_vs_bias.SetLineWidth( 2 )
gr_SiPMCorr_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_LYSOCorr_upstream_vs_bias.SetMarkerStyle( 25 )
gr_LYSOCorr_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_LYSOCorr_upstream_vs_bias.SetLineWidth( 2 )
gr_LYSOCorr_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_LYSOCorr_downstream_vs_bias.SetMarkerStyle( 25 )
gr_LYSOCorr_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_LYSOCorr_downstream_vs_bias.SetLineWidth( 2 )
gr_LYSOCorr_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 


mg_vs_bias = ROOT.TMultiGraph()

mg_vs_bias.Add(gr_SiPM_upstream_vs_bias)
mg_vs_bias.Add(gr_LYSO_upstream_vs_bias)
mg_vs_bias.Add(gr_SiPM_downstream_vs_bias)
mg_vs_bias.Add(gr_LYSO_downstream_vs_bias)

mg_vs_bias.Add(gr_SiPMCorr_upstream_vs_bias)
mg_vs_bias.Add(gr_LYSOCorr_upstream_vs_bias)
mg_vs_bias.Add(gr_SiPMCorr_downstream_vs_bias)
mg_vs_bias.Add(gr_LYSOCorr_downstream_vs_bias)


mg_vs_bias.Draw("AP")


mg_vs_bias.GetHistogram().GetXaxis().SetTitle("bias voltage [V]")
mg_vs_bias.GetHistogram().GetYaxis().SetTitle(SiPM_title)
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

leg_vs_bias.AddEntry(gr_LYSO_upstream_vs_bias, "LYSO upstream, LYSO area", "lp");
leg_vs_bias.AddEntry(gr_LYSO_downstream_vs_bias, "LYSO downstream, LYSO area", "lp");
leg_vs_bias.AddEntry(gr_LYSOCorr_upstream_vs_bias, "LYSO upstream, LYSO area, w/ corr", "lp");
leg_vs_bias.AddEntry(gr_LYSOCorr_downstream_vs_bias, "LYSO downstream, LYSO area, w/ corr", "lp");
leg_vs_bias.AddEntry(gr_SiPM_upstream_vs_bias, "LYSO upstream, SiPM area", "lp");
leg_vs_bias.AddEntry(gr_SiPM_downstream_vs_bias, "LYSO downstream, SiPM area", "lp");
leg_vs_bias.AddEntry(gr_SiPMCorr_upstream_vs_bias, "LYSO upstream, SiPM area, w/ corr", "lp");
leg_vs_bias.AddEntry(gr_SiPMCorr_downstream_vs_bias, "LYSO downstream, SiPM area, w/ corr", "lp");
leg_vs_bias.Draw()


myC.SaveAs(outputDir+SiPM_name+"_vs_bias.pdf")
myC.SaveAs(outputDir+SiPM_name+"_vs_bias.png")
myC.SaveAs(outputDir+SiPM_name+"_vs_bias.C")

