/* 循线模块 — MSPM0 DriverLib */
#include "line.h"
#include "APP/MOTOR/motor.h"

Line line;

/* 权重: 中心弱、边缘强 */
static const int8_t weight[8] = {-8, -6, -4, -1, 1, 4, 6, 8};

/* 8 路传感器 pin 定义 (左→右), 换引脚只改这里 */
static const struct { GPIO_Regs *port; uint32_t pin; } sensor[8] = {
    {GRAY_PIN_0_PORT, GRAY_PIN_0_PIN},
    {GRAY_PIN_1_PORT, GRAY_PIN_1_PIN},
    {GRAY_PIN_2_PORT, GRAY_PIN_2_PIN},
    {GRAY_PIN_3_PORT, GRAY_PIN_3_PIN},
    {GRAY_PIN_4_PORT, GRAY_PIN_4_PIN},
    {GRAY_PIN_5_PORT, GRAY_PIN_5_PIN},
    {GRAY_PIN_6_PORT, GRAY_PIN_6_PIN},
    {GRAY_PIN_7_PORT, GRAY_PIN_7_PIN},
};

void Line_Init(Line *l)
{
    l->pos      = 0;
    l->yaw      = 0;
    l->prev_yaw = 0;
    l->state    = 0;
    l->turn_dir = 0;
}

void Line_Run(Line *l)
{
    /* 读 8 路 GPIO */
    uint8_t d = 0;
    for (int i = 0; i < 8; i++) {
        if (DL_GPIO_readPins(sensor[i].port, sensor[i].pin)) d |= (1 << i);
    }

    /* 数左右黑线传感器 */
    uint8_t l_cnt = 0, r_cnt = 0;
    for (uint8_t i = 0; i < 4; i++) { if (!(d & (1 << i))) l_cnt++; }
    for (uint8_t i = 4; i < 8; i++) { if (!(d & (1 << i))) r_cnt++; }

    /* 直角弯判断 */
    if (r_cnt >= 3 && l_cnt <= 2) {
        l->yaw      = (float)TURN_STEER;
        l->state    = 2;
        l->turn_dir = 1;
        l->prev_yaw = (float)TURN_STEER;
    } else if (l_cnt >= 3 && r_cnt <= 2) {
        l->yaw      = -(float)TURN_STEER;
        l->state    = 2;
        l->turn_dir = 0;
        l->prev_yaw = -(float)TURN_STEER;
    } else {
        /* 加权质心法 */
        int32_t sum_w = 0, sum_n = 0;
        for (uint8_t i = 0; i < 8; i++) {
            if (!(d & (1 << i))) { sum_w += weight[i]; sum_n++; }
        }

        if (sum_n != 0) {
            l->pos      = (int8_t)(sum_w / sum_n);
            l->yaw      = (float)l->pos * KP;
            l->state    = 1;
            l->prev_yaw = l->yaw;
            l->turn_dir = (l->pos > 0) ? 1 : 0;
        } else {
            /* 丢线: 沿用上次转向 */
            l->pos   = 127;
            l->yaw   = l->prev_yaw;
            l->state = 0;
        }
    }

    /* 执行电机 */
    int16_t L = (int16_t)((float)BASE_SPEED - l->yaw);
    int16_t R = (int16_t)((float)BASE_SPEED + l->yaw);
    Motor_Run(&motor_left,  L);
    Motor_Run(&motor_right, R);
}
