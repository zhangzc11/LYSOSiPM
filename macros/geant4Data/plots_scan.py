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
outputDir = "/eos/user/z/zhicaiz/www/sharebox/TestBeam/geant4/forDN/scan/"

os.system("mkdir -p "+outputDir)

def two_var_vs_xVar(xVarName, xVarTitle, yVarName, yVarTitle, xVar1, exVar1, xVar2, exVar2, yVar1, eyVar1, yVar2, eyVar2, legend1, legend2, logX, maximumY=-999.9, minimumY=-999.9, maximumX = 1.0, minimumX = 0.0):
	
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

	gr1 = ROOT.TGraphErrors(len(xVar1), np.array(xVar1), np.array(yVar1), np.array(exVar1), np.array(eyVar1))
	gr2 = ROOT.TGraphErrors(len(xVar2), np.array(xVar2), np.array(yVar2), np.array(exVar2), np.array(eyVar2))
	
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
	mg_vs_xVar.GetHistogram().GetXaxis().SetRangeUser(minimumX, maximumX)
	if logX == 1:
		mg_vs_xVar.GetHistogram().GetXaxis().SetMoreLogLabels()

	ROOT.gPad.Modified()
	ROOT.gPad.Update()

	leg_vs_xVar = ROOT.TLegend(0.4,0.68,0.92,0.89)
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

def one_var_vs_xVar(xVarName, xVarTitle, yVarName, yVarTitle, xVar1, exVar1, yVar1, eyVar1, logX, maximumY=-999.9, minimumY=-999.9, maximumX=1.0, minimumX = 0.0):
	
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

	gr1 = ROOT.TGraphErrors(len(xVar1), np.array(xVar1), np.array(yVar1), np.array(exVar1), np.array(eyVar1))
	
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
	#gr1.GetHistogram().GetYaxis().SetRangeUser(minY, maxY)
	gr1.GetHistogram().GetXaxis().SetRangeUser(minimumX, maximumX)
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

LYSOthick = [2.5, 3.0, 3.5, 4.0, 4.5]
eLYSOthick = [0.0, 0.0, 0.0, 0.0, 0.0]

LYSOpolish = [20.0, 40.0, 60.0, 80.0, 90]
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


file_table = open("table.txt","r")

line_table = file_table.readlines()

