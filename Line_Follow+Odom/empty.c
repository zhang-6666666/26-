#include "ti_msp_dl_config.h"
#include "APP/MOTOR/motor.h"
#include "APP/TIMER/timer.h"
#include "APP/ENCODER/encoder.h"
#include "APP/LINE/line.h"
#include <math.h>

/* ---- 调试串口 ---- */

static void uart_putc(uint8_t c)
{
    DL_UART_transmitDataBlocking(DEBUG_INST, c);
}

static void uart_puts(const char *s)
{
    while (*s) uart_putc(*s++);
}

static void uart_puti(int32_t n)
{
    char buf[12];
    int i = 0;
    if (n < 0) { uart_putc('-'); n = -n; }
    do { buf[i++] = '0' + (n % 10); n /= 10; } while (n);
    while (i--) uart_putc(buf[i]);
}

/* ---- */

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

    /* 编码器 */
    Encoder_Init(&encoder_left,  ENCODER_PORT, ENCODER_LeftA_PIN,  ENCODER_LeftB_PIN);
    Encoder_Init(&encoder_right, ENCODER_PORT, ENCODER_RightB_PIN, ENCODER_RightA_PIN);
    Encoder_Start(&encoder_left);
    Encoder_Start(&encoder_right);

    /* 循线 */
    Line_Init(&line);

    /* 主循环: 由 sys_tick 1ms 驱动 */
    uint32_t last_tick = 0;
    uint32_t next_log  = 100;
    while (1) {
        if (sys_tick == last_tick) continue;
        last_tick = sys_tick;

        /* 1ms 任务 */
        Encoder_UpdateSpeed(&encoder_left);
        Encoder_UpdateSpeed(&encoder_right);
        Line_Run(&line);

        /* 里程计: 每 10ms 更新一次 (和 spd 同步) */
        static float odom_x_cm = 0, odom_y_cm = 0, odom_h = 0;
        static uint8_t odom_tick = 0;
        if (++odom_tick >= 10) {
            odom_tick = 0;
            float L_mm = encoder_left.spd  * 0.1396f;
            float R_mm = encoder_right.spd * 0.1396f;
            float center_mm = (L_mm + R_mm) * 0.5f;
            odom_x_cm += center_mm * 0.1f * cosf(odom_h);
            odom_y_cm += center_mm * 0.1f * sinf(odom_h);
            odom_h     += (R_mm - L_mm) / 115.0f;
        }

        /* 100ms 串口输出 */
        if (sys_tick >= next_log) {
            next_log += 100;
            uart_puts("L:"); uart_puti(Encoder_GetDist_mm(&encoder_left));
            uart_puts("mm V:"); uart_puti(encoder_left.speed_mm_s);
            uart_puts("mm/s X:"); uart_puti((int32_t)odom_x_cm);
            uart_puts("cm Y:"); uart_puti((int32_t)odom_y_cm);
            uart_puts("cm\r\n");
        }
    }
}

/* 系统滴答: 只做计数 */
void TIMA1_IRQHandler(void)
{
    DL_Timer_clearInterruptStatus(TIMER_0_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT);
    sys_tick++;
}

/* 编码器 GPIO 中断 */
void GROUP1_IRQHandler(void)
{
    uint32_t sta;

    sta = DL_GPIO_getEnabledInterruptStatus(GPIOB,
        ENCODER_LeftA_PIN | ENCODER_LeftB_PIN);
    if (sta) {
        DL_GPIO_clearInterruptStatus(GPIOB, sta);
        Encoder_OnEdge(&encoder_left);
    }

    sta = DL_GPIO_getEnabledInterruptStatus(GPIOB,
        ENCODER_RightA_PIN | ENCODER_RightB_PIN);
    if (sta) {
        DL_GPIO_clearInterruptStatus(GPIOB, sta);
        Encoder_OnEdge(&encoder_right);
    }
}
