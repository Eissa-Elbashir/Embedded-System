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
    unsigned char ReadADCValueLowHigh(void);
    unsigned char ReadADCValueLowLow(void);
    
    
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
        while(TXSTAbits.TRMT == 0 );   
        TXREG = ReadADCValueHigh(); 
        while(TXSTAbits.TRMT == 0 );       
        TXREG = ReadADCValueLowHigh(); 
        while(TXSTAbits.TRMT == 0 );       
        TXREG = ReadADCValueLowLow(); 
        while(TXSTAbits.TRMT == 0 );
        TXREG = 0xA;        // Line feed character  (0000000000) 
        delay_1s();
	}
    
}
     
unsigned char ReadADCValueHigh(void)
{
    unsigned char Value;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1);
    Value = ADRESH + 0b00110000;
    return(Value);
}

unsigned char ReadADCValueLowHigh(void)
{
    unsigned char Shift;
    unsigned char Value;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1);  
    Shift = ADRESL >> 4;
    if (Shift >= 10)
    {
        Shift = Shift - 9;
        Value = Shift + 0b01000000;
    }
    else
    {
        Value = Shift + 0b00110000;
    }
    return(Value);
}

unsigned char ReadADCValueLowLow(void)
{
    unsigned char AND;
    unsigned char Value;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1);  
    AND = ADRESL & 0b00001111;
    if (AND >= 10)
    {
        AND = AND - 9;
        Value = AND + 0b01000000;
    }
    else
    {
        Value = AND + 0b00110000;
    }
    return(Value);
}

void delay_1s()
    {
        long counter;
        counter = 0;
        while(counter<50000)
            counter++;
    }
