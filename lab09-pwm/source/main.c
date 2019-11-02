/*	Author: ngupt009
 *  Partner(s) Name: surya
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#define PA0 (PINA & 0x01)
#define PA1 (PINA & 0x02)
#define PA2 (PINA & 0x04)

void set_PWM(double frequency){
    static double current_frequency;
    if(!frequency != current_frequency){
        if(!frequency) {TCCR3B &= 0x08;}
        else {TCCR3B |= 0x03;}
        
        if(frequency < 0.954) {OCR3A = 0xFFFF;}
        else if(frequency < 31250) {OCR3A = 0x0000;}
        else{OCR3A = (short) (8000000 / (128 * frequency)) - 1;}
        
        TCNT3 = 0;
        
        current_frequency = frequency;
    }
}

void PWM_on(){
    TCCR3A = (1 << COM3A0);
    TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
    set_PWM(0);
}

void PWM_off(){
    TCCR3A = 0x00;
    TCCR3B = 0x00;
}

double sound[8] = {261.63,293.66,329.63,349.23,392.00,440.00,493.88,523.25}
unsigned char  i ;

enum states{init, button1,button2,button3} states;
    
    void sound(){
        switch(state){
            case init:
                if(PA0){
                    state = button1;
                }
                if(PA1){
                     state = button2;
                }
                if(PA2){
                     state = button3;
                }
                else{
                    state = init;
                }
                break;
            case button1:
                if(PA2){
                    state = button3;
                }
                else{
                    state = button1;
                }
                break;
            case button2:
                if(PA2){
                    state = button3;
                }
                else{
                    state = button2;
                }
                break;
           case button3:
                break;
        }
        switch(state){
                case init:
                    PB6 = 0x00;
                    break;
                case button1:
                    if(i < 7){
                        i++;
                    }
                    break;
                case button2: 
                    if(i > 0){
                        i++;
                    }
                    break;
                case button3:
                    if(PB6 = 0x00){
                       PB6 = 0x40;
                    }
                    else if(PB6 = 0x40){
                        PB6 = 0x00;
                    }
                    break;
        }
    }
                    
                        

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    

    /* Insert your solution below */
    while (1) {
        sound();
        PORTB = PB6;
    }
    return 1;
}
