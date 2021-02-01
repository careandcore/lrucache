#include "leak_detector.h"

#define SIZE 256

typedef struct {
	void* pointer;
	int size;
	const char* file;
	int line;
}MemoryInfo;

static MemoryInfo M_array[SIZE];

void* mallocEX(size_t n, const char* file, int line) {

	void* ret = malloc(n);

	if (ret != NULL) {
		int i = 0;

		for (i = 0; i<SIZE; i++) {
			if (M_array[i].pointer == NULL) {
				M_array[i].pointer = ret;
				M_array[i].size = n;
				M_array[i].file = file;
				M_array[i].line = line;

				break;
			}

		}
	}
	return ret;
}

void freeEX(void* p) {
	if (p != NULL) {
		int i = 0;

		for (i = 0; i<SIZE; i++) {
			if (M_array[i].pointer == p) {
				M_array[i].pointer = NULL;
				M_array[i].size = 0;
				M_array[i].file = NULL;
				M_array[i].line = 0;

				free(p);
				break;
			}
		}
	}
}

void PRINT_LEAK_INFO() {
	int i = 0;
	printf("Potential Memory Leak Info: \n");

	for (i = 0; i<SIZE; i++) {
		if (M_array[i].pointer != NULL) {
			printf("Address: %p, size:%d, Location: %s:%d\n", M_array[i].pointer, M_array[i].size, M_array[i].file, M_array[i].line);
		}
	}
}