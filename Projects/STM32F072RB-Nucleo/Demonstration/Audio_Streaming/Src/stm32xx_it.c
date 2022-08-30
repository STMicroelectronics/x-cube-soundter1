/**
  ******************************************************************************
  * @file    stm32xx_it.c
  * @author  SRA
  * 
  * 
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file in
  * the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *                             
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32xx_it.h"

/** @addtogroup X_CUBE_SOUNDTER1_Applications
  * @{
  */

/** @addtogroup Audio_Streaming
  * @{
  */

/** @defgroup INTERRUPT_HANDLER
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*             Cortex-M0+ Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  HAL_IncTick();
}

#ifdef USE_STM32L4XX_NUCLEO
/**
  * @brief  This function handles DMA Stream interrupt request for First Device.
  * @param  None
  * @retval None
  */
void AUDIO_OUT1_IRQHandler(void)
{

  HAL_DMA_IRQHandler(hAudioOut[0].hdmatx);
}

/**
  * @brief  This function handles DMA Stream interrupt request for Second Device.
  * @param  None
  * @retval None
  */
void AUDIO_OUT2_IRQHandler(void)
{

  HAL_DMA_IRQHandler(hAudioOut[1].hdmatx);
}

#else

/**
  * @brief  This function handles DMA Stream interrupt request for First Device.
  * @param  None
  * @retval None
  */
void AUDIO_OUT1_IRQHandler(void)
{

  HAL_DMA_IRQHandler(hAudioOut[0].hdmatx);
}

/**
  * @brief  This function handles DMA Stream interrupt request for Second Device.
  * @param  None
  * @retval None
  */
void AUDIO_OUT2_IRQHandler(void)
{

  HAL_DMA_IRQHandler(hAudioOut[1].hdmatx);
}
#endif

/**
  * @brief  This function handles External lines 15 to 10 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
}

/**
  * @brief  This function handles External lines 4 to 15 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_15_IRQHandler(void)
{
  HAL_GPIO_EXTI_IRQHandler(KEY_BUTTON_PIN);
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


