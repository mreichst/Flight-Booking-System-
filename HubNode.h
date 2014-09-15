/*
Project:        GroupProject
File Name:      HubNode.h
Description:    This implements a linked list node for an airport hub. 
Copyright:      2014 Acuna Matata.
Members:        Avery Bensen, Adam Birdsall,  Michael Reichstein, Jeff Scaturro.
*/
#ifndef HUB_NODE_H
#define HUB_NODE_H
#include <string>
using namespace std;

// Forward Declartion for FlightNode.
class FlightNode;

class HubNode {
public:
	string name;
	string location;
	HubNode* next;
	FlightNode* headFlights;
	
    // Destructor.
    virtual ~HubNode();
};
#endif