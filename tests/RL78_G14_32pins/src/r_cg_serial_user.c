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
* File Name    : r_cg_serial_user.c
* Version      : Applilet3 for RL78/G14 V2.05.05.01 [25 Nov 2020]
* Device(s)    : R5F104BG
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for Serial module.
* Creation Date: 2/4/2022
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern uint8_t   g_iic20_master_status_flag;  /* iic20 start flag for send address check by master mode */
extern uint8_t * gp_iic20_tx_address;         /* iic20 send data pointer by master mode */
extern uint16_t  g_iic20_tx_count;            /* iic20 send data size by master mode */
extern uint8_t * gp_iic20_rx_address;         /* iic20 receive data pointer by master mode */
extern uint16_t  g_iic20_rx_count;            /* iic20 receive data size by master mode */
extern uint16_t  g_iic20_rx_length;           /* iic20 receive data length by master mode */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: r_iic20_interrupt
* Description  : This function is INTIIC20 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTIIC20_vect
__interrupt static void r_iic20_interrupt(void)
{
    volatile uint16_t w_count;

    for (w_count = 0U; w_count <= IIC20_WAITTIME_2; w_count++)
    {
        NOP();
    }

    if (((SSR10 & _0002_SAU_PARITY_ERROR) == 0x0002U) && (g_iic20_tx_count != 0U))
    {
        r_iic20_callback_master_error(MD_NACK);
    }
    else if(((SSR10 & _0001_SAU_OVERRUN_ERROR) == 0x0001U) && (g_iic20_tx_count != 0U))
    {
        r_iic20_callback_master_error(MD_OVERRUN);
    }
    else
    {
        /* Control for master send */
        if ((g_iic20_master_status_flag & _01_SAU_IIC_SEND_FLAG) == 1U)
        {
            if (g_iic20_tx_count > 0U)
            {
                SIO20 = *gp_iic20_tx_address;
                gp_iic20_tx_address++;
                g_iic20_tx_count--;
            }
            else
            {
                /* IIC master transmission finishes and a callback function can be called here. */
                r_iic20_callback_master_sendend();
            }
        }
        /* Control for master receive */
        else 
        {
            if ((g_iic20_master_status_flag & _04_SAU_IIC_SENDED_ADDRESS_FLAG) == 0U)
            {
                ST1 |= _0001_SAU_CH0_STOP_TRG_ON;
                SCR10 &= ~_C000_SAU_RECEPTION_TRANSMISSION;
                SCR10 |= _4000_SAU_RECEPTION;
                SS1 |= _0001_SAU_CH0_START_TRG_ON;
                g_iic20_master_status_flag |= _04_SAU_IIC_SENDED_ADDRESS_FLAG;
                
                if (g_iic20_rx_length == 1U)
                {
                    SOE1 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable IIC20 out */
                }
                
                SIO20 = 0xFFU;
            }
            else
            {
                if (g_iic20_rx_count < g_iic20_rx_length)
                {
                    *gp_iic20_rx_address = SIO20;
                    gp_iic20_rx_address++;
                    g_iic20_rx_count++;
                    
                    if (g_iic20_rx_count == (g_iic20_rx_length - 1U))
                    {
                        SOE1 &= ~_0001_SAU_CH0_OUTPUT_ENABLE;    /* disable IIC20 out */
                        SIO20 = 0xFFU;
                    }
                    else if (g_iic20_rx_count == g_iic20_rx_length)
                    {
                        /* IIC master reception finishes and a callback function can be called here. */
                        r_iic20_callback_master_receiveend();
                    }
                    else
                    {
                        SIO20 = 0xFFU;
                    }
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_iic20_callback_master_error
* Description  : This function is a callback function when IIC20 master error occurs.
* Arguments    : flag -
*                    status flag
* Return Value : None
***********************************************************************************************************************/
static void r_iic20_callback_master_error(MD_STATUS flag)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_iic20_callback_master_receiveend
* Description  : This function is a callback function when IIC20 finishes master reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iic20_callback_master_receiveend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_iic20_callback_master_sendend
* Description  : This function is a callback function when IIC20 finishes master transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iic20_callback_master_sendend(void)
{
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
