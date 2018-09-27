/***********************************************************************************************************************
 * DISCLAIMER
 * This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
 * No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all 
 * applicable laws, including copyright laws. 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
 * THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM 
 * EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES 
 * SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO 
 * THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 * Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of 
 * this software. By using this software, you agree to the additional terms and conditions found by accessing the 
 * following link:
 * http://www.renesas.com/disclaimer 
 *
 * Copyright (C) 2016 Renesas Electronics Corporation. All rights reserved.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name    : r_riic_rx65n.c
 * Description  : Functions for using RIIC on RX devices. 
 **********************************************************************************************************************/
/**********************************************************************************************************************
 * History : DD.MM.YYYY Version  Description
 *         : 01.10.2016 2.00     First Release
 *         : 02.06.2017 2.10     Corrected macro definitions of riic_mcu_mpc_enable() and riic_mcu_mpc_disable().
 *                               Changed include path because changed file structure.
 *                               Changed about the calculation processing for address of PFS, PCR, 
 *                               PDR and PMR register.
 *         : 31.08.2017 2.20     Changed definitions of Channel 1 for RX65N ROM 2M.
 **********************************************************************************************************************/

/***********************************************************************************************************************
 Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
/* Defines for RIIC support */
#include "r_riic_rh850f1x_if.h"
#include <standardports_p.h>
/* Check MCU Group */
#if defined(BSP_MCU_RH850F1X)

    #include "r_riic_rh850f1x_private.h"

/***********************************************************************************************************************
 Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/
/* Array of bit rate for RIICn (n=0, 1 or 2) */
const uint16_t g_riic_bps[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CFG_CH0_kBPS,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CFG_CH1_kBPS,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CFG_CH2_kBPS
#endif
};

/* Array of data of Slave Address 0 Register (SARL0 and SARU0) for RIICn (n=0, 1 or 2) */
const uint16_t g_riic_slv_ad0_val[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CFG_CH0_SLV_ADDR0,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CFG_CH1_SLV_ADDR0,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CFG_CH2_SLV_ADDR0
#endif
};

/* Array of data of Slave Address 1 Register (SARL1 and SARU1) for RIICn (n=0, 1 or 2) */
const uint16_t g_riic_slv_ad1_val[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CFG_CH0_SLV_ADDR1,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CFG_CH1_SLV_ADDR1,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CFG_CH2_SLV_ADDR1
#endif
};

/* Array of data of Slave Address 2 Register (SARL2 and SARU2) for RIICn (n=0, 1 or 2) */
const uint16_t g_riic_slv_ad2_val[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CFG_CH0_SLV_ADDR2,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CFG_CH1_SLV_ADDR2,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CFG_CH2_SLV_ADDR2
#endif
};

/* Array of slave address 0 format for RIICn (n=0, 1 or 2) */
const uint32_t g_riic_slv_ad0_format[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CFG_CH0_SLV_ADDR0_FORMAT,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CFG_CH1_SLV_ADDR0_FORMAT,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CFG_CH2_SLV_ADDR0_FORMAT
#endif
};

/* Array of slave address 1 format for RIICn (n=0, 1 or 2) */
const uint32_t g_riic_slv_ad1_format[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CFG_CH0_SLV_ADDR1_FORMAT,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CFG_CH1_SLV_ADDR1_FORMAT,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CFG_CH2_SLV_ADDR1_FORMAT
#endif
};

/* Array of slave address 2 format for RIICn (n=0, 1 or 2) */
const uint32_t g_riic_slv_ad2_format[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CFG_CH0_SLV_ADDR2_FORMAT,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CFG_CH1_SLV_ADDR2_FORMAT,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CFG_CH2_SLV_ADDR2_FORMAT
#endif
};

/* Array of general call address enable for RIICn (n=0, 1 or 2) */
const uint32_t g_riic_gca_enable[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CFG_CH0_SLV_GCA_ENABLE,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CFG_CH1_SLV_GCA_ENABLE,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CFG_CH2_SLV_GCA_ENABLE
#endif
};

