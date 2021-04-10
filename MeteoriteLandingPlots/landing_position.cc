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

#include "headers/Meteorite.h"

using namespace std;

void landing_position()
{
    // Input file directory
    string inDir = "../rootfiles/";
    // Input file
    string inFile = "meteorite_data.root";


    ///////////////// Load Data From Tree ///////////////////////
    TFile *input = new TFile((inDir + inFile).c_str(), "read");
    TTree *data_tree = (TTree*)input->Get("meteorite_data");

    Meteorite *temp = new Meteorite();
    data_tree->SetBranchAddress("id", &temp->id);
    data_tree->SetBranchAddress("type", &temp->type);
    data_tree->SetBranchAddress("year", &temp->year);
    data_tree->SetBranchAddress("mass", &temp->mass);
    data_tree->SetBranchAddress("fallen", &temp->fallen);
    data_tree->SetBranchAddress("latitude", &temp->latitude);
    data_tree->SetBranchAddress("longitude", &temp->longitude);

    vector<Meteorite> meteorites;
    for (int i = 0; i < data_tree->GetEntries(); i++) {
        data_tree->GetEntry(i);
        meteorites.push_back(new Meteorite(temp));
        // cout << meteorites[i].id << "\t" << meteorites[i].type << "\t" << meteorites[i].mass << "\t" << meteorites[i].fallen << "\t" << meteorites[i].year << "\t" << meteorites[i].latitude << "\t" << meteorites[i].longitude << endl;
    }



    //////////////////// Preparing Canvas ///////////////////////


    TCanvas *c1 = new TCanvas("c1", "", 800, 500);

    TMultiGraph *graph = new TMultiGraph();

    TGraph *light = new TGraph();
    TGraph *medium = new TGraph();
    TGraph *heavy = new TGraph();

    for (Meteorite &m : meteorites)
    {
        if(m.longitude > INT_MIN && m.latitude > INT_MIN && m.mass > INT_MIN)
        {
            if (m.mass > 100000)
            {
                heavy->SetPoint(heavy->GetN(), m.latitude, m.longitude);
            }
            else if (m.mass > 10000)
            {
                medium->SetPoint(medium->GetN(), m.latitude, m.longitude);
            } 
            else
            {
                light->SetPoint(light->GetN(), m.latitude, m.longitude);
            }
        }
    }
        
    light->SetMarkerStyle(2);
    light->SetMarkerColor(kBlack);
    medium->SetMarkerStyle(43);
    medium->SetMarkerColor(kBlue);
    heavy->SetMarkerStyle(43);
    heavy->SetMarkerColor(kRed);

    graph->Add(light, "p");
    graph->Add(medium, "p");
    graph->Add(heavy, "p");
    
    graph->SetTitle("Meteorite Landing Positions (1600 - 2020)");
    graph->GetXaxis()->SetTitle("Latitute");
    graph->GetYaxis()->SetTitle("Longitude");
    graph->Draw("AP");
    graph->GetXaxis()->SetRangeUser(-90, 90);
    graph->GetYaxis()->SetRangeUser(-180, 180);
    graph->Draw("AP");

    TBox *asia = new TBox(1, -170, 80, 25);
    asia->SetFillColorAlpha(kTeal, 0.1);
    asia->Draw();

    TLegend *leg1 = new TLegend(0.1428571,0.48,0.3308271,0.6947368);
    leg1->SetBorderSize(2);
    leg1->AddEntry(light, "Light Meteorites", "p");
    leg1->AddEntry(medium, "Medium Meteorites", "p");
    leg1->AddEntry(heavy, "Heavy Meteorites", "p");
    leg1->AddEntry(asia, "Asia", "f");
    leg1->Draw();

    c1->Update();
}
