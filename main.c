#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "lru.h"
#include "leak_detector.h"
typedef struct Person
{
	int id;
	char* name;
}Person;
unsigned int hashcode2(char* key)
{
	unsigned int hash = 0;
	while (*key) {
		hash = (hash << 5) + hash + *key++;
	}
	return hash;
}
unsigned int hashcode(Person* key)
{
	unsigned int hash = 0;
	hash = (hash << 5) + hash + key->id;
	return hash;
}

void mPrint(Lrucache* this) {
	if (this == NULL) {
		return;
	}
	printf("\nlrucache's capacity=%d\n",this ->size);
	printf("\nlrucache's num =%d\n", this->count);
	printf("\nThe newest node is :\nkey:%5d   value:%5d\n", ((Person*)this-> cacheHead ->key) -> id, this->cacheHead -> value);
	printf("\nThe oldest node is \nkey:%5d   value:%5d\n", ((Person*)this->cacheTail->key)->id, this->cacheTail->value);
	Node* p = this->cacheHead;
	int i = 1;
	while (p) {
		printf("the %d node is : key:%5d value:%5d\n", i++, ((Person*)p->key)->id, p->value);
		p = p->next;
	}
}
void mPrint2(Lrucache* this) {
	if (this == NULL) {
		return;
	}
	printf("\nlrucache's capacity=%d\n",this ->size);
	printf("\nlrucache's num =%d\n", this->count);
	printf("\nThe newest node is :\nkey:%5d   value:%5d\n", this->cacheHead->key, this->cacheHead->value);
	printf("\nThe oldest node is \nkey:%5d   value:%5d\n", this->cacheTail->key, this->cacheTail->value);
	Node* p = this->cacheHead;
	int i = 1;
	while (p) {
		printf("the %d node is : key:%5s value:%5d\n", i++, p->key, p->value);
		p = p->next;
	}
}

void mPrint3(Lrucache* this) {
	if (this == NULL) {
		return;
	}
	printf("\nlrucache's capacity=%d\n",this ->size);
	printf("\nlrucache's num =%d\n", this->count);
	printf("\nThe newest node is :\nkey:%5d   value:%5d\n", this->cacheHead->key, ((Person*)this->cacheHead->value)->id, ((Person*)this->cacheHead->value)->name);
	printf("\nThe oldest node is \nkey:%5d   value:%5d\n", this->cacheTail->key, ((Person*)this->cacheTail->value)->id, ((Person*)this->cacheTail->value)->name);
	Node* p = this->cacheHead;
	int i = 1;
	while (p) {
		printf("the %d node is : key:%5s   value's id=%5d\n value's name=%s \n",i++, this->cacheHead->key, ((Person*)p->value)->id, ((Person*)p->value)->name);
		p = p->next;
	}
}

