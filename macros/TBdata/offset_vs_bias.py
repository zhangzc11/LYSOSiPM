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

x_upstream = [0.185162, 0.154589, 0.171371, 0.181001, 0.180476]
xTW_upstream = [0.158712, 0.161405, 0.148421, 0.142046, 0.164791]
ex_upstream = [0.0,0.0,0.0,0.0,0.0]

x_downstream = [0.144011, 0.138892, 0.136248, 0.108282, 0.118162]
xTW_downstream = [0.1031, 0.107242, 0.0948513, 0.0904813, 0.112327]
ex_downstream = [0.0,0.0,0.0,0.0,0.0]

y_upstream = [0.229026, 0.165978, 0.200133, 0.158224, 0.164091]
yTW_upstream = [0.180723, 0.172692, 0.151679, 0.147783, 0.154421]
ey_upstream = [0.0,0.0,0.0,0.0,0.0]

y_downstream = [0.130, 0.150355, 0.1594, 0.125138, 0.155714]
yTW_downstream = [0.097, 0.120625, 0.122195, 0.113397, 0.152643]
ey_downstream = [0.0,0.0,0.0,0.0,0.0]


y_name = "timeoffset"
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

gr_y_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(y_upstream), np.array(ebias), np.array(ey_upstream))
gr_y_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(y_downstream), np.array(ebias), np.array(ey_downstream))

gr_x_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(x_upstream), np.array(ebias), np.array(ex_upstream))
gr_x_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(x_downstream), np.array(ebias), np.array(ex_downstream))

gr_yTW_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(yTW_upstream), np.array(ebias), np.array(ey_upstream))
gr_yTW_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(yTW_downstream), np.array(ebias), np.array(ey_downstream))

gr_xTW_upstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(xTW_upstream), np.array(ebias), np.array(ex_upstream))
gr_xTW_downstream_vs_bias = ROOT.TGraphErrors(6, np.array(bias), np.array(xTW_downstream), np.array(ebias), np.array(ex_downstream))



gr_y_upstream_vs_bias.SetMarkerStyle( 20 )
gr_y_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_y_upstream_vs_bias.SetLineWidth( 2 )
gr_y_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_y_downstream_vs_bias.SetMarkerStyle( 20 )
gr_y_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_y_downstream_vs_bias.SetLineWidth( 2 )
gr_y_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_x_upstream_vs_bias.SetMarkerStyle( 21 )
gr_x_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_x_upstream_vs_bias.SetLineWidth( 2 )
gr_x_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_x_downstream_vs_bias.SetMarkerStyle( 21 )
gr_x_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_x_downstream_vs_bias.SetLineWidth( 2 )
gr_x_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_yTW_upstream_vs_bias.SetMarkerStyle( 24 )
gr_yTW_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_yTW_upstream_vs_bias.SetLineWidth( 2 )
gr_yTW_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_yTW_downstream_vs_bias.SetMarkerStyle( 24 )
gr_yTW_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_yTW_downstream_vs_bias.SetLineWidth( 2 )
gr_yTW_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 

gr_xTW_upstream_vs_bias.SetMarkerStyle( 25 )
gr_xTW_upstream_vs_bias.SetMarkerColor( ROOT.kRed )
gr_xTW_upstream_vs_bias.SetLineWidth( 2 )
gr_xTW_upstream_vs_bias.SetLineColor( ROOT.kRed ) 

gr_xTW_downstream_vs_bias.SetMarkerStyle( 25 )
gr_xTW_downstream_vs_bias.SetMarkerColor( ROOT.kBlue )
gr_xTW_downstream_vs_bias.SetLineWidth( 2 )
gr_xTW_downstream_vs_bias.SetLineColor( ROOT.kBlue ) 


mg_vs_bias = ROOT.TMultiGraph()

mg_vs_bias.Add(gr_y_upstream_vs_bias)
mg_vs_bias.Add(gr_x_upstream_vs_bias)
mg_vs_bias.Add(gr_y_downstream_vs_bias)
mg_vs_bias.Add(gr_x_downstream_vs_bias)

mg_vs_bias.Add(gr_yTW_upstream_vs_bias)
mg_vs_bias.Add(gr_xTW_upstream_vs_bias)
mg_vs_bias.Add(gr_yTW_downstream_vs_bias)
mg_vs_bias.Add(gr_xTW_downstream_vs_bias)


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

leg_vs_bias.AddEntry(gr_x_upstream_vs_bias, "LYSO upstream, X", "lp");
leg_vs_bias.AddEntry(gr_x_downstream_vs_bias, "LYSO downstream, X", "lp");
leg_vs_bias.AddEntry(gr_xTW_upstream_vs_bias, "LYSO upstream, X, w/ TW corr", "lp");
leg_vs_bias.AddEntry(gr_xTW_downstream_vs_bias, "LYSO downstream, X, w/ TW corr", "lp");
leg_vs_bias.AddEntry(gr_y_upstream_vs_bias, "LYSO upstream, Y", "lp");
leg_vs_bias.AddEntry(gr_y_downstream_vs_bias, "LYSO downstream, Y", "lp");
leg_vs_bias.AddEntry(gr_yTW_upstream_vs_bias, "LYSO upstream, Y, w/ TW corr", "lp");
leg_vs_bias.AddEntry(gr_yTW_downstream_vs_bias, "LYSO downstream, Y, w/ TW corr", "lp");
leg_vs_bias.Draw()


myC.SaveAs(outputDir+y_name+"_vs_bias.pdf")
myC.SaveAs(outputDir+y_name+"_vs_bias.png")
myC.SaveAs(outputDir+y_name+"_vs_bias.C")

