//
// Created by Jiarui She on 2023/3/9.
//

#include <utility>
#include <sys/time.h>

#include "pow.h"

BLOCK::BLOCK(std::string ph, std::string d) :
        prev_hash(std::move(ph)),
        data(std::move(d)) {
    set_timestamp();
    set_hash();
}

BLOCK::BLOCK(long long t, std::string ph, std::string h, std::string d, int n) :
        timestamp(t),
        prev_hash(std::move(ph)),
        hash(std::move(h)),
        data(std::move(d)),
        nonce(n) {}

void BLOCK::set_timestamp() {
    struct timeval tv{};
    gettimeofday(&tv, nullptr);
    this->timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void BLOCK::set_hash() {
    CProofOfWork pow = CProofOfWork();
    pow.set_block(this);
    std::pair<int, std::string> temp = pow.Run();
    this->nonce = temp.first;
    this->hash = temp.second;
}

std::string BLOCK::get_prev_hash() const {
    return prev_hash;
}

std::string BLOCK::get_hash() const {
    return hash;
}

std::string BLOCK::get_data() const {
    return data;
}

std::int64_t BLOCK::get_timestamp() const {
    return timestamp;
}

int BLOCK::get_nonce() const {
    return nonce;
}

std::string BLOCK::Serialize() const {

    return "";
}

BLOCK *block::NewGenesisBlock() {
    return new BLOCK("", "New Genesis Block");
}
