//
// Created by jan on 11.04.17.
//

#include <G4CsvAnalysisManager.hh>
#include "Analysis.h"
#include "G4SystemOfUnits.hh"

Analysis::~Analysis() {
    auto analysisManager = G4CsvAnalysisManager::Instance();
    delete analysisManager; // in B4 they also delete the analysisManager, even if it is static??
}

void Analysis::Initialize() {
    auto analysisManager = G4CsvAnalysisManager::Instance();

    analysisManager->OpenFile("myAnalysis.csv"); // for some reason the file must be open during run
    analysisManager->CreateNtuple("PrimaryEnergy", "Spectrum and Dose"); // name and title
    analysisManager->CreateNtupleDColumn("PrimaryEnergy/MeV");
    analysisManager->CreateNtupleDColumn("Dose/gray");
    analysisManager->FinishNtuple();
}

void Analysis::Record(G4double energy, G4double dose){

    auto analysisManager = G4CsvAnalysisManager::Instance();

    analysisManager->FillNtupleDColumn(0, energy/MeV);
    analysisManager->FillNtupleDColumn(1, dose/gray);
    analysisManager->AddNtupleRow();
    analysisManager->Write();

}


void Analysis::Write() {
    G4CsvAnalysisManager::Instance()->Write();
}

void Analysis::Finish()
{
    Write();
    G4CsvAnalysisManager::Instance()->CloseFile();
}





