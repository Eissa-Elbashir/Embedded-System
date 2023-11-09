// Lab 10, Finding the missing Pulse
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
//unsigned char TimerValueLow;
//unsigned char TimerValueHigh;
unsigned short TimeBetwTeeth;

void __interrupt(high_priority) High_isr(void)
{
    unsigned short Value;
    WriteTimer0(0);
    while(PORTBbits.RB7 == 1);
    //TimerValueLow = TMR0L;
    //TimerValueHigh = TMR0H;
    Value = ((TMR0H << 8) | (TMR0L));
    TimeBetwTeeth = Value + Value + Value;
    INTCONbits.RBIF = 0;        // clear interrupt from RB7
}

void __interrupt(low_priority) low_isr(void)
{

}

void main (void)
{
    unsigned short Timer;
    //unsigned char ReadADCValueHighHigh(void);
    //unsigned char ReadADCValueHighLow(void);
    //unsigned char ReadADCValueLowHigh(void);
    //unsigned char ReadADCValueLowLow(void);

    OSCCONbits.SCS0 = 0;
    OSCCONbits.SCS1 = 0;
    
    TRISA = 0b00110011;		//Set port input output directions
	TRISB = 0b11010100;
    
	ADCON1 = 0b11111100;	//All bits digital I/O except AN0 and AN1
   
    T0CON = 0b10001000;  //16 bit, disabled, no prescaler 
    
    RCON = 0b00000000;      //disable interrupt priorities
    INTCON = 0b00001000;    //peripheral disable Port B interrupt on change enable
    INTCON2 = 0b00000001;   //pull ups enable interrupt on change high priority 
            
    PORTA=0xFF;             //Turn off seven segment display
    PORTB=0xFF;             //Note LED?s active low ie turned on with logic 0
    
    TXSTA =  0b10101110;
    RCSTA =  0b10000000;
    BAUDCTL = 0b01011000; 
    
    SPBRG = 3;
    SPBRGH = 1; 
    
    INTCONbits.GIE = 1;     //enable interrupt 
    
    while(1)
    {
        //if(PORTBbits.RB7 == 1);
        if ( PORTBbits.RB7 == 0 )
            {
            if ( ( Timer = (TMR0H << 8) | (TMR0L) ) > TimeBetwTeeth)
                {                
                PORTAbits.RA2 = ~ PORTAbits.RA2; 
                WriteTimer0(0);
                }
            /**
            while(TXSTAbits.TRMT == 0 );   
            TXREG = ReadADCValueHighHigh(); 
            while(TXSTAbits.TRMT == 0 );   
            TXREG = ReadADCValueHighLow(); 
            while(TXSTAbits.TRMT == 0 );       
            TXREG = ReadADCValueLowHigh(); 
            while(TXSTAbits.TRMT == 0 );       
            TXREG = ReadADCValueLowLow(); 
            while(TXSTAbits.TRMT == 0 );
            TXREG = 0xA;        // Line feed character  (0000000000) 
            if (PORTAbits.RA2 == 0)
                {
                while(TXSTAbits.TRMT == 0 );
                TXREG = 0b00110000; 
                }
            else
                {
                while(TXSTAbits.TRMT == 0 );
                TXREG = 0b00110001; 
                }
            TXREG = 0xA;        // Line feed character  (0000000000) 
             * */  
            }
    }   
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

/*
unsigned char ReadADCValueHighHigh(void)
{
    unsigned char Shift;
    unsigned char Value; 
    Shift = TimerValueHigh >> 4;
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

unsigned char ReadADCValueHighLow(void)
{
    unsigned char AND;
    unsigned char Value;
    AND = TimerValueHigh & 0b00001111;
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

unsigned char ReadADCValueLowHigh(void)
{
    unsigned char Shift;
    unsigned char Value;  
    Shift = TimerValueLow >> 4;
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
    AND = TimerValueLow & 0b00001111;
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
 
*/

