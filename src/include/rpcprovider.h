#pragma once
#include "google/protobuf/service.h"
// ����ṩ��ר�ŷ���rpc����� ���������
class RpcProvider{
public:
    // ��ܴ��룬�ṩ����rpc�����ĺ����ӿڣ���˲�������Ϊ����ҵ����Userservice
    void NotifyService(google::protobuf::Service *service);

    // ����rpc����ڵ㣬��ʼ�ṩrpcԶ�̹��̵��÷���
    void Run();
};

