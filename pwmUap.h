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

int16 newValueM3 = 0; 
int16 newValueM4 = 0; 
int16 newValueM5 = 0; 
int16 newValueM6 = 0; 
int8  newValueRk = 0; 
//ENAB POWER PWM
#define SD_PIN PIN_G15 // shutdown IR2014S
#define ON_PWR_PWM output_high(SD_PIN)
#define OFF_PWR_PWM output_low(SD_PIN)
//Time Pwm 
#define TIME_PWM 12500

#define POL_PERIOD (TIME_PWM>>1)
#define POL_POL_PERIOD (POL_PERIOD>>1)


// начальная настройка 
void initPWM();
//поворот 
void rotate(); 
// включение, отключение силовой части  
void onOffPWMCanal(int1 b); 
// вкл
void setEnableSD();
void setDisableSD();
// установка нового значения с АЦП до которого будет осуществлен поворот  
void setPwm3456(int16 pwm3, int16 pwm4, int16 pwm5, int16 pwm6, int8 blenk);
void setPwm3(int16 data); 
void setPwm4(int16 data); 
void setPwm5(int16 data); 
void setPwm6(int16 data); 
// управление бленкерами 
void setRk(int8 data);

// вулючение и отключение силов

/*void updatePwm3(); 
void updatePwm4(); 
void updatePwm5();
void updatePwm6(); */
void updateRk(); 

int8 canalPwm = 0; 
int16 dataCanal3 = 0; 
int1 enabRegul = 0; 




 




#endif