#include "motor.h"

void initMotor(Motor * m, int cPwm,  int16 tPwm, int16 vAdc1, int16 vAdc2)
{
	m->canalPwm = cPwm; 
	m->upValue = 0;  
	m->minSpeed = 100;
	m->maxSpeed = POL_POL_PERIOD;  
	m->enabRotate = 1;
	m->Error = 0; 
	m->oldValAdc = 0; 
	m->newValue = 0; 
	m->kP = 0; 
	m->kD = 0; 
	m->minAccel = 0; 
	m->maxAccel = POL_POL_PERIOD; 
	m->oldSpeed = 0;
	m->integrError = 0;
	m->maxIEr = (m->minSpeed<<3); 
	m->minIEr = ((m->minSpeed<<3)*(-1));  

}

void updateError(Motor *m)
{
	int16 dAdc  = (m->maxValAdc - m->minValAdc);
	if(dAdc < MIN_DADC)
	{
		setOrError(m, ERR_DADC); 
		m->enabRotate = 0; 
	}
	

}


int8 getError(Motor *m)
{
	int8 dataError = m->Error; 
	return dataError; 
}


void setOrError(Motor *m, int8 data)
{
	m->Error |= (data&0xFF);  
}

void setAndError(Motor *m, int8 data)
{
	m->Error &= (~(data&0xFF));  
}

/*void setError(Motor *m, int8 data)
{
	m->Error = data;
}*/

void setLimitAdcMotor(Motor *m, int16 vAdc1, int16 vAdc2)
{
	if(vAdc1>vAdc2)
	{
		m->upValue = 0; 
		m->minValAdc = vAdc2; 
		m->maxValAdc = vAdc1; 
		setOrError(m, ERR_VADC1_B);
	}
	else
	{	
		if(vAdc1<vAdc2)
		{	
			m->upValue = 1; 
			m->minValAdc = vAdc1; 
			m->maxValAdc = vAdc2;
			setOrError(m, ERR_VADC2_B);
		
		}
		else
		{
			setOrError(m, ERR_VADC_RAVN);
		}
	} 
	m->dAdc = ((float)(m->maxValAdc - m->minValAdc));
	setK(m); 
//	m->newValue = m->maxValAdc;   
}  

void setMinSpeed(Motor *m, int16 data)
{
	m->minSpeed = data; 
	m->maxIEr = (m->minSpeed<<3); 
	m->minIEr = ((m->minSpeed<<3)*(-1));
	m->kI = m->minSpeed; 
}

void setK(Motor *m)
{
	if(m->dAdc>0)
	{
		m->kP = (m->maxSpeed/m->dAdc); 
	}
	else
	{
		m->Error = 0; 
		m->kP = 1; 	
	}
//	m->kD = (m->kP*0.3f);
	//m->kI = 0.01;//m->minSpeed;
	m->kI = m->minSpeed; 
}

void setMaxSpeed(Motor *m,int16 data)
{
	if(data>POL_POL_PERIOD)
	{
		m->maxSpeed = POL_POL_PERIOD;		
	}
	else
	{
		m->maxSpeed = data;
	} 

	setK(m); 
}

int16 difSost(Motor *m, float data)
{	
	int16 result = 0;
	int16 d = (m->minSpeed>>1);   
	if(data>d)//(MIN_ERROR))
	{
		result = d; //data*m->kD; //m->minSpeed>>1; 
	}
	return result; 
}
int16  intSost(Motor *m,int1 dir,  float data)
{
	int16 result = 0;
	
	if(dir)
	{
		m->integrError +=((int16)data); 
	}
	else
	{
		m->integrError -= ((int16)data);
	}	

	if(m->integrError> m->maxIEr )
	{
		m->integrError = m->maxIEr; 
	}
	
	if(m->integrError< m->minIEr)
	{
		m->integrError = m->minIEr;
	}
	
	if(m->integrError<0)
	{
		float d =  (((float)m->integrError)*(-0.1f)); 	
		result = ((int16) d);
	}
	else
	{
		float d = (((float)m->integrError)*(0.1f)); 
		result = ((int16) d);
	}
	
	//if(data>MIN_ERROR)
	{
		 //result = ((int16)(data*m->kI));
		 //result = (((int16)m->integrError)&0xFFFF);   
		 
	}

	return result; 
}

