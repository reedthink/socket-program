//一个题外话：文件的信息是存储在何处？比如创建时间和修改时间
#include <stdio.h>
#include <unistd.h>
int gval = 10;
int main(int argc, char *argv[])
{
    __pid_t pid;
    int lval = 20;
    gval++;
    lval += 5;

    pid = fork();
    // int n;
    // scanf("%d",&n);
    if (pid == 0)
    {
        gval += 2;
        lval += 2;
    }
    else
        gval -= 2, lval -= 2;
    if (pid == 0)
    {
        printf("Child Proc: [%d,%d] \n", gval, lval);
    }
    else
    {
        printf("Parent Proc: [%d,%d] \n", gval, lval);
    }
    return 0;
}