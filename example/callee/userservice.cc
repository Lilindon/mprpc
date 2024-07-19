#include <iostream>
#include <string>
#include "user.pb.h"

/*
    Userservice 原本是一个本地服务
    提供俩进程间的本地方法，Login和GetFriendLists
*/
// class Userservice
// {
// public:
//     bool login(std::string name, std::string pwd)
//     {
//         std::cout << "doing local service: Login " << std::endl;
//         std::cout << "name:" << name << " pwd:" << pwd << std::endl;
//     }
// };
// 将本地方法 改写成 rpc方法
class Userservice : public fixbug::UserServiceRpc // 使用在rpc发布端 提供者
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login " << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;
    }
    /*
        rpc callee:
            1.通过muduo接收rpc请求
            2.通过rpc框架处理请求 =》 接收请求->请求那些方法->方法匹配？->匹配方法的请求上报
            3.server_stub对方法的参数进行反序列化
            4.server接收方法的参数并执行相应的方法，做本地业务，返回响应，执行回调
            5.server_stub对返回值进行序列化 返回给 caller
    */
    /*
        重写基类虚函数，下面的方法都是框架直接调用
        1.caller => login(LoginRequest) => muduo => collee
        2.callee => login(LoginRequest) => 下面重写的方法上
    */
    void Login(::google::protobuf::RpcController *controller,
               const ::fixbug::LoginRequest *request,
               ::fixbug::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        // 1框架给业务上报请求参数LoginRequest，业务获取相应数据做本地业务
        std::string name = request->name(); // 将数据反序列化成字节流 LoginRequest对象
        std::string pwd = request->pwd();
        // 2本地业务
        bool login_result = Login(name, pwd); 
        // 3把响应写入 包括错误码 错误消息 返回值
        fixbug::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);
        // 4执行回调  执行响应对象数据的 序列化和网络发送 由框架完成
        done->Run();
    }
};

int main()
{
    // 本地调用
    Userservice us;
    us.Login("xxx", "xxx");

    return 0;
}