#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "APP/PID/pid.h"

/* 角度环 PID 句柄 */
extern PID_T yaw_pid;

/* 角度环参数 */
#define ANGLE_PID_KP      18.0f    /* 比例系数 */
#define ANGLE_PID_KI       0.0f    /* 积分系数 */
#define ANGLE_PID_KD       0.0f    /* 微分系数 */
#define ANGLE_PID_LIMIT   2000.0f   /* PID 输出限幅 (PWM 占空比) */

/**
 * @brief 初始化角度闭环控制
 * @note 初始化 yaw_pid 并设置目标角度为当前角度（原地不动）
 */
void Control_Angle_Init(void);

/**
 * @brief 设置目标偏航角
 * @param angle 目标角度 (度, 0° ~ 360° 或 -180° ~ +180°)
 */
void Control_Angle_SetTarget(float angle);

/**
 * @brief 角度闭环控制循环 — 每 1ms 由主循环调用
 * @note 读取 wit_data.yaw，计算 PID，驱动左右电机差速转向
 */
void Control_Angle_Loop(void);

#endif
