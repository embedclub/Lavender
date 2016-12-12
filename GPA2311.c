#include <pga2311.h>

void pga_send(unsigned char buff_left,unsigned char buff_right)
{
	pga_sk=0;
	pga_cs=0;
	pga_cs=0;
	pga_cs=0;
	pga_cs=0;
	pga_cs=0;
	for(i=0;i<8;i++)
	{
		if(buff_right&0x80)
			pga_di=1;
		else
			pga_di=0;
		buff_right=buff_right<<1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=0;
	}
	for(i=0;i<8;i++)
	{
		if(buff_left&0x80)
			pga_di=1;
		else
			pga_di=0;
		buff_left=buff_left<<1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=0;
	}
	pga_cs=1;
	pga_di=1;
}

/*
void pga_send2(unsigned char buff_l,unsigned char buff_r)
{
	//第一片增益范围buff_left1			20-192(-86~0DB)
	//第二片增益范围buff_left2			20-240(-86~24DB)
	//单通道增益数据buff_l				0-260(-10~120)
	//单通道校准调整pga_offset_left		0-130
	//调整数据							41
	//buff_left1 + buff_left2 = buff_l*2 + 41 + pga_offset_left

	unsigned char i;
	unsigned char buff_left1;
	unsigned char buff_left2;
	unsigned char buff_right1;
	unsigned char buff_right2;
	unsigned int ii;

	//左声道
	ii=(unsigned int)buff_l*2+41+(unsigned int)pga_offset_left;
	if(ii<120)
	{
		buff_left1=20;
		buff_left2=ii-buff_left1;
	}
	else
	{
		if(ii<215)
		{
			buff_left1=96;
			buff_left2=ii-buff_left1;
		}
		else
		{
			buff_left1=192;
			buff_left2=ii-buff_left1;
		}
	}
	//右声道
	ii=(unsigned int)buff_r*2+41+(unsigned int)pga_offset_right;
	if(ii<120)
	{
		buff_right1=20;
		buff_right2=ii-buff_right1;
	}
	else
	{
		if(ii<215)
		{
			buff_right1=96;
			buff_right2=ii-buff_right1;
		}
		else
		{
			buff_right1=192;
			buff_right2=ii-buff_right1;
		}
	}
	
	pga_sk=0;
	pga_cs=0;
	pga_cs=0;
	pga_cs=0;
	pga_cs=0;
	pga_cs=0;
	for(i=0;i<8;i++)
	{
		if(buff_right2&0x80)
			pga_di=1;
		else
			pga_di=0;
		buff_right2=buff_right2<<1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=0;
	}
	for(i=0;i<8;i++)
	{
		if(buff_right1&0x80)
			pga_di=1;
		else
			pga_di=0;
		buff_right1=buff_right1<<1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=0;
	}
	for(i=0;i<8;i++)
	{
		if(buff_left2&0x80)
			pga_di=1;
		else
			pga_di=0;
		buff_left2=buff_left2<<1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=0;
	}
	for(i=0;i<8;i++)
	{
		if(buff_left1&0x80)
			pga_di=1;
		else
			pga_di=0;
		buff_left1=buff_left1<<1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=1;
		pga_sk=0;
	}
	pga_cs=1;
	pga_di=1;
}
*/
