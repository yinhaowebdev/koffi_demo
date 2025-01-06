#ifndef T1_H
#define T1_H

/* 定义导出宏 */
#ifdef _WIN32
    #ifdef T1_EXPORTS
        #define UPADRPC_PUBLIC(type) __declspec(dllexport) type
    #else
        #define UPADRPC_PUBLIC(type) __declspec(dllimport) type
    #endif
#else
    #define UPADRPC_PUBLIC(type) __attribute__((visibility("default"))) type
#endif

/* 定义响应结构体 */
struct UrpcResponse {
    int code;          /* 响应状态码 */
    void* data;        /* 响应数据 */
    int dataLen;       /* 数据长度 */
};

/* 定义回调函数类型 */
typedef void (*UrpcRequestAsyncCB)(const struct UrpcResponse* res, void* data);

#ifdef __cplusplus
extern "C" {
#endif

/* Subscribe函数声明 */
UPADRPC_PUBLIC(int) urpcClientSubscribe(UrpcRequestAsyncCB cb, void* udata);

/* Poll函数声明 */
UPADRPC_PUBLIC(int) urpcClientPoll();

#ifdef __cplusplus
}
#endif

#endif /* T1_H */