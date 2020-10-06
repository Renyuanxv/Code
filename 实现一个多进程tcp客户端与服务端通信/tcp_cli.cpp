//ͨ����װ��Tcpsocket��ʵ��������ʵ��tcp�ͻ��˳���                                                                                                       
#include <iostream>
#include <stdlib.h>
#include "tcpsocket.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("em:./tcp_cli 192.168.122.321 9000--����˰󶨵ĵ�ַ\n");
        return -1;
    }
    string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    Tcpsocket cli_sock;
    //�����׽���                
    CHECK_RET(cli_sock.Socket());
    //�󶨵�ַ��Ϣ(���Ƽ�)       
    //�����˷�������        
    CHECK_RET(cli_sock.Connect(ip, port));
    //ѭ���շ�����                       
    printf("client say: ");
    fflush(stdout);
    string buf;
    cin >> buf;
    //��Ϊ�ͻ��˲����ڶ����׽��ֵ��ļ������һ����ǰ�׽��ֳ���ֱ���˳�����
    / �����˳��ͻ��ͷ���Դ���ر��׽���
        CHECK_RET(cli_sock.Send(buf));
    buf.clear();
    CHECK_RET(cli_sock.Send(buf));
    buf.clear();
    CHECK_RET(cli_sock.Recv(&buf));
    printf("server say: %s\n", buf.c_str());
}
    // �ر��׽���
    cli_sock.Close();
    return 0;
}