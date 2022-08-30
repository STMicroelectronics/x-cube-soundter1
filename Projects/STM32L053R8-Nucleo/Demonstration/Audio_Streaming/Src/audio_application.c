/**
  ******************************************************************************
  * @file    audio_application.c
  * @author  SRA
  * 
  * 
  * @brief   Audio output application.
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
#include "audio_application.h"
#include "BiquadPresets.h"

/** @addtogroup X_CUBE_SOUNDTER1_Applications
  * @{
  */

/** @addtogroup Audio_Streaming
  * @{
  */

/** @defgroup AUDIO_APPLICATION
  * @{
  */

/** @defgroup AUDIO_APPLICATION_Exported_Variables
  * @{
  */

/**
  * @}
  */

/** @defgroup AUDIO_APPLICATION_Private_Variables
  * @{
  */
#define DEMO_NUMBER 5
static int16_t Audio_output_buffer[AUDIO_OUT_BUFFER_SIZE * 2];

CCA01M1_AUDIO_Init_t OutParams;
/**
  * @}
  */

/** @defgroup AUDIO_APPLICATION_Exported_Function
  * @{
  */

/**
  * @brief  Initializes all the required peripherals using the BSP Init function.
  * @param  None
  * @retval AUDIO_OK if no problem during initialization, AUDIO_ERROR otherwise
  */
uint32_t Init_AudioOut_Device(void)
{
  OutParams.BitsPerSample = 16;
  OutParams.ChannelsNbr = AUDIO_OUT_CHANNELS;
  OutParams.Device = STA350BW_0;
  OutParams.SampleRate = AUDIO_OUT_SAMPLING_FREQUENCY;
  OutParams.Volume = AUDIO_VOLUME_OUT;

  return CCA01M1_AUDIO_OUT_Init(CCA01M1_AUDIO_OUT_INSTANCE, &OutParams);
}

/**
  * @brief  Starts audio output.
  * @param  None
  * @retval AUDIO_OK if no problem during initialization, AUDIO_ERROR otherwise
  */
uint32_t Start_AudioOut_Device(void)
{
  return CCA01M1_AUDIO_OUT_Play(CCA01M1_AUDIO_OUT_INSTANCE, (uint8_t *)Audio_output_buffer, AUDIO_OUT_BUFFER_SIZE * 2);
}

/**
  * @brief  Stops audio output.
  * @param  None
  * @retval AUDIO_OK if no problem during initialization, AUDIO_ERROR otherwise
  */
uint32_t Stop_AudioOut_Device(void)
{
  return CCA01M1_AUDIO_OUT_Stop(CCA01M1_AUDIO_OUT_INSTANCE);
}

/**
  * @brief  Switch Filter configuration for demo purpose.
  * @param  None
  * @retval AUDIO_OK if no problem during initialization, AUDIO_ERROR otherwise
  */
