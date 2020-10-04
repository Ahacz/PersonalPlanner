#pragma once
#include <iostream>
#include <list>
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
	sqlite3* DB;
	std::list<myEvent>resultList;
public:
	
	EventDB();
	~EventDB();
	EventDB(EventDB const&) = delete;		//Prevent copying EventDB objects.
	void operator = (EventDB const&) = delete;
	std::list<myEvent> getEvents(std::string&, std::string&);
	void getSingleEvent(int&);
	bool addEvent(myEvent&);
	bool updateEvent(myEvent&);
	//bool deleteEvent(int&);
	void init(std::string);
};

