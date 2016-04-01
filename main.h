#include "24HJ64GP206.h"
#include "uart.h"

#ZERO_RAM
#DEVICE ADC=12

#FUSES NOWDT     	  	   		 //No Watch Dog Timer 
#FUSES HS
#FUSES PR_PLL                 //High speed Osc (> 4mhz) 
#FUSES PUT64                     //Power Up Timer 
#FUSES NOPROTECT                 //Code not protected from reads 
#FUSES NODEBUG                   //No Debug mode for ICD 
#FUSES NOWRT                     //Program memory not write protected

//*- CRC -*//
#rom getenv("PROGRAM_MEMORY")-2 = CHECKSUM

#define FREQUENCY 80000000  //!!!!PR_PLL
#use delay(clock=FREQUENCY, oscilator=FREQUENCY)

#use rs232(UART1, baud=115200, BITS =8,PARITY=N, STOP=1, ENABLE=PIN_F6, ERRORS, STREAM = RS1)

#use standard_io(All)


int8 adress = 0; 


//ID
#define ID1 0x17
#define ID2 0x03
#define ID3 0x20
#define ID4 0x16

//adress
#define ADRES1    0x85
#define ADRES2    0x85

//commands 
#define COM_SET_ALL_UI       0x40 //устанавливает значени€ всех стрелок, бленкеров, индексов
#define COM_SET_UGOL_STR	 0x31 //только стрелка угла атаки 	
#define COM_SET_UGOL_IND     0x3A //индекс угла атаки 		
#define COM_SET_PRG_STR      0x32 //стрелка перегрузки  
#define COM_SET_PRG_IND      0x41 //индекс перегрузки 
#define COM_SET_UP_BLN       0x42 //бленкер угла атаки & блекнкер перегрузки

#define COM_READ_CRC	     0x47 //чтение контрольной суммы
#define COM_INFO			 0x48 //поддерживаемы команды 
#define COM_READ_ID		     0x46 //идентивикатор
#define COM_RESET_MK		 0x55 //программный перезапуск ћ 	
#define RESET_MK_WORD_2      0xAA //2 е -слово используемое в команде перезапуска ћ 


//add modul 

#include "Led.c"      // timer5
#include "PLL.c"
#include "AZP.c"      // dma1, adc
#include "pwmUap.c"   //pwm, timer3 //
#include "RS485.c"    //timer4, uart1
#include "DMA_RS.c"   // DMA0
#include "CRC.c"
#include "calibrAdcPwm.c" // timer7
#include "motor.c"


void obmenRS(); 


