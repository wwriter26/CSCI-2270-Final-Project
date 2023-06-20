#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();


// Main function
int main(int argc, char* argv[]) {
    // TODO

    MovieHashTable movies = MovieHashTable();
    DirectorSkipList dsl = DirectorSkipList();

    readMovieCSV(argv[1], movies, dsl);
    string input = "";
    display_menu();

    cin >> input;

    while(input == "5") //accounting for if the users first option is 5 
    {
        cout << "You can't exit before trying Anything, choose a number 1 through 4" << endl;
        cin >> input;
    }
    
    while(input != "5")
    {   
        if(input == "1")
        {
            string movieInput = "";
            cout << "Enter movie name: "; 
            cin.ignore(); //the input buffer hasn't been cleared which this clears allowing access to the getline
            getline(cin,movieInput); //getting the entire line of the user's inputted movie
            if(movies.search(movieInput) == nullptr)
            {
                cout << movieInput << " Doesn't exist in the top 1000 IMDB Movies..." << endl;
            }
            else
            {
                cout << "The director of " << movieInput << " is " << movies.search(movieInput)->director << endl;
            }
        }
        else if(input == "2") // THE DSL SEARCH FUNCTION DOESN'T WORK
        {
            string directorInput = "";
            cout << "Enter director name: ";
            cin.ignore();
            getline(cin,directorInput); //getting the entire line of the user's inputted movie
            DirectorSLNode* temp = dsl.search(directorInput);
            if(temp == nullptr)
            {
                cout << directorInput << " Isn't a Director in the top 1000 IMDB Movies..." << endl;
            }
            else
            {
                cout << directorInput << " Directed " << dsl.search(directorInput)->movies.size() << " movie(s)" <<endl;
            }
            // delete temp;//_+_
        }
        else if(input == "3")
        {
            string movieInput = "";
            cout << "Enter movie name: "; 
            cin.ignore(); //the input buffer hasn't been cleared which this clears allowing access to the getline
            getline(cin,movieInput); //getting the entire line of the user's inputted movie
            if(movies.search(movieInput) == nullptr)
            {
                cout << movieInput << " Doesn't exist in the top 1000 IMDB Movies..." << endl;
            }
            else
            {
                cout << "Summary: " << movieInput << " is a " << movies.search(movieInput)->year << " (" << movies.search(movieInput)->genre << ") film featuring \"" 
                << movies.search(movieInput)->actors << "\"" << endl;
                cout << "Plot: \"" << movies.search(movieInput)->description << "\"" << endl;
            }
            cout << endl;
        }
        else if(input == "4")
        {
            string directorInput = "";
            cout << "Enter director name: ";
            cin.ignore();
            getline(cin,directorInput); //getting the entire line of the user's inputted movie
            if(dsl.search(directorInput) == nullptr)
            {
                cout << directorInput << " Isn't a Director in the top 1000 IMDB Movies..." << endl;
            }
            else
            {
                cout << directorInput << " Directed the following movies" << endl;
                int count = 0;
                for(int i = 0; i < dsl.search(directorInput)->movies.size(); i++)
                {
                    cout << "      " << count<<": " <<dsl.search(directorInput)->movies[i]->title << endl; //getting the name of each of the movies at node movies which is an array of nodes
                    count++;
                }
                
            }
            // cout << "Enter a Director Name:";
            // string name;
            // getline(cin,name);
            // DirectorSLNode* director = dsl.search(name);
            // if(director == nullptr)
            // {
            //     cout << "director DNE" << endl;
            //     continue;
            // }
            // cout << name << " has directed the following movies: " << endl;
            // for(int i = 0; i < director->movies.size(); i++)
            // {
            //     cout << i+1 << ": " << director->movies[i]->title << endl;
            // }
        }
        else if(input == "5")
        {
            //destructing the two data structures 
           cout << "Thanks :)" << endl;
            break;
        }
        else
        {
            cout << "Invalid input, Try again: ";
            cin >> input;
            continue;
        }
        display_menu();
        cin >> input;
    }

    
    return 0;
}

// Function to parse a CSV line into a MovieNode object
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}

// Function to read a CSV file into a vector of MovieNode objects
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    // TODO
    string line;
    ifstream read(filename);
    getline(read,line); //reading the first garbage line
    MovieNode* movieTemp = nullptr;
    while(getline(read,line))
    {
        movieTemp = parseMovieLine(line); //inserting into the hash table
        if(movieTemp == nullptr)
        {
            continue;
        }
        movieTable.insert(movieTemp->title,movieTemp);

        directorList.insert(movieTemp->director,movieTemp); //inserting into a skip list.

    }
    cout << "Number of Collisions: " << movieTable.getCollisions() << endl;
read.close();
}

// Function to display the menu options
void display_menu() {
    // TODO
    cout << "Please Select an option:" << endl;
    cout << "1. Find the director of a movie" << endl;
    cout << "2. Find the number of movies by a director" << endl;
    cout << "3. Find the description of a movie" << endl;
    cout << "4. List the movies by a director" << endl;
    cout << "5. Quit" << endl;
}
