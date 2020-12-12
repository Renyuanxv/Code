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

    // ������Ϣ����, key_tΪ��ʶ��
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        perror("msgget");
        exit(1);
    }

    // ����Ϣ������д��Ϣ
    while (running)
    {
        // ��������
        printf("Send Message: ");
        fgets(buffer, BUFSIZ, stdin); // �ӱ�׼�����ȡ����
        data.msg_type = 1;    // ��Ϣ����
        strcpy(data.text, buffer); // �ѱ�׼���븴�Ƶ�msg_st��text��

        // ����з�������
        if (msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)
        {
            perror("msgsnd");
            exit(1);
        }

        // ����end����
        if (strncmp(buffer, "end", 3) == 0)
            running = 0;
        sleep(1);
    }
    return 0;
}

