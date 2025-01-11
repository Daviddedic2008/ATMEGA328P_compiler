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