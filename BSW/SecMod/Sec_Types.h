/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        Implementation of the HIS security module - Type definitions
 *
 *  \description  Defines types, constants and configuration switches used by the security module
 *  -------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2017 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/*********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Joern Herwig                  JHg           Vector Informatik GmbH
 *  Markus Schneider              Mss           Vector Informatik GmbH
 *  Christian Baeuerle            CB            Vector Informatik GmbH
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  Andreas Wenckebach            AWh           Vector Informatik GmbH
 *  Achim Strobelt                Ach           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  01.00.00   2013-06-20  JHg     ESCAN00068213    Initial release based on FblSecMod_Vector 02.02.00
 *  02.00.00   2013-10-01  JHg     ESCAN00070689    Major refactoring
 *                                                   Renamed file name (was SecM_def.h)
 *                                                   Introduction of supporting types for easier handling
 *                                                   Added types for extended functionality (workspace and key handling)
 *                                                   Defaults and remapping of configuration switches
 *  02.01.00   2013-11-08  JHg     ESCAN00071173    Added support for CRC, seed/key and verification APIs
 *  02.01.01   2013-11-08  JHg     ESCAN00071733    No changes
 *  02.01.02   2013-11-11  JHg     ESCAN00071785    No changes
 *  02.02.00   2013-12-19  Mss     ESCAN00072743    No changes
 *  02.03.00   2014-02-20  JHg     ESCAN00073562    CRC algorithm selectable at compile time
 *                         Mss     ESCAN00073600    Decryption algorithm selectable at compile time
 *                         Mss     ESCAN00073811    No changes
 *  02.04.00   2015-02-09  CB      ESCAN00079848    No changes
 *  02.04.01   2015-03-10  Rie     ESCAN00081703    No changes
 *  02.04.02   2015-07-29  AWh     ESCAN00084125    Beautification
 *  02.05.00   2015-10-12  JHg     ESCAN00085810    No changes
 *  02.05.01   2015-10-28  JHg     ESCAN00086114    Added default values for signature scheme macros
 *  02.06.00   2015-11-11  JHg     ESCAN00086123    No changes
 *                         JHg     ESCAN00086125    Watchdog cycle count has to be a power of two
 *                                                  Adaptations for MISRA compliance
 *                         JHg     ESCAN00086239    Defines for type sizes
 *  02.07.00   2016-06-29  JHg     ESCAN00089792    Added support for CMAC (AES-128)
 *                         JHg     ESCAN00089879    Added support for additional padding and block operation modes
 *                         JHg     ESCAN00090731    No changes
 *                         JHg     ESCAN00090668    No changes
 *  02.08.00   2017-01-18  JHg     ESCAN00093625    Added support for CRC-64
 *                                                  Renamed SEC_CRC16_CCITT to SEC_CRC16
 *  02.09.00   2017-07-25  JHg     ESCAN00096045    Added support for Ed25519 signatures
 *                         Ach     ESCAN00095858    No changes
 **********************************************************************************************************************/

#ifndef __SECM_TYPES_H__
#define __SECM_TYPES_H__

/***********************************************************************************************************************
 *  INCLUDES
 **********************************************************************************************************************/

#include "Sec_Inc.h"

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

/* Defaults for configuration defines */

#if defined( SEC_WATCHDOG_CYCLE_COUNT )
#else
/** Watchdog triggered every n-th cycle (has to power of two) */
# define SEC_WATCHDOG_CYCLE_COUNT   (0x20u)
#endif

#if defined( SEC_ENABLE_WORKSPACE_INTERNAL ) || \
    defined( SEC_ENABLE_WORKSPACE_EXTERNAL )
#else
/** Use internal default workspaces */
# define SEC_ENABLE_WORKSPACE_INTERNAL
#endif /* SEC_ENABLE_WORKSPACE_INTERNAL || SEC_ENABLE_WORKSPACE_EXTERNAL */

#if defined( SEC_CHECKSUM_TYPE_CRC )
#else
/** Use CRC algorithm for checksum verification (security class DDD) */
# define SEC_CHECKSUM_TYPE_CRC      0u
#endif /* SEC_CHECKSUM_TYPE_CRC */
#if defined( SEC_CHECKSUM_TYPE_HASH )
#else
/** Use hash algorithms for checksum verification (security class DDD) */
# define SEC_CHECKSUM_TYPE_HASH     (SEC_CHECKSUM_TYPE_CRC + 1u)
#endif /* SEC_CHECKSUM_TYPE_HASH */

