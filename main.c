#include "main.h"

void main()
{
	init_PLL(); 
	initRS(); 
	adress = ADRES1; 
	initDMA(); 
	crc = getChecksum(); 
	initLed(); 
	initADC(); 
	initPWM(); 
	
	enable_interrupts(INTR_GLOBAL); 		
	onOffPWMCanal(0x01); 
		
	startAvtomatCalibr(); 
	

 
	
	while(TRUE)
	{
		// отключение силовой части в случае замыкания
		if(getStateOutError())
		{
			onOffPWMCanal(0x00);
			setOrError(&m3, ERR_PWR_KZ);
			setOrError(&m4, ERR_PWR_KZ);
			setOrError(&m5, ERR_PWR_KZ);
			setOrError(&m6, ERR_PWR_KZ);	 	
		}
	
		readDmaAdc(); 
		obmenRS(); 
		sendDataCalibr(); 
		rotate();
	
		

	}


}

void obmenRS()
{
	if(FLAG)
	{
		if(buffer[0] == adress)
		{			 	
			switch(buffer[1])
			{	
					case COM_READ_ERROR: 
					{
						int8 d3 = getError(&m3);
						int8 d4 = getError(&m4);
						int8 d5 = getError(&m5);
						int8 d6 = getError(&m6);
						ansComReadError(d3,d4,d5,d6); 
						runVD(LED_GREEN);
						indW = 0;
						break; 
	
					} 
					case COM_READ_SPEED:
					{
						ansComReadSpeed(); 
						runVD(LED_GREEN); 
						indW = 0; 
						break; 
					}
					case COM_SET_SPEED: 
					{
						int8 canal = (buffer[2]&0xFF);
						int1 b = 0; 

						switch(canal)
						{
							case SEL_SET_PWM3: {  if(indW>=7)
									   {
									   		int16 speedMin = make16(buffer[3], buffer[4]);
											int16 speedMax = make16(buffer[5], buffer[6]); 
									   		setMinSpeed(&m3, speedMin);
											setMaxSpeed(&m3, speedMax);
									   		ansComSetSpeedPwm(canal, speedMin, speedMax);
											b = 1;  
									   } break;}
							case SEL_SET_PWM4: {   if(indW>=7)
									   {
									   		int16 speedMin = make16(buffer[3], buffer[4]);
											int16 speedMax = make16(buffer[5], buffer[6]); 
									   		setMinSpeed(&m4, speedMin);
											setMaxSpeed(&m4, speedMax);
									   		ansComSetSpeedPwm(canal, speedMin, speedMax);
											b = 1; 
									   } break;}
							case SEL_SET_PWM5: {    if(indW>=7)
									   {
									   		int16 speedMin = make16(buffer[3], buffer[4]);
											int16 speedMax = make16(buffer[5], buffer[6]); 
									   		setMinSpeed(&m5, speedMin);
											setMaxSpeed(&m5, speedMax);
									   		ansComSetSpeedPwm(canal, speedMin, speedMax);
											b = 1;
									   } break;}
							case SEL_SET_PWM6: {  if(indW>=7)
									   {
									   		int16 speedMin = make16(buffer[3], buffer[4]);
											int16 speedMax = make16(buffer[5], buffer[6]); 
									   		setMinSpeed(&m6, speedMin);
											setMaxSpeed(&m6, speedMax);
									   		ansComSetSpeedPwm(canal, speedMin, speedMax);
											b = 1; 
									   } break;}
							case SEL_SET_PWM_RK: {  if(indW>=19)
										{
											int16 speedMin3 = make16(buffer[3], buffer[4]);
											int16 speedMax3 = make16(buffer[5], buffer[6]);
											int16 speedMin4 = make16(buffer[7], buffer[8]);
											int16 speedMax4 = make16(buffer[9], buffer[10]);
											int16 speedMin5 = make16(buffer[11], buffer[12]);
											int16 speedMax5 = make16(buffer[13], buffer[14]);
											int16 speedMin6 = make16(buffer[15], buffer[16]);
											int16 speedMax6 = make16(buffer[17], buffer[18]); 
									   		setMinSpeed(&m3, speedMin3);
											setMaxSpeed(&m3, speedMax3);
											setMinSpeed(&m4, speedMin4);
											setMaxSpeed(&m4, speedMax4);
											setMinSpeed(&m5, speedMin5);
											setMaxSpeed(&m5, speedMax5);
											setMinSpeed(&m6, speedMin6);
											setMaxSpeed(&m6, speedMax6);
									   		ansComSetSpeedAllPwm(canal, speedMin3, speedMax3,speedMin4, speedMax4,
														speedMin5, speedMax5,speedMin6, speedMax6 ); 
											b = 1;
										} break;}
		
							default: {  runVD(LED_RED); 
										ansErrorComCanal(canal); 
										   break;}
			
						}	
						if(b)
						{				 
							runVD(LED_GREEN);  
							b = 0; 
						
						}
						indW = 0;	
						break; 
	
					} 
					case COM_LIMIT_ADC:
					{
						ansComLimitAdc(minAdc1, minAdc2, minAdc3, minAdc4, maxAdc1,
										maxAdc2, maxAdc3, maxAdc4); 			
						runVD(LED_GREEN); 
						indW = 0; 
						break; 
					}
					case COM_RUN_CALIBR: 
					{
						startAvtomatCalibr(); 
						ansComRunCalibr();
						runVD(LED_GREEN); 
						indW = 0;  
						break;
					}
					case COM_ONOFF_PWM: 
					{
						int8 data = (buffer[2]&0xFF); 
						onOffPWMCanal(data&0x01); 
						ansComOnOffPwm(data); 
						runVD(LED_GREEN);
						indW = 0;  
						break; 
					}
					case COM_READ_ADC:
					{
						ansComReadCurAdc(valAdc1, valAdc2, valAdc3, valAdc4);
						runVD(LED_GREEN); 
						indW = 0; 
						break;
					}
					case COM_SET_PWM_RK: 
					{
						int8 canal = (buffer[2]&0xFF);
						int1 b = 0; 

						switch(canal)
						{
							case SEL_SET_PWM3: {  if(indW>=5)
									   {
									   		int16 dPwm = make16(buffer[3], buffer[4]); 
									   		setPwm3(dPwm);
									   		ansComSetPwm3(canal, dPwm);
											b = 1;  
									   } break;}
							case SEL_SET_PWM4: {  if(indW>=5)
									   {
									   		int16 dPwm = make16(buffer[3], buffer[4]); 
									   		setPwm4(dPwm);
									   		ansComSetPwm4(canal, dPwm);
											b = 1;  
									   } break;}
							case SEL_SET_PWM5: {  if(indW>=5)
									   {
									   		int16 dPwm = make16(buffer[3], buffer[4]); 
									   		setPwm5(dPwm);
									   		ansComSetPwm5(canal, dPwm);
											b = 1;  
									   } break;}
							case SEL_SET_PWM6: {  if(indW>=5)
									   {
									   		int16 dPwm = make16(buffer[3], buffer[4]); 
									   		setPwm6(dPwm);
									   		ansComSetPwm6(canal, dPwm);
											b = 1;  
									   } break;}
							case SEL_SET_RK: {  if(indW>=4)
									   {
									   		int8 dRk = (buffer[3]&0xFF);  
									   		setRk(dRk); 
									   		ansComSetRk(canal, dRk);
											b = 1;  
									   } break;}
							case SEL_SET_PWM_RK: {  if(indW>=12)
										{
											int16 dPwm3 = make16(buffer[3], buffer[4]); 
											int16 dPwm4 = make16(buffer[5], buffer[6]);
											int16 dPwm5 = make16(buffer[7], buffer[8]);
											int16 dPwm6 = make16(buffer[9], buffer[10]);
											int8 dRk = (buffer[11]&0xFF);   
											setPwm3456(dPwm3, dPwm4, dPwm5, dPwm6, dRk);
									 		ansComSetPwmRk(canal, dPwm3, dPwm4, dPwm5, dPwm6, dRk); 
											b = 1;
										} break;}
		
							default: {  runVD(LED_RED); 
										ansErrorComCanal(canal); 
										   break;}
			
						}	
						if(b)
						{				 
							runVD(LED_GREEN);  
							b = 0; 
						
						}
						indW = 0;	
						break; 
					} 

				//****************************************
				// CRC
				case COM_READ_CRC:
				{
						ansReadCrc(crc);
						runVD(LED_GREEN);
						indW = 0;
					
					break; 
				}
				case COM_INFO:
				{
						ansComInfo();
						runVD(LED_GREEN);
						indW = 0;
					
					break; 
				}
				case COM_READ_ID:
				{
						ansComId();
						runVD(LED_GREEN);
						indW = 0;
					
					break; 
				}
				case COM_RESET_MK:
				{
					int d = (buffer[2]&0xFF); 
					switch (d)
					{
						case 0xAA:
						{
							sendRS(buffer[0]); 
							sendRS(buffer[1]);
							sendRS(buffer[2]);
							runVD(LED_GREEN); 
							reset_cpu(); 
							indW=0;
							break; 
						}
						default: 
						{
							ansComRst(((~buffer[1])&0xFF), buffer[2]); 
							runVD(LED_RED);
							indW=0; 
							break; 
						

						} 
					}
					indW = 0;
					
					break; 
				}
				default:
				{
					ansErrorCom(buffer[1]&0xFF); 
					runVD(LED_RED);
					indW = 0;
				
					break;
				
				} 

			}
			
			buffer[0]=0;
			buffer[1]=0; 
			buffer[2]=0;
			indW = 0; 
		}
		else
		{
		
			indW = 0; 
	
		}
	
	
	
		
		
		flag = 0; 

		if(indW>SIZE_RS_BUFFER)
		{
			indW = 0;
			buffer[0]=0;
			buffer[1]=0; 
			buffer[2]=0;
			buffer[3]=0; 
			buffer[4]=0; 
			buffer[5]=0; 
			buffer[6]=0; 
			buffer[7]=0; 
			buffer[8]=0;
			buffer[9]=0;   
		}
	}

}