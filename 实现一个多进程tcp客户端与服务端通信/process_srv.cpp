#include <sys/wait.h>                                                                                                                                  
#include "tcpsocket.hpp"
#include <iostream>
#include <signal.h>

using namespace std;

void sigcd() {
     //当子进程退出的时候就会向父进程发送SIGCHLD信号，回调这个函数
     //waitpid返回值>0表示处理了一个退出的子进程
     //waitpid<=0表示没有退出的子进程
     while (waitpid(-1, 0, WNOHANG) > 0);//一次回调循环将退出的子进程全部处理
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
         printf("em:./tcp.srv 192.168.122.132 9000\n");
         return -1;       
    }
       string ip = argv[1];
       uint16_t port = atoi(argv[2]);//stoi将字符串转为数字
    
       signal(SIGCHLD, sigcd);
       Tcpsocket lst_sock;
       CHECK_RET(lst_sock.Socket());
       CHECK_RET(lst_sock.Bind(ip, port));
       CHECK_RET(lst_sock.Listen()); //开始监听
       while (1) {
            Tcpsocket cli_sock;
            string cli_ip;
            uint16_t cli_port;
            bool ret = lst_sock.Accept(&cli_sock, &cli_ip, &cli_port);//获取新套接字                                                                             
            if (ret == false) {
            //获取新连接失败，可以重新继续获取下一个
                 continue;
            }
            printf("new connect:[%s:%d]\n", cli_ip.c_str(), cli_port);
            //----------------------------------------------------------   
            pid_t pid = fork();
            if (pid == 0) {
            //让子进程处理与客户端通信
                while (1) {
                    string buf;
                    if (cli_sock.Recv(&buf) == false) {
                        cli_sock.Close();//通信套接字接受数据出错，关闭的是通信套接字
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
                //父子进程数据独有，都会具有cli_sock，但是父进程并不通信
                cli_sock.Close();//这个关闭对子进程没有影响，因为数据各自有一份 
        }
        return 0;
}
