#ifndef ENGINESETTINGS_H
#define ENGINESETTINGS_H

//*
//* Selecting the engine. | Выбор двигателя.
//* Note: Uncomment only one line containing "...Start.h", and only one line containing "...Idle.h". | Примечание: Раскомментируйте только одну строку содержащую "...Start.h", и только одну строку содержащую "...Idle.h".
//*
//#include "Engines\1965FordMustangV8start.h"
//#include "Engines\1965FordMustangV8Idle.h"
//#include "Engines\1981KenworthW900A_DetroitStart.h"
//#include "Engines\1981KenworthW900A_DetroitIdle.h"
//#include "Engines\468ChevyBigBlockStart.h"
//#include "Engines\468ChevyBigBlockIdle.h"
#include "Engines\62LS3Start.h"
#include "Engines\62LS3Idle.h"
//#include "Engines\8v92PeterbiltStart.h"
//#include "Engines\8v92PeterbiltIdle.h"
//#include "Engines\Actros1863start.h"
//#include "Engines\Actros1863Idle.h"
//#include "Engines\ActrosV6Start.h"
//#include "Engines\ActrosV6Idle.h"
//#include "Engines\ActrosV8Start.h"
//#include "Engines\ActrosV8Idle.h"
//#include "Engines\AdlerStart.h"
//#include "Engines\AdlerIdle.h"
//#include "Engines\BENFORD3TONStart.h"
//#include "Engines\BENFORD3TONIdle.h"
//#include "Engines\Cat3406BStart.h"
//#include "Engines\Cat3406BIdle.h"
//#include "Engines\Cat3408Start.h"
//#include "Engines\Cat3408Idle.h"
//#include "Engines\Cat3408newStart.h"
//#include "Engines\Cat3408newIdle.h"
//#include "Engines\Caterpillar323Start.h"
//#include "Engines\Caterpillar323Idle.h"
//#include "Engines\ChevyPickupV8SoundStart.h"
//#include "Engines\ChevyPickupV8SoundIdle.h"
//#include "Engines\DefenderTd5start.h"
//#include "Engines\DefenderTd5Idle.h"
//#include "Engines\DefenderV8OpenPipeStart.h"
//#include "Engines\DefenderV8OpenPipeIdle.h"
//#include "Engines\DefenderV8Start.h"
//#include "Engines\DefenderV8Idle.h"
//#include "Engines\DetroitDieselStart.h"
//#include "Engines\DetroitDieselIdle.h"
//#include "Engines\GAZ66start.h"
//#include "Engines\GAZ66Idle.h"
//#include "Engines\HarleyDavidsonFXSBStart.h"
//#include "Engines\HarleyDavidsonFXSBIdle.h"
//#include "Engines\HgP408Start.h"
//#include "Engines\HgP408Idle.h"
//#include "Engines\IS3TankStart.h"
//#include "Engines\IS3TankIdle.h"
//#include "Engines\InternationalDT-466Start.h"
//#include "Engines\InternationalDT-466Idle.h"
//#include "Engines\JeepGrandCherokeeTrackhawkStart.h"
//#include "Engines\JeepGrandCherokeeTrackhawkIdle.h"
//#include "Engines\JeepWranglerRubicon392V8Start.h"
//#include "Engines\JeepWranglerRubicon392V8Idle.h"
//#include "Engines\KenworthCummins335Start.h"
//#include "Engines\KenworthCummins335Idle.h"
//#include "Engines\KenworthW900Start.h"
//#include "Engines\KenworthW900Idle.h"
//#include "Engines\KirovetsK700start.h"
//#include "Engines\KirovetsK700Idle.h"
//#include "Engines\LaFerrariStart.h"
//#include "Engines\LaFerrariIdle.h"
//#include "Engines\Landcruiser12HTstart.h"
//#include "Engines\Landcruiser12HTIdle.h"
//#include "Engines\MANTGXstart.h"
//#include "Engines\MANTGXIdle.h"
//#include "Engines\MGBGtV8start.h"
//#include "Engines\MGBGtV8Idle.h"
//#include "Engines\MackStart.h"
//#include "Engines\MackIdle.h"
//#include "Engines\MagirusDeutz256Start.h"
//#include "Engines\MagirusDeutz256Idle.h"
//#include "Engines\ManKatStart.h"
//#include "Engines\ManKatIdle.h"
//#include "Engines\Saurer2DMstart.h"
//#include "Engines\Saurer2DMIdle.h"
//#include "Engines\ScaniaV850tonStart.h"
//#include "Engines\ScaniaV850tonIdle.h"
//#include "Engines\ScaniaV8start.h"
//#include "Engines\ScaniaV8Idle.h"
//#include "Engines\Tatra813start.h"
//#include "Engines\Tatra813Idle.h"
//#include "Engines\URAL375start.h"
//#include "Engines\URAL375Idle.h"
//#include "Engines\UnionPacific2002start.h"
//#include "Engines\UnionPacific2002Idle.h"
//#include "Engines\Ural375Dstart.h"
//#include "Engines\Ural375DIdle.h"
//#include "Engines\UralV8Start.h"
//#include "Engines\UralV8Idle.h"
//#include "Engines\VWBeetleStart.h"
//#include "Engines\VWBeetleIdle.h"

//* Sinus 1kHz for test and measurement.
//#include "Engines\1kHz.h" 

//* ========================================================================================================================================================================================

// Engine RPM range
#define TOP_SPEED_MULTIPLIER 50 // RPM multiplier: the bigger the number the larger the rev range, 20 - 50 is a good place to start (for most sounds = 30)
const short maxRpm = 1023; // max. 1023
const short minRpm = 0; // always 0

// Engine mass simulation
const char acc = 9; // Acceleration step per 5ms (9)
const char dec = 6; // Deceleration step per 5ms (6)

//* ========================================================================================================================================================================================

#if !defined(ENGINESOUNDSTARTDATA_H)
#error "Select engine start. | Выберите старт двигателя."
#endif
#if !defined(ENGINESOUNDIDLEDATA_H)
#error "Select engine idling. | Выберите холостой ход двигателя."
#endif

#endif