#if defined( SEC_MAC_TYPE_HMAC )
#else
/** Use HMAC for MAC verification (security class C) */
# define SEC_MAC_TYPE_HMAC          0u
#endif /* SEC_MAC_TYPE_HMAC */
#if defined( SEC_MAC_TYPE_CMAC )
#else
/** Use CMAC for MAC verification (security class C) */
# define SEC_MAC_TYPE_CMAC          (SEC_MAC_TYPE_HMAC + 1u)
#endif /* SEC_MAC_TYPE_CMAC */

/** Algorithm identifier for SHA-256 */
#if defined( SEC_SHA256 )
#else
# if (SEC_SHA1 > SEC_RIPEMD160)
#  define SEC_SHA256    (SEC_SHA1 + 1u)
# else
#  define SEC_SHA256    (SEC_RIPEMD160 + 1u)
# endif
#endif /* SEC_SHA256 */

#if defined( SEC_CRC32 )
#else
/** Use CRC-32 algorithm for checksum calculation */
# define SEC_CRC32         0u
#endif /* SEC_CRC32 */
#if defined( SEC_CRC16 )
#else
# if defined( SEC_CRC16_CCITT )
#  define SEC_CRC16        SEC_CRC16_CCITT
# else
/** Use CRC-16 algorithm for checksum calculation */
#  define SEC_CRC16        (SEC_CRC32 + 1u)
# endif /* SEC_CRC16_CCITT */
#endif /* SEC_CRC16 */
#if defined( SEC_CRC64 )
#else
/** Use CRC-64 algorithm for checksum calculation */
# define SEC_CRC64         (SEC_CRC16 + 1u)
#endif /* SEC_CRC64 */

#if defined( SEC_AES128 )
#else
/** Use AES128 algorithm for decryption / encryption */
# define SEC_AES128        0u
#endif /* SEC_AES128 */
#if defined( SEC_AES192 )
#else
/** Use AES192 algorithm for decryption / encryption */
# define SEC_AES192        (SEC_AES128 + 1u)
#endif /* SEC_AES192 */
#if defined( SEC_AES256 )
#else
/** Use AES256 algorithm for decryption / encryption */
# define SEC_AES256        (SEC_AES192 + 1u)
#endif /* SEC_AES256 */

#if defined( SEC_ECB )
#else
/** Use electronic code book block mode for decryption / encryption */
# define SEC_ECB    0u
#endif /* SEC_ECB */
#if defined( SEC_CBC_IV )
#else
/** Use cipher block chaining block mode with explicit initialization vector for decryption / encryption */
# define SEC_CBC_IV        (SEC_ECB + 1u)
#endif /* SEC_CBC_IV */
#if defined( SEC_CBC )
#else
/** Use cipher block chaining block mode with implicit initialization vector (= 0) for decryption / encryption */
# define SEC_CBC           (SEC_CBC_IV + 1u)
#endif /* SEC_CBC */

#if defined( SEC_NONE )
#else
/** Don't apply any padding for decryption / encryption */
# define SEC_NONE          0u
#endif /* SEC_NONE */
#if defined( SEC_ISO7816_4 )
#else
/** Use padding according to ISO/IEC 7816-4 for decryption / encryption */
# define SEC_ISO7816_4     (SEC_NONE + 1u)
#endif /* SEC_ISO7816_4 */
#if defined( SEC_PKCS7 )
#else
/** Use padding according to PKCS #7 for decryption / encryption */
# define SEC_PKCS7         (SEC_ISO7816_4 + 1u)
#endif /* SEC_PKCS7 */

