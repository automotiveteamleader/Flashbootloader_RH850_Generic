/* Kernbauer Version: 1.12 Konfiguration: FBL Erzeugungsgangnummer: 1 */

/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief         Application dependent nonvolatile memory access routines
 *
 *  \note          Please note, that this file contains a collection of callback functions to be used with the
 *                 Flash Bootloader. These functions may influence the behavior of the bootloader in principle.
 *                 Therefore, great care must be taken to verify the correctness of the implementation.
 *                 The contents of the originally delivered files are only examples resp. implementation proposals.
 *                 With regard to the fact that these functions are meant for demonstration purposes only, Vector
 *                 Informatik's liability shall be expressly excluded in cases of ordinary negligence, to the extent
 *                 admissible by law or statute.
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.
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
 *  Marcel Viole                  MVi           Vector Informatik GmbH
 *  Achim Strobelt                Ach           Vector Informatik GmbH
 *  Alexander Starke              ASe           Vector Informatik GmbH
 *  Joern Herwig                  Jhg           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY (KbFbl_apnvFrameOem.h)
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  04.00.00   2015-09-15  MVi     ESCAN00085257    Rework for SWCP filtering
 *  04.01.00   2015-10-09  Ach     ESCAN00085757    Correct SWCP filtering
 *  04.02.00   2015-10-23  Ach     ESCAN00085960    Rework dependency check configuration
 *                                 ESCAN00086035    Added support for Brilliance configuration
 *  04.03.00   2016-01-12  ASe     ESCAN00087395    No changes
 *  04.04.00   2016-03-07  MVi     ESCAN00088647    Missing prototype (Vag)
 *                                 ESCAN00088763    Added ApplFblIsValidBlock
 *                                 ESCAN00088771    No changes
 *                                 ESCAN00088772    Added ApplFblWriteSegmentList and ApplFblReadSegmentList
 *  04.05.00   2016-06-07  Ach     ESCAN00090359    Execute MISRA checks
 *  04.06.00   2016-08-24  Rie     ESCAN00091648    Added support for extended addressing
 *  04.07.00   2017-01-05  Ach     ESCAN00093448    Improve compatibility with SecMod generator modules
 *  04.08.00   2017-03-06  JHg     ESCAN00094275    Added support for multiple connections
 *  04.09.00   2017-08-14  MVi     ESCAN00096301    Use FblKbApi for segment list functions
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  00.90.00   2003-12-10  CB                       First implementation
 *  00.91.00   2003-12-19  CB                       Decryption/decompression interface changed
 *  01.00.00   2004-02-24  CB                       Release
 *  01.01.00   2004-03-24  Rr                       Added new functions
 *  01.02.00   2004-03-25  WM                       Minor changes
 *  01.03.00   2004-04-23  WM                       Added watchdog trigger functions
 *                         ACP                      Added ApplFblSecurityStatus
 *                         AMN                      Added ApplFblIsValidFlashBlock, ApplFblReadBlock
 *  01.04.00   2004-05-07  CB                       Added ApplCanBusOff, ApplCanWakeUp
 *  01.05.00   2004-05-19  CB                       Minor changes
 *  01.06.00   2004-06-30  MHz     ESCAN00007536    Added prototype for function
 *                                                  ApplFblStatusGet()
 *                         WM                       Added prototype for ApplFblInitErrStatus()
 *  01.07.00   2004-07-22  CB                       Added ApplFblReadEcuIdentification,
 *                                                  ApplFblStoreTesterCode, ApplFblStoreProgrammingDate
 *  01.08.00   2004-08-06  WM                       Added ApplFblSecurityAccessDelayActive
 *  01.09.00   2004-09-09  Rr                       No changes
 *  01.10.00   2004-09-16  WM                       No changes
 *  01.11.00   2004-10-25  AP      ESCAN00010007    Adaptation to support Vector
 *                                                  component OSEK NM
 *  01.12.00   2004-12-23  AMN                      Changed prototype of ApFblWriteDataByIdentifier
 *                                                  Added ApplFblPBLConfigSet prototype
 *                         ACP                      Version check reworked
 *                         CB                       Added fingerprint functions
 *  01.13.00   2005-01-14  CB                       Added several API functions
 *  01.14.00   2005-03-22  WM      ESCAN00011595    MISRA warnings
 *  01.15.00   2005-09-29  WM                       No changes
 *  01.16.00   2005-12-08  WM      ESCAN00014594    FblApSrcApplFblTpParamInit token
 *                                                  added for TPMC
 *  01.17.00   2006-02-28  AMN                      Added tokens ApplFblCopyToRAM and
 *                                                  ApplFblIsValidAppInRAM
 *  01.18.00   2006-03-24  QPs                      Added ApplFblGetSubNodeRxCanId for gateway
 *                                                  implementation
 *  01.19.00   2006-04-25  CB      ESCAN00015917    Return value added for
 *                                                  ApplFblInvalidateBlock
 *                         WM      ESCAN00015960    Segment verification added
 *                         QPs     ESCAN00016110    Added ApplCanBusOff for the gateway
 *                         CB      ESCAN00016144    Return value added for
 *                                                  ApplFblInitDecryption
 *                         CB      ESCAN00016147    ApplFblStoreBootSwIdent added
 *                                 ESCAN00016171    ApplFblSetSecAccessDelayFlag,
 *                                                  ApplFblGetSecAccessDelayFlag and
 *                                                  ApplFblClrSecAccessDelayFlag added
 *  01.20.00   2006-05-18  ACP     ESCAN00016438    Added kStartupPreInit/PostInit
 *                                                  definition for new ApplFblStartup() parameter
 *  01.21.00   2006-06-29  FHE                      Added header for ApplFblCheckProgDependencies()
 *  01.22.00   2006-07-24  JHg                      Moved watchdog trigger function to non banked
 *                                                  memory for MCS12X
 *                                                  PRE_ and POST_FblApSrcApplFblWDTrigger
 *                         CB      ESCAN00017003    Added ApplFblProgrammingStateChanged
 *                         AMN                      added prototype for ApplFblValidateApp
 *  01.23.00   2006-08-10  JHg                      Added token for additional watchdog functions
 *                         AMN     ESCAN00017479    Modifed API of ApplFblValidateApp
 *                                                  for Misra compliance
 *  01.24.00   2006-12-06  FHE     ESCAN00018639    Added ApplFblCheckConditions
 *  01.25.00   2007-02-07  Hp      ESCAN00019129    Add support for CCP in the bootloader
 *                                                  ApplFblWriteDataByLocalId returns now vuint8.
 *                                                  Add PreHandler and presence-pattern support.
 *  01.26.00   2007-03-30  WM      ESCAN00020175    Added ApplFblControlFailSafeReaction
 *  01.27.00   2007-07-06  JHg                      Return value added to ApplFblDecryption and
 *                                                  ApplFblDeinitDecryption
 *  01.28.00   2007-07-27  Ls                       No changes
 *  01.29.00   2008-03-07  Ci      ESCAN00014726    No changes
 *                         Hp      ESCAN00014726    No changes
 *                         JHg                      No changes
 *                         Hp      ESCAN00025029    Support Vector decompression module (optional)
 *  01.30.00   2008-03-28  JHg     ESCAN00025354    No changes
 *                                 ESCAN00025355    No changes
 *  01.31.00   2008-06-13  Ci      ESCAN00025071    Extended function description of
 *                                                  ApplFblStartup() with kStartupStayInBoot
 *                                 ESCAN00027445    Added support for configurations
 *                                                  with multiple CAN channels
 *  01.32.00   2008-09-10  JHg     ESCAN00029860    No changes
 *  01.33.00   2008-10-15  FHe     ESCAN00030640    Added support for VAG spec 1.2.1
 *  01.34.00   2009-03-13  JHg     ESCAN00032180    Added support for multichannel configurations
 *                                                  to ApplCanTxObjStart, ApplCanTxObjConfirmed
 *                         FHe                      Restored old format of ApplFblCheckProgConditions
 *                         Ci      ESCAN00033475    Added gateway specific callback
 *                                                  functions (Gw_Route support)
 *  01.35.00   2009-03-12  QPs     ESCAN00033801    Added communication wrapper specific
 *                                                  callback functions
 *  01.36.00   2009-07-21  QPs     ESCAN00035282    Added DC SLP10 extension:
 *                                                  ApplFblControlFailSafeReaction
