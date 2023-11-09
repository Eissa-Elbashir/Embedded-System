// Lab 4, Polling Timer Counter 0
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
void	main(void)
{
    void Display(unsigned char);
    void WriteTimer0(unsigned int);
    unsigned char Count = 0;
    
	OSCCONbits.SCS0=0; 		//set oscillator to primary (external)
	OSCCONbits.SCS1=0;
    
	TRISA = 0b00110011;		//Set port input output directions
	TRISB = 0b11000100;
	ADCON1 = 0b11111100;	//All bits digital I/O except AN0 and AN1
	T0CON = 0b10000101;  
        
	while(1)			//Loop forever
	{ 
        WriteTimer0(26473);
        while(INTCONbits.TMR0IF == 0);  //TMR0IF overflow interrupt flag
        INTCONbits.TMR0IF = 0;
        Display(Count);
        Count++;
        if(Count>15) Count = 0;
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

    void Display(unsigned char HexDigit)
    {
        
        switch(HexDigit)
        {
            case 0:
                LATB=0b00010000;
                LATA=0b00000000;
                break;
            case 1:
                LATB=0b00111010;
                LATA=0b00000100;
                break;
            case 2:
                LATB=0b00100001;
                LATA=0b00000000;
                break;
            case 3:
                LATB=0b00101000;
                LATA=0b00000000;
                break;
            case 4:
                LATB=0b00001010;
                LATA=0b00000100;
                break;
            case 5:
                LATB=0b00001000;
                LATA=0b00001000;
                break;
            case 6:
                LATB=0b00000000;
                LATA=0b00001000;
                break;
            case 7:
                LATB=0b00111010;
                LATA=0b00000000;
                break;
            case 8:
                LATB=0b00000000;
                LATA=0b00000000;
                break;
            case 9:
                LATB=0b00001000;
                LATA=0b00000000;
                break;
            case 10:
                LATB=0b00000010;
                LATA=0b00000000;
                break;
            case 11:
                LATB=0b00000000;
                LATA=0b00001100;
                break;
            case 12:
                LATB=0b00010001;
                LATA=0b00001000;
                break;
            case 13:
                LATB=0b00100000;
                LATA=0b00000100;
                break;
            case 14:
                LATB=0b00000001;
                LATA=0b00001000;
                break;
            case 15:
                LATB=0b00000011;
                LATA=0b00001000;
                break;
        }
    }