#ifndef FILEHANDLER_H
#define FILEHANDLER_H


#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include "../Simulator/Area.hpp"

class ClFileHandler
{
    public:
        ClFileHandler();
        ~ClFileHandler();
        //int writeLevel(std::string fileName, ClArea *pArea);    //obsolete, should not be used anymore
        int writeLevel(std::string fileName, ClArea *pArea, sf::Vector2f *levelSize, sf::Color *bgColor);
        int readLevel(std::string fileName, ClArea *pArea);     //obsolete, should not be used anymore
        int readLevel(std::string fileName, ClArea *pArea, sf::Vector2f *levelSize, sf::Color *bgColor);


        /*
        Return codes:
        0: No error
        1: Error while opening file
        3: Object Type from file out of range (enum staticObjects), autocorrection to WALL
        4: Unexpected token at line 2 of csv file when loading. Only ";" and numbers [0-9] are allowed, except first column.
        5: Unexpected RGB number in line 2 of csv file too long. Only [0-255] are allowed.
        6: Unexpected error reading line 2 of csv file: negative number.
        */


    private:
        int createFile(const char *fileName);           //if file exists it will be deleted, creates by ';' delimited file, file ending required, optimized for ".csv"
        int openExistingFile(const char *fileName);     //expects file ending with ".csv"
        //int writeLevelDetails(); //obsolete, should not be used anymore
        int writeLevelDetails(sf::Vector2f *levelSize, sf::Color *bgColor);
        int writeStaticObjects(ClArea *pArea);
        int importStaticObjects(ClArea *pArea);
        int importLevelDetails();
        int writeHeader(ClArea *pArea);
        int importLevelDetails(sf::Vector2f *levelSize, sf::Color *bgColor);


        unsigned int inNrOfObjects;
        std::ifstream inFile;
        std::ofstream myFile;
};

#endif // FILEHANDLER_H
