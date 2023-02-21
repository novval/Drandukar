#ifndef ENGINESOUND__H
#define ENGINESOUND__H

#include "stm32f103xe.h"

void engineSoundInit(void);
void engineSoundStart(void);
void engineSoundStop(void);
void engineSoundSimulation(int16_t throttle);

#endif
