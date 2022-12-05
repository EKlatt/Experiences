// https://briankhuu.com/blog/self/2015/07/05/understanding-more-about-avr-programming.html
// https://arduino.stackexchange.com/questions/56304/how-do-i-directly-access-a-memory-mapped-register-of-avr-with-c
// https://de.wikibooks.org/wiki/C-Programmierung_mit_AVR-GCC/_IO-Ports
// https://arbaranwal.github.io/tutorial/2017/06/23/atmega328-register-reference.html
// https://playground.arduino.cc/Code/BitMath/

//...\arduino-1.8.12\hardware\tools\avr\avr\include\avr\sfr_defs.h
// #define __SFR_OFFSET 0x20
// #define _MMIO_BYTE(mem_addr) (*(volatile uint8_t *)(mem_addr))
// #define _SFR_IO8(io_addr) _MMIO_BYTE((io_addr) + __SFR_OFFSET)

// ...\arduino-1.8.12\hardware\tools\avr\avr\include\avr\iom328p.h
// #define PIND _SFR_IO8(0x09)             // .equ PIND  = 0x09
// #define DDRD _SFR_IO8(0x0A)             // .equ DDRD  = 0x0a
// #define PORTD _SFR_IO8(0x0B)            // .equ PORTD = 0x0b

// https://www4.cs.fau.de/Lehre/SS19/V_SPIC/Vorlesung/Folien/14-MC.pdf
//#define PIND (*(volatile uint8_t *) 0x29 )                       // Port 0x09 and offset 0x20  
//#define DDRD (*(volatile uint8_t *) 0x2A )                       // Port 0x0A and offset 0x20 
//#define PORTD (*(volatile uint8_t *) 0x2B )                      // Port 0x0B and offset 0x20


