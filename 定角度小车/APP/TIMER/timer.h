/* 系统滴答 — MSPM0 DriverLib
 *
 * 硬件由 SysConfig 在 SYSCFG_DL_TIMER_0_init() 中配置为 1ms 周期定时器。
 * 本模块只做全局计数，供主循环做任务调度。
 */
#ifndef TIMER_H
#define TIMER_H

#include <ti/driverlib/driverlib.h>

extern volatile uint32_t sys_tick;  /* 1ms 全局计数器 */

void Timer_Init(void);

#endif
