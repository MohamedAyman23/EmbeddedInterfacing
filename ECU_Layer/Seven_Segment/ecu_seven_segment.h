/* 
 * File:   ecu_seven_segment.h
 * Author: moham
 *
 * Created on September 14, 2023, 8:40 PM
 */

#ifndef ECU_SEVEN_SEGMENT_H
#define	ECU_SEVEN_SEGMENT_H

/* ---------- Section : Includes ---------- */
#include "ecu_seven_segment_cfg.h"
#include "../../MCAL_Layer/GPIO/hal_gpio.h"

/* ---------- MACRO Declarations ---------- */
#define SEGMENT_PIN0        0
#define SEGMENT_PIN1        1
#define SEGMENT_PIN2        2
#define SEGMENT_PIN3        3
/* ---------- MACROS FUNCTIONS Declarations ---------- */

/* ---------- Section DataTypes ----------*/
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;
typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;
/* ---------- Software Interfaces Declarations ---------- */
/**
 * @brief Fuction to intialize the pins of the seven segment
 * @param Seg pointer to the sturcture to intialize the seven segment
 * @param Number the value to be written on the decoder and the seven segment
 * @return E_OK : if the function has executed successfully 
 *         E_NOT_OK : if the function has and error
 */
Std_ReturnType seven_segment_intialize(const segment_t *seg);
/**
 * @brief Fuction to write the number of the seven segment
 * @param seg pointer to the sturcture to intialize the seven segment
 * @param number the value to be written on the decoder and the seven segment
 * @return E_OK : if the function has executed successfully 
 *         E_NOT_OK : if the function has and error 
 */
Std_ReturnType seven_segment_write_number(const segment_t *seg, uint8 number);
#endif	/* ECU_SEVEN_SEGMENT_H */

