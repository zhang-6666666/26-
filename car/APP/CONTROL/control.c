#include "control.h"
#include "APP/MOTOR/motor.h"
#include "APP/WIT/wit.h"

PID_T yaw_pid;

/*******************************************************************************
 * @brief 初始化角度闭环控制
 * @param {}
 * @return {}
 * @note 上电时调用，以当前 yaw 为目标，避免上电瞬间电机猛转
 *******************************************************************************/
void Control_Angle_Init(void)
{
    pid_init(&yaw_pid,
             ANGLE_PID_KP,
             ANGLE_PID_KI,
             ANGLE_PID_KD,
             0,
             ANGLE_PID_LIMIT);
}

/*******************************************************************************
 * @brief 设置目标偏航角
 * @param {float} angle 目标角度
 * @return {}
 * @note 运行时动态修改目标角度
 *******************************************************************************/
void Control_Angle_SetTarget(float angle)
{
    pid_set_target(&yaw_pid, angle);
}

/*******************************************************************************
 * @brief 角度闭环控制循环（每 1ms 调用）
 * @param {}
 * @return {}
 * @note 差速转向：
 *       PID 输出 > 0 → 左轮正转 + 右轮反转 → 顺时针旋转
 *       PID 输出 < 0 → 左轮反转 + 右轮正转 → 逆时针旋转
 *******************************************************************************/
void Control_Angle_Loop(void)
{
    int16_t pid_out;
    int16_t left_pwm, right_pwm;

    /* 1. 计算角度 PID */
    pid_out = (int16_t)pid_calculate_angle_positional(&yaw_pid, wit_data.yaw);

    /* 2. 死区：误差很小时不输出，避免抖动 */
    if (pid_out > -10 && pid_out < 10)
    {
        Motor_Coast(&motor_left);
        Motor_Coast(&motor_right);
        return;
    }

    /* 3. 差速分配：左轮 +pid_out，右轮 -pid_out */
    left_pwm  =  pid_out;
    right_pwm = -pid_out;

    Motor_Run(&motor_left,  left_pwm);
    Motor_Run(&motor_right, right_pwm);
}
