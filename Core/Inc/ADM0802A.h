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

#include <stdbool.h>

#include "stm32f3xx_hal.h"

/*
 * GPIO PIN NAMES
 */

#define Pin_RW GPIO_PIN_0
#define Port_RW GPIOA
#define Pin_RS GPIO_PIN_1
#define Port_RS GPIOA
#define Pin_CA GPIO_PIN_4
#define Port_CA GPIOA
#define Pin_E GPIO_PIN_5
#define Port_E GPIOA
#define Pin_DB0 GPIO_PIN_6
#define Port_DB0 GPIOA
#define Pin_DB1 GPIO_PIN_7
#define Port_DB1 GPIOA
#define Pin_DB2 GPIO_PIN_0
#define Port_DB2 GPIOB
#define Pin_DB3 GPIO_PIN_1
#define Port_DB3 GPIOB
#define Pin_DB4 GPIO_PIN_2
#define Port_DB4 GPIOB
#define Pin_DB5 GPIO_PIN_10
#define Port_DB5 GPIOB
#define Pin_DB6 GPIO_PIN_4
#define Port_DB6 GPIOC
#define Pin_DB7 GPIO_PIN_5
#define Port_DB7 GPIOC

/*
 * COMMAND SHORTCUTS
 */

#define ADM0802A_COMMAND_CLEAR_DISPLAY 					 0x01
#define ADM0802A_COMMAND_RETURN_HOME 					 0x02
#define ADM0802A_COMMAND_ENTRY_MODE(ID, SH)				(0x04 | ((ID != 0) << 1) | (SH != 0))
#define ADM0802A_COMMAND_DISPLAY_CONTROL(D, C, B)		(0x08 | ((D != 0) << 2) | ((C != 0) << 1) | (B != 0))
#define ADM0802_COMMAND_CURSOR_DISPLAY_SHIFT(SC, RL)	(0x10 | ((SC != 0) << 3) | ((RL != 0) << 2))
#define ADM0802A_COMMAND_FUNCTION_SET(DL, N, F)			(0x20 | ((DL != 0) << 4) | ((N != 0) << 3) | ((F != 0) << 2))
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

void ADM0802A_DataWrite (char character, bool upper_set);

#endif /* INC_ADM0802A_H_ */
