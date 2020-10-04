#include <iostream>
#include <list>
#include <regex>

#include "EventDB.h"

using std::cin;
using std::cout;
using std::endl;

static void addNewEvent(EventDB&);
static void getEvents(EventDB&, bool =false);
static std::string getDate();
static std::string getName();
static std::string getDescription();
static bool isValidDate(std::string);
void displayEvent(myEvent toDisplay, bool = false);
void deleteEvent(EventDB&);

int main()
{
    EventDB handler;
    enum ProgramControl { addEvent = '1', viewEvents = '2', viewEventsRange = '3', removeEvent = '4', programExit = 'q' };
    char userChoice;
    do {
        cout << "Personnal Planner (Date ranges: 1900-2099).\n"
            << "1 - Add an event for a date | 2 - View events for a certain day | 3 - View events for a range of dates | 4 - Delete a record by ID | q - Exit: ";
        cin>>userChoice;
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
        case removeEvent:
            deleteEvent(handler);
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
        getDate(),         
        getName(),         
        getDescription()    //Get description - maybe multiple lines.
    };
    if (handler.addEvent(toAdd)) {
        cout << "Succesfully added an event.\n";
    }
    else cout << "Could not add an event.\n";
}
static void getEvents(EventDB& handler, bool multiple)
{
    std::list<myEvent> eventList;
	cout << "Starting Date. ";
	std::string dateFrom = getDate();
    std::string dateTo;
	if (multiple) {
		cout << "Ending Date. ";
		dateTo = getDate();
	}
	else {
		dateTo = dateFrom;
	}
    eventList = handler.getEvents(dateFrom, dateTo);
    if (eventList.size()) {
        for (auto i : eventList) {
            displayEvent(i);
        }
    }
    else {
        cout << "No results found. \n";
        return;
    }
    cout << "Please enter ID do view detailed information: ";
    int inputId;
    cin >> inputId;
    myEvent selectedEvent;
    for (auto i : eventList) {
        if (i.id == inputId){
            selectedEvent = i;
        }
    }
    if (selectedEvent.id != 0)
        displayEvent(selectedEvent, true);
    else cout << "Could not find a record with specified ID.\n";
}
static std::string getDate()    //Makes sure to pass a valid date in a string format.
{
    std::string input;
    do {
        cout << "Please provide a date in YYYY-MM-DD format: ";
        cin >> input;
    } while (!isValidDate(input));
    return input;
}
static std::string getName()
{
    std::string entry;
    cout << "Please provide a title for the event: ";
    cin >> entry;
    return entry;
    
}
static std::string getDescription()
{
    std::string desc;
    std::string line;
    cout << "Please provide a description for the event (multiline, may leave blank. enter 'c' to stop recording):\n";
    while (getline(cin, line))
    {
        if (line == "c")
            break;

        desc += line;
    }
    return desc;
}
static bool isValidDate(std::string toVerify)
{
    std::regex checkranges("^(19|20)\\d\\d[-](0[1-9]|1[012])[-](0[1-9]|[12][0-9]|3[01])$"); //This regular expression checks if dates are from 1900-2099
    if (!std::regex_match(toVerify, checkranges))                                     //However, date such as 1998-02-31 is still allowed.
        return false;
    int year, month, day;
    year = std::stoi(toVerify.substr(0,4));
    month = std::stoi(toVerify.substr(5, 2));
    day = std::stoi(toVerify.substr(8, 2));
    const int lookup_table[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
    if (day > lookup_table[month - 1]) {
        return false;
    }
    if ((month == 2) && (day == 29) && (year % 4 != 0))
        return false;
    if ((month == 2) && (day == 29) && (year % 400 == 0))
        return true;
    if ((month == 2) && (day == 29) && (year % 100 == 0))
        return false;
    return true;
}
void displayEvent(myEvent toDisplay, bool detailed)
{
    cout << "ID: " << toDisplay.id
        << " | Date: " << toDisplay.date
        << " | Title: " << toDisplay.name << '\n';
    if (detailed)
        cout << "Description:\n" << toDisplay.description << '\n';
}
void deleteEvent(EventDB& handler)
{
    int id;
    cout << "Please enter an ID of event: ";
    cin >> id;
    if (handler.deleteEvent(id))
        cout << "Succesfully deleted an event\n";
    else
        cout << "Could not delete event with this ID.\n";
}