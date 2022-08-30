## __Audio Streaming Demonstration__

The application is designed to play a pre-recorded audio frame, saved in the MCU 
flash memory, by means of the STA350BW device soldered on the X-NUCLEO-CCA01M1 
expansion board. The application can run on STM32F401, STM32F072, STM32L0, STM32L4
and STM32F7. 
It is built on top of STM32Cube software technology that ease portability across 
different STM32 microcontrollers.

The application demonstrates both basic audio functionalities, 
like initialization/play/stop/pause controls, and advanced Sound Terminal® 
features like biquadratic equalization computation and control. 
It is possible to switch between several
equalizations setup using the user button mounted on the STM32 Nucleo board.

In order to achieve these results, the application performs the following steps:
- Initialize communication peripheral, such as I2C and I2S or SAI buses
- initialize STA350BW audio device by means of I2C bus
- Start the playing of the audio frame from the STM32 flash memory
Then, at each click on the User Button, one of the following actions are performed:
- Compute some sets of biquadratic filter coefficients using the relevant  
Sound Terminal® Biquad Calculator middleware. Preset are also used to ease
 audio equalization.
- Set up the filter configurations. 
- Change Tone and Volume values

In the firmware, audio-related parts are collected in the audio_application.c 
file, that makes use of the dedicated X-NUCLEO-CCA01M1 BSP layer and the Sound 
Terminal® Biquad Calculator middleware.

Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
The application need to ensure that the SysTick time base is always set to 1 millisecond
to have correct HAL operation.


### __Hardware and Software environment__

  - This example runs on STM32F401RE, STM32F072RB, STM32L476RG, STM32F746ZG and STM32L053R8 devices.
    
  - This example has been tested with STMicroelectronics STM32F4xx-Nucleo RevB 
    boards and can be easily tailored to any other supported device 
    and development board.
    

### __How to use it?__

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

