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
#run = "combine_1002_1015_407nm"
#run = "combine_1016_1029_373nm"
#run = "combine_1032_1045_373nm"
#run = "combine_1046_1059_407nm"

run = "combine_1157_1171_373nm_UVfilter"
isUVlaser = True

#run = "1031"
inputDir = "~/LabData/Zhicai_Spring2018/data/"
outputDir = "~/LabData/Zhicai_Spring2018/plots/"

os.system("mkdir -p "+outputDir)

cut = "ch1Amp>0.2 && ch1Amp<0.35 && ch2Amp > 0.002 && t1gausroot>0 && ch2LinearTime60 - t1gausroot<45 && ch2LinearTime60 - t1gausroot>40"


deltaT_mean = 42.9 #for 407nm laser
RiseTime_mean = 0.67 # for 407nm laser
max_amp = 0.10 # for 407nm laser
max_timeReso = 0.05 # for 407nm laser

if isUVlaser:
	cut = "ch1Amp>0.2 && ch1Amp<0.35 && ch2Amp > 0.005 && t1gausroot>0 && ch2LinearTime60 - t1gausroot<45 && ch2LinearTime60 - t1gausroot>40"
	deltaT_mean = 41.9 #for 373nm laser
	RiseTime_mean = 2.0 # for 407nm laser
	max_amp = 0.03 # for 373nm laser
	max_timeReso = 0.20 # for 373nm laser
	max_risetime = 5.0


deltaT_low = deltaT_mean - 0.3
deltaT_high = deltaT_mean + 0.3

x_low = -0.5
x_high = 14.5
nbins_X = 15
########################################################

file=ROOT.TFile(inputDir+run+"_ana.root")
tree=file.Get("tree")

print tree.GetEntries()

x_pos = []
timeReso = []
timeReso_tw = []
timeReso_rc = []
timeReso_twrc = []
deltaT = []
deltaT_tw = []
deltaT_rc = []
deltaT_twrc = []
ch2Amp = []
ch2Risetime = []

ex_pos = []
etimeReso = []
etimeReso_tw = []
etimeReso_rc = []
etimeReso_twrc = []
edeltaT = []
edeltaT_tw = []
edeltaT_rc = []
edeltaT_twrc = []
ech2Amp = []
ech2Risetime = []


##############

tw_amp = []
tw_eamp = []
tw_dT = []
tw_edT = []
tw_sigmaT = []
tw_esigmaT = []

nbins_tw = 20
low_amp = 0.008
high_amp = 0.018

for iamp in range(0, nbins_tw):
	low_cut = low_amp + iamp*(high_amp-low_amp)/nbins_tw
	high_cut = low_amp + (iamp+1)*(high_amp-low_amp)/nbins_tw
	amp_this = low_amp + (iamp+0.5)*(high_amp-low_amp)/nbins_tw
	tw_amp.append(amp_this)
	tw_eamp.append(0.5*(high_amp-low_amp)/nbins_tw)

	cut_this = cut + " && ch2Amp > " + str(low_cut) + " && ch2Amp < " + str(high_cut)
	NEntries = tree.GetEntries(cut_this)
	#print cut_this
	print "deltaT for ch2Amp = "+str(cut_this)
	
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

	hist_deltaT = ROOT.TH1F("hist_deltaT_"+str(cut_this),"hist_deltaT_"+str(cut_this),400,deltaT_mean-2.0,deltaT_mean+2.0)
	tree.Draw("ch2LinearTime60-t1gausroot>>hist_deltaT_"+str(cut_this),cut_this)	
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
	myC.SaveAs(outputDir+run+"_deltaT_amp"+str(amp_this)+"V.pdf")
	myC.SaveAs(outputDir+run+"_deltaT_amp"+str(amp_this)+"V.png")
	myC.SaveAs(outputDir+run+"_deltaT_amp"+str(amp_this)+"V.C")
	mean_deltaT = tf1_gaus.GetParameter(1)
	emean_deltaT = tf1_gaus.GetParError(1)
	sigma_deltaT = tf1_gaus.GetParameter(2)
	esigma_deltaT = tf1_gaus.GetParError(2)

	if hist_deltaT.Integral() < 10.0:
		mean_deltaT = 0.0 
		emean_deltaT = 0.0 
		sigma_deltaT = 0.0
		esigma_deltaT = 0.0
	tw_dT.append(mean_deltaT)
	tw_edT.append(emean_deltaT)
	tw_sigmaT.append(sigma_deltaT)
	tw_esigmaT.append(esigma_deltaT)


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


tf1_tw_linear = ROOT.TF1("tf1_tw_linear","[0]*x+[1]", low_amp, high_amp)

gr_deltaT_vs_amp = ROOT.TGraphErrors(nbins_tw, np.array(tw_amp), np.array(tw_dT), np.array(tw_eamp), np.array(tw_edT))

tf1_tw_linear.SetParameter(0,0.0)
tf1_tw_linear.SetParameter(1,deltaT_high)
gr_deltaT_vs_amp.Fit("tf1_tw_linear")

