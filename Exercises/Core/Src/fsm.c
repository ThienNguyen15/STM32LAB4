/*
 * fsm.c
 *
 *  Created on: Nov 9, 2023
 *      Author: thien
 */

#include "fsm.h"

extern ADC_HandleTypeDef hadc1;

extern UART_HandleTypeDef huart2;

uint8_t buffer_var;
uint8_t buffer[MAX_BUFFER];
char concatstr[MAX_BUFFER] = "";
uint8_t index_buffer = 0;
uint8_t buffer_flag = 0;

int state_cmd = INIT;
uint8_t cmd_flag = INIT;
int ADC_value = 0;

void command_parser_fsm()
{
    switch (state_cmd)
    {
    	case INIT:
			memset(concatstr, 0, sizeof(concatstr));
    		if (buffer_var == '!')
    		{
    			memset(concatstr, 0, sizeof(concatstr));
    			state_cmd = READING;
    		}
    		break;
    	case READING:
<<<<<<< HEAD
			if(buffer_var != '!' && buffer_var != '#')
			{
				strncat(concatstr, (char*)&buffer_var, 1);
			}
    		else if (buffer_var == '!')
    		{
				memset(concatstr, 0, sizeof(concatstr));
    		}
			else if(buffer_var == '#')
			{
				if(strcmp(concatstr, "RST") == 0)
				{
					cmd_flag = RST;
					setTimer1(1);
				}
				if(strcmp(concatstr, "OK") == 0)
					cmd_flag = OK;
			}
			break;
		default:
			break;
	}
=======
    		if (buffer_var != '!' && buffer_var != '#' && idx_check <= strlen(concatstr))
    		{
			strncat(concatstr, (char*)&buffer_var, 1);
    			idx_check++;
    		}
		else if(buffer_var == '#')
			state_cmd = CHECK;
		if(idx_check > strlen(concatstr))
		{
			memset(concatstr, 0, sizeof(concatstr));
			state_cmd = INIT;
		}
		break;
	case CHECK:
		if(strcmp(concatstr, "RST") == 0)
		{
			cmd_flag = RST;
			setTimer1(1);
		}
		if(strcmp(concatstr, "OK") == 0)
			cmd_flag = OK;
		memset(concatstr, 0, sizeof(concatstr));
		state_cmd = INIT;
		break;
	default:
		break;
    }
>>>>>>> 1298edf249e86d394866ed97022e85a1c1297064
}

void uart_communication_fsm()
{
	char str[50];
	switch(cmd_flag)
	{
		case RST:
			if(timer1_flag == 1)
			{
				ADC_value = HAL_ADC_GetValue(&hadc1);
				HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!ADC=%d#\r\n",ADC_value), 500);
				state_cmd = INIT;
				setTimer1(300);
			}
			break;
		case OK:
			ADC_value = 0;
			cmd_flag = INIT;
			break;
		default:
			break;
	}
}
