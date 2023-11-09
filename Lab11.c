// Lab 11, Real time engine control 
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
void WriteTimer0(unsigned short);
unsigned short TimeBetwTeeth;
unsigned short Value;

void __interrupt(high_priority) High_isr(void)
{
    WriteTimer0(0);
    while(PORTBbits.RB7 == 1);
    Value = ((TMR0H << 8) | (TMR0L));
    TimeBetwTeeth = Value + Value + Value;
    INTCONbits.RBIF = 0;        // clear interrupt from RB7
}

void __interrupt(low_priority) low_isr(void)
{

}

void main (void)
{
    void delay_2ms(void);
    unsigned short ReadADCValue(void);
    unsigned short ADC_Reading;
    unsigned short Timer;
    unsigned short TimerValue;

    OSCCONbits.SCS0 = 0;
    OSCCONbits.SCS1 = 0;
    
    TRISA = 0b00110011;		//Set port input output directions
	TRISB = 0b11010100;
    
    ADCON0 = 0b00000001;    //connect ADC potentiometer to AN0
	ADCON1 = 0b11111100;	//All bits digital I/O except AN0 and AN1
    ADCON2 = 0b00100101;    //left justified, 8TAD, Fosc/16
   
    T0CON = 0b10001000;  //16 bit, disabled, no prescaler 
    
    RCON = 0b00000000;      //disable interrupt priorities
    INTCON = 0b00001000;    //peripheral disable Port B interrupt on change enable
    INTCON2 = 0b00000001;   //pull ups enable interrupt on change high priority 
            
    PORTA=0xFF;             //Turn off seven segment display
    PORTB=0xFF;             //Note LED?s active low ie turned on with logic 0
    
    INTCONbits.GIE = 1;     //enable interrupt 
    
    while(1)
    {
        if ( ( Timer = (TMR0H << 8) | (TMR0L) ) > TimeBetwTeeth)
            {
            ADC_Reading = ReadADCValue();
            if (ADC_Reading < 4)
                {
                TimerValue = ADC_Reading * Value;
                TimerValue = 65536 - TimerValue;
                WriteTimer0(TimerValue);
                while(INTCONbits.TMR0IF == 0);
                INTCONbits.TMR0IF = 0;
                }
            else
                {
                TimerValue = Value* 276;    //remaining of the circle 276;
                TimerValue = 65536 - TimerValue;
                WriteTimer0(TimerValue);
                while(INTCONbits.TMR0IF == 0);
                INTCONbits.TMR0IF = 0;
                ADC_Reading = ADC_Reading - 3;              
                TimerValue = ADC_Reading * Value;   
                TimerValue = 65536 - TimerValue;
                WriteTimer0(TimerValue);
                while(INTCONbits.TMR0IF == 0);
                INTCONbits.TMR0IF = 0;
                }
            //PORTAbits.RA2 = 0;
            PORTAbits.RA2 = ~ PORTAbits.RA2; 
            //delay_2ms();
            //PORTAbits.RA2 = 1;
            } 

    }   
}

unsigned short ReadADCValue(void)
    {
        unsigned short ADCValue;
        ADCON0bits.GO_DONE = 1;
        while(ADCON0bits.GO_DONE == 1);
        ADCValue = ADRESH >> 3;
        return(ADCValue);
    }

union Timers
       {
           unsigned int timer16bit;
           char timer8bit[2];
       };
       

void WriteTimer0(unsigned short timer0)
    {
        union Timers timer;

        timer.timer16bit = timer0;      // Copy timer value into union

        TMR0H = timer.timer8bit[1];     // Write high byte to Timer0
        TMR0L = timer.timer8bit[0];     // Write low byte to Timer0
    }

void delay_2ms()
    {
    char counter;
    counter = 0;
    while (counter <= 250)   
        counter++;
    }