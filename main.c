#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"
#include "lru.h"
#include "leak_detector.h"
void mPrint(Lrucache* this) {
	if (this == NULL) {
		return;
	}
	printf("\nlrucache's capacity = %d\n",this ->size);
	printf("\nlrucache's num =%d\n", this->count);
	printf("\nThe newest node is :\nkey:%5d   value:%5d\n", this-> cacheHead ->key, this->cacheHead -> value);
	printf("\nThe oldest node is :\nkey:%5d   value:%5d\n", this->cacheTail->key, this->cacheTail->value);
	Node* p = this->cacheHead;
	int i = 1;
	while (p) {
		printf("the %d node is : key:%5d value:%5d\n", i++, p->key, p->value);
		p = p->next;
	}
}
int main() {
	Lrucache* lrucache = LRUCache(5);
	if (lrucache == NULL) {
		printf("init_fuc fail!\n");
		return -1;
	}
	if (lrucache->size != 5) {
		printf("init_capacity fail!\n");
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
		printf("init_func fail!\n");
		return -1;
	}
	lrucache->put(lrucache, 1, 10);
	lrucache->put(lrucache, 2, 20);
	lrucache->put(lrucache, 3, 30);
	mPrint(lrucache);
	int value = lrucache->get(lrucache, 1);
	if (lrucache->cacheHead->key != 1 &&
		lrucache->cacheHead->value != 10 &&
		lrucache->cacheTail->key != 2 &&
		lrucache->cacheTail->value != 20) {
		printf("lru func logic error!\n");
	}
	lrucache->put(lrucache, 4, 40);
	lrucache->put(lrucache, 5, 50);
	if (lrucache->cacheHead->key != 5 &&
		lrucache->cacheHead->value != 50 &&
		lrucache->cacheTail->key != 2 &&
		lrucache->cacheTail->value != 20) {
		printf("lru func logic error!\n");
	}
	lrucache->put(lrucache, 6, 60);
	if (lrucache->cacheHead->key != 6 &&
		lrucache->cacheHead->value != 60 &&
		lrucache->cacheTail->key != 3 &&
		lrucache->cacheTail->value != 30) {
		printf("lru func logic error!\n");
	}
	mPrint(lrucache);
	printf("\n---------BEFORE CALL delete func:---------\n");
	PRINT_LEAK_INFO();
	lrucache->lrudelete(lrucache);
	printf("\n---------AFTER CALL delete func:---------\n");
	PRINT_LEAK_INFO();
	//system("pause");
	return 0;
}
