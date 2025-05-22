/* 
 * File:   mcal_external_interrupt.c
 * Author: moham
 *
 * Created on September 24, 2023, 2:34 PM
 */
#include "mcal_external_interrupt.h"

static void (* INT0_InterruptHandler)(void) = NULL;
static void (* INT1_InterruptHandler)(void) = NULL;
static void (* INT2_InterruptHandler)(void) = NULL;

static void (* RB4_InterruptHandler_High)(void) = NULL;
static void (* RB4_InterruptHandler_Low)(void) = NULL;
static void (* RB5_InterruptHandler_High)(void) = NULL;
static void (* RB5_InterruptHandler_Low)(void) = NULL;
static void (* RB6_InterruptHandler_High)(void) = NULL;
static void (* RB6_InterruptHandler_Low)(void) = NULL;
static void (* RB7_InterruptHandler_High)(void) = NULL;
static void (* RB7_InterruptHandler_Low)(void) = NULL;

static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static Std_ReturnType Interrupt_INTx_ClearFlag(const interrupt_INTx_t *int_obj);

static Std_ReturnType INT0_SetInterruptHandler(void (* InterruptHandler)(void));
static Std_ReturnType INT1_SetInterruptHandler(void (* InterruptHandler)(void));
static Std_ReturnType INT2_SetInterruptHandler(void (* InterruptHandler)(void));
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);

/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        /* Disable to the interrupt module */
        ret = Interrupt_INTx_Disable(int_obj);
        /* Clear flag of the External module */
        ret = Interrupt_INTx_ClearFlag(int_obj);
        /* Configure the External INTx Edge */
        ret = Interrupt_INTx_Edge_Init(int_obj);
        /* Configure the External INTx Priority */
/* I can delete this function implementation cause i configured the priority at INTx Enable function */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURES_ENABLE 
    
        ret = Interrupt_INTx_Priority_Init(int_obj);
        #endif
        /* Configure the External INTx Pins */
        ret = Interrupt_INTx_Pin_Init(int_obj);
        /* Configure External Call back function */
        ret = Interrupt_INTx_SetInterruptHandler(int_obj);
        /* Enable the Interrupt Module */
        ret = Interrupt_INTx_Enable(int_obj);
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
Std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        /* This routine to Disable the PORTB RBx interrupt */
        EXT_RBx_InterruptDisabel();
        /* This routine to Clear the PORTB RBx interrupt Flag */
        EXT_RBx_InterruptFlagClear();
        /*This routine to check if the priority level is applied or not */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURES_ENABLE
        INTERRUPT_PriorityLevelEnable();
        if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
            INTERRUPT_GlobalInterruptLowEnable();
            EXT_RBx_InterruptLowPrioriy();           
        }
        else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){            
            INTERRUPT_GlobalInterruptHighEnable();
            EXT_RBx_InterruptHighPrioriy(); 
        }
        else{/* NoThing*/}
#else
        INTERRUPT_GlobalInterruptEnable();//GIE
        INTERRUPT_PeripheralInterruptEnable();//PEIE
#endif
        /* This routine to initialize the pin */
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
        /*This routine  to callback function based on the specified RBx */
        switch(int_obj->mcu_pin.pin){
            case pin4:
                RB4_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB4_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                break;
            case pin5:
                RB5_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB5_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                break;
            case pin6:
                RB6_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB6_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                break;
            case pin7:
                RB7_InterruptHandler_High = int_obj->EXT_InterruptHandler_High;
                RB7_InterruptHandler_Low = int_obj->EXT_InterruptHandler_Low;
                break;
            default : ret = E_NOT_OK; 
                break;
        }
        EXT_RBx_InterruptEnabel();        
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */

Std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        /* This routine to Disable the PORTB RBx interrupt */
        EXT_RBx_InterruptDisabel();
        /* This routine to Clear the PORTB RBx interrupt Flag */
        EXT_RBx_InterruptFlagClear();
    }
    return ret;
}


/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURES_ENABLE
                INTERRUPT_PriorityLevelEnable();
                INTERRUPT_GbaleInterruptHighEnable();
                
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif               
                
                EXT_INT0_InterruptEnable();
                ret = E_OK;
                break;
            case INTERRUPT_EXT_INT1 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURES_ENABLE
                INTERRUPT_PriorityLevelEnable();
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GbaleInterruptLowEnable();
                    EXT_INT1_PriorityLevelLOW();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GbaleInterruptHighEnable();
                    EXT_INT1_PriorityLevelHIGH();
                }
                else{/* NoThing*/}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif  
                EXT_INT1_InterruptEnable();
                ret = E_OK;
                break;
            case INTERRUPT_EXT_INT2 :
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURES_ENABLE
                INTERRUPT_PriorityLevelEnable(); 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                     INTERRUPT_GbaleInterruptLowEnable();
                     EXT_INT2_PriorityLevelLOW();
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ 
                    INTERRUPT_GbaleInterruptHighEnable();
                    EXT_INT2_PriorityLevelHIGH();
                }
                else{/* NoThing*/}
#else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
#endif  
                EXT_INT2_InterruptEnable();
                ret = E_OK;
                break;
            default : ret = E_NOT_OK; break;
        }
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0 :
                EXT_INT0_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUPT_EXT_INT1 :
                EXT_INT1_InterruptDisable();
                ret = E_OK;
                break;
            case INTERRUPT_EXT_INT2 :
                EXT_INT2_InterruptDisable();
                ret = E_OK;
                break;
            default : ret = E_NOT_OK; break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURES_ENABLE
