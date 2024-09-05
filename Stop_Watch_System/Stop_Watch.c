/*
 ============================================================================
 Name        : Stop_Watch.c
 Author      : Abd-Elrahman Adel
 Description : Stop Watch System Project
 Date        : 14/09/2023
 ============================================================================
 */

#include "Stop_Watch.h"

/*defining the initial values of the stop watch time*/
/*you can change them if you want to check whether the time is being managed correctly or not */

/*the maximum time that can be reached by the stop watch is: 99:59:59*/
uint8_t hours_tens_digit = 0, hours_ones_digit = 0, minutes_tens_digit = 0,
		minutes_ones_digit = 0, seconds_tens_digit = 0, seconds_ones_digit = 0;
/*====================================================================================================================*/
void initialize_7447_decoder(void)
{
	DDRC |= 0x0F; /*(7447 decoder pins): setting the first 4 pins in PORTC as OUTPUT pins*/
	PORTC &= 0xF0; /*(7447 decoder pins): setting the initial value for the decoder to 0*/
}
/*====================================================================================================================*/

/*====================================================================================================================*/
void initialize_multiplexed_six_7Segments(void)
{
	DDRA |= 0x3F; /*(7Segments enable pins): setting the first 6 pins in PORTA as OUTPUT pins*/
	PORTA &= 0xC0; /*(7Segments enable pins): setting the initial values for the enable pins to zeros (turning them off)*/
}
/*====================================================================================================================*/

/*====================================================================================================================*/
void TIMER0_delay(uint8_t time_ms)
{
	TCNT0 = 0; /*setting timer initial value to 0*/
	OCR0 = time_ms; /*setting the compare value*/

	/*TIMER0 CONFIGURATION:
	 * 1. CTC Mode
	 * 2. clock = F_CPU/1024
	 */
	TCCR0 = (1 << FOC0) | (1 << WGM01) | (1 << CS02) | (1 << CS00);

	/*wait till the TIMER0 compare match occurs*/
	while (!(TIFR & (1 << OCF0)));

	TIFR |= (1 << OCF0); /*clear OCF0*/
	TCCR0 = 0; /*stop TIMER0*/
}
/*====================================================================================================================*/

/*====================================================================================================================*/
void TIMER1_CTC_Init(uint16_t ticks)
{
	TCNT1 = 0; /*setting timer initial value to 0*/
	OCR1A = ticks; /*setting the compare value*/

	/*TIMER1 CONFIGURATION:
	 * 1. CTC Mode
	 * 2. clock = F_CPU/64
	 */
	TCCR1A = (1 << FOC1A);
	TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);
	TIMSK |= (1 << OCIE1A); /*enable TIMER1 compare interrupt*/
	SREG |= (1 << 7); /*enable global interrupts in the microcontroller*/
}
/*====================================================================================================================*/

/*====================================================================================================================*/
/*In this interrupt service routine, I'm managing the time counting process with every compare match (every 1000 ms)*/
ISR(TIMER1_COMPA_vect)
{
	if (minutes_tens_digit == 5 && minutes_ones_digit == 9
			&& seconds_tens_digit == 5 && seconds_ones_digit == 9)
	{
		seconds_ones_digit = 0;
		seconds_tens_digit = 0;
		minutes_ones_digit = 0;
		minutes_tens_digit = 0;
		if (hours_tens_digit == 9 && hours_ones_digit == 9)
		{
			seconds_ones_digit = 0;
			seconds_tens_digit = 0;
			minutes_ones_digit = 0;
			minutes_tens_digit = 0;
			hours_ones_digit = 0;
			hours_tens_digit = 0;
		}
		else if (hours_ones_digit == 9)
		{
			hours_ones_digit = 0;
			hours_tens_digit++;
		}
		else
		{
			hours_ones_digit++;
		}
	}
	else if (seconds_tens_digit == 5 && seconds_ones_digit == 9)
	{
		seconds_ones_digit = 0;
		seconds_tens_digit = 0;
		if (minutes_tens_digit == 5 && minutes_ones_digit == 9)
		{

			minutes_ones_digit = 0;
			minutes_tens_digit = 0;

		}
		else if (minutes_ones_digit == 9)
		{
			minutes_ones_digit = 0;
			minutes_tens_digit++;
		}
		else
		{
			minutes_ones_digit++;
		}
	}
	else if (seconds_ones_digit == 9)
	{
		if (seconds_tens_digit == 5)
		{
			seconds_ones_digit = 0;
			seconds_tens_digit = 0;
		}
		else if (seconds_ones_digit == 9)
		{
			seconds_ones_digit = 0;
			seconds_tens_digit++;
		}
	}
	else
	{
		seconds_ones_digit++;
	}
}
/*====================================================================================================================*/

/*====================================================================================================================*/
void INT0_Init(void)
{
	DDRD &= 0xFB; /*setting the bit PD2 to INPUT pin*/
	PORTD |= 0x04; /*activating the internal pull up resistor*/
	MCUCR |= (1 << ISC01); /*trigger INT0 with the falling edge*/
	GICR |= (1 << INT0); /*enable external interrupt pin INT0*/
	SREG |= (1 << 7); /*enable global interrupts in the microcontroller*/
}
/*====================================================================================================================*/

/*====================================================================================================================*/
ISR(INT0_vect)
{
	/*reset the stop watch*/
	seconds_ones_digit = 0;
	seconds_tens_digit = 0;
	minutes_ones_digit = 0;
	minutes_tens_digit = 0;
	hours_ones_digit = 0;
	hours_tens_digit = 0;
}
/*====================================================================================================================*/

/*====================================================================================================================*/
void INT1_Init(void)
{
	DDRD &= 0xF7; /*setting the bit PD3 to INPUT pin*/
	MCUCR |= (1 << ISC11) | (1 << ISC10); /*trigger INT1 with the rising edge*/
	GICR |= (1 << INT1); /*enable external interrupt pin INT1*/
	SREG |= (1 << 7); /*enable global interrupts in the microcontroller*/
}
/*====================================================================================================================*/

/*====================================================================================================================*/
ISR(INT1_vect)
{
	/*stop TIMER1 by clearing the following 3 bits: CS12 , CS11 , CS10*/
	TCCR1B &= 0xF8;
}
/*====================================================================================================================*/

/*====================================================================================================================*/
void INT2_Init(void)
{
	DDRB &= 0xFB; /*setting the bit PB2 to INPUT pin*/
	PORTB |= 0x04; /*activating the internal pull up resistor*/
	MCUCSR &= ~(1 << ISC2); /*trigger INT2 with the falling edge*/
	GICR |= (1 << INT2); /*enable external interrupt pin INT2*/
	SREG |= (1 << 7); /*enable global interrupts in the microcontroller*/
}
/*====================================================================================================================*/

/*====================================================================================================================*/
ISR(INT2_vect)
{
	/*resume counting by selecting the same previous clock*: clock = F_CPU/64
	 * by setting the following bits: CS11 , CS10
	 */
	TCCR1B |= 0x03;
}
/*====================================================================================================================*/

