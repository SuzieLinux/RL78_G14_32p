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
* Device(s)    : R5F104ML
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements device driver for Serial module.
* Creation Date: 2/5/2022
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
extern uint8_t *gp_uart0_tx_address;         /* uart0 send buffer address */
extern uint16_t  g_uart0_tx_count;            /* uart0 send data number */
extern uint8_t *gp_uart0_rx_address;         /* uart0 receive buffer address */
extern uint16_t  g_uart0_rx_count;            /* uart0 receive data number */
extern uint16_t  g_uart0_rx_length;           /* uart0 receive data length */
extern uint8_t *gp_csi20_rx_address;         /* csi20 receive buffer address */
extern uint16_t  g_csi20_rx_length;           /* csi20 receive data length */
extern uint16_t  g_csi20_rx_count;            /* csi20 receive data count */
extern uint8_t *gp_csi20_tx_address;         /* csi20 send buffer address */
extern uint16_t  g_csi20_send_length;         /* csi20 send data length */
extern uint16_t  g_csi20_tx_count;            /* csi20 send data count */
extern uint8_t   g_iica0_master_status_flag;  /* iica0 master flag */
extern uint8_t   g_iica0_slave_status_flag;   /* iica0 slave flag */
extern uint8_t *gp_iica0_rx_address;         /* iica0 receive buffer address */
extern uint16_t  g_iica0_rx_cnt;              /* iica0 receive data length */
extern uint16_t  g_iica0_rx_len;              /* iica0 receive data count */
extern uint8_t *gp_iica0_tx_address;         /* iica0 send buffer address */
extern uint16_t  g_iica0_tx_cnt;              /* iica0 send data count */
extern uint8_t gSwitchFlag;
volatile uint8_t WriteRead_Complete = 0;
volatile int EE_status;
uint16_t _delay = 0x1FF;
/* Declare write buffer array, initialised with constant data written
   to the EEPROM each time. X is replaced with the data identifier. */
uint8_t write_buffer[] = "XXRL78G14  ";
/* Define read buffer array */
uint8_t read_buffer[] = "XXXXXXXXX";

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
* Function Name: r_csi20_interrupt
* Description  : This function is INTCSI20 interrupt service routine.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma vector = INTCSI20_vect
__interrupt static void r_csi20_interrupt(void) {
    volatile uint8_t err_type;
    volatile uint8_t sio_dummy;

    err_type = (uint8_t)(SSR10 & _0001_SAU_OVERRUN_ERROR);
    SIR10 = (uint16_t)err_type;

    if (1U == err_type) {
        r_csi20_callback_error(err_type);    /* overrun error occurs */
    } else {
        if (g_csi20_tx_count > 0U) {
            if (0U != gp_csi20_rx_address) {
                *gp_csi20_rx_address = SIO20;
                gp_csi20_rx_address++;
            } else {
                sio_dummy = SIO20;
            }

            if (0U != gp_csi20_tx_address) {
                SIO20 = *gp_csi20_tx_address;
                gp_csi20_tx_address++;
            } else {
                SIO20 = 0xFFU;
            }

            g_csi20_tx_count--;
        } else {
            if (0U == g_csi20_tx_count) {
                if (0U != gp_csi20_rx_address) {
                    *gp_csi20_rx_address = SIO20;
                } else {
                    sio_dummy = SIO20;
                }
            }

            r_csi20_callback_sendend();    /* complete send */
            r_csi20_callback_receiveend();    /* complete receive */
        }
    }
}

/***********************************************************************************************************************
* Function Name: r_csi20_callback_receiveend
* Description  : This function is a callback function when CSI20 finishes reception.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_csi20_callback_receiveend(void) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_csi20_callback_error
* Description  : This function is a callback function when CSI20 reception error occurs.
* Arguments    : err_type -
*                    error type value
* Return Value : None
***********************************************************************************************************************/
static void r_csi20_callback_error(uint8_t err_type) {
    /* Start user code. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_csi20_callback_sendend
* Description  : This function is a callback function when CSI20 finishes transmission.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
static void r_csi20_callback_sendend(void) {
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


/*******************************************************************************
* Function name : R_Master_EEPROM
* Description   : Initialises the buffer array to be manipulated on each SW1
*         press. Enters an infinite loop with SW1 presses used to write
*         data to the EEPROM slave and SW3 presses to read from the
*         EEPROM slave. After detection of switches having been
*         pressed, a comparison is conducted between the write and read
*         buffers to determine whether the read and write data matches.
* Argument  : none
* Return value  : none
*******************************************************************************/
void R_Master_EEPROM() {
    /* Configure the array location to be incremented */
    /* 1Mbit or 512Kbit EEP requires a 16/17 bit of address */
    write_buffer[0] = 0x00; /* keep adr= x0000 */
    write_buffer[1] = 0x00; /*keep adr= x0000 */

    /* Peform program infinitely */
    while (1) {
        if (R_IICA0_Busy_Check() == MD_OK) {
            /* Check if switch SW1 was pressed */
            if (gSwitchFlag == '1') {
                IIC_flg_end = 0;

                R_IICA0_Master_Send(EEPROM_DEVICE_ADDRESS,write_buffer,EEPROM_NUMB_WRITE,0);

                while (IIC_flg_end == 0) NOP();
                IIC_flg_end = 0;

                R_IICA0_StopCondition();

                /* Clear the switch press flag */
                gSwitchFlag = 0;

                /* Set flag to indicate that a write has completed */
                WriteRead_Complete |= 0x06;
            }


            /* Check if switch SW3 was pressed */
            if (gSwitchFlag == '2') {
                IIC_flg_end = 0;

                /* Set flag to indicate that a read is in progress */
                WriteRead_Complete |= 0x02;

                write_buffer[0] = 0x00; /* keep adr= x0000 */
                write_buffer[1] = 0x00; /*keep adr= x0000 */

                R_IICA0_Master_Send
                    (
                    EEPROM_DEVICE_ADDRESS,
                    write_buffer,
                    EEPROM_WORD_ADDRESS,
                    100
                    );

                while (IIC_flg_end == 0) NOP();
                IIC_flg_end = 0;

                R_IICA0_Master_Receive(EEPROM_DEVICE_ADDRESS, read_buffer, EEPROM_RECEIVE_COUNT, 0);

                while (IIC_flg_end == 0) NOP();
                IIC_flg_end = 0;

                R_IICA0_StopCondition();

                /* Set flag to indicate that a read has competed */
                WriteRead_Complete |= 0x01;

                /* Check if a write has already occured */
                if ((WriteRead_Complete & 0x04) != 0) {
                    /* Inform user of that data was
                    read from the EEPROM device */
                    EE_status = 1;
                } else {
                    EE_status = 0;
                    /* Clear the flag */
                    WriteRead_Complete &= 0xFD;
                }

                /* Clear the switch press flag */
                gSwitchFlag = 0;
            }

            /* Check if a write and a read were performed */
            if ((WriteRead_Complete & 0x07) == 0x7) {
                /* Compare the buffers using a loop */
                for (_delay = 0; _delay != EEPROM_RECEIVE_COUNT; _delay++) {
                    /* Compare the buffer locations */
                    if (write_buffer[_delay + EEPROM_WORD_ADDRESS] == read_buffer[_delay]) {
                        /* Display success message for each byte */
                        EE_status = 2;
                    } else {
                        /* Inform the user that an error occured */
                        EE_status = -1;
                        _delay = EEPROM_RECEIVE_COUNT - 1;

                    }
                }

                /* Indicate that at least one write was performed */
                WriteRead_Complete = 0x04;
            }
        }
    }
}


