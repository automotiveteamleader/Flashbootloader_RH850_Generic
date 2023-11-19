/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        Configuration of the HIS security module
 *
 *  \description  Template for configuration settings
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
 *  02.01.02   2013-11-11  JHg     ESCAN00071785    Added file
 *  02.02.00   2013-12-19  Mss     ESCAN00072743    No changes
 *  02.03.00   2014-02-20  JHg     ESCAN00073562    CRC algorithm selectable at compile time
 *                         Mss     ESCAN00073600    Decryption algorithm selectable at compile time
 *                         Mss     ESCAN00073811    No changes
 *  02.04.00   2015-02-09  CB      ESCAN00079848    No changes
 *  02.04.01   2015-03-10  Rie     ESCAN00081703    No changes
 *  02.04.02   2015-07-29  AWh     ESCAN00084125    No changes
 *  02.05.00   2015-10-12  JHg     ESCAN00085810    Added support for RSASSA-PSS signatures
 *  02.05.01   2015-10-28  JHg     ESCAN00086114    No changes
 *  02.06.00   2015-11-11  JHg     ESCAN00086123    No changes
 *                         JHg     ESCAN00086125    No changes
 *                         JHg     ESCAN00086239    No changes
 *  02.07.00   2016-06-29  JHg     ESCAN00089792    Added support for CMAC (AES-128)
 *                         JHg     ESCAN00089879    Added support for additional padding and block operation modes
 *                         JHg     ESCAN00090731    Added support for FIPS-186 PRNG
 *                         JHg     ESCAN00090668    No changes
 *  02.08.00   2017-01-18  JHg     ESCAN00093625    Added support for CRC-64
 *                                                  Renamed SEC_CRC16_CCITT to SEC_CRC16
 *  02.09.00   2017-07-25  JHg     ESCAN00096045    Added support for Ed25519 signatures
 *                         Ach     ESCAN00095858    No changes
 **********************************************************************************************************************/

#ifndef __SECM_CFG_H__
#define __SECM_CFG_H__

/***********************************************************************************************************************
 *  DEFINES
 **********************************************************************************************************************/

#define SEC_CLASS_DDD                           0u
#define SEC_CLASS_C                             1u
#define SEC_CLASS_CCC                           2u
#define SEC_CLASS_VENDOR                        3u
#define SEC_DEVELOPMENT                         1u
#define SEC_PRODUCTION                          2u
#define SEC_ADDRESS                             1u
#define SEC_FILE                                2u
#define SEC_CRC_SPEED_OPTIMIZED                 0u
#define SEC_CRC_SIZE_OPTIMIZED                  1u
#define SEC_SECURITY_CLASS                      SEC_CLASS_DDD
#define SEC_ECU_KEY                             0x00u
#define SEC_KEY_TIMEOUT                         100u
#define SEC_CALL_CYCLE                          10u
#define SEC_MEMORY_ACCESS                       SEC_ADDRESS
#define SEC_MODE                                SEC_PRODUCTION
#define SEC_CRC_OPT                             SEC_CRC_SPEED_OPTIMIZED
#define SEC_DISABLE_CRC_TOTAL
#define SEC_RIPEMD160                           0u
#define SEC_SHA1                                1u
#define SEC_SHA256                              2u
#define SEC_SHA512                              3u
#define SEC_HASH_ALGORITHM                      SEC_SHA1
#define SEC_AES128                              0u
#define SEC_AES192                              1u
#define SEC_AES256                              2u
#define SEC_DECRYPTION_ALGORITHM                SEC_AES128
#define SEC_ECB                                 0u
#define SEC_CBC_IV                              1u
#define SEC_CBC                                 2u
#define SEC_DECRYPTION_BLOCK_MODE               SEC_CBC_IV
#define SEC_NONE                                0u
#define SEC_ISO7816_4                           1u
#define SEC_PKCS7                               2u
#define SEC_DECRYPTION_PADDING                  SEC_PKCS7
#define SEC_CRC32                               0u
#define SEC_CRC16                               1u
#define SEC_CRC64                               2u
#define SEC_CRC_TYPE                            SEC_CRC32
#define SEC_CHECKSUM_TYPE_CRC                   0u
#define SEC_CHECKSUM_TYPE_HASH                  1u
#define SEC_CHECKSUM_TYPE                       SEC_CHECKSUM_TYPE_CRC
#define SEC_MAC_TYPE_HMAC                       0u
#define SEC_MAC_TYPE_CMAC                       1u
#define SEC_MAC_TYPE                            SEC_MAC_TYPE_HMAC
#define SEC_SIGNATURE_SCHEME_RSA_V15            0u
#define SEC_SIGNATURE_SCHEME_RSA_PSS            1u
#define SEC_SIGNATURE_SCHEME_ECDSA_CURVE25519   2u
#define SEC_SIGNATURE_SCHEME                    SEC_SIGNATURE_SCHEME_RSA_V15
#define SEC_VERIFY_BYTES                        64u
#define SEC_DISABLE_VERIFICATION_DISCRETE_HASH_CALC
#define SEC_PRNG_LCG                            0u
#define SEC_PRNG_FIPS186                        1u
#define SEC_PRNG                                SEC_PRNG_LCG
#define SEC_DISABLE_DECRYPTION
#define SEC_DISABLE_ENCRYPTION
#define SEC_DISABLE_VERIFICATION_ADDRESS_LENGTH
#define SEC_VER_SIG_OFFSET                      0u
#define SEC_VER_CRC_OFFSET                      0u

#endif /* __SECM_CFG_H__ */

/***********************************************************************************************************************
 *  END OF FILE: SECM_CFG.H
 **********************************************************************************************************************/
