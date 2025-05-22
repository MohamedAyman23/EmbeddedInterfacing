/* 
 * File:   application.c
 * Author: Mohammed
 *
 * Created on August 21, 2023, 3:26 PM
 */

#include "application.h"
#include "MCAL_Layer/EEPROM/hal_eeprom.h"
Std_ReturnType ret = E_NOT_OK;
volatile uint8 program_counter =0;
void INT0_App_ISR(void){
    program_counter++;
    if(3 == program_counter)
    {
        program_counter =0;
    }else{/* Nothing */}
    ret = Data_EEPROM_WriteByte(0x03FF, program_counter);
}
void program1(void){
    ret = led_turn_on(&led_1);
    __delay_ms(200);
    ret = led_turn_off(&led_1);
    __delay_ms(200);
}
void program2(void){
    ret = led_turn_on(&led_2);
    __delay_ms(200);
    ret = led_turn_off(&led_2);
    __delay_ms(200);
}

interrupt_INTx_t int0_obj = {
    .EXT_InterruptHandler = INT0_App_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .source = INTERRUPT_EXT_INT0,
    .priority = INTERRUPT_HIGH_PRIORITY, 
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = pin0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};


int main() {
    application_initialize();
    
    ret = Data_EEPROM_ReadByte(0x3ff, &program_counter);
    ret = Interrupt_INTx_Init(&int0_obj);
   
    while(1){   
        if(1 == program_counter){
            program1();
        }
        else if(2 == program_counter){
            program2();
        }
        else{
            ret = led_turn_off(&led_1);
            ret = led_turn_off(&led_2);
        }
    }

    return (EXIT_SUCCESS);
}

void application_initialize(void) {
    Ecu_interfaces_initialize();
}