/*
 * ADM0802A.c
 *
 *  Created on: Feb 22, 2025
 *      Author: josue
 */

#include "ADM0802A.h"

static uint8_t CharToEncoding (char character, bool upper_set);

/*
 * INITIALIZATION
 */

uint8_t ADM0802A_Init () {
	// Cursor to move right, DDRAM addr is increased by 1, and no display shift
	ADM0802A_CommandWrite (ADM0802A_COMMAND_ENTRY_MODE (1, 0));

	// Turn on display, cursor is enabled, and blink is enabled
	ADM0802A_CommandWrite (ADM0802A_COMMAND_DISPLAY_CONTROL (1, 1, 1));

	// Cursor and display shift are left off
	// 8-bit bus mode is used, 2-line display mode is used, and 5x8 dot display format is used
	ADM0802A_CommandWrite (ADM0802A_COMMAND_FUNCTION_SET (1, 1, 0));

	// Clear Display and return to home
	ADM0802A_CommandWrite (ADM0802A_COMMAND_CLEAR_DISPLAY);

	return 0;
}

/*
 * COMMAND FUNCTIONS
 */

void ADM0802A_CommandWrite (uint8_t command) {
	// Write the command to the data bus
	HAL_GPIO_WritePin (Port_DB0, Pin_DB0,  command & 0x01);
	HAL_GPIO_WritePin (Port_DB1, Pin_DB1, (command >> 1) & 0x01);
	HAL_GPIO_WritePin (Port_DB2, Pin_DB2, (command >> 2) & 0x01);
	HAL_GPIO_WritePin (Port_DB3, Pin_DB3, (command >> 3) & 0x01);
	HAL_GPIO_WritePin (Port_DB4, Pin_DB4, (command >> 4) & 0x01);
	HAL_GPIO_WritePin (Port_DB5, Pin_DB5, (command >> 5) & 0x01);
	HAL_GPIO_WritePin (Port_DB6, Pin_DB6, (command >> 6) & 0x01);
	HAL_GPIO_WritePin (Port_DB7, Pin_DB7, (command >> 7) & 0x01);

	// Toggle Enable pin to let device receive the information
	HAL_GPIO_WritePin (Port_E, Pin_E, GPIO_PIN_RESET);
	HAL_Delay (1);
	HAL_GPIO_WritePin (Port_E, Pin_E, GPIO_PIN_SET);
	HAL_Delay (1);
	HAL_GPIO_WritePin (Port_E, Pin_E, GPIO_PIN_RESET);

	// Delay to let instruction be executed according to Instruction table p.8
	if (command >> 7)			HAL_Delay (12);
	else if (command >> 6) 		HAL_Delay (12);
	else if (command >> 5) 		HAL_Delay (12);
	else if (command >> 4) 		HAL_Delay (12);
	else if (command >> 3) 		HAL_Delay (12);
	else if (command >> 2) 		HAL_Delay (12);
	else if (command >> 1) 		HAL_Delay (46);
	else						HAL_Delay (46);
}

/*
 * DATA FUNCTIONS
 */

void ADM0802A_DataWrite (char character, bool upper_set) {
	// Toggle RS pin to high to enable writing to RAM
	HAL_GPIO_WritePin (Port_RS, Pin_RS, GPIO_PIN_SET);

	// Translate the character into the encoding from p.9
	uint8_t value = CharToEncoding (character, 0);

	// Writ the value to the data bus
	HAL_GPIO_WritePin (Port_DB0, Pin_DB0,  value & 0x01);
	HAL_GPIO_WritePin (Port_DB1, Pin_DB1, (value >> 1) & 0x01);
	HAL_GPIO_WritePin (Port_DB2, Pin_DB2, (value >> 2) & 0x01);
	HAL_GPIO_WritePin (Port_DB3, Pin_DB3, (value >> 3) & 0x01);
	HAL_GPIO_WritePin (Port_DB4, Pin_DB4, (value >> 4) & 0x01);
	HAL_GPIO_WritePin (Port_DB5, Pin_DB5, (value >> 5) & 0x01);
	HAL_GPIO_WritePin (Port_DB6, Pin_DB6, (value >> 6) & 0x01);
	HAL_GPIO_WritePin (Port_DB7, Pin_DB7, (value >> 7) & 0x01);

	// Toggle Enable pin to let device receive the information
	HAL_GPIO_WritePin (Port_E, Pin_E, GPIO_PIN_RESET);
	HAL_Delay (1);
	HAL_GPIO_WritePin (Port_E, Pin_E, GPIO_PIN_SET);
	HAL_Delay (1);
	HAL_GPIO_WritePin (Port_E, Pin_E, GPIO_PIN_RESET);

	// Delay to let instruction be executed according to Instruction table p.8
	HAL_Delay (12);

	// Toggle RS pin to low
	HAL_GPIO_TogglePin (Port_RS, Pin_RS);
}

static inline uint8_t CharToEncoding (char character, bool upper_set) {
	return (upper_set) ? (0x80 | character) : (character);
}


