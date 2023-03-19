#include "blockchain.h"
#include "utils.h"

int main()
{
    // leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;

    // open
    leveldb::DB *db = utils::Open("/Users/sjrrr/Fudan/Study/Blockchain/JRChain/resource/test");
    // leveldb::Status status = leveldb::DB::Open(options, "/Users/sjrrr/Fudan/Study/Blockchain/JRChain/resource/test", &db);
    // assert(status.ok());

    std::string key = "keytest";
    std::string value = "this is the value of keytest";

    // write
    utils::StoreData(db, key, value);
    // leveldb::Status status2 = db->Put(leveldb::WriteOptions(), key, value);
    // assert(status2.ok());

    // read
    leveldb::Status status3 = db->Get(leveldb::ReadOptions(), key, &value);
    assert(status3.ok());

    std::cout << "value of " << key << " is " << value << std::endl;

    // delete
    leveldb::Status status4 = db->Delete(leveldb::WriteOptions(), key);
    assert(status4.ok());

    leveldb::Status status5 = db->Get(leveldb::ReadOptions(), key, &value);
    assert(!status5.ok());

    // close
    delete db;

    // leveldb::DB *db;
    // std::string db_path = "/Users/sjrrr/Fudan/Study/Blockchain/JRChain/resource/test";
    // std::cout << utils::OpenDB(db, db_path) << std::endl;
    // std::string k = "0";
    // std::string v = "1";
    // leveldb::Status status = db->Put(leveldb::WriteOptions(), k, v);
    // assert(status.ok());
    //    std::cout << utils::StoreData(db, "00000f9a89ee0a9f9fadcfd5e89a38e0dd2f35e6960b82e86fbe1b02a267f560",
    //    "&T&1678723824562&PH&&H&00000f9a89ee0a9f9fadcfd5e89a38e0dd2f35e6960b82e86fbe1b02a267f560") << std::endl;

    // CBlockchain blockchain = CBlockchain();

    // blockchain.AddBlock("Send 1 BTC to SJR");
    // blockchain.AddBlock("Send 2 more BTC to SJR");

    // blockchain.Show();

    return 0;
}
