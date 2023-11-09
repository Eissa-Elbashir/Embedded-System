// Lab 8, Generating Pulses Exercise 4
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
void WriteTimer0(unsigned int);
unsigned int ReadADCValue(void);
unsigned int ADC_Reading;

void __interrupt(high_priority) High_isr(void)
{
    char Temp;
    Temp = PORTB;       //clear mismatch (ie port change) condition
    int n = n++;
    if (n % 2 == 0)
        {
        WriteTimer0(ADC_Reading);
        INTCONbits.TMR0IF = 0;  //reset overflow
        PORTAbits.RA2 = 0;
        }
    else
        {
        WriteTimer0(ADC_Reading);
        INTCONbits.TMR0IF = 0;  //reset overflow
        PORTAbits.RA2 = 1; 
        }
}


void __interrupt(low_priority) low_isr(void)
{
   
}

void	main(void)
{   
	OSCCONbits.SCS0=0; 		//set oscillator to primary (external)
	OSCCONbits.SCS1=0;
    
	TRISA = 0b00110011;		//Set port input output directions
	TRISB = 0b11000100;
    
    T0CON = 0b10000101;  //16 bit, enabled, 64 prescale
        
    ADCON0 = 0b00000001;    //connect ADC potentiometer to AN0
	ADCON1 = 0b11111100;	//All bits digital I/O except AN0 and AN1
    ADCON2 = 0b00100101;    //left justified, 8TAD, Fosc/16
           
    PORTA=0xFF;             //Turn off seven segment display
    PORTB=0xFF;             //Note LED?s active low ie turned on with logic 0

    RCON = 0b00000000;      //disable interrupt priorities
    INTCON = 0b00100000;    //peripheral disable Port B interrupt on change enable
    INTCON2 = 0b00000100;   //pull ups enable interrupt on change high priority 
            
    PORTAbits.RA2 = 0;
    INTCONbits.GIE = 1;     //enable interrupt 

    
	while(1)			//Loop forever
	{
        ADC_Reading = ReadADCValue();
	}
    
}

unsigned int ReadADCValue(void)
{
    unsigned char Value;
    unsigned int TimerValue;
    ADCON0bits.GO_DONE = 1;
    while(ADCON0bits.GO_DONE == 1);
    Value = ADRESH;
    TimerValue = (Value * 114.8) + 9770;    //One High or Low equal to 0.25 to 1 second is 114.8
    TimerValue = 65536 - TimerValue;
    return(TimerValue);
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
