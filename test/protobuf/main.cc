#include "test.pb.h"
#include <iostream>
#include <string>
using namespace fixbug;

int main()
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