/* Array of initialize data of I2C-bus Mode Register 2 (ICMR2) for RIICn (n=0, 1 or 2) */
const uint32_t g_riic_icmr2_init[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CH0_ICMR2_INIT,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CH1_ICMR2_INIT,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CH2_ICMR2_INIT
#endif
};

/* Array of initialize data of I2C-bus Mode Register 3 (ICMR3) for RIICn (n=0, 1 or 2) */
const uint32_t g_riic_icmr3_init[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CH0_ICMR3_INIT,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CH1_ICMR3_INIT,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CH2_ICMR3_INIT
#endif
};

/* Array of initialize data of I2C-bus Function Enable Register (ICFER) for RIICn (n=0, 1 or 2) */
const uint32_t g_riic_icfer_init[MAX_RIIC_CH_NUM] =
{
#if (1U == RIIC_CFG_CH0_INCLUDED)
    RIIC_CH0_ICFER_INIT,
#endif
#if (1U == RIIC_CFG_CH1_INCLUDED)
    RIIC_CH1_ICFER_INIT,
#endif
#if (1U == RIIC_CFG_CH2_INCLUDED)
    RIIC_CH2_ICFER_INIT
#endif
};

/***********************************************************************************************************************
 Private global variables and functions
 **********************************************************************************************************************/
    #if (1U == RIIC_CFG_PORT_SET_PROCESSING)
/***********************************************************************************************************************
 * Function Name: riic_mcu_io_open
 * Description  : Sets ports to input mode.
 *              : Ports input pull-up becomes "Off".
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_io_open (uint8_t channel)
{
    /* Channel number? */
    switch (channel)
    {
        #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */
            /* Sets the port register of SCL pin. */
        	PORT_Enable( R_RIIC_CFG_RIIC0_SCL0_PORT, R_RIIC_CFG_RIIC0_SCL0_BIT,
        			PORT_DIR_KEEP, PORT_MODE_PERIPHERAL,
						   R_RIIC_PORT_FUNC_SCL0 );
            /* Sets the port register of SDA pin. */
        	PORT_Enable( R_RIIC_CFG_RIIC0_SDA0_PORT, R_RIIC_CFG_RIIC0_SDA0_BIT,
        			PORT_DIR_KEEP, PORT_MODE_PERIPHERAL,
						   R_RIIC_PORT_FUNC_SDA0 );
        break;
        #endif

        #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */

            /* Sets the port register of SCL pin. */
            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SCL1 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SCL1 input mode */

            /* Sets the port register of SDA pin. */
            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SDA1 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SDA1 input mode */
            uctmp = (*ppdr); /* Reads PDR. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */

            /* Sets the port register of SCL pin. */
            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SCL2 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SCL2 input mode */

            /* Sets the port register of SDA pin. */
            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppcr = (uint8_t *)((uint32_t)RIIC_PRV_PCR_BASE_REG + (uint32_t)port_gr);
            ppdr = (uint8_t *)((uint32_t)RIIC_PRV_PDR_BASE_REG + (uint32_t)port_gr);
            (*ppcr) &= (~(1U << pin_num)); /* SDA2 input pull-up resister : off */
            (*ppdr) &= (~(RIIC_IN << pin_num)); /* SDA2 input mode */
            uctmp = (*ppdr); /* Reads PDR. */
        break;
        #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
} /* End of function riic_mcu_io_open() */

