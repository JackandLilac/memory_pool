//
// Created by 张杰 on 2018/9/23.
//

#ifndef TEST_INT_POOL_H
#define TEST_INT_POOL_H

#endif //TEST_INT_POOL_H

#include <memory.h>
#include <algorithm>
#include <map>
#include <list>
#include <mutex>
#include <thread>
#include "constant.h"

using namespace std;

struct Block{
    int index;
    int32_t* value;
};

typedef map<int, Block> BlockVector;

class IntPool{

public:
    IntPool(int block_size, int pre_allocate, int total_allocate);
    ~IntPool();
    Block* get();
    size_t get_block_size();
    int get_allocated();
    int get_avilable();
    void release(Block block);
    int get_used();

private:
    size_t block_size;
    int pre_allocate;
    int allocate;
    int total_allocate;
    int used=0;
    BlockVector block_map;
    list<int> unused_key;

private:
    std::mutex mt;
};