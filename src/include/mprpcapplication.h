#pragma once

#include "mprpcconfig.h"
// mprpc框架的基础类(单例)
/*
单例设计
    private:  构造
              （左右值）拷贝构造 = delete
    public: 
    获取惟一实例
    static 类名& GetInstance(){
        static 类目 app;
        return app;
    }

*/
// mprpc框架基础类，负责框架的初始化
class MprpcApplication{
public:
    static void Init(int argc, char **argv); // 静态方法无法访问非静态成员变量
    static MprpcApplication& GetInstance();
private:
    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
    static MprpcConfig m_config; // 静态成员变量 在类外定义
};
