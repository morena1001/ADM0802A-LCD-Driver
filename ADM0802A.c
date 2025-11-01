/*
 * ADM0802A.c
 *
 *  Created on: Feb 22, 2025
 *      Author: josue
 */

#include "ADM0802A.h"

static uint8_t CharToEncoding (char character, bool upper_set);
static GPIO_TypeDef* GetPort (char* port);
static uint16_t GetPin (char* pin);

/*
 * INITIALIZATION
 */

uint8_t ADM0802A_Init (char* rw_pair, char* rs_pair, char* ca_pair, char* e_pair, char* db0_pair, char* db1_pair, char* db2_pair, char* db3_pair, char* db4_pair, char* db5_pair, char* db6_pair, char* db7_pair) {
	char* pin = (char*) malloc (2 * sizeof (char));

	// Set rw pin
	strncpy (pin, rw_pair + 1, 2);
	port_rw = GetPort (rw_pair);
	pin_rw = GetPin (pin);

	// Set rs pin
	strncpy (pin, rs_pair + 1, 2);
	port_rs = GetPort (rs_pair);
	pin_rs = GetPin (pin);

	// Set ca pin
	strncpy (pin, ca_pair + 1, 2);
	port_ca = GetPort (ca_pair);
	pin_ca = GetPin (pin);

	// Set e pin
	strncpy (pin, e_pair + 1, 2);
	port_e = GetPort (e_pair);
	pin_e = GetPin (pin);

	// Set db0 pin
	strncpy (pin, db0_pair + 1, 2);
	port_db0 = GetPort (db0_pair);
	pin_db0 = GetPin (pin);

	// Set db1 pin
	strncpy (pin, db1_pair + 1, 2);
	port_db1 = GetPort (db1_pair);
	pin_db1 = GetPin (pin);

	// Set db2 pin
	strncpy (pin, db2_pair + 1, 2);
	port_db2 = GetPort (db2_pair);
	pin_db2 = GetPin (pin);

	// Set db3 pin
	strncpy (pin, db3_pair + 1, 2);
	port_db3 = GetPort (db3_pair);
	pin_db3 = GetPin (pin);

	// Set db4 pin
	strncpy (pin, db4_pair + 1, 2);
	port_db4 = GetPort (db4_pair);
	pin_db4 = GetPin (pin);

	// Set db5 pin
	strncpy (pin, db5_pair + 1, 2);
	port_db5 = GetPort (db5_pair);
	pin_db5 = GetPin (pin);

	// Set db6 pin
	strncpy (pin, db6_pair + 1, 2);
	port_db6 = GetPort (db6_pair);
	pin_db6 = GetPin (pin);

	// Set db7 pin
	strncpy (pin, db7_pair + 1, 2);
	port_db7 = GetPort (db7_pair);
	pin_db7 = GetPin (pin);


	// Cursor to move right, DDRAM addr is increased by 1, and no display shift
	ADM0802A_CursorMove_Right ();

	// Turn on display, cursor is enabled, and blink is enabled
	ADM0802A_Display_On ();
	ADM0802A_Cursor_On ();
	ADM0802A_CursorBlink_On ();

	// Cursor and display shift are left off
	// 8-bit bus mode is used, 2-line display mode is used, and 5x8 dot display format is used
	ADM0802A_Bus_8Bit ();
	ADM0802A_Display_2Line ();

	// Clear Display and return to home
	ADM0802A_ClearDisplay ();

	return 0;
}

/*
 * COMMAND FUNCTIONS
 */

