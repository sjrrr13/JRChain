#include "utils.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <iostream>

static const std::string T_KEY = "&T&";
static const int T_KEY_LEN = 3;
static const std::string PH_KEY = "&PH&";
static const int PH_KEY_LEN = 4;
static const std::string H_KEY = "&H&";
static const int H_KEY_LEN = 3;
static const std::string D_KEY = "&D&";
static const int D_KEY_LEN = 3;
static const std::string N_KEY = "&N&";
static const int N_KEY_LEN = 3;

namespace utils
{
    /*
     * Use SHA256 as hash function
     */
    std::string MyHash(const std::string &str)
    {
        unsigned char szHash256[32];
        SHA256((const unsigned char *)str.c_str(), str.length(), szHash256);
        std::string result;
        for (unsigned char i : szHash256)
        {
            char szBuf[32] = {0};
            sprintf(szBuf, "%02x", i);
            result += szBuf;
        }
        return result;
    }

    /*
     * Change an integer to a hex 16bits string
     */
    std::string IntToHex(int64_t num)
    {
        std::ostringstream ss;
        ss << std::setfill('0') << std::setw(16) << std::hex << num;

        return ss.str();
    }

    // void OpenDB(leveldb::DB *db, const std::string &db_path)
    // {
    //     leveldb::Options options;
    //     options.create_if_missing = true;
    //     leveldb::Status status = leveldb::DB::Open(options, db_path, &db);

    //     Assert(status.ok(), "Error opening database.");
    // }

    leveldb::DB *OpenDB(const std::string &db_path)
    {
        leveldb::DB *db;
        leveldb::Options options;
        options.create_if_missing = true;
        leveldb::Status status = leveldb::DB::Open(options, db_path, &db);

        Assert(status.ok(), "Error opening database.");

        return db;
    }

    void StoreData(leveldb::DB *db, const std::string &key, const std::string &value)
    {
        // std::cout << "Start to store, key is " << key << ", data is " << value << std::endl;
        leveldb::Status status = db->Put(leveldb::WriteOptions(), key, value);
        // std::cout << status.ToString() << std::endl;
        Assert(status.ok(), "Error writing data to database.");
    }

    void LoadData(leveldb::DB *db, const std::string &key, std::string *value)
    {
        leveldb::Status status = db->Get(leveldb::ReadOptions(), key, value);
        if (status.IsNotFound())
            return;

        Assert(status.ok(), "Error reading " + key + " from database.");
    }

    std::string Serialize(BLOCK *b)
    {
        if (b == nullptr)
        {
            std::cout << "NULL BLOCK" << std::endl;
            return "";
        }
        // std::cout << "serializing, ph is " << b->get_prev_hash() << std::endl;
        std::string data;
        data += T_KEY + std::to_string(b->get_timestamp());
        data += PH_KEY + b->get_prev_hash();
        data += H_KEY + b->get_hash();
        data += D_KEY + b->get_data();
        data += N_KEY + std::to_string(b->get_nonce());

        return data;
    }

    // &T&123&PH&
    BLOCK *Deserialize(std::string &data)
    {
        int t_index = data.find(T_KEY);
        int ph_index = data.find(PH_KEY);
        int h_index = data.find(H_KEY);
        int d_index = data.find(D_KEY);
        int n_index = data.find(N_KEY);

        if (t_index == std::string::npos || ph_index == std::string::npos || h_index == std::string::npos || d_index == std::string::npos || n_index == std::string::npos)
        {
            std::cout << "Error deserialize data to block" << std::endl;
            return nullptr;
        }

        long long t = 0;
        std::istringstream is_t(data.substr(t_index + T_KEY_LEN, ph_index - t_index - T_KEY_LEN));
        is_t >> t;
        
        std::string ph = data.substr(ph_index + PH_KEY_LEN, h_index - ph_index - PH_KEY_LEN);
        
        std::string h = data.substr(h_index + H_KEY_LEN, d_index - h_index - H_KEY_LEN);
        
        std::string d = data.substr(d_index + D_KEY_LEN, n_index - d_index - D_KEY_LEN);
        
        int n = 0;
        std::istringstream is_n(data.substr(n_index + N_KEY_LEN, data.length() - n_index - N_KEY_LEN));
        is_n >> n;

        return new BLOCK(t, ph, h, d, n);
    }

    void Assert(bool flag, std::string msg)
    {
        if (!flag)
        {
            std::cout << msg << std::endl;
            exit(-1);
        }
    }
}