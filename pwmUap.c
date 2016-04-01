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

void testPoAdc(int8 canal, int16 data)
{
	switch(canal)
	{
		case 3: {setRotate(&m3, valAdc1, data); break;}
		case 4: {setRotate(&m4, valAdc2, data); break;}
		case 5: {setRotate(&m5, valAdc3, data); break;}
		case 6: {setRotate(&m6, valAdc4, data); break;}
		default: {}
	}

}


void dif(int16 data)
{
	if(oldValAdc1>valAdc1)
	{
		difAdc1 = oldValAdc1 - valAdc1;  
	}
	else
	{
		difAdc1 = valAdc1 - oldValAdc1; 
	}
	
}

void setPwm3(int16 data)
{
	if(enabRegul)
	{
		if(oldValAdc1>difAdc1)
		{
		
		}
		int16 n = 0; 
		float d = 0; 
		if(valAdc1>data)
		{//niz
			d = valAdc1 - data;			 

			float dAdc = (maxAdc1-minAdc1); 
			float ds =((((float)(d*POL_POL_PERIOD))/dAdc));
		
	  
			n = ((int16)ds); 
			set_compare_time(3, n,(n+POL_PERIOD));	
		}
		else
		{
			if(valAdc1<data)
			{//vverx
				d = data - valAdc1;			
		 		float dAdc = (maxAdc1-minAdc1); 
		        float ds =((((float)(d*POL_POL_PERIOD))/dAdc));
				n = ((int16)ds);
				set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n))));			
			}
			else
			{
				set_compare_time(3, 0,POL_PERIOD);		
			}
		}
			
	}
	
}
void setPwm4(int16 data)
{
	if(enabRegul)
	{
		int16 n = 0; 
		float d = 0; 
		if(valAdc2>data)
		{//niz
			d = valAdc2 - data;			 
			float dAdc = (maxAdc2-minAdc2); 
			float ds =((((float)(d*POL_POL_PERIOD))/dAdc));
			n = ((int16)ds); 
			set_compare_time(4,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n))));	
		}
		else
		{
			if(valAdc2<data)
			{//vverx
				d = data - valAdc2;			
		 		float dAdc = (maxAdc2-minAdc2); 
		        float ds =((((float)(d*POL_POL_PERIOD))/dAdc));
				n = ((int16)ds);
				set_compare_time(4, n,(n+POL_PERIOD));		
			}
			else
			{
				set_compare_time(4, 0,POL_PERIOD);		
			}
		}
			
	}
}
void setPwm5(int16 data)
{
	if(enabRegul)
	{
		int16 n = 0; 
		float d = 0; 
		if(valAdc3>data)
		{//niz
			d = valAdc3 - data;			 
			float dAdc = (maxAdc3-minAdc3); 
			float ds =( (((float)(d*POL_POL_PERIOD))/dAdc));
			n = ((int16)ds); 
			set_compare_time(5,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n))));	
				
		}
		else
		{
			if(valAdc3<data)
			{//vverx
				d = data - valAdc3;			
		 		float dAdc = (maxAdc3-minAdc3); 
		        float ds = ( (((float)(d*POL_POL_PERIOD))/dAdc));
				n = ((int16)ds);
				set_compare_time(5, n,(n+POL_PERIOD));		
			}
			else
			{
				set_compare_time(5, 0,POL_PERIOD);		
			}
		}
			
	}
}
void setPwm6(int16 data)
{
	if(enabRegul)
	{
		int16 n = 0; 
		float d = 0; 
		if(valAdc4>data)
		{//niz
			d = valAdc4 - data;			 
			float dAdc = (maxAdc4-minAdc4); 
			float ds =((((float)(d*POL_POL_PERIOD))/dAdc));
			n = ((int16)ds); 
			set_compare_time(6, n,(n+POL_PERIOD));	
		}
		else
		{
			if(valAdc4<data)
			{//vverx
				d = data - valAdc4;			
		 		float dAdc = (maxAdc4-minAdc4); 
		        float ds = ((((float)(d*POL_POL_PERIOD))/dAdc));
				n = ((int16)ds);
				set_compare_time(6,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n))));			
			}
			else
			{
				set_compare_time(6, 0,POL_PERIOD);		
			}
		}
			
	}
}

void onOffPWMCanal(int1 b)
{
	if(b==0)
	{
		setDisableSD();
	}
	else
	{
		setEnableSD(); 
	} 
	
}

void setEnableSD()
{
	output_high(SD_PIN); 
}

void setDisableSD()
{
	output_low(SD_PIN);
}

 
void setAllPwm(int8 uSdata, int8 uIdata, int8 pSdata, int8 pIdata, int8 blenk)
{
	 setUstr(uSdata);  
	 setUind(uIdata); 
     setPstr(pSdata); 
     setPind(pIdata); 
     setUPbln(blenk); 
}

void setUstr(int8 data)
{
	currentUstr = data; 
	updateUstr(); 
} 
void setUind(int8 data) 
{
	currentUind = data; 
	updateUind(); 
} 
void setPstr(int8 data)
{
	currentPstr = data; 
	updatePstr(); 
} 
void setPind(int8 data)
{
	currentPind = data; 
	updatePind(); 
} 
void setUPbln(int8 data)
{
	currentUPbln = data;
	updateBlenker();   
}

void updateUstr()
{

}
void updateUind()
{

} 
void updatePstr()
{

}
void updatePind()
{

}

void updateBlenker()
{
	if((currentUPbln&0x01))
	{
		BLENK2_ON; 
	}
	else
	{
		BLENK2_OFF; 
	}
	
	if((currentUPbln&0x10))
	{
		BLENK1_ON; 
	}
	else
	{
		BLENK1_OFF; 
	}
	
}

