#include<iostream>
#include <vector>
#include "MovieHashTable.hpp"
using namespace std;

// Constructor for MovieHashTable with default size
MovieHashTable::MovieHashTable() {
    // TODO
    table_size = DEFAULT_HTABLE_CAPACITY;
    table = new MovieNode*[table_size];
    for(int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
    n_collisions = 0;
}

// Constructor for MovieHashTable with given size
MovieHashTable::MovieHashTable(int s) {
    // TODO
    table_size = s;
    table = new MovieNode*[table_size];
    for(int i = 0; i < table_size; i++)
    {
        table[i] = nullptr;
    }
    n_collisions = 0;
}

// Destructor for MovieHashTable that deletes all nodes in the hash table
MovieHashTable::~MovieHashTable() {
    // TODO
    MovieNode* curr;
        MovieNode* prev;
    for(int i = 0; i < table_size; i++) //for loop that iterates through the table size given in the constructor
    {
        curr = table[i];
        prev = NULL;
        while(curr != NULL) //while curr isn't equal to null, set previous equal to curr and currs to curr's next and delete prev to deconstruct the  hash table O(n)
        {
            prev = curr;
            curr = curr->next;
            delete prev;
        }
    }
    delete[] table;
}

// Hash function for MovieHashTable that returns an index in the hash table for a given movie title.
// Students must use their identikey to come up with a creative hash function that minimizes collisions
// for the given IMDB-Movie database to ensure efficient insertion and retrieval of movie nodes.
int MovieHashTable::hash(string title) {
    // TODO
    int hash = 0;
    for(int i = 0; i < title.length(); i++) //using the ASCII Table values to produce a random size to reduce the numebr of collisions that can occur
    {
        hash += title[i];
    }
    hash *= 3415*3415; // my identikey incoorperation
    hash = hash%table_size; // mod table size so that the hash actually can fit in the table.
    return hash;
}

// Inserts a movie node into the hash table with the specified title
void MovieHashTable::insert(string title, MovieNode* movie) {
    // TODO
    MovieNode* exists = search(title); //utilizing the search function to make sure that this movie doesn't already exist.
    if(exists != nullptr)
    {
        cout << "Duplicate Key" << endl;
        return;
    }
    int index = hash(title); //getting the index of the hash with the specified title of the movie.

    //shifting over the chaining in the linked list so that the new movie can be inserted at the head of the chained list
    MovieNode* curr = table[index];
    if(curr != nullptr) //for each time head exists, there will be a collision which will increment the counter
    {
        setCollisions();
    }
    movie->next = curr; //setting the movie as the new head

    table[index] = movie; //setting the index of the title as the movie.
    return;
}

// Searches for a node in the hash table with the specified title
MovieNode* MovieHashTable::search(string title) {
    // TODO
    int index = hash(title); //getting the index of the title 
    MovieNode* curr = table[index]; //getting head at that index
    while(curr != nullptr) //go through all of the movies until there are no more to search
    {
        if(curr->title == title) // if the title matches the  given one, the movie does exist 
        {
            return curr;
        }
        curr = curr->next;
    }

    return nullptr;
}

// Returns the number of collisions that have occurred during insertion into the hash table
int MovieHashTable::getCollisions() {
    // TODO
    return n_collisions;
}

// Increments the number of collisions that have occurred during insertion into the hash table
void MovieHashTable::setCollisions() {
    // TODO
    n_collisions++;
    return;
}