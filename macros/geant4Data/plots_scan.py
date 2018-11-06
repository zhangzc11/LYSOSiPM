import ROOT
import array
import itertools
import os
import numpy as np
import shlex


ROOT.gROOT.SetBatch(True)

ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptFit(111)
#################plot settings###########################
axisTitleSizeX = 0.06
axisTitleSizeY = 0.05
axisTitleOffsetX = 0.9
axisTitleOffsetY = 1.0

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
outputDir = "/Users/zhicai/cernbox/TestBeam/geant4/plots/scan/"

os.system("mkdir -p "+outputDir)

def two_var_vs_xVar(xVarName, xVarTitle, yVarName, yVarTitle, xVar1, exVar1, xVar2, exVar2, yVar1, eyVar1, yVar2, eyVar2, legend1, legend2, logX, maximumY=-999.9, minimumY=-999.9):
	
	yVar1 = 	[float(i) for i in yVar1]
	yVar2 = 	[float(i) for i in yVar2]

	myC = ROOT.TCanvas( "myC", "myC", 200, 10, 800, 600 )
	myC.SetLogx(logX)
	myC.SetGridy(1)
	myC.SetGridx(1)
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

	gr1 = ROOT.TGraphErrors(xVar1.size(), np.array(xVar1), np.array(yVar1), np.array(exVar1), np.array(eyVar1))
	gr2 = ROOT.TGraphErrors(xVar2.size(), np.array(xVar2), np.array(yVar2), np.array(exVar2), np.array(eyVar2))
	
	gr1.SetMarkerStyle( 20 )
	gr1.SetMarkerColor( ROOT.kRed )
	gr1.SetLineWidth( 2 )
	gr1.SetLineColor( ROOT.kRed )

	gr2.SetMarkerStyle( 21 )
	gr2.SetMarkerColor( ROOT.kBlue )
	gr2.SetLineWidth( 2 )
	gr2.SetLineColor( ROOT.kBlue )
	
	
	maxY = gr1.GetHistogram().GetMaximum()
	minY = gr1.GetHistogram().GetMinimum()
	if maxY < gr2.GetHistogram().GetMaximum():
		maxY = gr2.GetHistogram().GetMaximum()
	if minY > gr2.GetHistogram().GetMinimum():
		minY = gr2.GetHistogram().GetMinimum()
	
	#if minY < 0.7*maxY:
	#	minY = 0.0
	minY = 0.0

	maxY = 1.5*maxY
	#minY = 0.8*minY
	if maximumY > -999.0:
		maxY = maximumY
	if minimumY > -999.0:
		minY = minimumY

	mg_vs_xVar = ROOT.TMultiGraph()

	mg_vs_xVar.Add(gr1)
	mg_vs_xVar.Add(gr2)
	mg_vs_xVar.Draw("ALPE")

	mg_vs_xVar.GetHistogram().GetXaxis().SetTitle(xVarTitle)
	mg_vs_xVar.GetHistogram().GetYaxis().SetTitle(yVarTitle)
	mg_vs_xVar.GetHistogram().SetTitle("")
	mg_vs_xVar.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
	mg_vs_xVar.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
	mg_vs_xVar.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
	mg_vs_xVar.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
	mg_vs_xVar.GetHistogram().GetYaxis().SetRangeUser(minY, maxY)
	if logX == 1:
		mg_vs_xVar.GetHistogram().GetXaxis().SetMoreLogLabels()

	ROOT.gPad.Modified()
	ROOT.gPad.Update()

	leg_vs_xVar = ROOT.TLegend(0.66,0.68,0.92,0.89)
	leg_vs_xVar.SetBorderSize(0)
	leg_vs_xVar.SetNColumns(1)
	leg_vs_xVar.SetTextSize(0.045)
	leg_vs_xVar.SetLineColor(1)
	leg_vs_xVar.SetLineStyle(1)
	leg_vs_xVar.SetLineWidth(1)
	leg_vs_xVar.SetFillColor(0)
	leg_vs_xVar.SetFillStyle(1001)

	leg_vs_xVar.AddEntry(gr1, legend1, "pe");
	leg_vs_xVar.AddEntry(gr2, legend2, "pe");

	leg_vs_xVar.Draw()
	myC.SaveAs(outputDir+yVarName+"_vs_"+xVarName+".pdf")
	myC.SaveAs(outputDir+yVarName+"_vs_"+xVarName+".png")
	myC.SaveAs(outputDir+yVarName+"_vs_"+xVarName+".C")

