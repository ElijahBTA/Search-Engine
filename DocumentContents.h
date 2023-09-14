//
// Created by Elijah  Posiulai on 12/1/22.
//

#ifndef FINALPROJEXAMPLES_DOCUMENTCONTENTS_H
#define FINALPROJEXAMPLES_DOCUMENTCONTENTS_H
#include <string>
#include <iostream>
using namespace std;


class DocumentContents {
private:
    //All the varibles that are important when needing to return to the user
    string title;
    string publication;
    string author;
    string text;
    //weight i used for calcuating relevacny
    double weight;
    int numofWordsinFile;

public:
    DocumentContents() = default;
    //Constrcuter that initializes all variable for me to make it eaisier
    DocumentContents(string title_, string publication_, string author_, string text_) :
        title{title_}, publication{publication_}, author{author_}, text{text_},
        weight{0}, numofWordsinFile{0} {}
    string getTitle();
    string getPublication();
    string getAuthor();
    string getText();
    void setTitle( string );
    void setAuthor( string );
    void setPublication( string );
    void setText( string );
    void setNumofWordsinFile(int);
    int getNumofDocs();
    void setWeight(double);
    double getWeight() const;

    //overloading these so that i could find relveacny of documents by comparing their weight
    friend bool operator== (const DocumentContents&, const DocumentContents&);
    friend bool operator< (const DocumentContents&, const DocumentContents&);

};


#endif //FINALPROJEXAMPLES_DOCUMENTCONTENTS_H