gr_deltaT_vs_amp.SetMarkerStyle( 20 )
gr_deltaT_vs_amp.SetMarkerColor( ROOT.kBlack )
gr_deltaT_vs_amp.SetLineWidth( 2 )
gr_deltaT_vs_amp.SetLineColor( ROOT.kBlack ) 
gr_deltaT_vs_amp.GetXaxis().SetTitle("amplitude [V]")
gr_deltaT_vs_amp.GetYaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
gr_deltaT_vs_amp.SetTitle("")
gr_deltaT_vs_amp.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_deltaT_vs_amp.GetXaxis().SetNdivisions( 505 )
gr_deltaT_vs_amp.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_deltaT_vs_amp.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_deltaT_vs_amp.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_deltaT_vs_amp.GetYaxis().SetRangeUser(deltaT_low,deltaT_high)
gr_deltaT_vs_amp.Draw("AP")
myC.SaveAs(outputDir+run+"_deltaT_vs_amp.pdf")
myC.SaveAs(outputDir+run+"_deltaT_vs_amp.png")
myC.SaveAs(outputDir+run+"_deltaT_vs_amp.C")

tw_corr_a = tf1_tw_linear.GetParameter(0)

print "time walk correction slope: "+str(tw_corr_a)




##############risetime correction

rc_risetime = []
rc_erisetime = []
rc_dT = []
rc_edT = []
rc_sigmaT = []
rc_esigmaT = []

nbins_rc = 20
low_risetime = 0.8
high_risetime = 1.8

for irisetime in range(0, nbins_rc):
	low_cut = low_risetime + irisetime*(high_risetime-low_risetime)/nbins_rc
	high_cut = low_risetime + (irisetime+1)*(high_risetime-low_risetime)/nbins_rc
	risetime_this = low_risetime + (irisetime+0.5)*(high_risetime-low_risetime)/nbins_rc
	rc_risetime.append(risetime_this)
	rc_erisetime.append(0.5*(high_risetime-low_risetime)/nbins_rc)

	cut_this = cut + " && ch2Risetime > " + str(low_cut) + " && ch2Risetime < " + str(high_cut)
	NEntries = tree.GetEntries(cut_this)
	#print cut_this
	print "deltaT for ch2Risetime = "+str(risetime_this)
	
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

	hist_deltaT = ROOT.TH1F("hist_deltaT_"+str(cut_this),"hist_deltaT_"+str(cut_this),400,deltaT_mean-2.0,deltaT_mean+2.0)
	tree.Draw("ch2LinearTime60-t1gausroot>>hist_deltaT_"+str(cut_this),cut_this)	
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
	myC.SaveAs(outputDir+run+"_deltaT_risetime"+str(risetime_this)+"ns.pdf")
	myC.SaveAs(outputDir+run+"_deltaT_risetime"+str(risetime_this)+"ns.png")
	myC.SaveAs(outputDir+run+"_deltaT_risetime"+str(risetime_this)+"ns.C")
	mean_deltaT = tf1_gaus.GetParameter(1)
	emean_deltaT = tf1_gaus.GetParError(1)
	sigma_deltaT = tf1_gaus.GetParameter(2)
	esigma_deltaT = tf1_gaus.GetParError(2)

	if hist_deltaT.Integral() < 10.0:
		mean_deltaT = 0.0 
		emean_deltaT = 0.6*deltaT_low
		sigma_deltaT = 0.0
		esigma_deltaT = 0.0
	rc_dT.append(mean_deltaT)
	rc_edT.append(emean_deltaT)
	rc_sigmaT.append(sigma_deltaT)
	rc_esigmaT.append(esigma_deltaT)


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


tf1_rc_linear = ROOT.TF1("tf1_rc_linear","[0]*x+[1]", low_risetime, high_risetime)

gr_deltaT_vs_risetime = ROOT.TGraphErrors(nbins_rc, np.array(rc_risetime), np.array(rc_dT), np.array(rc_erisetime), np.array(rc_edT))

tf1_rc_linear.SetParameter(0,0.2)
tf1_rc_linear.SetParameter(1,deltaT_low)
gr_deltaT_vs_risetime.Fit("tf1_rc_linear")

gr_deltaT_vs_risetime.SetMarkerStyle( 20 )
gr_deltaT_vs_risetime.SetMarkerColor( ROOT.kBlack )
gr_deltaT_vs_risetime.SetLineWidth( 2 )
gr_deltaT_vs_risetime.SetLineColor( ROOT.kBlack ) 
gr_deltaT_vs_risetime.GetXaxis().SetTitle("risetime [ns]")
gr_deltaT_vs_risetime.GetYaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
gr_deltaT_vs_risetime.SetTitle("")
gr_deltaT_vs_risetime.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_deltaT_vs_risetime.GetXaxis().SetNdivisions( 505 )
gr_deltaT_vs_risetime.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_deltaT_vs_risetime.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_deltaT_vs_risetime.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_deltaT_vs_risetime.GetYaxis().SetRangeUser(deltaT_low,deltaT_high)
gr_deltaT_vs_risetime.Draw("AP")
myC.SaveAs(outputDir+run+"_deltaT_vs_risetime.pdf")
myC.SaveAs(outputDir+run+"_deltaT_vs_risetime.png")
myC.SaveAs(outputDir+run+"_deltaT_vs_risetime.C")

rc_corr_a = tf1_rc_linear.GetParameter(0)

print "time walk correction slope: "+str(rc_corr_a)

##############risetime correction after time walk correction

rcAftertw_risetime = []
rcAftertw_erisetime = []
rcAftertw_dT = []
rcAftertw_edT = []
rcAftertw_sigmaT = []
rcAftertw_esigmaT = []

nbins_rcAftertw = 20
low_risetime = 0.8
high_risetime = 1.8

