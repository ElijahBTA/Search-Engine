//
// Created by Elijah  Posiulai on 11/29/22.
//

#include "IndexHandlerr.h"


void IndexHandlerr::insertDocs(int key, DocumentContents& docMap) {
   documents.insert({key,docMap});
}

void IndexHandlerr::insertPersons(string &person, int docID) {
    if (persons.contains(person)) {
        persons.find(person)[docID]++;
    } else {
        persons.insert(person, {{docID, 1}});
    }
}

void IndexHandlerr::insertOrgs(string &org, int docIDs) {

    if (organizations.contains(org)) {
        organizations.find(org)[docIDs]++;
    } else {
        organizations.insert(org, {{docIDs, 1}});
    }
}

void IndexHandlerr::insertWords(string &wordss, int Docid) {

    if (words.contains(wordss)) {
        words.find(wordss)[Docid]++;
    } else {
        words.insert(wordss, {{Docid, 1}});
    }
}

void IndexHandlerr::printP() {
    persons.prettyPrintTree();
}

void IndexHandlerr::printW() {
    words.prettyPrintTree();
}

void IndexHandlerr::printO() {
    organizations.prettyPrintTree();
}

bool IndexHandlerr::contains(const string &datas) {
   return words.contains(datas);

}

DocumentContents& IndexHandlerr::getDocument(int id) {
    return documents[id];
}

vector<DocumentContents> IndexHandlerr::getDocumentsForPersons(const string &DocsForP) {
    //my find function returns an unordred map and from there i push back the documents at first into a vector
    auto map = persons.find(DocsForP);
    vector<DocumentContents> temp;
    for (auto itr : map) {
        temp.push_back(documents[itr.first]);
    }
    return temp;
}

vector<DocumentContents> IndexHandlerr::getDocumentsForWords(const string &wordss) {
    auto map = words.find(wordss);
    vector<DocumentContents> temp;
    for (auto itr : map) {
        temp.push_back(documents[itr.first]);
    }
    return temp;
}

vector<DocumentContents> IndexHandlerr::getDocumentsForOrgs(const string &orgss) {

    auto map = organizations.find(orgss);
    vector<DocumentContents> temp;
    for (auto itr : map) {
        temp.push_back(documents[itr.first]);
    }
    return temp;
}

unordered_map<int, int> IndexHandlerr::getOcurrPerson(const string &OcurrP) {
    auto map=persons.find(OcurrP);
    return map;
}

unordered_map<int, int> IndexHandlerr::getOcurrOrgs(const string &OcurrO) {
    auto map=organizations.find(OcurrO);
    return map;
}

unordered_map<int, int> IndexHandlerr::getOcurrWords(const string &OcurrW) {
    auto map=words.find(OcurrW);
    return map;
}

int IndexHandlerr::getSizeofDocuments() {
    return documents.size();
}

void IndexHandlerr::clearindex() {
    persons.makeEmpty();
    words.makeEmpty();
    organizations.makeEmpty();
    documents.clear();
}

int IndexHandlerr::getSizeofWordsTree() {

}

void IndexHandlerr::setTotalNodesinWords(int total) {
totalNodesinWords+=total;
}

int IndexHandlerr::getTotalNodesinWords() {
    return totalNodesinWords;
}

void IndexHandlerr::writePersistenceWords(string fileName) {
    //all writing persistnece function use same code just changes the tree
    ofstream myfile(fileName);

    words.setCurr();
    while (words.hasNext()) {
        auto docsPair = words.getCurr();
        words.nextCurr();

        for (auto doc : docsPair.second) {
            myfile << docsPair.first << "\t";
            myfile << doc.first << "\t";
            if (words.hasNext()) {
                myfile << doc.second << endl;
            } else {
                myfile << doc.second;
            }
        }
    }
}

void IndexHandlerr::writePersistencePersons(string fileName) {
    ofstream myfile(fileName);

    persons.setCurr();
    while (persons.hasNext()) {
        auto docsPair = persons.getCurr();
        persons.nextCurr();

        for (auto doc : docsPair.second) {
            myfile << docsPair.first << "\t";
            myfile << doc.first << "\t";
            if (persons.hasNext()) {
                myfile << doc.second << endl;
            } else {
                myfile << doc.second;
            }
        }
    }
}



void IndexHandlerr::writePersistenceOrgs(string fileName) {
    ofstream myfile(fileName);

    //calling functions i made in Avltree.h
    organizations.setCurr();
    while (organizations.hasNext()) {
        auto docsPair = organizations.getCurr();
        organizations.nextCurr();

        for (auto doc : docsPair.second) {
            myfile << docsPair.first << "\t";
            myfile << doc.first << "\t";
            if (organizations.hasNext()) {
                myfile << doc.second << endl;
            } else {
                myfile << doc.second;
            }
        }
    }
}


void IndexHandlerr::writeDocuments(string fileName) {
    ofstream myfile(fileName);
    size_t count = 0;
    for (auto it = documents.begin(); it != documents.end(); ++it) {
        myfile << it->first << "\t";
        myfile << it->second.getTitle() << "\t";
        myfile << it->second.getPublication() << "\t";
        myfile << it->second.getAuthor() << "\t";
        myfile << it->second.getText() << "\t";


        if (count == documents.size() - 1) {
            myfile << it->second.getNumofDocs();
        } else {
            myfile << it->second.getNumofDocs() << endl;
        }
        count++;
    }
    myfile.close();

}





void IndexHandlerr::readPersistenceDocuments(string fileName) {
    ifstream infile(fileName);

    if (!infile) {
        cout << "File not found!" << endl;
        return;
    }

    string title;
    string docID;
    string publication;
    string datePublished;
    string author;
    string text;
    string numDocs;
    while (infile.good()) {
        getline(infile, docID, '\t');
        getline(infile, title, '\t');
        getline(infile, publication, '\t');
        getline(infile, author, '\t');
        getline(infile, text, '\t');
        getline(infile, numDocs);
        DocumentContents DocMapping(title, publication, author, text);
        DocMapping.setNumofWordsinFile(stoi(numDocs));
        documents[stoi(docID)] = DocMapping;
    }
}

void IndexHandlerr::readPersistenceWords(string fileName) {
    ifstream infile(fileName);

    if (!infile) {
        cout << "File not found!" << endl;
        return;
    }

    string word;
    string docID;
    string occurrence;
    while (infile.good()) {
        getline(infile, word, '\t');
        getline(infile, docID, '\t');
        getline(infile, occurrence);
        words.find(word)[stoi(docID)] = stoi(occurrence);
    }
}

void IndexHandlerr::readPersistencePersons(string fileName) {
    ifstream infile(fileName);

    if (!infile) {
        cout << "File not found!" << endl;
        return;
    }

    string word;
    string docID;
    string occurrence;
    while (infile.good()) {
        getline(infile, word, '\t');
        getline(infile, docID, '\t');
        getline(infile, occurrence);
        persons.find(word)[stoi(docID)] = stoi(occurrence);
    }
}

void IndexHandlerr::readPersistenceOrgs(string fileName) {
    ifstream infile(fileName);

    if (!infile) {
        cout << "File not found!" << endl;
        return;
    }

    string word;
    string docID;
    string occurrence;
    while (infile.good()) {
        getline(infile, word, '\t');
        getline(infile, docID, '\t');
        getline(infile, occurrence);
        organizations.find(word)[stoi(docID)] = stoi(occurrence);
    }
}




