#include <sys/wait.h>                                                                                                                                  
#include "tcpsocket.hpp"
#include <iostream>
#include <signal.h>

using namespace std;

void sigcd() {
     //���ӽ����˳���ʱ��ͻ��򸸽��̷���SIGCHLD�źţ��ص��������
     //waitpid����ֵ>0��ʾ������һ���˳����ӽ���
     //waitpid<=0��ʾû���˳����ӽ���
     while (waitpid(-1, 0, WNOHANG) > 0);//һ�λص�ѭ�����˳����ӽ���ȫ������
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
         printf("em:./tcp.srv 192.168.122.132 9000\n");
         return -1;       
    }
       string ip = argv[1];
       uint16_t port = atoi(argv[2]);//stoi���ַ���תΪ����
    
       signal(SIGCHLD, sigcd);
       Tcpsocket lst_sock;
       CHECK_RET(lst_sock.Socket());
       CHECK_RET(lst_sock.Bind(ip, port));
       CHECK_RET(lst_sock.Listen()); //��ʼ����
       while (1) {
            Tcpsocket cli_sock;
            string cli_ip;
            uint16_t cli_port;
            bool ret = lst_sock.Accept(&cli_sock, &cli_ip, &cli_port);//��ȡ���׽���                                                                             
            if (ret == false) {
            //��ȡ������ʧ�ܣ��������¼�����ȡ��һ��
                 continue;
            }
            printf("new connect:[%s:%d]\n", cli_ip.c_str(), cli_port);
            //----------------------------------------------------------   
            pid_t pid = fork();
            if (pid == 0) {
            //���ӽ��̴�����ͻ���ͨ��
                while (1) {
                    string buf;
                    if (cli_sock.Recv(&buf) == false) {
                        cli_sock.Close();//ͨ���׽��ֽ������ݳ����رյ���ͨ���׽���
                        continue;
                    }
                    printf("client:[%s:%d] say:%s\n", &cli_ip[0], cli_port, &buf[0]);
                    cout << "server say: ";
                    fflush(stdout);
                    buf.clear();
                    cin >> buf;
                    if (cli_sock.Send(buf) == false) {
                        cli_sock.Close();
                        continue;
                    }
                }
                cli_sock.Close();
                exit(0);
            
            }
                //���ӽ������ݶ��У��������cli_sock�����Ǹ����̲���ͨ��
                cli_sock.Close();//����رն��ӽ���û��Ӱ�죬��Ϊ���ݸ�����һ�� 
        }
        return 0;
}
