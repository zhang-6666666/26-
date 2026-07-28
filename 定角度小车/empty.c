#include <math.h>
#include <stdio.h>
#include <string.h>

#include "ti/driverlib/dl_uart_main.h"
#include "ti_msp_dl_config.h"
#include "APP/MOTOR/motor.h"
#include "APP/TIMER/timer.h"
#include "APP/WIT/wit.h"
#include "APP/PID/pid.h"
#include "APP/CONTROL/control.h"


void Send_String(char *str);


int main(void)
{
    SYSCFG_DL_init();

    /* 电机 */
    Motor_Init(&motor_left,
               MOTOR_PORT, MOTOR_AIN1_PIN,
               MOTOR_PORT, MOTOR_AIN2_PIN,
               PWM_0_INST, GPIO_PWM_0_C0_IDX);
    Motor_Init(&motor_right,
               MOTOR_PORT, MOTOR_BIN1_PIN,
               MOTOR_PORT, MOTOR_BIN2_PIN,
               PWM_0_INST, GPIO_PWM_0_C1_IDX);

    /* 系统滴答: 1ms */
    Timer_Init();
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    WIT_Init();
    Control_Angle_Init();
    

    /* 主循环: 由 sys_tick 1ms 驱动 */
    uint32_t next_log  = 100;
    while (1) 
    {
        /* 100ms 串口输出 */
        if (sys_tick >= next_log) 
        {
            next_log += 100;
            char YAW[32];
            sprintf(YAW, "angle:%.2f \r\n", wit_data.yaw);
            Send_String(YAW);
            Control_Angle_Loop();

        }
        
    }
}



/* 自定义串口阻塞式发送 */
void Send_String(char *str)
{
    while(*str != '\0') 
    {
        DL_UART_Main_transmitDataBlocking(DEBUG_INST, (uint8_t)(*str++));
    }
}


/* 系统滴答: 只做计数 */
void TIMA1_IRQHandler(void)
{
    DL_Timer_clearInterruptStatus(TIMER_0_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT);
    sys_tick++;
}


#if defined UART_WIT_INST_IRQHandler
void UART_WIT_INST_IRQHandler(void)
{
    uint8_t checkSum, packCnt = 0;
    extern uint8_t wit_dmaBuffer[33];

    DL_DMA_disableChannel(DMA, DMA_WIT_CHAN_ID);
    uint8_t rxSize = 32 - DL_DMA_getTransferSize(DMA, DMA_WIT_CHAN_ID);

    if(DL_UART_isRXFIFOEmpty(UART_WIT_INST) == false)
        wit_dmaBuffer[rxSize++] = DL_UART_receiveData(UART_WIT_INST);

    while(rxSize >= 11)
    {
        checkSum=0;
        for(int i=packCnt*11; i<(packCnt+1)*11-1; i++)
            checkSum += wit_dmaBuffer[i];

        if((wit_dmaBuffer[packCnt*11] == 0x55) && (checkSum == wit_dmaBuffer[packCnt*11+10]))
        {
            if(wit_dmaBuffer[packCnt*11+1] == 0x51)
            {
                wit_data.ax = (int16_t)((wit_dmaBuffer[packCnt*11+3]<<8)|wit_dmaBuffer[packCnt*11+2]) / 2.048; //mg
                wit_data.ay = (int16_t)((wit_dmaBuffer[packCnt*11+5]<<8)|wit_dmaBuffer[packCnt*11+4]) / 2.048; //mg
                wit_data.az = (int16_t)((wit_dmaBuffer[packCnt*11+7]<<8)|wit_dmaBuffer[packCnt*11+6]) / 2.048; //mg
                wit_data.temperature =  (int16_t)((wit_dmaBuffer[packCnt*11+9]<<8)|wit_dmaBuffer[packCnt*11+8]) / 100.0; //°C
            }
            else if(wit_dmaBuffer[packCnt*11+1] == 0x52)
            {
                wit_data.gx = (int16_t)((wit_dmaBuffer[packCnt*11+3]<<8)|wit_dmaBuffer[packCnt*11+2]) / 16.384; //°/S
                wit_data.gy = (int16_t)((wit_dmaBuffer[packCnt*11+5]<<8)|wit_dmaBuffer[packCnt*11+4]) / 16.384; //°/S
                wit_data.gz = (int16_t)((wit_dmaBuffer[packCnt*11+7]<<8)|wit_dmaBuffer[packCnt*11+6]) / 16.384; //°/S
            }
            else if(wit_dmaBuffer[packCnt*11+1] == 0x53)
            {
                wit_data.roll  = (int16_t)((wit_dmaBuffer[packCnt*11+3]<<8)|wit_dmaBuffer[packCnt*11+2]) / 32768.0 * 180.0; //°
                wit_data.pitch = (int16_t)((wit_dmaBuffer[packCnt*11+5]<<8)|wit_dmaBuffer[packCnt*11+4]) / 32768.0 * 180.0; //°
                wit_data.yaw   = (int16_t)((wit_dmaBuffer[packCnt*11+7]<<8)|wit_dmaBuffer[packCnt*11+6]) / 32768.0 * 180.0; //°
                wit_data.version = (int16_t)((wit_dmaBuffer[packCnt*11+9]<<8)|wit_dmaBuffer[packCnt*11+8]);
            }
        }

        rxSize -= 11;
        packCnt++;
    }
    
    uint8_t dummy[4];
    DL_UART_drainRXFIFO(UART_WIT_INST, dummy, 4);
    DL_DMA_setDestAddr(DMA, DMA_WIT_CHAN_ID, (uint32_t) &wit_dmaBuffer[0]);
    DL_DMA_setTransferSize(DMA, DMA_WIT_CHAN_ID, 32);
    DL_DMA_enableChannel(DMA, DMA_WIT_CHAN_ID);
}
#endif
