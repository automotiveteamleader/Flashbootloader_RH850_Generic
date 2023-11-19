/* -----------------------------------------------------------------------------
  Filename:    ftp_cfg.h
  Description: Toolversion: 07.03.01.01.70.10.35.00.00.00
               
               Serial Number: CBD1701035
               Customer Info: Nexteer Automotive (Suzhou) Co.
                              Package: FBL Vector SLP3 - CANfbl license for the project EPS for OEMs without manufacturer specific requirements
                              Micro: R7F701313EAFP 
                              Compiler: GreenHills 2015.1.7
               
               
               Generator Fwk   : GENy 
               Generator Module: FblTp_Iso
               
               Configuration   : D:\usr\usage\Delivery\CBD17x\CBD1701035\D00\external\Demo\DemoFbl\Config\DemoFbl_CBD1701035.gny
               
               ECU: 
                       TargetSystem: Hw_Rh850Cpu
                       Compiler:     GreenHills
                       Derivates:    P1M
               
               Channel "Channel0":
                       Databasefile: D:\usr\usage\Delivery\CBD17x\CBD1701035\D00\external\Demo\DemoFbl\Config\DemoFBL_Vector_SLP3.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         Demo_0_CAN11

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(__FTP_CFG_H__)
#define __FTP_CFG_H__

/* PRQA S 3453 EOF */ /* MD_MSR_19.7 */
#define FBL_TP_DISABLE_EXTENDED_ADDRESSING
#define FBL_TP_DISABLE_TX_FRAME_PADDING
#define kFblTpFillPattern                    0
#define FBL_TP_DISABLE_ACCEPT_TOO_LARGE_DATA
#define FBL_TP_DISABLE_OVERRUN_FLAG_IN_FC
#define FBL_TP_DISABLE_ISO_COMPLIANCE
#define FBL_TP_DISABLE_ONLY_FIRST_FC
#define FBL_TP_ENABLE_FLOW_STATE
#define kFblTpWFTmax                         16u
#define FBL_TP_DISABLE_NO_STMIN_AFTER_FC
#define FBL_TP_DISABLE_WAIT_CORRECT_SN
#define FBL_TP_ENABLE_ISO15765_2_2
#define FBL_TP_DISABLE_VARIABLE_TX_DLC
#define FBL_TP_ENABLE_FIX_RX_DLC_CHECK
#define FBL_TP_DISABLE_VARIABLE_RX_DLC
#define FBL_TP_ENABLE_INTERNAL_MEMCPY
#define TpCallCycle                          1
#define FBL_TP_ENABLE_CONFIRMATION_INTERRUPT
#define FBL_TP_DISABLE_QUEUED_REQUESTS
#define kFblTpConfInterruptTimeout           70
#define kFblTpSTMin                          0
#define kFblTpTimeoutFC                      250
#define kFblTpTimeoutCF                      250
#define kFblTpTransmitCF                     10
#define kFblTpBlocksize                      0
#define kFblTpBufferSize                     2050
#define __ApplFblTpErrorIndication(i)        FblCwTpErrorIndication(i)
#define __ApplFblTpDataInd(i)                FblCwTpDataInd(i)
#define __ApplFblTpDataIndOverrun(actLen, refLen) FblCwTpDataIndBO(actLen, refLen)
#define __ApplFblTpConfirm(i)                FblCwTpConfirmation(i)
#define __ApplFblTpCopyFromCAN(dst, src, len) (void)(MEMCPY( (void *)(dst), (V_MEMROM0 V_MEMROM1 void V_MEMROM2 *)(src), (size_t)(len) ))
#define __ApplFblTpCopyToCAN(dst, src, len)  (void)(MEMCPY( (void *)(dst), (V_MEMROM0 V_MEMROM1 void V_MEMROM2 *)(src), (size_t)(len) ))
#define __ApplFblTpNotifyTx(i)
#define __ApplFblTpCanMessageTransmitted()
#define __ApplFblTpCanMessageReceived()
#define __ApplFblTpRxSF()                    FblCwTpRxStartIndication()
#define __ApplFblTpRxFF()                    FblCwTpRxStartIndication()
#define __ApplFblTpRxCF()
#define __ApplFblTpMsgTooLong(len_lobyte, len_hibyte)
#ifndef C_CPUTYPE_8BIT
#define FBL_TP_ENABLE_OSEK_DATA_LENGTH
typedef vuint16 tTpDataType;
#else
#define FBL_TP_ENABLE_OSEK_DATA_LENGTH
typedef vuint16 tTpDataType;
#endif


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 281181119
      #error "The magic number of the generated file <D:\usr\usage\Delivery\CBD17x\CBD1701035\D00\external\Demo\DemoFbl\Appl\GenData\ftp_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 281181119
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __FTP_CFG_H__ */
