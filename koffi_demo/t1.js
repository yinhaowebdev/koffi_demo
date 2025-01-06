const koffi = require('koffi');

// 加载动态库
const lib = koffi.load('./../cpp/libt1.dylib');

// 定义 UrpcResponse 结构体
const UrpcResponse = koffi.struct('UrpcResponse', {
    code: 'int32',
    data: 'void *',
    dataLen: 'int32'
});

// 定义回调函数类型
const UrpcRequestAsyncCB = koffi.proto('void UrpcRequestAsyncCB(const UrpcResponse *response, void *data)');
// 声明函数
const urpcClientSubscribe = lib.func('urpcClientSubscribe', 'int', [koffi.pointer('UrpcRequestAsyncCB'), koffi.pointer('void')]);

const urpcClientPoll = lib.func('urpcClientPoll', 'int', []);
// 创建一个示例使用函数
function subscribe(callback) {
    // 使用 koffi.register
    const wrappedCallback = koffi.register(
        (response, userData) => {
            // 解码
            const responseStruct = koffi.decode(response, UrpcResponse);
            messageData = koffi.decode(responseStruct.data, 'char', responseStruct.dataLen);

            callback({
                code: responseStruct.code,
                data: messageData,
                dataLen: responseStruct.dataLen
            });
        },
        koffi.pointer(UrpcRequestAsyncCB)
    );

    const result = urpcClientSubscribe(wrappedCallback, null);
    console.log('Subscribe result:', result);
    return result === 0;
}

// 运行函数
function run() {
    console.log('Starting t1 client...');
    
    // 订阅回调
    subscribe((response) => {
        console.log('Received response:', {
            timestamp: new Date().toISOString(),
            code: response.code,
            dataLen: response.dataLen,
            data: response.data
        });
    });

    // 定期轮询
    function doPoll() {
        const result = urpcClientPoll();
        if (result > 0) {
            console.log('Poll processed at:', new Date().toISOString(), result);
        }
    }

    // 每秒执行一次轮询
    setInterval(doPoll, 1000);
}

// 如果直接运行此文件，则执行 run 函数
if (require.main === module) {
    run();
}

// 导出函数
module.exports = {
    subscribe,
    poll: urpcClientPoll,
    run
};
