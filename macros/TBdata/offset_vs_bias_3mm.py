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

x_4mm = [0.173542, 0.137326, 0.156245, 0.147311, 0.144701]
xTW_4mm = [0.14511, 0.141104, 0.141456, 0.137485, 0.14765]
ex_4mm = [0.0,0.0,0.0,0.0,0.0]

x_3mm = [0.174996, 0.214111, 0.120719, 0.157117, 0.158669]
xTW_3mm = [0.106348, 0.121212, 0.0978124, 0.123417, 0.120487]
ex_3mm = [0.0,0.0,0.0,0.0,0.0]

y_4mm = [0.161172, 0.131518, 0.143084, 0.136436, 0.128387]
yTW_4mm = [0.144642, 0.138663, 0.126299, 0.120722, 0.130987]
ey_4mm = [0.0,0.0,0.0,0.0,0.0]

y_3mm = [0.1700, 0.1800, 0.112906, 0.144679, 0.136799]
yTW_3mm = [0.175, 0.17, 0.0907189, 0.121189, 0.113698]
ey_3mm = [0.0,0.0,0.0,0.0,0.0]


y_name = "timeoffset_3mm"
y_title = "time offset [ns]"


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

gr_y_4mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(y_4mm), np.array(ebias), np.array(ey_4mm))
gr_y_3mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(y_3mm), np.array(ebias), np.array(ey_3mm))

gr_x_4mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(x_4mm), np.array(ebias), np.array(ex_4mm))
gr_x_3mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(x_3mm), np.array(ebias), np.array(ex_3mm))

gr_yTW_4mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(yTW_4mm), np.array(ebias), np.array(ey_4mm))
gr_yTW_3mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(yTW_3mm), np.array(ebias), np.array(ey_3mm))

gr_xTW_4mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(xTW_4mm), np.array(ebias), np.array(ex_4mm))
gr_xTW_3mm_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(xTW_3mm), np.array(ebias), np.array(ex_3mm))



gr_y_4mm_vs_bias.SetMarkerStyle( 20 )
gr_y_4mm_vs_bias.SetMarkerColor( ROOT.kRed )
gr_y_4mm_vs_bias.SetLineWidth( 2 )
gr_y_4mm_vs_bias.SetLineColor( ROOT.kRed ) 

gr_y_3mm_vs_bias.SetMarkerStyle( 20 )
gr_y_3mm_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_y_3mm_vs_bias.SetLineWidth( 2 )
gr_y_3mm_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_x_4mm_vs_bias.SetMarkerStyle( 21 )
gr_x_4mm_vs_bias.SetMarkerColor( ROOT.kRed )
gr_x_4mm_vs_bias.SetLineWidth( 2 )
gr_x_4mm_vs_bias.SetLineColor( ROOT.kRed ) 

gr_x_3mm_vs_bias.SetMarkerStyle( 21 )
gr_x_3mm_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_x_3mm_vs_bias.SetLineWidth( 2 )
gr_x_3mm_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_yTW_4mm_vs_bias.SetMarkerStyle( 24 )
gr_yTW_4mm_vs_bias.SetMarkerColor( ROOT.kRed )
gr_yTW_4mm_vs_bias.SetLineWidth( 2 )
gr_yTW_4mm_vs_bias.SetLineColor( ROOT.kRed ) 

gr_yTW_3mm_vs_bias.SetMarkerStyle( 24 )
gr_yTW_3mm_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_yTW_3mm_vs_bias.SetLineWidth( 2 )
gr_yTW_3mm_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_xTW_4mm_vs_bias.SetMarkerStyle( 25 )
gr_xTW_4mm_vs_bias.SetMarkerColor( ROOT.kRed )
gr_xTW_4mm_vs_bias.SetLineWidth( 2 )
gr_xTW_4mm_vs_bias.SetLineColor( ROOT.kRed ) 

gr_xTW_3mm_vs_bias.SetMarkerStyle( 25 )
gr_xTW_3mm_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_xTW_3mm_vs_bias.SetLineWidth( 2 )
gr_xTW_3mm_vs_bias.SetLineColor( ROOT.kBlue ) 


mg_vs_bias = ROOT.TMultiGraph()

mg_vs_bias.Add(gr_y_4mm_vs_bias)
mg_vs_bias.Add(gr_x_4mm_vs_bias)
mg_vs_bias.Add(gr_y_3mm_vs_bias)
mg_vs_bias.Add(gr_x_3mm_vs_bias)

mg_vs_bias.Add(gr_yTW_4mm_vs_bias)
mg_vs_bias.Add(gr_xTW_4mm_vs_bias)
mg_vs_bias.Add(gr_yTW_3mm_vs_bias)
mg_vs_bias.Add(gr_xTW_3mm_vs_bias)


mg_vs_bias.Draw("AP")


mg_vs_bias.GetHistogram().GetXaxis().SetTitle("bias voltage [V]")
mg_vs_bias.GetHistogram().GetYaxis().SetTitle(y_title)
mg_vs_bias.GetHistogram().SetTitle("")
mg_vs_bias.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
mg_vs_bias.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
mg_vs_bias.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
mg_vs_bias.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
mg_vs_bias.GetHistogram().GetXaxis().SetRangeUser(55.0,61.0)

ROOT.gPad.Modified()
ROOT.gPad.Update()

leg_vs_bias = ROOT.TLegend(0.15,0.15,0.9,0.4)
leg_vs_bias.SetBorderSize(0)
leg_vs_bias.SetNColumns(2)
leg_vs_bias.SetTextSize(0.03)
leg_vs_bias.SetLineColor(1)
leg_vs_bias.SetLineStyle(1)
leg_vs_bias.SetLineWidth(1)
leg_vs_bias.SetFillColor(0)
leg_vs_bias.SetFillStyle(1001)

leg_vs_bias.AddEntry(gr_x_4mm_vs_bias, "4mm LYSO, X", "lp");
leg_vs_bias.AddEntry(gr_xTW_4mm_vs_bias, "4mm LYSO, X, with TW corr", "lp");
leg_vs_bias.AddEntry(gr_x_3mm_vs_bias, "3mm LYSO, X", "lp");
leg_vs_bias.AddEntry(gr_xTW_3mm_vs_bias, "3mm LYSO, X, with TW corr", "lp");
leg_vs_bias.AddEntry(gr_y_4mm_vs_bias, "4mm LYSO, Y", "lp");
leg_vs_bias.AddEntry(gr_yTW_4mm_vs_bias, "4mm LYSO, Y, with TW corr", "lp");
leg_vs_bias.AddEntry(gr_y_3mm_vs_bias, "3mm LYSO, Y", "lp");
leg_vs_bias.AddEntry(gr_yTW_3mm_vs_bias, "3mm LYSO, Y, with TW corr", "lp");
leg_vs_bias.Draw()


myC.SaveAs(outputDir+y_name+"_vs_bias.pdf")
myC.SaveAs(outputDir+y_name+"_vs_bias.png")
myC.SaveAs(outputDir+y_name+"_vs_bias.C")

