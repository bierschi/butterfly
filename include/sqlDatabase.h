
#ifndef BUTTERFLY_SQLDATABASE_H
#define BUTTERFLY_SQLDATABASE_H

#include <iostream>
#include <sqlite3.h>

#include "logger.h"

namespace butterfly
{

/**
 * Class SQLDatabase to provide interaction with sql databases
 */
class SQLDatabase
{
private:
    sqlite3* _db;
    std::string _dbpath;

public:

    /**
     * Constructor SQLDatabase
     */
    explicit SQLDatabase();

    /**
     * Destructor SQLDatabase
     */
    virtual ~SQLDatabase();

    /**
     * Opens the database connection to dbpath
     *
     * @param dbpath: path to a database file
     * @return true if the opening was successful
     */
    bool open(const std::string &dbpath);

    /**
     * Closes the database connection
     *
     * @return true if the closing was successful
     */
    bool close();

    /**
     * Query the database with a query string
     *
     * @param query: sql query string
     * @param callback: callback function
     * @param data: data for the callback function
     * @return true if the query was sucessful
     */
    bool query(const std::string &query, int (*callback)(void*, int, char**, char**)= nullptr, void *data= nullptr) const;

    /**
     * Prints the content of the database
     */
    void print() const;

    /**
     * Print database callback
     *
     * @param data: data for the callback
     * @param argc: Number of columns
     * @param argv: Array of pointers to the strings
     * @param azColName: Array of pointers to strings
     * @return
     */
    static int printDatabaseCallback(void *data, int argc, char *argv[], char *azColName[]);
};

} // namespace butterfly

#endif //BUTTERFLY_SQLDATABASE_H
