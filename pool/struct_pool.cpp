//
// Created by 张杰 on 2018/9/21.
//

#include <iostream>
#include "struct_pool.h"
using namespace std;

MemPool::MemPool() {

    this->pre_alloc=DEFAULT_PRE_CAPACITY;
    this->max_alloc=DEFAULT_MAX_CAPACITY;
    this->m_block_size = DEFAULT_PRE_BLOCKSIZE;
    m_blocks_map.clear();
    for (int i=0; i<pre_alloc; i++){
        Block nBlock;
        nBlock.is_use = 0;
        nBlock.block = new char[this->m_block_size];
        m_blocks_map[i] = nBlock;
    }
    cur_use = 0;
    total_alloc = pre_alloc;
}

MemPool::MemPool(size_t block_size, int pre_alloc, int max_alloc) {
    this->pre_alloc=pre_alloc;
    this->max_alloc=max_alloc;
    this->m_block_size = block_size;
    m_blocks_map.clear();
    for (int i=0; i<pre_alloc; i++){
        Block nBlock;
        nBlock.is_use = 0;
        nBlock.block = new char[this->m_block_size];
        m_blocks_map[i] = nBlock;
    }
    cur_use = 0;
    total_alloc = pre_alloc;
}

MemPool::~MemPool() {

    BlockMap::iterator it = m_blocks_map.begin();
    for(; it!=m_blocks_map.end(); it++){
        cout<< "free info " << it->second.block << endl;
        delete[] it->second.block; //释放空间
    }
    m_blocks_map.clear();
}

void* MemPool::get() {
    for (auto it = m_blocks_map.begin(); it!=m_blocks_map.end(); it++){
        if(it->second.is_use == 0){
            it->second.is_use == 1;
            cur_use++;
            cout<<"this block index is " << it->second.index << " is going to be userd" << endl;
            return it->second.block;
        }
    }
    auto it = m_blocks_map.end();
    it--;
    int mat_index = it->second.index;
    if(mat_index > DEFAULT_MAX_CAPACITY){

        cout << "reach max cannot allocate anymore" << endl;
        return nullptr;
    }
    int cur_index = mat_index + 1;
    cur_use++;
    total_alloc++;
    Block block;
    block.index = cur_index;
    block.is_use = 1;
    block.block = new char[m_block_size];
    m_blocks_map[cur_index] = block;
    return m_blocks_map[cur_index].block;
}

void MemPool::release(void *ptr) {
    char* tmp = reinterpret_cast<char*>(ptr);
    for(auto it = m_blocks_map.begin(); it != m_blocks_map.end(); it++){

        if (it->second.block == tmp){
            cout << "release this block " << it->second.index << endl;
            it->second.is_use == 0;
            cur_use--;
            return;
        }
    }
}

size_t MemPool::block_size() {
    return m_blocks_map.size();
}

int MemPool::allocated() {
    return total_alloc;
}

int MemPool::available() {
    return DEFAULT_MAX_CAPACITY - cur_use;
}
