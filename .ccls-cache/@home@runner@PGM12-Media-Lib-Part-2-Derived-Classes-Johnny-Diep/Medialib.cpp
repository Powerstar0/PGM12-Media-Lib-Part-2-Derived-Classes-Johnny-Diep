//
// Created by Johnny on 3/24/2024.
//

#include "Medialib.h"

//
// Created by Johnny on 3/24/2024.
//

// Default Constructor
Media::Media() {
    type = ' ';
    title = " ";
    keyName = " ";
    rating = 0;
    genre = " ";
    length = 0;
    yearReleased = 0;
}

//Overloaded Constructor
Media::Media(char c, string t, string k, int r, string g, int l, int y) {
    type = c;
    title = t;
    keyName = k;
    rating = r;
    genre = g;
    length = l;
    yearReleased = y;
}


//Process mediaList file
void readMediaList(ifstream &i, ostream& outErr, vector<Media> &m) {
    //Loop through entire file
    while (i.good()) {
        string line;
        getline(i, line);
        istringstream inSS(line);
        string hold;
        // Inputs for Media vector
        char type;
        string title;
        string keyName;
        int rating;
        string genre;
        int length;
        int yearReleased;
        // Get inputs
        // Type
        getline(inSS, hold, ',');
        type = hold[0];
        if (type == 'Q') {
            break;
        }
        // Title
        getline(inSS, hold, ',');
        title = hold;
        // KeyName
        getline(inSS, hold, ',');
        keyName = hold;
        // Rating
        getline(inSS, hold, ',');
        try {
            int preRating = stoi(hold);
            if (preRating > 10 || preRating < 1) {
                outErr << "ERROR: " << line << endl;
                outErr << "There was an invalid value entered for rating." << endl << endl;
                continue;
            }
            rating = preRating;
        }
        //Catch error
        catch (...) {
            outErr << "ERROR: " << line << endl;
            outErr << "Previous record has an invalid stoi argument error" << endl << endl;
            continue;
        }
        // Genre
        getline(inSS, hold, ',');
        genre = hold;
        // length
        getline(inSS, hold, ',');
        try {
            length = stoi(hold);
        }
        // Catch error
        catch (...) {
            outErr << "ERROR: " << line << endl;
            outErr << "Previous record has an invalid stoi argument error" << endl << endl;
            continue;
        }
        // yearReleased
        getline(inSS, hold, ',');
        try {
            int preYearReleased = stoi(hold);
            if (preYearReleased > 2023 || preYearReleased < 1500) {
                outErr << "ERROR: " << line << endl;
                outErr << "There was an invalid value entered for year." << endl << endl;
                continue;
            }
            yearReleased = preYearReleased;
        }
        //Catch error
        catch (...) {
            outErr << "ERROR: " << line << endl;
            outErr << "Previous record has an invalid stoi argument error" << endl << endl;
            continue;
        }
        //Push Media to vector
        Media tempM(type, title, keyName, rating, genre, length, yearReleased);
        m.push_back(tempM);
    }
}

