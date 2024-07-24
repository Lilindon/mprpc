#pragma once
#include "google/protobuf/service.h"
// 框架提供的专门发布rpc服务的 网络对象类
class RpcProvider{
public:
    // 框架代码，提供发布rpc方法的函数接口，因此参数不能为具体业务层的Userservice
    void NotifyService(google::protobuf::Service *service);

    // 启动rpc服务节点，开始提供rpc远程过程调用服务
    void Run();
};

