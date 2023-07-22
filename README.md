# SoftPWM_STM32F4XX
SoftPWM for STM32F4XX

## About
This Software PWM Libary was mainly focused for Servo Motors or Dimming LEDs, it cant reach high frequncies with a high accuracy, but if you can live  
with it not being on point, you can maybe be happy with it at higher frequencies.  
  
in sw_pwm.h you can change a macro that chooses how fast the interrupt triggers, choose this as fits for your system and  
requirements
  
## Notes  
the sw_pwm.h libary uses the timer.h libary to keep track of time, if you already have your own implementation you can switch it up with ur own aslong  
as the functions do the same thing  
  
## Dependencies  
This Libary requires the HAL for the STM32F4XX, as it builds up on that  
  
## Example  
You can find the Example in the Example Folder    
it includes a small libary that helps setting up GPIOs more Easily, but also builds on the HAL defines  
It sets up 3 PwmPins on the GPIOA Port the result looks like this :  

![aOBF1H5](https://github.com/Haron123/SoftPWM_STM32F4XX/assets/31776616/c4dbc73c-f313-4c2e-8711-54fbde7fe61a)