//Process mediaCommands file
void processMediaCommands(istream& in, ostream& out, ostream& outERR, vector <Media> &m) {
    //Loop through entire file
    while (in.good()) {
      vector<string> row;
      string word;
        //Initialize variables
        string line;
        getline(in, line);
        istringstream inSS(line);
        string hold;
        int threshold;
        int counter;
        //Type
      while (getline(inSS, word, ',')) {
        row.push_back(word);
      }
        char command = row.at(0).at(0);
        out << endl;
      if (row.size() == 1) {
        row.push_back("blank");
      }
        // Print Media and check for rating
        if (command == 'M') {
            counter = 0;
            try {
                threshold = stoi(row.at(1));
                //Range Check
                if (threshold > 10 || threshold < 1) {
                    outERR << "Unable to process command. The rating of: " << threshold << " is invalid" << endl << endl;
                    continue;
                }
                out << "*****************************************************" << endl;
                out << "YOUR MOVIE LIST" << endl << endl;
                out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << endl;
                for (auto i : m) {
                    counter++;
                    //Prints if rating is equal or higher
                    if (i.getType() == 'M' && i.getRating() >= threshold) {
                        out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << endl;
                    }
                }
            }
            catch(...) {
                //Check to see if there's a genre
                  if (row.at(1) != "blank") {
                    counter = 0;
                    string genre3;
                  string genre2;
                    //Check to see if item is found
                    bool itemFound = false;
                    for (auto i : m) {
                        counter++;
                        if (i.getType() == 'M') {
                          genre3 = row.at(1);
                          // Erase leading whitespace
                          genre3.erase(0, genre3.find_first_not_of(" \t\n\r\f\v"));
                          // Erase trailing whitespace
                          genre3.erase(genre3.find_last_not_of(" \t\n\r\f\v") + 1);
                          genre2 = i.getGenre();
                          if (genre3 == genre2) {
                            itemFound = true;
                            break;
                          }
                        }
                    }
                    if (!itemFound) {
                        outERR << "Unable to process command. There was not item of genre: " << row.at(1) << " in your list" << endl << endl;
                        continue;
                    }
                    out << "*****************************************************" << endl;
                    out << "YOUR MOVIE LIST" << endl << endl;
                    out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << endl;
                    for (auto i : m) {
                        counter++;
                        //Print based on the genre
                        if (i.getType() == 'M' && i.getGenre() == genre3) {
                            out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << endl;
                        }
                    }
                }
                else {
                    //Print full movie list
                    out << "*****************************************************" << endl;
                    out << "YOUR MOVIE LIST" << endl << endl;
                    out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << endl;
                    for (auto i : m) {
                        counter++;
                        if (i.getType() == 'M') {
                            out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << endl;
                        }
                    }
                }
            }
        }
        // Print Books and check for rating
        else if (command == 'B') {
            counter = 0;
            try {
                threshold = stoi(row.at(1));
                //Check range
                if (threshold > 10 || threshold < 1) {
                    outERR << "Unable to process command. The rating of: " << threshold << " is invalid" << endl << endl;
                    continue;
                }
                out << "*****************************************************" << endl;
                out << "YOUR BOOK LIST" << endl << endl;
                out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << endl;
                for (auto i : m) {
                    counter++;
                    //Check if rating is equal or higher
                    if (i.getType() == 'B' && i.getRating() >= threshold) {
                        out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << endl;
                    }
                }
            }
            catch(...) {
                //Check to see if there's a genre
                  if (row.at(1) != "blank") {
                    counter = 0;
                    string genre3;
                  string genre2;
                    //Check to see if item is found
                    bool itemFound = false;
                    for (auto i : m) {
                        counter++;
                        if (i.getType() == 'B') {
                          genre3 = row.at(1);
                          // Erase leading whitespace
                          genre3.erase(0, genre3.find_first_not_of(" \t\n\r\f\v"));
                          // Erase trailing whitespace
                          genre3.erase(genre3.find_last_not_of(" \t\n\r\f\v") + 1);
                          genre2 = i.getGenre();
                          if (genre3 == genre2) {
                            itemFound = true;
                            break;
                          }
                        }
                    }
                    if (!itemFound) {
                        outERR << "Unable to process command. There was not item of genre: " << row.at(1) << " in your list" << endl << endl;
                        continue;
                    }
                    out << "*****************************************************" << endl;
                    out << "YOUR BOOK LIST" << endl << endl;
                    out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << endl;
                    for (auto i : m) {
                        counter++;
                        //Print based on genre
                        if (i.getType() == 'B' && i.getGenre() == genre3) {
                            out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << endl;
                        }
                    }
                }
                else {
                    //Print full book list
                    counter = 0;
                    out << "*****************************************************" << endl;
                    out << "YOUR BOOK LIST" << endl << endl;
                    out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << endl;
                    for (auto i : m) {
                        counter++;
                        if (i.getType() == 'B') {
                            out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << endl;
                        }
                    }
                }
            }
        }
        // Print Songs and check for rating
        else if (command == 'S') {
            counter = 0;
            try {
                threshold = stoi(row.at(1));
                //Check Range
                if (threshold > 10 || threshold < 1) {
                    outERR << "Unable to process command. The rating of: " << threshold << " is invalid" << endl << endl;
                    continue;
                }
                out << "*****************************************************" << endl;
                out << "YOUR SONG LIST" << endl << endl;
                out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << endl;
                for (auto i : m) {
                    counter++;
                    //Print is rating is equal or higher
                    if (i.getType() == 'S' && i.getRating() >= threshold) {
                        out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << endl;
                    }
                }
            }
            catch(...) {
                //Check to see if there's a genre
                if (row.at(1) != "blank") {
                    counter = 0;
                    string genre3;
                  string genre2;
                    //Check to see if item is found
                    bool itemFound = false;
                    for (auto i : m) {
                        counter++;
                        if (i.getType() == 'S') {
                          genre3 = row.at(1);
                          // Erase leading whitespace
                          genre3.erase(0, genre3.find_first_not_of(" \t\n\r\f\v"));
                          // Erase trailing whitespace
                          genre3.erase(genre3.find_last_not_of(" \t\n\r\f\v") + 1);
                          genre2 = i.getGenre();
                          if (genre3 == genre2) {
                            itemFound = true;
                            break;
                          }
                        }
                    }
                    if (!itemFound) {
                        outERR << "Unable to process command. There was not item of genre: " << row.at(1) << " in your list" << endl << endl;
                        continue;
                    }
                    out << "*****************************************************" << endl;
                    out << "YOUR SONG LIST" << endl << endl;
                    out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << endl;
                  for (auto i : m) {
                        counter++;
                        //Print based on genre
                        if (i.getType() == 'S') 
                          if (genre3 == i.getGenre()){
                            out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << endl;
                        }
                    }
                }
                else {
                    //Prints full song list
                    counter = 0;
                    out << "*****************************************************" << endl;
                    out << "YOUR SONG LIST" << endl << endl;
                    out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << endl;
                    for (auto i : m) {
                        counter++;
                        if (i.getType() == 'S') {
                            out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << endl;
                        }
                    }
                }
            }
        }
        else if (command == 'T') {
            //Prints total of collection including the types
            printTotals(out, m);
        }
        else if (command == 'N') {
            //Adds new media to collection
            addNewMedia(inSS, out, outERR, m, row);
        }
        else if (command == 'A') {
            //Prints all media in collection
            counter = 0;
            try {
                //Looks for rating
                threshold = stoi(row.at(1));
                if (threshold > 10 || threshold < 1) {
                    outERR << "Unable to process command. The rating of: " << threshold << " is invalid" << endl << endl;
                    continue;
                }
                out << "*****************************************************" << endl;
                out << "YOUR MEDIA LIST" << endl << endl;
                out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << setw(5) << "TYPE" << endl;
                for (auto i : m) {
                    counter++;
                    if (i.getRating() >= threshold) {
                        out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << setw(5) << i.getType() << endl;
                    }
                }
            }
            catch(...) {
                //Prints all media (no rating threshold)
                out << "*****************************************************" << endl;
                out << "YOUR MEDIA LIST" << endl << endl;
                out << "#   " << setw(40) << left << "TITLE" << setw(6) << "YEAR" << setw(10) << "RATING" << setw(5) << "TYPE" << endl;
                for (auto i : m) {
                    counter++;
                    out << setw(4) << counter << setw(40) << left << i.getTitle() << setw(6) << i.getYearReleased() << setw(10) << i.getRating() << setw(5) << i.getType() << endl;
                }
            }
        }
        else if (command == 'Q') {
            //Exit
            return;
        }
        else {
            //Invalid inputs
            outERR << "The command: " << command << " is invalid." << endl << endl;
        }

    }
}

