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
#run = "combine_1060_1079_407nm"
run = "combine_1080_1100_373nm"
isUVlaser = True

inputDir = "~/LabData/Zhicai_Spring2018/data/"
outputDir = "~/LabData/Zhicai_Spring2018/plots/"

os.system("mkdir -p "+outputDir)

cut = "ch1Amp>0.2 && ch1Amp<0.35 && ch2Amp > 0.002 && t1gausroot>0"# &&  ch2LinearTime60 - t1gausroot<44 && ch2LinearTime60 - t1gausroot>41"


deltaT_mean = 42.7 #for 407nm laser
RiseTime_mean = 0.67 # for 407nm laser
max_amp = 0.50 # for 407nm laser
max_timeReso = 0.08 # for 407nm laser

if isUVlaser:
	cut = "ch1Amp>0.2 && ch1Amp<0.35 && ch2Amp > 0.002 && t1gausroot>0"# &&  ch2LinearTime60 - t1gausroot<44 && ch2LinearTime60 - t1gausroot>41"
	deltaT_mean = 41.75 #for 373nm laser
	RiseTime_mean = 0.7 # for 407nm laser
	max_amp = 0.30 # for 373nm laser
	max_timeReso = 0.10 # for 373nm laser

bias_low = 62.75
bias_high = 72.75
nbins_bias = 20
########################################################

file=ROOT.TFile(inputDir+run+"_ana.root")
tree=file.Get("tree")

print tree.GetEntries()

bias_val = []
timeReso = []
deltaT = []
ch2Amp = []
ch2Risetime = []
ch2IntRatio = []

