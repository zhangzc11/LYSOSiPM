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
outputDir = "/afs/cern.ch/user/z/zhicaiz/www/sharebox/TestBeam/FNAL_June2018_v5_final/aspectratio/"

os.system("mkdir -p "+outputDir)


########################################################


AR_3x3mm = [0.053, 0.063, 0.074, 0.113, 0.141, 0.360, 0.563]
eAR_3x3mm = [0.0,0.0,0.0,0.0,0.0,0.0,0.0]
ezeros_3x3mm = [0.0,0.0,0.0,0.0,0.0,0.0,0.0]

AR_6x6mm = [0.213, 0.563, 2.25]
eAR_6x6mm = [0.0,0.0,0.0]
ezeros_6x6mm = [0.0,0.0,0.0]

def var_vs_AR(varName, varTitle, var1, var2, evar1, evar2, legend1, legend2, logX, maximumY=-999.9, minimumY=-999.9):
	
	var1 = 	[float(i) for i in var1]
	var2 = 	[float(i) for i in var2]

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

	gr1 = ROOT.TGraphErrors(7, np.array(AR_3x3mm), np.array(var1), np.array(eAR_3x3mm), np.array(evar1))
	gr2 = ROOT.TGraphErrors(3, np.array(AR_6x6mm), np.array(var2), np.array(eAR_6x6mm), np.array(evar2))
	
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

	mg_vs_AR = ROOT.TMultiGraph()

	mg_vs_AR.Add(gr1)
	mg_vs_AR.Add(gr2)
	mg_vs_AR.Draw("ALPE")

	mg_vs_AR.GetHistogram().GetXaxis().SetTitle("aspect ratio")
	mg_vs_AR.GetHistogram().GetYaxis().SetTitle(varTitle)
	mg_vs_AR.GetHistogram().SetTitle("")
	mg_vs_AR.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
	mg_vs_AR.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
	mg_vs_AR.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
	mg_vs_AR.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
	#mg_vs_AR.GetXaxis().SetLimits(0.01,1.5)
	mg_vs_AR.GetHistogram().GetYaxis().SetRangeUser(minY, maxY)
	if logX == 1:
		mg_vs_AR.GetHistogram().GetXaxis().SetMoreLogLabels()

	ROOT.gPad.Modified()
	ROOT.gPad.Update()

	leg_vs_AR = ROOT.TLegend(0.66,0.68,0.92,0.89)
	leg_vs_AR.SetBorderSize(0)
	leg_vs_AR.SetNColumns(1)
	leg_vs_AR.SetTextSize(0.045)
	leg_vs_AR.SetLineColor(1)
	leg_vs_AR.SetLineStyle(1)
	leg_vs_AR.SetLineWidth(1)
	leg_vs_AR.SetFillColor(0)
	leg_vs_AR.SetFillStyle(1001)

	leg_vs_AR.AddEntry(gr1, legend1, "pe");
	leg_vs_AR.AddEntry(gr2, legend2, "pe");

	leg_vs_AR.Draw()
	myC.SaveAs(outputDir+varName+"_vs_AR_upstream.pdf")
	myC.SaveAs(outputDir+varName+"_vs_AR_upstream.png")
	myC.SaveAs(outputDir+varName+"_vs_AR_upstream.C")


timereso_local_best_3x3mm = [51.0,53.0,46.0,53.0,41.0,38.0,35.0]
timereso_local_best_3x3mm_subtract14 = [np.sqrt(a*a-14.0*14.0) for a in timereso_local_best_3x3mm]
etimereso_local_best_3x3mm = [1.0,1.0,4.0,1.0,3.0,2.0,1.0]
etimereso_local_best_3x3mm_subtract14 = [a for a in etimereso_local_best_3x3mm]
timereso_local_best_6x6mm = [38.0,28.0,25.0]
timereso_local_best_6x6mm_subtract14 = [np.sqrt(a*a-14.0*14.0) for a in timereso_local_best_6x6mm]
etimereso_local_best_6x6mm = [1.0,3.0,2.0]
etimereso_local_best_6x6mm_subtract14 = [a for a in etimereso_local_best_6x6mm]

