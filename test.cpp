#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "AvlTree.h"
#include <vector>

// add includes


TEST_CASE("Check that DSList works", "[DSList]")
{
    //making my avl tree to hold a key and the documents name
    AvlTree<string,vector<string>> treeTest;

//testing funcitons of AvlTree below
    treeTest.insert("hey",{"d1"});
    treeTest.insert("hey",{"d1"});

    REQUIRE(treeTest.contains("hey")==true);
    treeTest.makeEmpty();
    REQUIRE(treeTest.isEmpty()==true);
    treeTest.insert("hello",{"d3"});
    REQUIRE(treeTest.isEmpty()==false);
    treeTest.insert("wyd",{"d2"});
    treeTest.insert("wyd",{"d1"});
    treeTest.insert("wassup",{"d1"});
    REQUIRE(treeTest.contains("wyd")==true);
    REQUIRE(treeTest.contains("wassup")==true);
    REQUIRE(treeTest.contains("hello")==true);
    vector<string> docss = treeTest.find("hello");

    treeTest.makeEmpty();
    REQUIRE(treeTest.contains("wyd")==false);
    REQUIRE(treeTest.isEmpty()==true);
    treeTest.prettyPrintTree();







}

