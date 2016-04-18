#include "pwmUap.h"

void initPWM()
{
	onOffPWMCanal(0); 
	setup_timer3(TMR_INTERNAL | TMR_DIV_BY_8, TIME_PWM);
	setup_compare( 1,COMPARE_CONT_PULSE | COMPARE_TIMER3);
	setup_compare( 2,COMPARE_CONT_PULSE | COMPARE_TIMER3);
	setup_compare( 3,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
	setup_compare( 4,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
	setup_compare( 5,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
	setup_compare( 6,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
	set_compare_time(1, 0, POL_PERIOD);
	set_compare_time(2, POL_PERIOD, 0);
	set_compare_time(3, 0,POL_PERIOD); //3125, 9375);
	set_compare_time(4, 0,POL_PERIOD);//3125, 9375);
	set_compare_time(5, 0,POL_PERIOD); //9375, 3125);
	set_compare_time(6, 0,POL_PERIOD);//3125, 9375);
	enabRegul = 0; 

	initMotor(&m3, 3, TIME_PWM, 0, 0); 
	initMotor(&m4, 4, TIME_PWM, 0, 0); 
	initMotor(&m5, 5, TIME_PWM, 0, 0); 
	initMotor(&m6, 6, TIME_PWM, 0, 0); 	
}



void rotate()
{
	if(endCalibrMotor)
	{
		//output_low(PIN_G0);
		for(int i = 3; i<7; i++)
		{
			switch(i)
			{
				case 3: {setRotate(&m3, valAdc1, newValueM3); break;}
				case 4: {setRotate(&m4, valAdc2, newValueM4); break;}
				case 5: {setRotate(&m5, valAdc3, newValueM5); break;}
				case 6: {setRotate(&m6, valAdc4, newValueM6); break;}
				default: {}
			}
		}
		//output_high(PIN_G0);	
	}
}


void onOffPWMCanal(int1 b)
{
	if(b==0)
	{
		OFF_PWR_PWM;
	}
	else
	{
		ON_PWR_PWM;
	} 
	
}

/*void setEnableSD()
{
	output_high(SD_PIN); 
}

void setDisableSD()
{
	output_low(SD_PIN);
}*/

 
void setPwm3456(int16 pwm3, int16 pwm4, int16 pwm5, int16 pwm6, int8 rk)
{
	 setPwm3(pwm3);  
	 setPwm4(pwm4); 
     setPwm5(pwm5); 
     setPwm6(pwm6); 
     setRk(rk); 
}

void setPwm3(int16 data)
{
	newValueM3 = data; 
} 
void setPwm4(int16 data) 
{
	newValueM4 = data; 
} 
void setPwm5(int16 data)
{
	newValueM5 = data; 
} 
void setPwm6(int16 data)
{
	newValueM6 = data;  
} 
void setRk(int8 data)
{
	newValueRk = data; 
}


void updateRk()
{
	if((newValueRk&0x01))
	{
		BLENK2_ON; 
	}
	else
	{
		BLENK2_OFF; 
	}
	
	if((newValueRk&0x10))
	{
		BLENK1_ON; 
	}
	else
	{
		BLENK1_OFF; 
	}
	
}

