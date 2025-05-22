/* 
 * File:   hal_eeprom.c
 * Author: moham
 *
 * Created on September 29, 2023, 3:01 PM
 */

#include "hal_eeprom.h"

Std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    Std_ReturnType ret = E_OK;
    /* Read the Interrupt Status Enable/Disable */
    uint8 Data_Interrupts_Staus = INTCONbits.GIE;
    /* Update the Address registers */
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8)(bAdd & 0xFF);
    /* Update the Data Registers */
    EEDATA = bData;
    /* Select Access Data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMEORY;
    /* Allow Write Cycles to Flash/EEPROM */
    EECON1bits.WREN = ALLOWS_WRITE_CYCLES_FLASH_EEPROM;
    /* Disable all Interrupts "Global Interrupts" */
    INTERRUPT_GlobalInterruptDisable();
    /*Write the required sequence : 0x55 -> 0xAA */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    /* Initialize a Data EEPROM Erase/Write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    /* Wait for Writing to complete */
    while(EECON1bits.WR);
    /* Inhibits Write cycle to Flash program/ Data EEPROM */
    EECON1bits.WREN = INHIBITS_WRITE_CYCLES_FLASH_EEPROM;
    /* Restore the Interrupt Status "Enable/Disable" */
    INTCONbits.GIE = Data_Interrupts_Staus;
    return ret;
}
Std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    Std_ReturnType ret = E_OK;
    if(NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else{
        /* Update the Address registers */
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        /*Select Access Data EEPOM Memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMEORY;
        /* Initiate a Data EEPROM Read cycle */
        EECON1bits.RD = INTIATE_DATA_EEPROM_READ;
        /* NOP 2 Instructions cycles */
        NOP();
        NOP();
        /* Return Data */
        *bData = EEDATA;
    }
    return ret;
}
