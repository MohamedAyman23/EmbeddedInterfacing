/* 
 * File:   mcal_std_types.h
 * Author: moham
 *
 * Created on August 21, 2023, 6:31 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/* Section : Includes */
#include "std_libararies.h"
/* Section DataTypes */
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

typedef signed char sint8;
typedef signed short sint16;
typedef signed int sint32;

typedef uint8 Std_ReturnType;
/* MACRO Declarations */
#define BIT_MASK        (uint8)0x01

#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x0l
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define CONFIG_ENABLE   0x01
#define CONFIG_DISABLE  0x00


#define E_OK        (Std_ReturnType)0x01
#define E_NOT_OK    (Std_ReturnType)0x00


/* MACROS FUNCTIONS Declarations */

/* Functions Declarations */

#endif	/* MCAL_STD_TYPES_H */