ebias_val = []
etimeReso = []
edeltaT = []
ech2Amp = []
ech2Risetime = []
ech2IntRatio = []

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
	print "timing resolution for bias = "+str(bias_this)
	
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

	N_deltaT = 1200
	if NEntries < 5000:
		N_deltaT = 500
	if NEntries < 2000:
		N_deltaT = 200
	if NEntries < 1000:
		N_deltaT = 100
	if NEntries < 800:
		N_deltaT = 50

	hist_deltaT = ROOT.TH1F("hist_deltaT_"+str(bias_this),"hist_deltaT_"+str(bias_this),N_deltaT,deltaT_mean-2.0,deltaT_mean+2.0)
	tree.Draw("ch2LinearTime60-t1gausroot>>hist_deltaT_"+str(bias_this),cut_this)	
	hist_deltaT.SetMarkerStyle( 20 )
	hist_deltaT.SetMarkerColor( ROOT.kBlack )
	hist_deltaT.GetXaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
	hist_deltaT.GetYaxis().SetTitle("Events")
	hist_deltaT.SetTitle("")
	hist_deltaT.GetXaxis().SetTitleSize( axisTitleSizeX )
        hist_deltaT.GetXaxis().SetTitleOffset( axisTitleOffsetX )
        hist_deltaT.GetYaxis().SetTitleSize( axisTitleSizeY )
        hist_deltaT.GetYaxis().SetTitleOffset( axisTitleOffsetY )
	hist_deltaT.Draw("E")
	maximumY=hist_deltaT.GetMaximum()
	highDeltaT=hist_deltaT.GetBinCenter(hist_deltaT.FindLastBinAbove(int(0.2*maximumY)))
	lowDeltaT=hist_deltaT.GetBinCenter(hist_deltaT.FindFirstBinAbove(int(0.2*maximumY)))
	tf1_gaus = ROOT.TF1("tf1_gaus","gaus", deltaT_mean-2.0, deltaT_mean+2.0)
	tf1_gaus.SetParameter(1, hist_deltaT.GetMean())
	hist_deltaT.Fit("tf1_gaus","","",lowDeltaT, highDeltaT)
	myC.SaveAs(outputDir+run+"_deltaT_bias"+str(bias_this)+"V.pdf")
	myC.SaveAs(outputDir+run+"_deltaT_bias"+str(bias_this)+"V.png")
	myC.SaveAs(outputDir+run+"_deltaT_bias"+str(bias_this)+"V.C")
	mean_deltaT = tf1_gaus.GetParameter(1)
	if abs(mean_deltaT - hist_deltaT.GetMean()) > 0.5:
		mean_deltaT = hist_deltaT.GetMean()
	emean_deltaT = tf1_gaus.GetParError(1)
	sigma_deltaT = tf1_gaus.GetParameter(2)
	'''
	if sigma_deltaT > hist_deltaT.GetStdDev():	
		sigma_deltaT = hist_deltaT.GetStdDev()
	'''
	esigma_deltaT = tf1_gaus.GetParError(2)

	deltaT.append(mean_deltaT)
	edeltaT.append(emean_deltaT)
	timeReso.append(sigma_deltaT)
	etimeReso.append(esigma_deltaT)

	print "mean of delta T = "+str(hist_deltaT.GetMean())
	print "fit mean of delta T = "+str(mean_deltaT)
	print "std dev of delta T = "+str(hist_deltaT.GetStdDev())
	print "fit sigma of delta T = "+str(sigma_deltaT)


	hist_ch2Amp = ROOT.TH1F("hist_ch2Amp_"+str(bias_this),"hist_ch2Amp_"+str(bias_this), 1000, 0.0, 0.5)
	tree.Draw("ch2Amp>>hist_ch2Amp_"+str(bias_this),cut_this)	
	hist_ch2Amp.SetMarkerStyle( 20 )
	hist_ch2Amp.SetMarkerColor( ROOT.kBlack )
	hist_ch2Amp.GetXaxis().SetTitle("amplitude [V]")
	hist_ch2Amp.GetYaxis().SetTitle("Events")
	hist_ch2Amp.SetTitle("")
	hist_ch2Amp.GetXaxis().SetTitleSize( axisTitleSizeX )
        hist_ch2Amp.GetXaxis().SetTitleOffset( axisTitleOffsetX )
        hist_ch2Amp.GetYaxis().SetTitleSize( axisTitleSizeY )
        hist_ch2Amp.GetYaxis().SetTitleOffset( axisTitleOffsetY )
	hist_ch2Amp.Draw("E")
	maximumY=hist_ch2Amp.GetMaximum()
	highch2Amp=hist_ch2Amp.GetBinCenter(hist_ch2Amp.FindLastBinAbove(int(0.3*maximumY)))
	lowch2Amp=hist_ch2Amp.GetBinCenter(hist_ch2Amp.FindFirstBinAbove(int(0.3*maximumY)))
	tf1_gaus_amp = ROOT.TF1("tf1_gaus_amp","gaus", 0.0, 0.5)
	tf1_gaus_amp.SetParameter(1, hist_ch2Amp.GetMean())
	hist_ch2Amp.Fit("tf1_gaus_amp","","",lowch2Amp, highch2Amp)
	myC.SaveAs(outputDir+run+"_ch2Amp_bias"+str(bias_this)+"V.pdf")
	myC.SaveAs(outputDir+run+"_ch2Amp_bias"+str(bias_this)+"V.png")
	myC.SaveAs(outputDir+run+"_ch2Amp_bias"+str(bias_this)+"V.C")
	mean_ch2Amp = tf1_gaus_amp.GetParameter(1)
	emean_ch2Amp = tf1_gaus_amp.GetParError(1)
	sigma_ch2Amp = tf1_gaus_amp.GetParameter(2)

	ch2Amp.append(mean_ch2Amp)
	ech2Amp.append(emean_ch2Amp)

	print "mean of ch2Amp = "+str(hist_ch2Amp.GetMean())
	print "fit mean of ch2Amp = "+str(mean_ch2Amp)
	print "fit sigma of ch2Amp = "+str(sigma_ch2Amp)


	N_Risetime = 500
	if NEntries < 1000:
		N_Risetime = 100
		
	hist_ch2Risetime = ROOT.TH1F("hist_ch2Risetime_"+str(bias_this),"hist_ch2Risetime_"+str(bias_this), N_Risetime, 0.0, 5.0)
	tree.Draw("ch2Risetime>>hist_ch2Risetime_"+str(bias_this),cut_this)	
	hist_ch2Risetime.SetMarkerStyle( 20 )
	hist_ch2Risetime.SetMarkerColor( ROOT.kBlack )
	hist_ch2Risetime.GetXaxis().SetTitle("risetime [ns]")
	hist_ch2Risetime.GetYaxis().SetTitle("Events")
	hist_ch2Risetime.SetTitle("")
	hist_ch2Risetime.GetXaxis().SetTitleSize( axisTitleSizeX )
        hist_ch2Risetime.GetXaxis().SetTitleOffset( axisTitleOffsetX )
        hist_ch2Risetime.GetYaxis().SetTitleSize( axisTitleSizeY )
        hist_ch2Risetime.GetYaxis().SetTitleOffset( axisTitleOffsetY )
	hist_ch2Risetime.Draw("E")
	maximumY=hist_ch2Risetime.GetMaximum()
	highch2Risetime=hist_ch2Risetime.GetBinCenter(hist_ch2Risetime.FindLastBinAbove(int(0.2*maximumY)))
	lowch2Risetime=hist_ch2Risetime.GetBinCenter(hist_ch2Risetime.FindFirstBinAbove(int(0.1*maximumY)))
	tf1_gaus_risetime = ROOT.TF1("tf1_gaus_risetime","gaus", 0.0, 5.0)
	tf1_gaus_risetime.SetParameter(1, hist_ch2Risetime.GetMean())
	hist_ch2Risetime.Fit("tf1_gaus_risetime","","",lowch2Risetime, highch2Risetime)
	myC.SaveAs(outputDir+run+"_ch2Risetime_bias"+str(bias_this)+"V.pdf")
	myC.SaveAs(outputDir+run+"_ch2Risetime_bias"+str(bias_this)+"V.png")
	myC.SaveAs(outputDir+run+"_ch2Risetime_bias"+str(bias_this)+"V.C")
	mean_ch2Risetime = tf1_gaus_risetime.GetParameter(1)
	if abs(mean_ch2Risetime - hist_ch2Risetime.GetMean()) > 1.0:
		mean_ch2Risetime = hist_ch2Risetime.GetMean()
	emean_ch2Risetime = tf1_gaus_risetime.GetParError(1)
	sigma_ch2Risetime = tf1_gaus_risetime.GetParameter(2)

	ch2Risetime.append(mean_ch2Risetime)
	ech2Risetime.append(emean_ch2Risetime)

	print "mean of ch2Risetime = "+str(hist_ch2Risetime.GetMean())
	print "fit mean of ch2Risetime = "+str(mean_ch2Risetime)
	print "fit sigma of ch2Risetime = "+str(sigma_ch2Risetime)

	hist_ch2IntRatio = ROOT.TH1F("hist_ch2IntRatio_"+str(bias_this),"hist_ch2IntRatio_"+str(bias_this), 600, 0.0, 1.5)
	tree.Draw("(ch2Int - ch2Int_gauspeak)/ch2Int>>hist_ch2IntRatio_"+str(bias_this),cut_this)	
	hist_ch2IntRatio.SetMarkerStyle( 20 )
	hist_ch2IntRatio.SetMarkerColor( ROOT.kBlack )
	hist_ch2IntRatio.GetXaxis().SetTitle("scintillation light / total charge")
	hist_ch2IntRatio.GetYaxis().SetTitle("Events")
	hist_ch2IntRatio.SetTitle("")
	hist_ch2IntRatio.GetXaxis().SetTitleSize( axisTitleSizeX )
        hist_ch2IntRatio.GetXaxis().SetTitleOffset( axisTitleOffsetX )
        hist_ch2IntRatio.GetYaxis().SetTitleSize( axisTitleSizeY )
        hist_ch2IntRatio.GetYaxis().SetTitleOffset( axisTitleOffsetY )
	hist_ch2IntRatio.Draw("E")
	maximumY=hist_ch2IntRatio.GetMaximum()
	lowch2IntRatio=hist_ch2IntRatio.GetBinCenter(hist_ch2IntRatio.FindFirstBinAbove(int(0.3*maximumY)))
	#highch2IntRatio=hist_ch2IntRatio.GetBinCenter(hist_ch2IntRatio.FindLastBinAbove(int(0.5*maximumY)))
	maximumX=hist_ch2IntRatio.GetBinCenter(hist_ch2IntRatio.GetMaximumBin())
	highch2IntRatio = maximumX + (maximumX-lowch2IntRatio)
	tf1_gaus_IntRatio = ROOT.TF1("tf1_gaus_IntRatio","gaus", 0.0, 1.5)
	tf1_gaus_IntRatio.SetParameter(1, hist_ch2IntRatio.GetMean())
	hist_ch2IntRatio.Fit("tf1_gaus_IntRatio","","",lowch2IntRatio, highch2IntRatio)
	myC.SaveAs(outputDir+run+"_ch2IntRatio_bias"+str(bias_this)+"V.pdf")
	myC.SaveAs(outputDir+run+"_ch2IntRatio_bias"+str(bias_this)+"V.png")
	myC.SaveAs(outputDir+run+"_ch2IntRatio_bias"+str(bias_this)+"V.C")
	mean_ch2IntRatio = tf1_gaus_IntRatio.GetParameter(1)
	emean_ch2IntRatio = tf1_gaus_IntRatio.GetParError(1)
	sigma_ch2IntRatio = tf1_gaus_IntRatio.GetParameter(2)

        if hist_ch2IntRatio.Integral() < 10.0:
                mean_ch2IntRatio = 0.0
                emean_ch2IntRatio = 0.0
                sigma_ch2IntRatio = 0.0
                esigma_ch2IntRatio = 0.0

	ch2IntRatio.append(mean_ch2IntRatio)
	ech2IntRatio.append(emean_ch2IntRatio)

	print "mean of ch2IntRatio = "+str(hist_ch2IntRatio.GetMean())
	print "fit mean of ch2IntRatio = "+str(mean_ch2IntRatio)
	print "fit sigma of ch2IntRatio = "+str(sigma_ch2IntRatio)



