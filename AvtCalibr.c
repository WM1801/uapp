#include "AvtCalibr.h"

void initAvtomat()
{
	memset(tempValADC, 0, (SIZE_TEMP_ADC<<1)); 
	currentStateAvt = 0; 
	oldStateAvt = 0; 
	newStateAvt = 0; 
	enabSendCalibrData = 0;

}

void resetCountZikl()
{
	ziklReadCalibr = 0; 
	indexDataRead = 0;
	enabSendCalibrData = 0;  
}

void stopTimer7()
{
	disable_interrupts(int_TIMER7); 
	set_timer7(0); 
}

void startTimer7()
{
	
	disable_interrupts(int_TIMER7); 
	setup_timer7(TMR_INTERNAL|TMR_DIV_BY_256, TIME_TEST_ADC_PWM); 
	set_timer7(0); 
	enable_interrupts(int_TIMER7); 	
}

void startAvtomatCalibr(Motor* m)
{
	currentMotor = &m; 
	stopTimer7(); 
	initAvtomat();
	startTimer7(); 		
}

void updateState()
{
	oldStateAvt = currentStateAvt; 
	currentStateAvt = newStateAvt; 	
}

void testPWM( int1 b) // motor
{
		switch(3)
		{
			case 3: {
						if(b){set_compare_time(3, SK_VAL1_UP, SK_VAL2_UP);}
						else{set_compare_time(3, SK_VAL1_DW, SK_VAL2_DW);}
						break;
					}
			case 4: {
						if(b){set_compare_time(4, SK_VAL1_UP, SK_VAL2_UP);}
						else{set_compare_time(4, SK_VAL1_DW, SK_VAL2_DW);}
						break;
					}
			case 5: {
						if(b){set_compare_time(5, SK_VAL1_UP, SK_VAL2_UP);}
						else{set_compare_time(5, SK_VAL1_DW, SK_VAL2_DW);}
						break;
					}
			case 6: {
						if(b){set_compare_time(6, SK_VAL1_UP, SK_VAL2_UP);}
						else{set_compare_time(6, SK_VAL1_DW, SK_VAL2_DW);}
						break;
					}
			default:{}	

		}
}

#int_timer7 
void timer7_isr(void)
{	
	ziklReadCalibr++;
	enabReadAdc = 1; 
	if(ziklREadCalibr>=MAX_COUNT_ZIKL_WAIT)
	{
		errorRotate = ERROR_WAIT;
		currentMotor->error |= 0x80; 
		newStateAvt = S10; 
	}
	switch(currentStateAvt)
	{
		case S0 :{ initAvtomat(); newStateAvt = S1;    break;}
		case S1 :{ resetCountZikl(); newStateAvt = S2;  break;}
		case S2 :{ setRotatePwm(1); newStateAvt = S3;  break;}
		case S3 :{ if(waitStop()){ newStateAvt = S4;  }else{ newStateAvt = S3;} break;}	
		case S4 :{ readData1Adc(); newStateAvt = S5; break;}
		case S5 :{ resetCountZikl(); newStateAvt = S6; break;}
		case S6 :{ setRotatePwm(0); newStateAvt = S7; break;}
		case S7 :{ if(waitStop()){ newStateAvt = S8;  }else{ newStateAvt = S7;} break;}
		case S8 :{ readData2Adc(); newStateAvt = S9; break;}	
		case S9 :{ sravnData(); newStateAvt = S10;  break;}
		case S10:{ stopTimer7(); setEnableSendData();  break;}
		default :{ stopTimer7(); setEnableSendData();  break;}
	}	
	setDebugRS();
	updateState(); 

}

void setDebugRS()
{
	debugRS = 1;
}

void sendState( ) // motor
{
	if(debugRS )
	{
		switch(currentStateAvt)
		{
			case S0 :{ sendRS(0x30); break;}
			case S1 :{ sendRS(0x31); break;}
			case S2 :{ sendRS(0x32); break;}
			case S3 :{ sendRS(0x33); break;}	
			case S4 :{ sendRS(0x34); break;}
			case S5 :{ sendRS(0x35); break;}
			case S6 :{ sendRS(0x36); break;}
			case S7 :{ sendRS(0x37); break;}
			case S8 :{ sendRS(0x38); break;}	
			case S9 :{ sendRS(0x39);  break;}
			case S10:{ sendRS(0x40);  break;}
			default :{ sendRS(0x40);  break;}
		}
		debugRS = 0; 
	}	

}

//****************
void sendDataCalibr() // motor
{
	if(enabSendCalibrData)
	{
		sendRS(adress); 
		sendRS(0x13);
	/*	sendRS16(minADC1);
		sendRS16(minADC2);
		sendRS16(minADC3);
		sendRS16(minADC4);
		sendRS16(maxADC1);
		sendRS16(maxADC2);
		sendRS16(maxADC3);
		sendRS16(maxADC4);
		sendRS(errorRotate); 
		enabSendCalibrData = 0; */
	}
}

//**************** 
void setEnableSendData()
{
	enabSendCalibrData = 1; 
}
//****************
void readData1Adc()
{
	switch(currentMotor->canalPwm)
	{
		case 3: {readValADC1  = valAdc1;  break; }
		case 4: {readValADC1  = valAdc2;  break; }
		case 5: {readValADC1  = valAdc3;  break; }
		case 6: {readValADC1  = valAdc4;  break; }
		default: {currentMotor->error |= 0x80;  }
	}
}

void readData2Adc()
{
	switch(currentMotor->canalPwm)
	{
		case 3: {readValADC2  = valAdc1;  break; }
		case 4: {readValADC2  = valAdc2;  break; }
		case 5: {readValADC2  = valAdc3;  break; }
		case 6: {readValADC2  = valAdc4;  break; }
		default: {currentMotor->error |= 0x80;  }
	}
}

//****************
int1 waitStop()
{
	int1 result = 0;
	if(enabReadAdc)
	{
		switch(currentMotor->canalPwm)
		{
			case 3: {tempValADC[indexDataRead] = valAdc1;  break; }
			case 4: {tempValADC[indexDataRead] = valAdc2;  break; }
			case 5: {tempValADC[indexDataRead] = valAdc3;  break; }
			case 6: {tempValADC[indexDataRead] = valAdc4;  break; }
			default: {currentMotor->error |= 0x80;  }
		}
		indexDataRead++; 
		if(indexDataRead>=SIZE_TEMP_ADC)
		{
			indexDataRead = 0; 
		}
		result = getFullMasCalibr(tempValADC[0], tempValADC[1], tempValADC[2], tempValADC[3]); 	
		enabreadAdc = 0; 
	}	
	return result; 
}
//******************************
void sravnData()
{
	setLimitAdcMotor(&currentMotor, readValADC1 , readValADC2); 
}


void setRotatePwm(int1 b)
{
	if(b) { testPWM( 1); }
	else { testPWM( 0); }
}


int1 getFullMasCalibr(int16 a, int16 b, int16 c, int16 d) 
{

	if((((a&ACCURACY_ADC)==(b&ACCURACY_ADC))&((c&ACCURACY_ADC)==(d&ACCURACY_ADC)))&((a&ACCURACY_ADC)==(c&ACCURACY_ADC)))
	{
		return 1; 
	}
	else
	{
		return 0; 
	}

}

