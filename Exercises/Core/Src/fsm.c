/*
 * fsm.c
 *
 *  Created on: Nov 9, 2023
 *      Author: thien
 */

#include "fsm.h"

void command_parser_fsm()
{
    switch(state_cmd)
    {
        case INIT:
            if (strcmp(buffer, "!RST#") == 0)
                state_cmd = RST;
            else if (strcmp(buffer, "!OK#") == 0)
                state_cmd = OK;
            else
                state_cmd = INVALID;
            break;
        case RST:
            cmd_flag = RST;
            break;
        case OK:
            cmd_flag = OK;
            break;
        case INVALID:
            state_cmd = INIT;
            break;
        default:
            break;
    }
    memset(buffer, 0, sizeof(buffer));
    index_buffer = 0;
}


void uart_communiation_fsm()
{
	char str[50];
	switch(state_cmd)
	{
		case RST:
			if(timer1_flag)
			{
				ADC_value = HAL_ADC_GetValue(&hadc1);
				HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "!ADC=%d#\r\n",ADC_value), 500);
				setTimer1(100);
			}
			break;
		case OK:
			ADC_value = -1;
			state_cmd = INIT;
			break;
		default:
			break;
	}
}
