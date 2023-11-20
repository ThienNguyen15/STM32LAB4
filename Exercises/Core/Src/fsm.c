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
int cmd_flag = INIT;
int check_cmd = 0;
int ADC_value = 0;

void check_cmd_fnc()
{
	if(strcmp(concatstr, "RST") == 0)
	{
		cmd_flag = RST;
		setTimer1(1);
	}
	if(strcmp(concatstr, "OK") == 0)
		cmd_flag = OK;
}

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
				check_cmd = 1;
				cmd_flag = INIT1;
			}
			break;
		default:
			break;
	}
}

void uart_communication_fsm()
{
	char str[50];
	switch(cmd_flag)
	{
		case INIT1:
			if(check_cmd == 1)
			{
				check_cmd_fnc();
			}
			check_cmd = 0;
			break;
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
			cmd_flag = INIT1;
			break;
		default:
			break;
	}
}
