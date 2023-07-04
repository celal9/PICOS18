#include "common.h"

char rcv_value;
/**********************************************************************
 * Function you want to call when an IT occurs.
 **********************************************************************/
  extern void AddOneTick(void);
/*extern void MyOwnISR(void); */
  void InterruptVectorL(void);
  void InterruptVectorH(void);

/**********************************************************************
 * General interrupt vector. Do not modify.
 **********************************************************************/
#pragma code IT_vector_low=0x18
void Interrupt_low_vec(void)
{
   _asm goto InterruptVectorL  _endasm
}
#pragma code

#pragma code IT_vector_high=0x08
void Interrupt_high_vec(void)
{
   _asm goto InterruptVectorH  _endasm
}
#pragma code

/**********************************************************************
 * General ISR router. Complete the function core with the if or switch
 * case you need to jump to the function dedicated to the occuring IT.
 * .tmpdata and MATH_DATA are saved automaticaly with C18 v3.
 **********************************************************************/
extern int start;
extern int waitCount;
extern int tossCount;
extern int cookCount;
extern int slow_cookCount;
extern int receive_count;
extern int capacity;
extern int received;
extern int wait;
extern int toss;
extern int cook;
extern int slow_cook;
extern char response[21];
extern char wait_command[3];
extern char toss_command[4];
extern char cook_command[6];
extern char slow_cook_command[5];

#pragma	code _INTERRUPT_VECTORL = 0x003000
#pragma interruptlow InterruptVectorL
void InterruptVectorL(void)
{
	EnterISR();
	
	if (INTCONbits.TMR0IF == 1)
		AddOneTick();
	/* Here are the other interrupts you would desire to manage */
	if (PIR1bits.TXIF == 1) {
        if(wait==1){
            if(waitCount<2){
                waitCount++;
                TXREG= wait_command[waitCount];
            }
            else{
                wait=0;
                waitCount=0;
                SetEvent(TASK1_ID, STATUS_EVENT);
            }
        }
        else if(toss==1){
            if(tossCount<3){
                tossCount++;
                TXREG= toss_command[tossCount];
            }
            else{
                toss=0;
                tossCount=0;
            }
        }
        else if(cook==1){
            if(cookCount<5){
                cookCount++;
                TXREG= cook_command[cookCount];
            }
            else{
                cook=0;
                cookCount=0;
            }
        }
        else if(slow_cook==1){
            if(slow_cookCount<5){
                slow_cookCount++;
                TXREG= slow_cook_command[slow_cookCount];
            }
            else{
                slow_cook=0;
                slow_cookCount=0;
            }
        }
	}
	if (PIR1bits.RCIF == 1) {
        // receiving is the same for both picsim and real life.
        getData();
        PIR1bits.RCIF = 0;
      
	}
        if (RCSTAbits.OERR)
        {
          RCSTAbits.CREN = 0;
          RCSTAbits.CREN = 1;
        }
	LeaveISR();
}
#pragma	code

/* BE CARREFULL : ONLY BSR, WREG AND STATUS REGISTERS ARE SAVED  */
/* DO NOT CALL ANY FUNCTION AND USE PLEASE VERY SIMPLE CODE LIKE */
/* VARIABLE OR FLAG SETTINGS. CHECK THE ASM CODE PRODUCED BY C18 */
/* IN THE LST FILE.                                              */
#pragma	code _INTERRUPT_VECTORH = 0x003300
#pragma interrupt InterruptVectorH nosave=FSR0, TBLPTRL, TBLPTRH, TBLPTRU, TABLAT, PCLATH, PCLATU, PROD, section(".tmpdata"), section("MATH_DATA")
void InterruptVectorH(void)
{
  if (INTCONbits.INT0IF == 1)
    INTCONbits.INT0IF = 0;
}
#pragma	code



extern void _startup (void);
#pragma code _RESET_INTERRUPT_VECTOR = 0x003400
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code


/* End of file : int.c */
