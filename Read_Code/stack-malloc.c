#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>

struct ABC {
    int a;

    char str[];
};

void Myfun(int x)
{

    printf("%d\n", x);
}

typedef struct Pdev_tag {
    int a;
    int b;
    int c;
    int d;
    void (*Pfun)(int);
    char name[];

} Pdev;

int main(){
    struct ABC a;
    Pdev dev;
    Pdev *pdev = NULL;
    char str[] = "embedclub121122212221aksjajjajjsjsadsjkjkjfcjkadfcadjkjc";
    int i;

    pdev  = (Pdev *)malloc(sizeof(Pdev));

    pdev->a = 20;

    for(i = 0; i < strlen(str); i++){
        pdev->name[i] = str[i];
    }
//  pdev->name[0] = 'c';
//  pdev->name[1] = 'c';

    printf("%s\n", pdev->name);
    pdev->Pfun = &Myfun;

    if(pdev->Pfun)
        pdev->Pfun(pdev->a);


    dev.a = 10;
//  for(i = 0; i < strlen(str); i++){
    //dev.name[0] = 'c';
    //dev.name[1] = 'c';
//  }
    printf("%d\n", sizeof(Pdev));


    dev.Pfun = &Myfun;

    if(dev.Pfun)
        dev.Pfun(dev.a);

    return 0;
}