|   01.36.00               AWh     ESCAN00036825    No changes
 *  01.37.00   2009-08-31  AWh     ESCAN00037405    Inconsistent return value type between
 *                                                  WriteDataByCommonId prototype and implementation
 *                         QPs     ESCAN00037479    Added FrTrcv specific callback functions
 *  01.38.00   2009-09-18  Tbe     ESCAN00037856    Added Ethernet/DoIP specific
 *                                                  callback functions
 *  01.39.00   2009-12-02  Ci      ESCAN00038917    Adapted prototype of
 *                                                  ApplFblFatalError()
 *                                 ESCAN00038918    Added support for validation
 *                                                  struct handling
 *                                 ESCAN00038919    Added callback for flash erased
 *                                                  detection
 *  01.40.00   2010-02-15  Ci      ESCAN00040663    Enhanced flash erased detection
 *                                                  interface
 *                         Ci      ESCAN00040852    Replaced decryption interface by
 *                                                  data processing API
 *  01.41.00   2010-07-08  MVi     ESCAN00043736    Remove pragmas when memmap is used
 *                         Ci      ESCAN00043863    Added function ApplCanTpConfirmation
 *                         QPs     ESCAN00043896    Added support for LIN bootloader
 *  01.42.00   2010-07-23  CB      ESCAN00044299    No changes
 *  01.43.00   2010-09-15  Ci      ESCAN00044991    Added new Gw_Route API functions
 *  01.44.00   2010-12-10  MVi     ESCAN00047478    Enhanced flash erased detection interface
 *                                 ESCAN00047482    Added routine control succeeded interface
 *  01.45.00   2011-02-03  Ach     ESCAN00048191    No changes
 *  01.46.00   2011-07-14  Ci      ESCAN00052149    Adapted Gw_Route task interface
 *  01.47.00   2011-11-25  Hp      ESCAN00052787    Extend support for PresencePatterns
 *  01.48.00   2011-12-14  AWh     ESCAN00055586    Extend Api with ApplFblInvalidateApp function
 *  01.49.00   2012-02-14  Ach     ESCAN00056341    Added ApplFblStartApplication() function
 *  01.50.00   2012-02-22  Ach     ESCAN00052787    Extend support for PresencePatterns
 *                         MVi     ESCAN00056833    No changes
 *                                 ESCAN00056834    Added _EXPORT suffix to memmap defines
 *                         CB      ESCAN00056642    Added ApplFblCanPlatformToPhysChannel()
 *  01.51.00   2012-03-23  QPs     ESCAN00057230    Extend support for FlexRay
 *                         Ach     ESCAN00057636    No changes
 *                         CB      ESCAN00057670    Added Suspend Programming API
 *  01.52.00   2012-03-30  QPs     ESCAN00058040    Reworked PRE/POST tokens for ApplFblWDTrigger
 *  01.53.00   2012-08-16  MVi     ESCAN00060433    No changes
 *  01.54.00   2012-12-06  AWh     ESCAN00061619    Moved presence pattern macros to header
 *                         Ach     ESCAN00062912    Adapted comments to use Doxygen
 *  01.55.00   2013-01-24  Ach     ESCAN00064406    No changes
 *                         JHg     ESCAN00064421    Added callback ApplFblOnTransitionSession
 *                                 ESCAN00064437    Added callback ApplFblStateTask
 *  01.56.00   2013-02-08  ASe     ESCAN00064889    Reworked comments
 *  01.57.00   2014-01-21  ASe     ESCAN00072931    No changes
 *  01.58.00   2014-02-24  MVi     ESCAN00073549    No changes
 *  01.58.01   2014-04-03  ASe     ESCAN00074701    Fixed comments
 *  01.59.00   2014-07-16  QPs     ESCAN00077127    No changes
 *  01.60.00   2014-08-25  Dod     ESCAN00078033    Add callbacks ApplFblMemPreWrite/Erase and ApplFblGetLogBlkHash
 *  01.61.00   2015-01-13  Ach     ESCAN00080481    Change visibility of ApplFblChkModulePresence()
 *  01.62.00   2015-05-12  CB      ESCAN00082959    Added functions to read and store the TP target address
 *  01.63.00   2015-05-27  CB      ESCAN00083167    Additional callback functions for status backup
 *  01.64.00   2015-09-14  Ci      ESCAN00084704    No changes
 *                         QPs     ESCAN00085203    Added callback ApplFblCheckTesterSourceAddr
 *  01.64.01   2015-12-15  TnS     ESCAN00087100    Moved initialization for Timer Interrupt use case to FblWd
 *  01.65.00   2016-01-11  ASe     ESCAN00087324    No changes
 *                         Rr      ESCAN00087414    Extend Renault SLP3 specific API for reading light LogZone
 *  01.66.00   2016.02.25  TnS     ESCAN00088471    No changes
 *  01.67.00   2016-03-07  MVi     ESCAN00088759    Added ApplFblIsValidBlock
 *  01.68.00   2016-03-17  Shs     ESCAN00088957    Added support for PATAC SLP2
 *  01.69.00   2016-05-09  HRf     ESCAN00089907    No changes
 *  01.70.00   2016-05-17  Rie     ESCAN00090027    No changes
 *  01.71.00   2016-06-27  Ach     ESCAN00090683    Support configuration switch FBL_CW_ENABLE_MULTIPLE_NODES
 *  01.72.00   2016-07-15  DlM     ESCAN00090996    Added function for programming voltage check
 *  01.73.00   2016-08-02  Ach     ESCAN00091282    Added ApplFblGetVerificationData()
 *  01.74.00   2016-08-24  Rie     ESCAN00091646    Added ApplFblCheckFuncTargetAddr()
 *  01.75.00   2016-10-04  CEl     ESCAN00092168    Added ApplFblSetLogBlkHash()
 *  01.76.00   2016-12-01  Ach     ESCAN00093116    Added length parameter to ApplFblGetVerificationData()
 *  01.77.00   2017-02-07  Ach     ESCAN00093891    Added constant definition for common data structure
 *  01.77.01   2017-06-22  Rie     ESCAN00095595    No changes
 *  01.78.00   2017-07-04  CB      ESCAN00095725    Added functions to read and write the segment list in NV-memory
 *                         CEl     ESCAN00095744    No changes
 *  01.79.00   2017-07-31  Ach     ESCAN00096124    Add interface to handle DET callouts
 *  01.80.00   2017-08-08  Rie     ESCAN00096215    No changes
 *  01.81.00   2017-09-13  Ach     ESCAN00096636    Add interface definition for ApplDiagUserRoutine
 *  01.82.00   2017-10-09  Ach     ESCAN00096961    No changes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  REVISION HISTORY (KbFbl_apOem.h)
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  04.00.00   2015-07-30  Ach     ESCAN00084038    Rework for filtering with SWCP
 *  04.00.01   2015-08-18  Ach     ESCAN00084594    No changes
 *  04.00.02   2015-08-22  TnS     ESCAN00084862    No changes
 *                         MVi     ESCAN00085392    Rework for SWCP filtering (VAG)
 *                                 ESCAN00085408    No changes
 *  04.01.00   2015-10-09  Ach     ESCAN00085761    No changes
 *  04.02.00   2015-10-23  Ach     ESCAN00085959    No changes
 *                                 ESCAN00086033    Added support for Brilliance configuration
 *  04.03.00   2015-11-13  Ach     ESCAN00086391    No changes
 *  04.04.00   2015-12-10  Ach     ESCAN00087062    No changes
 *                                 ESCAN00087067    No changes
 *  04.05.00   2016-02-25  Ach     ESCAN00088484    No changes
 *                                 ESCAN00088523    Removed signature length definition
 *  04.06.00   2016-03-14  MVi     ESCAN00088693    No changes
 *                                 ESCAN00088765    No changes
 *                                 ESCAN00088893    No changes
 *  04.07.00   2016-04-13  Ach     ESCAN00089462    No changes
 *  04.08.00   2016-06-07  Ach     ESCAN00090336    Execute MISRA checks
 *  04.09.00   2016-06-27  Ach     ESCAN00090684    Support configuration switch FBL_CW_ENABLE_MULTIPLE_NODES
 *  04.10.00   2016-07-05  KJs     ESCAN00090718    No changes
 *  04.11.00   2016-08-08  Ach     ESCAN00091370    No changes
 *                         Rie     ESCAN00091649    No changes
 *  04.12.00   2017-02-08  Ach     ESCAN00093887    No changes
 *  04.13.00   2017-03-17  MVi     ESCAN00094410    No changes
 *  04.14.00   2017-03-21  MVi     ESCAN00094450    No changes
 *  04.15.00   2017-08-14  MVi     ESCAN00096302    No changes
 *  04.16.00   2017-09-15  Ach     ESCAN00096526    No changes
 *                                 ESCAN00096529    No changes
 *                                 ESCAN00096578    No changes
 *                         MVi     ESCAN00096580    No changes
 *                         Ach     ESCAN00096639    No changes
 *  04.16.01   2017-10-10  MVi     ESCAN00096952    No changes
 *                         Ach     ESCAN00096962    No changes
 *  04.16.02   2017-10-16  MVi     ESCAN00097049    No changes
 **********************************************************************************************************************/
