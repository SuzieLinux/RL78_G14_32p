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

/* IC devices supported */
#define EE_4kb   0     /* AT24C32 */
#define EE_8kb   1     /* AT24C64 */
#define EE_16kb  2     /* AT24C128 */
#define EE_32kb  3     /* AT24C256 */
#define EE_64kb  4     /* M24512 */
#define EE_128kb 5     /* M24M01 or BR24G1MFJ */
#define EE_256kb 6     /* M24M02 */

extern uint8_t   g_iica0_master_status_flag;  /* iica0 master flag */
extern uint8_t   g_iica0_slave_status_flag;   /* iica0 slave flag */
extern uint8_t * gp_iica0_rx_address;         /* iica0 receive buffer address */
extern uint16_t  g_iica0_rx_cnt;              /* iica0 receive data length */
extern uint16_t  g_iica0_rx_len;              /* iica0 receive data count */
extern uint8_t * gp_iica0_tx_address;         /* iica0 send buffer address */
extern uint16_t  g_iica0_tx_cnt;              /* iica0 send data count */

void EE_WriteBlock8kb(uint16_t start_address, uint8_t len, uint8_t const *pucBuffer, uint8_t Device);
void EE_WriteBlock32kb(uint16_t start_address, uint8_t len, uint8_t const *pucBuffer, uint8_t Device);
void EE_WriteBlock64kb(uint16_t start_address, uint8_t len, uint8_t const *pucBuffer, uint8_t Device);
void EE_WriteBlock128kb(uint32_t start_address, uint16_t len, uint8_t const *pucBuffer, uint8_t Device);
void EE_WriteBlock256kb(uint32_t start_address, uint16_t len, uint8_t const *pucBuffer, uint8_t Device);
void EE_WriteByte64kb(uint16_t ByteAddress, uint8_t Byte, uint8_t Device);
void EE_WriteByte128kb(uint16_t ByteAddress, uint8_t Byte, uint8_t Device);
void EE_WriteByte256kb(uint16_t ByteAddress, uint8_t Byte, uint8_t Device);
void EE_ReadBlock64kb(uint16_t start_address, uint16_t len, uint8_t *pucBuffer, uint8_t Device);
void EE_ReadBlock128kb(uint32_t start_address, uint32_t len, uint8_t *pucBuffer, uint8_t Device);
void EE_ReadBlock256kb(uint32_t start_address, uint32_t len, uint8_t *pucBuffer, uint8_t Device);
uint8_t EE_ReadByte64kb(uint16_t start_address, uint8_t Device);
void EE_ReadByte128kb(uint32_t start_address, uint32_t len, uint8_t *pucBuffer, uint8_t Device);
void EE_ReadByte256kb(uint32_t start_address, uint32_t len, uint8_t *pucBuffer, uint8_t Device);

#endif

