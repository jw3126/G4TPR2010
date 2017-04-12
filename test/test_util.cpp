//
// Created by jan on 12.04.17.
//

#include "util.h"
#include "catch.h"



TEST_CASE( "HasKey", "HasKey" ) {
    auto obj = std::map<int, double>();

    REQUIRE( !HasKey(obj, 1) );
    REQUIRE( !HasKey(obj, 1) );
    obj[1] = 2.;
    REQUIRE( HasKey(obj, 1) );
    REQUIRE( !HasKey(obj, 2) );

}

TEST_CASE( "HasElement", "HasElement" ) {
    auto obj = std::vector<int>();

    REQUIRE( !HasElement(obj, 1) );
    REQUIRE( !HasElement(obj, 1) );
    obj.push_back(2);
    REQUIRE( !HasElement(obj, 1) );
    obj.push_back(1);
    REQUIRE( HasElement(obj, 1) );
    obj.push_back(2);
    REQUIRE( HasElement(obj, 1) );
    obj.push_back(1);
    REQUIRE( HasElement(obj, 1) );
}