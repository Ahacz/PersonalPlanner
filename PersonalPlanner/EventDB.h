#pragma once
#include <iostream>
#include <vector>
#include "sqlite3.h"

struct myEvent {
	int id;
	std::string date;
	std::string name;
	std::string description;
};
class EventDB
{
private:
	std::vector<myEvent> loadedEvents;
	myEvent currentEvent;
	sqlite3* DB;
public:
	EventDB() {};
	~EventDB();		//This destructor gets called only at the end of the program. 
	EventDB(EventDB const&) = delete;
	void operator = (EventDB const&) = delete;
	void loadEvents(std::string&, std::string&, std::vector<myEvent>&);
	void addEvent();
	bool init(std::string);
};

