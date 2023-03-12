#ifndef ENGINESOUND_H
#define ENGINESOUND_H

#if (ENGINE_SOUND_USE) && (ENGINE_SOUND_ON)
void engineSoundStart(void);
void engineSoundStop(void);
void engineSoundSimulation(short throttle);
#else
#define engineSoundInit()
#define engineSoundStart()
#define engineSoundStop()
#define engineSoundSimulation(throttle)
#endif

#endif
