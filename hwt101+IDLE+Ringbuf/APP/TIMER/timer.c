/* 系统滴答 — MSPM0 DriverLib */
#include "timer.h"

volatile uint32_t sys_tick = 0;

void Timer_Init(void)
{
    /* 硬件初始化 (时钟/模式/中断) 由 SysConfig 完成，这里只占位 */
}
