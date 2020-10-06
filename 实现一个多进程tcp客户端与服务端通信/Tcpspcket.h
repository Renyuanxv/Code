#pragma once
//��װʵ��һ��tcpsocket�࣬�����ṩ�򵥽ӿ�
//ʹ�ⲿͨ��ʵ����һ��tcpsocket����������tcpͨ�ų���Ľ���
#include <netinet/in.h> //sockaddr�ṹ�� 
#include <sys/socket.h> //�׽��ֽӿ�ͷ�ļ�
#include <string>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
    using namespace std;
    #define BACKLOG 10
    #define CHECK_RET(ret)  if ((ret) == false) { return -1; }

 class Tcpsocket {
   public:
         Tcpsocket() :_sockfd(-1) {
       
         }
   
         //�����׽���                                      
         bool Socket() {
          //socket(��ַ���׽������ͣ�Э������)
          _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
                if (_sockfd < 0) {
                       perror("socket error");
                       return false;
            
                }
         return true;
        
         }

       void Addr(struct sockaddr_in* addr, const string & ip, uint16_t port) {
             addr->sin_family = AF_INET;
             addr->sin_port = htons(port);
             inet_pton(AF_INET, ip.c_str(), &(addr->sin_addr.s_addr));
        
       }
  
       //�󶨵�ַ��Ϣ
       bool Bind(const string & ip, const uint16_t port) {
            struct sockaddr_in addr;
            Addr(&addr, ip, port);
            socklen_t len = sizeof(struct sockaddr_in);
            int ret = bind(_sockfd, (struct sockaddr*) & addr, len);
            if (ret < 0) {
                  perror("bind error");
                  return false;
            
            }
            return true;
       }
    
       //����˿�ʼ����  
       bool Listen(int backlog = BACKLOG) {
       //listen(��������ͬһʱ��Ĳ���������)
            int ret = listen(_sockfd, backlog);
            if (ret < 0) {
                    perror("listen error");
                    return false;
            
                }
            return true;
       }
    
       //�ͻ��˷�����������
       bool Connect(const string & ip, const uint16_t port) {
               //����IPV4��ַ�ṹ���������˵�ַ��Ϣ
               struct sockaddr_in addr;
               Addr(&addr, ip, port);
        
                //�����˷�������                       
                //connect(�ͻ���������������˵�ַ��Ϣ����ַ����) 
              socklen_t len = sizeof(struct sockaddr_in);
              int ret = connect(_sockfd, (struct sockaddr*) & addr, len);
              if (ret < 0) {
                     perror("connect error");
                     return false;
              }
              return true;
        }
    
       //����˻�ȡ�½�����                    
       bool Accept(Tcpsocket * sock, string * ip = NULL, uint16_t * port = NULL) {
            //accept(�����׽��֣��Զ˵�ַ��Ϣ����ַ��Ϣ����) �����µ�������
            struct sockaddr_in addr;
            socklen_t len = sizeof(struct sockaddr_in);
            //��ȡ�µ��׽��֣��Լ�����׽��ֶ�Ӧ�ĶԶ˵�ַ��Ϣ               
            int clisockfd = accept(_sockfd, (struct sockaddr*) & addr, &len);
            if (clisockfd < 0) {
                    perror("accept error");
                    return false;
            }
            //�û�������һ��Tcpsocket�����ָ��   
            //Ϊ�����������������и�ֵ---��ֵΪ�½��׽��ֵ���������
            //������ͻ��˵�ͨ��ͨ���������Ϳ������    
            sock->_sockfd = clisockfd;
            if (ip != NULL) {
                 * ip = inet_ntoa(addr.sin_addr);//�����ֽ���IP->�ַ���IP
             }
            if (port != NULL) {
                * port = ntohs(addr.sin_port);
            }
            return true;
       }
    
           //��������                         
        bool Send(const string & data) {
        //send(�����������ݣ����ݳ��ȣ�ѡ�����)                       
             int ret = send(_sockfd, data.c_str(), data.size(), 0);
             if (ret < 0) {
                  perror("send error");
                  return false;
             }
              return true;
        }
    
        //��������                                         
        bool Recv(string * buf) {
              //recv(�������������������ݳ��ȣ�ѡ�����)
              char tmp[4096] = { 0 };
              int ret = recv(_sockfd, tmp, 4096, 0);
               if (ret < 0) {
                     perror("recv error");
                     return false;
            
                }
               else if (ret == 0) {
                     printf("connection break\n");
                     return false;
            
              }
              buf->assign(tmp, ret);//��tmp�п���ret��С�����ݵ�buf��
              return true;
        }
    
        //�ر��׽���
        void Close() {
             close(_sockfd);
             _sockfd = -1;
        }

private:
     int _sockfd;
};