#ifndef BSP_MCU_RH850F1KH
/***********************************************************************************************************************
 * Function Name: riic_mcu_mpc_enable
 * Description  : Enables RIIC multi-function pin controller.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_mpc_enable (uint8_t channel)
{
    volatile uint8_t uctmp = 0x00;
    volatile uint8_t __evenaccess * ppmr = NULL;
    volatile uint8_t __evenaccess * ppfs = NULL;
    uint8_t port_gr = 0;
    uint8_t pin_num = 0;

    /* The upper layer software should call "riic_disable()." */
    /* The upper layer software should set SCL and SDA ports to input mode using PDR. */
    /* The upper layer software should perform RIIC reset or internal reset. */

    /* Channel number? */
    switch (channel)
    {
        #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */
            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            /* Specifies the assignments of input/output signals for peripheral functions to the desired pins.
             But SCL and SDA are already in a high-impedance state.
             Because the upper layer software called "riic_reset_set()". */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL0_ENABLE; /* Pin function select to RIIC SCL pin. */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA0_ENABLE; /* Pin function select to RIIC SDA pin. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */

            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SCL). */
            uctmp = (*ppmr); /* Reads PMR. */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SDA). */
            uctmp = (*ppmr); /* Reads PMR. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */
            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            /* Specifies the assignments of input/output signals for peripheral functions to the desired pins.
             But SCL and SDA are already in a high-impedance state.
             Because the upper layer software called "riic_reset_set()". */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL1_ENABLE; /* Pin function select to RIIC SCL pin. */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA1_ENABLE; /* Pin function select to RIIC SDA pin. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */

            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SCL). */
            uctmp = (*ppmr); /* Reads PMR. */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SDA). */
            uctmp = (*ppmr); /* Reads PMR. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */
            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            /* Specifies the assignments of input/output signals for peripheral functions to the desired pins.
             But SCL and SDA are already in a high-impedance state.
             Because the upper layer software called "riic_reset_set()". */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL2_ENABLE; /* Pin function select to RIIC SCL pin. */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA2_ENABLE; /* Pin function select to RIIC SDA pin. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */

            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SCL). */
            uctmp = (*ppmr); /* Reads PMR. */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) |= (1U << pin_num); /* Uses as RIIC (SDA). */
            uctmp = (*ppmr); /* Reads PMR. */
        break;
        #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
} /* End of function riic_mcu_mpc_enable() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_mpc_disable
 * Description  : Disables RIIC multi-function pin controller.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_mpc_disable (uint8_t channel)
{
    volatile uint8_t uctmp = 0x00;
    volatile uint8_t __evenaccess * ppmr = NULL;
    volatile uint8_t __evenaccess * ppfs = NULL;
    uint8_t port_gr = 0;
    uint8_t pin_num = 0;

    /* The upper layer software should set SCL snd SDA ports to input mode using PDR. */

    /* Channel number? */
    switch (channel)
    {
        #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */
            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH0_SCL0_GP;
            pin_num = RIIC_CH0_SCL0_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL0_INIT; /* Pin function select to Hi-Z. */

            port_gr = RIIC_CH0_SDA0_GP;
            pin_num = RIIC_CH0_SDA0_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA0_INIT; /* Pin function select to Hi-Z. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */
            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH1_SCL1_GP;
            pin_num = RIIC_CH1_SCL1_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL1_INIT; /* Pin function select to Hi-Z. */

            port_gr = RIIC_CH1_SDA1_GP;
            pin_num = RIIC_CH1_SDA1_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA1_INIT; /* Pin function select to Hi-Z. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */
        break;
        #endif

        #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */
            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppmr = (uint8_t *)((uint32_t)RIIC_PRV_PMR_BASE_REG + (uint32_t)port_gr);
            (*ppmr) &= (~(1U << pin_num)); /* Uses as a GPIO (Input port). */

            R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_MPC); /* Enables the PFS register writing. */

            port_gr = RIIC_CH2_SCL2_GP;
            pin_num = RIIC_CH2_SCL2_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SCL2_INIT; /* Pin function select to Hi-Z. */

            port_gr = RIIC_CH2_SDA2_GP;
            pin_num = RIIC_CH2_SDA2_PIN;
            ppfs = (uint8_t *)((uint32_t)RIIC_PRV_PFS_BASE_REG + (uint32_t)((port_gr * 8) + pin_num));
            (*ppfs) = RIIC_MPC_SDA2_INIT; /* Pin function select to Hi-Z. */

            R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_MPC); /* Disables the PFS register writing. */
        break;
        #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
    uctmp = RIIC_PWPR_BOWI; /* Reads PWPR. */
} /* End of function riic_mcu_mpc_disable() */
#endif
#endif