var_vs_AR("timereso_local_best", "time resolution [ps]", timereso_local_best_3x3mm, timereso_local_best_6x6mm, etimereso_local_best_3x3mm, etimereso_local_best_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",0,90.0,10.0)
var_vs_AR("timereso_local_best_logX", "time resolution [ps]", timereso_local_best_3x3mm, timereso_local_best_6x6mm, etimereso_local_best_3x3mm, etimereso_local_best_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",1,90.0,10.0)

var_vs_AR("timereso_local_best_subtract14", "time resolution [ps]", timereso_local_best_3x3mm_subtract14, timereso_local_best_6x6mm_subtract14, etimereso_local_best_3x3mm_subtract14, etimereso_local_best_6x6mm_subtract14, "3x3 mm SiPM", "6x6 mm SiPM",0,90.0,10.0)
var_vs_AR("timereso_local_best_subtract14_logX", "time resolution [ps]", timereso_local_best_3x3mm_subtract14, timereso_local_best_6x6mm_subtract14, etimereso_local_best_3x3mm_subtract14, etimereso_local_best_6x6mm_subtract14, "3x3 mm SiPM", "6x6 mm SiPM",1,90.0,10.0)



timereso_averageXY_3x3mm = [73.0,71.0,66.0,60.0,51.0,42.0,39.0]
timereso_averageXY_3x3mm_subtract14 = [np.sqrt(a*a-14.0*14.0) for a in timereso_averageXY_3x3mm]
etimereso_averageXY_3x3mm = [1.0,1.0,1.0,1.0,1.0,1.0,1.0]
etimereso_averageXY_3x3mm_subtract14 = [a for a in etimereso_averageXY_3x3mm]
timereso_averageXY_6x6mm = [50.0,36.0,28.0]
timereso_averageXY_6x6mm_subtract14 = [np.sqrt(a*a-14.0*14.0) for a in timereso_averageXY_6x6mm]
etimereso_averageXY_6x6mm = [1.0,1.0,1.0]
etimereso_averageXY_6x6mm_subtract14 = [a for a in etimereso_averageXY_6x6mm]

var_vs_AR("timereso_averageXY", "time resolution [ps]", timereso_averageXY_3x3mm, timereso_averageXY_6x6mm, etimereso_averageXY_3x3mm, etimereso_averageXY_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",0,90.0,10.0)
var_vs_AR("timereso_averageXY_logX", "time resolution [ps]", timereso_averageXY_3x3mm, timereso_averageXY_6x6mm, etimereso_averageXY_3x3mm, etimereso_averageXY_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",1,90.0,10.0)

var_vs_AR("timereso_averageXY_subtract14", "time resolution [ps]", timereso_averageXY_3x3mm_subtract14, timereso_averageXY_6x6mm_subtract14, etimereso_averageXY_3x3mm_subtract14, etimereso_averageXY_6x6mm_subtract14, "3x3 mm SiPM", "6x6 mm SiPM",0,90.0,10.0)
var_vs_AR("timereso_averageXY_subtract14_logX", "time resolution [ps]", timereso_averageXY_3x3mm_subtract14, timereso_averageXY_6x6mm_subtract14, etimereso_averageXY_3x3mm_subtract14, etimereso_averageXY_6x6mm_subtract14, "3x3 mm SiPM", "6x6 mm SiPM",1,90.0,10.0)



amplitude_local_best_landau_fit_3x3mm = [276.0,263.0,224.0,341.0,314.0,487.0,617.0]
eamplitude_local_best_landau_fit_3x3mm = [1.0,1.0,3.0,1.0,6.0,5.0,3.0]
amplitude_local_best_landau_fit_6x6mm = [640.0,840.0,766.0]
eamplitude_local_best_landau_fit_6x6mm = [3.0,25.0,30.0]

var_vs_AR("amplitude_local_best_landau_fit", "amplitude [mV]", amplitude_local_best_landau_fit_3x3mm, amplitude_local_best_landau_fit_6x6mm, eamplitude_local_best_landau_fit_3x3mm, eamplitude_local_best_landau_fit_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",0, 1500.0, 0.0)
var_vs_AR("amplitude_local_best_landau_fit_logX", "amplitude [mV]", amplitude_local_best_landau_fit_3x3mm, amplitude_local_best_landau_fit_6x6mm, eamplitude_local_best_landau_fit_3x3mm, eamplitude_local_best_landau_fit_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",1, 1500.0, 0.0)


amplitude_local_best_simple_average_3x3mm = [287.0,276.0,242.0,362.0,333.0,522.0,628.0]
eamplitude_local_best_simple_average_3x3mm = [1.0,1.0,2.0,1.0,3.0,4.0,3.0]
amplitude_local_best_simple_average_6x6mm = [632.0,804.0,762.0]
eamplitude_local_best_simple_average_6x6mm = [3.0,3.0,4.0]

var_vs_AR("amplitude_local_best_simple_average", "amplitude [mV]", amplitude_local_best_simple_average_3x3mm, amplitude_local_best_simple_average_6x6mm, eamplitude_local_best_simple_average_3x3mm, eamplitude_local_best_simple_average_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",0, 1500.0, 0.0)
var_vs_AR("amplitude_local_best_simple_average_logX", "amplitude [mV]", amplitude_local_best_simple_average_3x3mm, amplitude_local_best_simple_average_6x6mm, eamplitude_local_best_simple_average_3x3mm, eamplitude_local_best_simple_average_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",1, 1500.0, 0.0)


amplitude_whole_tile_landau_fit_3x3mm = [197.0,201.0,165.0,307.0,255.0,442.0,600.0]
eamplitude_whole_tile_landau_fit_3x3mm = [a for a in eamplitude_local_best_landau_fit_3x3mm]
amplitude_whole_tile_landau_fit_6x6mm = [300.0,750.0,744.0]
eamplitude_whole_tile_landau_fit_6x6mm = [a for a in eamplitude_local_best_landau_fit_6x6mm]

var_vs_AR("amplitude_whole_tile_landau_fit", "amplitude [mV]", amplitude_whole_tile_landau_fit_3x3mm, amplitude_whole_tile_landau_fit_6x6mm, eamplitude_whole_tile_landau_fit_3x3mm, eamplitude_whole_tile_landau_fit_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",0, 1500.0, 0.0)
var_vs_AR("amplitude_whole_tile_landau_fit_logX", "amplitude [mV]", amplitude_whole_tile_landau_fit_3x3mm, amplitude_whole_tile_landau_fit_6x6mm, eamplitude_whole_tile_landau_fit_3x3mm, eamplitude_whole_tile_landau_fit_6x6mm, "3x3 mm SiPM", "6x6 mm SiPM",1, 1500.0, 0.0)



