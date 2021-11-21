#include "main.h"
/*********************************************全局变量************************************************/
/**********************************************************************************************************
*函 数 名: main
*功能说明: 主函数
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/ 
int main()
{
	Init_Device();
	while(1)
	{

	}
	return 0;
}

//定时器2，扫描键盘，判断是否按下，中断周期为1.25ms	

void InterruptTime2() interrupt 5								//定时器2中断
{	
	  static unsigned char Key_Dat = 0;
		//P4 = 0x00;
		if(Key_Dat==5) 
		{
			Key_Dat = 0;
		}
		if(Key_Dat==0)
		{
			KEY_DAT = 0;
		}
		else
		{
			KEY_DAT = 1;
		}
		KEY_CLK = 1;
		Keyscan(Key_Dat);
		Key_Dat+=1;
		KEY_CLK = 0;
		TF2 = 0;																		//清除中断标志位
	  
}
	

//定时器4，扫描键值，并执行相应操作，中断周期为1.25ms	
void InterruptTime4() interrupt 16	
{	
	
		KeyboardDriver();
  	T4CON &=0x7F;						//清除中断标志位																							·
															
}	

//延时函数，粗延时，直接用for循环执行无意义语句延时
void delay( int time_us)
{
	int i =0;
	int j;
	for(i=0;i<time_us;i++)
	{
		j=0;
	}
}




