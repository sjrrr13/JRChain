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
CBlockchain::CBlockchain() {
    if (utils::OpenDB(db, db_path)) {
        if (!utils::LoadData(db, last_key, tip)) {
            BLOCK *b = block::NewGenesisBlock();
            utils::StoreData(db, b->get_hash(), b->Serialize());
            utils::StoreData(db, last_key, b->get_hash());
            tip = b->get_hash();
        }
    }
}

void CBlockchain::AddBlock(std::string data) {
    auto *new_block = new BLOCK(tip, std::move(data));
    std::cout << "new block created." << std::endl;
    std::cout << utils::StoreData(db, new_block->get_hash(), utils::Serialize(new_block)) << std::endl;;
    std::cout << utils::StoreData(db, last_key, new_block->get_hash()) << std::endl;
    std::cout << "new block stored." << std::endl;

    tip = new_block->get_hash();
}

void CBlockchain::Show() {
    std::string h = tip;
    int i = 1;
    CProofOfWork pow = CProofOfWork();
    BLOCK *b = GetBlock(h);

    while (b != nullptr) {
        pow.set_block(b);

        std::cout << "Height: " << i << std::endl;
        std::cout << "Prev Hash: " << b->get_prev_hash() << std::endl;
        std::cout << "Data: " << b->get_hash() << std::endl;
        std::cout << "Hash: " << b->get_data() << std::endl;
        std::cout << "Nonce: " << b->get_nonce() << std::endl;
        std::cout << "PoW: " << (pow.Validate() > 0 ? "true" : "false") << std::endl;
        std::cout << std::endl;

        h = b->get_prev_hash();
        b = GetBlock(h);
        ++i;
    }
}

BLOCK *CBlockchain::GetBlock(std::string hash) const {
    std::string data;
    if (utils::LoadData(db, hash, data))
        return utils::Deserialize(data);
    else
        return nullptr;
}

CBlockchain::~CBlockchain() {
    delete db;
}

