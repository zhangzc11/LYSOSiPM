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


def var_vs_sipmsize(varName, varTitle, var1, var2, evar1, evar2, legend1, legend2):
	
	var1 = 	[float(i) for i in var1]
	var2 = 	[float(i) for i in var2]

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

	gr1 = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(var1), np.array(esipmsize), np.array(evar1))
	gr2 = ROOT.TGraphErrors(4, np.array(sipmsize), np.array(var2), np.array(esipmsize), np.array(evar2))
	
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

	maxY = 1.4*maxY
	minY = 0.8*minY

	mg_vs_sipmsize = ROOT.TMultiGraph()

	mg_vs_sipmsize.Add(gr1)
	mg_vs_sipmsize.Add(gr2)

	mg_vs_sipmsize.Draw("AP")

	mg_vs_sipmsize.GetHistogram().GetXaxis().SetTitle("SiPM size [mm]")
	mg_vs_sipmsize.GetHistogram().GetYaxis().SetTitle(varTitle)
	mg_vs_sipmsize.GetHistogram().SetTitle("")
	mg_vs_sipmsize.GetHistogram().GetXaxis().SetTitleSize( axisTitleSizeX )
	mg_vs_sipmsize.GetHistogram().GetXaxis().SetTitleOffset( axisTitleOffsetX )
	mg_vs_sipmsize.GetHistogram().GetYaxis().SetTitleSize( axisTitleSizeY )
	mg_vs_sipmsize.GetHistogram().GetYaxis().SetTitleOffset( axisTitleOffsetY )
	mg_vs_sipmsize.GetHistogram().GetXaxis().SetRangeUser(2.0,11.0)
	mg_vs_sipmsize.GetHistogram().GetYaxis().SetRangeUser(minY, maxY)

	ROOT.gPad.Modified()
	ROOT.gPad.Update()

	leg_vs_sipmsize = ROOT.TLegend(0.3,0.65,0.9,0.85)
	leg_vs_sipmsize.SetBorderSize(0)
	leg_vs_sipmsize.SetNColumns(1)
	leg_vs_sipmsize.SetTextSize(0.04)
	leg_vs_sipmsize.SetLineColor(1)
	leg_vs_sipmsize.SetLineStyle(1)
	leg_vs_sipmsize.SetLineWidth(1)
	leg_vs_sipmsize.SetFillColor(0)
	leg_vs_sipmsize.SetFillStyle(1001)

	leg_vs_sipmsize.AddEntry(gr1, legend1, "p");
	leg_vs_sipmsize.AddEntry(gr2, legend2, "p");

	leg_vs_sipmsize.Draw()

	myC.SaveAs(outputDir+varName+"_vs_sipmsize.pdf")
	myC.SaveAs(outputDir+varName+"_vs_sipmsize.png")
	myC.SaveAs(outputDir+varName+"_vs_sipmsize.C")



ezeros = [0.0,0.0,0.0,0.0]

offset_3mm_up = []
offset_3mm_down = []
risetime_x0_3mm_up = []
risetime_x0_3mm_down = []
risetime_x5_3mm_up = []
risetime_x5_3mm_down = []
nPhotons_amp_x0_3mm_up = []
nPhotons_amp_x0_3mm_down = []
nPhotons_amp_x5_3mm_up = []
nPhotons_amp_x5_3mm_down = []
nPhotons_x0_3mm_up = []
nPhotons_x0_3mm_down = []
nPhotons_x5_3mm_up = []
nPhotons_x5_3mm_down = []
nPhotons_peak_x0_3mm_up = []
nPhotons_peak_x0_3mm_down = []
nPhotons_peak_x5_3mm_up = []
nPhotons_peak_x5_3mm_down = []
nPhotons_firstbin_x0_3mm_up = []
nPhotons_firstbin_x0_3mm_down = []
nPhotons_firstbin_x5_3mm_up = []
nPhotons_firstbin_x5_3mm_down = []

