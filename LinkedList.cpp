#include <iostream>
#include "LinkedList.h"
using namespace std;


LinkedList::LinkedList(){//Default Constructor
    Head = nullptr;
}

LinkedList::~LinkedList(){//Destructor
    Node * newNode = Head;
    while(newNode != nullptr){
        Node* next = newNode->next;
        delete newNode;
        newNode = next;
    }
}

void LinkedList::Addperson(int id, string name, string dob, string a, string a2, string a3, int a4){//Add function
Node * newNode = new Node(id, name, dob, a, a2, a3, a4);//new data allocated
newNode->next = Head;
Head = newNode;
cout << "Thank you for your information " << newNode->name<< " has been added to the list"<<endl;
}

void LinkedList::DeletePerson(int id){//delete function requires id input 
    Node * curr = Head;
    Node* prev = nullptr;

    while(curr != nullptr){

        if (curr->ID == id){
            if(prev != nullptr){
                prev->next = curr->next;// redirecting pointers to ensure no data is lost or misplaced
            }
                else {
                    Head = curr->next;
                }
                delete curr;
            cout << "The person with id: "<< id << " has been deleted from the List"<< endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Person with this id is not found in the list"<<endl;
}

Node* LinkedList::SearchPerson(int id){// function that returns a Node Pointer after searching for specific id
    Node * curr = Head;
    while (curr != nullptr){
        if(curr->ID == id){
            return curr;
        }
        else {
            curr = curr->next;

        }
    }
    return nullptr; // not found in list

}
Node* LinkedList::SearchPersonN(string n){// function that returns a Node Pointer after searching for specific name
    Node * curr = Head;
    while (curr != nullptr){
        if(curr->name == n){
            return curr;
        }
        else {
            curr = curr->next;

        }
    }
    return nullptr; // not found in list

}
void LinkedList::UpdateInfo(int id){// Function to update information while prompting user
   Node* UpdatedNode = SearchPerson(id);
   cout << "Current information: "<< endl;
   cout << "Name: " << UpdatedNode->name<<endl;
   cout << "ID: " << UpdatedNode->ID<<endl;
   cout << "Date of Birth: " << UpdatedNode->DOB<<endl;
   cout << "Address: " << UpdatedNode->address<<endl;
        if (UpdatedNode != nullptr) {
            string n, dob, a,a2,a3;
            int a4;
            cout << "Please enter new Name: ";
            cin >> n;
            cout << "Please enter new DOB: ";
            cin >> dob;
            cout << "Please enter new Address(Street): ";
            cin >> a;
            cout << endl;
            cout << "Please enter new Address(City): ";
            cin >> a2;
            cout << endl;
            cout << "Please enter new Address(State): ";
            cin >> a3;
            cout << endl;
            cout << "Please enter new Address(Zip Code): ";
            cin >> a4;
            cout << endl;
            UpdatedNode->name = n;
            UpdatedNode->DOB = dob;
            UpdatedNode->address = a;
            UpdatedNode->a2 = a2;
            UpdatedNode->a3 = a3;
            UpdatedNode->a4 = a4;
            cout << "Person information updated successfully."<< endl;
            cout << "New information: "<< endl;
            cout << "Name: " << UpdatedNode->name<<endl;
            cout << "ID: " << UpdatedNode->ID<<endl;
            cout << "Date of Birth: " << UpdatedNode->DOB<<endl;
            cout << "Address(Street): " << UpdatedNode->address<<endl;
            cout << "Address(City): " << UpdatedNode->a2<<endl;
            cout << "Address(State): " << UpdatedNode->a3<<endl;
            cout << "Address(Zip Code): " << UpdatedNode->a4<<endl;

        } else {
            cout << "Person with ID " << id << " not found."<< endl;
        } 

}


void LinkedList::DisplayEveryone(){//display function
    Node* curr = Head;
    while(curr != nullptr){
        cout << "Name: "<< curr->name<<endl;
        cout << "ID: "<< curr->ID<<endl;
        cout << "Date of birth: "<< curr->DOB<< endl;
        cout << "Address(Street): "<<curr->address << endl;
        cout << "Address(City): "<<curr->a2 << endl;
        cout << "Address(State): "<<curr->a3 << endl;
        cout << "Address(Zip Code): "<<curr->a4 << endl;

        curr= curr->next;
    }
}