/*
Project:        GroupProject
File Name:      FlightNode.cpp
Description:    This class has the desctructor of FlightNode.
Copyright:      2014 Acuna Matata.
Members:        Avery Bensen, Adam Birdsall,  Michael Reichstein, Jeff Scaturro.
*/
#include "FlightNode.h"

//FlightNode desctructor
FlightNode::~FlightNode() {
    if (next != NULL)
        delete next;
}

int FlightNode::getDelay() {
    return 0;
}
float FlightNode::getBaggageFees(int bags) {
	return bags*0.0;
}

 float SouthWest::getBaggageFees(int bags) {
     return bags*25.00;
 }
 
 float USAirway::getBaggageFees(int bags) {
     return (bags-1)*25.00;
 }
 
 float Delta::getBaggageFees(int bags) {
     return bags*0.00;
 }
 
 int SouthWest::getDelay() {
     //Southwest:  7:00AM to 5:00PM (30 minutes delay) ; 5:01PM to 6:59AM (no delay)
     // 07 to 17 and 17:01 to 06:59
     if (departure.hours >= 07 && departure.hours <= 17) {
         if ( departure.hours == 17 && departure.minutes > 0)
             return 0;
         return 30;
     }
     return 0;
 }
 
 int USAirway::getDelay() {
     // US Airway: 7:00AM to 5:00PM (10 minutes delay); 5:01PM to 1:00AM (15 minutes delay);
     // 1:01AM to 6:59AM (no delay).
     // 07 to 17 = 10; 17:01 to 01 = 15; 01:01 to 06:59 = 0;
     if(departure.hours == 0 && departure.hours <= 1) {
         if(departure.hours != 1)
             return 15;
         else if(departure.hours == 1 && departure.minutes == 0)
             return 15;
     }
     else if(departure.hours >= 1 && departure.hours <= 7) {
         if(departure.hours != 1 && departure.hours != 7)
             return 0;
         else if(departure.hours == 1 && departure.minutes == 0)
             return 15;
         else if(departure.hours == 7 && departure.minutes == 0)
             return 10;
     }
     else if(departure.hours >= 7 && departure.hours <= 17) {
         if(departure.hours != 7 && departure.hours != 17)
             return 10;
         else if(departure.hours == 17 && departure.minutes == 0)
             return 10;
     }
     else if(departure.hours >= 17 && departure.hours <= 23) {
         if(departure.hours != 17)
             return 15;
         else if(departure.hours == 17 && departure.minutes > 0)
             return 15;
     }
     return 0;
 }
 
 int Delta::getDelay() {
     // Delta: 20 minutes delay
     return 20;
 }