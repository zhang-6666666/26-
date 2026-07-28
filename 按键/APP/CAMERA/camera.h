#ifndef __CAMERA_H
#define __CAMERA_H

#include "ti_msp_dl_config.h"

/* K230 摄像头发送的坐标数据 */
typedef struct {
    int16_t x;          /* 目标 X 坐标 */
    int16_t y;          /* 目标 Y 坐标 */
    uint8_t is_new;     /* 新数据标志: 1=有新帧, 0=已被消费 */
} Camera_Data_t;

extern Camera_Data_t camera_data;

void Camera_Init(void);

#endif /* __CAMERA_H */
