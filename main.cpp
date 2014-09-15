/*
Project:        GroupProject
File Name:      main.cpp
Description:    This controls the program and prints out menu.
                It is the main class, so everything here calls others.
Copyright:      2014 Acuna Matata.
Members:        Avery Bensen, Adam Birdsall,  Michael Reichstein, Jeff Scaturro.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>
#pragma comment(lib, "winmm.lib")
#include "FlightNode.h"
#include "Date_Time.h"
#include "HubNode.h"
#include "string.h"
#include "Methods.h"

using namespace std; 

// Global Variables
HubNode* hubListHead = NULL;

// Forward Declarations
void readFlightFile();
void readHubFile();
void debugHubPrint();
void debugFlightPrint(HubNode* current);
void findHub(string toFind, FlightNode* addingFlight);

//main method to call methods and will eventually have menu 
int main() {
    // Welcome ;)
    PlaySound(TEXT("hakunamatata.wav"), NULL, SND_ASYNC);
    
    // LOAD
    readHubFile();
    readFlightFile();

    /*
    // Set up a Date_Time to simulate a user's input.
    Date_Time *test = new Date_Time(10, 10, 10, 10, 2012);
    
    //until we have a menu; this gives  the instruction to search for a fast flight from PHX to Honolulu
	cout<<endl<<"This is the fastest route From Phoenix to Honolulu: "<<endl;
    calculateShortest(hubListHead, "Honolulu International Airport", test, 5);
    
    
	//until we have a menu; this gives the instructions to search for cheapest from PHX to LAX
	cout<<endl<<"This is the cheapest route From Phoenix to Los Angeles: "<<endl;
    calculateCheapest(hubListHead, "Los Angeles International Airport", test, 3);
    */
    
    // MENU
    menu(hubListHead);
    
    //Memory Management
    hubListHead = NULL;
    
    system("PAUSE");

    return 0;
}

//reads in the Hub.csv and places it in respective HubNodes
void readHubFile() {
    // Data to read.
    string line, name, location;
    HubNode *newHubNode;
    HubNode *iter;
    HubNode *prev;

    ifstream myfile("Hub.csv");
	if (myfile.is_open()) {
        //Below function will read until next comma ',' in same line and store that string in 'value' variable and print
        getline(myfile, line); // Skip first line.
        
		while (myfile.good()) {
            while (getline(myfile, name, ',')) { //Get every value in order.
                newHubNode = new HubNode;
                newHubNode->headFlights = NULL;
				getline(myfile, location);
                newHubNode->name = name;
                newHubNode->location = location;
                newHubNode->next = NULL;
                
                // If the new node is empty, error.
                if (newHubNode == NULL) {
                    cout << "Error allocating memory in readHubFile()";
                }
                
				//Adding to Linked List END
                if (hubListHead == NULL) {
                    newHubNode->next = hubListHead;
                    hubListHead = newHubNode;
                }
                else {
                    iter = new HubNode;
                    iter =  hubListHead;
                    prev = new HubNode;
                    prev = NULL;
                    
                    // traverse to the end.
                    while (iter != NULL) {
                        // Move to next node
                        prev = iter;
                        iter = iter->next;
                    }
                    prev->next = newHubNode;
                    newHubNode->next = NULL;
                    
                    //Memory Management
                    delete iter;
                    iter = NULL;
                    prev = NULL;
                    newHubNode = NULL;
                }
            }
        }
        myfile.close();
    }
    else
        cout << "Unable to open file" << endl;
}

