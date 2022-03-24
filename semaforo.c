/*Il programma comanda due coppie di semafori e un attraversamento pedonale se premuto l'apposito pulsante.*/  

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
void time(int a);

//void __interrupt() isr(void); ---- se la verione di xc8 è successiva a 2.0
//void interrupt isr();         ---- se la verione di xc8 è precedente a 2.0
void __interrupt() isr(void);

// Variable definition
int a, i;

void main(){

    init_device();
      
    while(1){
        PORTA = 0b10000110;
        PORTC = 0b00000000;
        time(15);
        PORTA = 0b01000101;
        PORTC = 0b00000000;
        time(7);
        PORTA = 0b00101000;
        PORTC = 0b00000001;
        time(3);
        PORTA = 0b00110000;
        PORTC = 0b00000001;
        time(15);
        PORTA = 0b00101000;
        PORTC = 0b00000001;
        time(7);
        PORTA = 0b01000101;
        PORTC = 0b00000000;
        time(3);
    }
}

//void __interrupt()isr(){} ---- se la verione di xc8 è successiva a 2.0
//void interrupt isr(){}    ---- se la verione di xc8 è precedente a 2.0
void __interrupt()isr(){

    if(T0IF){
        T0IF=0;
    }
    
    if(INTF && RA4){   
        INTF=0;
        time(5);
        PORTA = 0b00101000;
        PORTC = 0b00000001;
        time(7);
        PORTA = 0b01000101;
        PORTC = 0b00000000;
        time(3);  
        PORTA = 0b10000110;
        PORTC = 0b00000000;
        time(15);
        PORTA = 0b01000101;
        PORTC = 0b00000000;
        time(7);
        PORTA = 0b00101000;
        PORTC = 0b00000001;
        time(3);
        PORTA = 0b00110000;
        PORTC = 0b00000001;   
    }else{
      INTF=0;  
    }
}    

void time(int a){
    for(i=0; i<=125*a; i++){   
        TMR0 = 6;
        while(!T0IF);
        T0IF = 0;  
    }
    i=0;
}

void inline init_device(){
    
    TRISA = 0b00000000;
    TRISB = 0b00000001;
    TRISC = 0b00000000;
    TRISD = 0b00000000;
    TRISE = 0b00000000;

    PORTA = 0b00000000;
    PORTB = 0b00000000;
    PORTC = 0b00000000;
    PORTD = 0b00000000;
    PORTE = 0b00000000;

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

    INTCON = 0b10110000;
    // bit 7 --- GIE: Global Interrupt Enable bit
    // bit 6 --- PEIE: Peripheral Interrupt Enable bit
    // bit 5 --- T0IE: Timer0 Overflow Interrupt Enable bit
    // bit 4 --- INTE: INT External Interrupt Enable bit
    // bit 3 --- RBIE: PORTB Change Interrupt Enable bit
    // bit 2 --- T0IF: Timer0 Overflow Interrupt Flag bit
    // bit 1 --- INTF: INT External Interrupt Flag bit
    // bit 0 --- RBIF: PORTB Change Interrupt Flag bit

    ANSEL = 0b00000000;
    // bit 7 --- Analog select AN7 RE2
    // bit 6 --- Analog select AN6 RE1
    // bit 5 --- Analog select AN5 RE0
    // bit 4 --- Analog select AN4 RA5
    // bit 3 --- Analog select AN3 RA3
    // bit 2 --- Analog select AN2 RA2
    // bit 1 --- Analog select AN1 RA1
    // bit 0 --- Analog select AN0 RA0
    
    ANSELH = 0b00000000;
    // bit 7 --- Not used (0)
    // bit 6 --- Not used (0)
    // bit 5 --- Analog select AN13 RB5
    // bit 4 --- Analog select AN12 RB0
    // bit 3 --- Analog select AN11 RB4
    // bit 2 --- Analog select AN10 RB1
    // bit 1 --- Analog select AN9 RB3
    // bit 0 --- Analog select AN8 RB2

    ADCON0 = 0b00000000;
    // bit 7 --- ADCS1: Conversion clock select bit
    // bit 6 --- ADCS0: Conversion clock select bit
    // bit 5 --- CHS3: Analog channel select bit
    // bit 4 --- CHS2: Analog channel select bit
    // bit 3 --- CHS1: Analog channel select bit
    // bit 2 --- CHS0: Analog channel select bit
    // bit 1 --- GO/DONE: Conversion status bit (1 conversion in progress)
    // bit 0 --- ADON: adc enable bit
    
    ADCON1 = 0b00000000;
    // bit 7 --- ADFM: conversion result format (1 right justified)
    // bit 6 --- Not used (0)
    // bit 5 --- VCFG1: Vref
    // bit 4 --- VCFG0: Vss
    // bit 3 --- Not used (0)
    // bit 2 --- Not used (0)
    // bit 1 --- Not used (0)
    // bit 0 --- Not used (0)  
}