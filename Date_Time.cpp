/*
Project:        GroupProject
File Name:      Date_Time.cpp
Description:    This class has the methods of the object Date_Time.
Copyright:      2014 Acuna Matata.
Members:        Avery Bensen, Adam Birdsall,  Michael Reichstein, Jeff Scaturro.
*/
#include "Date_Time.h"

// Assuming it simply adds minutes to the departure time.
void Date_Time::AddMinutes(int min) {
    
    if (minutes + min >= 60) {
        minutes += min;
        while (minutes >= 60) {
            hours++;
            if (hours >=24) {
                day++;
                if(day > 30) {
                    month++;
                    if (month >= 12) {
                        year++;
                    }
                    month -= 11;
                }
                hours -= 24;
            }
            minutes -= 60;
        }
    }
    else
        minutes += min;
}

// Prints out the string of Date_Time.
string Date_Time::ToString() {
    string printOut;
    printOut = Date_Time::minutes + '|' + Date_Time::hours + '|' + Date_Time::day
        + '|' + Date_Time::month  + '|' +  Date_Time::year;
    return printOut;
}