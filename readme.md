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
--- 
## 上次沟通todo
1. 当cache满时，尾结点在哪儿释放？内存泄露工具是否有bug？
2. hashcode方法每次都要调用sprintf函数拷贝，工程效率太低
3. 希望支持hashmap的key能存储对象类型和基本类型
### 当前修改情况
1. cache满时无需释放节点，直接替换尾节点，直接覆盖后移到首节点位置即可，内存泄露工具确认无bug。
2. 修改hashmap结构，现支持key，value都为对象和基础类型存储，与此对应的是在首次创建LRU时，显式地传入hashcode方法。
--- 
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
  1 ---------value is object---------------
  2 lrucache's capacity=5
  3 
  4 lrucache's num =3
  5 
  6 The newest node is :
  7 key:4203116   value:    3
  8 
  9 The oldest node is
 10 key:4203112   value:    1
 11 the 1 node is : key:    3   value's id=    3
 12  value's name=liaoning
 13 the 2 node is : key:    3   value's id=    2
 14  value's name=beijing
 15 the 3 node is : key:    3   value's id=    1
 16  value's name=jiangxi
 17 
 18 lrucache's capacity=5
 19 
 20 lrucache's num =5
 21 
 22 The newest node is :
 23 key:4203138   value:    6
 24 
 25 The oldest node is
 26 key:4203116   value:    3
 27 the 1 node is : key:    6   value's id=    6
 28  value's name=shanghai
 29 the 2 node is : key:    6   value's id=    5
 30  value's name=hubei
 31 the 3 node is : key:    6   value's id=    4
 32  value's name=hainan
 33 the 4 node is : key:    6   value's id=    1
 34  value's name=jiangxi
 35 the 5 node is : key:    6   value's id=    3
 36  value's name=liaoning
 37 ---------BEFORE CALL delete func:---------Potential Memory Leak Info:
 38 Address: 0x729010, size:16, Location: main.c:76
 39 Address: 0x729030, size:16, Location: main.c:79
 40 Address: 0x729050, size:16, Location: main.c:82
 41 Address: 0x729070, size:16, Location: main.c:85
 42 Address: 0x729090, size:16, Location: main.c:88
 43 Address: 0x7290b0, size:16, Location: main.c:91
 44 Address: 0x7290d0, size:56, Location: ./src/lru.c:13
 45 Address: 0x729110, size:16, Location: ./src/HashTable.c:59
 46 Address: 0x7f70aea3b010, size:8388608, Location: ./src/HashTable.c:64
 47 Address: 0x729130, size:32, Location: ./src/lru.c:48
 48 Address: 0x729160, size:32, Location: ./src/HashTable.c:124
 49 Address: 0x729190, size:32, Location: ./src/lru.c:86
 50 Address: 0x7291c0, size:32, Location: ./src/HashTable.c:124
 51 Address: 0x7291f0, size:32, Location: ./src/lru.c:86
 52 Address: 0x729220, size:32, Location: ./src/HashTable.c:124
 53 Address: 0x729250, size:32, Location: ./src/lru.c:86
 54 Address: 0x729280, size:32, Location: ./src/HashTable.c:124
 55 Address: 0x7292b0, size:32, Location: ./src/lru.c:86
 56 Address: 0x7292e0, size:32, Location: ./src/HashTable.c:124
 57 Address: 0x729310, size:32, Location: ./src/HashTable.c:124
 58 Has released
 59 ---------AFTER CALL delete func:---------Potential Memory Leak Info:
 60 Address: 0x729010, size:16, Location: main.c:76
 61 Address: 0x729030, size:16, Location: main.c:79
 62 Address: 0x729050, size:16, Location: main.c:82
 63 Address: 0x729070, size:16, Location: main.c:85
 64 Address: 0x729090, size:16, Location: main.c:88
 65 Address: 0x7290b0, size:16, Location: main.c:91
 66 ---------key is object---------------
 67 lrucache's capacity=5
 68 
 69 lrucache's num =3
 70 
 71 The newest node is :
 72 key:    3   value:   30
 73 
 74 The oldest node is
 75 key:    1   value:   10
 76 the 1 node is : key:    3 value:   30
 77 the 2 node is : key:    2 value:   20
 78 the 3 node is : key:    1 value:   10
 79 
 80 lrucache's capacity=5
 81 
 82 lrucache's num =5
 83 
 84 The newest node is :
 85 key:    6   value:   60
 86 
 87 The oldest node is
 88 key:    3   value:   30
 89 the 1 node is : key:    6 value:   60
 90 the 2 node is : key:    5 value:   50
 91 the 3 node is : key:    4 value:   40
 92 the 4 node is : key:    1 value:   10
 93 the 5 node is : key:    3 value:   30
 94 ---------BEFORE CALL delete func:---------Potential Memory Leak Info:
 95 Address: 0x729010, size:16, Location: main.c:76
 96 Address: 0x729030, size:16, Location: main.c:79
 97 Address: 0x729050, size:16, Location: main.c:82
 98 Address: 0x729070, size:16, Location: main.c:85
 99 Address: 0x729090, size:16, Location: main.c:88