uint32_t Switch_Demo(void)
{
  BIQUAD_Filter_t Biquad_filter;
  uint8_t ret = 0;
  static uint8_t current_demo = 0;

  switch (current_demo)
  {
    case 0:
    {
      /*Setup Default Master Volume (in case this has been change during demos*/
      CCA01M1_AUDIO_OUT_SetVolume(CCA01M1_AUDIO_OUT_INSTANCE, AUDIO_VOLUME_OUT);

      /*Setup a Second Order High Pass with Fc = 1 KHz using the first biq filter for each channel. Coefficients are stored in BANK 1*/
      /*When coefficients are written to RAM, EQ is automatically activated
      It's possible to switch between different pre-stores presets switching RAM banks using SetDSPOptions with the STA350BW_RAM_BANK_SELECT
      parameter, for example:
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SELECT,STA350BW_RAM_BANK_FIRST);*/

      Biquad_filter.Type = BIQUAD_CALCULATOR_SO_HPF;
      Biquad_filter.Fs = AUDIO_OUT_SAMPLING_FREQUENCY;
      Biquad_filter.Fc = 1000;
      Biquad_filter.Q = 0.80;
      Biquad_filter.Slope = 0; /*Not used for this kind of filter*/
      Biquad_filter.Gain = 0; /*Not used for this kind of filter*/
      BQ_CALC_ComputeFilter(&Biquad_filter);
      CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_FIRST, STA350BW_CH1_BQ1,
                              Biquad_filter.Coefficients);
      CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_FIRST, STA350BW_CH2_BQ1,
                              Biquad_filter.Coefficients);

      /*Remove EQ and Tone bypass  (in case this has been change during demos)*/
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_C1EQBP, STA350BW_DISABLE);
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_C2EQBP, STA350BW_DISABLE);
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_C1TCB, STA350BW_DISABLE);
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_C2TCB, STA350BW_DISABLE);

      break;
    }
    case 1:
    {
      /*Setup a preset for Bass Boost using 4 biquads for each channel. Coefficients are stored in BANK 2*/
      /*When coefficients are written to RAM, EQ is automatically activated
      It's possible to switch between different pre-stores presets switching RAM banks using SetDSPOptions with the STA350BW_RAM_BANK_SELECT
      parameter, for example:
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SELECT,STA350BW_RAM_BANK_FIRST);*/

      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ1, (uint32_t *)&BASS_BOOST2_EQ_PRESET[0]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ2, (uint32_t *)&BASS_BOOST2_EQ_PRESET[5]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ3, (uint32_t *)&BASS_BOOST2_EQ_PRESET[10]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SECOND, STA350BW_CH1_BQ4, (uint32_t *)&BASS_BOOST2_EQ_PRESET[15]);

      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ1, (uint32_t *)&BASS_BOOST2_EQ_PRESET[0]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ2, (uint32_t *)&BASS_BOOST2_EQ_PRESET[5]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ3, (uint32_t *)&BASS_BOOST2_EQ_PRESET[10]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SECOND, STA350BW_CH2_BQ4, (uint32_t *)&BASS_BOOST2_EQ_PRESET[15]);

      break;
    }
    case 2:
    {
      /*Setup a preset for Vocal using 4 biquads for each channel. Coefficients are stored in BANK 3*/
      /*When coefficients are written to RAM, EQ is automatically activated
      It's possible to switch between different pre-stores presets switching RAM banks using SetDSPOptions with the STA350BW_RAM_BANK_SELECT
      parameter, for example:
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_SELECT,STA350BW_RAM_BANK_FIRST);*/

      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_THIRD, STA350BW_CH1_BQ1, (uint32_t *)&VOCAL_EQ_PRESET[0]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_THIRD, STA350BW_CH1_BQ2, (uint32_t *)&VOCAL_EQ_PRESET[5]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_THIRD, STA350BW_CH1_BQ3, (uint32_t *)&VOCAL_EQ_PRESET[10]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_THIRD, STA350BW_CH1_BQ4, (uint32_t *)&VOCAL_EQ_PRESET[15]);

      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_THIRD, STA350BW_CH2_BQ1, (uint32_t *)&VOCAL_EQ_PRESET[0]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_THIRD, STA350BW_CH2_BQ2, (uint32_t *)&VOCAL_EQ_PRESET[5]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_THIRD, STA350BW_CH2_BQ3, (uint32_t *)&VOCAL_EQ_PRESET[10]);
      ret = CCA01M1_AUDIO_OUT_SetEq(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_RAM_BANK_THIRD, STA350BW_CH2_BQ4, (uint32_t *)&VOCAL_EQ_PRESET[15]);

      break;
    }
    case 3:
    {
      /*Bypass BIQ Filters for both channels*/
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_C1EQBP, STA350BW_ENABLE);
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_C2EQBP, STA350BW_ENABLE);

      /*Change tone settings*/
      CCA01M1_AUDIO_OUT_SetTone(CCA01M1_AUDIO_OUT_INSTANCE, 0xF0);

      break;
    }
    case 4:
    {
      /*Bypass tone control for both channels*/
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_C1TCB, STA350BW_ENABLE);
      CCA01M1_AUDIO_OUT_SetDSPOption(CCA01M1_AUDIO_OUT_INSTANCE, STA350BW_C2TCB, STA350BW_ENABLE);

      /*Modify master volume*/
      CCA01M1_AUDIO_OUT_SetVolume(CCA01M1_AUDIO_OUT_INSTANCE, 0X30);
      break;
    }
  }
  current_demo = (current_demo + 1) % DEMO_NUMBER;
  return ret;
}

/**
  * @brief  Manages the DMA Half Transfer complete event.
  * @param  OutputDevice: the sound terminal device related to the DMA
  *         channel that generates the interrupt
  * @retval None
  */
void CCA01M1_AUDIO_OUT_HalfTransfer_CallBack(uint32_t Instance)
{
  uint32_t i = 0;
#ifndef USE_STM32L0XX_NUCLEO

  /*Copy song fragment to Audio Output buffer*/
  for (i = 0; i < AUDIO_OUT_BUFFER_SIZE / 2; i++)
  {
    Audio_output_buffer[2 * i] = Fragment1[song_position]; /*Left Channel*/
    Audio_output_buffer[2 * i + 1] = Fragment1[song_position]; /*Right Channel*/
    song_position = (song_position + 1) % Fragment1_size;
  }
#else
  /*Generate White Noise for the Output buffer*/
  for (i = 0; i < AUDIO_OUT_BUFFER_SIZE / 2; i++)
  {
    Audio_output_buffer[2 * i] = (rand() % 65536) - 32768;
    Audio_output_buffer[2 * i + 1] =  Audio_output_buffer[2 * i];
  }
#endif

}

/**
  * @brief  Manages the DMA Transfer complete event.
  * @param  OutputDevice: the sound terminal device related to the DMA
  *         channel that generates the interrupt
  * @retval None
  */
void CCA01M1_AUDIO_OUT_TransferComplete_CallBack(uint32_t Instance)
{

  uint32_t i = 0;
#ifndef USE_STM32L0XX_NUCLEO
  /*Copy song fragment to Audio Output buffer*/
  for (i = AUDIO_OUT_BUFFER_SIZE / 2; i < AUDIO_OUT_BUFFER_SIZE; i++)
  {
    Audio_output_buffer[2 * i] = Fragment1[song_position]; /*Left Channel*/
    Audio_output_buffer[2 * i + 1] = Fragment1[song_position]; /*Right Channel*/
    song_position = (song_position + 1) % Fragment1_size;
  }
#else
  /*Generate White Noise for the Output buffer*/
  for (i = AUDIO_OUT_BUFFER_SIZE / 2; i < AUDIO_OUT_BUFFER_SIZE; i++)
  {
    Audio_output_buffer[2 * i] = (rand() % 65536) - 32768;
    Audio_output_buffer[2 * i + 1] =  Audio_output_buffer[2 * i];
  }
#endif

}

/**
  * @brief EXTI line detection callbacks
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == KEY_BUTTON_PIN)
  {
    /* Toggle LED3 */
    BSP_LED_Toggle(LED2);
    Switch_Demo();
  }
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

/**
  * @}
  */


