/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_cg_rtc.h
* Version      : Applilet3 for RL78/G14 V2.05.05.01 [25 Nov 2020]
* Device(s)    : R5F104BG
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for RTC module.
* Creation Date: 2/5/2022
***********************************************************************************************************************/

#ifndef RTC_H
#define RTC_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/*
    Peripheral enable register 0 (PER0)
*/
/* Control of real-time clock (RTC) input clock (RTCEN) */
#define _00_RTC_CLOCK_STOP            (0x00U)    /* stops supply of input clock */
#define _08_RTC_CLOCK_SUPPLY          (0x80U)    /* supplies input clock */

/*
    Real-time clock register 0 (RTCC0)
*/
/* Real-time clock operation control (RTCE) */
#define _00_RTC_COUNTER_STOP          (0x00U)    /* stops clock operation */
#define _80_RTC_COUNTER_START         (0x80U)    /* starts clock operation */
/* Interrupt (INTRTC) selection (CT2 - CT0) */
#define _F8_RTC_INTRTC_CLEAR          (0xF8U)    /* clear constant-period interrupt function */
#define _00_RTC_INTRTC_NOT_GENERATE   (0x00U)    /* does not use constant-period interrupt function */
#define _01_RTC_INTRTC_CLOCK_0        (0x01U)    /* once per 0.5s */
#define _02_RTC_INTRTC_CLOCK_1        (0x02U)    /* once per 1 s */
#define _03_RTC_INTRTC_CLOCK_2        (0x03U)    /* once per 1 minute */
#define _04_RTC_INTRTC_CLOCK_3        (0x04U)    /* once per 1 hour */
#define _05_RTC_INTRTC_CLOCK_4        (0x05U)    /* once per 1 day */
#define _06_RTC_INTRTC_CLOCK_5        (0x06U)    /* once per 1 month */

/*
    Real-time clock control register 1 (RTCC1)
*/
/* Constant-period interrupt status flag (RIFG) */
#define _00_RTC_INTC_NOTGENERATE_FALG (0x00U)    /* constant-period interrupt is not generated */
#define _08_RTC_INTC_GENERATE_FLAG    (0x08U)    /* generated constant-period interrupt */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
    HALFSEC = 1U,
    ONESEC,
    ONEMIN,
    ONEHOUR,
    ONEDAY,
    ONEMONTH
}rtc_int_period_t;

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_RTC_Create(void);
void R_RTC_Start(void);
void R_RTC_Stop(void);
MD_STATUS R_RTC_Set_ConstPeriodInterruptOn(rtc_int_period_t period);
void R_RTC_Set_ConstPeriodInterruptOff(void);
static void r_rtc_callback_constperiod(void);

/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
