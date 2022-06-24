#pragma once
#pragma warning( disable : 4996)
#define WIN32
#ifdef WIN32 //Windows
#include <direct.h>
#include <io.h>
#else  // Linux
#include <sys/io.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#endif

#include <string>
#include <iostream>

inline void create_folder(const std::string &dir_path) {
    if (access(dir_path.c_str(), 0) == -1) { //判断该文件夹是否存在
#ifdef WIN32
        int flag = mkdir(dir_path.c_str());  //Windows创建文件夹
#else
        int flag = mkdir(dir.c_str(), S_IRWXU);  //Linux创建文件夹
#endif
        if (flag == 0) {  //创建成功
            std::cout << "Create directory successfully." << std::endl;
        }
        else { //创建失败
            std::cout << "Fail to create directory." << std::endl;
            throw std::exception();
        }
    }
    else {
        std::cout << "This directory already exists." << std::endl;
    }
}