/***********************************************************************************************************************
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY (RH850 KbFbl_apHW.C)
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  00.90.00   2012-12-18  CB                       First implementation
 *  01.00.00   2013-06-07  CB                       Release
 *  01.01.00   2015-10-21  JLe     ESCAN00086043    [GM Only] Add HighSpeed and LowSpeed macros
 *  01.02.00   2016-05-03  Ci      ESCAN00080515    No changes
 *  01.03.00   2016-05-23  CB      ESCAN00090133    No changes
 *  01.04.00   2016-08-03  Shs     ESCAN00091046    No changes
                           DlM     ESCAN00091205    No changes
 **********************************************************************************************************************/

#ifndef __FBL_APNV_H__
#define __FBL_APNV_H__

/***********************************************************************************************************************
 *  VERSION
 **********************************************************************************************************************/

/* ##V_CFG_MANAGEMENT ##CQProject : FblKbApi_FrameNv_UDS1 CQComponent : Implementation */
#define FBLKBAPI_FRAMENV_UDS1_VERSION             0x0409u
#define FBLKBAPI_FRAMENV_UDS1_RELEASE_VERSION     0x00u

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

#if defined( FBL_ENABLE_PRESENCE_PATTERN )
# define kFblPresencePatternSize    4u
# define kFblPresencePattern        {0x73u, 0x6Au, 0x29u, 0x3Eu}
/* Memory driver access */

