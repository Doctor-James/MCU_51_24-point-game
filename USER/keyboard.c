#include "main.h"
unsigned char keybuf[5][4] = {
		{0,0,0,0},{0,0,0,0},
		{0,0,0,0},{0,0,0,0},{0,0,0,0}};

char cal_str[32];
unsigned char number_rand[4];  //随机生成的四个数
unsigned int number_rand_state[4] = {0,0,0,0};  //备份
unsigned int number_rand_temp[4];  //随机生成的四个数
unsigned char dip_number_temp;
unsigned int number_rand_temptemp;
unsigned char keybuf_temp[5][4] = {
		{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},
		{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00},{0x00,0x00,0x00,0x00}};
static unsigned char keybuf_backup[5][4] = {
		{0,0,0,0},{0,0,0,0},
		{0,0,0,0},{0,0,0,0},{0,0,0,0}};
static unsigned char dip_number;
static unsigned char dip_number_col;
static unsigned char cal_number;
int result;					//计算所得的结果
unsigned int rand_seed;	//随机数种子
		
		
void Keyscan(unsigned char scannum)//读取键盘扫描值，即列信号，再判断行
{
	unsigned char i;

	keybuf_temp[scannum][0] = (keybuf_temp[scannum][0]<<1)|((~P4)&0x01);						//软件消抖，按位或，每扫描一次将键值最低位置1并左移一位
	keybuf_temp[scannum][1] = (keybuf_temp[scannum][1]<<1)|(((~P4)&0x02)>>1);
	keybuf_temp[scannum][2] = (keybuf_temp[scannum][2]<<1)|(((~P4)&0x04)>>2);
	keybuf_temp[scannum][3] = (keybuf_temp[scannum][3]<<1)|(((~P4)&0x08)>>3);
		
	for(i = 0;i < 4;i++)
	{
		if((keybuf_temp[scannum][i] & 0x1F) == 0x00) keybuf[scannum][i] = 0;					//检测到五次按下/松开，将键值标志位置1/0
		if((keybuf_temp[scannum][i] & 0x1F) == 0x1F) keybuf[scannum][i] = 1;
	}
	
}

void KeyboardDriver()			//键盘驱动程序
{
	unsigned char i,j,k;
	for(i = 0;i<5;i++)
	{
		for(j = 0;j<4;j++)
		{
			if(keybuf[i][j] != keybuf_backup[i][j])		//检测到跳变执行键盘相应功能
			{
				if(keybuf[i][j] == 1)
				{
					KeyboardMap(i,j);
				}
				keybuf_backup[i][j] = keybuf[i][j];
				k = 0;
			}											
		}
	}
}


void KeyboardMap(unsigned char i,unsigned char j)	//键盘功能映射
{

	if(dip_number>7&&dip_number_col ==0)
	{
		dip_number = 1;
		dip_number_col = 1;
	}
	else if(dip_number>7&&dip_number_col ==1)
	{
		dip_number = 1;
		dip_number_col = 2;
	}
		if(i ==0)
		{
			switch(j)
				{
					case 0:key_16(dip_number,dip_number_col);break;
					case 1:key_1(dip_number,dip_number_col); break;
					case 2:key_2(dip_number,dip_number_col); break;
					case 3:key_3(dip_number,dip_number_col); break;
					default:break;
				}
		}
		else if(i ==1)
		{
			switch(j)
				{
					case 0:key_4(dip_number,dip_number_col);break;
					case 1: break;
					case 2: break;
					case 3: break;
					default:break;
				}
		}
		else if(i ==2)
		{
			switch(j)
				{
					case 0:break;
					case 1: break;
					case 2:	key_17(dip_number,dip_number_col); break;
					case 3: key_11();break;
					default:break;
				}
		}
		else if(i ==3)
		{
			switch(j)
				{
					case 0:dip_number = 1;dip_number_col = 0;cal_number = 0;P4|=0xF0;F1_start();break;
					case 1:dip_number = 1;dip_number_col = 0;cal_number = 0;P4|=0xF0;key_F2();break;
					case 2:break;
					case 3:break;
					default:break;
				}
		}
		else if(i ==4)
		{
			switch(j)
				{
					case 0: key_12(dip_number,dip_number_col); break;
					case 1: key_13(dip_number,dip_number_col); break;
					case 2: key_14(dip_number,dip_number_col); break;
					case 3: key_15(dip_number,dip_number_col); break;
					default:break;
				}
		}
	
	
}


unsigned char toascll(unsigned char number)
{
	return number+0x30;
}

void set_24()
{
		unsigned char i;
    //使用for循环生成4个随机数
    for (i = 0; i < 4; i++) {
				srand(rand_seed);		       
				number_rand_temp[i] = (unsigned int)rand_seed;
			number_rand_temptemp = rand();
			  number_rand[i] = rand()%12+1;
				rand_seed+=number_rand[i];		//将随机数种子和每次生成的随机数相加作为新的随机数种子
    }
}

