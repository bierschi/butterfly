
#include "sqlDatabase.h"

namespace butterfly
{

SQLDatabase::SQLDatabase() : _db(nullptr)
{
    LOG_TRACE("Create Class SQLDatabase");

}

SQLDatabase::~SQLDatabase()
{
    sqlite3_close(_db);
}

bool SQLDatabase::open(const std::string &dbname)
{

    if ( sqlite3_open(dbname.c_str(), &_db) != SQLITE_OK)
    {
        LOG_ERROR("Error on opening database file " << dbname);
        return false;
    }

    _dbname = dbname;

    return true;
}

void SQLDatabase::close()
{
    sqlite3_close(_db);
}

bool SQLDatabase::query(const std::string &query)
{

    if ( sqlite3_exec(_db, query.c_str(), 0, 0, 0) != SQLITE_OK )
    {
        LOG_ERROR("Error on executing database query: " << query);
        return false;
    }

    return true;
}

void SQLDatabase::print() const
{

}

} // namespace butterfly
