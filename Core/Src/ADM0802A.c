/*
 * ADM0802A.c
 *
 *  Created on: Feb 22, 2025
 *      Author: josue
 */

#include "ADM0802A.h"

/*
 * INITIALIZATION
 */

uint8_t ADM0802A_Init () {
	/*
	 * ADM0802A_COMMAND_ENTRY_MODE(ID, SH) 			(0x04 | ((uint8_t (ID != 0)) << 1) | (uint8_t (SH != 0)))
#define ADM0802A_COMMAND_DISPLAY_CONTROL(D, C, B) 		(0x08 | ((uint8_t (D != 0)) << 2) | ((uint8_t (C != 0)) << 1) | (uint8_t (B != 0)))
#define ADM0802A_COMMAND_CURSOR_DISPLAY_SHIFT(SC, RL) 	(0x10 | ((uint8_t (SC != 0)) << 3) | ((uint8_t (RL != 0)) << 2))
#define ADM0802A_COMMAND_FUNCTION_SET(DL, N, F) 		(0x20 | ((uint8_t (DL != 0)) << 4) | ((uint8_t (N != 0)) << 3) | ((uint8_t (F != 0)) << 2))
#define ADM0802A_COMMAND_SET_CGRAM_ADDR(AC) 			(0x40 | (AC & 0x3F))
#define ADM0802A_COMMAND_SET_DDRAM_ADDR(AC) 			(0x80 | (AC & 0x7F))
	 */
	ADM0802A_CommandWrite (ADM0802A_COMMAND_ENTRY_MODE(1, 0));

	return 0;
}

/*
 * COMMAND FUNCTIONS
 */

void ADM0802A_CommandWrite (uint8_t command) {

}

/*
 * DATA FUNCTIONS
 */

void AMD0802A_DataWrite (uint8_t value) {

}


