
gcc -c -I./incl/ ./src/leak_detector.c -o leak_detector.o
gcc -c -I./incl/ ./src/HashTable.c -o HashTable.o
gcc -c -I./incl/ ./src/lru.c -o lru.o
gcc -c -I./incl/ main.c -o main.o

gcc -o main.exe leak_detector.o HashTable.o lru.o main.o

rm *.o
