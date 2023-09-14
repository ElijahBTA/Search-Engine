//
// Created by Elijah  Posiulai on 11/28/22.
//

#ifndef FINALPROJEXAMPLES_DOCUMENTPARSERR_H
#define FINALPROJEXAMPLES_DOCUMENTPARSERR_H

#include "IndexHandlerr.h"
#include "DocumentContents.h"
#include <unordered_set>

class DocumentParserr {
private:

    int docID;
    //needs to be pointer so that all classes are talking to the same IndexHandler object
    IndexHandlerr *tree;
    //unorded set to make finding things fast O(1)
    unordered_set <string> stringSet;


//htkkb
public:
    DocumentParserr() = default;
    //Constucter that gets passed in the Indexhandler by Interface so that everything is on the same page
    DocumentParserr(IndexHandlerr* &t) : tree{t}, docID{0} {}
    //these are the two functions below that are used for creating index  and reading from all json files
    void testReadJsonFile(const string &fileName);
    void testFileSystem(const string &path);
    //function belwo contains stop words
    void readStopWords(const string& path);

};


#endif //FINALPROJEXAMPLES_DOCUMENTPARSERR_H