/***********************************************************************************************************************
 * Function Name: riic_mcu_check_channel
 * Description  : Checks channel is valid or not.
 * Arguments    : uint8_t channel
 * Return Value : true                   : RIIC channel is valid.
 *                false                  : RIIC channel is invalid.
 **********************************************************************************************************************/
bool riic_mcu_check_channel (uint8_t channel)
{
    bool ret = false;

    switch (channel)
    {

    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            ret = true;
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            ret = true;
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            ret = true;
        break;
    #endif

        default :

            /* The channel number is invalid. */
            ret = false;
        break;
    }

    return ret;
} /* End of function riic_mcu_check_channel() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_int_init
 * Description  : Registers a callback function for supported TEI and EEI group interrupts.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_int_init (uint8_t channel)
{
	//Interrupt routine are registered in another way.
	//Below code are not necessary for there are no BSP code.
#ifndef BSP_MCU_RH850F1KH
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC0_EEI0, (bsp_int_cb_t) riic0_eei_isr);
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC0_TEI0, (bsp_int_cb_t) riic0_tei_isr);
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC1_EEI1, (bsp_int_cb_t) riic1_eei_isr);
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC1_TEI1, (bsp_int_cb_t) riic1_tei_isr);
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC2_EEI2, (bsp_int_cb_t)riic2_eei_isr);
            R_BSP_InterruptWrite(BSP_INT_SRC_BL1_RIIC2_TEI2, (bsp_int_cb_t)riic2_tei_isr);
        break;
    #endif

        default :

            /* Do Nothing */
        break;
    }
#endif
} /* End of function riic_mcu_int_init() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_check_ir_txi
 * Description  : Check TXI interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : RIIC_IR_CLR         : TXI Interrupt request (IR) register is cleared.
 *              : RIIC_IR_SET         : TXI Interrupt request (IR) register is set.
 **********************************************************************************************************************/
uint32_t riic_mcu_check_ir_txi (uint8_t channel)
{
    uint32_t ret = RIIC_IR_CLR;

    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            ret = ((REG_ICRIIC0TI.UINT16 & INTC_IR_SET)>>12);
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            ret = RIIC_IR_TXI1;
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            ret = RIIC_IR_TXI2;
        break;
    #endif
        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }

    return ret;
} /* End of function riic_mcu_check_ir_txi() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_check_ir_rxi
 * Description  : Check RXI interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : RIIC_IR_CLR         : TXI Interrupt request (IR) register is cleared.
 *              : RIIC_IR_SET         : TXI Interrupt request (IR) register is set.
 **********************************************************************************************************************/
uint32_t riic_mcu_check_ir_rxi (uint8_t channel)
{
    uint32_t ret = RIIC_IR_CLR;

    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            ret = ((REG_ICRIIC0RI.UINT16 & INTC_IR_SET)>>12);
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            ret = RIIC_IR_RXI1;
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            ret = RIIC_IR_RXI2;
        break;
    #endif
        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }

    return ret;
} /* End of function riic_mcu_check_ir_rxi() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_clear_ir_txi
 * Description  : Clear TXI interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_clear_ir_txi (uint8_t channel)
{
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :

        	REG_ICRIIC0TI.UINT16 &= ~INTC_IR_SET;; /* Clears TXI interrupt request register. */
            if (RIIC_IR_CLR == (REG_ICRIIC0TI.UINT16 & INTC_IR_SET))
            {
                /* Do Nothing */
            }
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            RIIC_IR_TXI1 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if (RIIC_IR_CLR == RIIC_IR_TXI1)
            {
                /* Do Nothing */
            }
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            RIIC_IR_TXI2 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if(RIIC_IR_CLR == RIIC_IR_TXI2)
            {
                /* Do Nothing */
            }
        break;
    #endif
        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }
} /* End of function riic_mcu_clear_ir_txi() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_clear_ir_rxi
 * Description  : Clear RXI interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_clear_ir_rxi (uint8_t channel)
{
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
        	REG_ICRIIC0RI.UINT16 &= ~INTC_IR_SET;; /* Clears TXI interrupt request register. */
        	            if (RIIC_IR_CLR == (REG_ICRIIC0RI.UINT16 & INTC_IR_SET))
            {
                /* Do Nothing */
            }
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            RIIC_IR_RXI1 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if (RIIC_IR_CLR == RIIC_IR_RXI1)
            {
                /* Do Nothing */
            }
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            RIIC_IR_RXI2 = RIIC_IR_CLR; /* Clears TXI interrupt request register. */
            if(RIIC_IR_CLR == RIIC_IR_RXI2)
            {
                /* Do Nothing */
            }
        break;
    #endif
        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }
} /* End of function riic_mcu_clear_ir_rxi() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_hardware_lock
 * Description  : Attempt to acquire the lock that has been sent in.
 * Arguments    : uint8_t channel
 * Return Value : true                   ; Successful operation
 *              : false                  ; error operation
 **********************************************************************************************************************/
