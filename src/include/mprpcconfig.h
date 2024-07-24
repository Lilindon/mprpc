#pragma once

#include <unordered_map>
#include <string>

// ��ܶ�ȡ�����ļ���
// rpcserverip  rpcserverport zookeeperip zookerperport
class MprpcConfig{
public:
    // �������������ļ�
    void LoadConfigFile(const char *config_file);
    // ��ѯ��������Ϣ
    std::string Load(std::string key);


private:
    std::unordered_map<std::string, std::string> m_configMap;
    // ȥ���ַ���ǰ��Ŀո�
    void Trim(std::string& src_buf);
};