print "bias_val:"
print bias_val
print ebias_val
print "timeReso:"
print timeReso
print etimeReso
print "deltaT:"
print deltaT
print edeltaT
print "ch2Amp:"
print ch2Amp
print ech2Amp
print "ch2Risetime:"
print ch2Risetime
print ech2Risetime


## plot A vs B

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

gr_deltaT_vs_bias = ROOT.TGraphErrors(nbins_bias, np.array(bias_val), np.array(deltaT), np.array(ebias_val), np.array(edeltaT))
gr_deltaT_vs_bias.SetMarkerStyle( 20 )
gr_deltaT_vs_bias.SetMarkerColor( ROOT.kBlack )
gr_deltaT_vs_bias.SetLineWidth( 2 )
gr_deltaT_vs_bias.SetLineColor( ROOT.kBlack ) 
gr_deltaT_vs_bias.GetXaxis().SetTitle("bias [V]")
gr_deltaT_vs_bias.GetYaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
gr_deltaT_vs_bias.SetTitle("")
gr_deltaT_vs_bias.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_deltaT_vs_bias.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_deltaT_vs_bias.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_deltaT_vs_bias.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_deltaT_vs_bias.GetYaxis().SetRangeUser(41.0, 44.0)
gr_deltaT_vs_bias.Draw("AP")
myC.SaveAs(outputDir+run+"_deltaT_vs_bias.pdf")
myC.SaveAs(outputDir+run+"_deltaT_vs_bias.png")
myC.SaveAs(outputDir+run+"_deltaT_vs_bias.C")


