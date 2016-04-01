#include "motor.h"

void initMotor(Motor * m, int cPwm,  int16 tPwm, int16 vAdc1, int16 vAdc2)
{
	m->canalPwm = cPwm; 
	m->upValue = 0;  
	m->minSpeed = 0; 
	m->enabRotate = 1;
	m->Error = 0;  
}


void setLimitAdcMotor(Motor *m, int16 vAdc1, int16 vAdc2)
{
	if(vAdc1>vAdc2)
	{
		m->upValue = 0; 
		m->minValAdc = vAdc2; 
		m->maxValAdc = vAdc1; 
		m->Error |= 0x02; 
	}
	else
	{	
		if(vAdc1<vAdc2)
		{	
			m->upValue = 1; 
			m->minValAdc = vAdc1; 
			m->maxValAdc = vAdc2;
			m->Error |= 0x04;
		}
		else
		{
			m->Error |= 0x01; 
		}
	} 
	m->dAdc = ((float)(m->maxValAdc-m->minValAdc));  
}  

void setMinSpeed(Motor *m, int16 data)
{
	m->minSpeed = data; 
}

void setRotate(Motor *m, int16 currentData, int16 neWdata)
{	

if(m->enabRotate)
	{
		if((m->Error&0x02)|(m->Error&0x04))
		{
			int16 n = 0; 
			float error = 0; 
			if(currentData>newData)
			{//niz
				error = currentData - newData;			 
				float ps =((((float)(error*POL_POL_PERIOD))/m->dAdc));
				n = ((int16)ps);
				 
				if(m->upValue)
				{
					switch(m->canalPwm)
					{
						case 3: { set_compare_time(3, n,(n+POL_PERIOD)); break; }
						case 4: { set_compare_time(4, n,(n+POL_PERIOD)); break; }
						case 5: { set_compare_time(5, n,(n+POL_PERIOD)); break; }
						case 6: { set_compare_time(6, n,(n+POL_PERIOD)); break; }
						default: {}; 
					}
				}
				else
				{
					switch(m->canalPwm)
					{
						case 3: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
						case 4: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
						case 5: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
						case 6: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
						default: {}; 
					}
				}
					
			}
			else
			{
				if(currentData<newData)
				{//vverx
					error = newData -currentData;			
			        float ps =((((float)(error*POL_POL_PERIOD))/m->dAdc));
					n = ((int16)ps);
					if(m->upValue)
					{
						switch(m->canalPwm)
						{
							case 3: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
							case 4: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
							case 5: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
							case 6: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
							default: {}; 
						}
					}
					else
					{
						switch(m->canalPwm)
						{
							case 3: { set_compare_time(3, n,(n+POL_PERIOD)); break; }
							case 4: { set_compare_time(4, n,(n+POL_PERIOD)); break; }
							case 5: { set_compare_time(5, n,(n+POL_PERIOD)); break; }
							case 6: { set_compare_time(6, n,(n+POL_PERIOD)); break; }
							default: {}; 
						}
						
					}
								
				}
				else
				{
					switch(m->canalPwm)
					{
						case 3: { set_compare_time(3,0,POL_PERIOD); break; }
						case 4: { set_compare_time(4,0,POL_PERIOD); break; }
						case 5: { set_compare_time(5,0,POL_PERIOD); break; }
						case 6: { set_compare_time(6,0,POL_PERIOD); break; }
						default: {}; 
					}		
				}
			}

		}
			
	}
	
}

