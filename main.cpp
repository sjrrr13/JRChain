#include "blockchain.h"
#include "utils.h"

void db()
{
    leveldb::Options options;
    options.create_if_missing = true;

    // open
    leveldb::DB *db = utils::OpenDB("/Users/sjrrr/Fudan/Study/Blockchain/JRChain/resource/jr_db");
    // leveldb::Status status = leveldb::DB::Open(options, "/Users/sjrrr/Fudan/Study/Blockchain/JRChain/resource/test", &db);
    // assert(status.ok());

    leveldb::Iterator *it = db->NewIterator(leveldb::ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        // std::cout << it->key().ToString() << ": "  << it->value().ToString() << std::endl;
        leveldb::Status status4 = db->Delete(leveldb::WriteOptions(), it->key().ToString());
        assert(status4.ok());
    }
    assert(it->status().ok()); // Check for any errors found during the scan
    delete it;

    // auto tip = "000a5139656cd6d0bf503cdd95550030b5f35a6a687f0a66e116652f5df865d6";
    // auto *block = new BLOCK(tip, "Send 1 BTC to SJR");
    // auto k = block->get_hash();
    // auto v = utils::Serialize(block);

    // // write
    // utils::StoreData(db, k, v);
    // // leveldb::Status status2 = db->Put(leveldb::WriteOptions(), key, value);
    // // std::cout << status2.ToString() << std::endl;
    // // assert(status2.ok());

    // // read
    // leveldb::Status status3 = db->Get(leveldb::ReadOptions(), k, &v);
    // assert(status3.ok());
    // std::cout << "value of " << k << " is " << v << std::endl;

    // // delete
    // leveldb::Status status4 = db->Delete(leveldb::WriteOptions(), k);
    // assert(status4.ok());

    // leveldb::Status status5 = db->Get(leveldb::ReadOptions(), k, &v);
    // assert(status5.IsNotFound());

    // close
    delete db;
}

void test()
{
    CBlockchain blockchain = CBlockchain();

    blockchain.AddBlock("Send 1 BTC to SJR");
    blockchain.AddBlock("Send 2 more BTC to SJR");

    blockchain.Show();
}

int main()
{
    db();

    test();

    return 0;
}