int16 proSost(Motor *m, int16 data, float eData)
{
	
	//float ps =((((float)(data*POL_POL_PERIOD))/m->dAdc));
	float ps =((float)(eData*m->kP));
	int16 newSpeed = ((int16) ps); 

	// введение ограничений на величину изменения АЦП между измерениями   
	// текущая скорость 
/*	int16 Vtek = 0;
	// ускорение 
	int16 Atek = 0; 
	
	if(data>m->oldValAdc)
	{
		Vtek = (data - m->oldValAdc);
	}
	else
	{
		Vtek = (m->oldValAdc - data); 
	}
// speed ограничивается в kP
	if(Vtek>m->oldSpeed)
	{
		Atek = (Vtek - m->oldSpeed); 		
	}
	else
	{
		Atek = (m->oldSpeed - Vtek); 
	}
	m->oldSpeed = Vtek; 
	int16 kor = 0; 
	
	if(Atek>m->maxAccel)
	{
		kor = Atek - m->maxAccel; 
	}
	float nS; */
/*	if(newSpeed>kor)
	{
		nS =(((float) newSpeed)*0.9f);
		newSpeed = ((int16) ns);  
 	}  */ 
	return newSpeed;
	
}

void setNewValueMotor(Motor *m, int16 data)
{
	m->newValue = (data&0xFFFF); 

} 

void setRotate(Motor *m, int16 currentDataS, int16 newData)
{	
 m->newValue = (newData&0xFFFE);
int16 currentData =  (currentDataS&0xFFFE);
// проверка на завершение калибровки ацп
if(m->enabRotate)
	{
	
		if((m->Error&0x02)|(m->Error&0x04)) // если ацп работает и значения отличаются
		{
			int16 n = 0; 
			float error = 0; 
			if(currentData>m->newValue)// направление движения
			{//niz
				error = currentData - m->newValue; // рассогласование
				n = ((proSost(m,currentData, error)+ intSost(m,1, error))- difSost(m, currentData)); // значение ШИМ
				if(m->upValue) // двигатели крутятся в разные стороны потому понятие верх и низ для каждого индивидуально
				{				// и верх совпал с макс ацп
					switch(m->canalPwm&0xFF) // для индексов 
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
					if(n>TIME_PWM)
					{
						n = n-TIME_PWM; 
					}
					switch(m->canalPwm&0xFF) // для стрелок
					{
						case 3: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
						case 4: { set_compare_time(4,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
						case 5: { set_compare_time(5,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
						case 6: { set_compare_time(6,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
						default: {}; 
					}
				}
				m->oldValAdc = currentData;  // прошлое значения для которого производился расчет Шим
					
			}
			else
			{
				if(currentData<m->newValue)// направление движения
				{//vverx
					error = m->newValue -currentData;// рассогласование			
			       	n = ((proSost(m,currentData, error)+ intSost(m,0, error))- difSost(m, error)); // значение ШИМ
					if(m->upValue)// двигатели крутятся в разные стороны потому понятие верх и низ для каждого индивидуально
					{
						if(n>TIME_PWM)
						{
							n = n-TIME_PWM; 
						}
						switch(m->canalPwm&0xFF) // для индексов 
						{
							case 3: { set_compare_time(3,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
							case 4: { set_compare_time(4,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
							case 5: { set_compare_time(5,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
							case 6: { set_compare_time(6,(TIME_PWM-n),(POL_PERIOD-(TIME_PWM-(TIME_PWM-n)))); break; }
							default: {}; 
						}
					}
					else
					{
		
						switch(m->canalPwm&0xFF)// для стрелок
						{
							case 3: { set_compare_time(3, n,(n+POL_PERIOD)); break; }
							case 4: { set_compare_time(4, n,(n+POL_PERIOD)); break; }
							case 5: { set_compare_time(5, n,(n+POL_PERIOD)); break; }
							case 6: { set_compare_time(6, n,(n+POL_PERIOD)); break; }
							default: {}; 
						}
						
					}
					m->oldValAdc = currentData;  // прошлое значения для которого производился расчет Шим
								
				}
				else // двигатель стоит в заданной позиции, движение не требуется
				{
					switch(m->canalPwm&0xFF)
					{
						case 3: { set_compare_time(3,0,POL_PERIOD); break; }
						case 4: { set_compare_time(4,0,POL_PERIOD); break; }
						case 5: { set_compare_time(5,0,POL_PERIOD); break; }
						case 6: { set_compare_time(6,0,POL_PERIOD); break; }
						default: {}; 
					}
					m->oldValAdc = currentData;  // прошлое значения для которого производился расчет Шим		
				}
			}

		}
			
	}
	
}

void setMaxAccel(Motor *m, int16 data)
{
	m->maxAccel = data; 
}

int16 getMinSpeed(Motor *m)
{
    return m->minSpeed;  
} 
int16 getMaxSpeed(Motor *m)
{
    return m->maxSpeed; 
} 
int16 getMinAccel(Motor *m)
{
    return m->minAccel; 
} 
int16 getMaxAccel(Motor *m)
{
    return m->maxAccel; 
} 



void setIntError(Motor *m,signed int minE, signed int maxE)
{
	m->minIEr = minE; 
	m->maxIEr = maxE; 
}




