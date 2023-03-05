#ifndef ENGINESETTINGS_H
#define ENGINESETTINGS_H

//*
//* Selecting the engine. | Выбор двигателя.
//* Note: You only need to uncomment one. The first one is used, the subsequent ones are ignored. | Примечание: необходимо раскомментировать только один. Используется первый, последующие игнорируются.
//*

#include "Engines\1kHz.h"

//* ========================================================================================================================================================================================

// Engine RPM range
#define TOP_SPEED_MULTIPLIER 50 // RPM multiplier: the bigger the number the larger the rev range, 20 - 50 is a good place to start (for most sounds = 30)
const short maxRpm = 1023; // max. 1023
const short minRpm = 0; // always 0

// Engine mass simulation
const char acc = 9; // Acceleration step per 5ms (9)
const char dec = 6; // Deceleration step per 5ms (6)

//* ========================================================================================================================================================================================



#endif
