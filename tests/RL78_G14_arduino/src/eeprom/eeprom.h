/**
 * @file   eeprom.h
 * @author Michel Catudal
 * @date   31 January 2022
 * @version 0.1
 * @brief  EEPROM Driver
 *
*/

#ifndef eeprom_H
#define eeprom_H

#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
#include "r_cg_port.h"
#include "r_cg_userdefine.h"

extern uint8_t   g_iica0_master_status_flag;  /* iica0 master flag */
extern uint8_t   g_iica0_slave_status_flag;   /* iica0 slave flag */
extern uint8_t * gp_iica0_rx_address;         /* iica0 receive buffer address */
extern uint16_t  g_iica0_rx_cnt;              /* iica0 receive data length */
extern uint16_t  g_iica0_rx_len;              /* iica0 receive data count */
extern uint8_t * gp_iica0_tx_address;         /* iica0 send buffer address */
extern uint16_t  g_iica0_tx_cnt;              /* iica0 send data count */

void EE_WriteEEBlock(uint16_t start_address, uint16_t length, uint8_t const *pucBuffer);
void EE_WriteWord(uint16_t WordAddress, uint16_t Word);
void EE_WriteByte(uint16_t ByteAddress, uint8_t Byte);
void EE_ReadEEBlock(uint16_t start_address, uint16_t length, uint8_t *pucBuffer);
uint16_t EE_ReadWord(uint16_t WordAddress);
uint8_t EE_ReadByte(uint16_t ByteAddress);

#endif

