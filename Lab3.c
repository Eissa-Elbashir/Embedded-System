// Lab 3, ADC potentiometer
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
//const unsigned char ADC_CHANNEL0 = 0;
//========================================================
void	main(void)
{
    void delay(void);
    void Display(unsigned char);
    unsigned char ReadADCValue(void);
    void IntialiseADC(unsigned char);
    unsigned char ADC_Reading;
    
	OSCCONbits.SCS0=0; 		//set oscillator to primary (external)
	OSCCONbits.SCS1=0;
    
	TRISA = 0b00110011;		//Set port input output directions
	TRISB = 0b11000100;
	ADCON1 = 0b11111100;	//All bits digital I/O except AN0 and AN1
    
    ADCON0 = 0b00000001;    //connect ADC potentiometer to AN0
    ADCON2 = 0b00100101;    //left justified, 8TAD, Fosc/16
    
    //InitialiseADC(ADC_CHANNEL0);
    
	while(1)			//Loop forever
	{
        ADC_Reading = ReadADCValue();
        Display(ADC_Reading);
	}
    
}


//void InitialiseADC(unsigned char ChannelNumber)
//{

//}


unsigned char ReadADCValue(void)
{
    unsigned char Value;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1);
    Value = ADRESH >> 4;                // shift ADRESH 4 bits to the right 
    return(Value);
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
        default:
            LATB=0b00010000;
            LATA=0b00000000;
            break;
    }
}