/* Generate a define for the maximum of flash-segment-size or presence-pattern-size */
#if ( FBL_MAX_SEGMENT_SIZE < kFblPresencePatternSize )
# define FBL_PP_SEGMENT_SIZE        kFblPresencePatternSize
#else
# define FBL_PP_SEGMENT_SIZE        FBL_MAX_SEGMENT_SIZE
#endif
#endif /* FBL_ENABLE_PRESENCE_PATTERN */

/* ValidityFlags */
#define kEepValidateBlock                 0x01u
#define kEepInvalidateBlock               0x02u
/* ApplValidity */
#define kEepApplConsistent                0xD1u
#define kEepApplInconsistent              0xFFu
/* SecAccessDelayFlags */
#define kEepSecAccessDelayActive          0xA7u
#define kEepSecAccessDelayInactive        0xFFu

/* Size of validation bitfield */
#if defined( kEepSizeValidityFlags )
#else
# define kEepSizeValidityFlags            (kNrOfValidationBytes)
#endif

/* -- Flash access macros -- */
/* PRQA S 3453 8 */ /* MD_MSR_19.7 */
#define ApplFblGetPromMaxProgAttempts(blockNr) \
   (FblLogicalBlockTable.logicalBlock[(blockNr)].maxProgAttempts)
#define ApplFblReadPromSwVersion(descriptor, buffer) \
   FblReadProm((descriptor).blockStartAddress, (buffer), kApplInfoSizeSwVersion)
