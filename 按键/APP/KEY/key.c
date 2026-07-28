#include "key.h"
#include "ti_msp_dl_config.h"

/* ── Per-key state ───────────────────────────────────────────── */
typedef struct {
    GPIO_Regs     *port;        /* GPIO 端口 (KEY_KEY_N_PORT)       */
    uint32_t       pin;         /* 引脚     (KEY_KEY_N_PIN)         */
    volatile uint8_t *flag;    /* 指向对应的 key_N_flag (短按)     */
    volatile uint8_t *long_flag; /* 指向对应的 key_N_long_flag     */
    int            last_high;   /* 0=等待按下, 1=等待释放           */
    uint8_t        hold_count;  /* 按住期间的扫描次数 (×20ms)      */
} KeyInfo_t;

/* ── Key press flags ─────────────────────────────────────────── */
volatile uint8_t key_1_flag;
volatile uint8_t key_2_flag;
volatile uint8_t key_3_flag;
volatile uint8_t key_4_flag;

volatile uint8_t key_1_long_flag;
volatile uint8_t key_2_long_flag;
volatile uint8_t key_3_long_flag;
volatile uint8_t key_4_long_flag;

/* ── Key configuration array ─────────────────────────────────── */
static KeyInfo_t key_info[4] = {
    { KEY_KEY_1_PORT, KEY_KEY_1_PIN, &key_1_flag, &key_1_long_flag, 0, 0 },
    { KEY_KEY_2_PORT, KEY_KEY_2_PIN, &key_2_flag, &key_2_long_flag, 0, 0 },
    { KEY_KEY_3_PORT, KEY_KEY_3_PIN, &key_3_flag, &key_3_long_flag, 0, 0 },
    { KEY_KEY_4_PORT, KEY_KEY_4_PIN, &key_4_flag, &key_4_long_flag, 0, 0 },
};

/* ── Public API ──────────────────────────────────────────────── */
void Key_Edge_Scan(void)
{
    for (int i = 0; i < 4; i++) {
        KeyInfo_t *k = &key_info[i];

        /* 阶段1: 检测上升沿（按键按下） */
        if (k->last_high == 0) {
            if (DL_GPIO_readPins(k->port, k->pin)) {
                k->last_high  = 1;
                k->hold_count = 0;
            }
        }

        /* 阶段2: 按住期间 — 长按计时 */
        if (k->last_high == 1 && DL_GPIO_readPins(k->port, k->pin)) {
            k->hold_count++;
            if (k->hold_count >= KEY_LONG_PRESS_CNT && *k->long_flag == 0) {
                *k->long_flag = 1;
            }
        }

        /* 阶段3: 检测下降沿（按键释放 → 确认短按） */
        if (k->last_high == 1 && !DL_GPIO_readPins(k->port, k->pin)) {
            if (*k->flag == 0) {
                *k->flag = 1;
            }
            k->last_high  = 0;
            k->hold_count = 0;
        }
    }
}

void Key_Tick(void)
{
    static uint8_t Count;

    Count ++;
    if(Count >= 20)
    {
        Count = 0;

        Key_Edge_Scan();
    }
}
