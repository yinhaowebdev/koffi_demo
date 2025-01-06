# 最简demo

### 编译 cpp 文件
```
clang++ -shared -o ./cpp/test.dylib ./cpp/test.cpp
```


### 运行 js 文件
```
cd koffi_demo
yarn
node index.js
```

# 回调demo

### 编译cpp
指定c++11版本 关闭混淆
```
cd cpp    
clang++ -std=c++11 -shared -fPIC -fvisibility=hidden -o libt1.dylib t1.cpp
./test_t1 
```

### 测试cpp文件

```
g++ test_t1.cpp -o test_t1 -L. -lt1 -Wl,-rpath,.
./test_t1
```

### 运行 js 文件
```
cd koffi_demo
yarn
node t1.js
```

note: 当前示例在mac系统中运行，其他系统可能需要修改动态库的编译命令，以及js文件中动态库的加载路径。