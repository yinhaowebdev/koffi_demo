# 编译 cpp 文件
```
cd cpp
clang++ -shared -o ./cpp/test.dylib ./cpp/test.cpp
```

# 运行 js 文件
```
cd koffi_demo
yarn
node index.js
```

note: 当前示例在mac系统中运行，其他系统可能需要修改动态库的编译命令，以及js文件中动态库的加载路径。