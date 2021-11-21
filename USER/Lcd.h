#ifndef LCD_H
#define LCD_H

void write_code(unsigned char c,unsigned char cs1, unsigned char cs2);
void write_data(unsigned char c,unsigned char cs1,unsigned char cs2);
void set_stratline(unsigned char line);
void set_adr(unsigned char x,unsigned char y);
void dis_on_off(unsigned char commnd);
void clear();
void display_32_left(unsigned char x,unsigned char y,unsigned char number[32]);
void display_32_right(unsigned char x,unsigned char y,unsigned char number[32]);
void LCD_Map(unsigned char number,unsigned char lcd[32]);
#endif