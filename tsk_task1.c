#include "common.h"

/**********************************************************************
 * ----------------------- GLOBAL VARIABLES ---------------------------
 **********************************************************************/
int i=14;
int do_one;
int not_found=0;
int start_toss=0;
int tossCount=0;
int cookCount=0;
int slow_cookCount=0;
int toss=0;
int cook=0;
int slow_cook=0;
int receive_count;
int received;
char response[21];
char toss_command[4]= {'$','T',0x00 ,':'};
char cook_command[6]= {'$','C',0x00, 'N', 'N' ,':'};
char slow_cook_command[5]= {'$','C',0x00, 0x00 ,':'};

/**********************************************************************
 * ----------------------- LOCAL FUNCTIONS ----------------------------
 **********************************************************************/

void getData()
{
    unsigned char rxbyte = RCREG;
    
    if (rxbyte == '$')
    {
        receive_count = 0;
    }

    response[receive_count] = rxbyte;
    receive_count++;

    if (rxbyte == ':')
    {
        received=1;
    }
}
void t(){
    toss=1;
    TXREG= toss_command[tossCount];
}
void c(){
    cook=1;
    TXREG= cook_command[cookCount];
}
void sc(){
    slow_cook=1;
    TXREG= slow_cook_command[slow_cookCount];
}

void toss_part(){
    if(start_toss==1){
        if(response[3] != response[14] && response[4] != response[14] && response[7] != response[14] && response[8] != response[14] && response[11] != response[14] && response[12] != response[14]){
                if(response[14] != 'C' ||response[14] != 'S'|| response[14] != 'N'){
                    toss_command[2]= 0x00;
                    t();
                }
            }
        else if(response[3] != response[15] && response[4] != response[15] && response[7] != response[15] && response[8] != response[15] && response[11] != response[15] && response[12] != response[15]){
                if(response[15] != 'C' ||response[15] != 'S'|| response[15] != 'N'){
                    toss_command[2]= 0x01;
                    t();
                }
            }
        else if(response[3] != response[16] && response[4] != response[16] && response[7] != response[16] && response[8] != response[16] && response[11] != response[16] && response[12] != response[16]){
                if(response[16] != 'C' ||response[16] != 'S'|| response[16] != 'N'){
                    toss_command[2]= 0x02;
                    t();
                }
            }
        else if(response[3] != response[17] && response[4] != response[17] && response[7] != response[17] && response[8] != response[17] && response[11] != response[17] && response[12] != response[17]){
                if(response[17] != 'C' ||response[17] != 'S'|| response[17] != 'N'){
                    toss_command[2]= 0x03;
                    t();
                }
            }
    }
}

int cook_part(char id, char i1, char i2){
    cook_command[2]= id;
    if((i1 != response[14] && i1 != response[15] && i1 != response[16] && i1 != response[17]) || (i2 != response[17] && i2 != response[16] && i2 != response[15] && i2 != response[14] && i2 != 'N')){
        return 1;
    }
    else{
        if(i1 == response[14]){
            cook_command[3]= 0x00;
        }
        else if(i1 == response[15]){
            cook_command[3]= 0x01;
        }
        else if(i1 == response[16]){
            cook_command[3]= 0x02;
        }
        else if(i1 == response[17]){
            cook_command[3]= 0x03;
        }
        
        if(i2 == response[14]){
            cook_command[4]= 0x00;
        }
        else if(i2 == response[15]){
            cook_command[4]= 0x01;
        }
        else if(i2 == response[16]){
            cook_command[4]= 0x02;
        }
        else if(i2 == response[17]){
            cook_command[4]= 0x03;
        }
        else if(i2 == 'N'){
            cook_command[4]= 'N';
        }
        c();
        return 0;
    }
}


/**********************************************************************
 * ------------------------------ TASK1 -------------------------------
 *
 **********************************************************************/

TASK(TASK1) 
{
	while(1) {
        WaitEvent(STATUS_EVENT);
        ClearEvent(STATUS_EVENT);
        if(response[20]== ':'){
            if(response[2]==0x01 && response[6]==0x02 && response[10]==0x03){
                start_toss=1;
            }
            if(start_toss==1){
                if(response[2]>0 && response[2]<255){
                    do_one=cook_part(response[2], response[3], response[4]);
                }
                if(response[6]>0 && response[6]<255 && do_one){
                    do_one = cook_part(response[6], response[7], response[8]);
                }
                if(response[10]>0 && response[10]<255 && do_one){
                    do_one = cook_part(response[10], response[11], response[12]);
                }
                if(do_one){
                    toss_part();
                }
                
            }
            
        }
	}
	TerminateTask();
}

/* End of File : tsk_task1.c */