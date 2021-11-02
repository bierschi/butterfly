
#ifndef BUTTERFLY_AESKEYDATABASE_H
#define BUTTERFLY_AESKEYDATABASE_H

#include "sqlDatabase.h"
#include "bflyExceptions.h"
#include "bflyUtils.h"

namespace butterfly
{

/**
 * Class AESKeyDatabase to save the AES Keys in a database file
 */
class AESKeyDatabase : public SQLDatabase
{

private:
    std::string _aesKeyTableSQL;
    bool _removeDatabase;

public:

    /**
     * Constructor AESKeyDatabase
     *
     * @param dbpath: path to the db file
     * @param removeDatabase: boolean to remove the database file or not
     * @param dbtable: db table name
     */
    explicit AESKeyDatabase(const std::string &dbpath, bool removeDatabase=false, std::string dbtable="AES");

    /**
     * Destructor AESKeyDatabase
     */
    ~AESKeyDatabase() override;

    /**
     * Insert an new entry in the database table
     *
     * @param filepath: path to the file from the encryption
     * @param aesKey: aes key from the encryption
     * @param aesIv: aes iv from the encryption
     */
    void insertEntry(const std::string &filepath,  const std::string &aesKey, const std::string &aesIv);

    /**
     * Get an entry from the database table
     *
     * @param filepath: path to the file
     * @return column data as std::vector<std::string>
     */
    std::vector<std::string> getEntry(const std::string &filepath);

    /**
     * Deletes an entry from the database table
     *
     * @param filepath: path to the file
     */
    void deleteEntry(const std::string &filepath);

};

} // namespace butterfly

#endif //BUTTERFLY_AESKEYDATABASE_H
