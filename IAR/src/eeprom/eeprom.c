/**
 * @file   eeprom.c
 * @author Michel Catudal
 * @date   2 February 2022
 * @version 0.1
 * @brief  EEPROM Driver
 *
*/

#include "r_cg_macrodriver.h"
#include "r_cg_serial.h"
#include "r_cg_port.h"
#include "r_cg_userdefine.h"
#include "eeprom.h"
#include <string.h>

extern uint8_t IIC_flg_end;

/*****************************************************************************
 *      @brief   Write a block to 4kb or 8kb devices
 *               Page size for AT24C32 or AT24C64 is 32 bytes
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to write
 *      @param[in] Pointer to buffer
 *      @param[in] Device used 0 to 7, 8 possible devices (A2 A1 A0)
 *
 *      @return None
*/
void EE_WriteBlock8kb(uint16_t start_address, uint8_t len, uint8_t const *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[34];
    uint8_t adr = 0xA0 | (Device & 0x0F);

    if (!len) {
        return;
    }
    if (len > 32) {
        len = 32;     // Maximum size of a page is 32 bytes
    }

    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;
    memcpy(&write_buffer[2], pucBuffer, len);

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr, write_buffer, len + 2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Write a block to 16kb or 32kb devices
 *               Page size for AT24C128 or AT24C256 is 64 bytes
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to write
 *      @param[in] Pointer to buffer
 *      @param[in] Device used 0 to 7, 8 possible devices (A2 A1 A0)  (A2 A1 A0)
 *
 *      @return None
*/
void EE_WriteBlock32kb(uint16_t start_address, uint8_t len, uint8_t const *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[34];
    uint8_t adr = 0xA0 | (Device & 0x0F);

    if (!len) {
        return;
    }
    if (len > 64) {
        len = 64;     // Maximum size of a page is 64 bytes
    }

    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;
    memcpy(&write_buffer[2], pucBuffer, len);

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr, write_buffer, len + 2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Write a block to 64kb devices
 *               Page size for M24512 is 128 bytes
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to write
 *      @param[in] Pointer to buffer
 *      @param[in] Device used 0 to 7, 8 possible devices (A2 A1 A0)
 *
 *      @return None
*/
void EE_WriteBlock64kb(uint16_t start_address, uint8_t len, uint8_t const *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[34];
    uint8_t adr = 0xA0 | (Device & 0x0F);

    if (!len) {
        return;
    }
    if (len > 128) {
        len = 128;     // Maximum size of a page is 128 bytes
    }

    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;
    memcpy(&write_buffer[2], pucBuffer, len);

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr, write_buffer, len + 2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Write a block to 128kb devices
 *               Page size for BR24G1MFJ is 256 bytes
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to write
 *      @param[in] Pointer to buffer
 *      @param[in] Device used 0 to 3, 4 possible devices  (A2 A1)
 *
 *      @return None
*/
void EE_WriteBlock128kb(uint32_t start_address, uint16_t len, uint8_t const *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[34];
    uint8_t adr;

    if (!len) {
        return;
    }
    if (len > 256) {
        len = 256;     // Maximum size of a page is 128 bytes
    }

    adr = ((Device & 3) << 1) | 0xA0;
    /* upper address bit is in bit 0 of I2C device address */
    adr |= ((start_address >> 16) & 1);
    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;
    memcpy(&write_buffer[2], pucBuffer, len);

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr, write_buffer, len + 2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Write a block to 256kb devices
 *               Page size for M24M02 is 256 bytes
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to write
 *      @param[in] Pointer to buffer
 *      @param[in] Device used 0 to 3, 2 possible devices  (A2)
 *
 *      @return None
*/
void EE_WriteBlock256kb(uint32_t start_address, uint16_t len, uint8_t const *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[34];
    uint8_t adr;

    if (!len) {
        return;
    }
    if (len > 256) {
        len = 256;     // Maximum size of a page is 128 bytes
    }

    adr = ((Device & 1) << 2) | 0xA0;
    /* upper address 2 bits are in bit 0 and 1 of I2C device address */
    adr |= ((start_address >> 16) & 3);
    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;
    memcpy(&write_buffer[2], pucBuffer, len);

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr, write_buffer, len + 2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}


/*****************************************************************************
 *      @brief   Write a byte to devices up to 64kb
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Byte to write
 *      @param[in] Device used 0 to 7, 8 possible devices (A2 A1 A0)
 *
 *      @return None
*/
void EE_WriteByte64kb(uint16_t ByteAddress, uint8_t Byte, uint8_t Device) {
    uint8_t write_buffer[3];
    uint8_t adr = 0xA0 | (Device & 0x0F);

    write_buffer[0] = ByteAddress >> 8;
    write_buffer[1] = ByteAddress & 0xFF;
    write_buffer[2] = Byte;

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr, write_buffer, 3);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Write a byte to 128kb devices
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Byte to write
 *      @param[in] Device used 0 to 3, 4 possible devices  (A2 A1)
 *
 *      @return None
*/
void EE_WriteByte128kb(uint16_t ByteAddress, uint8_t Byte, uint8_t Device) {
    uint8_t write_buffer[3];
    uint8_t adr;

    adr = ((Device & 3) << 1) | 0xA0;
    /* upper address bit is in bit 0 of I2C device address */
    adr |= ((start_address >> 16) & 1);
    write_buffer[0] = ByteAddress >> 8;
    write_buffer[1] = ByteAddress & 0xFF;
    write_buffer[2] = Byte;

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr, write_buffer, 3);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Write a byte to 256kb devices
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Byte to write
 *      @param[in] Device used 0 to 3, 2 possible devices  (A2)
 *
 *      @return None
*/
void EE_WriteByte256kb(uint16_t ByteAddress, uint8_t Byte, uint8_t Device) {
    uint8_t write_buffer[3];
    uint8_t adr;

    adr = ((Device & 1) << 2) | 0xA0;
    /* upper address 2 bits are in bit 0 and 1 of I2C device address */
    adr |= ((start_address >> 16) & 3);
    write_buffer[0] = ByteAddress >> 8;
    write_buffer[1] = ByteAddress & 0xFF;
    write_buffer[2] = Byte;

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr, write_buffer, 3);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Reading a block of data from a device up to 64kb
 *               Trying to read past the size of the device will give strange results
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to read
 *      @param[in] Pointer to buffer
 *      @param[in] Device used 0 to 7, 8 possible devices (A2 A1 A0)
 *
 *      @return MD_OK or MD_ERROR1 or MD_ERROR2
*/
void EE_ReadBlock64kb(uint16_t start_address, uint16_t len, uint8_t *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[2];
    uint8_t adr = 0xA0 | (Device & 0x0F);

    if (len > (64 * 1024)) return;
    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr,write_buffer,2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_Master_Receive(adr, pucBuffer, len);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Reading a block of data from a 128kb device
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to read
 *      @param[in] Pointer to buffer
 *      @param[in] Device used 0 to 3, 4 possible devices  (A2 A1)
 *
 *      @return MD_OK or MD_ERROR1 or MD_ERROR2
*/
void EE_ReadBlock128kb(uint32_t start_address, uint32_t len, uint8_t *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[2];
    uint8_t adr;

    adr = ((Device & 3) << 1) | 0xA0;
    /* upper address bit is in bit 0 of I2C device address */
    adr |= ((start_address >> 16) & 1);
    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr,write_buffer,2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_Master_Receive(adr, pucBuffer, len);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Reading a block of data from a 256kb device
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to read
 *      @param[in] Pointer to buffer
 *      @param[in] Device used 0 to 3, 2 possible devices  (A2)
 *
 *      @return None
*/
void EE_ReadBlock256kb(uint32_t start_address, uint32_t len, uint8_t *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[2];
    uint8_t adr;

    adr = ((Device & 1) << 2) | 0xA0;
    /* upper address 2 bits are in bit 0 and 1 of I2C device address */
    adr |= ((start_address >> 16) & 3);
    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr,write_buffer,2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_Master_Receive(adr, pucBuffer, len);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Reading a byte from a device up to 64kb
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Device used 0 to 7, 8 possible devices (A2 A1 A0)
 *
 *      @return Byte read
*/
uint8_t EE_ReadByte64kb(uint16_t start_address, uint8_t Device) {
    uint8_t write_buffer[2];
    uint8_t adr = 0xA0 | (Device & 0x0F);
    uint8_t Byte;

    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr,write_buffer,2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_Master_Receive(adr, &Byte, 1);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
    return Byte;
}

/*****************************************************************************
 *      @brief   Reading a byte from a 128kb device
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Device used 0 to 3, 4 possible devices  (A2 A1)
 *
 *      @return Byte read
*/
void EE_ReadEEBlock128kb(uint32_t start_address, uint32_t len, uint8_t *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[2];
    uint8_t adr;

    adr = ((Device & 3) << 1) | 0xA0;
    /* upper address bit is in bit 0 of I2C device address */
    adr |= ((start_address >> 16) & 1);
    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr,write_buffer,2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_Master_Receive(adr, pucBuffer, len);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

/*****************************************************************************
 *      @brief   Reading a byte from a 256kb device
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Device used 0 to 3, 2 possible devices  (A2)
 *
 *      @return Byte read
*/
void EE_ReadEEBlock256kb(uint32_t start_address, uint32_t len, uint8_t *pucBuffer, uint8_t Device) {
    uint8_t write_buffer[2];
    uint8_t adr;

    adr = ((Device & 1) << 2) | 0xA0;
    /* upper address 2 bits are in bit 0 and 1 of I2C device address */
    adr |= ((start_address >> 16) & 3);
    write_buffer[0] = start_address >> 8;
    write_buffer[1] = start_address & 0xFF;

    IIC_flg_end = 0;

    R_IICA0_Master_Send(adr,write_buffer,2);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_Master_Receive(adr, pucBuffer, len);

    while (IIC_flg_end == 0) NOP();
    IIC_flg_end = 0;

    R_IICA0_StopCondition();
}

