# LUR 纯c代码实现
## 代码目录
- 
```
├── incl  
│   ├── HashTable.h
│   ├── leak_detector.h
│   └── lru.h
├── lib
├── libmake.sh
├── main.c
├── make.sh
└── src
    ├── HashTable.c
    ├── leak_detector.c
    └── lru.c
```

- incl：头文件
- lib：动态库生成文件
- src：函数接口实现文件
- main.c:单元测试文件
- libmake.sh：生成动态库并且链接脚本
- make.sh：正常编译链接脚本

## 文件功能说明
- leak_detector.c ：给malloc，calloc，free套了一层壳，记录了每次调用时的地址，文件名，行号等。先创建一个内存缓冲区，当每次调用MALLOC函数，自动在内存中存储申请内存的地址，文件，行号，大小信息；调用FREE时，释放该内存中的信息。
- HashTable.c： 实现了hashmap的功能
- lru.c：实现了lrucache的功能
- main.c:包含测试要点和实现了mprint功能
## 单元测试要点
- 创建成功判断
- 初始化判断
- put函数功能校验
- get函数功能校验
- cache满，lru逻辑处理校验
- cache未满，lru逻辑处理校验
- 内存泄露校验

## how to use
### 执行环境
- gcc (GCC) 4.4.6 20120305 (Red Hat 4.4.6-4)
### 命令
- sh make.sh ; ./main.exe(正常编译)
- sh libmake.sh;./libmake.exe(调用库文件)
## 执行结果
```
lrucache's capacity = 5

lrucache's num =3

The newest node is :
key:    3   value:   30

The oldest node is :
key:    1   value:   10
the 1 node is : key:    3 value:   30
the 2 node is : key:    2 value:   20
the 3 node is : key:    1 value:   10

lrucache's capacity = 5

lrucache's num =5

The newest node is :
key:    6   value:   60

The oldest node is :
key:    3   value:   30
the 1 node is : key:    6 value:   60
the 2 node is : key:    5 value:   50
the 3 node is : key:    4 value:   40
the 4 node is : key:    1 value:   10
the 5 node is : key:    3 value:   30

---------BEFORE CALL delete func:---------
Potential Memory Leak Info: 
Address: 0x720010, size:56, Location: ./src/lru.c:13
Address: 0x720050, size:8, Location: ./src/HashTable.c:58
Address: 0x7fa904568010, size:8388608, Location: ./src/HashTable.c:63
Address: 0x720070, size:24, Location: ./src/lru.c:54
Address: 0x720090, size:2, Location: ./src/HashTable.c:115
Address: 0x7200b0, size:32, Location: ./src/HashTable.c:119
Address: 0x7200e0, size:24, Location: ./src/lru.c:93
Address: 0x720100, size:2, Location: ./src/HashTable.c:115
Address: 0x720120, size:32, Location: ./src/HashTable.c:119
Address: 0x720150, size:24, Location: ./src/lru.c:93
Address: 0x720170, size:2, Location: ./src/HashTable.c:115
Address: 0x720190, size:32, Location: ./src/HashTable.c:119
Address: 0x7201c0, size:24, Location: ./src/lru.c:93
Address: 0x7201e0, size:2, Location: ./src/HashTable.c:115
Address: 0x720200, size:32, Location: ./src/HashTable.c:119
Address: 0x720230, size:24, Location: ./src/lru.c:93
Address: 0x720250, size:2, Location: ./src/HashTable.c:115
Address: 0x720270, size:32, Location: ./src/HashTable.c:119
Address: 0x7202a0, size:2, Location: ./src/HashTable.c:115
Address: 0x7202c0, size:32, Location: ./src/HashTable.c:119
releasing the memory 
has released

---------AFTER CALL delete func:---------
Potential Memory Leak Info: 
```

## 参考链接
- https://blog.csdn.net/zhyfxy/article/details/65635603
- https://blog.csdn.net/smstong/article/details/51145786
- https://www.cnblogs.com/dolphin0520/p/3741519.html
- https://blog.csdn.net/qq_37375427/article/details/88089266
