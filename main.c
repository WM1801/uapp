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
		readDmaAdc(); 
		obmenRS(); 
		sendDataCalibr(); 
	//	sendState();
		testPoAdc(canalPwm, dataCanal3); 

			
		
		

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
					case 0x14: 
					{
						enabRegul = buffer[2]&0x01; 
						canalPwm = (buffer[3]&0xFF); 
						dataCanal3 = make16(buffer[4], buffer[5]); 
						sendRS(adress); 
						sendRS(0x14);
						indW = 0;  
						break; 
					}
					case 0x13: 
					{
						setLimitAdcMotor(&m3, minAdc1, maxAdc1);
						//startAvtomatCalibr(); 
					/*	sendRS(adress); 
						sendRS(0x13);
						sendRS16(minADC1);
						sendRS16(minADC2);
						sendRS16(minADC3);
						sendRS16(minADC4);
						sendRS16(maxADC1);
						sendRS16(maxADC2);
						sendRS16(maxADC3);
						sendRS16(maxADC4);*/	
						indW = 0;  
						break;

					}
					case 0x12: 
					{
						onOffPWMCanal(buffer[2]&0x01); 
						sendRS(adress); 
						sendRS(0x12);
						indW = 0;  
						break; 
					}
					case 0x11:
					{
						sendRS(adress); 
						sendRS(0x11); 
						sendRS16(valAdc1); 
						sendRS16(valAdc2); 
						sendRS16(valAdc3); 
						sendRS16(valAdc4); 
						indW = 0; 
						break;
					}
					case COM_SET_ALL_UI: 
					{
						if(indW>=6)
						{
							//change   uStr	uInd	Pstr		Pind	UPblenk
							setAllPwm((buffer[2]&0xFF), (buffer[3]&0xFF), (buffer[4]&0xFF),(buffer[5]&0xFF), (buffer[6]&0xFF)); 
											//uStr	uInd	Pstr		Pind	UPblenk
							ansComSetAllUi((buffer[2]&0xFF), (buffer[3]&0xFF), (buffer[4]&0xFF),(buffer[5]&0xFF), (buffer[6]&0xFF)); 
							runVD(LED_GREEN);  
							indW = 0;
						}
						break; 
					} 
					case COM_SET_UGOL_STR:
					{
						if(indW>=3)// проверка на полный буффер
						{
							//change
							setUstr(buffer[2]&0xFF); 
							ansComSetUgolStr(buffer[2]&0xFF);
							runVD(LED_GREEN);
							indW = 0; 
						}
						break; 
					}
				
				
					case COM_SET_UGOL_IND:
					{
						if(indW>=3)// проверка на полный буффер
						{
							//change
							setUind(buffer[2]&0xFF); 
							ansComSetUgolInd(buffer[2]&0xFF);
							runVD(LED_GREEN);
							indW = 0; 
						}
						break;
					}

					case COM_SET_PRG_STR:
					{
						if(indW>=3)// проверка на полный буффер
						{
							//change
							setPstr(buffer[2]&0xFF); 
							ansComSetPrgStr(buffer[2]&0xFF);
							runVD(LED_GREEN);
							indW = 0; 
						}
						break;
					}

					case COM_SET_PRG_IND:
					{
						if(indW>=3)// проверка на полный буффер
						{
							//change
							setPind(buffer[2]&0xFF); 
							ansComSetPrgInd(buffer[2]&0xFF);
							runVD(LED_GREEN);
							indW = 0; 
						}
						break;
					}

					case COM_SET_UP_BLN:
					{
						if(indW>=3)// проверка на полный буффер
						{
							//change
							setUPbln(buffer[2]&0xFF); 
							ansComSetUPbln(buffer[2]&0xFF);
							runVD(LED_GREEN);
							indW = 0; 
						}
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