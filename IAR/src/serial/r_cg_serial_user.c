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
* Creation Date: 1/31/2022
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern uint8_t *gp_uart0_tx_address;         /* uart0 send buffer address */
extern uint16_t  g_uart0_tx_count;            /* uart0 send data number */
extern uint8_t *gp_uart0_rx_address;         /* uart0 receive buffer address */
extern uint16_t  g_uart0_rx_count;            /* uart0 receive data number */
extern uint16_t  g_uart0_rx_length;           /* uart0 receive data length */
extern uint8_t *gp_uart1_tx_address;         /* uart1 send buffer address */
extern uint16_t  g_uart1_tx_count;            /* uart1 send data number */
extern uint8_t *gp_uart1_rx_address;         /* uart1 receive buffer address */
extern uint16_t  g_uart1_rx_count;            /* uart1 receive data number */
extern uint16_t  g_uart1_rx_length;           /* uart1 receive data length */
extern uint8_t   g_iica0_master_status_flag;  /* iica0 master flag */
extern uint8_t   g_iica0_slave_status_flag;   /* iica0 slave flag */
extern uint8_t *gp_iica0_rx_address;         /* iica0 receive buffer address */
extern uint16_t  g_iica0_rx_cnt;              /* iica0 receive data length */
extern uint16_t  g_iica0_rx_len;              /* iica0 receive data count */
extern uint8_t *gp_iica0_tx_address;         /* iica0 send buffer address */
extern uint16_t  g_iica0_tx_cnt;              /* iica0 send data count */
volatile uint8_t WriteRead_Complete = 0;
volatile int EE_status;
uint16_t _delay = 0x1FF;
/* Declare write buffer array, initialised with constant data written
   to the EEPROM each time. X is replaced with the data identifier. */
uint8_t write_buffer[] = "XXRL78G14  ";
/* Define read buffer array */
uint8_t read_buffer[] = "XXXXXXXXX";
uint8_t IIC_flg_end = 0;

/***********************************************************************************************************************
* Function Name: r_uart0_interrupt_receive
* Description  : This function is INTSR0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTSR0_vect
__interrupt static void r_uart0_interrupt_receive(void) {
    volatile uint8_t rx_data;
    volatile uint8_t err_type;

    err_type = (uint8_t)(SSR01 & 0x0007U);
    SIR01 = (uint16_t)err_type;

    if (err_type != 0U) {
        r_uart0_callback_error(err_type);
    }

    rx_data = RXD0;

    if (g_uart0_rx_length > g_uart0_rx_count) {
        *gp_uart0_rx_address = rx_data;
        gp_uart0_rx_address++;
        g_uart0_rx_count++;

        if (g_uart0_rx_length == g_uart0_rx_count) {
            r_uart0_callback_receiveend();
        }
    } else {
        r_uart0_callback_softwareoverrun(rx_data);
    }
}

/***********************************************************************************************************************
* Function Name: r_uart0_interrupt_send
* Description  : This function is INTST0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTST0_vect
__interrupt static void r_uart0_interrupt_send(void) {
    if (g_uart0_tx_count > 0U) {
        TXD0 = *gp_uart0_tx_address;
        gp_uart0_tx_address++;
        g_uart0_tx_count--;
    } else {
        r_uart0_callback_sendend();
    }
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_receiveend
* Description  : This function is a callback function when UART0 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_receiveend(void) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_softwareoverrun
* Description  : This function is a callback function when UART0 receives an overflow data.
* Arguments    : rx_data -
*                    receive data
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_softwareoverrun(uint16_t rx_data) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_sendend
* Description  : This function is a callback function when UART0 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_sendend(void) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart0_callback_error
* Description  : This function is a callback function when UART0 reception error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_uart0_callback_error(uint8_t err_type) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart1_interrupt_receive
* Description  : This function is INTSR1 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTSR1_vect
__interrupt static void r_uart1_interrupt_receive(void) {
    volatile uint8_t rx_data;
    volatile uint8_t err_type;

    err_type = (uint8_t)(SSR03 & 0x0007U);
    SIR03 = (uint16_t)err_type;

    if (err_type != 0U) {
        r_uart1_callback_error(err_type);
    }

    rx_data = RXD1;

    if (g_uart1_rx_length > g_uart1_rx_count) {
        *gp_uart1_rx_address = rx_data;
        gp_uart1_rx_address++;
        g_uart1_rx_count++;

        if (g_uart1_rx_length == g_uart1_rx_count) {
            r_uart1_callback_receiveend();
        }
    } else {
        r_uart1_callback_softwareoverrun(rx_data);
    }
}

/***********************************************************************************************************************
* Function Name: r_uart1_interrupt_send
* Description  : This function is INTST1 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTST1_vect
__interrupt static void r_uart1_interrupt_send(void) {
    if (g_uart1_tx_count > 0U) {
        TXD1 = *gp_uart1_tx_address;
        gp_uart1_tx_address++;
        g_uart1_tx_count--;
    } else {
        r_uart1_callback_sendend();
    }
}

/***********************************************************************************************************************
* Function Name: r_uart1_callback_receiveend
* Description  : This function is a callback function when UART1 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart1_callback_receiveend(void) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart1_callback_softwareoverrun
* Description  : This function is a callback function when UART1 receives an overflow data.
* Arguments    : rx_data -
*                    receive data
* Return Value : None
***********************************************************************************************************************/
static void r_uart1_callback_softwareoverrun(uint16_t rx_data) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart1_callback_sendend
* Description  : This function is a callback function when UART1 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_uart1_callback_sendend(void) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_uart1_callback_error
* Description  : This function is a callback function when UART1 reception error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_uart1_callback_error(uint8_t err_type) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_iica0_interrupt
* Description  : This function is INTIICA0 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTIICA0_vect
__interrupt static void r_iica0_interrupt(void) {
    if ((IICS0 & _80_IICA_STATUS_MASTER) == 0x80U) {
        iica0_master_handler();
    }
}

