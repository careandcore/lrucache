#ifndef _LRU_H_
    #define _LRU_H_

#include "HashTable.h"
typedef struct Node Node;
typedef struct _Lrucache Lrucache;
typedef int (*fptrGet)(Lrucache*, const int);
typedef void (*fptrPut)(Lrucache*, const int,const int);
typedef void (*fptrDelete)(Lrucache*);
struct Node{
    int key;
    int value;
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
Lrucache* LRUCache(const int capacity); //���캯��
int getValue(Lrucache* this, const int key);
void putValue(Lrucache* this, const int key, const int value);
void deleteLRUCache(Lrucache* this);//��������
void pushFront(Lrucache* this,Node* p);
#endif // _LRU_H_