/*
** 按键功能，具体功能见报告中的键盘功能表
*/

void F1_start()
{
		unsigned char lcd[32] = {0};
		unsigned char i=0;
		set_24();
		clear();
	for(i=0;i<2;i++)
	{
		number_rand_state[i] = 0;
		LCD_Map(number_rand[i],lcd);
		dis_on_off(1);
		set_stratline(0);
		display_32_left(0,32*i,lcd);
	
	}
	
		for(i=2;i<4;i++)
	{
		number_rand_state[i] = 0;
		LCD_Map(number_rand[i],lcd);
		dis_on_off(1);
		set_stratline(0);
		display_32_right(0,32*(i-2),lcd);
	}

}


int key_1(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		if(number_rand_state[0] == 1)
		{
			return 0;
		}
		dis_on_off(1);
		set_stratline(0);
		
		//依次显示，设置显示的数字及位置
		if(number<=4)
		{
			LCD_Map(number_rand[0],lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(number_rand[0],lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		
		
		
		//此处代码是为了将诸如A,B,C,D的数在字符数组中存为10，11，12，13
		if(number_rand[0]<10)
		{
			cal_str[cal_number] = toascll(number_rand[0]);
			cal_number+=1;
		}
		else if(number_rand[0] == 10)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(0);
			cal_number+=1;
		}
		else if(number_rand[0] == 11)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
		}
		else if(number_rand[0] == 12)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(2);
			cal_number+=1;
		}
		else if(number_rand[0] == 13)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(3);
			cal_number+=1;
		}
		LCD_Map(0,lcd);
		dis_on_off(1);
		set_stratline(0);
		display_32_left(0,0,lcd);
		dip_number+=1;
		number_rand_state[0] = 1;
}

int key_2(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		if(number_rand_state[1] == 1)
		{
			return 0;
		}
		dis_on_off(1);
		set_stratline(0);
		if(number<=4)
		{
			LCD_Map(number_rand[1],lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(number_rand[1],lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		if(number_rand[1]<10)
		{
			cal_str[cal_number] = toascll(number_rand[1]);
			cal_number+=1;
		}
		else if(number_rand[1] == 10)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(0);
			cal_number+=1;
		}
		else if(number_rand[1] == 11)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
		}
		else if(number_rand[1] == 12)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(2);
			cal_number+=1;
		}
		else if(number_rand[1] == 13)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(3);
			cal_number+=1;
		}
		LCD_Map(0,lcd);
		dis_on_off(1);
		set_stratline(0);
		display_32_left(0,32,lcd);
		dip_number+=1;
		number_rand_state[1] = 1;
}

int key_3(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		
		if(number_rand_state[2] == 1)
		{
			return 0;
		}
		dis_on_off(1);
		set_stratline(0);
		if(number<=4)
		{
			LCD_Map(number_rand[2],lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(number_rand[2],lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		if(number_rand[2]<10)
		{
			cal_str[cal_number] = toascll(number_rand[2]);
			cal_number+=1;
		}
		else if(number_rand[2] == 10)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(0);
			cal_number+=1;
		}
		else if(number_rand[2] == 11)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
		}
		else if(number_rand[2] == 12)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(2);
			cal_number+=1;
		}
		else if(number_rand[2] == 13)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(3);
			cal_number+=1;
		}
		LCD_Map(0,lcd);
		dis_on_off(1);
		set_stratline(0);
		display_32_right(0,0,lcd);
		dip_number+=1;
		number_rand_state[2] = 1;
}

int key_4(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		
		if(number_rand_state[3] == 1)
		{
			return ;
		}
		
		dis_on_off(1);
		set_stratline(0);
		if(number<=4)
		{
			LCD_Map(number_rand[3],lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(number_rand[3],lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		if(number_rand[3]<10)
		{
			cal_str[cal_number] = toascll(number_rand[3]);
			cal_number+=1;
		}
		else if(number_rand[3] == 10)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(0);
			cal_number+=1;
		}
		else if(number_rand[3] == 11)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
		}
		else if(number_rand[3] == 12)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(2);
			cal_number+=1;
		}
		else if(number_rand[3] == 13)
		{
			cal_str[cal_number] = toascll(1);
			cal_number+=1;
			cal_str[cal_number] = toascll(3);
			cal_number+=1;
		}
		LCD_Map(0,lcd);
		dis_on_off(1);
		set_stratline(0);
		display_32_right(0,32,lcd);
		dip_number+=1;
		number_rand_state[3] = 1;
}

