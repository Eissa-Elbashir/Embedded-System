// Lab 2, seven segment display
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
    void delay_1s(void);
    void Display(unsigned char);
	OSCCONbits.SCS0=0; 		//set oscillator to primary (external)
	OSCCONbits.SCS1=0;
	TRISA = 0b00110011;		//Set port input output directions
	TRISB = 0b11000100;
	ADCON1 = 0b11111100;	//All bits digital I/O except AN0 and AN1
	PORTA=0xFF;			//Turn off seven-segment display
	PORTB=0xFF;			//Note LED?s active low ie turned on with logic 0
	while(1)			//Loop forever
	{
        unsigned char Count;
		delay_1s();
        Display(Count);
        Count++;
        if(Count>15) Count=0;
	}
    
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
    
    




void delay_1s()
    {
        long counter;
        counter = 0;
        while(counter<100000)
            counter++;
    }