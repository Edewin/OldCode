/* 
 * File:   typedefs.h
 * Author: Mirela
 *
 * Created on February 11, 2013, 11:44 AM
 */

/*
 * Costume variable types
 *
 * Tested:
 * Microstick + Microstick Plus
 * PIC24HJ64GP502
 *
 * File name: HardwareProfile.h
 * Author: Jozsef KOPJAK
 * Info: info@microstickplus.com
 *
 * Last modification: 17-10-2012
 */

#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

        typedef enum{false = 0, true = 1} BOOL;	// Boolean variable

        typedef	unsigned char	BYTE;	// Unsigned 8 bit long variable
	typedef signed char 	CHAR;	// Signed 8 bit long variable

	typedef	unsigned short	WORD;	// Unsigned 16 bit long variable
	typedef signed short	SHORT;	// Signed 16 bit long variable

	typedef unsigned long	ULONG;	// Unsigned 16 bit long variable
	typedef signed long	LONG;	// Signed 16 bit long variable

	typedef float		FLOAT;	// Floating point 32 long variable

	#if defined (__18CXX)				// PIC18F:
		typedef	unsigned char	UBASE_TYPE;	// Unsigned 8 bit long variable
		typedef signed char	BASE_TYPE;	// Signed 8 bit long variable
	#elif defined (__C30__)				// PIC24F, PIC24H, dsPIC:
		typedef	unsigned short	UBASE_TYPE;	// Unsigned 16 bit long variable
		typedef signed short	BASE_TYPE;	// Signed 16 bit long variable
	#elif defined (__PIC32MX__)			// PIC32:
		typedef	unsigned long	UBASE_TYPE;	// Unsigned 32 bit long variable
		typedef signed long	BASE_TYPE;	// Signed 32 bit long variable
	#else
		#error "Unknown compiler!"
	#endif

#endif
