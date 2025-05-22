/* 
 * File:   ecu_led.h
 * Author: moham
 *
 * Created on August 21, 2023, 6:51 PM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H
/* Section : Includes */
#include "../../MCAL_Layer/GPIO/hal_gpio.h"
#include "ecu_led_cfg.h"
/* Section DataTypes */
typedef enum{
    LED_OFF,
    LED_ON
}led_stuaus_t;
typedef struct{
    uint8 port       : 4;
    uint8 pin        : 3;
    uint8 led_status : 1;
}led_t;
/* MACRO Declarations */

/* MACROS FUNCTIONS Declarations */

/* Functions Declarations */
Std_ReturnType led_intialize(const led_t *led);
Std_ReturnType led_turn_off(const led_t *led);
Std_ReturnType led_turn_on(const led_t *led);
Std_ReturnType led_toggle(const led_t *led);
#endif	/* ECU_LED_H */

