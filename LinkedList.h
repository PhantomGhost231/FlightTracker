
// ASU CSE310 Fall 2023 Assignment #1
// Name: Rushil Prajapati
// ASU ID:1225139643
// Description: In this class we are supposed to input in the main Linked List 
// functions than will be needed to work with the Assignment1 class
//

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Flight represents a departure flight
struct Flight
{
    string airLine;
    int flightNum;
    string deptDate;        //departure date
    struct Flight* next;
};

//class LinkedList will contains a linked list of flights
class LinkedList
{
    private:
        struct Flight* head;
   

    public:
        LinkedList();
        ~LinkedList();
        bool searchFlight(string airLine, int flightNum, string deptDate);
        bool addFlight(string airLine, int flightNum, string deptDate);
        void displayAllFlights();
        void displayFlightsByAirLine(string airLine);
        void displayFlightsByDate(string date);
        bool cancelOneFlight(string airLine, int flightNum, string deptDate);
        bool cancelFlightsByAirLine(string airLine);
        bool cancelFlightsByDate(string deptDate);
        bool delayAFlight(string airLine, int flightNum, string oldDeptDate, string newDeptDate);
        bool changeAFlightAirLine(string oldAirLine, int flightNum, string deptDate, string newAirLine);
};

//Constructor to initialize an empty linked list
LinkedList::LinkedList()
{
    //Add your own code
    //----
    head=NULL;  //sets head to null
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the existing linked list.
//It deletes all the nodes including the head and finally prints the number of nodes deleted by it.
//Return value: Prints the number of nodes deleted by it.
LinkedList::~LinkedList()
{
	//Add your own code
    //----
    Flight* curr, *temp;
    curr=head;
    temp=head;
    int flightCount = 0;
    
    while(curr != NULL)
    {
       curr= curr->next;
       delete temp;
       temp=curr;
       flightCount++;  //counts the amount of flights that exists in the linked list right before deletion of the list
    }

    cout<< "\nThe number of deleted flights is: " << flightCount <<"\n";
}

//A function to find if the parameterized flight is inside the LinkedList or not.
//Return true if it exists and false otherwise.
bool LinkedList::searchFlight(string airLine, int flightNum, string deptDate)
{
	//Add your own code
    //----
    Flight* point = head;
    
    while(point != NULL)
    {
        if(point->airLine==airLine && point ->flightNum==flightNum && point->deptDate== deptDate )
        {
            return true;
        }
        
       point=point->next;
    }
     return false;
}

//***This is the most important function you need to work on since it build the linked list****
//Creates a new node and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of flights by the airLine, flight number
//and departure date. i.e. first by airLine, then by flight numbers. i.e. if two flights
//come from the same airline, the flight should be inserted by the increasing order of
//their flight numbers. Also it is possible that two or more flights have same airline
//and flight numbers, but with different departure date, then they should be inserted into
//the list by departure date. Early departure date flight should be put in front.
//Return value: true if it is successfully inserted and false in case of failures.
//Note: You should always consider 1) if list is empty; 2) if insert at the front, etc.
bool LinkedList::addFlight(string airLine, int flightNum, string deptDate)
{
    //Add your own code
    //----
    //searches through the flight to see if we have any similar flight methods
    Flight* current1 = head;
    while (current1 != NULL)
    {
        if (current1->airLine == airLine && current1->flightNum == flightNum && current1->deptDate == deptDate)
        {

            return false;
        }
        current1 = current1->next;
    }
    //creates new flight 
    Flight* newFlight = new Flight;
    newFlight->airLine = airLine;
    newFlight->flightNum = flightNum;
    newFlight-> deptDate = deptDate;
    newFlight->next = NULL;
  
  if(head==NULL)//checks if the first node is filled
   {
        head = newFlight;
        return true;
   }
   
    Flight* first = NULL;
    Flight* current = head;
    while (current != NULL) {  //loops through the entire linked list
        // Compares airLine, flightNum, and deptDate for the new flight and current node
        if (newFlight->airLine < current->airLine ||(newFlight->airLine == current->airLine && newFlight->flightNum < current->flightNum) || (newFlight->airLine == current->airLine && newFlight->flightNum == current->flightNum &&newFlight->deptDate < current->deptDate)) 
        {
            // Insert the new node before the current node
            if (first == NULL) {
                newFlight->next = head;
                head = newFlight;
            } else {
                first->next = newFlight;
                newFlight->next = current;
            }
            return true;
        }

        // Move to the next node
        first = current;
        current = current->next;
    }

    // Insert the new node at the end if not inserted earlier
    first->next = newFlight;
    newFlight->next = NULL;

    return true;
}

//Display all flights in the linked list starting from the head.
void LinkedList::displayAllFlights()
{
    //Add your own code
    //----
    
    Flight* temp = head;
    int counter = 0; 
    while(temp!= NULL)
    {
        	cout << left    << setw(5)  << temp->airLine
                    << setw(10) << temp->flightNum
                    << setw(12) << temp->deptDate   << "\n";
                    
                    temp = temp->next;
                    counter++;  
    }



	cout << "\nTotal # of flights: " << counter << "\n";
}

//Display all flights in the list with the specified airLine.
void LinkedList::displayFlightsByAirLine(string airLine)
{
    //Add your own code
    //----

   Flight* temp = head;
   int counter = 0;
   
   while(temp!=NULL)
   {
       if(temp->airLine==airLine)//displays all flights by deadline
       {
           
       
       cout << left    << setw(5)  << temp->airLine
                    << setw(10) << temp->flightNum
                    << setw(12) << temp->deptDate   << "\n";
                    counter++;
       }
       temp=temp->next;
       
   }

	if (counter==0)
        cout << "\nNo flights with the specified airLine found\n";
    else
        cout << "\nTotal: " << counter << " flights found with airline " << airLine << "\n";
}

//Display all flights with the specified date
void LinkedList::displayFlightsByDate(string date)
{
    //Add your own code
    //----
    Flight* temp = head;
   int counter = 0;
   
   while(temp!=NULL)
   {
       if(temp->deptDate==date)
       {
    cout << left    << setw(5)  << temp->airLine
                    << setw(10) << temp->flightNum
                    << setw(12) << temp->deptDate   << "\n";
                    counter++;
       }
       temp=temp->next;
   }

	if (counter==0)
        cout << "\nNo flights with the specified date found\n";
    else
        cout << "\nTotal: " << counter << " flights found on " << date << "\n";
}

//Cancel the specified flight from the list, releases the memory and updates pointers.
//Return true if it is successfully canceled, false otherwise.
bool LinkedList::cancelOneFlight(string airLine, int flightNum, string deptDate)
{
   Flight* first = NULL;
   Flight* current = head;
   
   
   //Add your own code
    //----
   
    while (current != NULL) {
        if (current->airLine == airLine && current->flightNum == flightNum && current->deptDate == deptDate) {
            // Found the flight to be canceled
            if (first == NULL) {
              
                head = current->next;
            } else {
               
                first->next = current->next;
            }

            delete current; // Release memory
            return true; // Flight canceled successfully
        }

        // Move to the next node
        first = current;
        current = current->next;
    }

    
    return false;
    
    
}

//Cancel all flights from a specific airline, releases the memory and updates pointers.
//Return true if it is successfully canceled, false otherwise. Note: multiple flights
//might be canceled
bool LinkedList::cancelFlightsByAirLine(string airLine)
{
    //Add your own code
    //----
    
    bool oneFlightcancel = false;
     Flight* first = NULL;
   Flight* current = head;
   
   while(current!=NULL)
   {
       if(current->airLine==airLine)
       {
           if(first==NULL)
           {
               head = current->next;
           }
           
           else
           {
               first->next = current-> next;
           }
           
           Flight* temp = current;
           current = current->next;
           delete temp; 
           oneFlightcancel = true;
           
       }
       
       else{
           first=current;
           current = current->next; 
       }
   }

  return oneFlightcancel;
}

//Removes all flights with the specified date, releases the memory and updates pointers.
//Return true if they are successfully removed, false otherwise. Note: all Flights with
//the same departure date should be removed from the list.
bool LinkedList::cancelFlightsByDate(string deptDate)
{
    //Add your own code
    //----
    bool Flightcancel = false;
     Flight* first = NULL;
   Flight* current = head;
   
   while(current!=NULL)
   {
       if(current->deptDate==deptDate)
       {
           if(first==NULL)
           {
               head = current->next;
           }
           
           else
           {
               first->next = current-> next;
           }
           
           Flight* temp = current;
           current = current->next;
           delete temp; 
           Flightcancel = true;
           
       }
       
       else{
           first=current;
           current = current->next; 
       }
   }

  return Flightcancel;
}

//Modifies the departure date of the given flight. Return true if it modifies successfully and
//false otherwise.
bool LinkedList::delayAFlight(string airLine, int flightNum, string oldDeptDate, string newDeptDate)
{
    //Add your own code
    //----
    Flight* current = head;
    Flight* first = nullptr;
    Flight* flightToDelay = nullptr;

    // Find the flight that is to be delayed
    while (current != nullptr)
    {
        if (current->airLine == airLine && current->flightNum == flightNum && current->deptDate == oldDeptDate)
        {
            flightToDelay = current;
            break;
        }

        first = current;
        current = current->next;
    }

    // If the flight was found, remove it from its current position
    if (flightToDelay)
    {
        if (first) {
            first->next = flightToDelay->next;
        } else {
            head = flightToDelay->next;
        }

        flightToDelay->deptDate = newDeptDate;
        
        // Reinsert the flight into the list in the correct order
        addFlight(flightToDelay->airLine, flightToDelay->flightNum, flightToDelay->deptDate);
        
        return true;
    }
    
    return false; // Flight not found
}

//Change a specific flight airline info. if it is found and change its airline successfully, return
//true; otherwise return false. Note: after successfully change its airline information, the linked list must
//still be in alphabetical order
bool LinkedList::changeAFlightAirLine(string oldAirLine, int flightNum, string deptDate, string newAirLine)
{
    //Add your own code
    //----
    Flight* current = head;
    Flight* first = nullptr;
    Flight* flightToChange = nullptr;

    // Find the flight to change and keep track of its firstious node
    while (current != nullptr)
    {
        if (current->airLine == oldAirLine && current->flightNum == flightNum && current->deptDate == deptDate)
        {
            flightToChange = current;
            break;
        }

        first = current;
        current = current->next;
    }

    // If the flight was found, remove it from its current position
    if (flightToChange)
    {
        if (first) {
            first->next = flightToChange->next;
        } else {
            head = flightToChange->next;
        }

        flightToChange->airLine = newAirLine;

        // Reinsert the flight into the list in the correct order
        addFlight(flightToChange->airLine, flightToChange->flightNum, flightToChange->deptDate);
        
        return true;
    }
    
    return false; // Flight not found
}