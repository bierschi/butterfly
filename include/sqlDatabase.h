
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
    std::string _dbname;

public:

    /**
     * Constructor SQLDatabase
     */
    explicit SQLDatabase();

    /**
     * Destructor SQLDatabase
     */
    ~SQLDatabase();

    bool open(const std::string &dbname);
    void close();

    bool query(const std::string &query);
    void print() const;
};

} // namespace butterfly

#endif //BUTTERFLY_SQLDATABASE_H