bool riic_mcu_hardware_lock (uint8_t channel)
{
#ifndef BSP_MCU_RH850F1KH// It is no meaning to check LOCK for NO OS being used
    bool chk = false;

    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            chk = R_BSP_HardwareLock(BSP_LOCK_RIIC0);
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            chk = R_BSP_HardwareLock(BSP_LOCK_RIIC1);
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            chk = R_BSP_HardwareLock(BSP_LOCK_RIIC2);
        break;
    #endif

        default :

            /* Do Nothing */
        break;
    }
    return chk;
#endif
} /* End of function riic_mcu_hardware_lock() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_hardware_unlock
 * Description  : Release hold on lock.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_hardware_unlock (uint8_t channel)
{
#ifndef BSP_MCU_RH850F1KH// It is no meaning to check LOCK for NO OS being used
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :
            R_BSP_HardwareUnlock(BSP_LOCK_RIIC0);
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :
            R_BSP_HardwareUnlock(BSP_LOCK_RIIC1);
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:
            R_BSP_HardwareUnlock(BSP_LOCK_RIIC2);
        break;
    #endif

        default :

            /* Do Nothing */
        break;
    }
#endif
} /* End of function riic_mcu_hardware_unlock() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_power_on
 * Description  : Turns on power to a RIIC channel.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_power_on (uint8_t channel)
{
#ifndef BSP_MCU_RH850F1KH //The power of RIIC can't be controlled alone
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

    /* Enable selected RIIC Channel. */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :

            /* Bring module out of stop state. */
            MSTP(RIIC0) = 0U;
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :

            /* Bring module out of stop state. */
            MSTP(RIIC1) = 0U;
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:

            /* Bring module out of stop state. */
            MSTP(RIIC2) = 0U;
        break;
    #endif

        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }

    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
#endif
} /* End of function riic_mcu_power_on() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_power_off
 * Description  : Turns off power to a RIIC channel.
 * Arguments    : uint8_t channel
 * Return Value : none
 **********************************************************************************************************************/
void riic_mcu_power_off (uint8_t channel)
{
#ifndef BSP_MCU_RH850F1KH //The power of RIIC can't be controlled alone
    /* Enable writing to MSTP registers. */
    R_BSP_RegisterProtectDisable(BSP_REG_PROTECT_LPC_CGC_SWR);

    /* Disable selected CMT Channel. */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 :

            /* Put module in stop state. */
            MSTP(RIIC0) = 1U;
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 :

            /* Put module in stop state. */
            MSTP(RIIC1) = 1U;
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02:

            /* Put module in stop state. */
            MSTP(RIIC2) = 1U;
        break;
    #endif

        default :

            /* Should never get here. Valid channel number is checked above. */
        break;
    }

    /* Disable writing to MSTP registers. */
    R_BSP_RegisterProtectEnable(BSP_REG_PROTECT_LPC_CGC_SWR);