for line in line_table:
	#print line
	line_array = shlex.split(line)
	if "_size" in line_array[0]:
		if "_md" in line_array[0]:
			idx_size = line_array[0].find("_size")+4
			idx_md = line_array[0].find("_md")
			size_this = line_array[0][idx_size+1:idx_md]
			index_size_array = 0
			for index_size in range(0,len(LYSOsize)):
				if float(size_this) == float(LYSOsize[index_size]):
					index_size_array = index_size
			amp_vs_AR_down[index_size_array] = float(line_array[5])
			eamp_vs_AR_down[index_size_array] = float(line_array[6])
			nPhotons_vs_AR_down[index_size_array] = float(line_array[1])
			enPhotons_vs_AR_down[index_size_array] = float(line_array[2])
			risetime_vs_AR_down[index_size_array] = float(line_array[9])
			erisetime_vs_AR_down[index_size_array] = float(line_array[10])
			deltaT_vs_AR_down[index_size_array] = float(line_array[13])
			
		else:
			idx_size = line_array[0].find("_size")+4
			size_this =  line_array[0][idx_size+1:]
			index_size_array = 0
			for index_size in range(0,len(LYSOsize)):
				if float(size_this) == float(LYSOsize[index_size]):
					index_size_array = index_size

			amp_vs_AR_up[index_size_array] = float(line_array[5])
			eamp_vs_AR_up[index_size_array] = float(line_array[6])
			nPhotons_vs_AR_up[index_size_array] = float(line_array[1])
			enPhotons_vs_AR_up[index_size_array] = float(line_array[2])
			risetime_vs_AR_up[index_size_array] = float(line_array[9])
			erisetime_vs_AR_up[index_size_array] = float(line_array[10])
			deltaT_vs_AR_up[index_size_array] = float(line_array[13])


	if "_thick" in line_array[0]:
		if "_md" in line_array[0]:
			idx_thick = line_array[0].find("_thick")+5
			idx_md = line_array[0].find("_md")
			thick_this = line_array[0][idx_thick+1:idx_md]
			index_thick_array = 0
			for index_thick in range(0,len(LYSOthick)):
				if float(thick_this) == float(LYSOthick[index_thick]):
					index_thick_array = index_thick
			amp_vs_thick_down[index_thick_array] = float(line_array[5])
			eamp_vs_thick_down[index_thick_array] = float(line_array[6])
			nPhotons_vs_thick_down[index_thick_array] = float(line_array[1])
			enPhotons_vs_thick_down[index_thick_array] = float(line_array[2])
			risetime_vs_thick_down[index_thick_array] = float(line_array[9])
			erisetime_vs_thick_down[index_thick_array] = float(line_array[10])
			deltaT_vs_thick_down[index_thick_array] = float(line_array[13])
			
		else:
			idx_thick = line_array[0].find("_thick")+5
			thick_this =  line_array[0][idx_thick+1:]
			index_thick_array = 0
			for index_thick in range(0,len(LYSOthick)):
				if float(thick_this) == float(LYSOthick[index_thick]):
					index_thick_array = index_thick

			amp_vs_thick_up[index_thick_array] = float(line_array[5])
			eamp_vs_thick_up[index_thick_array] = float(line_array[6])
			nPhotons_vs_thick_up[index_thick_array] = float(line_array[1])
			enPhotons_vs_thick_up[index_thick_array] = float(line_array[2])
			risetime_vs_thick_up[index_thick_array] = float(line_array[9])
			erisetime_vs_thick_up[index_thick_array] = float(line_array[10])
			deltaT_vs_thick_up[index_thick_array] = float(line_array[13])
			

	if "_polish" in line_array[0]:
		if "_md" in line_array[0]:
			idx_polish = line_array[0].find("_polish")+6
			idx_md = line_array[0].find("_md")
			polish_this = line_array[0][idx_polish+1:idx_md]
			index_polish_array = 0
			for index_polish in range(0,len(LYSOpolish)):
				if float(polish_this) == float(LYSOpolish[index_polish]):
					index_polish_array = index_polish
			amp_vs_polish_down[index_polish_array] = float(line_array[5])
			eamp_vs_polish_down[index_polish_array] = float(line_array[6])
			nPhotons_vs_polish_down[index_polish_array] = float(line_array[1])
			enPhotons_vs_polish_down[index_polish_array] = float(line_array[2])
			risetime_vs_polish_down[index_polish_array] = float(line_array[9])
			erisetime_vs_polish_down[index_polish_array] = float(line_array[10])
			deltaT_vs_polish_down[index_polish_array] = float(line_array[13])
			
		else:
			idx_polish = line_array[0].find("_polish")+6
			polish_this =  line_array[0][idx_polish+1:]
			index_polish_array = 0
			for index_polish in range(0,len(LYSOpolish)):
				if float(polish_this) == float(LYSOpolish[index_polish]):
					index_polish_array = index_polish

			amp_vs_polish_up[index_polish_array] = float(line_array[5])
			eamp_vs_polish_up[index_polish_array] = float(line_array[6])
			nPhotons_vs_polish_up[index_polish_array] = float(line_array[1])
			enPhotons_vs_polish_up[index_polish_array] = float(line_array[2])
			risetime_vs_polish_up[index_polish_array] = float(line_array[9])
			erisetime_vs_polish_up[index_polish_array] = float(line_array[10])
			deltaT_vs_polish_up[index_polish_array] = float(line_array[13])
			
		
print amp_vs_AR_up	
print eamp_vs_AR_up	
print nPhotons_vs_AR_up	
print enPhotons_vs_AR_up	
print risetime_vs_AR_up	
print erisetime_vs_AR_up	
print deltaT_vs_AR_up	
print edeltaT_vs_AR_up	
		
print amp_vs_AR_down	
print eamp_vs_AR_down	
print nPhotons_vs_AR_down	
print enPhotons_vs_AR_down	
print risetime_vs_AR_down	
print erisetime_vs_AR_down	
print deltaT_vs_AR_down	
print edeltaT_vs_AR_down	

		
print amp_vs_thick_up	
print eamp_vs_thick_up	
print nPhotons_vs_thick_up	
print enPhotons_vs_thick_up	
print risetime_vs_thick_up	
print erisetime_vs_thick_up	
print deltaT_vs_thick_up	
print edeltaT_vs_thick_up	
		
print amp_vs_thick_down	
print eamp_vs_thick_down	
print nPhotons_vs_thick_down	
print enPhotons_vs_thick_down	
print risetime_vs_thick_down	
print erisetime_vs_thick_down	
print deltaT_vs_thick_down	
print edeltaT_vs_thick_down	


