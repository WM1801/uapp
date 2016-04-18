#include "AZP.h"

void clearAdcDmaBuf() 
{
	memset(dmaAdcBuf, 0x00, sizeof(dmaAdcBuf));  
}

void initAdcDma()
{

	clearAdcDmaBuf(); 
	setup_dma(2, DMA_IN_ADC1, DMA_WORD);
	dma_start(2,DMA_CONTINOUS, &dmaAdcBuf[0]); 
	enable_interrupts(INT_DMA2);	
}

#INT_DMA2
void DMA2Interrupts()
{
	//dmaAdcFlag = 1; 
	readDmaAdc();
	//runVD(LED_RED);	
}

void readDmaAdc()
{
	//if(dmaAdcFlag)
	//{
		valAdc1 = (dmaAdcBuf[0]&0xFFFF);
		valAdc2 = (dmaAdcBuf[1]&0xFFFF);
		valAdc3 = (dmaAdcBuf[2]&0xFFFF);
		valAdc4 = (dmaAdcBuf[3]&0xFFFF); 
	//	dmaAdcFlag = 1;
	/*	tempDma = !tempDma; 
		if(tempDma)
		{	output_high(PIN_G1); }
		else {output_low(PIN_G1); }*/
			 
	 
	//}
}

void initADC()
{
	//1)set mode 12 bit
	MCU_ADON = 0;
	MCU_AD12B = 1; 
	//2)SET VOLTAGE REFERENSE 	 
	MCU_VCFG0 = 0; 
	MCU_VCFG1 = 0; 
	MCU_VCFG2 = 0; 
	//3)SELECT ANALOG CONVERSION CLOCK
	MCU_AD1CON3 = 0x0606; //0000_0100_0000_0100
	 					  // AutoSample 4TAD
						  // TAD = 5*Tcy	
						  // Tcy = 1/Fcy 
						  // Fcy = Fosc/2
	//4)select port pins
	MCU_PCFG16 = 0x01;
	MCU_PCFG17 = 0x01; 
	MCU_AD1PCFGL = 0x9FF3;
	//5)determine inputs to channels
	MCU_AD1CHS0 = 0x0006; 
	//6)DETERMINE how many Sample/Hold channels
	MCU_CHPS0 = 0; 
	MCU_CHPS1 = 0; 
	//7)Determine how sampling will occur
	
	MCU_SIMSAM = 0;
	MCU_CSS16 = 0; 
	MCU_CSS17 = 0; 
	MCU_AD1CSSL = 0x600C; 
	//8)Auto sampling 
	MCU_ASAM = 1;
	//Select conversion trigger and sampling time
	MCU_SSRC0 = 1; // internal counter ends sampling and start conversion (auto-convert)
	MCU_SSRC1 = 1;
	MCU_SSRC2 = 1; 
	//Select how conversion results
	MCU_FORM0 = 0;
	MCU_FORM1 = 0;
	//Select interrupt rate or DMA buffer pointer increment rate
	MCU_SMPI0 = 1; 
	MCU_SMPI1 = 1;
	MCU_SMPI2 = 0;
	MCU_SMPI3 = 0;
	//Select the number of samples 
	//in DMA buffer for each ADC module input
	MCU_AD1CON4 = 0; // 1 WORD  
	// Select the data format

	//Configure DMA channel (if needed)
	initAdcDma();	

	//Configure ADC interrupt (if required)
	
	MCU_ADDMABM = 0; 
	MCU_CSCNA = 1;
	MCU_BUFM = 0;
	//Turn on ADC module 
	 MCU_ADON = 1; 
	 	
}


