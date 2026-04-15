// Fork execution

#include<stdio.h>
int main()
{
    int counter = 0;
    int nPid = fork();
    printf("npid =%d\n", nPid);
    switch(nPid)
    {
        case -1 :
                printf("counter =%d\n");
                break;
        case 0 :
                counter = +4;
                printf("P2 counter =%d\n", counter);
        default:
                break;
    }
    counter++;
    printf("Countrer p1=%d\n",counter);

    wait(NULL);
    return 0;

}