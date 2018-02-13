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
#run = "combine_1250_1255_charge_vs_bias"
#run = "combine_1256_1259_charge_vs_bias"

#run = "combine_1278_1279_pureSiPM"
#run = "combine_1280_1282_SiPM_LYSO"
run = "combine_1283_1286_SiPM_LYSO_Source"

#run = "1265"

isPMT = False

amp_fac = 25.24 #36dB, and 0.5 instead of 0.2ns per bin
charge_low = 0.2
charge_low2 = 0.0
charge_high = 1.5
charge_high2 = 5.0

if isPMT:
	amp_fac = 0.1264
	charge_low = 0.0
	charge_low2 = 0.0
	charge_high = 800.0
	charge_high2 = 1000.0

inputDir = "~/LabData/Zhicai_Spring2018/data/"
outputDir = "~/LabData/Zhicai_Spring2018/plots/"

os.system("mkdir -p "+outputDir)

cut = "ch2Amp>0.001"

########################################################

file=ROOT.TFile(inputDir+run+"_ana.root")
tree=file.Get("tree")

print tree.GetEntries()

bias_val = []
ebias_val = []
charge = []
echarge = []

bias_low = 66.5
bias_high = 72.5
nbins_bias = 6

if isPMT:
	bias_low = 1700.0
	bias_high = 2500.0
	nbins_bias = 4

#####scan over different positions

for ibias in range(0, nbins_bias):
        low_cut = bias_low + ibias*(bias_high-bias_low)/nbins_bias
        high_cut = bias_low + (ibias+1)*(bias_high-bias_low)/nbins_bias
        bias_this = bias_low + (ibias+0.5)*(bias_high-bias_low)/nbins_bias
        bias_val.append(bias_this)
        ebias_val.append(0.5*(bias_high-bias_low)/nbins_bias)

        cut_this = cut + " && V_bias > " + str(low_cut) + " && V_bias <  " + str(high_cut)

	NEntries = tree.GetEntries(cut_this)

	#print cut_this
	print "charge for bias  = "+str(bias_this)
	
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

	NBins = 100
	if isPMT:
		NBins = 400
	hist_charge = ROOT.TH1F("hist_charge_"+str(bias_this),"hist_charge_"+str(bias_this), NBins, charge_low2, charge_high2)
	tree.Draw("ch2Int/"+str(amp_fac)+">>hist_charge_"+str(bias_this),cut_this)	
	hist_charge.SetMarkerStyle( 20 )
	hist_charge.SetMarkerColor( ROOT.kBlack )
	hist_charge.GetXaxis().SetTitle("charge [pC]")
	hist_charge.GetYaxis().SetTitle("Events")
	hist_charge.SetTitle("")
	hist_charge.GetXaxis().SetTitleSize( axisTitleSizeX )
        hist_charge.GetXaxis().SetTitleOffset( axisTitleOffsetX )
        hist_charge.GetYaxis().SetTitleSize( axisTitleSizeY )
        hist_charge.GetYaxis().SetTitleOffset( axisTitleOffsetY )
	hist_charge.Draw("E")
	maximumY=hist_charge.GetMaximum()
	highcharge=hist_charge.GetBinCenter(hist_charge.FindLastBinAbove(int(0.4*maximumY)))
	lowcharge=hist_charge.GetBinCenter(hist_charge.FindFirstBinAbove(int(0.1*maximumY)))
	if isPMT:	
		highcharge=hist_charge.GetBinCenter(hist_charge.FindLastBinAbove(int(0.1*maximumY)))
		peakcharge=hist_charge.GetBinCenter(hist_charge.FindLastBinAbove(int(0.8*maximumY)))
		#peakcharge=hist_charge.GetBinCenter(hist_charge.GetMaximumBin())
        	lowcharge=peakcharge-1.2*(highcharge-peakcharge)#hist_charge.GetBinCenter(hist_charge.FindFirstBinAbove(int(0.6*maximumY)))
	tf1_gaus = ROOT.TF1("tf1_gaus","gaus", charge_low2, charge_high2)
	tf1_gaus.SetParameter(1, hist_charge.GetMean())
	hist_charge.Fit("tf1_gaus","","",lowcharge, highcharge)
	myC.SaveAs(outputDir+run+"_charge_bias"+str(bias_this)+"V.pdf")
	mean_charge = tf1_gaus.GetParameter(1)
	emean_charge = tf1_gaus.GetParError(1)
	sigma_charge = tf1_gaus.GetParameter(2)
	esigma_charge = tf1_gaus.GetParError(2)

	charge.append(mean_charge)
	echarge.append(emean_charge)


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

gr_charge_vs_bias = ROOT.TGraphErrors(nbins_bias, np.array(bias_val), np.array(charge), np.array(ebias_val), np.array(echarge))
gr_charge_vs_bias.SetMarkerStyle( 20 )
gr_charge_vs_bias.SetMarkerColor( ROOT.kBlack )
gr_charge_vs_bias.SetLineWidth( 2 )
gr_charge_vs_bias.SetLineColor( ROOT.kBlack ) 
gr_charge_vs_bias.GetXaxis().SetTitle("supply voltage [V]")
gr_charge_vs_bias.GetYaxis().SetTitle("charge [pC]")
gr_charge_vs_bias.SetTitle("")
gr_charge_vs_bias.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_charge_vs_bias.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_charge_vs_bias.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_charge_vs_bias.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_charge_vs_bias.GetYaxis().SetRangeUser(charge_low,charge_high)
gr_charge_vs_bias.Draw("AP")
myC.SaveAs(outputDir+run+"_charge_vs_bias.pdf")
myC.SaveAs(outputDir+run+"_charge_vs_bias.png")
myC.SaveAs(outputDir+run+"_charge_vs_bias.C")


