//
// Created by Elijah  Posiulai on 11/28/22.
//

#include "DocumentParserr.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <iomanip>
#include <unordered_set>
#include "porter2_stemmer.h"


// RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

using namespace std;

void DocumentParserr::testReadJsonFile(const string &fileName) {

    // open an ifstream on the file of interest and check that it could be opened.
    ifstream input(fileName);
    if (!input.is_open()) {
        cerr << "cannot open file: " << fileName << endl;
        return;
    }


    // Create a RapidJSON IStreamWrapper using the file input stream above.
    rapidjson::IStreamWrapper isw(input);

    // Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    rapidjson::Document d;
    d.ParseStream(isw);

    docID++;
    // This accesses the -title- element in the JSON. Since the value
    //  associated with title is a string (rather than
    //  an array or something else), we call the GetString()
    //  function to return the actual title of the article
    //  as a c-string.
    string val = d["title"].GetString();
    string authorss = d["author"].GetString();
    string publishdate = d["published"].GetString();
    string name = d["text"].GetString();

//used my construcer so that every document read in all the title,publishdate, etc.. is all set
    DocumentContents DocMapping(val, publishdate, authorss, name);








//feeling up my words tree
    int nodesinWord;
    int WordsinDoc = 0;
    char copy[name.size() + 1];
    strcpy(copy, name.c_str());
    for (int i = 0; i < name.size(); i++) {
        copy[i] = tolower(copy[i]);
    }

    string delim = "1234567890.,/;:?! ";
    char *pch = strtok(copy, delim.c_str());


    //inserting the words into my word tree if it is not a stop word tokenziing here
    while (pch != nullptr) {
        string str(pch);
        //if the word is not found in the stop words then stem it and add it to tree
        if (stringSet.find(str) == stringSet.end()) {
            WordsinDoc++;
            nodesinWord++;
            //stemming
            Porter2Stemmer::trim(str);
            Porter2Stemmer::stem(str);
            tree->insertWords(str, docID);
        }

        pch = strtok(nullptr, delim.c_str());
    }
    DocMapping.setNumofWordsinFile(WordsinDoc);
    tree->setTotalNodesinWords(nodesinWord);

//enters entities in order to find persons then gets array
    auto persons = d["entities"]["persons"].GetArray();


    // We iterate over the Array returned from the line above.
    //  Each element kind of operates like a little JSON DocumentContents
    //  object in that you can use the same subscript notation
    //  to access particular values.

    //filling person tree
    for (auto &p: persons) {
        string name = p["name"].GetString();
        tree->insertPersons(name, docID);
    }

    //getting orgs names
    auto orgs = d["entities"]["organizations"].GetArray();


    //inserting orgs tree
    for (auto &s: orgs) {
        string namefororg = s["name"].GetString();
        tree->insertOrgs(namefororg, docID);
    }

    tree->insertDocs(docID, DocMapping);


    input.close();
}



void DocumentParserr::testFileSystem(const string &path) {
// recursive_director_iterator used to "access" folder at parameter -path-
    // we are using the recursive iterator so it will go into subfolders.
    // see: https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
    auto it = filesystem::recursive_directory_iterator(path);

    // loop over all the entries.

    for (const auto &entry : it)
    {
        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
        {

            testReadJsonFile(entry.path().string());

        }
    }
}

void DocumentParserr::readStopWords(const string &path) {
    ifstream stopWords(path);
    string stop;
    if(!stopWords){
        cout << " File of Stopwords did not open" << endl;
    }
    while(!stopWords.eof()){
        getline(stopWords,stop);
        stringSet.insert(stop);
    }
}




