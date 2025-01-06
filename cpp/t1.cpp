#include "t1.h"
#include <vector>
#include <mutex>
#include <string>
#include <cstring>

// 存储回调函数和用户数据的结构
struct CallbackInfo {
    UrpcRequestAsyncCB callback;
    void* userData;
};

// 全局变量
static std::vector<CallbackInfo> g_callbacks;
static std::mutex g_mutex;
static int g_counter = 0;  // 添加计数器

extern "C" {
    UPADRPC_PUBLIC(int) urpcClientSubscribe(UrpcRequestAsyncCB cb, void* udata) {
        if (!cb) {
            return -1;
        }

        std::lock_guard<std::mutex> lock(g_mutex);
        CallbackInfo info = {cb, udata};
        g_callbacks.push_back(info);
        return 0;
    }

    UPADRPC_PUBLIC(int) urpcClientPoll() {
        std::lock_guard<std::mutex> lock(g_mutex);
        
        // 创建动态消息
        g_counter++;
        std::string message = "Message #" + std::to_string(g_counter);
        
        // 分配内存并复制消息
        char* data = new char[message.length() + 1];
        strcpy(data, message.c_str());
        
        // 创建响应
        UrpcResponse response;
        response.code = 200;
        response.data = data;
        response.dataLen = static_cast<int>(message.length());
        
        // 通知所有订阅者
        for (const auto& info : g_callbacks) {
            if (info.callback) {
                info.callback(&response, info.userData);
            }
        }
        
        // 清理内存
        delete[] data;
        
        return 1;
    }
}