offset_4mm_up = []
offset_4mm_down = []
risetime_x0_4mm_up = []
risetime_x0_4mm_down = []
risetime_x5_4mm_up = []
risetime_x5_4mm_down = []
nPhotons_amp_x0_4mm_up = []
nPhotons_amp_x0_4mm_down = []
nPhotons_amp_x5_4mm_up = []
nPhotons_amp_x5_4mm_down = []
nPhotons_x0_4mm_up = []
nPhotons_x0_4mm_down = []
nPhotons_x5_4mm_up = []
nPhotons_x5_4mm_down = []
nPhotons_peak_x0_4mm_up = []
nPhotons_peak_x0_4mm_down = []
nPhotons_peak_x5_4mm_up = []
nPhotons_peak_x5_4mm_down = []
nPhotons_firstbin_x0_4mm_up = []
nPhotons_firstbin_x0_4mm_down = []
nPhotons_firstbin_x5_4mm_up = []
nPhotons_firstbin_x5_4mm_down = []

table_filename="table.txt"
#cout<<"totTable_"<<inFileName<<" "<<deltaT_x05<<" "<<risetime_x0<<" "<<risetime_x5<<" "<<nPhotons_amp_x0<<" "<<nPhotons_amp_x5<<" "<<nPhotons_x0<<" "<<nPhotons_x5<<" "<<nPhotons_peak_x0<<" "<<nPhotons_peak_x5<<" "<<nPhotons_firstbin_x0<<" "<<nPhotons_firstbin_x5<<endl

with open(table_filename,"r") as list_file:
	for this_line in list_file:
		line_array = shlex.split(this_line)
		if line_array[0]=="3":
			if line_array[2]=="0":
				#3mm, upstream
				offset_3mm_up.append(line_array[3])
				risetime_x0_3mm_up.append(line_array[4])
				risetime_x5_3mm_up.append(line_array[5])
				nPhotons_amp_x0_3mm_up.append(line_array[6])
				nPhotons_amp_x5_3mm_up.append(line_array[7])
				nPhotons_x0_3mm_up.append(line_array[8])
				nPhotons_x5_3mm_up.append(line_array[9])
				nPhotons_peak_x0_3mm_up.append(line_array[10])
				nPhotons_peak_x5_3mm_up.append(line_array[11])
				nPhotons_firstbin_x0_3mm_up.append(line_array[12])
				nPhotons_firstbin_x5_3mm_up.append(line_array[13])
			if line_array[2]=="1":
				#3mm, downstream
				offset_3mm_down.append(line_array[3])
				risetime_x0_3mm_down.append(line_array[4])
				risetime_x5_3mm_down.append(line_array[5])
				nPhotons_amp_x0_3mm_down.append(line_array[6])
				nPhotons_amp_x5_3mm_down.append(line_array[7])
				nPhotons_x0_3mm_down.append(line_array[8])
				nPhotons_x5_3mm_down.append(line_array[9])
				nPhotons_peak_x0_3mm_down.append(line_array[10])
				nPhotons_peak_x5_3mm_down.append(line_array[11])
				nPhotons_firstbin_x0_3mm_down.append(line_array[12])
				nPhotons_firstbin_x5_3mm_down.append(line_array[13])
		if line_array[0]=="4":
			if line_array[2]=="0":
				#4mm, upstream
				offset_4mm_up.append(line_array[3])
				risetime_x0_4mm_up.append(line_array[4])
				risetime_x5_4mm_up.append(line_array[5])
				nPhotons_amp_x0_4mm_up.append(line_array[6])
				nPhotons_amp_x5_4mm_up.append(line_array[7])
				nPhotons_x0_4mm_up.append(line_array[8])
				nPhotons_x5_4mm_up.append(line_array[9])
				nPhotons_peak_x0_4mm_up.append(line_array[10])
				nPhotons_peak_x5_4mm_up.append(line_array[11])
				nPhotons_firstbin_x0_4mm_up.append(line_array[12])
				nPhotons_firstbin_x5_4mm_up.append(line_array[13])
			if line_array[2]=="1":
				#4mm, downstream
				offset_4mm_down.append(line_array[3])
				risetime_x0_4mm_down.append(line_array[4])
				risetime_x5_4mm_down.append(line_array[5])
				nPhotons_amp_x0_4mm_down.append(line_array[6])
				nPhotons_amp_x5_4mm_down.append(line_array[7])
				nPhotons_x0_4mm_down.append(line_array[8])
				nPhotons_x5_4mm_down.append(line_array[9])
				nPhotons_peak_x0_4mm_down.append(line_array[10])
				nPhotons_peak_x5_4mm_down.append(line_array[11])
				nPhotons_firstbin_x0_4mm_down.append(line_array[12])
				nPhotons_firstbin_x5_4mm_down.append(line_array[13])


