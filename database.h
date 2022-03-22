/*c++ lab group 18 
    Lab 10 database header file 
   members: Duncan Collins, Rashminder Randhawa, Syed Ashan Subzwari 
   date : 11-30-2020
   
*/   


/* definitions */
#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>  
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;



struct StudentRec {				// defining the struct data type
	
	string firstname;
	string lastname;
	
	string ID;
	double GPA;
	
	void showRecord(); // display the full record 
	
	
	
};

class StudentDatabase

{

private:

    struct Node

    {

    StudentRec data;

    Node *Next;

    };

    unsigned int recordCount; // the number of records in the list

    Node *head = NULL; // pointer to the head of linked list, sorted by student name

    string DatabaseFileName;
    
    
    
    

public:



// constructor. Pass database filename

// read database from the file to the linked list and close file

// Records in file are unsorted. Records in the linked list are sorted



    StudentDatabase(string fileName);
    
    

// destructor, save entries in the linked list to the file and close file.

// also need to destroy the linked list and release all memory blocks



    ~StudentDatabase();

    unsigned int size() const; 
    
    
    // return the number of valid records

// add a record to the linked list. detect duplicated ID.

// For new ID, add to the linked list (make sure the resulting list is still sorted.)

// For existing ID, update the record



    void addRecord(const StudentRec & r);
    
    vector<StudentRec> change();

// remove a record from list by ID. Return true if success, false if fail

    bool removeRecord(string ID);
    
    

// Search by ID - but using an array-like interface.

// Return a pointer to the student record if found;

// return NULL if not found. To search, using an ID as the index.

// For example, if d is an instance of StudentDatabase, and "M112233" is the id,

// d["112233"] will return the corresponding student record

// Note you cannot implement binary search on a linked list,

// even when the list is sorted.

    StudentRec* operator[](string ID) const;
    

    
    

// search by name, return a vector containing all matching entries.

// The vector is empty if there is no match

    int BinarySearch(vector<StudentRec> & v, string ID, int radius, int place);
    
    void sortDatabase();

    vector <StudentRec> searchByName(string name) const;

};

#endif
