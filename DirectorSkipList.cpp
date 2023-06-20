#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;

// Constructor for DirectorSkipList with default capacity and levels
DirectorSkipList::DirectorSkipList() {
    // TODO
    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS;
    head = new DirectorSLNode("",levels);
    size = 0;

}

// Constructor for DirectorSkipList with given capacity and levels
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    // 
    capacity = _cap;
    levels = _levels;
    head = new DirectorSLNode("",levels);
    size = 0;
}

// Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
DirectorSkipList::~DirectorSkipList() {
    // TODO
    // while(head != nullptr)
    // {

    //     DirectorSLNode* temp = head; //setting temp to the ehad
    //     head = head->next[0]; // traversing across the bottom because there have to be nodes there and setting head equal to its next and deleteing the temp.
    //     delete temp;

    // }
    DirectorSLNode* curr = head;
    DirectorSLNode* prev = nullptr;

    while(curr!=nullptr)
    {
        if(curr == head)
        {
            prev = curr->next[0];
            curr = prev;
        }
        else
        {
            prev = curr->next[0];
            delete curr;
            curr = prev;

        }
    }
    delete head;
    head = nullptr;
    levels = 0;
    capacity = 0;
}

// Inserts a movie node into the skip list with the specified director
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    // TODO
    if(size == capacity) //if the size is equal to capacity, you can't add anymore movies
    {
        cout << "Can't Add Anymore Movies" << endl;
        return;
    }
    DirectorSLNode* temp = search(director); //if the director already exists within the skip List, just add the movie
    if(temp != nullptr)
    {
        temp->addMovie(_movie);
        return;
    }
//otherwise randomly flip coins for where the node will end up

int n_levels = 1;
while(n_levels < levels && rand() % 2 == 0) //flipping the coin, if it is heads, add a level, otherwise stop there.
{
    n_levels++;
}
 DirectorSLNode* newNode = new DirectorSLNode(director, n_levels); //node with the given director and correct level
    newNode->addMovie(_movie); //adds the movie from the argument.
    
    DirectorSLNode* curr = head; 
    // vector<DirectorSLNode*> prev(levels, nullptr); // make it size levels and set all of the values to pointers
    DirectorSLNode* prev[levels];
    
    
    for(int i = levels - 1; i >= 0; i--) //for loop that goes from levels greaters index down to the first index of 0
    {
        while(curr->next[i] != nullptr && curr->next[i]->director < director) // while curr's next(starts at the highest level) is not null and the alpebetical value is less than that of the director run:
        {
            curr = curr->next[i]; 
        }
        prev[i] = curr; //only getting one parent in each row
    }

   cout << "adding director: " << newNode->director << endl;
    for(int i = 0; i < n_levels; i++) //while there are more levels from the coin toss run:
    {
        newNode->next[i] = prev[i]->next[i]; // setting newnodes next to prevs next and then setting prevs next to new node.
        prev[i]->next[i] = newNode;
    }
    size++; //increment size to make sure that capacity isn't reached
    // prev.clear();
    // delete newNode;
}

// Searches for a node in the skip list with the specified director
DirectorSLNode *DirectorSkipList::search(string director) { //skip lists are alphebetical
    // TODO
    DirectorSLNode* curr = head;
    // DirectorSLNode* prev = nullptr;
    for(int i = levels - 1; i >= 0; i--) //going through the indecies of levels of each DSL
    {
        while(curr->next[i] != nullptr && curr->next[i]->director < director) // while curr's next(starts at the highest level) is not null and the alpebetical value is less than that of the director run:
        {
            curr = curr->next[i];
        }
    }
    //prettyPrint();
    curr = curr->next[0]; //important because it finds the next director that is correct
    if(curr != nullptr && curr->director == director) // if curr exists and the directors match, return the searched node.
    {
        return curr;
    }
    else{
        return nullptr;
    }
}

// Pretty-prints the skip list
void DirectorSkipList::prettyPrint() { //pretty print used for testing purposes
    // TODO
    cout << "#Skip List#" <<endl;
    for(int i = levels - 1; i >= 0; i--)
    {
        cout << "Level " << i << ": ";
        DirectorSLNode* temp = head->next[i];
        while(temp != nullptr)
        {
            cout << temp->director << " --> ";
            temp = temp->next[i];
        }
        cout << "NULL" << endl;
    }
}