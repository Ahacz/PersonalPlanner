#include <iostream>
#include <time.h>

#include "EventDB.h"

using std::cin;
using std::cout;
using std::endl;

static void addNewEvent(EventDB & handler);
static void getEvents(EventDB& handler);
static std::string getDate();

int main()
{
    EventDB handler;
    if (!handler.init("Events.db")) {
        cout << "Failed to open database!";
        return -1;
    }
    enum ProgramControl { addEvent = '1', viewEvents = '2', programExit = 'q' };
    char userChoice;
    do {
        cout << "Personnal Planner.\n"
            << "1 - Add an event for a date | 2 - View and edit events for a range of dates. | q - Exit: ";
        cin.get(userChoice);
        switch (userChoice) {
        case addEvent:
            addNewEvent(handler);
        case viewEvents:
            getEvents(handler);
        default: break;
        }
    } while (userChoice != programExit);
    return (0);
}

static void addNewEvent(EventDB &handler)
{
    std::string date = getDate();
}
static void getEvents(EventDB& handler)
{

}
static std::string getDate()    //Makes sure to pass a valid date in a string format.
{

}
