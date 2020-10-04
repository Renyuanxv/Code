//===============================
//��дһ��udp����˵�C���Գ���
//1.�����׽���
//2.Ϊ����׽��ְ󶨵�ַ��Ϣ
//3.��������
//4.��������
//5.�ر��׽���
//===============================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h> //sockaddr�ṹ�� / IPPROTO_UDP
#include <arpa/inet.h>  //����һЩ�ֽ���ת���Ľӿ�
#include <sys/socket.h> //�׽��ֽӿ�ͷ�ļ�

int main(int argc, char* argv[]) {
    //argc��ʾ����������ͨ��argv����򴫵ݶ˿ڲ���
    if (argc != 3) {
        printf("./udp_srv ip port   em: ./udp_srv 192.168.113.129 9000");
        return -1;
    }
    const char* ip_addr = argv[1];
    uint16_t port_addr = atoi(argv[2]);

    //�����׽���  socket(��ַ���׽������ͣ�Э������)
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
        perror("socket error");
        return -1;
    }

    //�󶨵�ַ��Ϣ  bind(�׽�������������ַ�ṹ����ַ����)
    //struct_sockaddr_in IPV4��ַ�ṹ
    //struct in_addr{uint32_t s_addr}; 
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    //htos-�������ֽڵ������ֽ�������ת��Ϊ�����ֽ��������
    addr.sin_port = htons(port_addr);//��Ҫʹ��htonl �����
    //inet_addr-��һ�����ʮ���Ƶ��ַ���IPת��Ϊ�����ֽ��������IP��ַ
    addr.sin_addr.s_addr = inet_addr(ip_addr);
    socklen_t len = sizeof(struct sockaddr_in);//��ȡIPV4�ĵ�ַ�ṹ����
    int ret = bind(sockfd, (struct sockaddr*) & addr, len);
    if (ret < 0) {
        perror("bind error");
        return -1;
    }

    //ѭ���������� recvfrom(�������������������ȣ��������ͻ��˵�ַ��Ϣ����ַ��Ϣ����)
    while (1) {
        char buf[1024] = { 0 };
        struct sockaddr_in cli_addr;
        socklen_t len = sizeof(struct sockaddr_in);
        //recvfrom(�������������������ȣ��������ͻ��˵�ַ��Ϣ����ַ��Ϣ����)
        //�����������ݣ������ݷ���buf�У������Ͷ˵ĵ�ַ����cli_addr�� 
        int ret = recvfrom(sockfd, buf, 1023, 0, (struct sockaddr*) & cli_addr, &len);
        if (ret < 0) {
            perror("recvfrom error");
            return -1;
        }
        printf("client say:%s\n", buf);

        printf("server say:");
        fflush(stdout);//���û���������,���͸��ͻ���
        memset(buf, 0X00, 1024);//���buf�е�����
        scanf("%s", buf);
        //ͨ��sendto��buf�е����ݷ��͵�cliaddr�ͻ���
        ret = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*) & cli_addr, len);
        if (ret < 0) {
            perror("sendto error");
            return -1;
        }
    }
    close(sockfd);//�ر��׽���
}
