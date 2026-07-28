#ifndef KEY_H
#define KEY_H

#include <ti/driverlib/driverlib.h>

/* ── 按键参数宏 ─────────────────────────────────────────── */
#define KEY_SCAN_MS         20    /* 扫描周期 (ms)，与 Key_Tick 内 Count 阈值一致 */
#define KEY_LONG_PRESS_MS  2000   /* 长按判定阈值 (ms)                              */

/* 转换为扫描次数: 长按阈值 / 扫描周期 */
#define KEY_LONG_PRESS_CNT  (KEY_LONG_PRESS_MS / KEY_SCAN_MS)

/* ── 短按标志 ──────────────────────────────────────────── */
extern volatile uint8_t key_1_flag;
extern volatile uint8_t key_2_flag;
extern volatile uint8_t key_3_flag;
extern volatile uint8_t key_4_flag;

/* ── 长按标志 ──────────────────────────────────────────── */
extern volatile uint8_t key_1_long_flag;
extern volatile uint8_t key_2_long_flag;
extern volatile uint8_t key_3_long_flag;
extern volatile uint8_t key_4_long_flag;

void Key_Edge_Scan(void);
void Key_Tick(void);

#endif
