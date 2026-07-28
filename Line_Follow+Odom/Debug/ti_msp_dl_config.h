/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define GPIO_HFXT_PORT                                                     GPIOA
#define GPIO_HFXIN_PIN                                             DL_GPIO_PIN_5
#define GPIO_HFXIN_IOMUX                                         (IOMUX_PINCM10)
#define GPIO_HFXOUT_PIN                                            DL_GPIO_PIN_6
#define GPIO_HFXOUT_IOMUX                                        (IOMUX_PINCM11)
#define CPUCLK_FREQ                                                     80000000
/* Defines for SYSPLL_ERR_01 Workaround */
/* Represent 1.000 as 1000 */
#define FLOAT_TO_INT_SCALE                                               (1000U)
#define FCC_EXPECTED_RATIO                                                  2000
#define FCC_UPPER_BOUND                       (FCC_EXPECTED_RATIO * (1 + 0.003))
#define FCC_LOWER_BOUND                       (FCC_EXPECTED_RATIO * (1 - 0.003))

bool SYSCFG_DL_SYSCTL_SYSPLL_init(void);


/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA0
#define PWM_0_INST_IRQHandler                                   TIMA0_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                             80000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOB
#define GPIO_PWM_0_C0_PIN                                         DL_GPIO_PIN_14
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM31)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM31_PF_TIMA0_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOA
#define GPIO_PWM_0_C1_PIN                                          DL_GPIO_PIN_7
#define GPIO_PWM_0_C1_IOMUX                                      (IOMUX_PINCM14)
#define GPIO_PWM_0_C1_IOMUX_FUNC                     IOMUX_PINCM14_PF_TIMA0_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA1)
#define TIMER_0_INST_IRQHandler                                 TIMA1_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA1_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                          (2499U)



/* Defines for DEBUG */
#define DEBUG_INST                                                         UART0
#define DEBUG_INST_FREQUENCY                                             4000000
#define DEBUG_INST_IRQHandler                                   UART0_IRQHandler
#define DEBUG_INST_INT_IRQN                                       UART0_INT_IRQn
#define GPIO_DEBUG_RX_PORT                                                 GPIOA
#define GPIO_DEBUG_TX_PORT                                                 GPIOA
#define GPIO_DEBUG_RX_PIN                                         DL_GPIO_PIN_11
#define GPIO_DEBUG_TX_PIN                                         DL_GPIO_PIN_10
#define GPIO_DEBUG_IOMUX_RX                                      (IOMUX_PINCM22)
#define GPIO_DEBUG_IOMUX_TX                                      (IOMUX_PINCM21)
#define GPIO_DEBUG_IOMUX_RX_FUNC                       IOMUX_PINCM22_PF_UART0_RX
#define GPIO_DEBUG_IOMUX_TX_FUNC                       IOMUX_PINCM21_PF_UART0_TX
#define DEBUG_BAUD_RATE                                                   (9600)
#define DEBUG_IBRD_4_MHZ_9600_BAUD                                          (26)
#define DEBUG_FBRD_4_MHZ_9600_BAUD                                           (3)





/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOB)

/* Defines for PIN_22: GPIOB.22 with pinCMx 50 on package pin 21 */
#define LED_PIN_22_PIN                                          (DL_GPIO_PIN_22)
#define LED_PIN_22_IOMUX                                         (IOMUX_PINCM50)
/* Port definition for Pin Group MOTOR */
#define MOTOR_PORT                                                       (GPIOB)

/* Defines for AIN2: GPIOB.9 with pinCMx 26 on package pin 61 */
#define MOTOR_AIN2_PIN                                           (DL_GPIO_PIN_9)
#define MOTOR_AIN2_IOMUX                                         (IOMUX_PINCM26)
/* Defines for AIN1: GPIOB.10 with pinCMx 27 on package pin 62 */
#define MOTOR_AIN1_PIN                                          (DL_GPIO_PIN_10)
#define MOTOR_AIN1_IOMUX                                         (IOMUX_PINCM27)
/* Defines for BIN2: GPIOB.7 with pinCMx 24 on package pin 59 */
#define MOTOR_BIN2_PIN                                           (DL_GPIO_PIN_7)
#define MOTOR_BIN2_IOMUX                                         (IOMUX_PINCM24)
/* Defines for BIN1: GPIOB.6 with pinCMx 23 on package pin 58 */
#define MOTOR_BIN1_PIN                                           (DL_GPIO_PIN_6)
#define MOTOR_BIN1_IOMUX                                         (IOMUX_PINCM23)
/* Port definition for Pin Group ENCODER */
#define ENCODER_PORT                                                     (GPIOB)

