#include <math.h>
#include <stdio.h>
#include <string.h>

#include "ti/driverlib/dl_uart_main.h"
#include "ti_msp_dl_config.h"
#include "APP/MOTOR/motor.h"
#include "APP/TIMER/timer.h"

uint32_t next_log = 100;
uint32_t flag_led = 1000;
void Send_String(char *str);

int main(void)
{
    SYSCFG_DL_init();

    /* 电机 */
    Motor_Init(&motor_left,
               MOTOR_PORT, MOTOR_AIN1_PIN,
               MOTOR_PORT, MOTOR_AIN2_PIN,
               PWM_0_INST, GPIO_PWM_0_C0_IDX);
    Motor_Init(&motor_right,
               MOTOR_PORT, MOTOR_BIN1_PIN,
               MOTOR_PORT, MOTOR_BIN2_PIN,
               PWM_0_INST, GPIO_PWM_0_C1_IDX);

    /* 系统滴答: 1ms */
    Timer_Init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

    /* 主循环: 由 sys_tick 1ms 驱动 */
    while (1)
    {
        /* 100ms 串口输出 */
        if (sys_tick >= next_log)
        {
            next_log += 100;
            Send_String("hello\r\n");
        }

        if (sys_tick >= flag_led)
        {
            flag_led += 1000;
            DL_GPIO_togglePins(LED_PORT, LED_PIN_22_PIN);
        }
    }
}

/* 自定义串口阻塞式发送 */
void Send_String(char *str)
{
    while (*str != '\0')
    {
        DL_UART_Main_transmitDataBlocking(DEBUG_INST, (uint8_t)(*str++));
    }
}

/* 系统滴答: 只做计数 */
void TIMA1_IRQHandler(void)
{
    DL_Timer_clearInterruptStatus(TIMER_0_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT);
    sys_tick++;
}