#define ApplFblReadPromSwPartNumber(descriptor, buffer) \
   FblReadProm((descriptor).blockStartAddress+kApplInfoOffsetSwPartNumber, (buffer), kApplInfoSizeSwPartNumber)
#define ApplFblReadPromSwSupplierInformation(descriptor, buffer) \
   FblReadProm((descriptor).blockStartAddress+kApplInfoOffsetSwSupplierInformation, (buffer), kApplInfoSizeSwSupplierInformation)

#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
/* Security access delay flag macros */ /* PRQA S 3453 6 */ /* MD_MSR_19.7 */
# define ApplFblGetSecAccessDelayFlag() \
   (ApplFblRWSecurityAccessDelayFlag(kEepReadData, 0u) != kEepSecAccessDelayInactive)
# define ApplFblSetSecAccessDelayFlag() \
   ApplFblRWSecurityAccessDelayFlag(kEepWriteData, kEepSecAccessDelayActive)
# define ApplFblClrSecAccessDelayFlag() \
   ApplFblRWSecurityAccessDelayFlag(kEepWriteData, kEepSecAccessDelayInactive)
#endif /* FBL_ENABLE_SEC_ACCESS_DELAY */

#if defined( FBL_ENABLE_RESPONSE_AFTER_RESET )
/* Reset response flag access macros */  /* PRQA S 3453 2 */ /* MD_MSR_19.7 */
# define ApplFblReadResetResponseFlag(buffer)      ApplFblNvReadResetResponseFlag(buffer)
# define ApplFblWriteResetResponseFlag(buffer)     ApplFblNvWriteResetResponseFlag(buffer)
#endif /* FBL_ENABLE_RESPONSE_AFTER_RESET */

