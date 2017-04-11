#include <G4VModularPhysicsList.hh>
#include <QBBC.hh>

#include <G4VisExecutive.hh>
#include <G4UImanager.hh>
#include <G4UIExecutive.hh>

#include "ActionInitialization.h"
#include "DetectorConstruction.h"
#include "G4CsvAnalysisManager.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4MULTITHREADED
#define RUNMANAGER G4MTRunManager
#else
#define RUNMANAGER G4RunManager
#endif

void visualize(int argc, char** argv) {
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    G4VisManager *visManager = new G4VisExecutive;
    visManager->Initialize();
    G4UImanager *uiManager = G4UImanager::GetUIpointer();

    uiManager->ApplyCommand("/control/execute init.mac");

    ui->SessionStart();
    delete ui;
}

void batch_run(RUNMANAGER* runManager, RunParameters& runParameters) {

    double E, E0, dE, Emax;
    E0 = 100*keV;
    dE = 100*keV;
    Emax = 6*MeV;

    for (E=E0; E<=Emax; E+=dE) {
        runParameters.primaryEnergy = E;
        runManager->BeamOn(runParameters.nEvent);
    }

}

RUNMANAGER* GetRunManager() {
#ifdef G4MULTITHREADED
    auto runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
#else
    auto runManager = new G4RunManager;
#endif
    return runManager;
}

int main(int argc, char** argv) {
    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    G4MTRunManager* runManager = GetRunManager();

    RunParameters runParameters = RunParameters();
    runParameters.geometryPath = "geometry.gdml";
    runParameters.primaryEnergy = 6*MeV;
    runParameters.nEvent = 100000;


    DetectorConstruction* detectorConstruction = new DetectorConstruction(runParameters);
    runManager->SetUserInitialization(detectorConstruction);

    G4VModularPhysicsList* physicsList = new QBBC;
    physicsList->SetVerboseLevel(0);
    runManager->SetUserInitialization(physicsList);

    ActionInitialization* actionInitialization = new ActionInitialization(runParameters);
    runManager->SetUserInitialization(actionInitialization);

    runManager->Initialize();

    auto analysisManager = G4CsvAnalysisManager::Instance();
    analysisManager->OpenFile("myAnalysis.csv"); // for some reason the file must be open during run
    analysisManager->CreateNtuple("PrimaryEnergy", "Spectrum and Dose"); // name and title
    analysisManager->CreateNtupleDColumn("PrimaryEnergy/MeV");
    analysisManager->CreateNtupleDColumn("Dose/gray");
    analysisManager->FinishNtuple();

    if (argc == 2) {
        visualize(argc, argv);
    } else {
        batch_run(runManager, runParameters);
    }

    analysisManager->Write();
    analysisManager->CloseFile();

    delete analysisManager; // in B4 they also delete the analysisManager, even if it is static??
    delete runManager;

    return 0;
}