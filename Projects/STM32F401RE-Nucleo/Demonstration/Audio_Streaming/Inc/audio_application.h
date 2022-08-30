/**
  ******************************************************************************
  * @file    audio_application.h 
  * @author  SRA
  * 
  * 
  * @brief   Header for audio_application.c module.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AUDIO_APPLICATION_H
#define __AUDIO_APPLICATION_H

/* Includes ------------------------------------------------------------------*/
#include "cube_hal.h"
#include "Fragment1.h"
#include "BiquadCalculator.h"
#include "stdlib.h"


/** @addtogroup X_CUBE_SOUNDTER1_Applications
* @{
*/ 

/** @addtogroup Audio_Streaming
* @{
*/

/** @defgroup AUDIO_APPLICATION 
* @{
*/


/** @defgroup AUDIO_APPLICATION_Private_Types 
* @{
*/  

/**
* @}
*/ 


/** @defgroup AUDIO_APPLICATION_Exported_Defines 
* @{
*/
#define FILTER_NB 2
/**
* @}
*/


/** @defgroup AUDIO_APPLICATION_Exported_Functions_Prototypes 
* @{
*/
uint32_t Init_Biquads_Filter(void);
uint32_t Init_AudioOut_Device(void);
uint32_t Start_AudioOut_Device(void);
uint32_t Stop_AudioOut_Device(void);
uint32_t Switch_Demo(void);


/**
* @}
*/  

/**
* @}
*/

/**
* @}
*/

/**
* @}
*/



#endif /* __AUDIO_APPLICATION_H */


