# PersonalPlanner
A crude personal planner made as an exercise for BCF

This program uses an SQLite database to store events. The program itself makes sure data is passed to database in correct format. 
Database handling is done by a class called EventDB, which takes care of using the database by exposing certain methods. This makes the code much easier to read. 
The program itself allows for addition, removal of events. The user may input dates between 1900-01-01 and 2099-12-31. 
Checks for correct dates as well as multiline input for description are done by the main function. 
The structure of database consists of a single table using columns ID, DATE, TITLE, DESCRIPTION. ID is simultaneusly ROWID as it is the primary key. 
Retrieving the data is done by using sqlite3_exec in combination with a custom callback function, appending rows to a list of structures.

Technologies used: SQLite, STL list, regular expressions.