void key_12(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		dis_on_off(1);
		set_stratline(0);
		if(number<=4)
		{
			LCD_Map(14,lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(14,lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		cal_str[cal_number] = '+';
		dip_number+=1;
		cal_number+=1;
}

void key_13(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		dis_on_off(1);
		set_stratline(0);
		if(number<=4)
		{
			LCD_Map(15,lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(15,lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		cal_str[cal_number] = '-';
		dip_number+=1;
		cal_number+=1;
}

void key_14(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		dis_on_off(1);
		set_stratline(0);
		if(number<=4)
		{
			LCD_Map(16,lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(16,lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		cal_str[cal_number] = '*';
		dip_number+=1;
		cal_number+=1;
}

void key_15(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		dis_on_off(1);
		set_stratline(0);
		if(number<=4)
		{
			LCD_Map(17,lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(17,lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		cal_str[cal_number] = '/';
		dip_number+=1;
		cal_number+=1;
}

void key_16(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		dis_on_off(1);
		set_stratline(0);
		if(number<=4)
		{
			LCD_Map(18,lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(18,lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		cal_str[cal_number] = '(';
		dip_number+=1;
		cal_number+=1;
}

void key_17(unsigned char number,unsigned char number_col)
{
		unsigned char lcd[32] = {0};
		dis_on_off(1);
		set_stratline(0);
		if(number<=4)
		{
			LCD_Map(19,lcd);
			display_32_left(2+(number_col*2),16*(number-1),lcd);
		}
		else if(number>4&&number<=8)
		{
			LCD_Map(19,lcd);
			display_32_right(2+(number_col*2),16*(number-5),lcd);
		}
		cal_str[cal_number] = ')';
		dip_number+=1;
		cal_number+=1;
}


//计算结果，并判断结果是否为24
void key_11()
{
	int result;
	unsigned char i;
	result = cal_main();
	if(result == 24)
	{
		P4&=0xEF;
	}
	else
	{
		P4&=0xDF;
	}
}

void key_F2()
{
	unsigned char lcd[32] = {0};
	unsigned char i=0;
	clear();
	for(i=0;i<2;i++)
	{
		number_rand_state[i] = 0;
		LCD_Map(number_rand[i],lcd);
		dis_on_off(1);
		set_stratline(0);
		display_32_left(0,32*i,lcd);
	}
	
		for(i=2;i<4;i++)
	{
		number_rand_state[i] = 0;
		LCD_Map(number_rand[i],lcd);
		dis_on_off(1);
		set_stratline(0);
		display_32_right(0,32*(i-2),lcd);
	}
}



//计算字符数组的主程序
int cal_main()
{
	int num1 = 0, num2 = 0, i = 0, tmp = 0;
	unsigned char debug;
	Stack *s_num = NULL, *s_opt = NULL;
	char *opt=(char *)malloc(cal_number*sizeof(char));
	memcpy(opt,cal_str,cal_number);
	if(StackInit(&s_num) !=SUCCESS || StackInit(&s_opt)	!= SUCCESS)
	{
		//printf("Stack Init Error\n");
		return 0;
	}
	
	
	//scanf("%s", opt);
	while(opt[i] != '\0' || StackEmpty(s_opt) != TRUE)
	{
		if(opt[i] >= '0' && opt[i] <= '9')
		{
			tmp = tmp*10 + opt[i]-'0';
			i++;
			if(opt[i] < '0' || opt[i] > '9')
			{
				Push(&s_num, tmp);
				tmp = 0;
			}
		}
		else
		{
			if(opt[i] == ')' && GetTop(s_opt) == '(')
			{
				Pop(&s_opt);
				i++;
				continue;
			}
			
			if(StackEmpty(s_opt) == TRUE ||
			   (GetTop(s_opt) == '(' && opt[i] != ')') ||
			   (priority(opt[i]) > priority(GetTop(s_opt))) )
			{
				Push(&s_opt, opt[i]);
				i++;
				continue;
			}
			
			if((opt[i] == '\0' && StackEmpty(s_opt) != TRUE)||
			   (opt[i] == ')' && GetTop(s_opt) != '(') ||
			   ( priority(opt[i]) <= priority( GetTop(s_opt) ) ) )
			{
				switch(Pop(&s_opt))
				{
					case '+':
						num1 = Pop(&s_num);
						num2 = Pop(&s_num);
						Push(&s_num, num1+num2);
						break;
					case '-':
						num1 = Pop(&s_num);
						num2 = Pop(&s_num);
						Push(&s_num, num2-num1);
						break;
					case '*':
						num1 = Pop(&s_num);
						num2 = Pop(&s_num);
						Push(&s_num, num1*num2);
						break;
					case '/':
						num1 = Pop(&s_num);
						num2 = Pop(&s_num);
						Push(&s_num, num2/num1);
						break;
				}
			}
		}
	}
	result = GetTop(s_num);
	return result;
}




