//
// Created by Jiarui She on 2023/3/9.
//

#ifndef JRCHAIN_POW_H
#define JRCHAIN_POW_H

#include "block.h"
#include "utils.h"

class CProofOfWork {
private:
    static const int target_bits = 4;
    static const int all_bits = 64;
    static const int max_nonce = INT_MAX;
    static std::string target;
    BLOCK* b;

    std::string PrepareData(int nonce);

public:
    explicit CProofOfWork();

    bool Validate();

    std::pair<int, std::string> Run();

    void set_block(BLOCK* bp);
};

#endif //JRCHAIN_POW_H
