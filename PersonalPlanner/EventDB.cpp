#include "EventDB.h"

using std::string;

EventDB::EventDB() 
{
    init("Events.db");
}
EventDB::~EventDB() 
{
    sqlite3_close(DB);  //Close the database connection.
}

void EventDB::init(string filename)     //Filename should be provided along with an extension.
{
    int exit = 0;
    exit = sqlite3_open(filename.c_str(), &DB);
    if (exit) {
        std::cerr << "Error opening/creating DB " << sqlite3_errmsg(DB) << std::endl;
        return;
    }
    string sql = "CREATE TABLE IF NOT EXISTS events("
        "ID INT PRIMARY KEY     NOT NULL, UNIQUE "
        "DATE           TEXT    NOT NULL, "
        "TITLE          TEXT    NOT NULL, "
        "DESCRIPTION    TEXT);";
    char* messageError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error opening/creating the table." << std::endl;
        sqlite3_free(messageError);
        return;
    }
    return;
}

bool EventDB::addEvent(myEvent& toAdd)
{
    int exit;
    char* messageError;
    string sql("INSERT INTO events VALUES(NULL, '" + toAdd.date + "', '" + toAdd.name + "', '" + toAdd.description + "');");    //this string adds a record without specifying a key
    //SQLite handles primary key by itself.
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messageError);
    }
}
bool EventDB::updateEvent(myEvent& toUpdate)
{

}

myEvent EventDB::getSingleEvent(__int64& id)
{

}

std::list<myEvent> EventDB::getEvents(string& from, string& to)
{

}