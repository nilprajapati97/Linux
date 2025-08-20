// Fork execution

#include<stdio.h>
int main()
{
    int counter = 0;
    int nPid = fork();
    printf("nPid =%d\n", nPid);
    if(nPid == 0)
    {
        printf("Child process\n");
        counter=5;
        printf("Counter p2=%d\n", counter);
        return 0;
    }
    else
    {
        sleep(1);
        printf("Parent process\n");
        counter++;
        printf("Counter p1=%d\n", counter);
    }
    printf("Counter p1=%d\n",counter);

    return 0;

}
/*
Output:
nPid =1234
Parent process
Counter p1=1
nPid =1235
Child process
Counter p2=1
Counter p1=1 

*/