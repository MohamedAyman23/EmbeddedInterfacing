/* 
 * File:   hal_eeprom.h
 * Author: moham
 *
 * Created on September 29, 2023, 3:01 PM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/* -------------------- Includes -------------------- */
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "../../MCAL_Layer/Interrupt/mcal_internal_interrupt.h"
/* -------------------- MACRO Declarations -------------------- */

/* Flash program or Data EEPROM Memory Select */
#define ACCESS_FLASH_PROGRAM_MEMORY             1
#define ACCESS_EEPROM_PROGRAM_MEMORY            0

/* Flash Program/Data EEPROM or Configuration Select */
#define ACCESS_CONFIG_REGISTERS                 1
#define ACCESS_FLASH_EEPROM_MEMEORY             0

/* Flash Program/Data EEPROM Write Enable */
#define ALLOWS_WRITE_CYCLES_FLASH_EEPROM        1
#define INHIBITS_WRITE_CYCLES_FLASH_EEPROM      0

/* Write Control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE        1
#define DATA_EEPROM_WRITE_ERASE_COMPLETED       0

/* Read Control */
#define INTIATE_DATA_EEPROM_READ                1
#define DATA_EEPROM_READ_COMPLETED              0

/* -------------------- MACROS FUNCTIONS Declarations -------------------- */

/* -------------------- DataTypes -------------------- */

/* -------------------- Software Interfaces Declarations -------------------- */

Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);

#endif	/* HAL_EEPROM_H */

