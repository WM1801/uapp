#include "calibrAdcPwm.h"


void initAvtomat()
{
	minAdc1 = 0x0000;
	minAdc2 = 0x0000;
	minAdc3 = 0x0000;
	minAdc4 = 0x0000;
	maxAdc1 = 0x0000;
	maxAdc2 = 0x0000;
	maxAdc3 = 0x0000;
	maxAdc4 = 0x0000;
	
	memset(tempValADC11, 0, (SIZE_TEMP_ADC<<1)); 
	memset(tempValADC12, 0, (SIZE_TEMP_ADC<<1)); 
	memset(tempValADC13, 0, (SIZE_TEMP_ADC<<1)); 
	memset(tempValADC14, 0, (SIZE_TEMP_ADC<<1)); 
/*	for(int i= 0; i<SIZE_TEMP_ADC; i++)
	{
		tempValADC11[i] = 0; 	
		tempValADC12[i] = 0;
		tempValADC13[i] = 0;
		tempValADC14[i] = 0;
	}*/
	
	currentStateAvt = 0; 
	oldStateAvt = 0; 
	newStateAvt = 0; 
	enabSendCalibrData = 0; 
	endCalibrMotor = 0; 
//	resetCountZikl(); 
}


void setPositionEndCalibr() // smotri stopTimer7(), primenenie dannoi f() vyzyvaet 
{				//Interrupts disabled during call to prevent re-entrancy:  (stopTimer7)
	newValueM3  = (maxAdc1&0xFFC0);
	newValueM4  = (maxAdc2&0xFFC0);
	newValueM5  = (maxAdc3&0xFFC0);
	newValueM6  = (maxAdc4&0xFFC0);

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
	endCalibrMotor = 1; 
	//setPositionEndCalibr(); -  Interrupts disabled during call to prevent re-entrancy:  (stopTimer7)
	newValueM3  = (maxAdc1&0xFFC0);
	newValueM4  = (maxAdc2&0xFFC0);
	newValueM5  = (maxAdc3&0xFFC0);
	newValueM6  = (maxAdc4&0xFFC0);
}

void startTimer7()
{
	
	disable_interrupts(int_TIMER7); 
	setup_timer7(TMR_INTERNAL|TMR_DIV_BY_256, TIME_TEST_ADC_PWM); 
	set_timer7(0); 
	enable_interrupts(int_TIMER7); 	
}

void startAvtomatCalibr()
{
	stopTimer7(); 
	setAndError(&m3, END_CALIBR|ERROR_CLBR|ERR_DADC|ERR_VADC2_B|ERR_VADC1_B|ERR_VADC_RAVN);
	setAndError(&m4, END_CALIBR|ERROR_CLBR|ERR_DADC|ERR_VADC2_B|ERR_VADC1_B|ERR_VADC_RAVN);
	setAndError(&m5, END_CALIBR|ERROR_CLBR|ERR_DADC|ERR_VADC2_B|ERR_VADC1_B|ERR_VADC_RAVN);
	setAndError(&m6, END_CALIBR|ERROR_CLBR|ERR_DADC|ERR_VADC2_B|ERR_VADC1_B|ERR_VADC_RAVN);
	initAvtomat();
	startTimer7(); 
	endCalibrMotor = 0; 
	errorRotate = 0; 

		
}

void updateState()
{
	oldStateAvt = currentStateAvt; 
	currentStateAvt = newStateAvt; 	
}
	


