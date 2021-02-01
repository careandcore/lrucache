
#include "lru.h"
#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include "leak_detector.h"
//#include "leak_detector_c.h"
#define STRING_SIZE 100
void pushFront(Lrucache* this,Node* p);

Lrucache* LRUCache(const int capacity){
    Lrucache* pObj = NULL;
    pObj = (Lrucache*)MALLOC(sizeof(Lrucache));
    if (pObj == NULL){
        return NULL;
    }
    pObj -> size = capacity;
	pObj -> count = 0;
    pObj -> get = getValue;
    pObj -> put = putValue;
    pObj -> ht = hash_table_new();
    pObj -> lrudelete = deleteLRUCache;
	pObj -> cacheHead = NULL;
	pObj -> cacheTail = NULL;
    return pObj;
}
int getValue(Lrucache* this, const int key){
    if(this->cacheHead == NULL){
        return -1;
    }
    char skey[STRING_SIZE]="";
    //itoa(key,skey,10);
    sprintf(skey,"%d",key);
    //1、查找cachelist中的值，返回节点位置
    Node* it = (Node*)hash_table_get(this -> ht, skey);
    if (it == NULL){
    //1、 如果节点中不存在这个值，则返回-1
        return -1;
    }
    else{
        //2、 如果找到节点中的值，拿到该节点的指针
        Node* p = it;
        //2、将该节点放置在头部
        pushFront(this,p);
    }
    //3、返回cachelist->value
    return this -> cacheHead->value;
}
void putValue(Lrucache* this, const int key, const int value){
	char skey[STRING_SIZE] = "";
    //itoa(key,skey,10);
    sprintf(skey,"%d",key);
    if (this -> cacheHead == NULL){//如果链表为空，则直接放在链表的头部
        this -> cacheHead = (Node*)MALLOC(sizeof(Node));
        this -> cacheHead -> key = key;
        this -> cacheHead -> value = value;
        this -> cacheHead -> pre = NULL;
        this -> cacheHead -> next = NULL;
        this -> cacheTail  = this -> cacheHead;
        hash_table_put2(this -> ht, skey, this -> cacheHead,NULL);
        this -> count ++;
    }
    else{//如果有，则在链表中查找
        Node* it = (Node*)hash_table_get(this -> ht, skey);

        if(it == NULL){
            // 未命中
            if (this -> count == this -> size){
                //cache 满了
                if(this -> cacheHead == this -> cacheTail && this -> cacheHead != NULL){
                    //如果cache=1时
                    this -> cacheHead -> key =key;
                    this -> cacheHead -> value = value;
                    hash_table_put2(this -> ht, skey, this -> cacheHead,NULL);
                }
                else{
                    //如果cache>1
                    Node* p = this -> cacheTail;
                    this -> cacheTail -> pre -> next = this -> cacheTail -> next;
                    this -> cacheTail = this -> cacheTail -> pre;

                    p -> key = key;
                    p -> value = value;
                    p -> next = this -> cacheHead;
                    p -> pre = this -> cacheHead -> pre;

                    this -> cacheHead -> pre = p;
                    this -> cacheHead = p;
                    hash_table_put2(this -> ht, skey, this -> cacheHead, NULL);
                }
            }
            else{//未满
                Node* p = (Node*)MALLOC(sizeof(Node));
                p -> key = key;
                p -> value = value;
                p -> next = this -> cacheHead;
                p -> pre = NULL;
                this -> cacheHead ->pre = p;
                this -> cacheHead = p;
                hash_table_put2(this -> ht, skey, this -> cacheHead, NULL);
                this -> count++;
            }
        }
        else{//1、命中
			//2、加上 设置value的方法
            Node* p = it;
            pushFront(this,p);
        }

    }
}

void pushFront(Lrucache* this,Node* p){
    if(this -> count == 1){
        return;
    }
    if(p == this -> cacheHead){
        return;
    }
    if(p == this -> cacheTail){
        this -> cacheTail = p -> pre;
    }
    p -> pre -> next = p -> next;
    if(p -> next != NULL){
        p -> next -> pre = p -> pre;
    }
    p -> next = this -> cacheHead;
    p -> pre = NULL;
    this -> cacheHead -> pre = p;
    this -> cacheHead = p;
}
void deleteLRUCache(Lrucache* this){
    if(this == NULL){
        printf("The pointer is NULL\n");
        return ;
    }
    else{
        printf("releasing the memory \n");
        hash_table_delete(this -> ht);
		if (this->cacheHead != NULL) {
			Node* p = this->cacheHead;
			Node* q = p;
			while (q) { //释放节点链表
				p = q;
				q = p->next;
				FREE(p);
			}
		}
		FREE(this);//释放对象
        printf("has released\n");
    }
}
