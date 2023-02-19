#ifndef ENGINESOUND__H
#define ENGINESOUND__H

#include "stm32f103xe.h"

//#define ENGINE_PWM_TIMER			TIM3
//#define ENGINE_PWM_CHANNEL		TIM_CHANNEL_4

void engineSoundInit(void);
void engineSoundStart(void);
void engineSoundStop(void);
void engineSoundSimulation(int16_t throttle);

#endif
