/*
 * fsm.h
 *
 *  Created on: Nov 9, 2023
 *      Author: thien
 */

#ifndef INC_FSM_H_
#define INC_FSM_H_

#include "main.h"
#include "software_timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT		0

#define READING		1

#define RST			2

#define OK			3

#define INIT1		4

#define MAX_BUFFER	50

extern uint8_t buffer_var;

extern uint8_t buffer[MAX_BUFFER];

extern char concatstr[MAX_BUFFER];

extern uint8_t index_buffer;

extern uint8_t buffer_flag;

void check_cmd_fnc();

void command_parser_fsm();

void uart_communication_fsm();

#endif /* INC_FSM_H_ */
