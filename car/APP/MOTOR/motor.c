/* TB6612 双路电机驱动 — MSPM0 DriverLib */
#include "motor.h"

Motor motor_left;
Motor motor_right;

static void motor_dir(Motor *m, uint8_t cw)
{
    if (cw) {
        DL_GPIO_setPins(m->ain1_port, m->ain1_pin);
        DL_GPIO_clearPins(m->ain2_port, m->ain2_pin);
    } else {
        DL_GPIO_clearPins(m->ain1_port, m->ain1_pin);
        DL_GPIO_setPins(m->ain2_port, m->ain2_pin);
    }
}

void Motor_Init(Motor *m,
                GPIO_Regs *ain1_port, uint32_t ain1_pin,
                GPIO_Regs *ain2_port, uint32_t ain2_pin,
                GPTIMER_Regs *htim, DL_TIMER_CC_INDEX pwm_channel)
{
    m->ain1_port   = ain1_port;
    m->ain1_pin    = ain1_pin;
    m->ain2_port   = ain2_port;
    m->ain2_pin    = ain2_pin;
    m->htim        = htim;
    m->pwm_channel = pwm_channel;

    Motor_Coast(m);
    DL_TimerA_setCaptureCompareValue(m->htim, 0, m->pwm_channel);
}

void Motor_Run(Motor *m, int16_t ccr)
{
    if (ccr == 0) { Motor_Coast(m); return; }

    motor_dir(m, ccr > 0);

    uint16_t val = (uint16_t)(ccr > 0 ? ccr : -ccr);
    DL_TimerA_setCaptureCompareValue(m->htim, val, m->pwm_channel);
}

void Motor_Coast(Motor *m)
{
    DL_GPIO_clearPins(m->ain1_port, m->ain1_pin);
    DL_GPIO_clearPins(m->ain2_port, m->ain2_pin);
}

void Motor_Brake(Motor *m)
{
    DL_GPIO_setPins(m->ain1_port, m->ain1_pin);
    DL_GPIO_setPins(m->ain2_port, m->ain2_pin);
}
