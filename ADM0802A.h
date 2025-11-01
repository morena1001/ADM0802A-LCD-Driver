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
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "stm32f3xx_hal.h" // Change this line to your stm32 mcu model

/*
 * MACROS
 */
#define PIN_PAIR(x, y) (#x#y)
#define CAT(x, ...) (x ## __VA_ARGS__)
#define PORT(x) (CAT (GPIO, x))
#define PIN(x) (CAT (GPIO_PIN_, x))

/*
 * GPIO PIN VARIABLES
 */

static GPIO_TypeDef* port_rw;
static GPIO_TypeDef* port_rs;
static GPIO_TypeDef* port_ca;
static GPIO_TypeDef* port_e;
static GPIO_TypeDef* port_db0;
static GPIO_TypeDef* port_db1;
static GPIO_TypeDef* port_db2;
static GPIO_TypeDef* port_db3;
static GPIO_TypeDef* port_db4;
static GPIO_TypeDef* port_db5;
static GPIO_TypeDef* port_db6;
static GPIO_TypeDef* port_db7;

static uint16_t pin_rw;
static uint16_t pin_rs;
static uint16_t pin_ca;
static uint16_t pin_e;
static uint16_t pin_db0;
static uint16_t pin_db1;
static uint16_t pin_db2;
static uint16_t pin_db3;
static uint16_t pin_db4;
static uint16_t pin_db5;
static uint16_t pin_db6;
static uint16_t pin_db7;

static bool inc_dec_ddram = 0;
static bool shift_display = 0;
static bool display_control = false;
static bool cursor_control = false;
static bool blink_control = false;
static bool bus_mode_8 = false;
static bool display_lines_2 = false;
static bool display_format_5x11 = false;

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

uint8_t ADM0802A_Init (char* rw_pair, char* rs_pair, char* ca_pair, char* e_pair, char* db0_pair, char* db1_pair, char* db2_pair, char* db3_pair, char* db4_pair, char* db5_pair, char* db6_pair, char* db7_pair);

/*
 * COMMAND FUNCTIONS
 */

void ADM0802A_CommandWrite (uint8_t command);

/*
 * DATA FUNCTIONS
 */

void ADM0802A_DataWrite (char character, bool upper_set);
//void ADM0802A_DataRead ()

/*
 * HELPER FUNCTIONS
 */

void ADM0802A_ClearDisplay ();
void ADM0802A_ReturnHome ();
void ADM0802A_CursorMove_Right ();
void ADM0802A_CursorMove_Left ();
void ADM0802A_DisplayShift_On ();
void ADM0802A_DisplayShift_Off ();
void ADM0802A_Display_On ();
void ADM0802A_Display_Off ();
void ADM0802A_Cursor_On ();
void ADM0802A_Cursor_Off ();
void ADM0802A_CursorBlink_On ();
void ADM0802A_CursorBlink_Off ();
void ADM0802A_ShiftPattern_CursorLeft_CounterDec ();
void ADM0802A_ShiftPattern_CursorRight_CounterInc ();
void ADM0802A_ShiftPattern_DisplayLeft ();
void ADM0802A_ShiftPattern_DisplayRight ();
void ADM0802A_Bus_8Bit ();
void ADM0802A_Bus_4Bit ();
void ADM0802A_Display_1Line ();
void ADM0802A_Display_2Line ();
void ADM0802A_Display_Format_5x8 ();
void ADM0802A_Display_Format_5x11 ();

#endif /* INC_ADM0802A_H_ */
