#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#define MAX_TEXT 512
struct msg_st
{
    long int msg_type;
    char text[MAX_TEXT];
};
int main()
{
    int running = 1;
    struct msg_st data;
    char buffer[BUFSIZ];
    int msgid = -1;

    // 建立消息队列, key_t为标识符
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    // 向消息队列中写消息
    while (running)
    {
        // 输入数据
        printf("Send Message: ");
        fgets(buffer, BUFSIZ, stdin); // 从标准输入读取数据
        data.msg_type = 1;    // 消息类型
        strcpy(data.text, buffer); // 把标准输入复制到msg_st的text中

        // 向队列发送数据
        if (msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)
        {
            perror("msgsnd");
            exit(1);
        }

        // 输入end结束
        if (strncmp(buffer, "end", 3) == 0)
            running = 0;
        sleep(1);
    }
    return 0;
}