print amp_vs_polish_up	
print eamp_vs_polish_up	
print nPhotons_vs_polish_up	
print enPhotons_vs_polish_up	
print risetime_vs_polish_up	
print erisetime_vs_polish_up	
print deltaT_vs_polish_up	
print edeltaT_vs_polish_up	
		
print amp_vs_polish_down	
print eamp_vs_polish_down	
print nPhotons_vs_polish_down	
print enPhotons_vs_polish_down	
print risetime_vs_polish_down	
print erisetime_vs_polish_down	
print deltaT_vs_polish_down	
print edeltaT_vs_polish_down	



one_var_vs_xVar("AR", "aspect ratio", "amp_up", "amplitude [ns^{-1}]", AspectRatio, eAspectRatio, amp_vs_AR_up, eamp_vs_AR_up, True, 1000.0, 0.0, 1.0, 0.1)
two_var_vs_xVar("AR", "aspect ratio", "amp", "amplitude [ns^{-1}]", AspectRatio, eAspectRatio, AspectRatio, eAspectRatio, amp_vs_AR_up, eamp_vs_AR_up, amp_vs_AR_down, eamp_vs_AR_down, "LYSO upstream", "LYSO downstream", True, 350.0, 180.0, 1.0, 0.1)

one_var_vs_xVar("AR", "aspect ratio", "nPhotons_up", "N.P.E.", AspectRatio, eAspectRatio, nPhotons_vs_AR_up, enPhotons_vs_AR_up, True, 10000.0, 0.0, 1.0, 0.1)
two_var_vs_xVar("AR", "aspect ratio", "nPhotons", "N.P.E.", AspectRatio, eAspectRatio, AspectRatio, eAspectRatio, nPhotons_vs_AR_up, enPhotons_vs_AR_up, nPhotons_vs_AR_down, enPhotons_vs_AR_down, "LYSO upstream", "LYSO downstream", True, 10000.0, 4000.0, 1.0, 0.1)

one_var_vs_xVar("AR", "aspect ratio", "deltaT_up", "time offset [ps]", AspectRatio, eAspectRatio, deltaT_vs_AR_up, edeltaT_vs_AR_up, True, 1000.0, 0.0, 1.0, 0.1)
two_var_vs_xVar("AR", "aspect ratio", "deltaT", "time offset [ps]", AspectRatio, eAspectRatio, AspectRatio, eAspectRatio, deltaT_vs_AR_up, edeltaT_vs_AR_up, deltaT_vs_AR_down, edeltaT_vs_AR_down, "LYSO upstream", "LYSO downstream", True, 200.0, 0.0, 1.0, 0.1)

one_var_vs_xVar("AR", "aspect ratio", "risetime_up", "risetime [ns]", AspectRatio, eAspectRatio, risetime_vs_AR_up, erisetime_vs_AR_up, True, 3.0, 0.0, 1.0, 0.1)
two_var_vs_xVar("AR", "aspect ratio", "risetime", "risetime [ns]", AspectRatio, eAspectRatio, AspectRatio, eAspectRatio, risetime_vs_AR_up, erisetime_vs_AR_up, risetime_vs_AR_down, erisetime_vs_AR_down, "LYSO upstream", "LYSO downstream", True, 3.0, 0.0, 1.0, 0.1)


one_var_vs_xVar("thick", "LYSO thickness [mm]", "amp_up", "amplitude [ns^{-1}]", LYSOthick, eLYSOthick, amp_vs_thick_up, eamp_vs_thick_up, False, 1000.0, 0.0, 5.0, 2.0)
two_var_vs_xVar("thick", "LYSO thickness [mm]", "amp", "amplitude [ns^{-1}]", LYSOthick, eLYSOthick, LYSOthick, eLYSOthick, amp_vs_thick_up, eamp_vs_thick_up, amp_vs_thick_down, eamp_vs_thick_down, "LYSO upstream", "LYSO downstream", False, 350.0, 180.0, 5.0, 2.0)

one_var_vs_xVar("thick", "LYSO thickness [mm]", "nPhotons_up", "N.P.E.", LYSOthick, eLYSOthick, nPhotons_vs_thick_up, enPhotons_vs_thick_up, False, 10000.0, 0.0, 5.0, 2.0)
two_var_vs_xVar("thick", "LYSO thickness [mm]", "nPhotons", "N.P.E.", LYSOthick, eLYSOthick, LYSOthick, eLYSOthick, nPhotons_vs_thick_up, enPhotons_vs_thick_up, nPhotons_vs_thick_down, enPhotons_vs_thick_down, "LYSO upstream", "LYSO downstream", False, 10000.0, 4000.0, 5.0, 2.0)

