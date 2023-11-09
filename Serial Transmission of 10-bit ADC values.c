// Lab 6, Serial Transmission of 10 bit ADC values
#include	<xc.h>
#include    <stdlib.h>
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
    unsigned char ReadADCValueHigh(void);
    unsigned char ReadADCValueLow(void);
    void itoa(int input, char * buffer, int radix);
    
	OSCCONbits.SCS0=0; 		//set oscillator to primary (external)
	OSCCONbits.SCS1=0;
    
	TRISA = 0b00110011;		//Set port input output directions
	TRISB = 0b11010100;
    
	ADCON1 = 0b11111100;	//All bits digital I/O except AN0 and AN1
    ADCON0 = 0b00000001;    //connect ADC potentiometer to AN0
    ADCON2 = 0b10100101;    //left justified, 8TAD, Fosc/16
    
    TXSTA =  0b10101110;
    RCSTA =  0b10000000;
    BAUDCTL = 0b01011000; 
    
    SPBRG = 3;
    SPBRGH = 1;
            
    PORTA=0xFF;	
    PORTB=0xFF;
    
	while(1)			//Loop forever
	{ 
        //while(TXSTAbits.TRMT == 0 );   
        //TXREG = ReadADCValueHigh(); 
        while(TXSTAbits.TRMT == 0 );
        char buffer[7];
        itoa(ReadADCValueLow(), buffer, 10);
        TXREG = buffer;
        //TXREG = ReadADCValueLow(); 
        while(TXSTAbits.TRMT == 0 );       
        TXREG = 0xA;        // Line feed character  (0000000000) 
        delay_1s();
	}
    
}
     
unsigned char ReadADCValueHigh(void)
{
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1);
    return(ADRESH);
}

unsigned char ReadADCValueLow(void)
{
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1);  
    return(ADRESL);
}

void delay_1s()
    {
        long counter;
        counter = 0;
        while(counter<50000)
            counter++;
    }
