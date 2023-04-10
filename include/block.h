//
// Created by Jiarui She on 2023/3/9.
//

#ifndef JRCHAIN_BLOCK_H
#define JRCHAIN_BLOCK_H

#include <string>

struct BLOCK {
private:
    long long timestamp;
    std::string prev_hash,
            hash,
            data;
    int nonce;

    void set_timestamp();

    void set_hash();

public:
    BLOCK(std::string, std::string);

    BLOCK(long long, std::string, std::string, std::string, int);

    std::string get_prev_hash() const;

    std::string get_hash() const;

    std::string get_data() const;

    std::int64_t get_timestamp() const;

    int get_nonce() const;
};

namespace block {
    BLOCK* NewGenesisBlock();
}

#endif //JRCHAIN_BLOCK_H
