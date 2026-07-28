#include <stdint.h>
#include "camera.h"
#include "ti_msp_dl_config.h"

uint8_t cam_dmaBuffer[33];
Camera_Data_t camera_data;

/*******************************************************************************
 * @brief 初始化 K230 摄像头 DMA 接收
 * @note  UART 硬件和 DMA 通道已由 SysConfig 初始化,
 *        这里只需配置 DMA 运行时参数 (源/目标地址, 传输大小)
 *******************************************************************************/
void Camera_Init(void)
{
    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID,(uint32_t)(&UART_K230_INST->RXDATA));
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID,(uint32_t)&cam_dmaBuffer[0]);
    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, 32);
    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
    NVIC_EnableIRQ(UART_K230_INST_INT_IRQN);

}