/***********************************************************************************************************************
* Function Name: iica0_master_handler
* Description  : This function is IICA0 master handler.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void iica0_master_handler(void) {
    /* Control for communication */
    if ((0U == IICBSY0) && (g_iica0_tx_cnt != 0U)) {
        r_iica0_callback_master_error(MD_SPT);
    }
    /* Control for sended address */
    else {
        if ((g_iica0_master_status_flag & _80_IICA_ADDRESS_COMPLETE) == 0U) {
            if (1U == ACKD0) {
                g_iica0_master_status_flag |= _80_IICA_ADDRESS_COMPLETE;

                if (1U == TRC0) {
                    WTIM0 = 1U;

                    if (g_iica0_tx_cnt > 0U) {
                        IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    } else {
                        r_iica0_callback_master_sendend();
                    }
                } else {
                    ACKE0 = 1U;
                    WTIM0 = 0U;
                    WREL0 = 1U;
                }
            } else {
                r_iica0_callback_master_error(MD_NACK);
            }
        } else {
            /* Master send control */
            if (1U == TRC0) {
                if ((0U == ACKD0) && (g_iica0_tx_cnt != 0U)) {
                    r_iica0_callback_master_error(MD_NACK);
                } else {
                    if (g_iica0_tx_cnt > 0U) {
                        IICA0 = *gp_iica0_tx_address;
                        gp_iica0_tx_address++;
                        g_iica0_tx_cnt--;
                    } else {
                        r_iica0_callback_master_sendend();
                    }
                }
            }
            /* Master receive control */
            else {
                if (g_iica0_rx_cnt < g_iica0_rx_len) {
                    *gp_iica0_rx_address = IICA0;
                    gp_iica0_rx_address++;
                    g_iica0_rx_cnt++;

                    if (g_iica0_rx_cnt == g_iica0_rx_len) {
                        ACKE0 = 0U;
                        WTIM0 = 1U;
                        WREL0 = 1U;
                    } else {
                        WREL0 = 1U;
                    }
                } else {
                    r_iica0_callback_master_receiveend();
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_iica0_callback_master_error
* Description  : This function is a callback function when IICA0 master error occurs.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iica0_callback_master_error(MD_STATUS flag) {
}

/***********************************************************************************************************************
* Function Name: r_iica0_callback_master_receiveend
* Description  : This function is a callback function when IICA0 finishes master reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iica0_callback_master_receiveend(void) {
    IIC_flg_end = 1;
}

/***********************************************************************************************************************
* Function Name: r_iica0_callback_master_sendend
* Description  : This function is a callback function when IICA0 finishes master transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_iica0_callback_master_sendend(void) {
    IIC_flg_end = 1;
}