for irisetime in range(0, nbins_rcAftertw):
	low_cut = low_risetime + irisetime*(high_risetime-low_risetime)/nbins_rcAftertw
	high_cut = low_risetime + (irisetime+1)*(high_risetime-low_risetime)/nbins_rcAftertw
	risetime_this = low_risetime + (irisetime+0.5)*(high_risetime-low_risetime)/nbins_rcAftertw
	rcAftertw_risetime.append(risetime_this)
	rcAftertw_erisetime.append(0.5*(high_risetime-low_risetime)/nbins_rcAftertw)

	cut_this = cut + " && ch2Risetime > " + str(low_cut) + " && ch2Risetime < " + str(high_cut)
	NEntries = tree.GetEntries(cut_this)
	#print cut_this
	print "deltaT for ch2Risetime = "+str(risetime_this)
	
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

	hist_deltaT = ROOT.TH1F("hist_deltaT_"+str(cut_this),"hist_deltaT_"+str(cut_this),400,deltaT_mean-2.0,deltaT_mean+2.0)
	tree.Draw("-0.2+ch2LinearTime60-ch2Amp*"+str(tw_corr_a)+"-t1gausroot>>hist_deltaT_"+str(cut_this),cut_this)	
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
	myC.SaveAs(outputDir+run+"_deltaT_risetime"+str(risetime_this)+"ns.pdf")
	myC.SaveAs(outputDir+run+"_deltaT_risetime"+str(risetime_this)+"ns.png")
	myC.SaveAs(outputDir+run+"_deltaT_risetime"+str(risetime_this)+"ns.C")
	mean_deltaT = tf1_gaus.GetParameter(1)
	emean_deltaT = tf1_gaus.GetParError(1)
	sigma_deltaT = tf1_gaus.GetParameter(2)
	esigma_deltaT = tf1_gaus.GetParError(2)

	if hist_deltaT.Integral() < 10.0:
		mean_deltaT = 0.0 
		emean_deltaT = 0.6*deltaT_low
		sigma_deltaT = 0.0
		esigma_deltaT = 0.0
	rcAftertw_dT.append(mean_deltaT)
	rcAftertw_edT.append(emean_deltaT)
	rcAftertw_sigmaT.append(sigma_deltaT)
	rcAftertw_esigmaT.append(esigma_deltaT)


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


tf1_rcAftertw_linear = ROOT.TF1("tf1_rcAftertw_linear","[0]*x+[1]", low_risetime, high_risetime)

gr_deltaT_vs_risetime = ROOT.TGraphErrors(nbins_rcAftertw, np.array(rcAftertw_risetime), np.array(rcAftertw_dT), np.array(rcAftertw_erisetime), np.array(rcAftertw_edT))

tf1_rcAftertw_linear.SetParameter(0,0.2)
tf1_rcAftertw_linear.SetParameter(1,deltaT_low)
gr_deltaT_vs_risetime.Fit("tf1_rcAftertw_linear")

gr_deltaT_vs_risetime.SetMarkerStyle( 20 )
gr_deltaT_vs_risetime.SetMarkerColor( ROOT.kBlack )
gr_deltaT_vs_risetime.SetLineWidth( 2 )
gr_deltaT_vs_risetime.SetLineColor( ROOT.kBlack ) 
gr_deltaT_vs_risetime.GetXaxis().SetTitle("risetime [ns]")
gr_deltaT_vs_risetime.GetYaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
gr_deltaT_vs_risetime.SetTitle("")
gr_deltaT_vs_risetime.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_deltaT_vs_risetime.GetXaxis().SetNdivisions( 505 )
gr_deltaT_vs_risetime.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_deltaT_vs_risetime.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_deltaT_vs_risetime.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_deltaT_vs_risetime.GetYaxis().SetRangeUser(deltaT_low,deltaT_high)
gr_deltaT_vs_risetime.Draw("AP")
myC.SaveAs(outputDir+run+"_deltaT_vs_risetime_Aftertw.pdf")
myC.SaveAs(outputDir+run+"_deltaT_vs_risetime_Aftertw.png")
myC.SaveAs(outputDir+run+"_deltaT_vs_risetime_Aftertw.C")

rcAftertw_corr_a = tf1_rcAftertw_linear.GetParameter(0)

print "time walk correction slope: "+str(rcAftertw_corr_a)


#####scan over different positions