def one_var_vs_xVar(xVarName, xVarTitle, yVarName, yVarTitle, xVar1, exVar1, yVar1, eyVar1, logX, maximumY=-999.9, minimumY=-999.9):
	
	yVar1 = 	[float(i) for i in yVar1]

	myC = ROOT.TCanvas( "myC", "myC", 200, 10, 800, 600 )
	myC.SetLogx(logX)
	myC.SetGridy(1)
	myC.SetGridx(1)
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

	gr1 = ROOT.TGraphErrors(xVar1.size(), np.array(xVar1), np.array(yVar1), np.array(exVar1), np.array(eyVar1))
	
	gr1.SetMarkerStyle( 20 )
	gr1.SetMarkerColor( ROOT.kRed )
	gr1.SetLineWidth( 2 )
	gr1.SetLineColor( ROOT.kRed )
	
	
	maxY = gr1.GetHistogram().GetMaximum()
	minY = gr1.GetHistogram().GetMinimum()
	
	#if minY < 0.7*maxY:
	#	minY = 0.0
	minY = 0.0

	maxY = 1.5*maxY
	#minY = 0.8*minY
	if maximumY > -999.0:
		maxY = maximumY
	if minimumY > -999.0:
		minY = minimumY

	gr1.Draw("ALPE")

	gr1.GetHistogram().GetXaxis().SetTitle(xVarTitle)
	gr1.GetHistogram().GetYaxis().SetTitle(yVarTitle)
	gr1.GetHistogram().SetTitle("")
	gr1.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
	gr1.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
	gr1.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
	gr1.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
	gr1.GetHistogram().GetYaxis().SetRangeUser(minY, maxY)
	if logX == 1:
		gr1.GetHistogram().GetXaxis().SetMoreLogLabels()

	ROOT.gPad.Modified()
	ROOT.gPad.Update()

	myC.SaveAs(outputDir+yVarName+"_vs_"+xVarName+".pdf")
	myC.SaveAs(outputDir+yVarName+"_vs_"+xVarName+".png")
	myC.SaveAs(outputDir+yVarName+"_vs_"+xVarName+".C")


########################################################

LYSOsize = [4.0, 6.0, 8.0, 10.0, 12.0]
AspectRatio = [16.0/(a*a) for a in LYSOsize]
eAspectRatio = [0.0, 0.0, 0.0, 0.0, 0.0]

LYSOthicik = [2.5, 3.0, 3.5, 4.0, 4.5]
eLYSOthicik = [0.0, 0.0, 0.0, 0.0, 0.0]

LYSOpolish = [20.0, 40.0, 60.0, 80.0, 100.0]
eLYSOpolish = [0.0, 0.0, 0.0, 0.0, 0.0]

amp_vs_AR_up = [0.0, 0.0, 0.0, 0.0, 0.0]
eamp_vs_AR_up = [0.0, 0.0, 0.0, 0.0, 0.0]
amp_vs_AR_down = [0.0, 0.0, 0.0, 0.0, 0.0]
eamp_vs_AR_down = [0.0, 0.0, 0.0, 0.0, 0.0]

amp_vs_size_up = [0.0, 0.0, 0.0, 0.0, 0.0]
eamp_vs_size_up = [0.0, 0.0, 0.0, 0.0, 0.0]
amp_vs_size_down = [0.0, 0.0, 0.0, 0.0, 0.0]
eamp_vs_size_down = [0.0, 0.0, 0.0, 0.0, 0.0]

amp_vs_thick_up = [0.0, 0.0, 0.0, 0.0, 0.0]
eamp_vs_thick_up = [0.0, 0.0, 0.0, 0.0, 0.0]
amp_vs_thick_down = [0.0, 0.0, 0.0, 0.0, 0.0]
eamp_vs_thick_down = [0.0, 0.0, 0.0, 0.0, 0.0]

amp_vs_polish_up = [0.0, 0.0, 0.0, 0.0, 0.0]
eamp_vs_polish_up = [0.0, 0.0, 0.0, 0.0, 0.0]
amp_vs_polish_down = [0.0, 0.0, 0.0, 0.0, 0.0]
eamp_vs_polish_down = [0.0, 0.0, 0.0, 0.0, 0.0]

nPhotons_vs_AR_up = [0.0, 0.0, 0.0, 0.0, 0.0]
enPhotons_vs_AR_up = [0.0, 0.0, 0.0, 0.0, 0.0]
nPhotons_vs_AR_down = [0.0, 0.0, 0.0, 0.0, 0.0]
enPhotons_vs_AR_down = [0.0, 0.0, 0.0, 0.0, 0.0]

nPhotons_vs_size_up = [0.0, 0.0, 0.0, 0.0, 0.0]
enPhotons_vs_size_up = [0.0, 0.0, 0.0, 0.0, 0.0]
nPhotons_vs_size_down = [0.0, 0.0, 0.0, 0.0, 0.0]
enPhotons_vs_size_down = [0.0, 0.0, 0.0, 0.0, 0.0]

