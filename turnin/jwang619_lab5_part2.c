/* Author: Jeffrey Wang jwang619@ucr.edu
 * Lab Section: 22
 * Assignment: Lab #5  Exercise #2
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

enum SMStates {SMStart, Init, Wait, Inc, Reset, Dec, WaitInc, WaitReset, WaitDec} SMState;

void SMFunc() {
        unsigned char inputA = 0x00;
        unsigned char outputC = 0x00;

        outputC = PORTC;
        inputA = ~PINA;
        switch(SMState) {
                case SMStart:
                        SMState = Init;
                        break;
                case Init:
			if((inputA & 0x03) == 0x01) {
				SMState = Inc;
			}
			else if((inputA & 0x03) == 0x03) {
                                SMState = Reset;
                        }
			else if((inputA & 0x03) == 0x02) {
                                SMState = Dec;
                        }
			else {
				SMState = Wait;
			}
			break;
                case Wait:
                        if((inputA & 0x03) == 0x01) {
                                SMState = Inc;
                        }
                        if((inputA & 0x03) == 0x03) {
                                SMState = Reset;
                        }
                        if((inputA & 0x03) == 0x02) {
                                SMState = Dec;
                        }
                        break;
                case Inc:
                        SMState = WaitInc;
                        break;
                case Reset:
                        SMState = WaitReset;
                        break;
                case Dec:
                        SMState = WaitDec;
                        break;
		case WaitInc:
			if((inputA & 0x03) == 0x03) {
                                SMState = Reset;
                        }
			if((inputA & 0x03) == 0x02) {
                                SMState = Dec;
                        }	
                        if((inputA & 0x03) == 0x00) {
                                SMState = Wait;
                        }
			break;
		case WaitReset:
                        if((inputA & 0x03) == 0x01) {
                                SMState = Inc;
                        }
                        if((inputA & 0x03) == 0x02) {
                                SMState = Dec;
                        }
                        if((inputA & 0x03) == 0x00) {
                                SMState = Wait;
                        }
                        break;
		case WaitDec:
                        if((inputA & 0x03) == 0x03) {
                                SMState = Reset;
                        }
                        if((inputA & 0x03) == 0x01) {
                                SMState = Inc;
                        }
                        if((inputA & 0x03) == 0x00) {
                                SMState = Wait;
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
                        outputC = 0x07;
                        break;
                case Wait:
                        break;
                case Inc:
			if(outputC < 0x09) {
                                outputC = outputC + 1;
                        }
                        break;
                case Reset:
                        outputC = 0x00;
                        break;
                case Dec:
                        if(outputC > 0x00) {
                                outputC = outputC - 1;
                        }
                        break;
		case WaitInc:
			break;
		case WaitReset:
			break;
		case WaitDec:
			break;
                default:
                        break;
        }
        PORTC = outputC;
}

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRA = 0x00; PORTA = 0xFF; // Configure port A's 8 pins as inputs
        DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
        SMState = SMStart;

    while (1) {
        SMFunc();
    }
    return 0;
}