for ix in range(0, nbins_X):
	low_cut = x_low + ix*(x_high-x_low)/nbins_X
	high_cut = x_low + (ix+1)*(x_high-x_low)/nbins_X
	x_this = x_low + (ix+0.5)*(x_high-x_low)/nbins_X
	x_pos.append(x_this)
	ex_pos.append(0.5*(x_high-x_low)/nbins_X)

	cut_this = cut + " && x > " + str(low_cut) + " && x <  " + str(high_cut)
	NEntries = tree.GetEntries(cut_this)

	#print cut_this
	print "timing resolution for x = "+str(x_this)
	
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

	hist_deltaT = ROOT.TH1F("hist_deltaT_"+str(x_this),"hist_deltaT_"+str(x_this),N_deltaT,deltaT_mean-2.0,deltaT_mean+2.0)
	tree.Draw("ch2LinearTime60-t1gausroot>>hist_deltaT_"+str(x_this),cut_this)	
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
	myC.SaveAs(outputDir+run+"_deltaT_x"+str(x_this)+"mm.pdf")
	myC.SaveAs(outputDir+run+"_deltaT_x"+str(x_this)+"mm.png")
	myC.SaveAs(outputDir+run+"_deltaT_x"+str(x_this)+"mm.C")
	mean_deltaT = tf1_gaus.GetParameter(1)
	emean_deltaT = tf1_gaus.GetParError(1)
	sigma_deltaT = tf1_gaus.GetParameter(2)

	if hist_deltaT.Integral() < 10.0:
		mean_deltaT = 0.0 
		emean_deltaT = 0.0 
		sigma_deltaT = 0.0
		esigma_deltaT = 0.0

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

	hist_deltaT_tw = ROOT.TH1F("hist_deltaT_tw_"+str(x_this),"hist_deltaT_tw_"+str(x_this),N_deltaT,deltaT_mean-2.0,deltaT_mean+2.0)
	tree.Draw("-0.1+ch2LinearTime60-ch2Amp*"+str(tw_corr_a)+"-t1gausroot>>hist_deltaT_tw_"+str(x_this),cut_this)	
	hist_deltaT_tw.SetMarkerStyle( 20 )
	hist_deltaT_tw.SetMarkerColor( ROOT.kBlack )
	hist_deltaT_tw.GetXaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
	hist_deltaT_tw.GetYaxis().SetTitle("Events")
	hist_deltaT_tw.SetTitle("")
	hist_deltaT_tw.GetXaxis().SetTitleSize( axisTitleSizeX )
        hist_deltaT_tw.GetXaxis().SetTitleOffset( axisTitleOffsetX )
        hist_deltaT_tw.GetYaxis().SetTitleSize( axisTitleSizeY )
        hist_deltaT_tw.GetYaxis().SetTitleOffset( axisTitleOffsetY )
	hist_deltaT_tw.Draw("E")
	maximumY=hist_deltaT_tw.GetMaximum()
	highDeltaT=hist_deltaT_tw.GetBinCenter(hist_deltaT_tw.FindLastBinAbove(int(0.2*maximumY)))
	lowDeltaT=hist_deltaT_tw.GetBinCenter(hist_deltaT_tw.FindFirstBinAbove(int(0.2*maximumY)))
	tf1_gaus = ROOT.TF1("tf1_gaus","gaus", deltaT_mean-2.0, deltaT_mean+2.0)
	tf1_gaus.SetParameter(1, hist_deltaT_tw.GetMean())
	hist_deltaT_tw.Fit("tf1_gaus","","",lowDeltaT, highDeltaT)
	myC.SaveAs(outputDir+run+"_deltaT_tw_x"+str(x_this)+"mm.pdf")
	myC.SaveAs(outputDir+run+"_deltaT_tw_x"+str(x_this)+"mm.png")
	myC.SaveAs(outputDir+run+"_deltaT_tw_x"+str(x_this)+"mm.C")
	mean_deltaT_tw = tf1_gaus.GetParameter(1)
	emean_deltaT_tw = tf1_gaus.GetParError(1)
	sigma_deltaT_tw = tf1_gaus.GetParameter(2)

	if hist_deltaT_tw.Integral() < 10.0:
		mean_deltaT_tw = 0.0 
		emean_deltaT_tw = 0.0 
		sigma_deltaT_tw = 0.0
		esigma_deltaT_tw = 0.0

	'''
	if sigma_deltaT_tw > hist_deltaT_tw.GetStdDev():	
		sigma_deltaT_tw = hist_deltaT_tw.GetStdDev()
	'''
	esigma_deltaT_tw = tf1_gaus.GetParError(2)

	deltaT_tw.append(mean_deltaT_tw)
	edeltaT_tw.append(emean_deltaT_tw)
	timeReso_tw.append(sigma_deltaT_tw)
	etimeReso_tw.append(esigma_deltaT_tw)

	print "mean of delta T = "+str(hist_deltaT_tw.GetMean())
	print "fit mean of delta T = "+str(mean_deltaT_tw)
	print "std dev of delta T = "+str(hist_deltaT_tw.GetStdDev())
	print "fit sigma of delta T = "+str(sigma_deltaT_tw)


	hist_deltaT_rc = ROOT.TH1F("hist_deltaT_rc_"+str(x_this),"hist_deltaT_rc_"+str(x_this),N_deltaT,deltaT_mean-2.0,deltaT_mean+2.0)
	tree.Draw("0.4+ch2LinearTime60-ch2Risetime*"+str(rc_corr_a)+"-t1gausroot>>hist_deltaT_rc_"+str(x_this),cut_this)	
	hist_deltaT_rc.SetMarkerStyle( 20 )
	hist_deltaT_rc.SetMarkerColor( ROOT.kBlack )
	hist_deltaT_rc.GetXaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
	hist_deltaT_rc.GetYaxis().SetTitle("Events")
	hist_deltaT_rc.SetTitle("")
	hist_deltaT_rc.GetXaxis().SetTitleSize( axisTitleSizeX )
        hist_deltaT_rc.GetXaxis().SetTitleOffset( axisTitleOffsetX )
        hist_deltaT_rc.GetYaxis().SetTitleSize( axisTitleSizeY )
        hist_deltaT_rc.GetYaxis().SetTitleOffset( axisTitleOffsetY )
	hist_deltaT_rc.Draw("E")
	maximumY=hist_deltaT_rc.GetMaximum()
	highDeltaT=hist_deltaT_rc.GetBinCenter(hist_deltaT_rc.FindLastBinAbove(int(0.2*maximumY)))
	lowDeltaT=hist_deltaT_rc.GetBinCenter(hist_deltaT_rc.FindFirstBinAbove(int(0.2*maximumY)))
	tf1_gaus = ROOT.TF1("tf1_gaus","gaus", deltaT_mean-2.0, deltaT_mean+2.0)
	tf1_gaus.SetParameter(1, hist_deltaT_rc.GetMean())
	hist_deltaT_rc.Fit("tf1_gaus","","",lowDeltaT, highDeltaT)
	myC.SaveAs(outputDir+run+"_deltaT_rc_x"+str(x_this)+"mm.pdf")
	myC.SaveAs(outputDir+run+"_deltaT_rc_x"+str(x_this)+"mm.png")
	myC.SaveAs(outputDir+run+"_deltaT_rc_x"+str(x_this)+"mm.C")
	mean_deltaT_rc = tf1_gaus.GetParameter(1)
	emean_deltaT_rc = tf1_gaus.GetParError(1)
	sigma_deltaT_rc = tf1_gaus.GetParameter(2)

	if hist_deltaT_rc.Integral() < 10.0:
		mean_deltaT_rc = 0.0 
		emean_deltaT_rc = 0.0 
		sigma_deltaT_rc = 0.0
		esigma_deltaT_rc = 0.0

	'''
	if sigma_deltaT_rc > hist_deltaT_rc.GetStdDev():	
		sigma_deltaT_rc = hist_deltaT_rc.GetStdDev()
	'''
	esigma_deltaT_rc = tf1_gaus.GetParError(2)

	deltaT_rc.append(mean_deltaT_rc)
	edeltaT_rc.append(emean_deltaT_rc)
	timeReso_rc.append(sigma_deltaT_rc)
	etimeReso_rc.append(esigma_deltaT_rc)

	print "mean of delta T = "+str(hist_deltaT_rc.GetMean())
	print "fit mean of delta T = "+str(mean_deltaT_rc)
	print "std dev of delta T = "+str(hist_deltaT_rc.GetStdDev())
	print "fit sigma of delta T = "+str(sigma_deltaT_rc)


	hist_deltaT_twrc = ROOT.TH1F("hist_deltaT_twrc_"+str(x_this),"hist_deltaT_twrc_"+str(x_this),N_deltaT,deltaT_mean-2.0,deltaT_mean+2.0)
	tree.Draw("0.1+ch2LinearTime60-ch2Amp*"+str(tw_corr_a)+" - ch2Risetime*"+str(rcAftertw_corr_a)+"-t1gausroot>>hist_deltaT_twrc_"+str(x_this),cut_this)	
	hist_deltaT_twrc.SetMarkerStyle( 20 )
	hist_deltaT_twrc.SetMarkerColor( ROOT.kBlack )
	hist_deltaT_twrc.GetXaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
	hist_deltaT_twrc.GetYaxis().SetTitle("Events")
	hist_deltaT_twrc.SetTitle("")
	hist_deltaT_twrc.GetXaxis().SetTitleSize( axisTitleSizeX )
        hist_deltaT_twrc.GetXaxis().SetTitleOffset( axisTitleOffsetX )
        hist_deltaT_twrc.GetYaxis().SetTitleSize( axisTitleSizeY )
        hist_deltaT_twrc.GetYaxis().SetTitleOffset( axisTitleOffsetY )
	hist_deltaT_twrc.Draw("E")
	maximumY=hist_deltaT_twrc.GetMaximum()
	highDeltaT=hist_deltaT_twrc.GetBinCenter(hist_deltaT_twrc.FindLastBinAbove(int(0.2*maximumY)))
	lowDeltaT=hist_deltaT_twrc.GetBinCenter(hist_deltaT_twrc.FindFirstBinAbove(int(0.2*maximumY)))
	tf1_gaus = ROOT.TF1("tf1_gaus","gaus", deltaT_mean-2.0, deltaT_mean+2.0)
	tf1_gaus.SetParameter(1, hist_deltaT_twrc.GetMean())
	hist_deltaT_twrc.Fit("tf1_gaus","","",lowDeltaT, highDeltaT)
	myC.SaveAs(outputDir+run+"_deltaT_twrc_x"+str(x_this)+"mm.pdf")
	myC.SaveAs(outputDir+run+"_deltaT_twrc_x"+str(x_this)+"mm.png")
	myC.SaveAs(outputDir+run+"_deltaT_twrc_x"+str(x_this)+"mm.C")
	mean_deltaT_twrc = tf1_gaus.GetParameter(1)
	emean_deltaT_twrc = tf1_gaus.GetParError(1)
	sigma_deltaT_twrc = tf1_gaus.GetParameter(2)

	if hist_deltaT_twrc.Integral() < 10.0:
		mean_deltaT_twrc = 0.0 
		emean_deltaT_twrc = 0.0 
		sigma_deltaT_twrc = 0.0
		esigma_deltaT_twrc = 0.0

	'''
	if sigma_deltaT_twrc > hist_deltaT_twrc.GetStdDev():	
		sigma_deltaT_twrc = hist_deltaT_twrc.GetStdDev()
	'''
	esigma_deltaT_twrc = tf1_gaus.GetParError(2)

	deltaT_twrc.append(mean_deltaT_twrc)
	edeltaT_twrc.append(emean_deltaT_twrc)
	timeReso_twrc.append(sigma_deltaT_twrc)
	etimeReso_twrc.append(esigma_deltaT_twrc)

	print "mean of delta T = "+str(hist_deltaT_twrc.GetMean())
	print "fit mean of delta T = "+str(mean_deltaT_twrc)
	print "std dev of delta T = "+str(hist_deltaT_twrc.GetStdDev())
	print "fit sigma of delta T = "+str(sigma_deltaT_twrc)


	hist_ch2Amp = ROOT.TH1F("hist_ch2Amp_"+str(x_this),"hist_ch2Amp_"+str(x_this), 200, 0.0, max_amp)
	tree.Draw("ch2Amp>>hist_ch2Amp_"+str(x_this),cut_this)	
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
	tf1_gaus_amp = ROOT.TF1("tf1_gaus_amp","gaus", 0.0, max_amp)
	tf1_gaus_amp.SetParameter(1, hist_ch2Amp.GetMean())
	hist_ch2Amp.Fit("tf1_gaus_amp","","",lowch2Amp, highch2Amp)
	myC.SaveAs(outputDir+run+"_ch2Amp_x"+str(x_this)+"mm.pdf")
	myC.SaveAs(outputDir+run+"_ch2Amp_x"+str(x_this)+"mm.png")
	myC.SaveAs(outputDir+run+"_ch2Amp_x"+str(x_this)+"mm.C")
	mean_ch2Amp = tf1_gaus_amp.GetParameter(1)
	emean_ch2Amp = tf1_gaus_amp.GetParError(1)
	sigma_ch2Amp = tf1_gaus_amp.GetParameter(2)
	esigma_ch2Amp = tf1_gaus_amp.GetParError(2)

	if hist_ch2Amp.Integral() < 10.0:
		mean_ch2Amp = 0.0
		emean_ch2Amp = 0.0
		sigma_ch2Amp = 0.0
		esigma_ch2Amp = 0.0
	ch2Amp.append(mean_ch2Amp)
	ech2Amp.append(emean_ch2Amp)

	print "mean of ch2Amp = "+str(hist_ch2Amp.GetMean())
	print "fit mean of ch2Amp = "+str(mean_ch2Amp)
	print "fit sigma of ch2Amp = "+str(sigma_ch2Amp)


	N_Risetime = 500
	if NEntries < 1000:
		N_Risetime = 100
		
	hist_ch2Risetime = ROOT.TH1F("hist_ch2Risetime_"+str(x_this),"hist_ch2Risetime_"+str(x_this), N_Risetime, 0.0, max_risetime)
	tree.Draw("ch2Risetime>>hist_ch2Risetime_"+str(x_this),cut_this)	
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
	highch2Risetime=hist_ch2Risetime.GetBinCenter(hist_ch2Risetime.FindLastBinAbove(int(0.7*maximumY)))
	lowch2Risetime=hist_ch2Risetime.GetBinCenter(hist_ch2Risetime.FindFirstBinAbove(int(0.05*maximumY)))
	peakch2Risetime=hist_ch2Risetime.GetBinCenter(hist_ch2Risetime.GetMaximumBin())
	if highch2Risetime - peakch2Risetime > peakch2Risetime - lowch2Risetime:
		highch2Risetime = peakch2Risetime + 0.5*(peakch2Risetime -  lowch2Risetime)
	tf1_gaus_risetime = ROOT.TF1("tf1_gaus_risetime","gaus", 0.0, max_risetime)
	tf1_gaus_risetime.SetParameter(1, hist_ch2Risetime.GetMean())
	hist_ch2Risetime.Fit("tf1_gaus_risetime","","",lowch2Risetime, highch2Risetime)
	myC.SaveAs(outputDir+run+"_ch2Risetime_x"+str(x_this)+"mm.pdf")
	myC.SaveAs(outputDir+run+"_ch2Risetime_x"+str(x_this)+"mm.png")
	myC.SaveAs(outputDir+run+"_ch2Risetime_x"+str(x_this)+"mm.C")
	mean_ch2Risetime = tf1_gaus_risetime.GetParameter(1)
	emean_ch2Risetime = tf1_gaus_risetime.GetParError(1)
	sigma_ch2Risetime = tf1_gaus_risetime.GetParameter(2)

	if hist_ch2Risetime.Integral() < 10.0:
		mean_ch2Risetime = 0.0
		emean_ch2Risetime = 0.0 
		sigma_ch2Risetime = 0.0
		esigma_ch2Risetime = 0.0

	ch2Risetime.append(mean_ch2Risetime)
	ech2Risetime.append(emean_ch2Risetime)

	print "mean of ch2Risetime = "+str(hist_ch2Risetime.GetMean())
	print "fit mean of ch2Risetime = "+str(mean_ch2Risetime)
	print "fit sigma of ch2Risetime = "+str(sigma_ch2Risetime)

