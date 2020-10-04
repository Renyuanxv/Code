//封装一个udpsocket类，向外提供简单的接口实现套接字编程
#include <iostream>
#include <string>
#include <cstdio>
#include <stdlib.h>
#include <unistd.h> //close接口
#include <netinet/in.h> //sockaddr结构体 / IPPROTO_UDP
#include <arpa/inet.h>  //包含一些字节序转换的接口#include <sys/socket.h> //套接字接口头文件
#include <sys/socket.h> //套接字接口
using namespace std;

#define CHECK_RET(ret){if((ret)==false)return -1;}

class UdpSocket {
public:
    UdpSocket() :_sockfd(-1) {}
    //1.创建套接字
    bool Socket() {
        //socket(地址域，套接字类型，协议类型)
        _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (_sockfd < 0) {
            perror("socket error");
            return false;
        }
        return true;
    }

    //2.为套接字绑定地址信息
    bool Bind(const string& ip, uint16_t port) {
        //定义IPV4地址结构
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());

        //绑定地址
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = bind(_sockfd, (struct sockaddr*) & addr, len);
        if (ret < 0) {
            perror("bind error");
            return false;
        }
        return true;
    }

    //3.发送数据
    bool Send(const string& data, const string& ip, uint16_t port) {
        //sendto(描述符，数据，长度，选项，对端地址，地址长度)
        //定义对端地址信息的IPV4地址结构
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        //向这个地址发送数据
        socklen_t len = sizeof(struct sockaddr_in);
        int ret = sendto(_sockfd, data.c_str(), data.size(), 0, (struct sockaddr*) & addr, len);
        if (ret < 0) {
            perror("sendto error");
            return false;
        }
        return true;
    }

    //输入型参数使用 const 引用
    //输出型参数使用 指针
    //输入输出型参数使用 引用
    //4.接收数据
    bool Recv(string* buf, string* ip, uint16_t* port) {
        //recvfrom(描述符，缓冲区，数据长度，选项参数，对端地址，地址长度)
        struct sockaddr_in addr;//用于获取发送端地址信息
        socklen_t len = sizeof(struct sockaddr_in);
        int ret;
        char tmp[4096] = { 0 };//临时用于存放数据的缓冲区
        ret = recvfrom(_sockfd, tmp, 4096, 0, (struct sockaddr*) & addr, &len);
        if (ret < 0) {
            perror("recvfrom error");
            return false;
        }
        buf->assign(tmp, ret);//给buf申请ret大小空间，从tmp中拷贝ret长度的数据进去
        //为了接口灵活，用户若不想获取地址信息，则不再转换获取
        //只有当用户想要获取地址的时候，才传入缓冲区，将数据写入进去  
        if (ip != NULL) {
            *ip = inet_ntoa(addr.sin_addr);//将网络字节序IP地址转换为字符串地址
        }
        if (port != NULL) {
            *port = ntohs(addr.sin_port);
        }
        return true;
    }
    //5.关闭套接字
    void Close() {
        close(_sockfd);
        _sockfd = -1;
        return;
    }

private:
    //贯穿全文的套接字描述符
    int _sockfd;

};
