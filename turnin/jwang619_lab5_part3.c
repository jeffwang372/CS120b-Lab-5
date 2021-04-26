/* Author: Jeffrey Wang jwang619@ucr.edu
 * Lab Section: 22
 * Assignment: Lab #5  Exercise #3
 * Exercise Description: [optional - include for your own benefit]
 *
 * I acknowledge all content contained herein, excluding template or example
 * code is my own original work.
 *
 *  Demo Link: https://drive.google.com/file/d/1hUasveRxuuCI38N0Cwld_du8wFg7aATD/view?usp=sharing
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum SMStates {SMStart, Init, Wait1, Light1, Wait2, Light2, Wait3, Light3} SMState;

void SMFunc() {
        unsigned char inputA = 0x00;
        unsigned char outputB = 0x00;

        outputB = PORTB;
        inputA = ~PINA;
        switch(SMState) {
                case SMStart:
                        SMState = Init;
                        break;
                case Init:
			SMState = Wait1;
			break;
                case Wait1:
                        if((inputA & 0x01) == 0x01) {
                                SMState = Light1;
                        }
                        break;
                case Light1:
                        if((inputA & 0x01) == 0x00) {
                                SMState = Wait2;
                        }
                        break;
                case Wait2:
                        if((inputA & 0x01) == 0x01) {
                                SMState = Light2;
                        }
                        break;
                case Light2:
                        if((inputA & 0x01) == 0x00) {
                                SMState = Wait3;
                        }
                        break;
		case Wait3:
			if((inputA & 0x01) == 0x01) {
                                SMState = Light3;
                        }
			break;
		case Light3:
                        if((inputA & 0x01) == 0x00) {
                                SMState = Wait1;
                        }
                        break;
                default:
                        SMState = SMStart;
                        break;

        }
        switch(SMState) {
                case SMStart:
                        break;
                case Init:
                        outputB = 0x00;
                        break;
                case Wait1:
                        break;
                case Light1:
			outputB = 0x1B;
                        break;
                case Wait2:
                        break;
                case Light2:
                        outputB = 0x39;
                        break;
		case Wait3:
			break;
		case Light3:
			outputB = 0x2C;
			break;
                default:
                        break;
        }
        PORTB = outputB;
}

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
        DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
        SMState = SMStart;

    while (1) {
        SMFunc();
    }
    return 0;
}