100 Address: 0x7290b0, size:16, Location: main.c:91
101 Address: 0x7290d0, size:56, Location: ./src/lru.c:13
102 Address: 0x729110, size:16, Location: ./src/HashTable.c:59
103 Address: 0x729130, size:8388608, Location: ./src/HashTable.c:64
104 Address: 0xf29140, size:32, Location: ./src/lru.c:48
105 Address: 0xf29170, size:32, Location: ./src/HashTable.c:124
106 Address: 0xf291a0, size:32, Location: ./src/lru.c:86
107 Address: 0xf291d0, size:32, Location: ./src/HashTable.c:124
108 Address: 0xf29200, size:32, Location: ./src/lru.c:86
109 Address: 0xf29230, size:32, Location: ./src/HashTable.c:124
110 Address: 0xf29260, size:32, Location: ./src/lru.c:86
111 Address: 0xf29290, size:32, Location: ./src/HashTable.c:124
112 Address: 0xf292c0, size:32, Location: ./src/lru.c:86
113 Address: 0xf292f0, size:32, Location: ./src/HashTable.c:124
114 Address: 0xf29320, size:32, Location: ./src/HashTable.c:124
115 Has released
116 ---------AFTER CALL delete func:---------Potential Memory Leak Info:
117 ---------key is base, value is base---------------
118 lrucache's capacity=5
119 
120 lrucache's num =3
121 
122 The newest node is :
123 key:4203116   value:   30
124 
125 The oldest node is
126 key:4203112   value:   10
127 the 1 node is : key:    3 value:   30
128 the 2 node is : key:    2 value:   20
129 the 3 node is : key:    1 value:   10
130 
131 lrucache's capacity=5
132 
133 lrucache's num =5
134 
135 The newest node is :
136 key:4203138   value:   60
137 
138 The oldest node is
139 key:4203116   value:   30
140 the 1 node is : key:    6 value:   60
141 the 2 node is : key:    5 value:   50
142 the 3 node is : key:    4 value:   40
143 the 4 node is : key:    1 value:   10
144 the 5 node is : key:    3 value:   30
145 ---------BEFORE CALL delete func:---------Potential Memory Leak Info:
146 Address: 0x7290d0, size:56, Location: ./src/lru.c:13
147 Address: 0x729110, size:16, Location: ./src/HashTable.c:59
148 Address: 0x729130, size:8388608, Location: ./src/HashTable.c:64
149 Address: 0x729010, size:32, Location: ./src/lru.c:48
150 Address: 0x729040, size:32, Location: ./src/HashTable.c:124
151 Address: 0x729070, size:32, Location: ./src/lru.c:86
152 Address: 0x7290a0, size:32, Location: ./src/HashTable.c:124
153 Address: 0xf29140, size:32, Location: ./src/lru.c:86
154 Address: 0xf29170, size:32, Location: ./src/HashTable.c:124
155 Address: 0xf291a0, size:32, Location: ./src/lru.c:86
156 Address: 0xf291d0, size:32, Location: ./src/HashTable.c:124
157 Address: 0xf29200, size:32, Location: ./src/lru.c:86
158 Address: 0xf29230, size:32, Location: ./src/HashTable.c:124
159 Address: 0xf29260, size:32, Location: ./src/HashTable.c:124
160 Has released
161 ---------AFTER CALL delete func:---------Potential Memory Leak Info:
```

## 参考链接
- https://blog.csdn.net/zhyfxy/article/details/65635603
- https://blog.csdn.net/smstong/article/details/51145786
- https://www.cnblogs.com/dolphin0520/p/3741519.html
- https://blog.csdn.net/qq_37375427/article/details/88089266
