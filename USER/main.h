#ifndef MAIN_H
#define MAIN_H
#include "system_init.h"
#include "keyboard.h"
#include "Lcd.h"
#include "calculate.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>

//¼üÅÌ
sbit KEY_CLK  = P3^7;
sbit KEY_DAT  = P3^6;

//LCD
sbit LCD_D0  = P2^0;
sbit LCD_D1  = P2^1;
sbit LCD_D2  = P2^2;
sbit LCD_D3  = P2^3;
sbit LCD_D4  = P2^4;
sbit LCD_D5  = P2^5;
sbit LCD_D6  = P2^6;
sbit LCD_D7  = P2^7;

sbit LCD_RS   = P3^0;
sbit LCD_RW  = P3^1;
sbit LCD_E    = P3^2;
sbit LCD_CS1  = P3^3;
sbit LCD_CS2  = P3^4;



void var_init();
void delay( int time_us);
#endif