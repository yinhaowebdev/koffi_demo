#include "t1.h"
#include <stdio.h>
#include <thread>
#include <chrono>

// 回调函数实现
void onResponse(const UrpcResponse* response, void* userData) {
    // 如果有数据，则打印数据内容
    if (response->data && response->dataLen > 0) {
        printf("Callback received: code=%d, dataLen=%d, data='%.*s'\n",
               response->code,
               response->dataLen,
               response->dataLen,
               (const char*)response->data);
    } else {
        printf("Callback received: code=%d, dataLen=%d, data=null\n",
               response->code,
               response->dataLen);
    }
}

int main() {
    printf("Starting test program...\n");

    // 订阅回调
    int result = urpcClientSubscribe(onResponse, nullptr);
    if (result != 0) {
        printf("Failed to subscribe: %d\n", result);
        return 1;
    }
    printf("Successfully subscribed\n");

    // 循环调用 poll
    int count = 0;
    while (count < 10) {  // 测试10次
        int pollResult = urpcClientPoll();
        printf("Poll result: %d\n", pollResult);
        
        // 等待1秒
        std::this_thread::sleep_for(std::chrono::seconds(1));
        count++;
    }

    printf("Test completed\n");
    return 0;
}