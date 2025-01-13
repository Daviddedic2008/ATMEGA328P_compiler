#pragma once

// mem sizes
#define FLASH_SIZE 2048
#define PROG_STORAGE 32768

// ports(digital)

// B
#define PORTB 0x25 // write
#define DDRB 0x24 // data direction for each pin
#define PINB 0x23 // read

// C
#define PORTC 0x28 // write
#define DDRC 0x27 // data direction for each pin
#define PINC 0x26 // read

// D
#define PORTD 0x2B // write
#define DDRD 0x2A // data direction for each pin
#define PIND 0x29 // read

// whats input vs output
#define INPUT_PIN 0
#define OUTPUT_PIN 0

// branching 
#define EQUAL 0
#define GREATER 1
#define LESS 2
#define NOT_EQUAL 3

// pointer regs
#define Z_LO 30
#define Z_HI 31
#define Z 0 // temp def

#define X_LO 26
#define X_HI 27
#define X 0 // temp def