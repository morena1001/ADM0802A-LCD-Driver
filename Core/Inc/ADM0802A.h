/*
 * ADM0802A.h
 *
 *  Created on: Feb 22, 2025
 *      Author: josue
 *
 *  Based of "ADM0802A-FSY-YBS-3.3V.doc" From cdn.sparkfun.com
 *  https://cdn.sparkfun.com/datasheets/LCD/Monochrome/ADM0802A-FSY-YBS-3.3V.pdf
 */

#ifndef INC_ADM0802A_H_
#define INC_ADM0802A_H_

#include "stm32f3xx_hal.h"

/*
 * COMMAND SHORTCUTS
 */

#define ADM0802A_COMMAND_CLEAR_DISPLAY 					0x01
#define ADM0802A_COMMAND_RETURN_HOME 					0x02
#define ADM0802A_COMMAND_ENTRY_MODE(ID, SH) 			(0x04 | ((uint8_t (ID != 0)) << 1) | (uint8_t (SH != 0)))
#define ADM0802A_COMMAND_DISPLAY_CONTROL(D, C, B) 		(0x08 | ((uint8_t (D != 0)) << 2) | ((uint8_t (C != 0)) << 1) | (uint8_t (B != 0)))
#define ADM0802A_COMMAND_CURSOR_DISPLAY_SHIFT(SC, RL) 	(0x10 | ((uint8_t (SC != 0)) << 3) | ((uint8_t (RL != 0)) << 2))
#define ADM0802A_COMMAND_FUNCTION_SET(DL, N, F) 		(0x20 | ((uint8_t (DL != 0)) << 4) | ((uint8_t (N != 0)) << 3) | ((uint8_t (F != 0)) << 2))
#define ADM0802A_COMMAND_SET_CGRAM_ADDR(AC) 			(0x40 | (AC & 0x3F))
#define ADM0802A_COMMAND_SET_DDRAM_ADDR(AC) 			(0x80 | (AC & 0x7F)) // ONLY FROM 0x00 to 0x4F is in 1 line display mode, other from 0x00 to 0x27 for line 1 and 0x40 to 0x67 for line 2

/*
 * INITIALIZATION
 */

uint8_t ADM0802A_Init ();

/*
 * COMMAND FUNCTIONS
 */

void ADM0802A_CommandWrite (uint8_t command);

/*
 * DATA FUNCTIONS
 */

void AMD0802A_DataWrite (uint8_t value);

#endif /* INC_ADM0802A_H_ */
