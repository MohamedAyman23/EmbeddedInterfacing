/* 
 * File:   hal_gpio.h
 * Author: mohamed_ayman
 *
 * Created on August 21, 2023, 5:54 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H



/* Section : Includes */

#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../compiler.h"
#include "../device_config.h"

/* Section DataTypes */

typedef enum{
    pin0 = 0,
    pin1,
    pin2,
    pin3,
    pin4,
    pin5,
    pin6,
    pin7
}pin_index_t;
typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;
typedef enum{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;
typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;
typedef struct{
    uint8 port      :3;
    uint8 pin       :3;
    uint8 direction :1;
    uint8 logic     :1;
}pin_config_t;
/* MACRO Declarations */
#define PORT_PIN_MAX_NUM    8
#define PORT_MAX_NUM        5
#define PORT_MASK           0xFF

#define PORT_PIN_CONFIGURATION      CONFIG_ENABLE
#define PORT_CONFIGURATION          CONFIG_ENABLE
/* MACROS FUNCTIONS Declarations */
#define HWREG(__X)         (*(volatile uint8 *)(__X))
#define SET_BIT(REG, BIT_POSN)   ((REG) |= (BIT_MASK << (BIT_POSN)))
#define CLEAR_BIT(REG, BIT_POSN)   ((REG) &= ~(BIT_MASK << (BIT_POSN)))
#define TOGGLE_BIT(REG, BIT_POSN)   ((REG) ^= (BIT_MASK << (BIT_POSN)))
#define READ_BIT(REG, BIT_POSN)   (((REG) >> (BIT_POSN)) & BIT_MASK)
/* Functions Declarations */
Std_ReturnType gpio_pin_direction_initialize(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_git_direction_status(const pin_config_t *_pin_config, direction_t *dir_status);
Std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);
Std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);
Std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
Std_ReturnType gpio_pin_initialize(const pin_config_t *_pin_config);

Std_ReturnType gpio_port_direction_initialize(port_index_t port, uint8 direction);
Std_ReturnType gpio_port_git_direction_status(port_index_t port, uint8 *direction_status);
Std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
Std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* HAL_GPIO_H */

