/* 软件编码器模块 — MSPM0 DriverLib
 *
 * GPIO 硬件配置 (输入/上拉/双边沿中断) 由 SysConfig 在 SYSCFG_DL_GPIO_init() 中完成。
 * 本模块只管理正交状态机和速度计算。
 */
#include "encoder.h"

Encoder encoder_left;
Encoder encoder_right;

/* 4 倍频正交状态机查找表 */
static const int8_t quad_lut[16] = {
     0, -1, +1,  0,
    +1,  0,  0, -1,
    -1,  0,  0, +1,
     0, +1, -1,  0,
};

void Encoder_Init(Encoder *e, GPIO_Regs *port, uint32_t a_pin, uint32_t b_pin)
{
    e->port       = port;
    e->a_pin      = a_pin;
    e->b_pin      = b_pin;
    e->last_ab    = 0;
    e->cnt        = 0;
    e->spd        = 0;
    e->speed_mm_s = 0;
    e->prev_pos   = 0;
    e->sample_cnt = 0;
}

void Encoder_Start(Encoder *e)
{
    (void)e;
    NVIC_EnableIRQ(GPIOB_INT_IRQn);
}

int32_t Encoder_GetCount(Encoder *e)
{
    return e->cnt;
}

int32_t Encoder_GetSpeed(Encoder *e)
{
    return e->spd;
}

void Encoder_OnEdge(Encoder *e)
{
    uint8_t ab = (DL_GPIO_readPins(e->port, e->a_pin) ? 0b10 : 0b00)
               | (DL_GPIO_readPins(e->port, e->b_pin) ? 0b01 : 0b00);

    e->cnt -= quad_lut[(e->last_ab << 2) | ab];
    e->last_ab = ab;
}

void Encoder_UpdateSpeed(Encoder *e)
{
    if (++e->sample_cnt >= 10) {
        e->spd        = e->cnt - e->prev_pos;   /* 计数/10ms */
        e->speed_mm_s = e->spd * 14;            /* 近似 mm/s: spd×100×204/1463 */
        e->prev_pos   = e->cnt;
        e->sample_cnt = 0;
    }
}

int32_t Encoder_GetDist_mm(Encoder *e)
{
    return e->cnt * 204 / 1463;   /* cnt × 周长mm / cnt_per_rev */
}
