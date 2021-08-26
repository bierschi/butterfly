
#include "sqlDatabase.h"

namespace butterfly
{

SQLDatabase::SQLDatabase(const std::string &dbpath, const std::string &dbtable) : _db(nullptr), _errorMsg(nullptr),
                                                                                  _dbpath(dbpath), _dbtable(dbtable)
{
    LOG_TRACE("Create Class SQLDatabase");
}

SQLDatabase::SQLDatabase() : _db(nullptr), _errorMsg(nullptr)
{
    LOG_TRACE("Create Class SQLDatabase");
}

bool SQLDatabase::setMode(int mode)
{
    if ( sqlite3_config(mode) != SQLITE_OK )
    {
        LOG_ERROR("Error on setting the sqlite config mode!")
        return false;
    }
    return true;
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
    if ( sqlite3_close(_db) != SQLITE_OK )
    {
        LOG_ERROR("Error on closing database " << _dbpath)
        return false;
    }
    return true;
}

bool SQLDatabase::query(const std::string &query, int (*callback)(void*, int, char**, char**), void *data)
{

    if ( _db != nullptr)
    {

        if (sqlite3_exec(_db, query.c_str(), callback, data, &_errorMsg) != SQLITE_OK )
        {
            LOG_ERROR("Error on executing database query: " << _errorMsg);
            return false;
        } else
        {
            LOG_TRACE("Successfully executed query: " << query);
            return true;
        }
    } else
    {
        LOG_ERROR("_db handler is not initialized!")
        return false;
    }

}

void SQLDatabase::print()
{
    if ( !_dbtable.empty() )
    {
        query("SELECT * FROM " + _dbtable + ";", printDatabaseCallback);
    }

}

int SQLDatabase::printDatabaseCallback(void *, int argc, char **argv, char **azColName)
{

    for(int i = 0; i< argc; i++)
    {
        LOG_TRACE(azColName[i] << ": " << argv[i]);
    }

    return SQLITE_OK;

}

int SQLDatabase::getColumnDataCallback(void *data, int argc, char **azData, char **)
{

    auto *columnData = static_cast<std::vector<std::string>*>(data);

    for(int i = 0; i < argc; i++)
    {
        columnData->push_back(azData[i]);
    }

    return SQLITE_OK;

}

} // namespace butterfly