print "x_pos:"
print x_pos
print ex_pos
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

myC.SetGridy(1)
gr_deltaT_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(deltaT), np.array(ex_pos), np.array(edeltaT))
gr_deltaT_vs_x.SetMarkerStyle( 20 )
gr_deltaT_vs_x.SetMarkerColor( ROOT.kBlack )
gr_deltaT_vs_x.SetLineWidth( 2 )
gr_deltaT_vs_x.SetLineColor( ROOT.kBlack ) 
gr_deltaT_vs_x.GetXaxis().SetTitle("x [mm]")
gr_deltaT_vs_x.GetYaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
gr_deltaT_vs_x.SetTitle("")
gr_deltaT_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_deltaT_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_deltaT_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_deltaT_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_deltaT_vs_x.GetYaxis().SetRangeUser(deltaT_low,deltaT_high)
gr_deltaT_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_deltaT_vs_x.pdf")
myC.SaveAs(outputDir+run+"_deltaT_vs_x.png")
myC.SaveAs(outputDir+run+"_deltaT_vs_x.C")


gr_deltaT_tw_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(deltaT_tw), np.array(ex_pos), np.array(edeltaT_tw))
gr_deltaT_tw_vs_x.SetMarkerStyle( 20 )
gr_deltaT_tw_vs_x.SetMarkerColor( ROOT.kBlack )
gr_deltaT_tw_vs_x.SetLineWidth( 2 )
gr_deltaT_tw_vs_x.SetLineColor( ROOT.kBlack ) 
gr_deltaT_tw_vs_x.GetXaxis().SetTitle("x [mm]")
gr_deltaT_tw_vs_x.GetYaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
gr_deltaT_tw_vs_x.SetTitle("")
gr_deltaT_tw_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_deltaT_tw_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_deltaT_tw_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_deltaT_tw_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_deltaT_tw_vs_x.GetYaxis().SetRangeUser(deltaT_low,deltaT_high)
gr_deltaT_tw_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_deltaT_tw_vs_x.pdf")
myC.SaveAs(outputDir+run+"_deltaT_tw_vs_x.png")
myC.SaveAs(outputDir+run+"_deltaT_tw_vs_x.C")


