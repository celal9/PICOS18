#include <p18f4620.h>

#include "common.h"
#include<stdlib.h>
#include<string.h>
/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/
int start=0;
int waitCount=0;
int wait=0;
int j;
int cus=0;
char customer;
char money_line[17] = "MONEY:";
char wait_command[3]= {'$','W',':'};
extern char response[21];
extern char string_pool[2][16];
unsigned char cing_line[17] = "C: ";
extern char response[21];
char money[5];
int monnnee=0;

/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/
void w(){
    wait=1;
    waitCount=0;
    TXREG= wait_command[waitCount];
}
/**********************************************************************
 * ------------------------------ TASK0 -------------------------------
 *
 **********************************************************************/
TASK(TASK0)
{
	SetRelAlarm(ALARM_TSK0, 10, 400);
    
	while(1) {
        WaitEvent(ALARM_EVENT);
        ClearEvent(ALARM_EVENT);
        
        if(response[1]== 'G'){
            start=1;
        }
        if(start==1){
            w();
            if(response[2]==0x00 && response[3]=='N' && response[4]=='N' && response[5]==0x00){
                cus++;
            }
            if(response[6]==0x00 && response[7]=='N' && response[8]=='N' && response[9]==0x00){
                cus++;
            }
            if(response[10]==0x00 && response[11]=='N' && response[12]=='N' && response[13]==0x00){
                cus++;
            }
            itoa(response[18], money);
            monnnee = strlen(money);
            for(j = 0; j < 5; j++)
                money_line[6+j]= ' ';
            for(j = 0; j < 5-monnnee; j++)
            money_line[11+j]='0';
            for(j = 0; j < monnnee; j++)
                money_line[16-monnnee+j]=money[j];
            j = 0;    
            if(3-cus==0)
                cing_line[j+3] = '0' ;
            if(3-cus==1)
                cing_line[j+3] = '1' ;
            if(3-cus==2)
                cing_line[j+3] = '2' ;
            if(3-cus==2)
                cing_line[j+3] = '3' ;
            cus=0;
            for(j = 0; j < 4; j++)
                cing_line[j+4] = ' ';
                cing_line[8] = 'I';
                cing_line[9] = 'N';
                cing_line[10] = 'G';
                cing_line[11] = ':';
            
            for(j = 0; j < 4; j++)
                cing_line[12+j] = response[j+14];
            ClearLCDScreen();
            LcdPrintString(money_line,0,0);
            LcdPrintString(cing_line,0,1);
        }
        else{
            ClearLCDScreen();
            LcdPrintString(string_pool[0], 0, 0);
            LcdPrintString(string_pool[1], 0, 1);
        }
       
	}
	TerminateTask();
}



/* End of File : tsk_task0.c */
