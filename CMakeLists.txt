cmake_minimum_required(VERSION 3.20)
project(JRChain)

set(CMAKE_CXX_STANDARD 14)

include_directories(
        ${PROJECT_SOURCE_DIR}/include/
        /opt/homebrew/opt/openssl@1.1/include/
        /opt/homebrew/Cellar/leveldb/1.23/include/
)

add_executable(JRChain main.cpp include/utils.h src/utils.cpp src/block.cpp include/block.h include/blockchain.h src/blockchain.cpp include/pow.h src/pow.cpp)

# target_link_libraries 必须要在 add_executable 之后，因为要先编译再链接
target_link_libraries(
        JRChain
        /opt/homebrew/opt/openssl@1.1//lib/libcrypto.a
        /opt/homebrew/Cellar/leveldb/1.23/lib/libleveldb.a
        /opt/homebrew/Cellar/snappy/1.1.9/lib/libsnappy.a
)