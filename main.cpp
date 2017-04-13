#include <G4VModularPhysicsList.hh>
#include <QBBC.hh>

#include <G4VisExecutive.hh>
#include <G4UImanager.hh>
#include <G4UIExecutive.hh>
#include <RunContext.h>

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
    //runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
#else
    auto runManager = new G4RunManager;
#endif
    return runManager;
}

int main(int argc, char** argv) {
    G4Random::setTheEngine(new CLHEP::RanecuEngine);

    RUNMANAGER* runManager = GetRunManager();


    Analysis analysis;
    analysis = Analysis();

    RunParameters runParameters = RunParameters();
    runParameters.geometryPath = "geometry.gdml";
    runParameters.primaryEnergy = 6*MeV;
    runParameters.nEvent = 10000;
    runParameters.nThreads = 4; //G4Threading::G4GetNumberOfCores();

    G4bool validate = false;
    G4GDMLParser parser;
    parser.Read(runParameters.geometryPath, validate);

    RunContext runContext = RunContext(analysis, runParameters, parser);


    DetectorConstruction* detectorConstruction = new DetectorConstruction(runContext);
    runManager->SetUserInitialization(detectorConstruction);

    G4VModularPhysicsList* physicsList = new QBBC;
    physicsList->SetVerboseLevel(0);
    runManager->SetUserInitialization(physicsList);

    ActionInitialization* actionInitialization = new ActionInitialization(runContext);
    runManager->SetUserInitialization(actionInitialization);
#ifdef G4MULTITHREADED
    runManager->SetNumberOfThreads(runParameters.nThreads);
#endif
    runManager->Initialize();

    analysis.Initialize();

    if (argc == 2) {
        visualize(argc, argv);
    } else {
        batch_run(runManager, runParameters);
    }

    analysis.Finish();

    delete runManager;

    return 0;
}