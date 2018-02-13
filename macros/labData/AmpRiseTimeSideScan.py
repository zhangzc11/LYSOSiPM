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

#run = "combine_1187_1197_407nm_side_xscan"
run = "combine_1198_1215_373nm_side_xscan"

isUVlaser = True

#run = "1031"
inputDir = "~/LabData/Zhicai_Spring2018/data/"
outputDir = "~/LabData/Zhicai_Spring2018/plots/"

os.system("mkdir -p "+outputDir)

cut = "ch1Amp>0.2 && ch1Amp<0.35 && ch2Amp > 0.002 && t1gausroot>0 && ch2LinearTime60 - t1gausroot<45 && ch2LinearTime60 - t1gausroot>40"


deltaT_mean = 42.3 #for 407nm laser
RiseTime_mean = 0.67 # for 407nm laser
max_amp = 0.40 # for 407nm laser
max_timeReso = 0.05 # for 407nm laser

if isUVlaser:
	cut = "ch1Amp>0.2 && ch1Amp<0.35 && ch2Amp > 0.002 && t1gausroot>0 && ch2LinearTime60 - t1gausroot<45 && ch2LinearTime60 - t1gausroot>40"
	deltaT_mean = 41.8 #for 373nm laser
	RiseTime_mean = 0.7 # for 407nm laser
	max_amp = 0.10 # for 373nm laser
	max_timeReso = 0.05 # for 373nm laser

x_low = -0.5
x_high = 13.5
nbins_X = 14
########################################################

file=ROOT.TFile(inputDir+run+"_ana.root")
tree=file.Get("tree")

print tree.GetEntries()

x_pos = []
timeReso = []
deltaT = []
ch2Amp = []
ch2Risetime = []

ex_pos = []
etimeReso = []
edeltaT = []
ech2Amp = []
ech2Risetime = []


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


	hist_ch2Amp = ROOT.TH1F("hist_ch2Amp_"+str(x_this),"hist_ch2Amp_"+str(x_this), 800, 0.0, 0.4)
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
	tf1_gaus_amp = ROOT.TF1("tf1_gaus_amp","gaus", 0.0, 0.4)
	tf1_gaus_amp.SetParameter(1, hist_ch2Amp.GetMean())
	hist_ch2Amp.Fit("tf1_gaus_amp","","",lowch2Amp, highch2Amp)
	myC.SaveAs(outputDir+run+"_ch2Amp_x"+str(x_this)+"mm.pdf")
	myC.SaveAs(outputDir+run+"_ch2Amp_x"+str(x_this)+"mm.png")
	myC.SaveAs(outputDir+run+"_ch2Amp_x"+str(x_this)+"mm.C")
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
		
	hist_ch2Risetime = ROOT.TH1F("hist_ch2Risetime_"+str(x_this),"hist_ch2Risetime_"+str(x_this), N_Risetime, 0.0, 5.0)
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
	highch2Risetime=hist_ch2Risetime.GetBinCenter(hist_ch2Risetime.FindLastBinAbove(int(0.2*maximumY)))
	lowch2Risetime=hist_ch2Risetime.GetBinCenter(hist_ch2Risetime.FindFirstBinAbove(int(0.1*maximumY)))
	tf1_gaus_risetime = ROOT.TF1("tf1_gaus_risetime","gaus", 0.0, 5.0)
	tf1_gaus_risetime.SetParameter(1, hist_ch2Risetime.GetMean())
	hist_ch2Risetime.Fit("tf1_gaus_risetime","","",lowch2Risetime, highch2Risetime)
	myC.SaveAs(outputDir+run+"_ch2Risetime_x"+str(x_this)+"mm.pdf")
	myC.SaveAs(outputDir+run+"_ch2Risetime_x"+str(x_this)+"mm.png")
	myC.SaveAs(outputDir+run+"_ch2Risetime_x"+str(x_this)+"mm.C")
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
gr_deltaT_vs_x.GetYaxis().SetRangeUser(41.6,42.6)
gr_deltaT_vs_x.Draw("AP")
myC.SaveAs(outputDir+run+"_deltaT_vs_x.pdf")
myC.SaveAs(outputDir+run+"_deltaT_vs_x.png")
myC.SaveAs(outputDir+run+"_deltaT_vs_x.C")

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
gr_ch2Amp_vs_x.GetYaxis().SetRangeUser(0.0, max_amp)
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