gr_deltaT_rc_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(deltaT_rc), np.array(ex_pos), np.array(edeltaT_rc))
gr_deltaT_rc_vs_x.SetMarkerStyle( 20 )
gr_deltaT_rc_vs_x.SetMarkerColor( ROOT.kBlack )
gr_deltaT_rc_vs_x.SetLineWidth( 2 )
gr_deltaT_rc_vs_x.SetLineColor( ROOT.kBlack ) 
gr_deltaT_rc_vs_x.GetXaxis().SetTitle("x [mm]")
gr_deltaT_rc_vs_x.GetYaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
gr_deltaT_rc_vs_x.SetTitle("")
gr_deltaT_rc_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_deltaT_rc_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_deltaT_rc_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_deltaT_rc_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_deltaT_rc_vs_x.GetYaxis().SetRangeUser(deltaT_low,deltaT_high)
gr_deltaT_rc_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_deltaT_rc_vs_x.pdf")
myC.SaveAs(outputDir+run+"_deltaT_rc_vs_x.png")
myC.SaveAs(outputDir+run+"_deltaT_rc_vs_x.C")


gr_deltaT_twrc_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(deltaT_twrc), np.array(ex_pos), np.array(edeltaT_twrc))
gr_deltaT_twrc_vs_x.SetMarkerStyle( 20 )
gr_deltaT_twrc_vs_x.SetMarkerColor( ROOT.kBlack )
gr_deltaT_twrc_vs_x.SetLineWidth( 2 )
gr_deltaT_twrc_vs_x.SetLineColor( ROOT.kBlack ) 
gr_deltaT_twrc_vs_x.GetXaxis().SetTitle("x [mm]")
gr_deltaT_twrc_vs_x.GetYaxis().SetTitle("#Delta t (SiPM, laser) [ns]")
gr_deltaT_twrc_vs_x.SetTitle("")
gr_deltaT_twrc_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_deltaT_twrc_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_deltaT_twrc_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_deltaT_twrc_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_deltaT_twrc_vs_x.GetYaxis().SetRangeUser(deltaT_low,deltaT_high)
gr_deltaT_twrc_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_deltaT_twrc_vs_x.pdf")
myC.SaveAs(outputDir+run+"_deltaT_twrc_vs_x.png")
myC.SaveAs(outputDir+run+"_deltaT_twrc_vs_x.C")


