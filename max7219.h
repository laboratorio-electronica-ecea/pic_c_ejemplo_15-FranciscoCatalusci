/*
 * File:   max7219.c
 * Author: Ing. Nahuel Espinosa
 *
 * Created on 31 de julio de 2018, 14:34
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MAX7219_H
#define MAX7219_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#define _XTAL_FREQ  4000000L

#define TRIS_SDO    TRISCbits.TRISC5
#define TRIS_SDI    TRISCbits.TRISC4
#define TRIS_SCK    TRISCbits.TRISC3

#define TRIS_SS1    TRISCbits.TRISC0
#define TRIS_SS2    TRISCbits.TRISC1
#define TRIS_SS3    TRISCbits.TRISC2
#define TRIS_SS4    TRISAbits.TRISA0
	
#define PIN_SS1	    PORTCbits.RC0
#define PIN_SS2	    PORTCbits.RC1
#define PIN_SS3	    PORTCbits.RC2
#define PIN_SS4	    PORTAbits.RA0

#define REG_NO_OP           0x00
#define REG_DIGIT_0         0x01
#define REG_DIGIT_1         0x02
#define REG_DIGIT_2         0x03
#define REG_DIGIT_3         0x04
#define REG_DIGIT_4         0x05
#define REG_DIGIT_5         0x06
#define REG_DIGIT_6         0x07
#define REG_DIGIT_7         0x08
#define REG_DECODE_MODE     0x09
#define REG_INTENSITY       0x0A
#define REG_SCAN_LIMIT      0x0B
#define REG_SHUTDOWN        0x0C
#define REG_DISPLAY_TEST    0x0F

#define MAX_DISPLAY_0       0
#define MAX_DISPLAY_1       1
#define MAX_DISPLAY_2       2
#define MAX_DISPLAY_3       3

void    max7219_config();

void    max7219_shutdown      (uint8_t addr, uint8_t state);
void    max7219_set_scan_limit(uint8_t addr, uint8_t limit);
void    max7219_set_intensity (uint8_t addr, uint8_t intensity);
void    max7219_clear_display (uint8_t addr);
void    max7219_set_led       (uint8_t addr, uint8_t row, uint8_t col, uint8_t state);
uint8_t max7219_get_led       (uint8_t addr, uint8_t row, uint8_t col);
void    max7219_set_row       (uint8_t addr, uint8_t row, uint8_t value);
uint8_t max7219_get_row       (uint8_t addr, uint8_t row);
void    max7219_set_column    (uint8_t addr, uint8_t col, uint8_t value);
uint8_t max7219_get_column    (uint8_t addr, uint8_t col);

#endif	/* MAX7219_H */