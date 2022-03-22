/*c++ lab group 18 
    Lab 10  database cpp file 
   members: Duncan Collins, Rashminder Randhawa, Syed Ashan Subzwari 
   date : 11-30-2020
   
*/   


/* definitions */



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
#include "database.h"

using namespace std;


    

void StudentRec::showRecord(void){                  // displaying the record for a single studnet 
        
        cout << lastname << ",   " << firstname << ",    " << ID  << ",    " << GPA << endl;
        
    }

StudentDatabase::StudentDatabase(string fileName){
    
    

    recordCount = 0;
    DatabaseFileName = fileName;        // setting the private varriable equal to fileName
    
    cout << endl << "files loaded to program" << endl;
    
    Node *NEW;              // initlizing pointers and varriables 
    Node *curr;
    Node *prev;
    string fir;
    string las;
    string id;
    double gpa;
    head = NULL;
    
    fstream f(fileName);     // open file 
    
	while (true){				 // setting a while loop, to while this is true, until the end of file 

        f >> fir;
        f >> las;
        f >> id;
        f >> gpa;
		
		if (f.eof()){
		    break;
		}
		else {
		    NEW = new Node({{fir, las, id, gpa}, NULL });
		    if (head != NULL)              // if the list is null continue 
            {

                prev = NULL;            
                curr = head;            
                
                
                while ((curr != NULL) && (id > curr->data.ID)) // while loop to find insertion points for the files data
                {
                    prev = curr;      
                    curr = curr->Next; 
                }
                if (prev == NULL) {      // if the previous list is null
                    head = NEW;
                    NEW->Next = curr;
                    recordCount = recordCount + 1;
                }
                else                         
                {
                    
                    prev->Next = NEW;           // else place the node in appropiaye locatin 
                    NEW-> Next = curr;
                    
                    recordCount= recordCount + 1;
                }
            }
            else		                     //else, add to the list 
            {   
                head = NEW;
                NEW->Next = NULL;
                recordCount = recordCount + 1;          // these give record a value every time the record increases 
            }
		}
			
	
	f.close();          // close file 
	
    cout << endl << "files added, still organizing them ..." << endl;
	



    
   }

} 

StudentDatabase::~StudentDatabase(void){
    
    ofstream docOut;						// opening output file 
	
	docOut.open(DatabaseFileName);      // which is the database file 
	
    Node* Ptr = head;
    
    while (Ptr != NULL)				// until pointer node is null, or end of list
    {
        
        docOut << Ptr->data.firstname << "       ";         // outputting the data orderly into the file 
        docOut << Ptr->data.lastname << "       ";
        docOut << Ptr->data.ID << "       ";
        docOut << Ptr->data.GPA << endl;
        Ptr = Ptr->Next;			
        
        
    }
    
    
    docOut.close();								// closing file 


    Ptr = head;			// puttin the ponter node at the front of the list 
    Node* nxt;          // and declaring a pointer node for the nxt value 

    while (Ptr != NULL)     // while loop for until the ptr is at the end 
    {
        nxt = Ptr->Next;	
        delete Ptr;				// deleting the nodes one by one 
        Ptr = nxt;			
    }

	
}


void StudentDatabase::sortDatabase(){           // defining the sort function, which uses bubble sorting 
	vector<StudentRec> Database;
	int swaps;
	for(int i = 0; i < Database.size(); i ++){							// this is a for loop to iterate through thr vector until its end value
		
		int swapping = 0;										
		for(int n = 0; n < Database.size() - 1; n++){						// loop within the loop, this is where the swapping happens in each iteration
			
			if(Database.at(n).ID > Database.at(n + 1).ID) {							// if the value is greater than the next value in the vector, then it must swap with the next value. 
				string temp; 
				temp = Database.at(n).ID;
				Database.at(n).ID = Database.at(n + 1).ID;
				Database.at(n+1).ID = temp;
				swaps = 1;
				
			}
		}
		
		if(!swaps){
			break;
		}
	}
	
}

int StudentDatabase::BinarySearch(vector<StudentRec> & v, string ID, int radius, int place){			// binary search function
	
	if(place <= radius){								// if the start place is less than the radius... meaning it hasnt searched through all the possible items yet
		
		int middle = (place + radius) / 2;					// middle value
		
		if( v.at(middle).ID == ID){						// if this is the value we are searching for then return it 
			return middle;
		}
		if(v.at(middle).ID > ID){								// if it is not, then we use reccursion and search through the next possible half
			return BinarySearch(v, ID, middle - 1, place);
		}
		if(v.at(middle).ID < ID){
			return BinarySearch(v, ID, radius, middle + 1);
			
		}
	}
	
	return -999;
}





