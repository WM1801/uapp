#ifndef CALIBRADCPWM_H
#define CALIBRADCPWM_H

#include "pwmUap.h"
#include "AZP.h"

#define TIME_TEST_ADC_PWM 31250  //200ms
#define MAX_COUNT_ZIKL_WAIT 200

#define ERROR_WAIT (1<<4)
#define ACCURACY_ADC 0xFFF0

#define SK_VAL1_UP 250
#define SK_VAL2_UP (POL_PERIOD + SK_VAL1_UP)
#define SK_VAL1_DW (TIME_PWM-SK_VAL1_UP)
#define SK_VAL2_DW (POL_PERIOD-(TIME_PWM-SK_VAL1_DW))
//states 
#define S0  0x0000
#define S1  0x0001
#define S2  0x0002
#define S3  0x0004
#define S4  0x0008
#define S5  0x0010
#define S6  0x0020
#define S7  0x0040
#define S8  0x0080
#define S9  0x0100
#define S10 0x0200

// граничные значения с АЦП при нахождении указателей
// в максимальном и минимальном положени по шкале
//min 
int16 minAdc1 = 0; 
int16 minAdc2 = 0; 
int16 minAdc3 = 0; 
int16 minAdc4 = 0; 
//max
int16 maxAdc1 = 0; 
int16 maxAdc2 = 0; 
int16 maxAdc3 = 0; 
int16 maxAdc4 = 0; 

#define SIZE_TEMP_ADC 4
int16 tempValADC11[SIZE_TEMP_ADC] = {0,0,0,0}; 
int16 tempValADC12[SIZE_TEMP_ADC] = {0,0,0,0};
int16 tempValADC13[SIZE_TEMP_ADC] = {0,0,0,0};
int16 tempValADC14[SIZE_TEMP_ADC] = {0,0,0,0};

int16 readValADC11 = 0; 
int16 readValADC12 = 0;
int16 readValADC21 = 0;
int16 readValADC22 = 0;
int16 readValADC31 = 0;
int16 readValADC32 = 0;
int16 readValADC41 = 0;
int16 readValADC42 = 0;

int8 errorRotate = 0;

int16 currentStateAvt = 0; 
int16 oldStateAvt = 0; 
int16 newStateAvt = 0; 
int1 enabSendCalibrData = 0;  
int1 endCalibrMotor = 0; 

void setPositionEndCalibr();

void initAvtomat(); 
void startAvtomatCalibr(); 
void startTimer7(); 
void resetCountZikl(); 
void resetAvtomat(); 
void updateState(); 
void readData1Adc(); 
void readData2Adc(); 
void sravnData();
void setEnableSendData();  
void sendDataCalibr(); 
void stopTimer7();
void setRotatePwm(int1 b); 
int1 waitStop(); 
void sendState( ); 

int16 ziklReadCalibr = 0;
int16 indexDataRead = 0;    


int1 getFullMasCalibr(int16 a, int16 b, int16 c, int16 d); 


int1 debugRS = 0; 
void setDebugRS();

#endif