#endif
} /* End of function riic_mcu_power_off() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_int_icier_setting
 * Description  : Time out interrupt enable bit setting.
 * Arguments    : uint8_t channel
 *              : uint8_t New_icier       ; New ICIER value
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_int_icier_setting (uint8_t channel, uint32_t New_icier)
{
    volatile uint32_t uctmp = 0x00;

    /* Channel number? */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */
        #if (1U == RIIC_CFG_CH0_TMO_ENABLE)
            RIIC0.IER.UINT32 = (New_icier | RIIC_ICIER_TMO);
            uctmp = RIIC0.IER.UINT32; /* Reads ICIER. */
        #else
            RIIC0.IER.UINT32 = New_icier;
            uctmp = RIIC0.IER.UINT32; /* Reads ICIER. */
        #endif
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */
        #if (1U == RIIC_CFG_CH1_TMO_ENABLE)
            RIIC1.ICIER.BYTE = (New_icier | RIIC_ICIER_TMO);
            uctmp = RIIC1.ICIER.BYTE; /* Reads ICIER. */
        #else
            RIIC1.ICIER.BYTE = New_icier;
            uctmp = RIIC1.ICIER.BYTE; /* Reads ICIER. */
        #endif
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */
        #if (1U == RIIC_CFG_CH2_TMO_ENABLE)
            RIIC2.ICIER.BYTE = (New_icier | RIIC_ICIER_TMO);
            uctmp = RIIC2.ICIER.BYTE; /* Reads ICIER. */
        #else
            RIIC2.ICIER.BYTE = New_icier;
            uctmp = RIIC2.ICIER.BYTE; /* Reads ICIER. */
        #endif
        break;
    #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
} /* End of function riic_mcu_int_icier_setting() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_int_enable
 * Description  : Clears interrupt request register.
 *              : Enables interrupt.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_int_enable (uint8_t channel)
{
    /* Channel number? */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */
        	REG_ICRIIC0TI.UINT16 = RIIC_CFG_CH0_TXI_INT_PRIORITY;
        	REG_ICRIIC0EE.UINT16 = RIIC_CFG_CH0_EEI_INT_PRIORITY;
        	REG_ICRIIC0RI.UINT16 = RIIC_CFG_CH0_RXI_INT_PRIORITY;
        	REG_ICRIIC0TEI.UINT16 = RIIC_CFG_CH0_TEI_INT_PRIORITY;

            /* Disables interrupt. */
//        	RIIC0.IER.UINT32 = RIIC_ICIER_INT_ENABLE;
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */
        	REG_ICRIIC1TI = RIIC_CFG_CH1_TXI_INT_PRIORITY;
        	REG_ICRIIC1EE = RIIC_CFG_CH1_EEI_INT_PRIORITY;
        	REG_ICRIIC1RI = RIIC_CFG_CH1_RXI_INT_PRIORITY;
        	REG_ICRIIC1TEI = RIIC_CFG_CH1_TEI_INT_PRIORITY;
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */
        	REG_ICRIIC2TI = RIIC_CFG_CH2_TXI_INT_PRIORITY;
        	REG_ICRIIC2EE = RIIC_CFG_CH2_EEI_INT_PRIORITY;
        	REG_ICRIIC2RI = RIIC_CFG_CH2_RXI_INT_PRIORITY;
        	REG_ICRIIC2TEI = RIIC_CFG_CH2_TEI_INT_PRIORITY;
        break;
    #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
} /* End of function riic_mcu_int_enable() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_int_disable
 * Description  : Disables interrupt.
 *              : Sets interrupt source priority.
 *              : Clears interrupt request register.
 * Arguments    : uint8_t channel
 * Return Value : None
 **********************************************************************************************************************/
