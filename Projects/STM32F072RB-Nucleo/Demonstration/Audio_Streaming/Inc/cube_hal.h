/**
  ******************************************************************************
  * @file    cube_hal.h
  * @author  SRA
  * 
  * 
  * @brief   Clock tree configuration header and include file
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

#ifndef _CUBE_HAL_H_
#define _CUBE_HAL_H_

/* Includes ------------------------------------------------------------------*/
#ifdef USE_STM32F4XX_NUCLEO
#define USB_IRQHandler OTG_FS_IRQHandler
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32xx_it.h"
#include "stm32f4xx_nucleo.h"
#include "audio_application.h"
#include "cca01m1_audio.h"
#include "cca01m1_audio_ex.h"
#endif

#ifdef USE_STM32F0XX_NUCLEO
#include "stm32f0xx_hal.h"
#include "stm32f0xx.h"
#include "stm32xx_it.h"
#include "stm32f0xx_nucleo.h"
#include "audio_application.h"
#include "cca01m1_audio.h"
#include "cca01m1_audio_ex.h"
#endif

#ifdef USE_STM32L0XX_NUCLEO
#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32xx_it.h"
#include "stm32l0xx_nucleo.h"
#include "audio_application.h"
#include "cca01m1_audio.h"
#include "cca01m1_audio_ex.h"
#endif

#ifdef USE_STM32L4XX_NUCLEO
#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include "stm32xx_it.h"
#include "stm32l4xx_nucleo.h"
#include "audio_application.h"
#include "cca01m1_audio.h"
#include "cca01m1_audio_ex.h"
#endif

#ifdef USE_STM32F7XX_NUCLEO_144
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#include "stm32xx_it.h"
#include "stm32f7xx_nucleo_144.h"
#include "audio_application.h"
#include "cca01m1_audio.h"
#include "cca01m1_audio_ex.h"
#endif

#ifdef USE_STM32F3XX_NUCLEO
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32xx_it.h"
#include "stm32f3xx_nucleo.h"
#include "audio_application.h"
#include "cca01m1_audio.h"
#include "cca01m1_audio_ex.h"
#endif

void SystemClock_Config(void);

#endif //_CUBE_HAL_H_
