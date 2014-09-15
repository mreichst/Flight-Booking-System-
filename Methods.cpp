/*
 Project:        GroupProject
 File Name:      Methods.cpp
 Description:    This class contains various helper methods to clean up our main.cpp.
 Copyright:      2014 Acuna Matata.
 Members:        Avery Bensen, Adam Birdsall,  Michael Reichstein, Jeff Scaturro.
 */
#include "Methods.h"

// Gets the hub by name
HubNode* getHubByName(HubNode* listHead, string name) {
    HubNode* hubIter = listHead;
    // Move to start at PHX.
    while ( hubIter != NULL && hubIter->name.compare(name) != 0) {
        hubIter = hubIter->next;
    }
    return hubIter;
    delete hubIter;
    hubIter = NULL;
}

// Method returns true if flight b is later than a.
bool isLater(Date_Time a, Date_Time b) {
    // Check year
    if (b.year > a.year)
        return true;
    if (b.year < a.year)
        return false;
    if (b.year == a.year) {
        
        // Check month
        if (b.month > a.month)
            return true;
        if (b.month < a.month)
            return false;
        if (b.month == a.month) {
            
            // Check day
            if (b.day > a.day)
                return true;
            if (b.day < a.day)
                return false;
            if (b.day == a.day) {
                
                // Check hours
                if (b.hours > a.hours)
                    return true;
                if (b.hours < a.hours)
                    return false;
                if (b.hours == a.hours) {
                    
                    // Check minutes
                    if (b.minutes > a.minutes)
                        return true;
                    if (b.minutes < a.minutes)
                        return false;
                    if (b.minutes == a.minutes) {
                        return false;
                    }}}}}
    return false;
}

// Method will return a linked list of the flights at a certain hub.
FlightNode *getFlights(HubNode *hubList, string nameHub) {
    HubNode *hubIter = new HubNode;
    hubIter = hubList;
    
    // Move to the hub
    while ( hubIter != NULL && hubIter->name != nameHub) {
        hubIter = hubIter->next;
    }
    
    return hubIter->headFlights;
    delete hubIter;
    hubIter = NULL;
}

//prints the final route for fastest or cheapest
void printRoute(FlightNode* array[], int bags) {
    // Temp variables to keep track of time and cost of the route.
    int i;
    int time = 0;
	double cost = 0;
    
    // Printout: flight #, time of departure, time of arrival, total cost.
	if (array[0] == NULL)
	{
		cout << "There is no flight open at this time to this location.";
		return;
	}

    for (i = 0; i < 2; i++) {
        if (array[0] == array[1]){
			i++;}
		// Updating the price and time of the route.
		cost += array[i]->price;
		time += array[i]->duration;
        
        // Printing out the details.
      cout<<endl<<endl<<array[i]->flightNumber<<"\t\t"<<array[i]->flightCompany
            <<"\t\t"<<array[i]->source->location<<"\t\t"<<array[i]->departure.month
            <<"/"<<array[i]->departure.day<<"/"<<array[i]->departure.year
            <<" "<<array[i]->departure.hours<<":"<<array[i]->departure.minutes;

        // Add the Duration to the time.
        array[i]->departure.AddMinutes(array[i]->duration);
       // Print out updated arrival time!
        cout<<endl << "\n\t\t\t\t"<<array[i]->destination->location<<"\t"<<array[i]->departure.month
            <<"/"<<array[i]->departure.day<<"/"<<array[i]->departure.year
            <<" "<<array[i]->departure.hours<<":"<<array[i]->departure.minutes;
        // Print out flight cost. 
        cout << endl << "\tBase Price: $" << array[i]->price - array[i]->getBaggageFees(bags) ;
        cout << " + Baggage fees: $" << array[i]->getBaggageFees(bags) << " = Flight Total: $" << array[i]->price;
    }
	cout<< endl << "\nChecked " << bags << " bags total." <<endl;
    cout<<"Total time: "<< time << endl;
    cout<<"Total cost: $"<< cost <<endl;
}