#print offset_3mm_up
#print offset_3mm_down

var_vs_sipmsize("timeoffset_LYSO4mm", "time offset [ns]", offset_4mm_up, offset_4mm_down, ezeros, ezeros, "LYSO (4mm) upstream", "LYSO (4mm) downstream")
var_vs_sipmsize("timeoffset_downstream", "time offset [ns]", offset_3mm_up, offset_4mm_up, ezeros, ezeros, "LYSO (3mm) upstream", "LYSO (4mm) upstream")

var_vs_sipmsize("risetime_x0_LYSO4mm", "risetime [ns]", risetime_x0_4mm_up, risetime_x0_4mm_down, ezeros, ezeros, "LYSO (4mm) upstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("risetime_x0_downstream", "risetime [ns]", risetime_x0_3mm_down, risetime_x0_4mm_down, ezeros, ezeros, "LYSO (3mm) downstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("risetime_LYSO4mm_downstream", "risetime [ns]", risetime_x0_4mm_down, risetime_x5_4mm_down, ezeros, ezeros, "LYSO (4mm) downstream - center", "LYSO (4mm) downstream - edge")

var_vs_sipmsize("nPhotons_amp_x0_LYSO4mm", "Amplitude [#gamma/ns]", nPhotons_amp_x0_4mm_up, nPhotons_amp_x0_4mm_down, ezeros, ezeros, "LYSO (4mm) upstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("nPhotons_amp_x0_downstream", "Amplitude [#gamma/ns]", nPhotons_amp_x0_3mm_down, nPhotons_amp_x0_4mm_down, ezeros, ezeros, "LYSO (3mm) downstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("nPhotons_amp_LYSO4mm_downstream", "Amplitude [#gamma/ns]", nPhotons_amp_x0_4mm_down, nPhotons_amp_x5_4mm_down, ezeros, ezeros, "LYSO (4mm) downstream - center", "LYSO (4mm) downstream - edge")


var_vs_sipmsize("nPhotons_x0_LYSO4mm", "charge full", nPhotons_x0_4mm_up, nPhotons_x0_4mm_down, ezeros, ezeros, "LYSO (4mm) upstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("nPhotons_x0_downstream", "charge full", nPhotons_x0_3mm_down, nPhotons_x0_4mm_down, ezeros, ezeros, "LYSO (3mm) downstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("nPhotons_LYSO4mm_downstream", "charge full", nPhotons_x0_4mm_down, nPhotons_x5_4mm_down, ezeros, ezeros, "LYSO (4mm) downstream - center", "LYSO (4mm) downstream - edge")


var_vs_sipmsize("nPhotons_peak_x0_LYSO4mm", "charge until peak", nPhotons_peak_x0_4mm_up, nPhotons_peak_x0_4mm_down, ezeros, ezeros, "LYSO (4mm) upstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("nPhotons_peak_x0_downstream", "charge until peak", nPhotons_peak_x0_3mm_down, nPhotons_peak_x0_4mm_down, ezeros, ezeros, "LYSO (3mm) downstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("nPhotons_peak_LYSO4mm_downstream", "charge until peak", nPhotons_peak_x0_4mm_down, nPhotons_peak_x5_4mm_down, ezeros, ezeros, "LYSO (4mm) downstream - center", "LYSO (4mm) downstream - edge")

var_vs_sipmsize("nPhotons_firstbin_x0_LYSO4mm", "charge first bin", nPhotons_firstbin_x0_4mm_up, nPhotons_firstbin_x0_4mm_down, ezeros, ezeros, "LYSO (4mm) upstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("nPhotons_firstbin_x0_downstream", "charge first bin", nPhotons_firstbin_x0_3mm_down, nPhotons_firstbin_x0_4mm_down, ezeros, ezeros, "LYSO (3mm) downstream - center", "LYSO (4mm) downstream - center")
var_vs_sipmsize("nPhotons_firstbin_LYSO4mm_downstream", "charge first bin", nPhotons_firstbin_x0_4mm_down, nPhotons_firstbin_x5_4mm_down, ezeros, ezeros, "LYSO (4mm) downstream - center", "LYSO (4mm) downstream - edge")










