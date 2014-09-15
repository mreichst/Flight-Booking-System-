/*
Project:        GroupProject
File Name:      Date_Time.h
Description:    This class creates an object of Date_Time that holds
                information about the time and date of a flight.
Copyright:      2014 Acuna Matata.
Members:        Avery Bensen, Adam Birdsall,  Michael Reichstein, Jeff Scaturro.
*/
#ifndef Date_Time_H
#define Date_Time_H
#include <iostream>
using namespace std;

class Date_Time {
public:
    int minutes;
    int hours;
    int day;
    int month;
    int year;
        
    // Default contstructor (sets everything to be 0).
	Date_Time(){
		minutes =0;
		hours =0;
		day=0;
		month=0;
		year=0;
	}

    // Our constructor.
    Date_Time(int m, int h, int d, int mth, int yr) {
        minutes = m;
        hours = h;
        day = d;
        month = mth;
        year = yr;
    }
    
    // Methods.
    void AddMinutes(int min);

	string ToString();
};
#endif