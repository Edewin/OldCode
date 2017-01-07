/*******************************************************************************
 System Initialization File

  Company:
    Microchip Technology Inc.
  
  File Name:
    system_init.c

  Summary:
    System Initialization.

  Description:
    This file contains source code necessary to initialize the system.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

#include "app.h"
/*TODO For Graphics stack
       #include "TouchScreen.h"
*/



// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************

/*
 System PLL Output Clock Divider (FPLLODIV)     = Divide by 1
 PLL Multiplier (FPLLMUL)                       = Multiply by 20
 PLL Input Divider (FPLLIDIV)                   = Divide by 2
 Watchdog Timer Enable (FWDTEN)                 = Disabled
 Clock Switching and Monitor Selection (FCKSM)  = Clock Switch Enable,
                                                  Fail Safe Clock Monitoring Enable
 Peripheral Clock Divisor (FPBDIV)              = Divide by 2
 */

// TODO configure the correct configuration fuse settings for your part


//End of configuration bits settings

/*TODO Configuration Tool would add below For Graphics stack
          void CheKseg0CacheOn(void);

		  #define GFX_DEFAULT_FOREGROUND_PAGE	GFX_PAGE9
          #define GFX_DEFAULT_BACKGROUND_PAGE 	GFX_PAGE10
          #define GFX_DEFAULT_DESTINATION_PAGE 	GFX_PAGE4

		  // TouchScreen Init Values
		  #ifdef USE_TOUCHSCREEN_RESISTIVE
		  #define TOUCH_INIT_VALUES   (NULL)
		  #endif
*/




// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************



// ****************************************************************************
// ****************************************************************************
// Section: System Initialization
// ****************************************************************************
// ****************************************************************************


  
/*******************************************************************************
  Function:
    void SYS_Initialize ( SYS_INIT_DATA *data )

  Summary:
    Initializes the board, services, drivers, application and other modules

  Description:
    This routine initializes the board, services, drivers, application and other
    modules as configured at build time.  In a bare-metal environment (where no
    OS is supported), this routine should be called almost immediately after
    entering the "main" routine.

  Precondition:
    The C-language run-time environment and stack must have been initialized.

  Parameters:
    data        - Pointer to the system initialization data structure containing
                  pointers to the board, system service, and driver
                  initialization routines
  Returns:
    None.

  Example:
    <code>
    SYS_INT_Initialize(NULL);
    </code>

  Remarks:
    Basic System Initialization Sequence:

    1.  Initialize minimal board services and processor-specific items
        (enough to use the board to initialize drivers and services)
    2.  Initialize all supported system services
    3.  Initialize all supported modules
        (libraries, drivers, middleware, and application-level modules)
    4.  Initialize the main (static) application, if present.

    The order in which services and modules are initialized and started may be
    important.

    For a static system (a system not using the Harmony's dynamic implementation
    of the initialization and "Tasks" services) this routine is implemented
    for the specific configuration of an application.
 */



void SYS_Initialize ( void* data )
{

    /* Initialize the BSP */
   // BSP_Initialize ( );

  
    // TODO perform initialization of the system

	/*TODO For Graphics Stack. In the future releases, the tool would add required initialization API's appropriately.

		// initialize the Flash Memory driver
		SST25Init();

		// initialize the timer that manages the tick counter
		TickInit();

		GFX_OBJ_Initialize();

		// initialize the components for Resistive Touch Screen
		TouchInit();

		GFX_PRIM_Initialize(0);

		DisplayBacklightOn();

		ImageDecoderInit();

		JPEGInit();

		GFX_SchemeInit();
	*/

	/* TODO For USB Stack. In the future releases, the tool would add required initialization API's appropriately.

		//Initialize the USB Host controller driver
		DRV_USB_Initialize ( );

		//Initialize the USB device layer
		USB_DEVICE_Initialize( );

		//Initialize the USB host layer
		USB_HOST_Initialize ( );

	*/

	/* TODO For TCPIP Stack. In the future releases, the tool would add required initialization API'sappropriately.

		// Initialize the TCPIP stack
		TCPIP_STACK_Initialize( );


	*/

    /* Initialize the Application */
    APP_Initialize ( );
	
	

    
}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
