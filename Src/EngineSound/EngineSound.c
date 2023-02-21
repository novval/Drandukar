//* 
//* Based on the idea of TheDIYGUY999 https://github.com/TheDIYGuy999/Rc_Engine_Sound
//* Thx for TheDIYGUY999.
//*
//* 2023-02-17
//*

#include "EngineSound.h"
#include "curves.h"
//#include "core_cm3.h"
//#include "stm32f1xx_hal.h"

// for LED_PIN debug
#include "defines.h"

#include "util.h"
extern InputStruct input2[INPUTS_NR];

#define PROGMEM
//#include "Engines\DefenderV8Start.h"
#include "Engines\ScaniaV8Start.h"
#include "Engines\ScaniaV8Idle.h"
//#include "Engines\UralV8Start.h"
//#include "Engines\1KhZ.h"
//#include "Engines\UralV8Idle.h"
//#include "Engines\chevyNovaV8.h"

//* from #include "settings.h"
// Engine RPM range
#define TOP_SPEED_MULTIPLIER 50 		// RPM multiplier: the bigger the number the larger the rev range, 20 - 50 is a good place to start (for most sounds = 30)
static const int16_t maxRpm = 1023; // max. 1023
static const int16_t minRpm = 0;		// always 0

// Engine mass simulation
static const int8_t acc = 9; // Acceleration step per 5ms (9)
static const int8_t dec = 6; // Deceleration step per 5ms (6)
//* end of #include "settings.h"

#define VOLUME_DECREASE		4

#define SAMPLE_RATE			16000
#define SAMPLE_BITS			8

#define PWM_DEFAULT_ARR		(1<<SAMPLE_BITS)
#define PWM_DEFAULT_CRR		(1<<(SAMPLE_BITS-1))
#define SND_DEFAULT_ARR		(SystemCoreClock / SAMPLE_RATE)

extern const __IO uint32_t uwTick;
#define millis()		uwTick

static enum EngineState {
	eStopped = 0,
	eStarting,
	eRunning,
	eStopping
} state;
static int samplePos;
static int sampleRate;

static void pwmTimerInit()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	
	GPIOB->CRH &= ~(GPIO_CRH_CNF9);
	GPIOB->CRH |= GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_1;

	TIM4->PSC = 0;
	TIM4->ARR = PWM_DEFAULT_ARR;
	TIM4->CCR4 = PWM_DEFAULT_CRR;
	TIM4->CCER |= TIM_CCER_CC4E;
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1;
	TIM4->CR1 |= TIM_CR1_CEN;
}

static void sndTimerInit()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

  HAL_NVIC_SetPriority(TIM3_IRQn, 0, 0);
	NVIC_EnableIRQ(TIM3_IRQn);
	
	TIM3->PSC = 0;
	TIM3->ARR = SND_DEFAULT_ARR;
	TIM3->DIER |= TIM_DIER_UIE;
	TIM3->CR1 |= TIM_CR1_CEN;
}

void engineSoundInit(void)
{
	engineSoundStop();
	state = eStopped;
	pwmTimerInit();
	sndTimerInit();
}

void engineSoundStart(void)
{
	state = eStarting;
	samplePos = 0;
	sampleRate = SND_DEFAULT_ARR;
}

void engineSoundStop(void)
{
	state = eStopping;
	samplePos = 0;
	sampleRate = SND_DEFAULT_ARR;
}

void engineSoundSimulation(int16_t throttle)
{
  static int16_t mappedThrottle = 0;
  static int16_t currentRpm = 0;
//  static unsigned long throtMillis = 0;

	if (state != eRunning)
		return;
	
//  if (millis() > throtMillis){//5) { // Every 5ms
//    throtMillis = millis();
		// compute unlinear throttle curve
		mappedThrottle = reMap(curveShifting, throttle / 2);
		if (mappedThrottle + acc > currentRpm && state == eRunning) { // Accelerate engine
			currentRpm += acc;
			if (currentRpm > maxRpm)
				currentRpm = maxRpm;
		} else if (mappedThrottle - dec < currentRpm) { // Decelerate engine
			currentRpm -= dec;
			if (currentRpm < minRpm)
				currentRpm = minRpm;
		}
		// Speed (sample rate) output
		sampleRate = SystemCoreClock / (BASE_RATE + (long)(currentRpm * TOP_SPEED_MULTIPLIER));
  	printf("st=%d, id1=%5d, id1=%5d, thr=%4d, map=%4d, rpm=%4d, arr=%4d, smr=%5d\r\n", state, input2[0].raw, input2[1].raw, throttle, mappedThrottle, currentRpm, sampleRate, SystemCoreClock / sampleRate);
//	}
}

void TIM3_IRQHandler()
{
	HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET);

  static float attenuator = 1;

	switch (state) {
		case eStopped:
			break;
		case eStarting:
			if (samplePos >= start_length) {
				samplePos = 0;
				state = eRunning;
			}
			TIM4->CCR4 = start_data[samplePos++]>>VOLUME_DECREASE;
			break;
		case eRunning:
			if (samplePos >= idle_length)
				samplePos = 0;
			TIM4->CCR4 = idle_data[samplePos++]>>VOLUME_DECREASE;
			break;
		case eStopping:
			if (samplePos >= idle_length)
				samplePos = 0;
			TIM4->CCR4 = (idle_data[samplePos++]>>VOLUME_DECREASE) / attenuator;
      attenuator += 0.001;
      if (attenuator >= 20) {  // 3 - 20
				state = eStopped;
				//TIM4->CCR4 = PWM_DEFAULT_CRR;
			}
      break;
	}

	TIM3->ARR = sampleRate;
	
	TIM3->SR &= ~TIM_SR_UIF;

	HAL_GPIO_TogglePin(LED_PORT, LED_PIN);
}