// Method will calculate the shortest travel time between two destinations.
void calculateShortest(HubNode* listHead, string finalDestination, Date_Time passedInTime, int bagsCheck) {
	// Sets up temporary variables we will use through this method.
    HubNode *hubIter = new HubNode;
    FlightNode* phxFlights = new FlightNode;
    HubNode* firstFlightHub = new HubNode;
    HubNode* secondFlightHub = new HubNode;
    FlightNode *secondLevelFlights = new FlightNode;
    FlightNode* finalRoute[2] = {};
    int level1Time, level2Time, fastestOverall = 1000000;

    // Sets header to the list.
    hubIter = listHead;
   
    // Add baggage fees to ALL flights. THen check according to their adjusted price.
    while ( hubIter != NULL) {
        FlightNode *flightIterator = new FlightNode;
        flightIterator = hubIter->headFlights;
        //while there is something in the list, it prints everything out
		while(flightIterator != NULL) {
            flightIterator->price += flightIterator->getBaggageFees(bagsCheck);
			flightIterator = flightIterator->next;
		}
        hubIter = hubIter->next;
        delete flightIterator;
        flightIterator = NULL;
    }
    // Set back to the head since we just traversed.
    hubIter = listHead;
    
    // Move to start at PHX.
    while ( hubIter != NULL && hubIter->name != "Phoenix Sky Harbor International Airport") {
        hubIter = hubIter->next;
    }
    
    // Start from phoenix's flights out.
    phxFlights = hubIter->headFlights;
    
    while ( phxFlights != NULL ) {
        firstFlightHub = phxFlights->destination;
        
        if( firstFlightHub->location.compare(finalDestination) == 0 ) {
            // Check that this flight is later than the user's desired date
            if (isLater(passedInTime, phxFlights->departure) == true) {
                if (phxFlights->duration < fastestOverall){
                    // If it is faster than the current fastest, set the flight route to this route.
                    // This is a direct flight so it is only one.
                    fastestOverall = phxFlights->duration;
                    finalRoute[0] = phxFlights;
                    finalRoute[1] = phxFlights;
                    cout << firstFlightHub->name << endl;
                }
            }
        }
        else {
            secondLevelFlights = getFlights(listHead, firstFlightHub->name);
            
            level1Time = phxFlights->duration;
            
            while ( secondLevelFlights != NULL ) {
                secondFlightHub = secondLevelFlights->destination;
                if (secondFlightHub->location.compare(finalDestination) == 0 ) {
                    level2Time = secondLevelFlights->duration;
                    phxFlights->departure.AddMinutes(phxFlights->duration);
                    // Check that the second flight IS later than the first one.
                    if (isLater(phxFlights->departure, secondLevelFlights->departure) == true) {
                        if ((level1Time + level2Time) < fastestOverall ){
                            // If this route (flight one + flight two) is the fastest, set route to this.
                            fastestOverall = (level1Time + level2Time);
                            finalRoute[0] = phxFlights;
                            finalRoute[1] = secondLevelFlights;
                        }
                    }
                }
                secondLevelFlights = secondLevelFlights->next;
            }
        }
        phxFlights = phxFlights->next;
    }
    printRoute(finalRoute, bagsCheck);
    cout<<endl;
    
    delete hubIter;
    hubIter = NULL;
    phxFlights = NULL;
    firstFlightHub = NULL;
    secondFlightHub = NULL;
    secondLevelFlights = NULL;
}

// Method to calculate the cheapest flight between the source and the destination.
void calculateCheapest(HubNode* listHead, string finalDestination, Date_Time passedInTime, int bagsCheck) {
    // Just like the other method except changing time for price.
    HubNode *hIter = new HubNode;
    FlightNode* pFlights = new FlightNode;
    HubNode* fFlightHub = new HubNode;
    HubNode* sFlightHub = new HubNode;
    FlightNode *sLevelFlights = new FlightNode;
    FlightNode* finalRoute[2] = {};
    int level1Time, level2Time, fastestOverall = 1000000;

    hIter = listHead;
    
    // Add baggage fees to ALL flights. Then check according to their adjusted price.
    while ( hIter != NULL) {
        FlightNode *flightIterator = new FlightNode;
        flightIterator = hIter->headFlights;
        //while there is something in the list, it prints everything out
		while(flightIterator != NULL) {
            flightIterator->price += flightIterator->getBaggageFees(bagsCheck);
			flightIterator = flightIterator->next;
		}
        hIter = hIter->next;
        
        delete flightIterator;
        flightIterator = NULL;
    }
    hIter = listHead;
    
    // Move to start at PHX.
    while ( hIter != NULL && hIter->name != "Phoenix Sky Harbor International Airport") {
        hIter = hIter->next;
    }
    
    // Start from phoenix's flights out.
    pFlights = hIter->headFlights;
    
    while ( pFlights != NULL ) {
        fFlightHub = pFlights->destination;

        if( fFlightHub->location.compare(finalDestination) == 0 ) {
            // Checks that the flight is later than the user's desire departure. 
            if (isLater(passedInTime, pFlights->departure) == true) {
                if (pFlights->price < fastestOverall){
                    fastestOverall = pFlights->price;
                    finalRoute[0] = pFlights;
                    finalRoute[1] = pFlights;
                }
            }
        }
        else {
            sLevelFlights = getFlights(listHead, fFlightHub->name);
            
            level1Time = pFlights->price;
            
            while ( sLevelFlights != NULL ) {
                sFlightHub = sLevelFlights->destination;
                if (sFlightHub->location.compare(finalDestination) == 0 ) {
                    level2Time = sLevelFlights->price;
                    pFlights->departure.AddMinutes(pFlights->duration);
                    // Check that the second flight IS later than the first one.
                    if (isLater(pFlights->departure, sLevelFlights->departure) == true) {
                        // If this time added to the first flight's time is faster overall:
                        if ((level1Time + level2Time) < fastestOverall ){
                            fastestOverall = (level1Time + level2Time);
                            finalRoute[0] = pFlights;
                            finalRoute[1] = sLevelFlights;
                        }
                    }
                }
                sLevelFlights = sLevelFlights->next;
            }
        }
        pFlights = pFlights->next;
    }
    printRoute(finalRoute, bagsCheck);
    cout<<endl;
    
    delete hIter;
    hIter = NULL;
    pFlights = NULL;
    fFlightHub = NULL;
    sFlightHub = NULL;
    sLevelFlights = NULL;
}