myC.SetGridy(0)


gr_ch2Amp_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(ch2Amp), np.array(ex_pos), np.array(ech2Amp))
gr_ch2Amp_vs_x.SetMarkerStyle( 20 )
gr_ch2Amp_vs_x.SetMarkerColor( ROOT.kBlack )
gr_ch2Amp_vs_x.SetLineWidth( 2 )
gr_ch2Amp_vs_x.SetLineColor( ROOT.kBlack ) 
gr_ch2Amp_vs_x.GetXaxis().SetTitle("x [mm]")
gr_ch2Amp_vs_x.GetYaxis().SetTitle("amplitude [V]")
gr_ch2Amp_vs_x.SetTitle("")
gr_ch2Amp_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_ch2Amp_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_ch2Amp_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_ch2Amp_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_ch2Amp_vs_x.GetYaxis().SetRangeUser(0.001, max_amp)
gr_ch2Amp_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_ch2Amp_vs_x.pdf")
myC.SaveAs(outputDir+run+"_ch2Amp_vs_x.png")
myC.SaveAs(outputDir+run+"_ch2Amp_vs_x.C")


gr_timeReso_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(timeReso), np.array(ex_pos), np.array(etimeReso))
gr_timeReso_vs_x.SetMarkerStyle( 20 )
gr_timeReso_vs_x.SetMarkerColor( ROOT.kBlack )
gr_timeReso_vs_x.SetLineWidth( 2 )
gr_timeReso_vs_x.SetLineColor( ROOT.kBlack ) 
gr_timeReso_vs_x.GetXaxis().SetTitle("x [mm]")
gr_timeReso_vs_x.GetYaxis().SetTitle("#sigma_{t} [ns]")
gr_timeReso_vs_x.SetTitle("")
gr_timeReso_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_timeReso_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_timeReso_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_timeReso_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_timeReso_vs_x.GetYaxis().SetRangeUser(0.01, max_timeReso)
gr_timeReso_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_timeReso_vs_x.pdf")
myC.SaveAs(outputDir+run+"_timeReso_vs_x.png")
myC.SaveAs(outputDir+run+"_timeReso_vs_x.C")

