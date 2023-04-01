#include "blockchain.h"
#include "utils.h"
#include "pow.h"

std::string CBlockchain::db_path = "/Users/sjrrr/Fudan/Study/Blockchain/JRChain/resource/jr_db";
const std::string CBlockchain::last_key = "l";

/*
 * 打开一个数据库文件，如果文件里已经存储了一个区块链：
 * - 创建一个新的 Blockchain 实例
 * - 设置 Blockchain 实例的 tip 为数据库中存储的最后一个块的哈希
 * 如果没有区块链：
 * - 创建创世块
 * - 存储到数据库
 * - 将创世块哈希保存为最后一个块的哈希
 * - 创建一个新的 Blockchain 实例，初始时 tip 指向创世块
 */
CBlockchain::CBlockchain()
{
    db = utils::OpenDB(db_path);
    utils::LoadData(db, last_key, &tip);
    if (tip.length() == 0) // No blockchain exists, create a new one.
    {
        std::cout << "No blockchain exists, create a new one" << std::endl
                  << std::endl;
        BLOCK *b = block::NewGenesisBlock();
        utils::StoreData(db, b->get_hash(), utils::Serialize(b));
        utils::StoreData(db, last_key, b->get_hash());
        tip = b->get_hash();
    }
    else
    {
        std::cout << "Successfully load blockchain" << std::endl
                  << std::endl;
    }
}

void CBlockchain::AddBlock(std::string data)
{
    BLOCK *b = new BLOCK(tip, data);
    utils::StoreData(db, b->get_hash(), utils::Serialize(b));
    utils::StoreData(db, last_key, b->get_hash());
    tip = b->get_hash();
}

void CBlockchain::Show()
{
    std::string h = tip;
    int i = 1;
    CProofOfWork pow = CProofOfWork();
    BLOCK *b = GetBlock(h);

    while (b != nullptr)
    {
        pow.set_block(b);

        std::cout << "Height: " << i << std::endl;
        std::cout << "Prev Hash: " << b->get_prev_hash() << std::endl;
        std::cout << "Hash: " << b->get_hash() << std::endl;
        std::cout << "Data: " << b->get_data() << std::endl;
        std::cout << "Nonce: " << b->get_nonce() << std::endl;
        std::cout << "PoW: " << (pow.Validate() > 0 ? "true" : "false") << std::endl;
        std::cout << std::endl;

        h = b->get_prev_hash();
        b = GetBlock(h);
        ++i;
    }
}

BLOCK *CBlockchain::GetBlock(std::string hash) const
{
    std::string data;
    utils::LoadData(db, hash, &data);
    if (data.length() > 0)
        return utils::Deserialize(data);
    else
        return nullptr;
}

CBlockchain::~CBlockchain()
{
    delete db;
}
