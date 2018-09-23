//
// Created by 张杰 on 2018/9/21.
//

#ifndef TEST_STRUCT_POOL_H
#define TEST_STRUCT_POOL_H

#endif //TEST_STRUCT_POOL_H

#include <memory>
#include <algorithm>
#include <map>
#include "constant.h"

using namespace std;

struct Block{
    short is_use;
    int32_t index;
    char *block;
};

typedef map<int, Block> BlockMap;

class MemPool{

public:
    MemPool(size_t block_size);
    MemPool(size_t block_size, int pre_alloc, int max_alloc);
    ~MemPool();

    void *get();
    void release(void *ptr);
    size_t block_size();
    int allocated();
    int available();
    int blocknum();

private:
    MemPool();

private:
    int pre_alloc;
    int max_alloc;
    int cur_use = 0;
    int total_alloc = 0;
    size_t m_block_size;
    BlockMap  m_blocks_map;

};