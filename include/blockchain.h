#ifndef JRCHAIN_BLOCKCHAIN_H
#define JRCHAIN_BLOCKCHAIN_H

#include <vector>
#include <iostream>
#include <leveldb/db.h>

#include "block.h"

class CBlockchain {
private:
    leveldb::DB *db;
    std::string tip;
    static std::string db_path;
    static const std::string last_key;

public:
    CBlockchain();

    void AddBlock(std::string);

    void Show();

    BLOCK* GetBlock(std::string) const;

    ~CBlockchain();
};

#endif //JRCHAIN_BLOCKCHAIN_H
