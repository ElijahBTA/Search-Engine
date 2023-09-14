//
// Created by Elijah  Posiulai on 12/1/22.
//

#ifndef FINALPROJEXAMPLES_QUERYPROCESSOR_H
#define FINALPROJEXAMPLES_QUERYPROCESSOR_H
#include "IndexHandlerr.h"
#include "DocumentContents.h"
#include <vector>
#include "porter2_stemmer.h"
#include <cmath>



class QueryProcessor {
private:

    IndexHandlerr *findingDocs;
    vector<DocumentContents> PersonsDocs;
    vector<DocumentContents> OrgsDocs;
    vector<DocumentContents> WordsDocs;
    //this vector of results holds the results of the docs that were found with the users query
    vector<DocumentContents> results;
    vector <string> Query;

public:
    QueryProcessor(IndexHandlerr*& findingDocs_) : findingDocs{findingDocs_} {}
    //pasrer function does all the magic
    void parser(const string &);
    void inputQuery();
    //calcWeight function helps me with relevancy
    void calcWeightP(const string &);
    void calcWeightW(const string &);
    void calcWeightO(const string &);
    //this fucntion is used to take into account the spaces
    vector<size_t> removeSpaces(string, string);

    static bool weightIntersection(const DocumentContents&, const DocumentContents&);



};


#endif //FINALPROJEXAMPLES_QUERYPROCESSOR_H