#if defined( SEC_SIGNATURE_SCHEME_RSA_V15 )
#else
/** Use RSASSA-PKCS1-v1_5 for signature verification */
# define SEC_SIGNATURE_SCHEME_RSA_V15              0u
#endif /* SEC_SIGNATURE_SCHEME_RSA_V15 */
#if defined( SEC_SIGNATURE_SCHEME_RSA_PSS )
#else
/** Use RSASSA-PSS for signature verification */
# define SEC_SIGNATURE_SCHEME_RSA_PSS              (SEC_SIGNATURE_SCHEME_RSA_V15 + 1u)
#endif /* SEC_SIGNATURE_SCHEME_RSA_PSS */
#if defined( SEC_SIGNATURE_SCHEME_ECDSA_CURVE25519 )
#else
/** Use RSASSA-PSS for signature verification */
# define SEC_SIGNATURE_SCHEME_ECDSA_CURVE25519     (SEC_SIGNATURE_SCHEME_RSA_PSS + 1u)
#endif /* SEC_SIGNATURE_SCHEME_RSA_PSS */

/*********************************************************************************************************************/

/* Return codes */

/** Positive return code */
#define SECM_OK      0x00u
/** Negative return code */
#define SECM_NOT_OK  0xFFu

#if defined( SEC_CALL_TYPE )
#else
/** Qualifier for function pointer declarations */
# define SEC_CALL_TYPE
#endif /* SEC_CALL_TYPE */

/** Null pointer for RAM data */
#define SEC_RAM_DATA_NULL              ((SecM_RamDataType)V_NULL)
/** Pointer to indicate use of internal default workspace */
#define SEC_DEFAULT_WORKSPACE          ((SecM_WorkspacePtrType)V_NULL)
/** Size to indicate use of internal default workspace */
#define SEC_DEFAULT_WORKSPACE_SIZE     0u
/** Size to indicate use of default key (e.g. for decryption) */
#define SEC_DEFAULT_KEY_SIZE           0u

/*********************************************************************************************************************/

/* Watchdog handling */

/** Empty watchdog trigger function pointer */
#define SEC_WATCHDOG_NONE              ((FL_WDTriggerFctType)0u)

/* PRQA S 3412 14 */ /* MD_MSR_19.4 */
/** Trigger watchdog
 *  Watchdog is disabled in case null pointer is passed */
#define SEC_WATCHDOG_TRIGGER(function)    \
   if ((SEC_WATCHDOG_NONE) != (function)) \
   {                                      \
      (function)();                       \
   }

/** Trigger watchdog every n-th cycle */
#define SEC_WATCHDOG_CYCLE_TRIGGER(function, cycle)            \
   if (((cycle) & (SEC_WATCHDOG_CYCLE_COUNT - 1u)) == 0x00u)   \
   {                                                           \
      SEC_WATCHDOG_TRIGGER(function);                          \
   }

/*********************************************************************************************************************/

/* Type sizes */

/** Byte size of byte type */
#define SEC_BYTE_TYPE_SIZE    1u
/** Byte size of short type */
#define SEC_SHORT_TYPE_SIZE   2u
/** Byte size of word type */
#define SEC_WORD_TYPE_SIZE    4u

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Supporting data types for easier handling */

/** Data type for byte values (8 bit)*/
typedef vuint8  SecM_ByteType;
/** Data type for short values (16 bit) */
typedef vuint16 SecM_ShortType;

/** Pointer type to byte data in RAM */
typedef V_MEMRAM1 SecM_ByteType V_MEMRAM2 V_MEMRAM3 *       SecM_RamDataType;
/** Pointer type to constant byte data in RAM */
typedef const V_MEMRAM1 SecM_ByteType V_MEMRAM2 V_MEMRAM3 * SecM_ConstRamDataType;
/** Pointer type to byte data in ROM */
typedef V_MEMROM1 SecM_ByteType V_MEMROM2 V_MEMROM3 *       SecM_RomDataType;
/** Void pointer type */
typedef V_MEMRAM1 void V_MEMRAM2 V_MEMRAM3 *                SecM_VoidPtrType;
/** Void pointer type (const) */
typedef const V_MEMRAM1 void V_MEMRAM2 V_MEMRAM3 *          SecM_ConstVoidPtrType;

/*********************************************************************************************************************/

/* Types specified by HIS specification */

/** Data type for status codes */
typedef SecM_ByteType SecM_StatusType;
/** Data type for word values (32 bit) */
typedef vuint32 SecM_WordType;
/** Data type for length information */
typedef SecM_ShortType SecM_LengthType;

