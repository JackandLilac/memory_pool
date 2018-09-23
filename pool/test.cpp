//
// Created by 张杰 on 2018/9/22.
//
#include <iostream>
#include <memory>
#include <string.h>
#include "stdlib.h"
#include "int_pool.h"

using namespace std;

#define DATA_BLOCK_LEN 50

struct sTest{
    int m_id;
    int m_num;
};

struct  sTest2
{
    int m_id;
    int m_num;
    char m_str[10];
};

//void test_struct_pool(){
//    MemPool myPool1(DATA_BLOCK_LEN, DEFAULT_PRE_CAPACITY, DEFAULT_MAX_CAPACITY);
//
//    cout << "myPool1 block size = " << myPool1.block_size() << endl;
//    cout << "myPool1 allocated block num = " << myPool1.allocated() << endl;
//    cout << "myPool1 available block num = " << myPool1.available() << endl;
//
//    // 分配一个内存块
//    struct sTest* pTest;
//    pTest = (struct sTest*)(myPool1.get());
//
//    pTest->m_id = 25;
//    pTest->m_num = 10000;
//    cout << pTest->m_id <<"  " <<pTest->m_num << endl;
//
//    struct sTest* pTest2;
//    pTest2 = (struct sTest*)(myPool1.get());
//
//    pTest2->m_id = 123;
//    pTest2->m_num = 13445;
//    cout << pTest2->m_id << "  " << pTest2->m_num << endl << endl;
//
//
//    cout << "myPool1 allocated block num = " << myPool1.allocated() << endl;
//    cout << "myPool1 available block num = " << myPool1.available() << endl << endl;
//
//    // 回收该内存块
//    myPool1.release(pTest);
//    pTest = NULL;
//
//    cout << "myPool1 allocated block num = " << myPool1.allocated() << endl;
//    cout << "myPool1 available block num = " << myPool1.available() << endl << endl;
//
//    pTest = (struct sTest*)(myPool1.get());
//    cout << pTest->m_id << endl;
//    cout << pTest->m_num << endl;
//
//    struct sTest2* pTtmp;
//    pTtmp = (struct sTest2*)(myPool1.get());
//    pTtmp->m_id = 1234;
//    char * cTmp= "skskdlsl";
//    memcpy(pTtmp->m_str, cTmp, strlen(cTmp));
//    cout << pTtmp->m_str << endl;
//
//    cout << "myPool1 allocated block num = " << myPool1.allocated() << endl;
//    cout << "myPool1 available block num = " << myPool1.available() << endl;
//
//    myPool1.release(pTtmp);
//
//    for (int i = 0; i < 30; ++i)
//    {
//        struct sTest* pTest3;
//        pTest3 = (struct sTest*)(myPool1.get());
//
//        pTest3->m_id = 123;
//        pTest3->m_num = 13445;
//        cout << pTest3->m_id << "  " << pTest3->m_num << endl << endl;
//        cout << "myPool1 allocated block num = " << myPool1.allocated() << endl;
//        cout << "myPool1 available block num = " << myPool1.available() << endl;
//        cout << "myPool1 total block num = " << myPool1.block_size() << endl << endl;
//    }
//
//    int iWait;
//    cin >> iWait;
//}

void print(int *head){
    int *p = head;
    while (p != nullptr && *p != 0) {
        cout<<*p <<" ";
        p++;
    }
    cout<<endl;
}

void printInfo(IntPool* intPool) {
    cout << "myPool1 block size = " << intPool->get_block_size() << endl;
    cout << "myPool1 allocated block num = " << intPool->get_allocated() << endl;
    cout << "myPool1 available block num = " << intPool->get_avilable() << endl;
    cout << "myPool1 used block num = " << intPool->get_used() << endl;
}

void copy(){

}

void test_int_pool(){

    IntPool intPool(DATA_BLOCK_LEN, DEFAULT_PRE_CAPACITY, DEFAULT_MAX_CAPACITY);
    printInfo(&intPool);
    Block *pi = intPool.get();
    if(pi == nullptr) {
        return;
    }
    Block block = *pi;
    int a[] = {1,2,3,4,5,63,3,4,2,3,4,3,2,3,2};
    cout << "sizeof : " << sizeof(a)/ sizeof(int) << endl;
    cout << "sizeof block : " << sizeof(*(block.value)) << endl;
    int* p = block.value;
    memcpy(p, a, sizeof(a));
    cout << "here" << endl;
    print(block.value);
    printInfo(&intPool);
    print(block.value);
    intPool.release(block);
    print(block.value);
    for(int i=0; i<10000000;i++) {
        Block *pi = intPool.get();
        if(pi == nullptr){
            continue;
        }
        if(i %10 == 0){
            intPool.release(*pi);
        }
    }
}

int main()
{
    test_int_pool();
}

