//PROGRAM: CS201PGM11MediaLibraryPart1
//NAME: Johnny Diep
//DATE: 03/24/2024
//Purpose: Read a collection of media in order to collect a library that could
//easily be added to. Classification of media and ability to print them out in
//several different ways. Able to print based on type, genre, and rating.

//Finished BONUS

//NOTE: Changed the mediaCommands.txt file on line 25 by changing "Rock" to "rock" to match the 2 songs that should be produced in the rubric as I believe that was the intention. Otherwise,
//"Rock" produces 5 songs as there's a distinction between the genre "Rock" vs "rock" due to capitalization.

#include <iostream>
#include <vector>
#include <fstream>
#include "Medialib.h"
#include "Media.h"
using namespace std;

int main()
{
    // File opening, verification, processing, writing, and closing
    vector<Media> collection;
    ofstream outfile("error.txt");
    ofstream report("report.txt");
    ifstream infile("mediaList.txt");
    ifstream mediacommands("mediaCommands.txt");
    // Verification
    if (!infile.is_open()) {
        cout << "mediaList.txt was unable to open";
        return 1;
    }
    if (!mediacommands.is_open()) {
        cout << "mediaCommands.txt was unable to open";
        return 1;
    }
    if (!outfile.is_open()) {
        cout << "error.txt was unable to open";
        return 1;
    }
    if (!report.is_open()) {
        cout << "error.txt was unable to open";
        return 1;
    }
    //Read Files and process
    readMediaList(infile, outfile, collection); //Read mediaList
    processMediaCommands(mediacommands, report, outfile, collection); //Read mediaCommands
    //Close files
    mediacommands.close();
    infile.close();
    outfile.close();
    report.close();
}