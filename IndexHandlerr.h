

#ifndef FINALPROJEXAMPLES_INDEXHANDLERR_H
#define FINALPROJEXAMPLES_INDEXHANDLERR_H
#include "AvlTree.h"
#include "DocumentContents.h"
#include "iostream"
#include "fstream"

#include <unordered_map>

class IndexHandlerr {
private:
// my main three trees that i will be using and the first int is the docId and second int is occurances in unorderedmap
    AvlTree<string, std::unordered_map<int, int>> persons;
    AvlTree<string, std::unordered_map<int, int>> organizations;
    AvlTree<string, std::unordered_map<int, int>> words;
    vector<int> intIds;
    int totalNodesinWords;


    std::unordered_map<int, DocumentContents> documents;
public:
    //for the insert function i utilize the insert function i have in AvlTree.h
    void insertPersons(string&, int);
    void insertOrgs(string&, int);
    void insertWords(string&, int);
    void insertDocs(int, DocumentContents&);

    //this return the unordered map which then i have access to the second which is the occurance
    unordered_map<int,int> getOcurrPerson(const string&);
    unordered_map<int,int> getOcurrOrgs(const string&);
    unordered_map<int,int> getOcurrWords(const string&);
    int getSizeofDocuments();
    DocumentContents& getDocument(int);
    //retunr the vecotr of documents assoiciated with that string good for when query
    vector<DocumentContents> getDocumentsForPersons(const string &);
    vector<DocumentContents> getDocumentsForWords(const string &);
    vector<DocumentContents> getDocumentsForOrgs(const string &);

    //print functions was mean for debugging and to see if my trees were being filled
    void printP();
    void printW();
    void printO();
    bool contains(const string &);
    void clearindex();
    int getSizeofWordsTree();
    void setTotalNodesinWords(int);
    int getTotalNodesinWords();

    //below is for reading/writing to persistence
    void writePersistenceWords(string);
    void writePersistencePersons(string);
    void writePersistenceOrgs(string);
    void writeDocuments(string);
    void readPersistenceDocuments(string);
    void readPersistenceWords(string);
    void readPersistencePersons(string);
    void readPersistenceOrgs(string);




};


#endif //FINALPROJEXAMPLES_INDEXHANDLERR_H
