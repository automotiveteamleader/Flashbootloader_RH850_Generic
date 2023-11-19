/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        Header file for the watchdog functions
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Andreas Wenckebach            AWh           Vector Informatik GmbH
 *  Ralf Haegenlaeuer             HRf           Vector Informatik GmbH
 *  Thomas Bezold                 TBe           Vector Informatik GmbH
 *  Alexander Starke              ASe           Vector Informatik GmbH
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  Torben Stoessel               TnS           Vector Informatik GmbH
 *  Achim Strobelt                Ach           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  02.00.00   2013-09-20  HRf     ESCAN00070534    No changes
 *  02.01.00   2013-10-01  AWh     ESCAN00070817    Allow to configure external Wd Event Timer handling (P2)
 *  02.02.00   2013-10-09  HRf     ESCAN00070988    No changes
 *  02.03.00   2014-01-20  AWh     ESCAN00071053    Unused macros for FBL_ENABLE_GENERIC_WDTIMER_EXT_HANDLING
 *                         TBe     ESCAN00071969    Corrected configuration check in event timer handling
 *                         ASe     ESCAN00072907    No changes
 *  02.04.00   2014-06-13  ASe     ESCAN00076257    Modified watchdog copy handling for C_COMP_IAR_RL78_AFCAN
 *  02.05.00   2014-10-17  Ach     ESCAN00078355    Added void wrapper for FblLookForWatchdog()
 *  02.06.00   2015-04-17  Rie     ESCAN00082413    Added MemMap support for FblLookForWatchdogVoid
 *  02.07.00   2015-06-12  AWh     ESCAN00083379    No changes
 *  02.08.00   2015-09-18  AWh     ESCAN00083585    Remove fixed FBL_WD_TRIGGER_SIZE macro for some hw platforms
 *                         AWh     ESCAN00083951    No changes
 *  02.09.00   2015-10-23  AWh     ESCAN00085794    No changes
 *                         CB      ESCAN00085818    Removed out-dated filters for Tasking- and Keil-compiler
 *  02.09.01   2015-12-10  TnS     ESCAN00086954    Compiler warning: variable set but never used
 *                         TnS     ESCAN00059743    Watchdog trigger function is not executed any more after flash
 *                                                  erase function was called (FBL_ENABLE_INTERRUPT is set)
 *  02.09.02   2015-12-10  AWh     ESCAN00087120    Timer interrupt use case not supported for Ford SLP7
 *  02.10.00   2016-02-23  Ach     ESCAN00088299    No changes
 *                         TnS     ESCAN00088434    Added comments
 *  02.11.00   2016-05-31  AWh     ESCAN00090236    No changes
 **********************************************************************************************************************/

#ifndef __FBL_WD_H__
#define __FBL_WD_H__

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : FblWd CQComponent : Implementation */
#define FBLWD_VERSION            0x0211u
#define FBLWD_RELEASE_VERSION    0x00u

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

/* PRQA S 3453 FblWd_3453 */ /* MD_MSR_19.7 */
/* PRQA S 3458 FblWd_3458 */ /* MD_MSR_19.4 */

/* Return values of LookForWatchdog */
/* Indicates its internal action    */
#define FBL_NO_TRIGGER     0x00u    /* No action performed (just watching the timer) */
#define FBL_WD_TRIGGERED   0x03u    /* Watchdog has been triggered */
#define FBL_TM_TRIGGERED   0x02u    /* Timer has expired and was re-triggered */

/* Macros for watchdog initialization */
#define GetWDInit()        (WDInitFlag == 0x01u)
#define SetWDInit()        (WDInitFlag = 0x01u)
#define ClrWDInit()        (WDInitFlag = 0x00u)

/* Map wdGenericEventTimer to P2 timeout timer */
# define wdGenericEventTimer P2Timer
/* Define P2Timer access macros */
# define GetP2Timer()       (P2Timer)
# define SetP2Timer(val)    (P2Timer = (val))
# define ClrP2Timer()       (P2Timer = 0x00u)

/* PRQA L:FblWd_3453 */
/* PRQA L:FblWd_3458 */

/***********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 **********************************************************************************************************************/

extern vuint16 P2Timer;    /**< Multiple purpose timer */
extern vuint8  WDInitFlag; /**< Watchdog initialized flag */

#if defined( FBL_WATCHDOG_ON )
# if ( FBL_WATCHDOG_TIME > 255u )
typedef vuint16 tWdTime;
# else
typedef vuint8 tWdTime;
# endif

extern tWdTime WDTimer; /**< Watchdog timer */
#endif /* FBL_WATCHDOG_ON */

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

# define INITWATCHDOG_START_SEC_CODE_EXPORT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */
void V_API_NEAR FblInitWatchdog ( void );

# define INITWATCHDOG_STOP_SEC_CODE_EXPORT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define LOOKFORWATCHDOG_START_SEC_CODE_EXPORT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

void V_API_NEAR FblLookForWatchdogVoid( void );
# define LOOKFORWATCHDOG_STOP_SEC_CODE_EXPORT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

# define LOOKFORWATCHDOG_START_SEC_CODE_EXPORT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

vuint8 V_API_NEAR FblLookForWatchdog( void );

# define LOOKFORWATCHDOG_STOP_SEC_CODE_EXPORT
# include "MemMap.h" /* PRQA S 5087 */ /* MD_MSR_19.1 */

#endif /* __FBL_WD_H__ */

/***********************************************************************************************************************
 *  END OF FILE: FBL_WD.H
 **********************************************************************************************************************/
