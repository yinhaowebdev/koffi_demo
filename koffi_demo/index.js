const koffi = require('koffi');

// 加载动态库
const lib = koffi.load('./../cpp/test.dylib');

// 定义动态库中的函数签名
const add = lib.func('double add(double, double)');
const greet = lib.func('const char* greet()');

(async () => {
    // 调用动态库方法
    const sum = add(5.2, 3.8); // 调用 add 函数
    console.log('Sum:', sum);

    const greeting = greet(); // 调用 greet 函数
    console.log('Greeting:', greeting);
})();
