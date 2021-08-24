
#ifndef BUTTERFLY_AESKEYDATABASE_H
#define BUTTERFLY_AESKEYDATABASE_H

#include "sqlDatabase.h"
#include "exceptions.h"
#include "utils.h"

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
     *
     * @param dbpath:
     * @param removeDatabase:
     * @param dbtable:
     */
    explicit AESKeyDatabase(const std::string &dbpath, bool removeDatabase=false, std::string dbtable="AES");

    /**
     * Destructor AESKeyDatabase
     */
    ~AESKeyDatabase() override;

    /**
     *
     * @param filepath
     * @param aesKey
     * @param aesIv
     */
    void insertEntry(const std::string &filepath, const std::string &aesKey, const std::string &aesIv);
    void getEntry(const std::string &filepath);
    void deleteEntry(const std::string &filepath);

};

} // namespace butterfly

#endif //BUTTERFLY_AESKEYDATABASE_H
