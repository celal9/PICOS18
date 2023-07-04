#ifndef COMMON_H
#define COMMON_H

#include "device.h"

/***********************************************************************
 * ------------------------ Timer settings -----------------------------
 **********************************************************************/
#define _10MHZ	63320
#define _16MHZ	61768
#define _20MHZ	60768
#define _32MHZ	57768
#define _40MHZ 	55768

/***********************************************************************
 * ----------------------------- Events --------------------------------
 **********************************************************************/
#define ALARM_EVENT       0x80
#define STATUS_EVENT        0x40
#define LCD_EVENT         0x01
/***********************************************************************
 * ----------------------------- Task ID -------------------------------
 **********************************************************************/
/* Info about the tasks:
 * TASK0: USART
 * TASK1: USART
 */
#define TASK0_ID             1
#define TASK1_ID             2

/* Priorities of the tasks */
#define TASK0_PRIO           8
#define TASK1_PRIO           7
#define LCD_ID              5
#define ALARM_TSK0          0       /* Alarm ID (index) in tascdesc.c */
#define LCD_ALARM_ID        1       /* Alarm ID (index) in tascdesc.c */
#define LCD_PRIO            10
#define ALARM_TSK0           0

void getData();
void w();
void t();

#endif

/* End of File : common.h */