void ADM0802A_CommandWrite (uint8_t command) {
	// Write the command to the data bus
	HAL_GPIO_WritePin (port_db0, pin_db0,  command & 0x01);
	HAL_GPIO_WritePin (port_db1, pin_db1, (command >> 1) & 0x01);
	HAL_GPIO_WritePin (port_db2, pin_db2, (command >> 2) & 0x01);
	HAL_GPIO_WritePin (port_db3, pin_db3, (command >> 3) & 0x01);
	HAL_GPIO_WritePin (port_db4, pin_db4, (command >> 4) & 0x01);
	HAL_GPIO_WritePin (port_db5, pin_db5, (command >> 5) & 0x01);
	HAL_GPIO_WritePin (port_db6, pin_db6, (command >> 6) & 0x01);
	HAL_GPIO_WritePin (port_db7, pin_db7, (command >> 7) & 0x01);

	// Toggle Enable pin to let device receive the information
	HAL_GPIO_WritePin (port_e, pin_e, GPIO_PIN_RESET);
	HAL_Delay (1);
	HAL_GPIO_WritePin (port_e, pin_e, GPIO_PIN_SET);
	HAL_Delay (1);
	HAL_GPIO_WritePin (port_e, pin_e, GPIO_PIN_RESET);

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
	HAL_GPIO_WritePin (port_rs, pin_rs, GPIO_PIN_SET);

	// Translate the character into the encoding from p.9
	uint8_t value = CharToEncoding (character, 0);

	// Writ the value to the data bus
	HAL_GPIO_WritePin (port_db0, pin_db0,  value & 0x01);
	HAL_GPIO_WritePin (port_db1, pin_db1, (value >> 1) & 0x01);
	HAL_GPIO_WritePin (port_db2, pin_db2, (value >> 2) & 0x01);
	HAL_GPIO_WritePin (port_db3, pin_db3, (value >> 3) & 0x01);
	HAL_GPIO_WritePin (port_db4, pin_db4, (value >> 4) & 0x01);
	HAL_GPIO_WritePin (port_db5, pin_db5, (value >> 5) & 0x01);
	HAL_GPIO_WritePin (port_db6, pin_db6, (value >> 6) & 0x01);
	HAL_GPIO_WritePin (port_db7, pin_db7, (value >> 7) & 0x01);

	// Toggle Enable pin to let device receive the information
	HAL_GPIO_WritePin (port_e, pin_e, GPIO_PIN_RESET);
	HAL_Delay (1);
	HAL_GPIO_WritePin (port_e, pin_e, GPIO_PIN_SET);
	HAL_Delay (1);
	HAL_GPIO_WritePin (port_e, pin_e, GPIO_PIN_RESET);

	// Delay to let instruction be executed according to Instruction table p.8
	HAL_Delay (12);

	// Toggle RS pin to low
	HAL_GPIO_TogglePin (port_rs, pin_rs);
}

/*
 * HELPER FUNCTIONS
 */
void ADM0802A_ClearDisplay () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_CLEAR_DISPLAY);
}

void ADM0802A_ReturnHome () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_RETURN_HOME);
}

void ADM0802A_CursorMove_Right () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_ENTRY_MODE(1, shift_display));
	inc_dec_ddram = 1;
}

void ADM0802A_CursorMove_Left () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_ENTRY_MODE(0, shift_display));
	inc_dec_ddram = 0;
}

void ADM0802A_DisplayShift_On () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_ENTRY_MODE(inc_dec_ddram, 1));
	shift_display = 1;
}

void ADM0802A_DisplayShift_Off () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_ENTRY_MODE(inc_dec_ddram, 0));
	shift_display = 0;
}

void ADM0802A_Display_On () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_DISPLAY_CONTROL (1, cursor_control, blink_control));
	display_control = true;
}

void ADM0802A_Display_Off () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_DISPLAY_CONTROL (0, cursor_control, blink_control));
	display_control = false;
}

void ADM0802A_Cursor_On () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_DISPLAY_CONTROL (display_control, 1, blink_control));
	cursor_control = true;
}

void ADM0802A_Cursor_Off () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_DISPLAY_CONTROL (display_control, 0, blink_control));
	cursor_control = false;
}

void ADM0802A_CursorBlink_On () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_DISPLAY_CONTROL (display_control, cursor_control, 1));
	blink_control = true;
}

void ADM0802A_CursorBlink_Off () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_DISPLAY_CONTROL (display_control, cursor_control, 0));
	blink_control = false;
}

void ADM0802A_ShiftPattern_CursorLeft_CounterDec () {
	ADM0802A_CommandWrite (ADM0802_COMMAND_CURSOR_DISPLAY_SHIFT(0, 0));
}

void ADM0802A_ShiftPattern_CursorRight_CounterInc () {
	ADM0802A_CommandWrite (ADM0802_COMMAND_CURSOR_DISPLAY_SHIFT(0, 1));
}

void ADM0802A_ShiftPattern_DisplayLeft () {
	ADM0802A_CommandWrite (ADM0802_COMMAND_CURSOR_DISPLAY_SHIFT(1, 0));
}

