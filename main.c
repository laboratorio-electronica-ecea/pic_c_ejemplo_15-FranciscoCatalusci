/*
 * Nombre del archivo:   main.c
 * Autor:
 *
 * Descripción: 
 *        Proyecto usando un display matricial con MAX7219.
 */

#include <xc.h>
#include <stdint.h>

#include "max7219.h"

/* ------------------------ Definiciones ------------------------------------ */
#define _XTAL_FREQ  4000000L    // Frecuencia de operación del cristal

#define LED_ON      1
#define LED_OFF     0

/* ------------------------ Definición de salidas --------------------------- */
#define PIN_LED1    PORTEbits.RE2
#define TRIS_LED1   TRISEbits.TRISE2

#define PIN_LED2    PORTEbits.RE1
#define TRIS_LED2   TRISEbits.TRISE1

#define PIN_LED3    PORTEbits.RE0
#define TRIS_LED3   TRISEbits.TRISE0

/* ------------------------ Definición de entradas -------------------------- */
#define PIN_TEC1    PORTBbits.RB0
#define TRIS_TEC1   TRISBbits.TRISB0

#define PIN_TEC2    PORTBbits.RB1
#define TRIS_TEC2   TRISBbits.TRISB1

/* ------------------------ Bits de configuración --------------------------- */
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits
//#pragma config FOSC = INTRC_NOCLKOUT // Oscillator Selection bits
#pragma config WDTE = OFF       // Watchdog Timer Enable bit
#pragma config PWRTE = OFF      // Power-up Timer Enable bit
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit
#pragma config CP = OFF         // Code Protection bit
#pragma config CPD = OFF        // Data Code Protection bit
#pragma config BOREN = OFF      // Brown Out Reset Selection bits
#pragma config IESO = OFF       // Internal External Switchover bit
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit
#pragma config LVP = OFF        // Low Voltage Programming Enable bit

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits

/* ------------------------ Prototipos de funciones ------------------------- */
void gpio_config();

/* ------------------------ Implementación de funciones --------------------- */
void main(void) {                       // Función principal
    gpio_config();                      // Inicializo las entradas y salidas

    PORTD = 0;
    PIN_LED1 = 0;                       // Apago el LED1
    
    max7219_config();
    max7219_shutdown(MAX_DISPLAY_0, 0);
    max7219_set_scan_limit(MAX_DISPLAY_0, 7);
    max7219_set_intensity (MAX_DISPLAY_0, 15);
    max7219_clear_display(MAX_DISPLAY_0);
    
    max7219_set_led(MAX_DISPLAY_0, 5, 5, LED_ON);
    
    while(1) {                          // Super loop
        // Ver este link: https://pbs.twimg.com/media/BafQje7CcAAN5en.jpg
        
        if( PIN_TEC1 == 0 ) {           // Espero que se presione la TEC1
            __delay_ms(40);             // Delay antirrebote
            
            PIN_LED1 = !PIN_LED1;       // Toggle LED1

            while( PIN_TEC1 == 0 );     // Espero que se suelte la TEC1
            __delay_ms(40);             // Delay antirrebote
        }
    }
    
    // NO DEBE LLEGAR NUNCA AQUÍ, debido a que este programa se ejecuta
    // directamente sobre un microcontrolador y no es llamado por un ningún
    // sistema operativo, como en el caso de un programa para PC.
    
    return;
}

void interrupt isr() {                  // Rutina de atención de interrupciones
    // Esta rutina debe ejecutarse rápidamente sin delays ni loops infinitos.
    // Recuerda colocar en 0 el flag que provocó la interrupción.
}

void gpio_config() {
    ANSEL = 0;                          // Configuro todas las entradas
    ANSELH = 0;                         // como digitales
    
    TRIS_TEC1 = 1;                      // Configuro la TEC1 como entrada
    TRIS_LED1 = 0;                      // Configuro el LED1 como salida
    
    TRISD = 0;
}
/* ------------------------ Fin de archivo ---------------------------------- */