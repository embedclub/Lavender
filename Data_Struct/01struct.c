/*************************************************************************
	> File Name: 01struct.c
	> Author: scc
	> Mail: scc_ddcx@163.com
	> Created Time: 2016年09月06日 星期二 16时50分06秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * floattoch(float m);

static char chinese[] = "零壹贰叁肆伍陆柒捌玖点";
static char ch[80];

void main() {
    float m;
    char *s;

    printf("Input Number: ");
    scanf("%f", &m);
    s = floattoch(m);
    printf("\n%s\n", s);
}

char *floattoch(float m) {
    char tmp[30];
    int i, j, k = 0, flag = 0, d = 0, temp;
    float n;

    i = m;
    do {
        j = i % 10;
        tmp[k] = chinese[j*2];
        tmp[k+1] = chinese[j*2+1];
        k += 2;
        i /= 10;
    } while(i);
    tmp[k] = 0;
  //tmp[k]=0;
  printf("%d\n",strlen(tmp));
  for(i=strlen(tmp)-1;i>=0;i-=2,d+=2)
  {
    ch[d]=tmp[i-1];
    ch[d+1]=tmp[i];
  }

i=(m-(int)m)*1000; k=0; 
temp=i;       //待会判断用 
do 
{ 
  j=i%10; 
  if(j) flag=1; 
  if(flag) 
  { 
    tmp[k]=chinese[j*2]; 
    tmp[k+1]=chinese[j*2+1]; 
    k+=2; 
  } 
  i/=10; 
}while(i); 
 while(temp<100) 
{//加入零 
    tmp[k]=chinese[0]; 
    tmp[k+1]=chinese[1]; 
    k+=2; 
    temp*=10; 
} 
tmp[k]=0; 
  if(strlen(tmp))
  {
    ch[d]=chinese[20];
    ch[d+1]=chinese[21];
    d+=2;
  }
  for(i=strlen(tmp)-1;i>=0;i-=2,d+=2)
  {
    ch[d]=tmp[i-1];
    ch[d+1]=tmp[i];
  }

  return(ch);
}
