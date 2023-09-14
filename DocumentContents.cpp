//
// Created by Elijah  Posiulai on 12/1/22.
//

#include "DocumentContents.h"

string DocumentContents::getTitle() {
    return title;
}

string DocumentContents::getPublication() {
    return publication;
}

string DocumentContents::getAuthor() {
    return author;
}

void DocumentContents::setTitle(string titles) {
    title=titles;
}

void DocumentContents::setAuthor(string authors) {
    author=authors;
}

void DocumentContents::setPublication(string publications) {
publication=publications;
}

string DocumentContents::getText() {
    return text;
}

void DocumentContents::setText(string texts) {
    text=texts;

}

void DocumentContents::setNumofWordsinFile(int Numwords) {
numofWordsinFile=Numwords;
}

int DocumentContents::getNumofDocs() {
    return numofWordsinFile;
}

void DocumentContents::setWeight(double weightt) {
weight=weightt;
}

double DocumentContents::getWeight() const {
    return weight;
}

bool operator==(const DocumentContents &lhs, const DocumentContents &rhs) {
    return lhs.title == rhs.title;
}

bool operator<(const DocumentContents &lhs, const DocumentContents &rhs) {
    return lhs.title < rhs.title;
}


