//��װһ��udpsocket�࣬�����ṩ�򵥵Ľӿ�ʵ���׽��ֱ��
#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h> //close�ӿ�
#include <netinet/in.h> //sockaddr�ṹ�� / IPPROTO_UDP
#include <arpa/inet.h>  //����һЩ�ֽ���ת���Ľӿ�#include <sys/socket.h> //�׽��ֽӿ�ͷ�ļ�
#include <sys/socket.h> //�׽��ֽӿ�
using namespace std;

#define CHECK_RET(ret){if((ret)==false)return -1;}

class UdpSocket {
public:
    UdpSocket() :_sockfd(-1) {}
    //1.�����׽���
    bool Socket() {
        //socket(��ַ���׽������ͣ�Э������)
        _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_sockfd < 0) {
            perror("socket error");
            return false;
        }
        return true;
    }

    //2.Ϊ�׽��ְ󶨵�ַ��Ϣ
    bool Bind(const string& ip, uint16_t port) {
        //����IPV4��ַ�ṹ
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());

        //�󶨵�ַ
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = bind(_sockfd, (struct sockaddr*) & addr, len);
        if (ret < 0) {
            perror("bind error");
            return false;
        }
        return true;
    }

    //3.��������
    bool Send(const string& data, const string& ip, uint16_t port) {
        //sendto(�����������ݣ����ȣ�ѡ��Զ˵�ַ����ַ����)
        //����Զ˵�ַ��Ϣ��IPV4��ַ�ṹ
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        //�������ַ��������
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = sendto(_sockfd, data.c_str(), data.size(), 0, (struct sockaddr*) & addr, len);
        if (ret < 0) {
            perror("sendto error");
            return false;
        }
        return true;
    }

    //�����Ͳ���ʹ�� const ����
    //����Ͳ���ʹ�� ָ��
    //��������Ͳ���ʹ�� ����
    //4.��������
    bool Recv(string* buf, string* ip, uint16_t* port) {
        //recvfrom(�������������������ݳ��ȣ�ѡ��������Զ˵�ַ����ַ����)
        struct sockaddr_in addr;//���ڻ�ȡ���Ͷ˵�ַ��Ϣ
        socklen_t len = sizeof(struct sockaddr_in);
        int ret;
        char tmp[4096] = { 0 };//��ʱ���ڴ�����ݵĻ�����
        ret = recvfrom(_sockfd, tmp, 4096, 0, (struct sockaddr*) & addr, &len);
        if (ret < 0) {
            perror("recvfrom error");
            return false;
        }
        buf->assign(tmp, ret);//��buf����ret��С�ռ䣬��tmp�п���ret���ȵ����ݽ�ȥ
        //Ϊ�˽ӿ����û��������ȡ��ַ��Ϣ������ת����ȡ
        //ֻ�е��û���Ҫ��ȡ��ַ��ʱ�򣬲Ŵ��뻺������������д���ȥ  
        if (ip != NULL) {
            *ip = inet_ntoa(addr.sin_addr);//�������ֽ���IP��ַת��Ϊ�ַ�����ַ
        }
        if (port != NULL) {
            *port = ntohs(addr.sin_port);
        }
        return true;
    }
    //5.�ر��׽���
    void Close() {
        close(_sockfd);
        _sockfd = -1;
        return;
    }

private:
    //�ᴩȫ�ĵ��׽���������
    int _sockfd;

};