gr_ch2Amp_vs_bias = ROOT.TGraphErrors(nbins_bias, np.array(bias_val), np.array(ch2Amp), np.array(ebias_val), np.array(ech2Amp))
gr_ch2Amp_vs_bias.SetMarkerStyle( 20 )
gr_ch2Amp_vs_bias.SetMarkerColor( ROOT.kBlack )
gr_ch2Amp_vs_bias.SetLineWidth( 2 )
gr_ch2Amp_vs_bias.SetLineColor( ROOT.kBlack ) 
gr_ch2Amp_vs_bias.GetXaxis().SetTitle("bias [V]")
gr_ch2Amp_vs_bias.GetYaxis().SetTitle("amplitude [V]")
gr_ch2Amp_vs_bias.SetTitle("")
gr_ch2Amp_vs_bias.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_ch2Amp_vs_bias.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_ch2Amp_vs_bias.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_ch2Amp_vs_bias.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_ch2Amp_vs_bias.GetYaxis().SetRangeUser(0.0, 0.4)
gr_ch2Amp_vs_bias.Draw("AP")
myC.SaveAs(outputDir+run+"_ch2Amp_vs_bias.pdf")
myC.SaveAs(outputDir+run+"_ch2Amp_vs_bias.png")
myC.SaveAs(outputDir+run+"_ch2Amp_vs_bias.C")


