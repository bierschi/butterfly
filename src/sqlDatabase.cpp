
#include "sqlDatabase.h"

namespace butterfly
{

SQLDatabase::SQLDatabase() : _db(nullptr)
{
    LOG_TRACE("Create Class SQLDatabase");

}

SQLDatabase::~SQLDatabase()
{
    if (sqlite3_close(_db) != SQLITE_OK )
    {
        LOG_ERROR("Error on closing database " << _dbpath)
    }
}

bool SQLDatabase::open(const std::string &dbpath)
{

    if ( sqlite3_open(dbpath.c_str(), &_db) != SQLITE_OK)
    {
        LOG_ERROR("Error on opening database file " << dbpath);
        return false;
    }

    _dbpath = dbpath;

    return true;
}

bool SQLDatabase::close()
{
    if (sqlite3_close(_db) != SQLITE_OK )
    {
        LOG_ERROR("Error on closing database " << _dbpath)
        return false;
    }
    return true;
}

bool SQLDatabase::query(const std::string &query, int (*callback)(void*, int, char**, char**), void *data) const
{

    if ( _db != nullptr)
    {
        if ( sqlite3_exec(_db, query.c_str(), callback, data, nullptr) != SQLITE_OK )
        {
            LOG_ERROR("Error on executing database query: " << query);
            return false;
        } else
        {
            LOG_TRACE("Executed query: " << query);
            return true;
        }
    } else
    {
        LOG_ERROR("_db handler is not initialized!")
        return false;
    }

}

void SQLDatabase::print() const
{
    query("SELECT * FROM *;", printDatabaseCallback);
}

int SQLDatabase::printDatabaseCallback(void *, int argc, char **argv, char **azColName)
{
    for(int i = 0; i< argc; i++)
    {
        LOG_INFO(azColName[i] << "\t: " << argv[i]);
    }
    return SQLITE_OK;
}

} // namespace butterfly
