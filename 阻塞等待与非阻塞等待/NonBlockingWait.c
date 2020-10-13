#include <stdio.h>                                                                  
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        return 1;
    }
    else if (pid == 0) {
        printf("child is run,pid is %d\n", getpid());
        sleep(5);
        exit(1);
    }
    else {
        int status = 0;
        pid_t ret = 0;
        while (ret == 0) {
            ret = waitpid(-1, &status, WNOHANG);//非阻塞等待 WNOHANG值为1的宏 
            if (ret == 0) {
                printf("child is running\n");
            }
            sleep(1);
        }
        if (WIFEXITED(status) && ret == pid) {
            printf("wait child 5s success,child return code is:%d\n", WEXITSTATUS(status));
        }
        else {
            printf("wait child failed,return.\n");
        }
    }
    return 0;
}

