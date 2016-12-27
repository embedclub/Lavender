#include <reg52.h>

sbit pga_cs					=P1^1;
sbit pga_di					=P1^2;
sbit pga_sk					=P1^3;

extern pga_send(unsigned char buff_left,unsigned char buff_right);
