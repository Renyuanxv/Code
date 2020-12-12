// MsgReceive.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

struct msg_st
{
    long int msg_type;
    char text[BUFSIZ];
};

int main()
{
    int running = 1;
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0; // 指定想要哪一种消息，type=0表示取第一个

    //建立消息队列 key_t为标识符
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    //从队列中获取消息，直到遇到end为止
    while (running)
    {
        if (msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1)
        {
            perror("msgrcv");
            exit(1);
        }
        printf("Recive Message: %s\n", data.text);
        //遇到end结束
        if (strncmp(data.text, "end", 3) == 0)
            running = 0;
    }

    //删除消息队列
    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
        perror("msgctl");
        exit(1);
    }
    return 0;
}