int main() {

	char* ww = "weiye";
	Person* p1 = (Person*)MALLOC(sizeof(Person));
	p1->id = 1;
	p1->name = "jiangxi";
	Person* p2 = (Person*)MALLOC(sizeof(Person));
	p2->id = 2;
	p2->name = "beijing";
	Person* p3 = (Person*)MALLOC(sizeof(Person));
	p3->id = 3;
	p3->name = "liaoning";
	Person* p4 = (Person*)MALLOC(sizeof(Person));
	p4->id = 4;
	p4->name = "hainan";
	Person* p5 = (Person*)MALLOC(sizeof(Person));
	p5->id = 5;
	p5->name = "hubei";
	Person* p6 = (Person*)MALLOC(sizeof(Person));
	p6->id = 6;
	p6->name = "shanghai";
	printf("---------value is object---------------");
	Lrucache* lrucache3 = LRUCache(5, hashcode2);
	lrucache3->put(lrucache3, "1", p1);
	lrucache3->put(lrucache3, "2", p2);
	lrucache3->put(lrucache3, "3", p3);
	mPrint3(lrucache3);
	int value2 = lrucache3->get(lrucache3, "1");
	if (lrucache3->cacheHead->key != "1" &&
		lrucache3->cacheHead->value != p1 &&
		lrucache3->cacheHead->key != "2" &&
		lrucache3->cacheTail->value != p2) {
		printf("lru logic error\n");
	}
	lrucache3->put(lrucache3, "4", p4);
	lrucache3->put(lrucache3, "5", p5);
	if (lrucache3->cacheHead->key != "5" &&
		lrucache3->cacheHead->value != p5 &&
		lrucache3->cacheHead->key != "2" &&
		lrucache3->cacheTail->value != p2) {
		printf("lru logic error\n");
	}
	lrucache3->put(lrucache3, "6", p6);
	if (lrucache3->cacheHead->key != "6" &&
		lrucache3->cacheHead->value != p6 &&
		lrucache3->cacheHead->key != "3" &&
		lrucache3->cacheTail->value != p3) {
		printf("lru logic error\n");
	}
	mPrint3(lrucache3);
	printf("---------BEFORE CALL delete func:---------");
	PRINT_LEAK_INFO();
	lrucache3->lrudelete(lrucache3);
	printf("---------AFTER CALL delete func:---------");
	PRINT_LEAK_INFO();

	printf("---------key is object---------------");
	Lrucache* lrucache = LRUCache(5, hashcode);
	if (lrucache == NULL) {
		printf("init fail\n");
		return -1;
	}
	if (lrucache->size != 5) {
		printf("init fail\n");
		return -1;
	}
	if (lrucache->count != 0 ||
		lrucache->ht == NULL ||
		lrucache->get == NULL ||
		lrucache->put == NULL ||
		lrucache->lrudelete == NULL ||
		lrucache->cacheHead != NULL ||
		lrucache->cacheTail != NULL)
	{
		printf("init fail\n");
		return -1;
	}
	lrucache->put(lrucache, p1, 10);
	lrucache->put(lrucache, p2, 20);
	lrucache->put(lrucache, p3, 30);
	mPrint(lrucache);
	int value = lrucache->get(lrucache, p1);
	if (((Person*)lrucache->cacheHead->key)->id != 1 &&
		lrucache->cacheHead->value != 10 &&
		((Person*)lrucache->cacheHead->key)->id != 2 &&
		lrucache->cacheTail->value != 20) {
		printf("lru logic error\n");
	}
	lrucache->put(lrucache, p4, 40);
	lrucache->put(lrucache, p5, 50);
	if (((Person*)lrucache->cacheHead->key)->id != 5 &&
		lrucache->cacheHead->value != 50 &&
		((Person*)lrucache->cacheHead->key)->id != 2 &&
		lrucache->cacheTail->value != 20) {
		printf("lru logic error\n");
	}
	lrucache->put(lrucache, p6, 60);
	if (((Person*)lrucache->cacheHead->key)->id != 6 &&
		lrucache->cacheHead->value != 60 &&
		((Person*)lrucache->cacheHead->key)->id != 3 &&
		lrucache->cacheTail->value != 30) {
		printf("lru logic error\n");
	}
	mPrint(lrucache);
	printf("---------BEFORE CALL delete func:---------");
	PRINT_LEAK_INFO();
	lrucache->lrudelete(lrucache);
	printf("---------AFTER CALL delete func:---------");
	PRINT_LEAK_INFO();

	printf("---------key is base, value is base---------------");
	Lrucache* lrucache2 = LRUCache(5, hashcode2);
	lrucache2->put(lrucache2, "1", 10);
	lrucache2->put(lrucache2, "2", 20);
	lrucache2->put(lrucache2, "3", 30);
	mPrint2(lrucache2);
	int value1 = lrucache2->get(lrucache2, "1");
	if (lrucache2->cacheHead->key != "1" &&
		lrucache2->cacheHead->value != 10 &&
		lrucache2->cacheHead->key != "2" &&
		lrucache2->cacheTail->value != 20) {
		printf("lru logic error\n");
	}
	lrucache2->put(lrucache2, "4", 40);
	lrucache2->put(lrucache2, "5", 50);
	if (lrucache2->cacheHead->key != "5" &&
		lrucache2->cacheHead->value != 50 &&
		lrucache2->cacheHead->key != "2" &&
		lrucache2->cacheTail->value != 20) {
		printf("lru logic error\n");
	}
	lrucache2->put(lrucache2, "6", 60);
	if (lrucache2->cacheHead->key != "6" &&
		lrucache2->cacheHead->value != 60 &&
		lrucache2->cacheHead->key != "3" &&
		lrucache2->cacheTail->value != 30) {
		printf("lru logic error\n");
	}
	mPrint2(lrucache2);
	printf("---------BEFORE CALL delete func:---------");
	PRINT_LEAK_INFO();
	lrucache2->lrudelete(lrucache2);
	printf("---------AFTER CALL delete func:---------");
	PRINT_LEAK_INFO();
	system("pause");
}