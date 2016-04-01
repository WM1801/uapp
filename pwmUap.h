#ifndef PWMUAP_H
#define PWMUAP_H

#include "CalibrAdcPwm.h"
#include "motor.h"

//PWM OUTPUT
#define CANAL1_PWM PIN_D0
#define CANAL2_PWM PIN_D1
#define CANAL3_PWM PIN_D2
#define CANAL4_PWM PIN_D3
#define CANAL5_PWM PIN_D4
#define CANAL6_PWM PIN_D5


#define PIN_BLENK1 PIN_F0
#define PIN_BLENK2 PIN_F1 
#define BLENK1_ON  output_low(PIN_BLENK1); 
#define BLENK1_OFF output_high(PIN_BLENK1); 
#define BLENK2_ON  output_low(PIN_BLENK2); 
#define BLENK2_OFF output_high(PIN_BLENK2); 

Motor m3; 
Motor m4; 
Motor m5; 
Motor m6; 
//ENAB POWER PWM
#define SD_PIN PIN_G15 // shutdown IR2014S
//Time Pwm 
#define TIME_PWM 12500

#define POL_PERIOD (TIME_PWM>>1)
#define POL_POL_PERIOD (POL_PERIOD>>1)
int8 currentUstr = 0; 
int8 currentUind = 0; 
int8 currentPstr = 0; 
int8 currentPind = 0; 
int8 currentUPbln = 0; 

// начальная настройка 
void initPWM(); 
void onOffPWMCanal(int1 b); 
void setAllPwm(int8 uSdata, int8 uIdata, int8 pSdata, int8 pIdata, int8 blenk);
void setUstr(int8 data); 
void setUind(int8 data); 
void setPstr(int8 data); 
void setPind(int8 data); 
void setUPbln(int8 data);


void setEnableSD();
void setDisableSD();
void updateUstr(); 
void updateUind(); 
void updatePstr();
void updatePind(); 
void updateBlenker(); 

int8 canalPwm = 0; 
int16 dataCanal3 = 0; 
int1 enabRegul = 0; 
void testPoAdc(int8 canal, int16 data); 
void setPwm3(int16 data);
void setPwm4(int16 data);
void setPwm5(int16 data);
void setPwm6(int16 data); 

void dif(int16 data); 

int16 oldValAdc1 = 0; 
int16 oldValAdc2 = 0; 
int16 oldValAdc3 = 0; 
int16 oldValAdc4 = 0;

int16 difAdc1 = 0; 
int16 difAdc2 = 0; 
int16 difAdc3 = 0; 
int16 difAdc4 = 0;
/*
int16 minAdc1 = 0; 
int16 minAdc2 = 0; 
int16 minAdc3 = 0; 
int16 minAdc4 = 0;
int16 maxAdc1 = 0; 
int16 maxAdc2 = 0; 
int16 maxAdc3 = 0; 
int16 maxAdc4 = 0;
 */
 




#endif