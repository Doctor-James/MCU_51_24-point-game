#ifndef SYSTEM_INIT_H
#define SYSTEM_INIT_H
#include "compiler_defs.h"
#include "C8051F020.h"
void Init_Device(void);
void Oscillator_Init();
void Port_IO_Init();
void Timer_Init();
void Interrupts_Init();
void Reset_Sources_Init();
#endif