// Displays the menu for the user. Main control of the program.
void menu(HubNode *head) {
    // Variables we will use while the user traverses the menu.
    int day, month, bags, dlocation, routeSetting, year;
    string destinationFormatted;
    Date_Time userFirstChoice;
    char menu; //print the menu and make the user select an option
    
    // Header (does not need to print out every time).
    cout << "Acuna Matata's Flight Agency"<<endl;
    
    do{
        cout << "\t Menu Selections:"<<endl;
        cout << "\t\t a: Purchase Flight Ticket"<<endl;
        cout << "\t\t q: Quit"<<endl;
        cout << "Choice Selection: ";
        cin >> menu;
        
        switch (menu) {
                //Buying a flight ticket
            case 'a':
                // Destination.
                do {
                    cin.clear();
                    cin.ignore();
                    cout << "\nWhere would you like to travel to?"
                    <<"(Enter the Number corresponding to your destination)"<<endl
                    <<"1: Tucson"<<endl
                    <<"2: Los Angeles"<<endl
                    <<"3: San Francisco"<<endl
                    <<"4: San Diego"<<endl
                    <<"5: Albany"<<endl
                    <<"6: Chicago"<<endl
                    <<"7: Boston"<<endl
                    <<"8: Las Vegas"<<endl
                    <<"9: New York"<<endl
                    <<"10: Miami"<<endl
                    <<"11: Honolulu"<<endl
                    <<"12: Denver"<<endl;             
                    cin >> dlocation;
                } while (dlocation > 12 || dlocation < 1);
                
                // End input validation prior to using switch.
                switch (dlocation) {
                    case 1: destinationFormatted = "Tucson";
                        break;
                    case 2: destinationFormatted = "Los Angeles";
                        break;
                    case 3: destinationFormatted = "San Francisco";
                        break;
                    case 4: destinationFormatted = "San Diego";
                        break;
                    case 5: destinationFormatted = "Albany";
                        break;
                    case 6: destinationFormatted = "Chicago";
                        break;
                    case 7: destinationFormatted = "Boston";
                        break;
                    case 8: destinationFormatted = "Las Vegas";
                        break;
                    case 9: destinationFormatted = "New York";
                        break;
                    case 10: destinationFormatted = "Miami";
                        break;
                    case 11: destinationFormatted = "Honolulu";
                        break;
                    case 12: destinationFormatted = "Denver";
                        break;
                        // No default needed b/c of input validation.
                }
                
                // Get the year
                do {
                    cin.clear();
                    cin.ignore();
                    cout << endl<< "What year would you like to depart on? (Enter in numerical form): ";
                    cin >> year;
                    if (year < 2013) {
                        cout << endl << "Please enter a valid year to depart on.";
                    }
                } while (year < 2013);
                
                // Get the Month.
                do {
                    cin.clear();
                    cin.ignore();
                    cout << "\nWhat month would you like to depart on? (Please enter in numerical form): ";
                    cin >> month;
                    if (month < 1 || month > 12)
                    {
                        cout << "\nPlease enter a valid month to depart on.";
                    }
                } while (month < 1 || month > 12);
                
                // Get the Day
                do {
                    cin.clear();
                    cin.ignore();
                    cout << "\nWhat day would you like to depart on? (Please enter in numerical form): ";
                    cin >> day;
                    if (day < 1 || day > 30)
                    {
                        cout << "\nPlease enter a valid day to depart on.";
                    }
                } while (day < 1 || day > 30);
                
                // New Date_Time based off when the user would like to depart on.
                userFirstChoice = Date_Time(0, 0, day, month, year);
                
                // Get Bags checked
                do {
                    cin.clear();
                    cin.ignore();
                    cout <<endl<< "How many bags would you like to check?: ";
                    cin >> bags;
                } while (bags < 0);
                
                // What type of search? Fastest/Cheapest
                do {
                    cout << endl<< "Would you like the fastest, or the cheapest route?";
                    cout << endl<< "0: Fastest" << endl << "1: Cheapest";
                    cin >> routeSetting;
                    
                } while (routeSetting < 0 || routeSetting > 1);

                // Matching Function.
                switch (routeSetting) {
                    case 0:
                        calculateShortest(head, destinationFormatted, userFirstChoice, bags);
                        break;
                    case 1:
                        calculateCheapest(head, destinationFormatted, userFirstChoice, bags);
                        break;
                }
                
                // Now quit the program after printing (printing is done in calculate).
                menu = 'q';
                break;

            case 'q': //Quit menu
                break;
            default: //incorrect case error message
                cout << "\nPlease choose a valid option."<<endl;
        }
    } while (menu != 'q');
}