gr_timeReso_vs_bias = ROOT.TGraphErrors(nbins_bias, np.array(bias_val), np.array(timeReso), np.array(ebias_val), np.array(etimeReso))
gr_timeReso_vs_bias.SetMarkerStyle( 20 )
gr_timeReso_vs_bias.SetMarkerColor( ROOT.kBlack )
gr_timeReso_vs_bias.SetLineWidth( 2 )
gr_timeReso_vs_bias.SetLineColor( ROOT.kBlack ) 
gr_timeReso_vs_bias.GetXaxis().SetTitle("bias [V]")
gr_timeReso_vs_bias.GetYaxis().SetTitle("#sigma_{t} [ns]")
gr_timeReso_vs_bias.SetTitle("")
gr_timeReso_vs_bias.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_timeReso_vs_bias.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_timeReso_vs_bias.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_timeReso_vs_bias.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_timeReso_vs_bias.GetYaxis().SetRangeUser(0.01, 0.1)
gr_timeReso_vs_bias.Draw("AP")
myC.SaveAs(outputDir+run+"_timeReso_vs_bias.pdf")
myC.SaveAs(outputDir+run+"_timeReso_vs_bias.png")
myC.SaveAs(outputDir+run+"_timeReso_vs_bias.C")


gr_ch2Risetime_vs_bias = ROOT.TGraphErrors(nbins_bias, np.array(bias_val), np.array(ch2Risetime), np.array(ebias_val), np.array(ech2Risetime))
gr_ch2Risetime_vs_bias.SetMarkerStyle( 20 )
gr_ch2Risetime_vs_bias.SetMarkerColor( ROOT.kBlack )
gr_ch2Risetime_vs_bias.SetLineWidth( 2 )
gr_ch2Risetime_vs_bias.SetLineColor( ROOT.kBlack ) 
gr_ch2Risetime_vs_bias.GetXaxis().SetTitle("bias [V]")
gr_ch2Risetime_vs_bias.GetYaxis().SetTitle("risetime [ns]")
gr_ch2Risetime_vs_bias.SetTitle("")
gr_ch2Risetime_vs_bias.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_ch2Risetime_vs_bias.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_ch2Risetime_vs_bias.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_ch2Risetime_vs_bias.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_ch2Risetime_vs_bias.GetYaxis().SetRangeUser(0.5, 0.9)
gr_ch2Risetime_vs_bias.Draw("AP")
myC.SaveAs(outputDir+run+"_ch2Risetime_vs_bias.pdf")
myC.SaveAs(outputDir+run+"_ch2Risetime_vs_bias.png")
myC.SaveAs(outputDir+run+"_ch2Risetime_vs_bias.C")


gr_ch2IntRatio_vs_bias = ROOT.TGraphErrors(nbins_bias, np.array(bias_val), np.array(ch2IntRatio), np.array(ebias_val), np.array(ech2IntRatio))
gr_ch2IntRatio_vs_bias.SetMarkerStyle( 20 )
gr_ch2IntRatio_vs_bias.SetMarkerColor( ROOT.kBlack )
gr_ch2IntRatio_vs_bias.SetLineWidth( 2 )
gr_ch2IntRatio_vs_bias.SetLineColor( ROOT.kBlack ) 
gr_ch2IntRatio_vs_bias.GetXaxis().SetTitle("bias [V]")
gr_ch2IntRatio_vs_bias.GetYaxis().SetTitle("scintillation light / total charge")
gr_ch2IntRatio_vs_bias.SetTitle("")
gr_ch2IntRatio_vs_bias.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_ch2IntRatio_vs_bias.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_ch2IntRatio_vs_bias.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_ch2IntRatio_vs_bias.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_ch2IntRatio_vs_bias.GetYaxis().SetRangeUser(0.0, 1.0)
gr_ch2IntRatio_vs_bias.Draw("AP")
myC.SaveAs(outputDir+run+"_ch2IntRatio_vs_bias.pdf")
myC.SaveAs(outputDir+run+"_ch2IntRatio_vs_bias.png")
myC.SaveAs(outputDir+run+"_ch2IntRatio_vs_bias.C")






