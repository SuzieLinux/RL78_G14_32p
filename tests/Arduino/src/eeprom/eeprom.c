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

/*! The I2C address is fixed for the AT24C32 device. */
#define AT24C32_ADDRESS 0xA0

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

    R_IICA0_Master_Send(AT24C32_ADDRESS, pack, length + 2);
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

    pack[0] = WordAddress >> 8;
    pack[1] = WordAddress & 0xFF;
    pack[2] = Word & 0xFF;
    pack[3] = Word >> 8;

    R_IICA0_Master_Send(AT24C32_ADDRESS, pack, 4);
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

    pack[0] = ByteAddress >> 8;
    pack[1] = ByteAddress & 0xFF;
    pack[2] = Byte;

    R_IICA0_Master_Send(AT24C32_ADDRESS, pack, 3);
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
void EE_ReadEEBlock(uint16_t start_address, uint16_t length, uint8_t *pucBuffer)
{
    uint8_t pack[32];

    pack[0] = start_address >> 8;
    pack[1] = start_address & 0xFF;

    R_IICA0_Master_Send(AT24C32_ADDRESS, pack, 2);
    /* Wait to receive IIC reply from the EEP */
    while(R_IICA0_Master_Receive(AT24C32_ADDRESS, pucBuffer, length) != MD_OK);

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
    uint16_t Word;

    R_IICA0_Master_Send(AT24C32_ADDRESS,(uint8_t *) &WordAddress, 2);

    /* Wait to receive IIC reply from the EEP */
    while(R_IICA0_Master_Receive(AT24C32_ADDRESS, (uint8_t *) &Word, 2) != MD_OK);

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
    uint8_t Byte;

    R_IICA0_Master_Send(AT24C32_ADDRESS,(uint8_t *) &ByteAddress, 2);

    /* Wait to receive IIC reply from the EEP */
    while(R_IICA0_Master_Receive(AT24C32_ADDRESS, (uint8_t *) &Byte, 1) != MD_OK);

    return Byte;
}

