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
    ResultCode *rc = rsp.mutable_result(); // ʹ��mutable_�޸�result���������
    rc->set_errcode(0);

    User *user1 = rsp.add_friend_list();   // ʹ��add_�޸�friend_list���������
    user1->set_name("zhang san");          // ʹ��set_���ö����ֵ
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
    // ���л�Ϊ�ֽ���
    if(req.SerializeToString(&send_str)){
        std::cout << send_str.c_str() << std::endl;
    }

    // ��send_str�����л� һ��login�������
    LoginRequest reqB;
    if(reqB.ParseFromString(send_str)){
        std::cout << reqB.name() << std::endl;
        std::cout << reqB.pwd() << std::endl;
    }

    return 0;
}