void testPWM(int8 n, int1 b)
{
		switch(n)
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
	if(ziklREadCalibr>=MAX_COUNT_ZIKL_WAIT)
	{
		errorRotate = ERROR_WAIT;
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

void sendState( )
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
void sendDataCalibr()
{
	if(enabSendCalibrData)
	{
	setLimitAdcMotor(&m3, minAdc1, maxAdc1);
	setLimitAdcMotor(&m4, maxAdc2, minAdc2); // перевернута шкала АЦП
	setLimitAdcMotor(&m5, maxAdc3, minAdc3); // перевернута шкала АЦП
	setLimitAdcMotor(&m6, minAdc4, maxAdc4);
	setOrError(&m3, END_CALIBR);
	setOrError(&m4, END_CALIBR);
	setOrError(&m5, END_CALIBR);
	setOrError(&m6, END_CALIBR);
	updateError(&m3);
	updateError(&m4);
	updateError(&m5);
	updateError(&m6);
	if(errorRotate&ERROR_WAIT)
	{
		setOrError(&m3, ERROR_CLBR);
		setOrError(&m4, ERROR_CLBR);
		setOrError(&m5, ERROR_CLBR);
		setOrError(&m6, ERROR_CLBR);

	}
	
	/*	sendRS(adress); 
		sendRS(COM_RUN_CALIBR);
		sendRS16(minADC1);
		sendRS16(minADC2);
		sendRS16(minADC3);
		sendRS16(minADC4);
		sendRS16(maxADC1);
		sendRS16(maxADC2);
		sendRS16(maxADC3);
		sendRS16(maxADC4);
		sendRS(errorRotate); */
		enabSendCalibrData = 0; 
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
	readValADC11 = valAdc1;
	readValADC21 = valAdc2;
	readValADC31 = valAdc3;
	readValADC41 = valAdc4; 
}

void readData2Adc()
{
	readValADC12 = valAdc1;
	readValADC22 = valAdc2;
	readValADC32 = valAdc3;
	readValADC42 = valAdc4; 
}

//****************
int1 waitStop()
{
	int1 boll = 0; 
	tempValADC11[indexDataRead] = valAdc1;
	tempValADC12[indexDataRead] = valAdc2;
	tempValADC13[indexDataRead] = valAdc3;
	tempValADC14[indexDataRead] = valAdc4;
	indexDataRead++; 
	if(indexDataRead>=SIZE_TEMP_ADC)
	{
		indexDataRead = 0; 
	}
	int1 a = getFullMasCalibr(tempValADC11[0], tempValADC11[1], tempValADC11[2], tempValADC11[3]); 
	int1 b = getFullMasCalibr(tempValADC12[0], tempValADC12[1], tempValADC12[2], tempValADC12[3]);
	int1 c = getFullMasCalibr(tempValADC13[0], tempValADC13[1], tempValADC13[2], tempValADC13[3]);
	int1 d = getFullMasCalibr(tempValADC14[0], tempValADC14[1], tempValADC14[2], tempValADC14[3]); 
	if(((a&b)&(c&d)))
	{
		boll = 1; 
	}		
	return boll; 
}
//******************************
void sravnData()
{
	if(readValADC11>=readValADC12) 
	{ 
		maxAdc1 = readValADC11; 
		minAdc1 = readValADC12;
	}
	else
	{
		maxAdc1 = readValADC12; 
		minAdc1 = readValADC11;
	}

	if(readValADC21>=readValADC22) 
	{ 
		maxAdc2 = readValADC21; 
		minAdc2 = readValADC22;
	}
	else
	{
		maxAdc2 = readValADC22; 
		minAdc2 = readValADC21;
	}

	if(readValADC31>=readValADC32) 
	{ 
		maxAdc3 = readValADC31; 
		minAdc3 = readValADC32;
	}
	else
	{
		maxAdc3 = readValADC32; 
		minAdc3 = readValADC31;
	}

	if(readValADC41>=readValADC42) 
	{ 
		maxAdc4 = readValADC41; 
		minAdc4 = readValADC42;
	}
	else
	{
		maxAdc4 = readValADC42; 
		minAdc4 = readValADC41;
	}



}


void setRotatePwm(int1 b)
{

		if(b)
		{
			testPWM(3, 1); 
			testPWM(4, 1);
			testPWM(5, 1);
			testPWM(6, 1);
		}
		else
		{
			testPWM(3, 0); 
			testPWM(4, 0);
			testPWM(5, 0);
			testPWM(6, 0);
		}

}




void readCalibrTwo()
{
	if((valAdc1&0xFFF0)<(minAdc1&0xFFF0))
	{
		maxAdc1 = minAdc1; 
		minAdc1 = valAdc1; 
	}
	else
	{
		maxAdc1 = valAdc1; 
	}

	if((valAdc2&0xFFF0)<(minAdc2&0xFFF0))
	{
		maxAdc2 = minAdc2; 
		minAdc2 = valAdc2; 
	}
	else
	{
		maxAdc2 = valAdc2; 
	}

	if((valAdc3&0xFFF0)<(minAdc3&0xFFF0))
	{
		maxAdc3 = minAdc3; 
		minAdc3 = valAdc3; 
	}
	else
	{
		maxAdc3 = valAdc3; 
	}

	if((valAdc4&0xFFF0)<(minAdc4&0xFFF0))
	{
		maxAdc4 = minAdc4; 
		minAdc4 = valAdc4; 
	}
	else
	{
		maxAdc4 = valAdc4; 
	}
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

