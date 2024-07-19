#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;

int main(){
    // LoginResponse rsp;
    // ResultCode *rc = rsp.mutable_result();
    // rc->set_errcode(1);
    // rc->set_errmsg("login error");

    GetFriendListResponse rsp;
    ResultCode *rc = rsp.mutable_result(); // 使用mutable_修改result里面的数据
    rc->set_errcode(0);

    User *user1 = rsp.add_friend_list();   // 使用add_修改friend_list里面的数据
    user1->set_name("zhang san");          // 使用set_设置对象的值
    user1->set_age(20); 
    user1->set_sex(User::MAN);

    std::cout << rsp.friend_list_size() << std::endl;
    return 0;
}


int main1()
{
    LoginRequest req;
    req.set_name("zhang san");
    req.set_pwd("123456");

    std::string send_str;
    // 序列化为字节流
    if(req.SerializeToString(&send_str)){
        std::cout << send_str.c_str() << std::endl;
    }

    // 从send_str反序列化 一个login请求对象
    LoginRequest reqB;
    if(reqB.ParseFromString(send_str)){
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }

    return 0;
}