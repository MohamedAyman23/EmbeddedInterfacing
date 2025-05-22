/* 
 * File:   ecu_layer_initialize.h
 * Author: moham
 *
 * Created on September 17, 2023, 11:34 AM
 */

#ifndef ECU_LAYER_INITIALIZE_H
#define	ECU_LAYER_INITIALIZE_H
/* ---------- Section : Includes ---------- */
#include "../MCAL_Layer/GPIO/hal_gpio.h"
#include "LED/ecu_led.h"
#include "BUTTON/ecu_button.h"
#include "Relay/ecu_relay.h"
#include "Dc_Motor/ecu_dc_motor.h"
#include "Seven_Segment/ecu_seven_segment.h"
#include "KeyPad/ecu_keypad.h"
#include "Chr_LCD/ecu_chr_lcd.h"

/* ---------- MACRO Declarations ---------- */

/* ---------- VARIABLE Declarations ---------- */

extern keypad_t keypad1;
extern chr_lcd_8bit_t lcd_2; 
extern chr_lcd_4bit_t lcd_1;
extern led_t led_1;
extern led_t led_2;
extern led_t led_3;
extern led_t led_4;
/* ---------- MACROS FUNCTIONS Declarations ---------- */

/* ---------- Section DataTypes ----------*/

/* ---------- Software Interfaces Declarations ---------- */
void Ecu_interfaces_initialize(void);

#endif	/* ECU_LAYER_INITIALIZE_H */

