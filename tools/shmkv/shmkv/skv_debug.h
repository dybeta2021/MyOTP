//
// Created by 稻草人 on 2021/12/26.
// debug print

// ref: https://www.runoob.com/cprogramming/c-function-fprintf.html
// C 库函数 int fprintf(FILE *stream, const char *format, ...) 发送格式化输出到流 stream 中

// ref: https://blog.csdn.net/a380880304/article/details/50145495
// __LINE__：在源代码中插入当前源代码行号
// __FILE__：在源文件中插入当前源文件名

// ref: https://blog.51cto.com/u_9323514/2463984
// ‘__VA_ARGS__’ 是 C99 引入的用于支持宏定义函数中使用可变参数

#ifndef PYSHMKV_DEBUG_H
#define PYSHMKV_DEBUG_H

/// 使用debug模式
#define SKV_DEBUG

#ifdef SKV_DEBUG
#define DEBUG_LOG(...)                                  \
    do {                                                \
        fprintf(stderr, "%s@%d: ", __FILE__, __LINE__); \
        fprintf(stderr, __VA_ARGS__);                   \
        fprintf(stderr, "\n");                          \
    } while (0)
#else
#define DEBUG_LOG(...)
#endif

#endif//PYSHMKV_DEBUG_H
