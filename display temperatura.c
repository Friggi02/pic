/*Il programma legge in input un byte sulla porta A che rapresenta un valore di tensione che a sua volta
rappresenta una temperatura. Viene calcolata la tensione e successivamente la temperatura in gradi celsius.
Questo dato viene mostrato tramite due display a sette segmenti collegati alle porte C e D.*/


// Configuration Bit Settings
#pragma config FOSC   = INTRC_NOCLKOUT     // Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE   = OFF                // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE  = OFF                // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE  = ON                 // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP     = OFF                // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD    = OFF                // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN  = OFF                // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO   = OFF                // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN  = OFF                // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP    = OFF                // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
#pragma config BOR4V  = BOR40V             // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT    = OFF                // Flash Program Memory Self Write Enable bits (Write protection off)

// Libraries selection
#include <xc.h>
#include <stdint.h>
#include <stdbool.h>
#include <pic.h>

// Clock definition
#define _XTAL_FREQ 4000000

// Function definition
void inline init_device();
void segdisp();

// Variable definition
uint8_t dato_decimale, byte_input, x, y, displayinput, displayoutput, temperaturaint;
float tensione, temperaturafloat;

void main(){

	init_device();
		
	while(1){   
		byte_input = PORTA;
		dato_decimale = byte_input;
		tensione = (2.53*2/256)*dato_decimale;
		temperaturafloat = ((tensione/8.125)-0.2153846154)/0.01;
				  
		temperaturaint = temperaturafloat;
		
		x = temperaturaint/10;
		y = temperaturaint%10;

		displayinput = x;
		segdisp(displayinput);
		PORTC = displayoutput;
		
		displayinput = y;
		segdisp(displayinput);
		PORTD = displayoutput;
	}

	return 0;
}

void inline init_device(){
	 
	 TRISA = 0b11111111;
	 TRISB = 0b00000000;
	 TRISC = 0b00000000;
	 TRISD = 0b00000000;
	 TRISE = 0b00000000;
	 
	 PORTA = 0b00000000;
	 PORTB = 0b00000000;
	 PORTC = 0b00000000;
	 PORTD = 0b00000000;
	 PORTE = 0b00000000;
	 
	 ANSEL = 0b00000000;
	 ANSELH = 0b00000000;  
	 
	 TMR0 = 6;
	 
	 OPTION_REG = 0b01000100;
	 // bit 7 --- RBPU: PORTB Pull-up Enable bit
	 // bit 6 --- INTEDG: Interrupt Edge Select bit
	 // bit 5 --- T0CS: TMR0 Clock Source Select bit
	 // bit 4 --- T0SE: TMR0 Source Edge Select bit
	 // bit 3 --- PSA: Prescaler Assignment bit
	 // bit 2 --- PS2: Prescaler Rate Select bit 2
	 // bit 1 --- PS1: Prescaler Rate Select bit 1
	 // bit 0 --- PS0: Prescaler Rate Select bit 0
	 
	 INTCON = 0b00000000;    
	 // bit 7 --- GIE: Global Interrupt Enable bit
	 // bit 6 --- PEIE: Peripheral Interrupt Enable bit
	 // bit 5 --- T0IE: Timer0 Overflow Interrupt Enable bit
	 // bit 4 --- INTE: INT External Interrupt Enable bit (RB0)
	 // bit 3 --- RBIE: PORTB Change Interrupt Enable bit (4 bit più significativi di PORTB)
	 // bit 2 --- T0IF: Timer0 Overflow Interrupt Flag bit
	 // bit 1 --- INTF: INT External Interrupt Flag bit (RB0)
	 // bit 0 --- RBIF: PORTB Change Interrupt Flag bit (4 bit più significativi di PORTB)
}

void segdisp(displayinput){
	displayoutput = 0;
	if(displayinput==0){
		displayoutput = 0b00111111;
	}else if(displayinput==1){
		displayoutput = 0b00000110;
	}else if(displayinput==2){
		displayoutput = 0b01011011;
	}else if(displayinput==3){
		displayoutput = 0b01001111;
	}else if(displayinput==4){
		displayoutput = 0b01100110;
	}else if(displayinput==5){
		displayoutput = 0b01101101;
	}else if(displayinput==6){
		displayoutput = 0b01111101;
	}else if(displayinput==7){
		displayoutput = 0b00000111;
	}else if(displayinput==8){
		displayoutput = 0b01111111;
	}else if(displayinput==9){
		displayoutput = 0b01100111;
	}
}