#if defined( FBL_CW_ENABLE_MULTIPLE_CONNECTIONS )
/* PRQA S 3453 2 */ /* MD_MSR_19.7 */
# define ApplFblReadTpTargetAddr(buffer)           ApplFblNvReadTpAddress(buffer)
# define ApplFblWriteTpTargetAddr(buffer)          ApplFblNvWriteTpAddress(buffer)
#endif /* FBL_CW_ENABLE_NORMAL_FIXED_ADDRESSING || FBL_CW_ENABLE_EXTENDED_ADDRESSING || FBL_CW_ENABLE_MULTIPLE_CONNECTIONS */

/***********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 **********************************************************************************************************************/

tFblProgStatus ApplFblExtProgRequest( void );
tApplStatus ApplFblIsValidApp( void );
tFblResult ApplFblValidateBlock( tBlockDescriptor blockDescriptor );
tFblResult ApplFblInvalidateBlock( tBlockDescriptor blockDescriptor );
tFblResult ApplFblStoreFingerprint( vuint8 * buffer );
tFblResult ApplFblIncProgCounts( tBlockDescriptor blockDescriptor );
tFblResult ApplFblGetProgCounts( tBlockDescriptor blockDescriptor, V_MEMRAM1 vuint16 V_MEMRAM2 V_MEMRAM3 * progCounts);
tFblResult ApplFblIncProgAttempts( tBlockDescriptor blockDescriptor );
tFblResult ApplFblGetProgAttempts( tBlockDescriptor blockDescriptor, V_MEMRAM1 vuint16 V_MEMRAM2 V_MEMRAM3 * progAttempts );
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
tFblResult ApplFblWriteSecAccessInvalidCount( V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * invalidCount );
tFblResult ApplFblReadSecAccessInvalidCount( V_MEMRAM1 vuint8 V_MEMRAM2 V_MEMRAM3 * invalidCount );
#endif
#if defined( FBL_ENABLE_SEC_ACCESS_DELAY )
vuint8 ApplFblRWSecurityAccessDelayFlag( vuint8 mode, vuint8 value );
#endif
void ApplFblErrorNotification( tFblErrorType errorType, tFblErrorCode errorCode );
#if defined( FBL_ENABLE_PRESENCE_PATTERN )
tFblResult ApplFblAdjustLbtBlockData(tBlockDescriptor * blockDescriptor);
tFblResult ApplFblChkModulePresence( tBlockDescriptor * blockDescriptor );
#endif /* FBL_ENABLE_PRESENCE_PATTERN */
#if defined( SEC_DISABLE_CRC_TOTAL )
#else
tFblResult ApplFblWriteCRCTotal( V_MEMRAM1 tBlockDescriptor V_MEMRAM2 V_MEMRAM3 * blockDescriptor, vuint32 crcStart, vuint32 crcLength, vuint32 crcValue );
#endif /* SEC_DISABLE_CRC_TOTAL */

#if defined( FBL_APPL_ENABLE_STARTUP_DEPENDENCY_CHECK )
#else
tFblResult ApplFblValidateApp( void );
tFblResult ApplFblInvalidateApp( void );
#endif /* FBL_APPL_ENABLE_STARTUP_DEPENDENCY_CHECK */

#endif /* __FBL_APNV_H__ */

/***********************************************************************************************************************
 *  END OF FILE: FBL_APNV.H
 **********************************************************************************************************************/
