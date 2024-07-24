
#include "studio_crc.h"

#include <zlib.h>      // 引入zlib库进行CRC32校验



bool studio_crc::verifyCRC32(const char* data, size_t dataSize, unsigned int crc32_recv)
{
    // 验证响应数据是否足够包含文件大小和CRC32校验值
    if (!data)
    {
        std::cout << "data is empty " << std::endl;
        return false;
    }

    // 计算CRC32
    unsigned int crc32_calc = crc32(0L, Z_NULL, 0);
    crc32_calc = crc32(crc32_calc, (const Bytef*)data, dataSize);
    printf("Src crc32: %u calculate crc32: %u \n", crc32_recv, crc32_calc);
    // 比较并返回校验结果
    if (crc32_recv == crc32_calc)
    {
        std::cout << "CRC32 check success" << std::endl;
        return true;  
    }
    else
    {
        std::cout << "CRC32 check fail" << std::endl;
        return false;  
    }
}



bool studio_crc::verifyCRC16(uint8_t* data, uint16_t dataSize, uint16_t crc16_recv)
{
    uint8_t crc_hi = 0xFF; /*已初始化高CRC字节*/
    uint8_t crc_lo = 0xFF; /*低CRC字节已初始化*/
    unsigned int i;        /*将索引到CRC查找中*/

    /* pass through message data */
    while (dataSize--)
    {
        i = crc_hi ^ *data++; /* calculate the CRC  */
        crc_hi = crc_lo ^ table_crc_hi[i];
        crc_lo = table_crc_lo[i];
    }
    uint16_t res_crc = (crc_hi << 8 | crc_lo);

    // 比较并返回校验结果
    if (res_crc == crc16_recv)
    {
        std::cout << "CRC16 check success" << std::endl;
        return true;  
    }
    else
    {
        std::cout << "CRC16 check fail" << std::endl;
        return false;  
    }
}



