
gcc -c -I./incl/ -fPIC ./src/leak_detector.c -o leak_detector.o
gcc -c -I./incl/ -fPIC ./src/HashTable.c -o HashTable.o
gcc -c -I./incl/ -fPIC ./src/lru.c -o lru.o
gcc -c -I./incl/ main.c -o main.o

gcc -shared -fPIC -o ./lib/liblru.so leak_detector.o HashTable.o lru.o 
gcc -o libmain.exe main.o ./lib/liblru.so
rm *.o
