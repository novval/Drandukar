//* 
//* Based on the idea of TheDIYGUY999 https://github.com/TheDIYGuy999/Rc_Engine_Sound
//* Thx for TheDIYGUY999.
//*
//* 2023-02-17
//*
#include "config.h"

#if (ENGINE_SOUND_USE) && (ENGINE_SOUND_ON)
#include "EngineSound.h"
#include "EngineCurves.h"
#include "EngineSettings.h"
#include "stm32f1xx_hal.h"

#define SAMPLE_RATE			idleSampleRate
#define SAMPLE_BITS			8

#define SND_DEFAULT_ARR		(SystemCoreClock / SAMPLE_RATE)

//extern const __IO uint32_t uwTick;
//#define millis()		uwTick

static enum EngineState {
	eStopped = 0,
	eStarting,
	eRunning,
	eStopping
} state;

static int16_t mappedThrottle;
static int16_t currentRpm;
//  static unsigned long throtMillis = 0;

static void dacInit()
{
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;

	GPIOA->CRL &= ~(GPIO_CRL_CNF4 | GPIO_CRL_MODE4);

	DAC->CR = DAC_CR_EN1;
}

static void dmaInit()
{
	RCC->AHBENR |= RCC_AHBENR_DMA2EN;

	DMA2_Channel3->CCR = 0;
	DMA2_Channel3->CNDTR = startSampleCount;
	DMA2_Channel3->CPAR = (uint32_t)&DAC->DHR8R1;
	DMA2_Channel3->CMAR = (uint32_t)&startSamples;
	DMA2_Channel3->CCR = DMA_CCR_PL_1 | DMA_CCR_PL_0 | DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_TCIE | DMA_CCR_EN;

  HAL_NVIC_SetPriority(DMA2_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Channel3_IRQn);
}

static void sndTimerInit()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

  HAL_NVIC_SetPriority(TIM6_IRQn, 0, 0);
	NVIC_EnableIRQ(TIM6_IRQn);
	
	TIM6->PSC = 0;
	TIM6->ARR = SND_DEFAULT_ARR;
	TIM6->DIER = TIM_DIER_UDE;
	TIM6->CR2 = TIM_CR2_MMS_1;
	TIM6->CR1 = TIM_CR1_ARPE;
}

static void engineSoundInit(void)
{
	state = eStopped;
	dacInit();
	dmaInit();
	sndTimerInit();
}

void engineSoundStart(void)
{
	engineSoundInit();
	state = eStarting;
	mappedThrottle = 0;
	currentRpm = 0;
//	throtMillis = 0;
	TIM6->ARR = SND_DEFAULT_ARR;
	TIM6->CR1	|= TIM_CR1_CEN;
}

void engineSoundStop(void)
{
	state = eStopping;
	TIM6->ARR = SND_DEFAULT_ARR;
}

void engineSoundSimulation(int16_t throttle)
{
	if (state != eRunning)
		return;
	
//  if (millis() > throtMillis){//5) { // Every 5ms
//    throtMillis = millis();
		// compute unlinear throttle curve
		mappedThrottle = reMap(curveShifting, throttle / 2);
		if (mappedThrottle + acc > currentRpm) { // Accelerate engine
			currentRpm += acc;
			if (currentRpm > maxRpm)
				currentRpm = maxRpm;
		} else if (mappedThrottle - dec < currentRpm) { // Decelerate engine
			currentRpm -= dec;
			if (currentRpm < minRpm)
				currentRpm = minRpm;
		}
		// Speed (sample rate) output
		int sampleRate = SystemCoreClock / (SAMPLE_RATE + (long)(currentRpm * TOP_SPEED_MULTIPLIER));
		TIM6->ARR = sampleRate;
  	printf("st=%d, thr=%4d, map=%4d, rpm=%4d, arr=%4d, smr=%5d\r\n", state, throttle, mappedThrottle, currentRpm, sampleRate, SystemCoreClock / sampleRate);
//	}
}

void DMA2_Channel3_IRQHandler()
{
	DMA2->IFCR = DMA_IFCR_CTCIF3;
	DMA2_Channel3->CCR = 0;
	DMA2_Channel3->CNDTR = idleSampleCount;
	DMA2_Channel3->CMAR = (uint32_t)&idleSamples;
	DMA2_Channel3->CCR = DMA_CCR_PL_1 | DMA_CCR_PL_0 | DMA_CCR_MINC | DMA_CCR_DIR | DMA_CCR_CIRC | DMA_CCR_EN;
	state = eRunning;
}
#else
void engineSoundInit(void) {}
void engineSoundStart(void) {}
void engineSoundStop(void) {}
void engineSoundSimulation(int16_t throttle) {}
#endif
