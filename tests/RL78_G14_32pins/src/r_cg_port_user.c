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
* File Name    : r_cg_port_user.c
* Version      : Applilet3 for RL78/G14 V2.05.05.01 [25 Nov 2020]
* Device(s)    : R5F104BG
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for PORT module.
* Creation Date: 2/9/2022
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_port.h"
#include "r_cg_userdefine.h"


inline void uart_time_delay(void)
{
    NOP();
}

#define Tx_Pin P0.bit.no1

void uart_tx_bit_bang(unsigned char val)
{
    unsigned char i;
    Tx_Pin = 0;                         // Start bit
    uart_time_delay();
    for (i = 8; i != 0; --i)
    {
        if (val & 1) Tx_Pin = 1;   // Begin with LSB
        else         Tx_Pin = 0;
        val >>= 1;
        uart_time_delay();
    }
    Tx_Pin = 1;                         // Stop bit
    uart_time_delay();
}