nPhotons_vs_thick_up = [0.0, 0.0, 0.0, 0.0, 0.0]
enPhotons_vs_thick_up = [0.0, 0.0, 0.0, 0.0, 0.0]
nPhotons_vs_thick_down = [0.0, 0.0, 0.0, 0.0, 0.0]
enPhotons_vs_thick_down = [0.0, 0.0, 0.0, 0.0, 0.0]

nPhotons_vs_polish_up = [0.0, 0.0, 0.0, 0.0, 0.0]
enPhotons_vs_polish_up = [0.0, 0.0, 0.0, 0.0, 0.0]
nPhotons_vs_polish_down = [0.0, 0.0, 0.0, 0.0, 0.0]
enPhotons_vs_polish_down = [0.0, 0.0, 0.0, 0.0, 0.0]

risetime_vs_AR_up = [0.0, 0.0, 0.0, 0.0, 0.0]
erisetime_vs_AR_up = [0.0, 0.0, 0.0, 0.0, 0.0]
risetime_vs_AR_down = [0.0, 0.0, 0.0, 0.0, 0.0]
erisetime_vs_AR_down = [0.0, 0.0, 0.0, 0.0, 0.0]

risetime_vs_size_up = [0.0, 0.0, 0.0, 0.0, 0.0]
erisetime_vs_size_up = [0.0, 0.0, 0.0, 0.0, 0.0]
risetime_vs_size_down = [0.0, 0.0, 0.0, 0.0, 0.0]
erisetime_vs_size_down = [0.0, 0.0, 0.0, 0.0, 0.0]

risetime_vs_thick_up = [0.0, 0.0, 0.0, 0.0, 0.0]
erisetime_vs_thick_up = [0.0, 0.0, 0.0, 0.0, 0.0]
risetime_vs_thick_down = [0.0, 0.0, 0.0, 0.0, 0.0]
erisetime_vs_thick_down = [0.0, 0.0, 0.0, 0.0, 0.0]

risetime_vs_polish_up = [0.0, 0.0, 0.0, 0.0, 0.0]
erisetime_vs_polish_up = [0.0, 0.0, 0.0, 0.0, 0.0]
risetime_vs_polish_down = [0.0, 0.0, 0.0, 0.0, 0.0]
erisetime_vs_polish_down = [0.0, 0.0, 0.0, 0.0, 0.0]

deltaT_vs_AR_up = [0.0, 0.0, 0.0, 0.0, 0.0]
edeltaT_vs_AR_up = [0.0, 0.0, 0.0, 0.0, 0.0]
deltaT_vs_AR_down = [0.0, 0.0, 0.0, 0.0, 0.0]
edeltaT_vs_AR_down = [0.0, 0.0, 0.0, 0.0, 0.0]

deltaT_vs_size_up = [0.0, 0.0, 0.0, 0.0, 0.0]
edeltaT_vs_size_up = [0.0, 0.0, 0.0, 0.0, 0.0]
deltaT_vs_size_down = [0.0, 0.0, 0.0, 0.0, 0.0]
edeltaT_vs_size_down = [0.0, 0.0, 0.0, 0.0, 0.0]

deltaT_vs_thick_up = [0.0, 0.0, 0.0, 0.0, 0.0]
edeltaT_vs_thick_up = [0.0, 0.0, 0.0, 0.0, 0.0]
deltaT_vs_thick_down = [0.0, 0.0, 0.0, 0.0, 0.0]
edeltaT_vs_thick_down = [0.0, 0.0, 0.0, 0.0, 0.0]

deltaT_vs_polish_up = [0.0, 0.0, 0.0, 0.0, 0.0]
edeltaT_vs_polish_up = [0.0, 0.0, 0.0, 0.0, 0.0]
deltaT_vs_polish_down = [0.0, 0.0, 0.0, 0.0, 0.0]
edeltaT_vs_polish_down = [0.0, 0.0, 0.0, 0.0, 0.0]



one_var_vs_AR("AR", "aspect ratio", "amp_up", "amplitude [ns^{-1}]", AspectRatio, eAspectRatio, amp_vs_AR_up, eamp_vs_AR_up, True, 0.0, 1000.0)
two_var_vs_AR("AR", "aspect ratio", "amp", "amplitude [ns^{-1}]", AspectRatio, eAspectRatio, amp_vs_AR_up, eAspectRatio, amp_vs_AR_up, eamp_vs_AR_up, amp_vs_AR_down, eamp_vs_AR_down, "LYSO upstream", "LYSO downstream", True, 0.0, 1000.0)

#def one_var_vs_xVar(xVarName, xVarTitle, yVarName, yVarTitle, xVar1, exVar1, yVar1, eyVar1, logX, maximumY=-999.9, minimumY=-999.9):

#def two_var_vs_xVar(xVarName, xVarTitle, yVarName, yVarTitle, xVar1, exVar1, xVar2, exVar2, yVar1, eyVar1, yVar2, eyVar2, legend1, legend2, logX, maximumY=-999.9, minimumY=-999.9):
