#ifndef _LRU_H_
    #define _LRU_H_

#include "HashTable.h"
typedef struct Node Node;
typedef struct _Lrucache Lrucache;
typedef int (*fptrGet)(Lrucache*, void*);
typedef void (*fptrPut)(Lrucache*, void*,void*);
typedef void (*fptrDelete)(Lrucache*);
struct Node{
    void* key;
    void* value;
    Node* pre;
    Node* next;
};

struct  _Lrucache{
    int count;
    int size;
    HashTable* ht;
    Node* cacheHead;
    Node* cacheTail;
    fptrGet get;
    fptrPut put;
    fptrDelete lrudelete;
};
Lrucache* LRUCache(const int capacity,int(*hashcode)(void*)); //构造函数
int getValue(Lrucache* this, void* key);
void putValue(Lrucache* this, void* key, void* value);
void deleteLRUCache(Lrucache* this);//析构函数
void pushFront(Lrucache* this,Node* p);
#endif // _LRU_H_
