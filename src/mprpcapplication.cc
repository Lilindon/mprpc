#include "mprpcapplication.h"
#include <iostream>
#include <unistd.h>
#include <string>

// 静态成员变量 在类外初始化
MprpcConfig MprpcApplication::m_config;

MprpcApplication& MprpcApplication::GetInstance(){
    static MprpcApplication app;
    return app;
}

void ShowArgsHelp(){
    std::cout << "format: command -i <configfile> " << std::endl;
}

// 类外实现静态方法 不用带static
void MprpcApplication::Init(int argc, char **argv){
    if(argc < 2){
        ShowArgsHelp();
        exit(EXIT_FAILURE);
    }
    int c = 0;
    std::string config_files;
    while((c = getopt(argc, argv, "i:")) != -1){ // 获取一个不可少的i参数
        switch(c){
        case 'i':
            config_files = optarg;
            break;
        case '?':
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        case ':':
            ShowArgsHelp();
            exit(EXIT_FAILURE);
        default:
            break;
        }
    }

    // 开始加载配置文件 rpcserver_ip= rpcserver_port zookeep
    m_config.LoadConfigFile(config_files.c_str()); 
    std::cout << "rpcserverip:" << m_config.Load("rpcserverip") << std::endl;
    std::cout << "rpcserverport:" << m_config.Load("rpcserverport") << std::endl;
    std::cout << "zookeeperip:" << m_config.Load("zookeeperip") << std::endl;
    std::cout << "zookerperport:" << m_config.Load("zookerperport") << std::endl;
}
