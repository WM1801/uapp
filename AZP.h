#ifndef AZP_H
#define AZP_H

#include "ADC.h"

//ADC INPUT
#define AV1 PIN_B2  //AN2
#define AV2 PIN_B3  //AN3
#define AV3 PIN_B13 //AN13
#define AV4 PIN_B14 //AN14

#define SIZE_DMA_ADC_BUF 4
#BANK_DMA 
static volatile int16 dmaAdcBuf[SIZE_DMA_ADC_BUF];

int1 dmaAdcFlag = 0;  

int16 valAdc1 = 0; 
int16 valAdc2 = 0; 
int16 valAdc3 = 0; 
int16 valAdc4 = 0; 


void clearAdcDmaBuf();
void initAdcDma();  
void initADC(); 
void readDmaAdc();



 







#endif