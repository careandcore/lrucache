
#include "lru.h"
#include "HashTable.h"
#include <stdio.h>
#include <stdlib.h>
#include "leak_detector.h"
//#include "leak_detector_c.h"
#define STRING_SIZE 100
void pushFront(Lrucache* this,Node* p);

Lrucache* LRUCache(const int capacity,int(*hashcode)(void*)){
    Lrucache* pObj = NULL;
    pObj = (Lrucache*)MALLOC(sizeof(Lrucache));
    if (pObj == NULL){
        return NULL;
    }
    pObj -> size = capacity;
	pObj -> count = 0;
    pObj -> get = getValue;
    pObj -> put = putValue;
    pObj -> ht = hash_table_new(hashcode);
    pObj -> lrudelete = deleteLRUCache;
	pObj -> cacheHead = NULL;
	pObj -> cacheTail = NULL;
    return pObj;
}
int getValue(Lrucache* this, void* key){
    if(this->cacheHead == NULL){
        return -1;
    }
    //1������cachelist�е�ֵ�����ؽڵ�λ��
    Node* it = (Node*)hash_table_get(this -> ht, key);
    if (it == NULL){
    //1�� ����ڵ��в��������ֵ���򷵻�-1
        return -1;
    }
    else{
        //2�� ����ҵ��ڵ��е�ֵ���õ��ýڵ��ָ��
        Node* p = it;
        //2�����ýڵ������ͷ��
        pushFront(this,p);
    }
    //3������cachelist->value
    return this -> cacheHead->value;
}
void putValue(Lrucache* this, void* key, void* value){//const int
    if (this -> cacheHead == NULL){//�������Ϊ�գ���ֱ�ӷ���������ͷ��
        this -> cacheHead = (Node*)MALLOC(sizeof(Node));
        this -> cacheHead -> key = key;
        this -> cacheHead -> value = value;
        this -> cacheHead -> pre = NULL;
        this -> cacheHead -> next = NULL;
        this -> cacheTail  = this -> cacheHead;
        hash_table_put2(this -> ht, key, this -> cacheHead,NULL);
        this -> count ++;
    }
    else{//����У����������в���
        Node* it = (Node*)hash_table_get(this -> ht, key);
        if(it == NULL){
            // δ����
            if (this -> count == this -> size){
                //cache ����
                if(this -> cacheHead == this -> cacheTail && this -> cacheHead != NULL){
                    //���cache=1ʱ
                    this -> cacheHead -> key =key;
                    this -> cacheHead -> value = value;
                    hash_table_put2(this -> ht, key, this -> cacheHead,NULL);
                }
                else{
                    //���cache>1
                    Node* p = this -> cacheTail;
                    this -> cacheTail -> pre -> next = this -> cacheTail -> next;
                    this -> cacheTail = this -> cacheTail -> pre;

                    p -> key = key;
                    p -> value = value;
                    p -> next = this -> cacheHead;
                    p -> pre = this -> cacheHead -> pre;

                    this -> cacheHead -> pre = p;
                    this -> cacheHead = p;
                    hash_table_put2(this -> ht, key, this -> cacheHead, NULL);
                }
            }
            else{//δ��
                Node* p = (Node*)MALLOC(sizeof(Node));
                p -> key = key;
                p -> value = value;
                p -> next = this -> cacheHead;
                p -> pre = NULL;
                this -> cacheHead ->pre = p;
                this -> cacheHead = p;
                hash_table_put2(this -> ht, key, this -> cacheHead, NULL);
                this -> count++;
            }
        }
        else{//1������
			//2������ ����value�ķ���
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
        hash_table_delete(this -> ht);
		if (this->cacheHead != NULL) {
			Node* p = this->cacheHead;
			Node* q = p;
			while (q) { //�ͷŽڵ�����
				p = q;
				q = p->next;
				FREE(p);
			}
		}
		FREE(this);//�ͷŶ���
        printf("Has released\n");
    }
}
