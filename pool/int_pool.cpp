//
// Created by 张杰 on 2018/9/23.
//
#include <iostream>
#include "int_pool.h"

IntPool::IntPool(int block_size, int pre_allocate, int total_allocate) {

    if(pre_allocate > total_allocate) {
        throw 1;
    }
    this->block_size = block_size;
    this->pre_allocate = pre_allocate;
    this->total_allocate = total_allocate;
    for(int i=0 ; i < this->pre_allocate; i++) {

        Block block;
        block.index = i;
        block.value = new int[block_size];
        unused_key.push_back(i);
        block_map[i] = block;
    }
    allocate = pre_allocate;
}

IntPool::~IntPool() {

    for(int i=0; i<allocate; i++){

        Block b = block_map[i];
        delete[] b.value;
    }
}

Block* IntPool::get() {

    std::lock_guard<std::mutex> lck(mt);
    //如果unused不为空，直接分配一个
    if (unused_key.size() > 0) {
        int key = unused_key.front();
        unused_key.pop_front();
        Block block = block_map[key];
        used++;
        return &block;
    }

    //达到分配定额，则返回nullptr
    if (allocate >= total_allocate){
//        cout << "run out of memory" << endl;
        return nullptr;
    }
    //继续分配内存
    int left = total_allocate - allocate;
    int cur_allocate = left < ALLOCATE_SIZE_PERTIME?left:ALLOCATE_SIZE_PERTIME;
    cout << "reallocate num: " << cur_allocate << " threadid is : " << std::this_thread::get_id()<<endl;
    int i=allocate;
    for( ; i<allocate+cur_allocate-1; i++) {
        Block block;
        block.index = i;
        block.value = new int[block_size];
        unused_key.push_back(i);
        block_map[i] = block;
    }
    allocate = allocate + cur_allocate;
    cout << "current allocate is : " << allocate << endl;
    //留下一个空位返回
    Block block;
    block.index = i;
    block.value = new int[block_size];
    block_map[i] = block;
    used++;
    return &block;
}

void IntPool::release(Block block) {

    std::lock_guard<std::mutex> lck(mt);
    int id = block.index;
    memset(block.value, 0, block_size);
    used--;
    unused_key.push_back(id);
}

size_t IntPool::get_block_size() { return block_size; }

int IntPool::get_allocated() { return allocate; }

int IntPool::get_avilable() { return total_allocate - allocate; }

int IntPool::get_used() { return used; }