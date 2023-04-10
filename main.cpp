#include "blockchain.h"

int main()
{
    CBlockchain blockchain = CBlockchain();

    blockchain.AddBlock("Send 1 BTC to SJR");
    blockchain.AddBlock("Send 2 more BTC to SJR");

    blockchain.Show();
    
    return 0;
}
