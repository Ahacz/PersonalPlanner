#include "EventDB.h"

using std::string;

EventDB::EventDB() {}
EventDB::~EventDB() 
{
    sqlite3_close(DB);  //Close the database connection.
}


bool EventDB::init(string filename)     //Filename should be provided along with an extension.
{
    int exit = 0;
    exit = sqlite3_open(filename.c_str(), &DB);
    if (exit) {
        std::cerr << "Error opening/creating DB " << sqlite3_errmsg(DB) << std::endl;
        return (false);
    }
    string sql = "CREATE TABLE IF NOT EXISTS events("
        "ID INT PRIMARY KEY     NOT NULL, UNIQUE "
        "DATE           TEXT    NOT NULL, "
        "TITLE          TEXT    NOT NULL, "
        "DESCRIPTION    TEXT    NOT NULL, );";
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening/creating the table." << std::endl;
        sqlite3_free(messaggeError);
        return (false);
    }
    return true;
}

bool EventDB::addEvent(myEvent& toAdd)
{

}
bool EventDB::updateEvent(myEvent& toUpdate)
{

}

myEvent EventDB::getSingleEvent(int& id)
{

}

std::list<myEvent> EventDB::getEvents(string& from, string& to)
{

}