//reads in the Flights.csv and places them in respective FlightNode in HubNode
void readFlightFile() {
	// Variables we will use through reading.
    string line, number, sourceAirport, destination, company, dateTime, price, duration;
    int min, hour, day, month, year;

    // Reading the file. 
    ifstream myfile ("Flight.csv");
	if (myfile.is_open())
    {
        //Below function read until next comma ',' in same line and store that string in 'value' variable and print
        getline(myfile, line); // Skip first line.
        
		while (myfile.good()) {
            while (getline(myfile, number, ',')) { //Get every value in order.
                FlightNode *newFlightNode = new FlightNode;
                
                getline(myfile, price, ',');
                getline(myfile, sourceAirport, ',');
                getline(myfile, destination, ',');
                getline(myfile, dateTime, ',');
                getline(myfile, duration, ',');
                getline(myfile, company);

                if (company.compare("SouthWest") == 0)
                    newFlightNode = new SouthWest;
                if (company.compare("USAirway") == 0)
                    newFlightNode = new USAirway;
                if (company.compare("Delta") == 0)
                    newFlightNode = new Delta;
                
                // Setting all the data for our FlightNode
                newFlightNode->flightNumber = number;
                newFlightNode->price = stod(price);
                
                HubNode* newSourceHubNode = getHubByName(hubListHead, sourceAirport);
                HubNode* newDestHubNode = getHubByName(hubListHead, destination);
                
                // Source Hub
                newFlightNode->source = newSourceHubNode;
                
                // Destination Hub
                newFlightNode->destination = newDestHubNode;
                
                // Data for the Date and time.
                // Parsing the string.
                string word;
                stringstream stream(dateTime);
                while ( getline(stream, word, '/')) {
                    min = stoi(word);
                    getline(stream, word, '/');
                    hour = stoi(word);
                    getline(stream, word, '/');
                    day = stoi(word);
                    getline(stream, word, '/');
                    month = stoi(word);
                    getline(stream, word, '/');
                    year = stoi(word);
                }
                Date_Time newDateTime = Date_Time(min, hour, day, month, year);
            
				newFlightNode->departure = newDateTime;
                
                newFlightNode->duration = stoi(duration);
                newFlightNode->flightCompany = company;
                newFlightNode->next = NULL;
                newFlightNode->departure.AddMinutes(newFlightNode->getDelay());

                // If the new node is empty, error.
                if (newFlightNode == NULL) {
                    cout << "Error allocating memory in readFlightFile()";
                }
                
                //Adding to Linked List IN the hub's node END
                if (newSourceHubNode->headFlights == NULL) {
                    newFlightNode->next = newSourceHubNode->headFlights;
                    newSourceHubNode->headFlights = newFlightNode;
                }
                else {
                    FlightNode *flightIter = new FlightNode;
                    flightIter =  newSourceHubNode->headFlights;
                    FlightNode *prev = new FlightNode;
                    prev = NULL;
                    
                    // traverse to the end.
                    while (flightIter != NULL) {
                        // Move to next node
                        prev = flightIter;
                        flightIter = flightIter->next;
                    }
                    prev->next = newFlightNode;
                    newFlightNode->next = NULL;
                }
				
                newFlightNode = NULL;
                delete newFlightNode;
                newFlightNode = NULL;
                newSourceHubNode = NULL;
                newDestHubNode = NULL;
            }
        }
        myfile.close();
    }
    else 
        cout << "Unable to open file" << endl;
}

//prints the Hubs
void debugHubPrint() {
	//checks to see of there is anything in list_head
	HubNode *iter = new HubNode;
   
	if(hubListHead == NULL) {
		cout<< "No Entries.";
	}
	else {
        iter = hubListHead;
		//while there is something in the list, it prints everything out
		while(iter != NULL) {
			cout << iter->name<< ", "<<iter->location << endl;
            cout << "Flights out:" << endl;
            debugFlightPrint(iter);
			iter = iter->next;
		}
		cout<< endl;
	}
    delete iter;
    iter = NULL;
}

//prins the flights
void debugFlightPrint(HubNode* current) {
	//checks to see of there is anything in list_head
	FlightNode *iter = new FlightNode;
    
	if(current->headFlights == NULL) {
		cout<< "No Entries.";
	}
	else {       
        iter = current->headFlights;
        //while there is something in the list, it prints everything out
		while(iter != NULL) {
            cout << iter->flightNumber << ", " << iter->price << ", " << iter->source->name << ", " << iter->destination->name
               // << ", " << iter->departure.ToString() << "," 
				<<", " << iter->departure.minutes << "|" << iter->departure.hours << "|" << iter->departure.day
				<<"|" << iter->departure.month << "|" << iter->departure.year
				<<", "<<iter->duration<<", "<<iter->flightCompany<<endl;
			iter = iter->next;
		}
		cout<< endl;
	}
    delete iter;
    iter = NULL;
}