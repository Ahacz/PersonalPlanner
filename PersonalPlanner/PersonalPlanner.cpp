#include <iostream>
#include <time.h>
#include <list>

#include "EventDB.h"

using std::cin;
using std::cout;
using std::endl;

static void addNewEvent(EventDB & handler);
static void getEvents(EventDB& handler, bool multiple=false);
static std::string getDate();
static std::string getName();
static std::string getDescription();

int main()
{
    EventDB handler;
    if (!handler.init("Events.db")) {
        cout << "Failed to open database!";
        return -1;
    }
    enum ProgramControl { addEvent = '1', viewEvents = '2', viewEventsRange = '3', programExit = 'q' };
    char userChoice;
    do {
        cout << "Personnal Planner.\n"
            << "1 - Add an event for a date | View events for a certain day | 3 - View and edit events for a range of dates | q - Exit: ";
        cin.get(userChoice);
        switch (userChoice) {
        case addEvent:
            addNewEvent(handler);
            break;
        case viewEvents:
            getEvents(handler);
            break;
        case viewEventsRange:
            getEvents(handler, true);
            break;
        default: break;
        }
    } while (userChoice != programExit);
    return (0);
}

static void addNewEvent(EventDB &handler)
{
    myEvent toAdd{
        0,                  //id - won't be used for adding.
        getDate(),          //Get the date of event
        getName(),          //Get title of event
        getDescription()    //Get description - maybe multiple lines.
    };
    if (handler.addEvent(toAdd)) {
        cout << "Succesfully added an event.\n";
    }
    else cout << "Could not add an event\n";
}
static void getEvents(EventDB& handler, bool multiple)
{
    std::list<myEvent> eventList;
	cout << "Please enter the beginning date in YYYY-MM-DD format: ";
	std::string dateFrom = getDate();
    std::string dateTo;
	if (multiple) {
		cout << "Please enter the ending date in YYYY-MM-DD format: ";
		dateTo = getDate();
	}
	else {
		dateTo = dateFrom;
	}

    //After getting and displaying the list:
    cout << "Please enter ";
    char choice;
    enum RecordControl { viewDetails = '1', viewEvents = '2', programExit = 'q' };
}
static std::string getDate()    //Makes sure to pass a valid date in a string format.
{
    cout << "Please provide a date in YYYY-MM-DD format: ";

}
static std::string getName()
{
    cout << "Please provide a title for the event: ";
}
static std::string getDescription()
{
    std::string desc;
    std::string line;
    cout << "Please provide a description for the event (multiline, may leave blank. enter 'c' to stop recording):\n";
    cin >> line;
    desc = line;    //This way description must contain at least a single character.
    while (line != "c") {
        desc += line + "/n";
        cin >> line;
    }
    return desc.substr(0, desc.size() - 1); //remove the last newline sign
}
