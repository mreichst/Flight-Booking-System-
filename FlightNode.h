/*
Project:        GroupProject
File Name:      FlightNode.h
Description:    This implements a linked list node for a flight. 
Copyright:      2014 Acuna Matata.
Members:        Avery Bensen, Adam Birdsall,  Michael Reichstein, Jeff Scaturro.
*/
#ifndef FLIGHT_NODE_H
#define FLIGHT_NODE_H
#include <string>
#include "Date_Time.h"
#include "HubNode.h"
using namespace std;

class FlightNode {
public:
	string flightNumber;
	double price;
	string flightCompany;
	Date_Time departure;
	int duration;
	HubNode* source;
	HubNode* destination;
	FlightNode* next;

    //Destructor
    virtual ~FlightNode();
    // Methods
	virtual float getBaggageFees(int bags);
	virtual int getDelay();
};

class SouthWest:public FlightNode {
public:
    // Methods
	float getBaggageFees(int bags);
	int getDelay();
};

class USAirway:public FlightNode {
public:
    // Methods
	float getBaggageFees(int bags);
	int getDelay();
};

class Delta:public FlightNode {
public:
    // Methods
	float getBaggageFees(int bags);
	int getDelay();
};
#endif