#include "TROOT.h" 
#include "iostream"
#include <iomanip>
#include "TH1.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TPad.h"
#include "stdlib.h"
#include "TStyle.h"
#include "TH1D.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TRandom2.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TFile.h"
#include "string.h"
#include "TChain.h"
#include "TTree.h"
#include "TArrow.h"
#include "TGaxis.h"
#include "TLatex.h"
#include "TBufferFile.h"
#include "TLorentzVector.h"
#include "THStack.h"
#include <math.h>

using namespace std;

void surface_solar_radiation()
{
    // Input file directory
    string inDir = "../rootfiles/";
    // Input file
    string inFile = "solar_radiation_data.root";


    ///////////////// Load Data From Tree ///////////////////////
    TFile *input = new TFile((inDir + inFile).c_str(), "read");
    TTree *data_tree = (TTree*)input->Get("solar_radiation_data");

    double x, y, errX, errY;
    int entries = data_tree->GetEntries();

    data_tree->SetBranchAddress("time", &x);
    data_tree->SetBranchAddress("radiation", &y);
    data_tree->SetBranchAddress("errorX", &errX);
    data_tree->SetBranchAddress("errorY", &errY);



    //////////////////// Preparing Canvas ///////////////////////

    TCanvas *c1 = new TCanvas("c1", "", 800, 500);
    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();

    TGraphErrors *g = new TGraphErrors();
    g->SetTitle("Solar Radiation");
    g->GetXaxis()->SetTitle("Time (Hrs)");
    g->GetYaxis()->SetTitle("Radiation ( #frac{kW}{m^{2}})");

    for (int i = 0; i < entries; i++) {
        data_tree->GetEntry(i);
        int n = g->GetN();
        g->SetPoint(n, x, y);
        g->SetPointError(n, errX, errY);
    }
    g->Draw("AC"); 

    TF1 *pol4 = new TF1("f1", "pol4", 8, 16);
    pol4->SetLineWidth(4);
    g->Fit(pol4, "R");

    TLegend *leg1 = new TLegend(0.6278195,0.7031579,0.8671679,0.8315789);
    leg1->SetBorderSize(0);
    leg1->AddEntry(g, "Measured Radiation", "l");
    leg1->AddEntry(pol4, "4th Order Poly", "l");
    leg1->Draw();
}