static Std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT1 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT1_PriorityLevelLOW(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT1_PriorityLevelHIGH(); }
                else{/* NoThing*/}
                ret = E_OK;
                break;
            case INTERRUPT_EXT_INT2 :
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){ EXT_INT2_PriorityLevelLOW(); }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){ EXT_INT2_PriorityLevelHIGH(); }
                else{/* NoThing*/}
                ret = E_OK;
                break;           
            default : ret = E_NOT_OK; 
                break;
        }
    }
    return ret;
}
#endif
/**
 * 
 * @param int_obj
 * @return 
 */
 
static Std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT0_InerruptFallingEdge(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT0_InerruptRisingEdge(); }
                else{/* NoThing */}
                ret = E_OK;
                break;
            case INTERRUPT_EXT_INT1 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT1_InerruptFallingEdge(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT1_InerruptRisingEdge(); }
                else{/* NoThing */}
                ret = E_OK;
                break;
            case INTERRUPT_EXT_INT2 :
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){ EXT_INT2_InerruptFallingEdge(); }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){ EXT_INT2_InerruptRisingEdge(); }
                else{/* NoThing */}
                ret = E_OK;
                break;
            default : ret = E_NOT_OK; break;
        }
    }
    return ret;
}

/**
 * 
 * @param int_obj
 * @return 
 */
static Std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_initialize(&(int_obj->mcu_pin));
    }
    return ret;
}
/**
 * 
 * @param int_obj
 * @return 
 */

static Std_ReturnType Interrupt_INTx_ClearFlag(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0 :
                EXT_INT0_InterruptFlagClear();
                ret = E_OK;
                break;
            case INTERRUPT_EXT_INT1 :
                EXT_INT1_InterruptFlagClear();
                ret = E_OK;
                break;
            case INTERRUPT_EXT_INT2 :
                EXT_INT2_InterruptFlagClear();
                ret = E_OK;
                break;
            default : ret = E_NOT_OK; break;
        }
    }
    return ret;
}

static Std_ReturnType INT0_SetInterruptHandler(void (* InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
    }
    return ret;
}
static Std_ReturnType INT1_SetInterruptHandler(void (* InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else{
        INT1_InterruptHandler = InterruptHandler;
    }
    return ret;
}
static Std_ReturnType INT2_SetInterruptHandler(void (* InterruptHandler)(void)){
    Std_ReturnType ret = E_OK;
    if(NULL == InterruptHandler)
    {
        ret = E_NOT_OK;
    }
    else{
        INT2_InterruptHandler = InterruptHandler;
    }
    return ret;
}
static Std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    Std_ReturnType ret = E_OK;
    if(NULL == int_obj)
    {
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXT_INT0 :
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler);             
                break;
            case INTERRUPT_EXT_INT1 :
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler);              
                break;
            case INTERRUPT_EXT_INT2 :
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler);               
                break;
            default : ret = E_NOT_OK; break;
        }
    }
    return ret;
}


void INT0_ISR(void){
    /* Clear Interrupt Flag */
    EXT_INT0_InterruptFlagClear();
    /* Write code here */
    
    /* Callback function calling*/
    if(INT0_InterruptHandler)
    {
        INT0_InterruptHandler();
    }
}
void INT1_ISR(void){
    /* Clear Interrupt Flag */
    EXT_INT1_InterruptFlagClear();
    /* Write code here */
    
    /* Callback function calling*/
    if(INT1_InterruptHandler)
    {
        INT1_InterruptHandler();
    }
}
void INT2_ISR(void){
    /* Clear Interrupt Flag */
    EXT_INT2_InterruptFlagClear();
    /* Write code here */
    
    /* Callback function calling*/
    if(INT2_InterruptHandler)
    {
        INT2_InterruptHandler();
    }
}

void RB4_ISR(uint8 RB4_source){
    /* Clear RB4 Interrupt Flag */
    EXT_RBx_InterruptFlagClear();
    /* Can write code here */
    /* Callback function calling */
    if(0 == RB4_source){
        RB4_InterruptHandler_High();
    }
    else if(1 == RB4_source){
        RB4_InterruptHandler_Low();
    }
    
}
void RB5_ISR(uint8 RB5_source){
    /* Clear RB4 Interrupt Flag */
    EXT_RBx_InterruptFlagClear();
    /* Can write code here */
    /* Callback function calling */
    if(0 == RB5_source){
        RB5_InterruptHandler_High();
    }
    else if(1 == RB5_source){
        RB5_InterruptHandler_Low();
    }
}
void RB6_ISR(uint8 RB6_source){
    /* Clear RB4 Interrupt Flag */
    EXT_RBx_InterruptFlagClear();
    /* Can write code here */
    /* Callback function calling */
    if(0 == RB6_source){
        RB6_InterruptHandler_High();
    }
    else if(1 == RB6_source){
        RB6_InterruptHandler_Low();
    }
}
void RB7_ISR(uint8 RB7_source){
    /* Clear RB4 Interrupt Flag */
    EXT_RBx_InterruptFlagClear();
    /* Can write code here */
    /* Callback function calling */
    if(0 == RB7_source){
        RB7_InterruptHandler_High();
    }
    else if(1 == RB7_source){
        RB7_InterruptHandler_Low();
    }
}


static Std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj){
    
}
static Std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj){
    
}
static Std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj){
    
}
static Std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj){
    
}