unsigned int StudentDatabase::size() const{             
    
    unsigned int i = 0; // Initialize i as 0                 
    Node* curr = head; // Initialize current node at head, front of list 
    while (curr != NULL)  
    {  
        i = i + 1;  
        curr = curr->Next;  // the current is switched to the next, and the i is iterated 
    }  
    
    return i;  
}  
    




void StudentDatabase::addRecord(const StudentRec & r){
    Node *Ptr = head;       // initializing the nodes 
    Node *NEW;
    Node *curr;
    
    NEW = new Node({{r.firstname, r.lastname, r.ID, r.GPA}, NULL });        // setting up the new node
    
    if(head == NULL){           // if the list is empty 
        
        head = NEW;     // the new node is the front of list 
    }
    else{
        while (Ptr != NULL){            // while not empty 
            curr = Ptr;
            Ptr = Ptr -> Next;
        }
        curr-> Next = NEW;           // iterated to end of list and puts node in back 
        
        
    }
}


bool StudentDatabase::removeRecord(string ID){
    
    Node* Ptr = head;				//Define the pointer node 
    Node* temp;			//a temp node to be deleted later 



    if (Ptr->data.ID == ID)
    {
        if (Ptr->Next == NULL)
        {
            temp = Ptr;				
            Ptr = Ptr->Next;			// go to the next node 
            head = NULL;						
            delete temp;					// delete the tmep node 
            
            while (Ptr->Next != NULL)
        {
                if (Ptr->Next->data.ID == ID)		// is it the correct id ? if so continue 
                {
                            					
                    temp = Ptr->Next;			// set the temp ad the next node after pointer 
                    if (Ptr->Next->Next == NULL)	// is the next node , and the one after null 
                    {
                        Ptr->Next = NULL;			// is the next node null 
                            break;							
                    }
                    else								
                     {
                        Ptr->Next = temp->Next;
                    }
                    delete temp;  
                    }
                Ptr = Ptr->Next; 
             }                					
             
            return true;     
        }
        
        
        else
        {
            temp = Ptr;				// temp for deleting 
            Ptr = Ptr->Next;		
            head = Ptr;
            delete temp;					// delete the temp node 
                    						
            Ptr = head;
                                            // same as the previous while loop 
            while (Ptr->Next != NULL)
        {
                if (Ptr->Next->data.ID == ID)		
                {
                            						
                    temp = Ptr->Next;			
                    if (Ptr->Next->Next == NULL)	
                    {
                        Ptr->Next = NULL;			
                            break;							
                    }
                    else								
                     {
                        Ptr->Next = temp->Next; 
                    }
                    delete temp;  
                    }
                Ptr = Ptr->Next; 
             }

            return true;
        }
    }

    
}



StudentRec* StudentDatabase::operator[](string ID) const{
    Node* curr = head;               // makes the current node at the begining of the list 
    StudentRec* Ptr;                
    curr = curr->Next;                  // the current node is then pushed forward
    
    for (unsigned int i = 0; i < size(); i++){          // for the length of the list it checks if the id is the valid id and goes to the next node if not 
        
        if(ID == curr->data.ID){
            
            return &(curr->data);
            
        }
        curr = curr->Next;
        
    }
    
    delete curr;        // free mem
    return NULL;            // return null if not found 
}






vector <StudentRec> StudentDatabase::searchByName(string name) const{

    vector<StudentRec> temporary;
    Node* Ptr;
    Ptr = head;
    while (Ptr != NULL) // until end of list, put all the nodes into the vector 
    {
        temporary.push_back({ Ptr->data.firstname , Ptr->data.lastname, Ptr->data.ID, Ptr->data.GPA });
        Ptr = Ptr->Next;
    }
	
	
	vector <StudentRec> searchName;             // defining a temporory vector to return in the function, and initially clearing it 
	
	
	for (int i = 0; i < temporary.size() ; ++i){			//loop to find the student record for the first and last name/ linear search 
				
		if ((temporary.at(i).lastname + ", " + temporary.at(i).firstname) == name){	//if the students "lastname, firstname" matches the given "lastname, firstname" then the following happens
					
			searchName.push_back(temporary.at(i));			// the students records are put into the vector 
		}
}

	return searchName;
}
	vector<StudentRec> StudentDatabase::change(){       // changes list to vector for certain functions 
	    
	    vector<StudentRec> temporary;
	    temporary.clear();
        Node* Ptr;
        Ptr = head;
        while (Ptr != NULL) // until end of list, put all the nodes into the vector, same as whats in the begining of the search by name function 
            {       
            temporary.push_back({ Ptr->data.firstname , Ptr->data.lastname, Ptr->data.ID, Ptr->data.GPA });
            Ptr = Ptr->Next;
            }
            
        return temporary;
        }	

