/* 循线模块 — MSPM0 DriverLib */
#ifndef LINE_H
#define LINE_H

#include "ti_msp_dl_config.h"

#define BASE_SPEED   600
#define KP           50.0f
#define TURN_STEER   400

typedef struct {
    int8_t      pos;        /* 质心, 127=丢线 */
    float       yaw;        /* 当前转向量 (正=右, 负=左) */
    float       prev_yaw;   /* 上次转向量 (丢线时沿用) */
    uint8_t     state;      /* 0=丢线, 1=循线, 2=转弯 */
    uint8_t     turn_dir;   /* 上次转弯方向: 0=左, 1=右 */
} Line;

void Line_Init(Line *l);
void Line_Run(Line *l);

extern Line line;

#endif
