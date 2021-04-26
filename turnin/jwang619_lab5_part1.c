/* Author: Jeffrey Wang jwang619@ucr.edu
 * Lab Section: 22
 * Assignment: Lab #5  Exercise #1
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link:
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
        DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	unsigned char fuelLevel = 0x00;
	unsigned char outC = 0x00;
    while (1) {
	outC = 0x00;
	fuelLevel = PINA & 0x0F;
	if(fuelLevel == 1 || fuelLevel == 2) {
		outC = 0x20;
	}
	else if (fuelLevel == 3 || fuelLevel == 4) {
		outC = 0x30;
	}
	else if (fuelLevel == 5 || fuelLevel == 6) {
		outC = 0x38;
	}
	else if (fuelLevel >= 7 && fuelLevel <= 9) {
                outC = 0x3C;
        }
	else if (fuelLevel >= 10 && fuelLevel <= 12) {
                outC = 0x3E;
        }
	else if (fuelLevel >= 13 && fuelLevel <= 15) {
                outC = 0x3F;
        }
	
	if(fuelLevel <= 4) {
		outC = outC | 0x40;
	}
	PORTC = outC;
	

    }
    return 0;
}
