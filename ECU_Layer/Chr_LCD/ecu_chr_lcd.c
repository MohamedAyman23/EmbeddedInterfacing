/* 
 * File:   ecu_chr_lcd.c
 * Author: moham
 *
 * Created on September 19, 2023, 9:59 AM
 */

#include "ecu_chr_lcd.h"

static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd, uint8 _data_command);
static Std_ReturnType lcd_send_4bit_enable_signal(const chr_lcd_4bit_t *lcd);
static Std_ReturnType lcd_send_8bit_enable_signal(const chr_lcd_8bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column);
static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);



Std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd){
    
    uint8 l_data_pins_counter =0;
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter =0; l_data_pins_counter < 4; l_data_pins_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, _LCD_RETURN_HOM);
        ret = lcd_4bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_command(lcd, _LCD_4BIT_MODE_2LINE);
        ret = lcd_4bit_send_command(lcd, _LCD_DDRAM_START);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_command(const chr_lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bit(lcd, ((command) >> 4));
        ret = lcd_send_4bit_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, command);
        ret = lcd_send_4bit_enable_signal(lcd);
        
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bit(lcd, ((data) >> 4));
        ret = lcd_send_4bit_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, data);
        ret = lcd_send_4bit_enable_signal(lcd);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_string_data(const chr_lcd_4bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        while(*str){
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_string_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd, row, column);
        while(*str){
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}
Std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column,
                                         const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter =0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_4bit_send_command(lcd, _LCD_CGRAM_START  + (mem_pos * 8));
        for(lcd_counter = 0; lcd_counter < 8; lcd_counter++)
        {
            ret = lcd_4bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);//to display the data on the LCD screen
        
        /** 
         * @param mem_pos like an index of an array on the CGRAM memory mem_pos = 0 
         *  means that print the data in dot matrix in character of the 1 element of the 
         *  CGRAM memory
         */
    }
    return ret;
}


Std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd){
    uint8 l_data_pins_counter =0;
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for(l_data_pins_counter =0; l_data_pins_counter < 8; l_data_pins_counter++){
            ret = gpio_pin_initialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, _LCD_RETURN_HOM);
        ret = lcd_8bit_send_command(lcd, _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_command(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_command(lcd, _LCD_8BIT_MODE_2LINE);
        ret = lcd_8bit_send_command(lcd, _LCD_DDRAM_START);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_command(const chr_lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(l_counter =0; l_counter < 8; l_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_counter]), (command >> l_counter) & ((uint8)0x01));
        }
        ret = lcd_send_8bit_enable_signal(lcd);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_OK;
    uint8 l_counter = 0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(l_counter =0; l_counter < 8; l_counter++)
        {
            ret = gpio_pin_write_logic(&(lcd->lcd_data[l_counter]), (data >> l_counter) & ((uint8)0x01));
        }
        ret = lcd_send_8bit_enable_signal(lcd);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_string_data(const chr_lcd_8bit_t *lcd, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_string_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd, row, column);
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    return ret;
}
Std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column,
                                         const uint8 _chr[], uint8 mem_pos){
    Std_ReturnType ret = E_OK;
    uint8 lcd_counter =0;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = lcd_8bit_send_command(lcd, _LCD_CGRAM_START  + (mem_pos * 8));
        for(lcd_counter = 0; lcd_counter < 8; lcd_counter++)
        {
            ret = lcd_8bit_send_char_data(lcd, _chr[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);//to display the data on the LCD screen
        
        /** 
         * @param mem_pos like an index of an array on the CGRAM memory mem_pos = 0 
         *  means that print the data in dot matrix in character of the 1 element of the 
         *  CGRAM memory
         */
    }
    return ret;
}

Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else{
        memset(str,'\0', 4);
        sprintf(str, "%i", value);
    }
    
}
Std_ReturnType convert_uint16_to_string(uint16 value, uint16 *str){
  Std_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else{
        memset(str,'\0', 6);
        sprintf(str, "%i", value);
    }  
}
Std_ReturnType convert_uint32_to_string(uint32 value, uint32 *str){
   Std_ReturnType ret = E_OK;
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else{
        memset(str,'\0', 11);
        sprintf(str, "%i", value);
    } 
}

static Std_ReturnType lcd_send_4bit(const chr_lcd_4bit_t *lcd, uint8 _data_command){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), ((_data_command) >> 0 )& ((uint8)0x01));
        ret &= ret;
        ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), ((_data_command) >> 1 )& ((uint8)0x01));
        ret &= ret;
        ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), ((_data_command) >> 2 )& ((uint8)0x01));
        ret &= ret;
        ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), ((_data_command) >> 3 )& ((uint8)0x01));
        ret &= ret;
    }
    return ret;
}

static Std_ReturnType lcd_send_4bit_enable_signal(const chr_lcd_4bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_send_8bit_enable_signal(const chr_lcd_8bit_t *lcd){
    Std_ReturnType ret = E_OK;
    if(NULL == lcd){
        ret = E_NOT_OK;
    }else{
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        switch(row){
            case ROW1: ret = lcd_8bit_send_command(lcd, (0x80 + column));break;
            case ROW2: ret = lcd_8bit_send_command(lcd, (0xC0 + column));break;
            case ROW3: ret = lcd_8bit_send_command(lcd, (0x94 + column));break;
            case ROW4: ret = lcd_8bit_send_command(lcd, (0xD4 + column));break;
            default : break;
        }
    }
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column){
    Std_ReturnType ret = E_OK;
    column--;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else{
        switch(row){
            case ROW1: ret = lcd_4bit_send_command(lcd, (0x80 + column));break;
            case ROW2: ret = lcd_4bit_send_command(lcd, (0xC0 + column));break;
            case ROW3: ret = lcd_4bit_send_command(lcd, (0x94 + column));break;
            case ROW4: ret = lcd_4bit_send_command(lcd, (0xD4 + column));break;
            default : break;
        }
    }
    return ret;
}