//Print total items and of each type in collection
void printTotals(ostream& out, vector <Media> &m) {
    int total = 0;
    int movies = 0;
    int books = 0;
    int songs = 0;
    out << "*****************************************************" << endl;
    for (auto i : m) {
        total++;
        if (i.getType() == 'M')
            movies++;
        if (i.getType() == 'S')
            songs++;
        if (i.getType() == 'B')
            books++;
    }
    out << "YOUR MEDIA LIBRARY" << endl;
    out << "#  " << "TYPE" << endl;
    out << setw(4) << left << movies << "MOVIES" << endl;
    out << setw(4) << left << books << "BOOKS" << endl;
    out << setw(4) << left << songs << "SONGS" << endl;
    out << setw(4) << left << total << "ITEMS" << endl << endl;
}

//Add new media to collection (with error handling)
void addNewMedia(istream& inCommands, ostream& out, ostream& outErr, vector<Media>& m, vector<string>& row) {
    string tempStr;
    vector<string> row2 = row;
    //Separates word in csv row
    //while (getline(inCommands, tempStr, ',')) {
     //   row2.push_back(tempStr);
    //}
    //Type
    char type = row.at(1).at(0);
    if (type != 'M' && type != 'S' && type != 'B') {
        outErr << "Unable to process type" << endl << endl;
        return;
    }
    //Title
    string title = row[2];
    //Name
    string name = row[3];
    //Rating
    int rating;
    try {
        rating = stoi(row[4]);
        //Range check
        if (rating > 10 || rating < 1) {
            outErr << "Unable to process command. There was an invalid value entered for rating: " << title << endl << endl;
            return;
        }
    }
    catch(...) {
        //Invalid input
        outErr << "Unable to process command. There was an invalid value entered for rating: " << title << endl << endl;
        return;
    }
    //Genre
    string genre = row[5];
    //Length
    int length;
    try {
        length = stoi(row[6]);
    }
    catch(...) {
        //Invalid input
        outErr << "Unable to process command. There was an invalid value entered for length: " << title << endl << endl;
        return;
    }
    //Year released
    int year;
    try {
        year = stoi(row[7]);
        //Range check
        if (year > 2023 || year < 1500) {
            outErr << "Unable to process command. There was an invalid value entered for year: " << title << endl << endl;
            return;
        }
    }
    catch(...) {
        //Invalud input
        outErr << "Unable to process command. There was an invalid value entered for year: " << title << endl << endl;
        return;
    }
    //Push Media
    Media tempM(type, title, name, rating, genre, length, year);
    m.push_back(tempM);
    out << title << " was added to your list" << endl << endl;
}
