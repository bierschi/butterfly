
#include "aesKeyDatabase.h"

namespace butterfly
{

AESKeyDatabase::AESKeyDatabase(const std::string &dbpath, bool removeDatabase, std::string dbtable) : SQLDatabase(dbpath, dbtable), _removeDatabase(removeDatabase)
{

    LOG_TRACE("Create Class AESKeyDatabase");

    // enable multithread environment
    if ( !setMode(SQLITE_CONFIG_SERIALIZED) )
    {
        LOG_ERROR("Could not set the mode to serialized in AESKeyDatabase");
    }

    // open database
    if ( !open(dbpath) )
    {
        throw SQLDatabaseException("Error on opening database " + _dbpath);
    }

    _aesKeyTableSQL = "CREATE TABLE IF NOT EXISTS " + _dbtable + " (FILEPATH TEXT PRIMARY KEY, AESKEY BLOB, AESIV BLOB);";

    if ( !query(_aesKeyTableSQL) )
    {
        LOG_ERROR("Error on creating " << _dbtable << " Table!");
    }

}

AESKeyDatabase::~AESKeyDatabase()
{
    if ( close() )
    {
        if ( _removeDatabase && butterfly::removeFile(_dbpath) )
        {
            LOG_INFO("Removed the database file " << _dbpath);
        }

    }
}

void AESKeyDatabase::insertEntry(const std::string &filepath, const std::string &aesKey, const std::string &aesIv)
{

    std::string sql = "INSERT INTO AES(FILEPATH, AESKEY, AESIV) VALUES('" + filepath + "', '" + aesKey + "', '" + aesIv + "');";

    query(sql);

}

std::vector<std::string> AESKeyDatabase::getEntry(const std::string &filepath)
{
    std::vector<std::string> colData;

    std::string sql = "SELECT * FROM " + _dbtable +  " WHERE FILEPATH='" + filepath + "';";
    query(sql, getColumnDataCallback, &colData);

    return colData;
}

void AESKeyDatabase::deleteEntry(const std::string &filepath)
{

    std::string sql = "DELETE FROM " + _dbtable + " WHERE FILEPATH='" + filepath + "';";

    query(sql);

}

} // namespace butterfly

