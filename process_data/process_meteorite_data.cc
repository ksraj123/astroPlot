// Dataset Provided by NASA on Kaggle - https://www.kaggle.com/nasa/meteorite-landings

#include "TROOT.h" 
#include <iomanip>
#include "TFile.h"
#include "string.h"
#include "TTree.h"
#include <cmath>
#include <climits>
#include <iostream>
#include <fstream>

using namespace std;

void process_meteorite_data()
{
    string type;
    bool fallen;
    int id, year;
    double mass, longitude, latitude;

    fstream file;
    file.open("raw_data/nasa_meteorite_landing_raw.txt", ios::in);

    TFile *output = new TFile("../rootfiles/meteorite_data.root", "recreate");
    TTree *meteorite_data = new TTree("meteorite_data", "meteorite_data");

    meteorite_data->Branch("id", &id, "id/I");
    meteorite_data->Branch("year", &year, "year/I");
    meteorite_data->Branch("type", &type, "type/C");
    meteorite_data->Branch("mass", &mass, "mass/D");
    meteorite_data->Branch("fallen", &fallen, "fallen/O");
    meteorite_data->Branch("latitude", &latitude, "latitude/D");
    meteorite_data->Branch("longitude", &longitude, "longitude/D");

    while(1) {
        string temp, location;
        file >> id >> type >> mass >> temp >> year >> location;
        latitude = stod(location.substr(1, location.find(',')));
        longitude = stod(location.substr(location.find(',') + 1));
        fallen = temp.compare("Fell") == 0;

        if (mass == -99999)
            mass = INT_MIN;
        if (longitude == -99999)
            longitude = INT_MIN;
        if (latitude == -99999)
            latitude = INT_MIN;
        if (year == -99999)
            year = INT_MIN;
        
        cout << "\t" << id << "\t" << type << "\t" << mass << "\t" << fallen << "\t" << year << "\t" << latitude << "\t" << longitude << endl;

        if (file.eof()) break;

        meteorite_data->Fill();
    }

    output->Write();
    output->Close();
    file.close();
}