void riic_mcu_int_disable (uint8_t channel)
{
    /* Channel number? */
    switch (channel)
    {
    #if (1U == RIIC_CFG_CH0_INCLUDED)
        case 0x00 : /* Channel 0 */
        	REG_ICRIIC0TI.UINT16 = RIIC_CFG_DISABLE_INT;
        	REG_ICRIIC0EE.UINT16 = RIIC_CFG_DISABLE_INT;
        	REG_ICRIIC0RI.UINT16 = RIIC_CFG_DISABLE_INT;
        	REG_ICRIIC0TEI.UINT16 = RIIC_CFG_DISABLE_INT;

            /* Disables interrupt. */
        	RIIC0.IER.UINT32 = RIIC_ICIER_INT_DISABLE;
        break;
    #endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
        case 0x01 : /* Channel 1 */

            /* Disables interrupt. */
            RIIC_IER_EEI1_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI1 groupBL1 interrupt request enable register. */
            RIIC_IER_RXI1 = RIIC_IER_DISABLE; /* Disables RXI1 interrupt request enable register. */
            RIIC_IER_TXI1 = RIIC_IER_DISABLE; /* Disables TXI1 interrupt request enable register. */
            RIIC_IER_TEI1_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI1 groupBL1 interrupt request enable register. */

            /* Sets interrupt source priority. */
            RIIC_IPR_RXI1 = RIIC_IPR_CH1_RXI_INIT; /* Sets RXI1 interrupt source priority register. */
            RIIC_IPR_TXI1 = RIIC_IPR_CH1_TXI_INIT; /* Sets TXI1 interrupt source priority register. */
            uctmp = RIIC_IPR_TXI1; /* Reads IPR. */
        break;
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
        case 0x02: /* Channel 2 */

            /* Disables interrupt. */
            RIIC_IER_EEI2_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI2 groupBL1 interrupt request enable register. */
            RIIC_IER_RXI2 = RIIC_IER_DISABLE; /* Disables RXI2 interrupt request enable register. */
            RIIC_IER_TXI2 = RIIC_IER_DISABLE; /* Disables TXI2 interrupt request enable register. */
            RIIC_IER_TEI2_GPBL1 = RIIC_IER_DISABLE; /* Disables TEI2 groupBL1 interrupt request enable register. */

            /* Sets interrupt source priority. */
            RIIC_IPR_RXI2 = RIIC_IPR_CH2_RXI_INIT; /* Sets RXI2 interrupt source priority register. */
            RIIC_IPR_TXI2 = RIIC_IPR_CH2_TXI_INIT; /* Sets TXI2 interrupt source priority register. */
            uctmp = RIIC_IPR_TXI2; /* Reads IPR. */
        break;
    #endif

        default :

            /* Please add a channel as needed. */
        break;
    }
} /* End of function riic_mcu_int_disable() */

/***********************************************************************************************************************
 * Function Name: riic_mcu_check_freq
 * Description  : check pclk frequency and return that value.
 * Arguments    : None
 * Return Value : PCLK frequency
 **********************************************************************************************************************/
double riic_mcu_check_freq (void)
{
    return BSP_PCLKB_HZ;
} /* End of function riic_mcu_check_freq() */

    #if (1U == RIIC_CFG_CH0_INCLUDED)
/***********************************************************************************************************************
 * Function Name: riic0_eei_isr
 * Description  : Interrupt EEI handler for channel 0.
 *                Types of interrupt requests transfer error or event generation.
 *                The event generations are arbitration-lost, NACK detection, timeout detection, 
 *                start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
#pragma section text"comint"
#pragma interrupt riic0_eei_isr( enable=false , channel=77 , callt=false , fpu=false )
void riic0_eei_isr (void)
{
    riic0_eei_sub();
} /* End of function riic0_eei_isr() */

/***********************************************************************************************************************
 * Function Name: riic0_txi_isr
 * Description  : Interrupt TXI handler for channel 0.
 *                Types of interrupt requests transmission data empty.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
//        #pragma interrupt (riic0_txi_isr(vect = VECT(RIIC0, TXI0)))
#pragma interrupt riic0_txi_isr( enable=false , channel=76 , callt=false , fpu=false )
void riic0_txi_isr(void)
{
    riic0_txi_sub();
} /* End of function riic0_txi_isr() */

