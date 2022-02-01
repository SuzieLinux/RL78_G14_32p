/**
 * @file   eeprom.c
 * @author Michel Catudal
 * @date   31 January 2022
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

/*! The I2C address is fixed for the AT24C32 device. */
#define AT24C32_ADDRESS 0xA0

static uint8_t TX_done = 0;
static uint8_t RX_done = 0;
static MD_STATUS RX_TX_error = 0;

/*****************************************************************************
 *      @brief   Write a block of 1 to 32 bytes
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to write
 *      @param[in] Pointer to buffer
 *
 *      @return None
*/
void EE_WriteEEBlock(uint16_t start_address, uint16_t length, uint8_t const *pucBuffer)
{
    uint8_t pack[34];
    MD_STATUS status;

    P6_bit.no2 = 0;     //  Remove EEPROM Write Protect

    if (!length)
    {
        return;
    }
    if (length > 32)
    {
        length = 32;     // Maximum size of a page is 32 bytes
    }

    pack[0] = start_address >> 8;
    pack[1] = start_address & 0xFF;
    memcpy(&pack[2], pucBuffer, length);

    TX_done = 0;
    status = R_IICA0_Master_Send(AT24C32_ADDRESS, pack, length + 2, 15);

    if (status == MD_OK)
    {
        while (!TX_done);
        TX_done = 0;
    }
}

/*****************************************************************************
 *      @brief   Write a two bytes word
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Word to write
 *
 *      @return None
*/
void EE_WriteWord(uint16_t WordAddress, uint16_t Word)
{
    uint8_t pack[4];
    MD_STATUS status;

    P6_bit.no2 = 0;     //  Remove EEPROM Write Protect

    pack[0] = WordAddress >> 8;
    pack[1] = WordAddress & 0xFF;
    pack[2] = Word & 0xFF;
    pack[3] = Word >> 8;

    TX_done = 0;
    status = R_IICA0_Master_Send(AT24C32_ADDRESS, pack, 4, 15);

    if (status == MD_OK)
    {
        while (!TX_done);
        TX_done = 0;
    }
}

/*****************************************************************************
 *      @brief   Write a byte
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Byte to write
 *
 *      @return None
*/
void EE_WriteByte(uint16_t ByteAddress, uint8_t Byte)
{
    uint8_t pack[3];
    MD_STATUS status;

    P6_bit.no2 = 0;     //  Remove EEPROM Write Protect

    pack[0] = ByteAddress >> 8;
    pack[1] = ByteAddress & 0xFF;
    pack[2] = Byte;

    TX_done = 0;
    status = R_IICA0_Master_Send(AT24C32_ADDRESS, pack, 3, 15);

    if (status == MD_OK)
    {
        while (!TX_done);
        TX_done = 0;
    }
}

/*****************************************************************************
 *      @brief   Reading a block of 1 to 32 bytes
 *
 *      @param[in] Address in EEPROM
 *      @param[in] Size of data to read
 *      @param[in] Pointer to buffer
 *
 *      @return MD_OK or MD_ERROR1 or MD_ERROR2
*/
MD_STATUS EE_ReadEEBlock(uint16_t start_address, uint16_t length, uint8_t *pucBuffer)
{
    uint8_t pack[32];
    MD_STATUS status;

    if (!length)
    {
        return MD_ERROR;
    }
    if (length > 32)
    {
        length = 32;     // Maximum size of a page is 32 bytes
    }

    pack[0] = start_address >> 8;
    pack[1] = start_address & 0xFF;

    TX_done = 0;
    status = R_IICA0_Master_Send(AT24C32_ADDRESS, pack, 2, 15);

    if (status == MD_OK)
    {
        while (!TX_done);
        TX_done = 0;
    }
    else
    {
        return MD_ERROR;
    }

    RX_done = 0;
    /* Receive the data */
    status = R_IICA0_Master_Receive(AT24C32_ADDRESS | 0x01,pack,length,15);

    if (status == MD_OK)
    {
        while (!TX_done);
        RX_done = 0;
    }

    return MD_OK;
}

/*****************************************************************************
 *      @brief   Reading a two bytes word
 *
 *      @param[in] Address in EEPROM
 *
 *      @return word read
*/
uint16_t EE_ReadWord(uint16_t WordAddress)
{
    uint8_t pack[34];
    uint16_t Word;
    MD_STATUS status;

    pack[0] = WordAddress >> 8;
    pack[1] = WordAddress & 0xFF;

    TX_done = 0;
    status = R_IICA0_Master_Send(AT24C32_ADDRESS,(uint8_t *) &WordAddress, 2, 15);

    if (status == MD_OK)
    {
        while (!TX_done);
        TX_done = 0;
    }
    else
    {
        return 0;
    }

    RX_done = 0;
    /* Receive the data */
    status = R_IICA0_Master_Receive(AT24C32_ADDRESS | 0x01,(uint8_t *) &Word,2,15);

    if (status == MD_OK)
    {
        while (!TX_done);
        TX_done = 0;
    }

    return Word;
}

/*****************************************************************************
 *      @brief   Reading a byte
 *
 *      @param[in] Address in EEPROM
 *
 *      @return word read
*/
uint8_t EE_ReadByte(uint16_t ByteAddress)
{
    uint8_t pack[34];
    uint8_t Byte;
    MD_STATUS status;

    pack[0] = ByteAddress >> 8;
    pack[1] = ByteAddress & 0xFF;

    TX_done = 0;
    status = MD_STATUS R_IICA0_Master_Send(AT24C32_ADDRESS, &ByteAddress, 2, 15);

    if (status == MD_OK)
    {
        while (!TX_done);
        TX_done = 0;
    }
    else
    {
        return 0;
    }

    RX_done = 0;
    /* Receive the data */
    status = R_IICA0_Master_Receive(AT24C32_ADDRESS | 0x01,&Byte,1,15);

    if (status == MD_OK)
    {
        while (!TX_done);
        TX_done = 0;
    }

    return Byte;
}

