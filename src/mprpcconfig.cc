#include "mprpcconfig.h"
#include <iostream>
#include <string>

// �������������ļ�
void MprpcConfig::LoadConfigFile(const char *config_file){
    FILE *pf = fopen(config_file, "r");
    if(pf == nullptr){
        std::cout << config_file << " is not exist!" << std::endl;
        exit(EXIT_FAILURE);
    }

    // 1ע�� 2��ȷ�������� 3ȥ����ͷ����Ŀո�
    while(!feof(pf)){
        char buf[512] = {0};
        fgets(buf, 512, pf);
        // ȥ���ַ���ǰ�����ո�
        std::string read_buf(buf);
        Trim(read_buf);
        // �ж� # ��ע��
        if(read_buf[0] == '#' || read_buf.empty()){
            continue;
        }
        // ����������
        int idx = read_buf.find("=");
        if(idx == -1){
            // ���ò��Ϸ�
            continue;
        }
        std::string key;
        std::string value;
        key = read_buf.substr(0,idx);
        Trim(key);
        // 127.0.0.1  \n
        int endidx = read_buf.find('\n', idx); 
        value = read_buf.substr(idx+1, endidx-idx-1);
        Trim(value);
        m_configMap.insert({key, value});
    }
}

// ��ѯ��������Ϣ
std::string MprpcConfig::Load(std::string key){
    auto it = m_configMap.find(key);
    if(it == m_configMap.end()){
        return  "";
    }
    return it->second;  
}

void MprpcConfig::Trim(std::string& src_buf){
    int idx = src_buf.find_first_not_of(' ');
    if(idx != -1){
        src_buf = src_buf.substr(idx, src_buf.size()-idx);
    }
    // ȥ���ַ�������Ķ���ո�
    idx = src_buf.find_last_not_of(' ');
    if(idx != -1){
        src_buf = src_buf.substr(0, idx+1);
    }



}
