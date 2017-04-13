//
// Created by jan on 11.04.17.
//

#include <G4CsvAnalysisManager.hh>
#include <assert.h>
#include "Analysis.h"
#include "G4SystemOfUnits.hh"

Analysis::~Analysis() {
    // in B4 they also delete the analysisManager, even if it is singleton??
    auto analysisManager = G4CsvAnalysisManager::Instance();
    delete analysisManager;
}

void Analysis::Initialize() {
    auto am = G4CsvAnalysisManager::Instance();

    am->OpenFile("myAnalysis.csv"); // for some reason the file must be open during run
    std::string tupleName, tupleTitle;
    am->CreateNtuple(tupleName="Results", tupleTitle="Primary Energy and eDep"); // name and title
    am->CreateNtupleDColumn("PrimaryEnergy/MeV");
    am->CreateNtupleSColumn("Detector");
    am->CreateNtupleIColumn("Number of Events");

    am->CreateNtupleDColumn("mean eDep/MeV");
    am->CreateNtupleDColumn("std eDep/MeV");
    am->FinishNtuple();
}

void Analysis::Record(G4double energy, std::string detname, G4int nEvents, G4double eDep, G4double eDep2)
{

    auto am = G4CsvAnalysisManager::Instance();

    G4double std_one_gamma = Std(eDep, eDep2, nEvents);  // standard deviation of energy deposit of a single gamma
    G4double std = std_one_gamma / sqrt(nEvents);  // standard deviation of estimated mean energy deposit of one gamma

    am->FillNtupleDColumn(0, energy/MeV);
    am->FillNtupleSColumn(1, detname);
    am->FillNtupleIColumn(2, nEvents);
    am->FillNtupleDColumn(3, Mean(eDep, nEvents) / MeV);
    am->FillNtupleDColumn(4, std / MeV);

    am->AddNtupleRow();
    am->Write();

}

G4double Analysis::Mean(G4double eDep, G4int nEvents) {return eDep/nEvents;}

G4double Analysis::Std(G4double eDep, G4double eDep2, G4int nEvents) {
    G4double EX, E2X, var;
    EX = eDep / nEvents;       // E X
    E2X = eDep2 / nEvents; // E (X^2)
    var = E2X - EX*EX;
    assert(var >= 0);
    return sqrt(var);
}
//
//void Analysis::Write() {
//    G4CsvAnalysisManager::Instance()->Write();
//}

void Analysis::Finish()
{
//    Write();
    G4CsvAnalysisManager::Instance()->CloseFile();

}