/* Defines for LeftA: GPIOB.4 with pinCMx 17 on package pin 52 */
// pins affected by this interrupt request:["LeftA","LeftB","RightA","RightB"]
#define ENCODER_INT_IRQN                                        (GPIOB_INT_IRQn)
#define ENCODER_INT_IIDX                        (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define ENCODER_LeftA_IIDX                                   (DL_GPIO_IIDX_DIO4)
#define ENCODER_LeftA_PIN                                        (DL_GPIO_PIN_4)
#define ENCODER_LeftA_IOMUX                                      (IOMUX_PINCM17)
/* Defines for LeftB: GPIOB.5 with pinCMx 18 on package pin 53 */
#define ENCODER_LeftB_IIDX                                   (DL_GPIO_IIDX_DIO5)
#define ENCODER_LeftB_PIN                                        (DL_GPIO_PIN_5)
#define ENCODER_LeftB_IOMUX                                      (IOMUX_PINCM18)
/* Defines for RightA: GPIOB.11 with pinCMx 28 on package pin 63 */
#define ENCODER_RightA_IIDX                                 (DL_GPIO_IIDX_DIO11)
#define ENCODER_RightA_PIN                                      (DL_GPIO_PIN_11)
#define ENCODER_RightA_IOMUX                                     (IOMUX_PINCM28)
/* Defines for RightB: GPIOB.12 with pinCMx 29 on package pin 64 */
#define ENCODER_RightB_IIDX                                 (DL_GPIO_IIDX_DIO12)
#define ENCODER_RightB_PIN                                      (DL_GPIO_PIN_12)
#define ENCODER_RightB_IOMUX                                     (IOMUX_PINCM29)
/* Defines for PIN_0: GPIOB.19 with pinCMx 45 on package pin 16 */
#define GRAY_PIN_0_PORT                                                  (GPIOB)
#define GRAY_PIN_0_PIN                                          (DL_GPIO_PIN_19)
#define GRAY_PIN_0_IOMUX                                         (IOMUX_PINCM45)
/* Defines for PIN_1: GPIOB.17 with pinCMx 43 on package pin 14 */
#define GRAY_PIN_1_PORT                                                  (GPIOB)
#define GRAY_PIN_1_PIN                                          (DL_GPIO_PIN_17)
#define GRAY_PIN_1_IOMUX                                         (IOMUX_PINCM43)
/* Defines for PIN_2: GPIOA.16 with pinCMx 38 on package pin 9 */
#define GRAY_PIN_2_PORT                                                  (GPIOA)
#define GRAY_PIN_2_PIN                                          (DL_GPIO_PIN_16)
#define GRAY_PIN_2_IOMUX                                         (IOMUX_PINCM38)
/* Defines for PIN_3: GPIOA.14 with pinCMx 36 on package pin 7 */
#define GRAY_PIN_3_PORT                                                  (GPIOA)
#define GRAY_PIN_3_PIN                                          (DL_GPIO_PIN_14)
#define GRAY_PIN_3_IOMUX                                         (IOMUX_PINCM36)
/* Defines for PIN_4: GPIOB.20 with pinCMx 48 on package pin 19 */
#define GRAY_PIN_4_PORT                                                  (GPIOB)
#define GRAY_PIN_4_PIN                                          (DL_GPIO_PIN_20)
#define GRAY_PIN_4_IOMUX                                         (IOMUX_PINCM48)
/* Defines for PIN_5: GPIOB.25 with pinCMx 56 on package pin 27 */
#define GRAY_PIN_5_PORT                                                  (GPIOB)
#define GRAY_PIN_5_PIN                                          (DL_GPIO_PIN_25)
#define GRAY_PIN_5_IOMUX                                         (IOMUX_PINCM56)
/* Defines for PIN_6: GPIOA.25 with pinCMx 55 on package pin 26 */
#define GRAY_PIN_6_PORT                                                  (GPIOA)
#define GRAY_PIN_6_PIN                                          (DL_GPIO_PIN_25)
#define GRAY_PIN_6_IOMUX                                         (IOMUX_PINCM55)
/* Defines for PIN_7: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GRAY_PIN_7_PORT                                                  (GPIOA)
#define GRAY_PIN_7_PIN                                          (DL_GPIO_PIN_27)
#define GRAY_PIN_7_IOMUX                                         (IOMUX_PINCM60)


/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);

bool SYSCFG_DL_SYSCTL_SYSPLL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_DEBUG_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
