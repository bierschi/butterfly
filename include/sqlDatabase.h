
#ifndef BUTTERFLY_SQLDATABASE_H
#define BUTTERFLY_SQLDATABASE_H

#include <iostream>
#include <vector>

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
    char* _errorMsg;

protected:
    std::string _dbpath, _dbtable;

    SQLDatabase(const std::string &dbpath, const std::string &dbtable);

public:

    /**
     * Constructor SQLDatabase
     */
    explicit SQLDatabase();

    /**
     * Destructor SQLDatabase
     */
    virtual ~SQLDatabase() = default;

    /**
     * Sets the sql config mode
     *
     * @param mode: int number for sqlite3_config call
     * @return true if setting was successful
     */
    static bool setMode(int mode);

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
    bool query(const std::string &query, int (*callback)(void*, int, char**, char**) = nullptr, void *data = nullptr);

    /**
     * Prints the content of the database
     */
    void print();

    /**
     * Print database callback
     *
     * @param data: data for the callback
     * @param argc: Number of columns
     * @param azData: Array of pointers to the strings
     * @param azColName: Array of pointers to strings
     * @return SQLITE_OK
     */
    static int printDatabaseCallback(void *data, int argc, char **azData, char **azColName);

    /**
     * Get column data from database table
     *
     * @param data: data for the callback
     * @param argc: Number of columns
     * @param azData: Array of pointers to the strings
     * @param azColName: Array of pointers to strings
     * @return SQLITE_OK
     */
    static int getColumnDataCallback(void *data, int argc, char **azData, char **azColName);
};

} // namespace butterfly

#endif //BUTTERFLY_SQLDATABASE_H
