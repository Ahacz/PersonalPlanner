#include "EventDB.h"
#include <string>

using std::string;

int callbackResults(void*, int, char**, char**);
EventDB::EventDB() 
{
    init("Events.db");
    resultList.clear();
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
        "ID INT PRIMARY KEY, "
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
        return false;
    }
    return true;
}
bool EventDB::deleteEvent(int& id)
{
    string sql = "DELETE FROM events WHERE ROWID = " + std::to_string(id) + "; ";
    int exit;
    char* messageError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Delete" << std::endl;
        sqlite3_free(messageError);
        return false;
    }
    return true;
}

std::list<myEvent> EventDB::getEvents(string& from, string& to)
{
    resultList.clear();         //Empty the list before filling it.
    int exit;
    char* messageError;
    string sql("SELECT ROWID,DATE,TITLE,DESCRIPTION FROM events WHERE date BETWEEN '"+from+"' AND '"+to+"';");    
    exit = sqlite3_exec(DB, sql.c_str(), callbackResults, (void*)&resultList, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Select" << std::endl;
        sqlite3_free(messageError);
    }
    return resultList;
}

int callbackResults(void* list, int count, char** fieldValue, char** columnName) 
{
    myEvent tmp;
    tmp.id = std::stoi(fieldValue[0]?fieldValue[0]:"0");
    tmp.date = fieldValue[1] ? fieldValue[1] : "NULL";
    tmp.name = fieldValue[2] ? fieldValue[2] : "NULL";
    tmp.description = fieldValue[3] ? fieldValue[3] : "NULL";
    static_cast<std::list<myEvent>*>(list)->emplace_back(tmp);
    return 0;
}