gr_timeReso_tw_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(timeReso_tw), np.array(ex_pos), np.array(etimeReso_tw))
gr_timeReso_tw_vs_x.SetMarkerStyle( 20 )
gr_timeReso_tw_vs_x.SetMarkerColor( ROOT.kBlack )
gr_timeReso_tw_vs_x.SetLineWidth( 2 )
gr_timeReso_tw_vs_x.SetLineColor( ROOT.kBlack ) 
gr_timeReso_tw_vs_x.GetXaxis().SetTitle("x [mm]")
gr_timeReso_tw_vs_x.GetYaxis().SetTitle("#sigma_{t} [ns]")
gr_timeReso_tw_vs_x.SetTitle("")
gr_timeReso_tw_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_timeReso_tw_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_timeReso_tw_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_timeReso_tw_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_timeReso_tw_vs_x.GetYaxis().SetRangeUser(0.01, max_timeReso)
gr_timeReso_tw_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_timeReso_tw_vs_x.pdf")
myC.SaveAs(outputDir+run+"_timeReso_tw_vs_x.png")
myC.SaveAs(outputDir+run+"_timeReso_tw_vs_x.C")

gr_timeReso_rc_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(timeReso_rc), np.array(ex_pos), np.array(etimeReso_rc))
gr_timeReso_rc_vs_x.SetMarkerStyle( 20 )
gr_timeReso_rc_vs_x.SetMarkerColor( ROOT.kBlack )
gr_timeReso_rc_vs_x.SetLineWidth( 2 )
gr_timeReso_rc_vs_x.SetLineColor( ROOT.kBlack ) 
gr_timeReso_rc_vs_x.GetXaxis().SetTitle("x [mm]")
gr_timeReso_rc_vs_x.GetYaxis().SetTitle("#sigma_{t} [ns]")
gr_timeReso_rc_vs_x.SetTitle("")
gr_timeReso_rc_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_timeReso_rc_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_timeReso_rc_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_timeReso_rc_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_timeReso_rc_vs_x.GetYaxis().SetRangeUser(0.01, max_timeReso)
gr_timeReso_rc_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_timeReso_rc_vs_x.pdf")
myC.SaveAs(outputDir+run+"_timeReso_rc_vs_x.png")
myC.SaveAs(outputDir+run+"_timeReso_rc_vs_x.C")

gr_timeReso_twrc_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(timeReso_twrc), np.array(ex_pos), np.array(etimeReso_twrc))
gr_timeReso_twrc_vs_x.SetMarkerStyle( 20 )
gr_timeReso_twrc_vs_x.SetMarkerColor( ROOT.kBlack )
gr_timeReso_twrc_vs_x.SetLineWidth( 2 )
gr_timeReso_twrc_vs_x.SetLineColor( ROOT.kBlack ) 
gr_timeReso_twrc_vs_x.GetXaxis().SetTitle("x [mm]")
gr_timeReso_twrc_vs_x.GetYaxis().SetTitle("#sigma_{t} [ns]")
gr_timeReso_twrc_vs_x.SetTitle("")
gr_timeReso_twrc_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_timeReso_twrc_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_timeReso_twrc_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_timeReso_twrc_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_timeReso_twrc_vs_x.GetYaxis().SetRangeUser(0.01, max_timeReso)
gr_timeReso_twrc_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_timeReso_twrc_vs_x.pdf")
myC.SaveAs(outputDir+run+"_timeReso_twrc_vs_x.png")
myC.SaveAs(outputDir+run+"_timeReso_twrc_vs_x.C")


gr_ch2Risetime_vs_x = ROOT.TGraphErrors(nbins_X, np.array(x_pos), np.array(ch2Risetime), np.array(ex_pos), np.array(ech2Risetime))
gr_ch2Risetime_vs_x.SetMarkerStyle( 20 )
gr_ch2Risetime_vs_x.SetMarkerColor( ROOT.kBlack )
gr_ch2Risetime_vs_x.SetLineWidth( 2 )
gr_ch2Risetime_vs_x.SetLineColor( ROOT.kBlack ) 
gr_ch2Risetime_vs_x.GetXaxis().SetTitle("x [mm]")
gr_ch2Risetime_vs_x.GetYaxis().SetTitle("risetime [ns]")
gr_ch2Risetime_vs_x.SetTitle("")
gr_ch2Risetime_vs_x.GetXaxis().SetTitleSize( axisTitleSizeX )
gr_ch2Risetime_vs_x.GetXaxis().SetTitleOffset( axisTitleOffsetX )
gr_ch2Risetime_vs_x.GetYaxis().SetTitleSize( axisTitleSizeY )
gr_ch2Risetime_vs_x.GetYaxis().SetTitleOffset( axisTitleOffsetY )
gr_ch2Risetime_vs_x.GetYaxis().SetRangeUser(0.5,1.5)
gr_ch2Risetime_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_ch2Risetime_vs_x.pdf")
myC.SaveAs(outputDir+run+"_ch2Risetime_vs_x.png")
myC.SaveAs(outputDir+run+"_ch2Risetime_vs_x.C")




