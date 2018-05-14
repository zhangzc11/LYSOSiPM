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
outputDir = "./plots_V2/"

os.system("mkdir -p "+outputDir)


########################################################

bias = [56.0,57.0,58.0,59.0,60.0]
ebias = [0.5,0.5,0.5,0.5,0.5]

LYSO_4mm = [0.0632081, 0.0738757, 0.116975, 0.104504, 0.0896635]
LYSOCorr_4mm = [0.0632081, 0.0731887, 0.0695529, 0.0744929, 0.0647054]
eLYSO_4mm = [0.0,0.0,0.0,0.0,0.0]

LYSO_3mm = [0.0652689, 0.0604565, 0.0897435, 0.0616501, 0.0663384]
LYSOCorr_3mm = [0.0652689, 0.0496391, 0.062362, 0.0560803, 0.0564728]
eLYSO_3mm = [0.0,0.0,0.0,0.0,0.0]

SiPM_4mm = [0.0427518, 0.0507468, 0.0528026, 0.0550675, 0.0500489]
SiPMCorr_4mm = [0.0411169, 0.0446211, 0.0499816, 0.0486331, 0.0449771]
eSiPM_4mm = [0.0,0.0,0.0,0.0,0.0]

SiPM_3mm = [0.0480348, 0.0456343, 0.0463389, 0.0431563, 0.04424]
SiPMCorr_3mm = [0.0397811, 0.036107, 0.0444951, 0.0423983, 0.0425856]
eSiPM_3mm = [0.0,0.0,0.0,0.0,0.0]


SiPM_name = "timeresolution_3mm"
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

gr_SiPM_4mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(SiPM_4mm), np.array(ebias), np.array(eSiPM_4mm))
gr_SiPM_3mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(SiPM_3mm), np.array(ebias), np.array(eSiPM_3mm))

gr_LYSO_4mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(LYSO_4mm), np.array(ebias), np.array(eLYSO_4mm))
gr_LYSO_3mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(LYSO_3mm), np.array(ebias), np.array(eLYSO_3mm))

gr_SiPMCorr_4mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(SiPMCorr_4mm), np.array(ebias), np.array(eSiPM_4mm))
gr_SiPMCorr_3mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(SiPMCorr_3mm), np.array(ebias), np.array(eSiPM_3mm))

gr_LYSOCorr_4mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(LYSOCorr_4mm), np.array(ebias), np.array(eLYSO_4mm))
gr_LYSOCorr_3mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(LYSOCorr_3mm), np.array(ebias), np.array(eLYSO_3mm))



gr_SiPM_4mm_vs_bias.SetMarkerStyle( 20 )
gr_SiPM_4mm_vs_bias.SetMarkerColor( ROOT.kRed )
gr_SiPM_4mm_vs_bias.SetLineWidth( 2 )
gr_SiPM_4mm_vs_bias.SetLineColor( ROOT.kRed ) 

gr_SiPM_3mm_vs_bias.SetMarkerStyle( 20 )
gr_SiPM_3mm_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_SiPM_3mm_vs_bias.SetLineWidth( 2 )
gr_SiPM_3mm_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_LYSO_4mm_vs_bias.SetMarkerStyle( 21 )
gr_LYSO_4mm_vs_bias.SetMarkerColor( ROOT.kRed )
gr_LYSO_4mm_vs_bias.SetLineWidth( 2 )
gr_LYSO_4mm_vs_bias.SetLineColor( ROOT.kRed ) 

gr_LYSO_3mm_vs_bias.SetMarkerStyle( 21 )
gr_LYSO_3mm_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_LYSO_3mm_vs_bias.SetLineWidth( 2 )
gr_LYSO_3mm_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_SiPMCorr_4mm_vs_bias.SetMarkerStyle( 24 )
gr_SiPMCorr_4mm_vs_bias.SetMarkerColor( ROOT.kRed )
gr_SiPMCorr_4mm_vs_bias.SetLineWidth( 2 )
gr_SiPMCorr_4mm_vs_bias.SetLineColor( ROOT.kRed ) 

gr_SiPMCorr_3mm_vs_bias.SetMarkerStyle( 24 )
gr_SiPMCorr_3mm_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_SiPMCorr_3mm_vs_bias.SetLineWidth( 2 )
gr_SiPMCorr_3mm_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_LYSOCorr_4mm_vs_bias.SetMarkerStyle( 25 )
gr_LYSOCorr_4mm_vs_bias.SetMarkerColor( ROOT.kRed )
gr_LYSOCorr_4mm_vs_bias.SetLineWidth( 2 )
gr_LYSOCorr_4mm_vs_bias.SetLineColor( ROOT.kRed ) 

gr_LYSOCorr_3mm_vs_bias.SetMarkerStyle( 25 )
gr_LYSOCorr_3mm_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_LYSOCorr_3mm_vs_bias.SetLineWidth( 2 )
gr_LYSOCorr_3mm_vs_bias.SetLineColor( ROOT.kBlue ) 


mg_vs_bias = ROOT.TMultiGraph()

mg_vs_bias.Add(gr_SiPM_4mm_vs_bias)
mg_vs_bias.Add(gr_LYSO_4mm_vs_bias)
mg_vs_bias.Add(gr_SiPM_3mm_vs_bias)
mg_vs_bias.Add(gr_LYSO_3mm_vs_bias)

mg_vs_bias.Add(gr_SiPMCorr_4mm_vs_bias)
mg_vs_bias.Add(gr_LYSOCorr_4mm_vs_bias)
mg_vs_bias.Add(gr_SiPMCorr_3mm_vs_bias)
mg_vs_bias.Add(gr_LYSOCorr_3mm_vs_bias)


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

leg_vs_bias.AddEntry(gr_LYSO_4mm_vs_bias, "4mm LYSO, LYSO area", "lp");
leg_vs_bias.AddEntry(gr_LYSOCorr_4mm_vs_bias, "4mm LYSO, LYSO area, with corrections", "lp");
leg_vs_bias.AddEntry(gr_LYSO_3mm_vs_bias, "3mm LYSO, LYSO area", "lp");
leg_vs_bias.AddEntry(gr_LYSOCorr_3mm_vs_bias, "3mm LYSO, LYSO area, with corrections", "lp");
leg_vs_bias.AddEntry(gr_SiPM_4mm_vs_bias, "4mm LYSO, SiPM area", "lp");
leg_vs_bias.AddEntry(gr_SiPMCorr_4mm_vs_bias, "4mm LYSO, SiPM area, with corrections", "lp");

leg_vs_bias.AddEntry(gr_SiPM_3mm_vs_bias, "3mm LYSO, SiPM area", "lp");
leg_vs_bias.AddEntry(gr_SiPMCorr_3mm_vs_bias, "3mm LYSO, SiPM area, with corrections", "lp");
leg_vs_bias.Draw()


myC.SaveAs(outputDir+SiPM_name+"_vs_bias.pdf")
myC.SaveAs(outputDir+SiPM_name+"_vs_bias.png")
myC.SaveAs(outputDir+SiPM_name+"_vs_bias.C")

