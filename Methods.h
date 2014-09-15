/*
 Project:        GroupProject
 File Name:      Methods.h
 Description:    This class contains various helper methods to clean up our main.cpp.
 Copyright:      2014 Acuna Matata.
 Members:        Avery Bensen, Adam Birdsall,  Michael Reichstein, Jeff Scaturro.
 */
#ifndef ___40GroupProject__Methods__
#define ___40GroupProject__Methods__
#include <iostream>
#include "FlightNode.h"
#include "HubNode.h"
#include <string>
using namespace std;

HubNode* getHubByName(HubNode* listHead, string name);
bool isLater(Date_Time a, Date_Time b);
FlightNode *getFlights(HubNode *hubList, string nameHub);
void printRoute(FlightNode* array[], int bags);
void calculateShortest(HubNode* listHead, string finalDestination, Date_Time passedInTime, int bagsCheck);
void calculateCheapest(HubNode* listHead, string finalDestination, Date_Time passedInTime, int bagsCheck);
void menu(HubNode *head);
#endif /* defined(___40GroupProject__Methods__) */