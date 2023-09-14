//
// Created by Elijah  Posiulai on 12/4/22.
//

#include "Interface.h"

void Interface::run() {

    int choice = 0;
    do {
        choice = menu();

        switch (choice) {
            case 1:
                createIndex();
                break;
            case 2:
                readIndex();
                break;
            case 3:
                writeIndex();
                break;
            case 4:
                enterQuery();
                break;
            case 5:
                outputStats();
                break;
            case 6:
                handler->clearindex();
                break;
            case -1:
                cout << "Goodbye" << endl;
            default:
                cout << "Invalid option ... try again" << endl;
        }
    } while (choice != -1);
}

int Interface::menu() {

    cout << "1. Create Index" << endl;
    cout << "2. Read Persistence" << endl;
    cout << "3. Write Persistence" << endl;
    cout << "4. Query" << endl;
    cout << "5. Output Stats" << endl;
    cout << "6. Clear Index" << endl;
    cout << "Enter choice or -1 to exit: ";
    int choice;
    cin >> choice;
    return choice;
}


void Interface::createIndex() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end1;
    start=std::chrono::high_resolution_clock::now();
    DocumentParserr parserr(handler);
    string filetoRead;
    parserr.readStopWords("../stopwords.txt");
    cout << "Enter file that you want to create a Index for: ";
    //for example if your wanting to access the 300,000 file you would do ../archive_large
    //if wanting the sampledata you do ../sample_data
    cin >> filetoRead;
    parserr.testFileSystem(filetoRead);
    end1=std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time1= end1-start;
    timeForIndex=time1.count();



}

void Interface::writeIndex() {
    handler->writePersistenceWords("../words.tsv");
    handler->writeDocuments("../documents.tsv");
    handler->writePersistencePersons("../persons.tsv");
    handler->writePersistenceOrgs("../orgs.tsv");
}

void Interface::readIndex() {
    handler->readPersistenceWords("../words.tsv");
    handler->readPersistenceDocuments("../documents.tsv");
    handler->readPersistencePersons("../persons.tsv");
    handler->readPersistenceOrgs("../orgs.tsv");
}


void Interface::enterQuery() {
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end1;
    start=std::chrono::high_resolution_clock::now();
    QueryProcessor processor(handler);
    processor.inputQuery();
    end1=std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time1= end1-start;
    timeForQuery=time1.count();

}

void Interface::outputStats() {
    cout << "Number of docs: " << handler->getSizeofDocuments() << endl;
    cout << "Total number of unique words " << handler->getTotalNodesinWords() << endl;
    cout << "Timing for indexing " << gettimingforIndex() << " and Query " << gettimingForQuery() << endl;


}

double Interface::gettimingforIndex() {
    return timeForIndex;
}

double Interface::gettimingForQuery() {
    return timeForQuery;
}

