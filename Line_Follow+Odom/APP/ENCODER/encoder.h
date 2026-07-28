/* 软件编码器模块 — MSPM0 DriverLib */
#ifndef ENCODER_H
#define ENCODER_H

#include <ti/driverlib/driverlib.h>
#include <stdint.h>

typedef struct {
    GPIO_Regs      *port;
    uint32_t        a_pin, b_pin;
    uint8_t         last_ab;       /* 上一次 AB 电平 (0-3) */
    volatile int32_t cnt;          /* 当前位置 (4倍频累计) */
    volatile int32_t spd;          /* 当前速度 (计数/10ms) */
    volatile int32_t speed_mm_s;   /* 当前速度 (mm/s) */
    volatile int32_t prev_pos;     /* 上次采样位置 */
    volatile uint32_t sample_cnt;  /* 速度采样分频计数 */
} Encoder;

void Encoder_Init(Encoder *e, GPIO_Regs *port, uint32_t a_pin, uint32_t b_pin);
void Encoder_Start(Encoder *e);
int32_t Encoder_GetCount(Encoder *e);
int32_t Encoder_GetSpeed(Encoder *e);
int32_t Encoder_GetDist_mm(Encoder *e);
void Encoder_OnEdge(Encoder *e);
void Encoder_UpdateSpeed(Encoder *e);

extern Encoder encoder_left;
extern Encoder encoder_right;

#endif
