//
// Created by Jiarui She on 2023/2/19.
//

#ifndef JRCHAIN_UTILS_H
#define JRCHAIN_UTILS_H

#include <string>
#include <leveldb/db.h>

#include "block.h"

namespace utils
{
    std::string MyHash(const std::string &);

    std::string IntToHex(int64_t);

    // void OpenDB(leveldb::DB *, const std::string &);

    leveldb::DB *OpenDB(const std::string &);

    void StoreData(leveldb::DB *, const std::string &, const std::string &);

    void LoadData(leveldb::DB *, const std::string &, std::string *);

    std::string Serialize(BLOCK *);

    BLOCK *Deserialize(std::string &);

    void Assert(bool, std::string);
}
#endif // JRCHAIN_UTILS_H