/** Data type for address information */
typedef SecM_WordType SecM_AddrType;
/** Data type for size information */
typedef SecM_WordType SecM_SizeType;

/** Description of a download segment */
typedef struct
{
   SecM_AddrType transferredAddress;
   SecM_AddrType targetAddress;
   SecM_SizeType length;
} FL_SegmentInfoType;

/** List of downloaded segments */
typedef struct
{
   /** Number of segments in list */
   SecM_ByteType        nrOfSegments;
   /** List of segments */
   /* According to HIS specification */
   V_MEMRAM1 FL_SegmentInfoType V_MEMRAM2 V_MEMRAM3 * segmentInfo;
} FL_SegmentListType;

/** Pointer to watchdog trigger function */
typedef void (* FL_WDTriggerFctType)( void );
/** Pointer to memory read function */
typedef SecM_SizeType (* FL_ReadMemoryFctType)( SecM_AddrType, SecM_RamDataType, SecM_SizeType );

/*********************************************************************************************************************/

/* Fast types (used for loops) */

#if defined( C_CPUTYPE_8BIT )
/** Fast type which can hold at least a byte */
typedef SecM_ByteType   SecM_ByteFastType;
/** Fast type which can hold at least a short */
typedef SecM_ShortType  SecM_ShortFastType;
#elif defined( C_CPUTYPE_16BIT )
typedef SecM_ShortType  SecM_ByteFastType;
typedef SecM_ShortType  SecM_ShortFastType;
#elif defined( C_CPUTYPE_32BIT )
typedef SecM_WordType   SecM_ByteFastType;
typedef SecM_WordType   SecM_ShortFastType;
#endif /* C_CPUTYPE */

/** Fast type which can hold length information */
typedef SecM_ShortFastType SecM_LengthFastType;

/*********************************************************************************************************************/

/* Buffer types */

/** Information of buffer located in RAM */
typedef struct
{
   /** Pointer to data */
   SecM_ConstRamDataType   data;
   /** Buffer size given in byte */
   SecM_LengthType         size;
} SecM_RamBufferType;

/** Information of buffer located in ROM */
typedef struct
{
   /** Pointer to data */
   SecM_RomDataType  data;
   /** Buffer size given in byte */
   SecM_LengthType   size;
} SecM_RomBufferType;

/*********************************************************************************************************************/

/* Cryptographic key types */

/** Reference to cryptographic key */
typedef SecM_RomBufferType SecM_CryptKeyType;

/** Reference to symmetric cryptographic key (always located in RAM) */
typedef SecM_RamBufferType SecM_SymKeyType;

/** Reference to asymmetric cryptographic key pair */
typedef struct
{
   /** Shared key */
   SecM_CryptKeyType shared;
   /** Individual (public) key */
   SecM_CryptKeyType individual;
} SecM_AsymKeyType;

/*********************************************************************************************************************/

/* Workspace types */

/** Basic workspace structure used for aligned pointer type */
typedef struct
{
   SecM_ByteType  digest[1];  /**< Placeholder for message digest located at beginning of every workspace */
   SecM_WordType  dummy;      /**< Dummy member to enforce alignment, not actually used */
} SecM_BasicWkspType;

/** Pointer to aligned workspace */
typedef V_MEMRAM1 SecM_BasicWkspType V_MEMRAM2 V_MEMRAM3 * SecM_WorkspacePtrType;

/** Reference to workspace */
typedef struct
{
   /** Pointer to data */
   SecM_WorkspacePtrType   data;
   /** Buffer size given in byte */
   SecM_LengthType         size;
} SecM_WorkspaceType;

/***********************************************************************************************************************
 *  CONFIGURATION CHECKS
 **********************************************************************************************************************/

#if ( 0u == SEC_WATCHDOG_CYCLE_COUNT ) || \
    ( (SEC_WATCHDOG_CYCLE_COUNT & (SEC_WATCHDOG_CYCLE_COUNT - 1u)) != 0u )
# error "Error in SEC_TYPES.H: Watchdog cycle count has to be a power of two (2^n)!"
#endif

#endif /* __SECM_TYPES_H__ */

/***********************************************************************************************************************
 *  END OF FILE: SEC_TYPES.H
 **********************************************************************************************************************/
