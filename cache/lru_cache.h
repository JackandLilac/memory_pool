//
// Created by 张杰 on 2018/9/21.
//

#ifndef TEST_LRU_CACHE_H
#define TEST_LRU_CACHE_H

#endif //TEST_LRU_CACHE_H

#include <iostream>
#include <vector>

using namespace std;

class LRUCache{

public:

    struct Node{

        string key;
    };


private:

    vector<Node> nodes;
    vector<Node*> unused;

};


