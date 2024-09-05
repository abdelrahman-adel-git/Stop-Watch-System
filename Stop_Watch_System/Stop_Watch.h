/*
 ============================================================================
 Name        : Stop_Watch.h
 Author      : Abd-Elrahman Adel
 Description : Stop Watch System Project
 Date        : 14/09/2023
 ============================================================================
 */

#ifndef STOP_WATCH_H_
#define STOP_WATCH_H_

/*======================================================LIBRARIES=====================================================*/

/*including the needed avr libraries*/
#include <avr/io.h>
#include <avr/interrupt.h>
/*====================================================================================================================*/

/*======================================================VARIABLES=====================================================*/

/*global variables for storing the values of each digit of the time*/
extern uint8_t hours_tens_digit, hours_ones_digit, minutes_tens_digit,
		minutes_ones_digit, seconds_tens_digit, seconds_ones_digit;
/*====================================================================================================================*/

/*========================================================MACROS======================================================*/

/*macro for displaying the multiplexed six 7-Segments*/
/*I am delaying for about 2 ms between displaying each 7-segment and another*/
#define display_time() {\
    PORTA = (PORTA & 0xC0) | (0x01);/*enable the 1st 7-segment only and disable the rest*/\
	PORTC = (PORTC & 0xF0) | (seconds_ones_digit & 0x0F);/*display the seconds ones digit*/\
	TIMER0_delay(2);\
	PORTA = (PORTA & 0xC0) | (0x02);/*enable the 2nd 7-segment only and disable the rest*/\
	PORTC = (PORTC & 0xF0) | (seconds_tens_digit & 0x0F);/*display the seconds tens digit*/\
	TIMER0_delay(2);\
	PORTA = (PORTA & 0xC0) | (0x04);/*enable the 3rd 7-segment only and disable the rest*/\
	PORTC = (PORTC & 0xF0) | (minutes_ones_digit & 0x0F);/*display the minutes ones digit*/\
	TIMER0_delay(2);\
	PORTA = (PORTA & 0xC0) | (0x08);/*enable the 4th 7-segment only and disable the rest*/\
	PORTC = (PORTC & 0xF0) | (minutes_tens_digit & 0x0F);/*display the minutes tens digit*/\
	TIMER0_delay(2);\
	PORTA = (PORTA & 0xC0) | (0x10);/*enable the 5th 7-segment only and disable the rest*/\
	PORTC = (PORTC & 0xF0) | (hours_ones_digit & 0x0F);/*display the hours ones digit*/\
	TIMER0_delay(2);\
	PORTA = (PORTA & 0xC0) | (0x20);/*enable the 6th 7-segment only and disable the rest*/\
	PORTC = (PORTC & 0xF0) | (hours_tens_digit & 0x0F);/*display the hours tens digit*/\
	TIMER0_delay(2);\
}
/*====================================================================================================================*/

/*======================================================FUNCTIONS=====================================================*/

void initialize_7447_decoder(void); /*function for initializing the 7447 decoder*/
void initialize_multiplexed_six_7Segments(void); /*function for initializing the six multiplexed 7-Segments*/
void TIMER0_delay(uint8_t time_ms); /*customized delay function*/
void TIMER1_CTC_Init(uint16_t ticks); /*function for initializing TIMER1*/
void INT0_Init(void); /*function for initializing EXTERNAL INT0*/
void INT1_Init(void); /*function for initializing EXTERNAL INT1*/
void INT2_Init(void); /*function for initializing EXTERNAL INT2*/
/*====================================================================================================================*/

#endif /* STOP_WATCH_H_ */
