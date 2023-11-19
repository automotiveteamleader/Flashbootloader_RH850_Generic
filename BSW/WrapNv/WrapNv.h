/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file         WrapNv.h
 *  \brief        Wrapper for NV-memory access
 *  -------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2016 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/*********************************************************************************************************************/

/**********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  -------------------------------------------------------------------------------------------------------------------
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  -------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  -------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  -------------------------------------------------------------------------------------------------------------------
 *  02.00.00   2016-02-22  Rie     ESCAN00088726    Added support for Fee/NvM
 *                                                  Removed unused code
 *  02.01.00   2016-03-09  Rie     ESCAN00088817    No changes
 *                                 ESCAN00088819    No changes
 *  02.02.00   2016-07-05  Rie     ESCAN00090830    Added support for no NV driver use-case
 *  02.02.01   2016-09-06  Rie     ESCAN00091757    Fixed MISRA findings
 *  02.02.02   2016-10-17  Rie     ESCAN00092351    No changes
 *********************************************************************************************************************/

#ifndef __WRAPNV_H__
#define __WRAPNV_H__

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : SysService_WrapperNv CQComponent : Implementation */
#define SYSSERVICE_WRAPPERNV_VERSION              0x0202u
#define SYSSERVICE_WRAPPERNV_RELEASE_VERSION      0x02u

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

#include "WrapNv_Cfg.h"

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

/* PRQA S 0883 TAG_WrapNv_0883 */ /* MD_WrapNv_0883 */
/** Positive return value of NV-Wrapper */
#if defined( kFblOk )
# define WRAPNV_E_OK                kFblOk
#elif defined( kEepMgrOk )
# define WRAPNV_E_OK                kEepMgrOk
#elif defined( E_OK )
# define WRAPNV_E_OK                E_OK
#else
# define WRAPNV_E_OK                0u
#endif

/** Negative return value of NV-Wrapper */
#if defined( kFblFailed )
# define WRAPNV_E_NOT_OK            kFblFailed
#elif defined( kEepMgrFailed )
# define WRAPNV_E_NOT_OK            kEepMgrFailed
#elif defined( E_NOT_OK )
# define WRAPNV_E_NOT_OK            E_NOT_OK
#else
# define WRAPNV_E_NOT_OK            1u
#endif

/** Pending return value of NV-Wrapper */
#if defined( kEepMgrBusy )
# define WRAPNV_E_PENDING           kEepMgrBusy
#elif defined( E_PENDING )
# define WRAPNV_E_PENDING           E_PENDING
#else
# define WRAPNV_E_PENDING           2u
#endif

/** Return type of NV-Wrapper */
#if defined( kFblOk )
# define WrapNv_ReturnType          tFblResult
#elif defined( kEepMgrOk )
# define WrapNv_ReturnType          vuint8
#elif defined( E_OK )
# define WrapNv_ReturnType          Std_ReturnType
#else
# define WrapNv_ReturnType          WrapNv_DefaultReturntype
#endif
/* PRQA L:TAG_WrapNv_0883 */

/**********************************************************************************************************************
 *  TYPEDEFS
 *********************************************************************************************************************/

typedef enum
{
   WRAPNV_OPSTATUS_INIT = 0u,
   WRAPNV_OPSTATUS_PENDING,
   WRAPNV_OPSTATUS_CANCEL,
   WRAPNV_OPSTATUS_IDLE           /**< Used only internally */
} tWrapNvOpStatus;

typedef unsigned char WrapNv_DefaultReturntype;

#endif /* __WRAPNV_H__ */

/***********************************************************************************************************************
 *  END OF FILE: WRAPNV.H
 **********************************************************************************************************************/
