//
// Created by Elijah  Posiulai on 12/1/22.
//

#include "QueryProcessor.h"


void QueryProcessor::parser(const string &query) {
    char copy[query.size() + 1];
    strcpy(copy, query.c_str());

    string delim = " ";
    char* pch = strtok(copy,delim.c_str());


//tokenizing and parsing the query with if else statements determed on what is read from query
    while (pch != nullptr) {
        string str(pch);
        auto person_index = str.find("PERSON:");
        //this case takes into account a person
        if (person_index != string::npos) {
            string term = str.substr(7);
            //replaces the - with spaces as specfied you need to enter query with - instead of spaces
            vector<size_t> positions = removeSpaces(term, "-");
            for (unsigned long position : positions) {
                term[position] = ' ';
            }


            calcWeightP(term);
            auto mapping=findingDocs->getDocumentsForPersons(term);

            //sorts documents based on the weight
            sort(mapping.begin(), mapping.end());

            if (!mapping.empty()) {

                if (results.empty()) {
                    results = mapping;
                } else {
                    //this part sets intersection of documents
                    auto it = set_intersection(results.begin(), results.end(),
                                               mapping.begin(), mapping.end(), results.begin());
                    results.resize(it - results.begin());
                }
            }




        } else if (str.find("ORG:") != string::npos) {
            //this code below does the same thing as person but getDocs for Orgs
            string term = str.substr(4);

            vector<size_t> positions = removeSpaces(term, "-");
            for (unsigned long position : positions) {
                term[position] = ' ';
            }
            calcWeightO(term);
            auto mapping=findingDocs->getDocumentsForOrgs(term);

            sort(mapping.begin(), mapping.end());

            if (!mapping.empty()) {
                if (results.empty()) {
                    results = mapping;
                } else {
                    auto it = set_intersection(results.begin(), results.end(),
                                               mapping.begin(), mapping.end(), results.begin());
                    results.resize(it - results.begin());
                }
            }



        } else if (str[0] == '-') {
        // this is the case of not wanting the documents of a word
            string term = str.substr(1);
            //stemming
            Porter2Stemmer::trim(term);
            Porter2Stemmer::stem(term);
            // grab docs for word
            calcWeightW(term);
            auto mapping=findingDocs->getDocumentsForWords(term);

            sort(mapping.begin(), mapping.end());
            if (!mapping.empty()) {

                if (results.empty()) {
                    results = mapping;
                } else {
                    //this gets rid of the documents they dont want
                    for (auto tmp: mapping) {
                        auto itr = std::find(results.begin(), results.end(), tmp);
                        if (itr != results.end()) {
                            results.erase(itr);
                        }
                    }

                }
            }
        } else {
            //this is the case if it is just a word they are wanting
            string term = str;
            Porter2Stemmer::trim(term);
            Porter2Stemmer::stem(term);
            // grab docs for word
            calcWeightW(term);
            auto mapping=findingDocs->getDocumentsForWords(term);

            sort(mapping.begin(), mapping.end());
            if (!mapping.empty()) {

                if (results.empty()) {
                    results = mapping;
                } else {
                    auto it = set_intersection(results.begin(), results.end(),
                                               mapping.begin(), mapping.end(), results.begin());
                    results.resize(it - results.begin());
                }
            }
        }


        pch = strtok(nullptr,delim.c_str());
    }

    sort(results.begin(), results.end(), weightIntersection);

//making it sure that it gives at most only top 15 articles
    if(results.size()>15){
        results.resize(15);
    }
    //this prints out all the documents associated with the query
    for (size_t i =0; i<results.size(); i++) {
        cout << "Article " << i+1 << ": " << results.at(i).getTitle() << endl;
        cout << "Publication: " << results.at(i).getPublication() << endl;
        cout << "Author: " << results.at(i).getAuthor() << endl;
    }
    //this gives the option to get the text of whatever document
    int userArticle=0;

    cout << "Select what article you would like the text for 1-" << results.size() <<
    " or if not type 0 " << endl;
    cin >> userArticle;
   if(userArticle!=0){
       cout << "Article text is " << endl;
       cout << results.at(userArticle-1).getText() << endl;
   }

}

void QueryProcessor::calcWeightP(const string &term) {
    auto map=findingDocs->getOcurrPerson(term);

    double Idf = log2(findingDocs->getSizeofDocuments()/map.size());

    for(auto itr:map){
        int doc=findingDocs->getDocument(itr.first).getNumofDocs();
        double Tf = itr.second/(double) doc;
        double weightTfIdf=Tf*Idf;
        findingDocs->getDocument(itr.first).setWeight(weightTfIdf);
    }



}

void QueryProcessor::calcWeightW(const string &terms) {
    auto map=findingDocs->getOcurrWords(terms);

    double Idf = log2(findingDocs->getSizeofDocuments()/map.size());

    for(auto itr:map){
        int numDocs = findingDocs->getDocument(itr.first).getNumofDocs();
        double Tf = itr.second / (double) numDocs;
        double weightTfIdf=Tf*Idf;
        findingDocs->getDocument(itr.first).setWeight(weightTfIdf);
    }
}

void QueryProcessor::calcWeightO(const string &termss) {
    auto map=findingDocs->getOcurrOrgs(termss);

    double Idf = log2(findingDocs->getSizeofDocuments()/map.size());

    for(auto itr:map){
        int doc=findingDocs->getDocument(itr.first).getNumofDocs();
        double Tf = itr.second/(double) doc;
        double weightTfIdf=Tf*Idf;
        findingDocs->getDocument(itr.first).setWeight(weightTfIdf);
    }
}

bool QueryProcessor::weightIntersection(const DocumentContents &lhs, const DocumentContents &rhs) {
    return lhs.getWeight() > rhs.getWeight();
}

void QueryProcessor::inputQuery() {
    cout << "If wanting to put more than one name for PERSON or ORG put a - instead of a space " << endl;
    //for example sales PERSON:elijah-posiulai
    cout << "Enter query: ";
    string query;
    cin.ignore();
    getline(cin, query);
    parser(query);
}

vector<size_t> QueryProcessor::removeSpaces(string str, string sub) {
    vector<size_t> positions; // holds all the positions that sub occurs within str
    size_t pos = str.find(sub, 0);
    while(pos != string::npos)
    {
        positions.push_back(pos);
        pos = str.find(sub,pos+1);
    }

    return positions;
}