void ADM0802A_ShiftPattern_DisplayRight () {
	ADM0802A_CommandWrite (ADM0802_COMMAND_CURSOR_DISPLAY_SHIFT(1, 1));
}

void ADM0802A_Bus_8Bit () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_FUNCTION_SET (1, display_lines_2, display_format_5x11));
	bus_mode_8 = true;
}

void ADM0802A_Bus_4Bit () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_FUNCTION_SET (0, display_lines_2, display_format_5x11));
	bus_mode_8 = false;
}

void ADM0802A_Display_1Line () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_FUNCTION_SET (bus_mode_8, 0, display_format_5x11));
	display_lines_2 = false;
}

void ADM0802A_Display_2Line () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_FUNCTION_SET (bus_mode_8, 1, display_format_5x11));
	display_lines_2 = true;
}

void ADM0802A_Display_Format_5x8 () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_FUNCTION_SET (bus_mode_8, display_lines_2, 0));
	display_format_5x11 = false;
}

void ADM0802A_Display_Format_5x11 () {
	ADM0802A_CommandWrite (ADM0802A_COMMAND_FUNCTION_SET (bus_mode_8, display_lines_2, 1));
	display_format_5x11 = true;
}



static inline uint8_t CharToEncoding (char character, bool upper_set) {
	return (upper_set) ? (0x80 | character) : (character);
}

static GPIO_TypeDef* GetPort (char* port) {
	switch (toupper (*port)) {
		#ifdef GPIOA
			case 'A':	return PORT (A);
		#endif

		#ifdef GPIOB
			case 'B':	return PORT (B);
		#endif

		#ifdef GPIOC
			case 'C':	return PORT (C);
		#endif

		#ifdef GPIOD
			case 'D':	return PORT (D);
		#endif

		#ifdef GPIOE
			case 'E':	return PORT (E);
		#endif

		#ifdef GPIOF
			case 'F':	return PORT (F);
		#endif

		#ifdef GPIOG
			case 'G':	return PORT (G);
		#endif

		#ifdef GPIOH
			case 'H':	return PORT (H);
		#endif

		#ifdef GPIOI
			case 'I':	return PORT (I);
		#endif

		#ifdef GPIOJ
			case 'J':	return PORT (J);
		#endif

		#ifdef GPIOK
			case 'K':	return PORT (K);
		#endif

		#ifdef GPIOL
			case 'L':	return PORT (L);
		#endif

		#ifdef GPIOM
			case 'M':	return PORT (M);
		#endif

		#ifdef GPION
			case 'N':	return PORT (N);
		#endif

		#ifdef GPIOO
			case 'O':	return PORT (O);
		#endif

		#ifdef GPIOP
			case 'P':	return PORT (P);
		#endif

			default: 	return PORT (A);
	}
}

static uint16_t GetPin (char* pin) {
	switch (atoi (pin)) {
		#ifdef GPIO_PIN_0
			case 0:		return PIN (0);
		#endif

		#ifdef GPIO_PIN_1
			case 1:		return PIN (1);
		#endif

		#ifdef GPIO_PIN_2
			case 2:		return PIN (2);
		#endif

		#ifdef GPIO_PIN_3
			case 3:		return PIN (3);
		#endif

		#ifdef GPIO_PIN_4
			case 4:		return PIN (4);
		#endif

		#ifdef GPIO_PIN_5
			case 5:		return PIN (5);
		#endif

		#ifdef GPIO_PIN_6
			case 6:		return PIN (6);
		#endif

		#ifdef GPIO_PIN_7
			case 7:		return PIN (7);
		#endif

		#ifdef GPIO_PIN_8
			case 8:		return PIN (8);
		#endif

		#ifdef GPIO_PIN_9
			case 9:		return PIN (9);
		#endif

		#ifdef GPIO_PIN_10
			case 10:	return PIN (10);
		#endif

		#ifdef GPIO_PIN_11
			case 11:	return PIN (11);
		#endif

		#ifdef GPIO_PIN_12
			case 12:	return PIN (12);
		#endif

		#ifdef GPIO_PIN_13
			case 13:	return PIN (13);
		#endif

		#ifdef GPIO_PIN_14
			case 14:	return PIN (14);
		#endif

		#ifdef GPIO_PIN_15
			case 15:	return PIN (15);
		#endif

			default: 	return PIN (0);
	}
}