/***********************************************************************************************************************
 * Function Name: riic0_rxi_isr
 * Description  : Interrupt RXI handler for channel 0.
 *                Types of interrupt requests reception end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
//        #pragma interrupt (riic0_rxi_isr(vect = VECT(RIIC0, RXI0)))
#pragma interrupt riic0_rxi_isr( enable=false , channel=78 , callt=false , fpu=false )
void riic0_rxi_isr (void)
{
    riic0_rxi_sub();
} /* End of function riic0_rxi_isr() */

/***********************************************************************************************************************
 * Function Name: riic0_tei_isr
 * Description  : Interrupt TEI handler for channel 0.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
#pragma interrupt riic0_tei_isr( enable=false , channel=79 , callt=false , fpu=false )
void riic0_tei_isr (void)
{
    riic0_tei_sub();
} /* End of function riic0_tei_isr() */
#pragma section default
#endif

    #if (1U == RIIC_CFG_CH1_INCLUDED)
/***********************************************************************************************************************
 * Function Name: riic1_eei_isr
 * Description  : Interrupt EEI handler for channel 1.
 *                Types of interrupt requests transfer error or event generation.
 *                The event generations are arbitration-lost, NACK detection, timeout detection, 
 *                start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic1_eei_isr (void * vect)
{
    riic1_eei_sub();
} /* End of function riic1_eei_isr() */

/***********************************************************************************************************************
 * Function Name: riic1_txi_isr
 * Description  : Interrupt TXI handler for channel 1.
 *                Types of interrupt requests transmission data empty.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
        #pragma interrupt (riic1_txi_isr(vect = VECT(RIIC1, TXI1)))
static void riic1_txi_isr (void)
{
    riic1_txi_sub();
} /* End of function riic1_txi_isr() */

/***********************************************************************************************************************
 * Function Name: riic1_rxi_isr
 * Description  : Interrupt RXI handler for channel 1.
 *                Types of interrupt requests reception end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
        #pragma interrupt (riic1_rxi_isr(vect = VECT(RIIC1, RXI1)))
static void riic1_rxi_isr (void)
{
    riic1_rxi_sub();
} /* End of function riic1_rxi_isr() */

/***********************************************************************************************************************
 * Function Name: riic1_tei_isr
 * Description  : Interrupt TEI handler for channel 1.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic1_tei_isr (void * vect)
{
    riic1_tei_sub();
} /* End of function riic1_tei_isr() */
    #endif

    #if (1U == RIIC_CFG_CH2_INCLUDED)
/***********************************************************************************************************************
 * Function Name: riic2_eei_isr
 * Description  : Interrupt EEI handler for channel 2.
 *                Types of interrupt requests transfer error or event generation.
 *                The event generations are arbitration-lost, NACK detection, timeout detection, 
 *                start condition detection, and stop condition detection.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic2_eei_isr(void * vect)
{
    riic2_eei_sub();
} /* End of function riic2_eei_isr() */

/***********************************************************************************************************************
 * Function Name: riic2_txi_isr
 * Description  : Interrupt TXI handler for channel 2.
 *                Types of interrupt requests transmission data empty.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
        #pragma interrupt (riic2_txi_isr(vect = VECT(RIIC2, TXI2)))
static void riic2_txi_isr(void)
{
    riic2_txi_sub();
} /* End of function riic2_txi_isr() */

/***********************************************************************************************************************
 * Function Name: riic2_rxi_isr
 * Description  : Interrupt RXI handler for channel 2.
 *                Types of interrupt requests reception end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
        #pragma interrupt (riic2_rxi_isr(vect = VECT(RIIC2, RXI2)))
static void riic2_rxi_isr(void)
{
    riic2_rxi_sub();
} /* End of function riic2_rxi_isr() */

/***********************************************************************************************************************
 * Function Name: riic2_tei_isr
 * Description  : Interrupt TEI handler for channel 2.
 *                Types of interrupt requests transmission end.
 * Arguments    : None
 * Return Value : None
 **********************************************************************************************************************/
void riic2_tei_isr(void * vect)
{
    riic2_tei_sub();
} /* End of function riic2_tei_isr() */
    #endif

#endif /* defined(BSP_MCU_RX65N) */

