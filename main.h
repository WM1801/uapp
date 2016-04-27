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
//PWM
#define COM_SET_PWM_RK       0x31 //устанавливает значения всех стрелок, бленкеров, индексов
#define COM_SET_SPEED		 0x33 //максим и мин скорости	
	//parameters PWM
	#define SEL_SET_PWM_RK		 0x10 //значения всех стрелок, бленкеров, индексов
	#define SEL_SET_PWM5	     0x05 //только стрелка угла атаки 	
	#define SEL_SET_PWM3         0x03 //индекс угла атаки 		
	#define SEL_SET_PWM4         0x04 //стрелка перегрузки  
	#define SEL_SET_PWM6         0x06 //индекс перегрузки 
	#define SEL_SET_RK           0x07 //бленкер угла атаки & блекнкер перегрузки
#define COM_READ_SPEED       0x43  // чтение установленых макс и мин скорости
//ADC
#define COM_RUN_CALIBR       0x32 //запуск калибровки АЦП
#define COM_READ_ADC         0x40 //текущее значение АЦП
#define COM_LIMIT_ADC		 0x41 //измеренные минимум и максимум АЦП
#define COM_READ_ERROR		 0x42 //текущее состояние мотора ()
//PWM_POWER
#define COM_ONOFF_PWM		 0x35 // включение и отключение Шим

//
#define COM_READ_CRC	     0x47 //чтение контрольной суммы
#define COM_INFO			 0x48 //поддерживаемы команды 
#define COM_READ_ID		     0x46 //идентификатор
#define COM_RESET_MK		 0x55 //программный перезапуск МК	
	#define RESET_MK_WORD_2      0xAA //2 е -слово используемое в команде перезапуска МК


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
#include "ioPin.c"


void obmenRS(); 


