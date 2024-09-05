/*
 ============================================================================
 Name        : Stop_Watch_System.c
 Author      : Abd-Elrahman Adel
 Description : Stop Watch System Project
 Date        : 14/09/2023
 ============================================================================
 */
#include "Stop_Watch.h" /*include the stop watch system header file*/

int main(void)
{
	initialize_7447_decoder();
	initialize_multiplexed_six_7Segments();
	TIMER1_CTC_Init(15625); /*compare match every 1000 ms*/
	INT0_Init();
	INT1_Init();
	INT2_Init();
	for (;;)
	{
		display_time(); /*keep displaying the time non stop*/
	}
}
