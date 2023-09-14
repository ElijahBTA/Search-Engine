//
// Created by Elijah  Posiulai on 12/4/22.
//

#ifndef FINALPROJEXAMPLES_INTERFACE_H
#define FINALPROJEXAMPLES_INTERFACE_H
#include "IndexHandlerr.h"
#include "DocumentParserr.h"
#include "QueryProcessor.h"
#include <chrono>


class Interface {
private:
    IndexHandlerr* handler;
    double timeForIndex;
    double timeForQuery;

public:
    Interface() {
        handler = new IndexHandlerr();
    }
    ~Interface() {
        delete handler;
    }
    void run();
    int menu();
    void createIndex();
    void writeIndex();
    void enterQuery();
    void readIndex();
    void outputStats();
    double gettimingforIndex();
    double gettimingForQuery();

};


#endif //FINALPROJEXAMPLES_INTERFACE_H
