//
// Created by jan on 12.04.17.
//


#include <Scoring.h>
#include <G4Box.hh>
#include <G4NistManager.hh>
#include "util.h"
#include "catch.h"



TEST_CASE( "Scoring", "[Scoring]" ) {
    Scoring s = Scoring();
    // Get nist material manager
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* material1 = nist->FindOrBuildMaterial("G4_WATER");

    G4Box* solid1 = new G4Box("solid1", 1,2,3);
    G4LogicalVolume* logic1 = new G4LogicalVolume(solid1, material1, "logic1");
    s.RegisterScorer(logic1, "dose1");
    REQUIRE(s.GetNumberOfEvents() == 0);
    REQUIRE(s.IsWatched(logic1));

    REQUIRE(s.GetRunScore("dose1") == 0);
    s.AddEventScore(logic1, 12);
    s.FinishEvent();
    REQUIRE(s.GetNumberOfEvents() == 1);
    REQUIRE(s.GetNumberOfEvents() == 1);

    REQUIRE(s.GetRunScore("dose1") == 12);
    REQUIRE(s.GetRunScore2("dose1") == 12*12);

    s.FinishEvent();
    REQUIRE(s.GetRunScore("dose1") == 12);
    REQUIRE(s.GetRunScore2("dose1") == 12*12);
    REQUIRE(s.GetNumberOfEvents() == 2);

    // another scorer watching the same volume
    s.RegisterScorer(logic1, "dose1b");
    REQUIRE(s.GetRunScore("dose1") == 12);
    REQUIRE(s.GetRunScore("dose1b") == 0);
    s.FinishEvent();
    REQUIRE(s.GetRunScore("dose1") == 12);
    REQUIRE(s.GetRunScore("dose1b") == 0);
    REQUIRE(s.GetNumberOfEvents() == 3);

    s.AddEventScore(logic1, 4);
    s.FinishEvent();
    REQUIRE(s.GetRunScore("dose1") == 16);
    REQUIRE(s.GetRunScore2("dose1") == 12*12 +4*4);

    REQUIRE(s.GetRunScore("dose1b") == 4);

    // another volume
    G4Box* solid2 = new G4Box("solid2", 1,2,3);
    G4LogicalVolume* logic2 = new G4LogicalVolume(solid1, material1, "logic2");
    s.RegisterScorer(logic2, "dose2");

    REQUIRE(s.GetRunScore("dose2") == 0);
    s.AddEventScore(logic1, 4);
    s.FinishEvent();
    REQUIRE(s.GetRunScore("dose2") == 0);

    s.ResetRun();
    REQUIRE(s.GetNumberOfEvents() == 0);
    REQUIRE(s.GetRunScore("dose1b") == 0);
    REQUIRE(s.GetRunScore2("dose1b") == 0);

    // scorer watching two volumes
    s.RegisterScorer(logic1, "dose12");
    s.RegisterScorer(logic2, "dose12");
    s.AddEventScore(logic1, 1);
    s.FinishEvent();
    REQUIRE(s.GetRunScore("dose12") == 1);
    s.AddEventScore(logic2, 2);
    s.FinishEvent();
    REQUIRE(s.GetRunScore("dose12") == 3);
    REQUIRE(s.GetRunScore("dose1") == 1);
    REQUIRE(s.GetRunScore("dose1b") == 1);
    REQUIRE(s.GetRunScore("dose2") == 2);

//    s.AddEventScore(vol1, 1);

}