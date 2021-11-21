#ifndef KEYBOARD_H
#define KEYBOARD_H
void Keyscan(unsigned char scannum);
void Keyscan_col(int row);
void set_24();
void KeyboardDriver();
void KeyboardMap(unsigned char i,unsigned char j);
void F1_start();
int key_1(unsigned char number,unsigned char number_col);
int key_2(unsigned char number,unsigned char number_col);
int key_3(unsigned char number,unsigned char number_col);
int key_4(unsigned char number,unsigned char number_col);
void key_12(unsigned char number,unsigned char number_col);
void key_13(unsigned char number,unsigned char number_col);
void key_14(unsigned char number,unsigned char number_col);
void key_15(unsigned char number,unsigned char number_col);
void key_16(unsigned char number,unsigned char number_col);
void key_17(unsigned char number,unsigned char number_col);
void key_11();
void key_F2();
int cal_main();
#endif