/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-01-26     armink       the first version
 */

#include <fal.h>

#include <gd32f5xx.h>

typedef struct gd32f5_flash
{
    rt_uint32_t sector;
    rt_uint32_t sector_base;
    rt_uint32_t sector_size;
} gd32f5_flash_t;

/**
 * Flash info
 */
const static gd32f5_flash_t gd32f5_flash_info[] =
{
    /* sector            |  base address             | sector size */
    // Bank0
    {CTL_SECTOR_NUMBER_0,  ((rt_uint32_t)0x08000000),  16  * 1024},
    {CTL_SECTOR_NUMBER_1,  ((rt_uint32_t)0x08004000),  16  * 1024},
    {CTL_SECTOR_NUMBER_2,  ((rt_uint32_t)0x08008000),  16  * 1024},
    {CTL_SECTOR_NUMBER_3,  ((rt_uint32_t)0x0800C000),  16  * 1024},
    {CTL_SECTOR_NUMBER_4,  ((rt_uint32_t)0x08010000),  64  * 1024},
    {CTL_SECTOR_NUMBER_5,  ((rt_uint32_t)0x08020000),  128 * 1024},
    {CTL_SECTOR_NUMBER_6,  ((rt_uint32_t)0x08040000),  128 * 1024},
    {CTL_SECTOR_NUMBER_7,  ((rt_uint32_t)0x08060000),  128 * 1024},
    {CTL_SECTOR_NUMBER_8,  ((rt_uint32_t)0x08080000),  128 * 1024},
    {CTL_SECTOR_NUMBER_9,  ((rt_uint32_t)0x080A0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_10, ((rt_uint32_t)0x080C0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_11, ((rt_uint32_t)0x080E0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_12, ((rt_uint32_t)0x08100000),  128 * 1024},
    {CTL_SECTOR_NUMBER_13, ((rt_uint32_t)0x08120000),  128 * 1024},
    {CTL_SECTOR_NUMBER_14, ((rt_uint32_t)0x08140000),  128 * 1024},
    {CTL_SECTOR_NUMBER_15, ((rt_uint32_t)0x08160000),  128 * 1024},
    {CTL_SECTOR_NUMBER_16, ((rt_uint32_t)0x08180000),  128 * 1024},
    {CTL_SECTOR_NUMBER_17, ((rt_uint32_t)0x081A0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_18, ((rt_uint32_t)0x081C0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_19, ((rt_uint32_t)0x081E0000),  128 * 1024},

    // Bank1
    {CTL_SECTOR_NUMBER_20, ((rt_uint32_t)0x08200000),  16  * 1024},
    {CTL_SECTOR_NUMBER_21, ((rt_uint32_t)0x08204000),  16  * 1024},
    {CTL_SECTOR_NUMBER_22, ((rt_uint32_t)0x08208000),  16  * 1024},
    {CTL_SECTOR_NUMBER_23, ((rt_uint32_t)0x0820C000),  16  * 1024},
    {CTL_SECTOR_NUMBER_24, ((rt_uint32_t)0x08210000),  64  * 1024},
    {CTL_SECTOR_NUMBER_25, ((rt_uint32_t)0x08220000),  128 * 1024},
    {CTL_SECTOR_NUMBER_26, ((rt_uint32_t)0x08240000),  128 * 1024},
    {CTL_SECTOR_NUMBER_27, ((rt_uint32_t)0x08260000),  128 * 1024},
    {CTL_SECTOR_NUMBER_28, ((rt_uint32_t)0x08280000),  128 * 1024},
    {CTL_SECTOR_NUMBER_29, ((rt_uint32_t)0x082A0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_30, ((rt_uint32_t)0x082C0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_31, ((rt_uint32_t)0x082E0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_32, ((rt_uint32_t)0x08300000),  128 * 1024},
    {CTL_SECTOR_NUMBER_33, ((rt_uint32_t)0x08320000),  128 * 1024},
    {CTL_SECTOR_NUMBER_34, ((rt_uint32_t)0x08340000),  128 * 1024},
    {CTL_SECTOR_NUMBER_35, ((rt_uint32_t)0x08360000),  128 * 1024},
    {CTL_SECTOR_NUMBER_36, ((rt_uint32_t)0x08380000),  128 * 1024},
    {CTL_SECTOR_NUMBER_37, ((rt_uint32_t)0x083A0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_38, ((rt_uint32_t)0x083C0000),  128 * 1024},
    {CTL_SECTOR_NUMBER_39, ((rt_uint32_t)0x083E0000),  128 * 1024},

    // Bank1_Ex
    {CTL_SECTOR_NUMBER_40, ((rt_uint32_t)0x08400000),  256 * 1024},
    {CTL_SECTOR_NUMBER_41, ((rt_uint32_t)0x08440000),  256 * 1024},
    {CTL_SECTOR_NUMBER_42, ((rt_uint32_t)0x08480000),  256 * 1024},
    {CTL_SECTOR_NUMBER_43, ((rt_uint32_t)0x084C0000),  256 * 1024},
    {CTL_SECTOR_NUMBER_44, ((rt_uint32_t)0x08500000),  256 * 1024},
    {CTL_SECTOR_NUMBER_45, ((rt_uint32_t)0x08540000),  256 * 1024},
    {CTL_SECTOR_NUMBER_46, ((rt_uint32_t)0x08580000),  256 * 1024},
    {CTL_SECTOR_NUMBER_47, ((rt_uint32_t)0x085C0000),  256 * 1024},
    {CTL_SECTOR_NUMBER_48, ((rt_uint32_t)0x08600000),  256 * 1024},
    {CTL_SECTOR_NUMBER_49, ((rt_uint32_t)0x08640000),  256 * 1024},
    {CTL_SECTOR_NUMBER_50, ((rt_uint32_t)0x08680000),  256 * 1024},
    {CTL_SECTOR_NUMBER_51, ((rt_uint32_t)0x086C0000),  256 * 1024},
    {CTL_SECTOR_NUMBER_52, ((rt_uint32_t)0x08700000),  256 * 1024}, 
    {CTL_SECTOR_NUMBER_53, ((rt_uint32_t)0x08740000),  256 * 1024},
};

/**
 * Get the sector of a given address
 *
 * @param address flash address
 *
 * @return The sector of a given address
 */
static rt_uint32_t gd32_get_sector(rt_uint32_t address)
{
    rt_uint32_t sector = 0;

    for (rt_uint32_t i = 0; i < sizeof(gd32f5_flash_info) / sizeof(gd32f5_flash_t); i++)
    {
        if (address >= gd32f5_flash_info[i].sector_base &&
            address < (gd32f5_flash_info[i].sector_base + gd32f5_flash_info[i].sector_size))
        {
            sector = gd32f5_flash_info[i].sector;
            break;
        }
    }

    return sector;
}

/**
 * Get the sector size
 *
 * @param sector sector
 *
 * @return sector size
 */
static rt_uint32_t gd32_get_sector_size(rt_uint32_t sector) 
{
    for (rt_uint32_t i = 0; i < sizeof(gd32f5_flash_info) / sizeof(gd32f5_flash_t); i++)
    {
        if (sector == gd32f5_flash_info[i].sector)
        {
            return gd32f5_flash_info[i].sector_size;
        }
    }
}
static int init(void)
{
    /* do nothing now */
}

static int read(long offset, rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t i;
    rt_uint32_t addr = gd32f5_onchip_flash.addr + offset;
    for (i = 0; i < size; i++, addr++, buf++)
    {
        *buf = *(rt_uint8_t *) addr;
    }

    return size;
}

static int write(long offset, const rt_uint8_t *buf, rt_size_t size)
{
    rt_size_t i;
    rt_uint32_t read_data;
    rt_uint32_t addr = gd32f5_onchip_flash.addr + offset;

    fmc_unlock();
    fmc_flag_clear(
            FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_LDECCDET | FMC_FLAG_WPERR | FMC_FLAG_PGAERR
            | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR | FMC_FLAG_RDCERR | FMC_FLAG_BUSY);
    for (i = 0; i < size; i++, buf++, addr++)
    {
        /* write data */
        fmc_byte_program(addr, *buf);
        read_data = *(rt_uint8_t *) addr;
        /* check data */
        if (read_data != *buf)
        {
            return -1;
        }
    }
    fmc_lock();

    return size;
}

static int erase(long offset, rt_size_t size)
{
    fmc_state_enum flash_status;
    rt_size_t erased_size = 0;
    rt_uint32_t cur_erase_sector;
    rt_uint32_t addr = gd32f5_onchip_flash.addr + offset;

    /* start erase */
    fmc_unlock();
    fmc_flag_clear(
            FMC_FLAG_END | FMC_FLAG_OPERR | FMC_FLAG_LDECCDET | FMC_FLAG_WPERR | FMC_FLAG_PGAERR
            | FMC_FLAG_PGMERR | FMC_FLAG_PGSERR | FMC_FLAG_RDCERR | FMC_FLAG_BUSY);
    /* it will stop when erased size is greater than setting size */
    while (erased_size < size)
    {
        cur_erase_sector = gd32_get_sector(addr + erased_size);
        flash_status = fmc_sector_erase(cur_erase_sector);
        if (flash_status != FMC_READY)
        {
            return -1;
        }
        erased_size += gd32_get_sector_size(cur_erase_sector);
    }
    fmc_lock();

    return size;
}

const struct fal_flash_dev gd32f5_onchip_flash =
{
    .name       = "gd32_onchip",
    .addr       = 0x08000000,
    .len        = 7680 * 1024,
    .blk_size   = 256 * 1024,
    .ops        = {init, read, write, erase},
    .write_gran = 8
};

