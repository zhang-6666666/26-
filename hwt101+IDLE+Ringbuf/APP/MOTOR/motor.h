/* TB6612 双路电机驱动 — MSPM0 DriverLib */
#ifndef MOTOR_H
#define MOTOR_H

#include <ti/driverlib/driverlib.h>
#include <stdint.h>

/* Motor 句柄 — 字段扁平化，配置由 empty.c 从 syscfg 宏传入 */
typedef struct {
    GPIO_Regs        *ain1_port, *ain2_port;
    uint32_t          ain1_pin,  ain2_pin;
    GPTIMER_Regs     *htim;
    DL_TIMER_CC_INDEX pwm_channel;
} Motor;

void Motor_Init(Motor *m,
                GPIO_Regs *ain1_port, uint32_t ain1_pin,
                GPIO_Regs *ain2_port, uint32_t ain2_pin,
                GPTIMER_Regs *htim, DL_TIMER_CC_INDEX pwm_channel);
void Motor_Run(Motor *m, int16_t ccr);
void Motor_Coast(Motor *m);
void Motor_Brake(Motor *m);

extern Motor motor_left;
extern Motor motor_right;

#endif
