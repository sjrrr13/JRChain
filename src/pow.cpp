#include "pow.h"
#include <iostream>

std::string CProofOfWork::target;

std::string CProofOfWork::PrepareData(int nonce) {
    std::string data = b->get_prev_hash();
    data += b->get_data();
    data += utils::IntToHex(b->get_timestamp());
    data += utils::IntToHex((int64_t) target_bits);
    data += utils::IntToHex((int64_t) nonce);

    return data;
}

CProofOfWork::CProofOfWork() {
    b = nullptr;

    if (target.length() > 0)
        return;

    for (int i = 0; i < target_bits; ++i)
        target += "0";
    target += "1";
    for (int i = 0; i < all_bits - target_bits - 1; ++i)
        target += "0";
}

bool CProofOfWork::Validate() {
    if (b == nullptr) {
        std::cout << "No block to validate" << std::endl;
        return false;
    }

    std::string data = PrepareData(b->get_nonce());
    return (utils::MyHash(data).compare(target) < 0);
}

std::pair<int, std::string> CProofOfWork::Run() {
    if (b == nullptr) {
        std::cout << "No block given" << std::endl;
        return std::make_pair(-1, "");
    }

    std::cout << "Mining the block with data \"" << b->get_data() << "\"" << std::endl;

    int nonce = 0;
    std::string data, hash;
    while (nonce < max_nonce) {
        data = PrepareData(nonce);
        hash = utils::MyHash(data);
        if (hash.compare(target) <= 0) {
            std::cout << "hash is " << hash << std::endl;
            break;
        } else {
            ++nonce;
        }
    }
    std::cout << std::endl;

    return std::make_pair(nonce, hash);
}

void CProofOfWork::set_block(BLOCK *bp) {
    this->b = bp;
}
