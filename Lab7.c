// Lab 7, Interrupts
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
void __interrupt(high_priority) High_isr(void)
{
    char Temp;
    Temp = PORTB;       //clear mismatch (ie port change) condition
    INTCONbits.RBIF = 0;        // clear interrupt from RB7 change 
    PORTAbits.RA2 = ~ PORTAbits.RA2;      // Toggle RA2 every interrupt
}

void __interrupt(low_priority) low_isr(void)
{

}

void main (void)
{
    void delay_1s(void);
    OSCCONbits.SCS0 = 0;
    OSCCONbits.SCS1 = 0;
    
    TRISA = 0b00110011;		//Set port input output directions
	TRISB = 0b11000100;
    
	ADCON1 = 0b11111100;	//All bits digital I/O except AN0 and AN1
   
    RCON = 0b00000000;      //disable interrupt priorities
    INTCON = 0b00001000;    //peripheral disable Port B interrupt on change enable
    INTCON2 = 0b00000001;   //pull ups enable interrupt on change high priority 
            
    PORTA=0xFF;             //Turn off seven segment display
    PORTB=0xFF;             //Note LED?s active low ie turned on with logic 0
    PORTAbits.RA2 = 0;
    
    INTCONbits.GIE = 1;     //enable interrupt 
    
    while(1)
    {
        delay_1s();
        PORTBbits.RB1 = ~ PORTBbits.RB1;      //Toggle segment d
    }   
}

void delay_1s()
    {
        long counter;
        counter = 0;
        while(counter<100000)
            counter++;
    }