one_var_vs_xVar("thick", "LYSO thickness [mm]", "deltaT_up", "time offset [ps]", LYSOthick, eLYSOthick, deltaT_vs_thick_up, edeltaT_vs_thick_up, False, 1000.0, 0.0, 5.0, 2.0)
two_var_vs_xVar("thick", "LYSO thickness [mm]", "deltaT", "time offset [ps]", LYSOthick, eLYSOthick, LYSOthick, eLYSOthick, deltaT_vs_thick_up, edeltaT_vs_thick_up, deltaT_vs_thick_down, edeltaT_vs_thick_down, "LYSO upstream", "LYSO downstream", False, 150.0, 0.0, 5.0, 2.0)


one_var_vs_xVar("thick", "LYSO thickness [mm]", "risetime_up", "risetime [ns]", LYSOthick, eLYSOthick, risetime_vs_thick_up, erisetime_vs_thick_up, False, 3.0, 0.0, 5.0, 2.0)
two_var_vs_xVar("thick", "LYSO thickness [mm]", "risetime", "risetime [ns]", LYSOthick, eLYSOthick, LYSOthick, eLYSOthick, risetime_vs_thick_up, erisetime_vs_thick_up, risetime_vs_thick_down, erisetime_vs_thick_down, "LYSO upstream", "LYSO downstream", False, 3.0, 0.0, 5.0, 2.0)


one_var_vs_xVar("polish", "LYSO polish r", "amp_up", "amplitude [ns^{-1}]", LYSOpolish, eLYSOpolish, amp_vs_polish_up, eamp_vs_polish_up, False, 1000.0, 0.0, 100.0, 0.0)
two_var_vs_xVar("polish", "LYSO polish r", "amp", "amplitude [ns^{-1}]", LYSOpolish, eLYSOpolish, LYSOpolish, eLYSOpolish, amp_vs_polish_up, eamp_vs_polish_up, amp_vs_polish_down, eamp_vs_polish_down, "LYSO upstream", "LYSO downstream", False, 250.0, 150.0, 100.0, 0.0)

one_var_vs_xVar("polish", "LYSO polish r", "nPhotons_up", "N.P.E.", LYSOpolish, eLYSOpolish, nPhotons_vs_polish_up, enPhotons_vs_polish_up, False, 10000.0, 0.0, 100.0, 0.0)
two_var_vs_xVar("polish", "LYSO polish r", "nPhotons", "N.P.E.", LYSOpolish, eLYSOpolish, LYSOpolish, eLYSOpolish, nPhotons_vs_polish_up, enPhotons_vs_polish_up, nPhotons_vs_polish_down, enPhotons_vs_polish_down, "LYSO upstream", "LYSO downstream", False, 6000.0, 3000.0, 100.0, 0.0)

one_var_vs_xVar("polish", "LYSO polish r", "deltaT_up", "time offset [ps]", LYSOpolish, eLYSOpolish, deltaT_vs_polish_up, edeltaT_vs_polish_up, False, 1000.0, 0.0, 100.0, 0.0)
two_var_vs_xVar("polish", "LYSO polish r", "deltaT", "time offset [ps]", LYSOpolish, eLYSOpolish, LYSOpolish, eLYSOpolish, deltaT_vs_polish_up, edeltaT_vs_polish_up, deltaT_vs_polish_down, edeltaT_vs_polish_down, "LYSO upstream", "LYSO downstream", False, 300.0, 0.0, 100.0, 0.0)

one_var_vs_xVar("polish", "LYSO polish r", "risetime_up", "risetime [ns]", LYSOpolish, eLYSOpolish, risetime_vs_polish_up, erisetime_vs_polish_up, False, 3.0, 0.0, 100.0, 0.0)
two_var_vs_xVar("polish", "LYSO polish r", "risetime", "risetime [ns]", LYSOpolish, eLYSOpolish, LYSOpolish, eLYSOpolish, risetime_vs_polish_up, erisetime_vs_polish_up, risetime_vs_polish_down, erisetime_vs_polish_down, "LYSO upstream", "LYSO downstream", False, 1.0, 0.0, 100.0, 0.0)


