#ifndef _SCHEDULE_H
#define _SCHEDULE_H

#include "board.h"

typedef struct _schedule{
	 uint16_t   cnt_1ms;
	 uint16_t   cnt_2ms;
	 uint16_t   cnt_5ms;
	 uint16_t   cnt_10ms;
	 uint16_t   cnt_20ms;
	 uint16_t   cnt_50ms;
}schedule;

void TDT_Loop_1000Hz(void); //1msִ��һ��
void TDT_Loop_500Hz(void);	//2msִ��һ��
void TDT_Loop_200Hz(void);	//5msִ��һ��
void TDT_Loop_100Hz(void);	//10msִ��һ��
void TDT_Loop_50Hz(void);	//20msִ��һ��
void TDT_Loop_20Hz(void);	//50msִ��һ��

void TDT_Loop(schedule* robotSchdule);
												
#endif
