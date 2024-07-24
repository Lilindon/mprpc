#pragma once

#include "mprpcconfig.h"
// mprpc��ܵĻ�����(����)
/*
�������
    private:  ����
              ������ֵ���������� = delete
    public: 
    ��ȡΩһʵ��
    static ����& GetInstance(){
        static ��Ŀ app;
        return app;
    }

*/
// mprpc��ܻ����࣬�����ܵĳ�ʼ��
class MprpcApplication{
public:
    static void Init(int argc, char **argv); // ��̬�����޷����ʷǾ�̬��Ա����
    static MprpcApplication& GetInstance();
private:
    MprpcApplication(){}
    MprpcApplication(const MprpcApplication&) = delete;
    MprpcApplication(MprpcApplication&&) = delete;
    static MprpcConfig m_config; // ��̬��Ա���� �����ⶨ��
};
