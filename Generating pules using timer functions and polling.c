// Lab 8, Interrupts
#include	<xc.h>
// Configuration settings
#pragma config OSC=HS,FSCM=OFF,IESO=OFF
#pragma config PWRT=ON,BOR=OFF,BORV=45
#pragma config WDT=OFF
#pragma config MCLRE=ON
#pragma config STVR=OFF,LVP=OFF,DEBUG=OFF
#pragma config CP0=OFF,CP1=OFF
#pragma config CPB=OFF,CPD=OFF
#pragma config WRT0=OFF,WRT1=OFF
#pragma config WRTB=OFF,WRTC=OFF,WRTD=OFF
#pragma config EBTR0=OFF,EBTR1=OFF
#pragma config EBTRB=OFF

//========================================================



 main (void)
{
    void WriteTimer0(unsigned int);
    void delay_100ms(void);
    void delay_50ms(void);
    
    OSCCONbits.SCS0 = 0;
    OSCCONbits.SCS1 = 0;
    
    TRISA = 0b00110011;		//Set port input output directions
	TRISB = 0b11000100;
    
    T0CON = 0b10000101;  //16 bit, enabled, 64 prescale
	ADCON1 = 0b11111100;	//All bits digital I/O except AN0 and AN1
           
    PORTA=0xFF;             //Turn off seven segment display
    PORTB=0xFF;             //Note LED?s active low ie turned on with logic 0
  
    while(1)
    {
        PORTAbits.RA2 = 0;
        WriteTimer0(61536); //4000
        while(INTCONbits.TMR0IF == 0);  //TMR0IF overflow interrupt flag
        INTCONbits.TMR0IF = 0;
        PORTAbits.RA2 = 1;
        WriteTimer0(63536); //2000
        while(INTCONbits.TMR0IF == 0);  //TMR0IF overflow interrupt flag
        INTCONbits.TMR0IF = 0;       
    }   
}

 union Timers
       {
           unsigned int timer16bit;
           char timer8bit[2];
       };
       

void WriteTimer0(unsigned int timer0)
    {
        union Timers timer;

        timer.timer16bit = timer0;      // Copy timer value into union

        TMR0H = timer.timer8bit[1];     // Write high byte to Timer0
        TMR0L = timer.timer8bit[0];     // Write low byte to Timer0
    }
 
