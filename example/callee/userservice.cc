#include <iostream>
#include <string>
#include "user.pb.h"
#include "mprpcapplication.h"
#include "rpcprovider.h"
/*
    Userservice ԭ����һ�����ط���
    �ṩ�����̼�ı��ط�����Login��GetFriendLists
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
// �����ط��� ��д�� rpc����
class Userservice : public fixbug::UserServiceRpc // ʹ����rpc������ rpc�����ṩ��
{
public:
    bool Login(std::string name, std::string pwd)
    {
        std::cout << "doing local service: Login " << std::endl;
        std::cout << "name:" << name << " pwd:" << pwd << std::endl;
        return true;
    }
    /*
        rpc callee:
            1.ͨ��muduo����rpc����
            2.ͨ��rpc��ܴ������� =�� ��������->������Щ����->����ƥ�䣿->ƥ�䷽���������ϱ�
            3.server_stub�Է����Ĳ������з����л�
            4.server���շ����Ĳ�����ִ����Ӧ�ķ�����������ҵ�񣬷�����Ӧ��ִ�лص�
            5.server_stub�Է���ֵ�������л� ���ظ� caller
    */
    /*
        ��д�����麯��������ķ������ǿ��ֱ�ӵ���
        1.caller => login(LoginRequest) => muduo => collee
        2.callee => login(LoginRequest) => ������д�ķ�����
    */
    void Login(::google::protobuf::RpcController *controller,
               const ::fixbug::LoginRequest *request,
               ::fixbug::LoginResponse *response,
               ::google::protobuf::Closure *done)
    {
        // 1 ��ܸ�ҵ���ϱ��������LoginRequest��ҵ���ȡ��Ӧ����������ҵ��
        std::string name = request->name(); // �����ݷ����л����ֽ��� LoginRequest����
        std::string pwd = request->pwd();
        // 2 ����ҵ��
        bool login_result = Login(name, pwd); 
        // 3 ����Ӧд�� ���������� ������Ϣ ����ֵ
        fixbug::ResultCode* code = response->mutable_result();
        code->set_errcode(0);
        code->set_errmsg("");
        response->set_success(login_result);
        // 4 ִ�лص�  ִ����Ӧ�������ݵ� ���л������緢�� �ɿ�����
        done->Run();
    }
};

int main(int argc, char **argv)
{
    // ���ÿ�ܵĳ�ʼ������
    MprpcApplication::Init(argc, argv);

    // provider��һ��rpc���������󣬷���rpc����,�߲���,ʹ��muduo��ʵ��
    RpcProvider provider;
    // ��Userservice ������ rpc�ڵ���
    provider.NotifyService(new Userservice());
   
   
    // ����һ��rpc���񷢲��ڵ�,Run�� ��������״̬���ȴ�Զ��rpc����
    provider.Run();

    return 0;
}