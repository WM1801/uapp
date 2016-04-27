#define SIZE_DMA_BUF 24
#define PIN_RS_SEND PIN_F6
int1 dmaBusy = 0; 
// ответы по RS
void ansComSetPwmRk(int8 canal, int16 p3, int16 p4, int16 p5, int16 p6, int8 rk); 
void ansComSetPwm3(int8 canal, int16 p3 );  
void ansComSetPwm4(int8 canal, int16 p4);  
void ansComSetPwm5(int8 canal, int16 p5);  
void ansComSetPwm6(int8 canal, int16 p6);  
void ansComSetRk(int8 canal, int8 rk); 
void ansComReadSpeed(); 
void ansComRunCalibr(); 

void ansComLimitAdc(int16 minAdc1,int16 minAdc2,int16 minAdc3,int16 minAdc4, int16 maxAdc1,int16 maxAdc2, int16 maxAdc3,int16 maxAdc4);
void ansComReadCurAdc(int16 a1, int16 a2, int16 a3, int16 a4);
void ansComOnOffPwm(int8 data); 
void ansComSetSpeedPwm(int16 canal, int16 speedMin, int16 speedMax);
void ansComSetSpeedAllPwm(int16 can, int16 sMn3, int16 sMx3, int16 sMn4, int16 sMx4, int16 sMn5, int16 sMx5, int16 sMn6, int16 sMx6 ); 
void ansComReadError(int8 d1, int8 d2, int8 d3, int8 d4);

void ansReadCrc(int16 crc); 
void ansComInfo(); 
void ansComId(); 
void ansComRst(int8 com, int8 data); 
void ansErrorCom(int8 com); 



#BANK_DMA
static volatile byte dmaBuffer[SIZE_DMA_BUF]; 

void clearDmaBuf() 
{
	memset(dmaBuffer, 0x00, sizeof(dmaBuffer)); 
	dmaBusy = 0; 
	dmaBuffer[0] = adress;
}

void initDma()
{
	clearDmaBuf(); 
	enable_interrupts(INT_DMA0);
	setup_dma(0, DMA_OUT_UART1, DMA_BYTE);
	output_low(PIN_RS_SEND);
}

void sendInRsDma(int len)
{
	dmaBusy = 1; 
	output_high(PIN_RS_SEND);
	dma_start(0, DMA_ONE_SHOT|DMA_FORCE_NOW, dmaBuffer, len ); 
}

#INT_DMA0
void DMAInterrupts()
{
	dmaBusy = 0; 
	output_low(PIN_RS_SEND);
}


#INT_DMAERR
void DmaErrorInterrupt()
{
   
}

void ansComLimitAdc(int16 a1,int16 a2,int16 a3,int16 a4, int16 b1,int16 b2, b3,int16 b4)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_LIMIT_ADC; 
	dmaBuffer[2]=(a1>>8); 
	dmaBuffer[3]=(a1&0xFF);
	dmaBuffer[4]=(a2>>8);
	dmaBuffer[5]=(a2&0xFF);
	dmaBuffer[6]=(a3>>8);
	dmaBuffer[7]=(a3&0xFF); 
	dmaBuffer[8]=(a4>>8);
	dmaBuffer[9]=(a4&0xFF); 
	dmaBuffer[10]=(b1>>8); 
	dmaBuffer[11]=(b1&0xFF);
	dmaBuffer[12]=(b2>>8);
	dmaBuffer[13]=(b2&0xFF);
	dmaBuffer[14]=(b3>>8);
	dmaBuffer[15]=(b3&0xFF); 
	dmaBuffer[16]=(b4>>8);
	dmaBuffer[17]=(b4&0xFF); 
	sendInRsDma(19);

}

void ansComSetPwmRk(int8 canal, int16 p3, int16 p4, int16 p5, int16 p6, int8 rk)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_PWM_RK; 
	dmaBuffer[2]=canal;
	dmaBuffer[3]=(p3>>8); 
	dmaBuffer[4]=(p3&0xFF);
	dmaBuffer[5]=(p4>>8);
	dmaBuffer[6]=(p4&0xFF);
	dmaBuffer[7]=(p5>>8);
	dmaBuffer[8]=(p5&0xFF); 
	dmaBuffer[9]=(p6>>8);
	dmaBuffer[10]=(p6&0xFF); 
	dmaBuffer[11]=rk; 
	sendInRsDma(13);
} 
void ansComSetPwm3(int8 canal, int16 p3)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_PWM_RK;
	dmaBuffer[2]=canal; 
	dmaBuffer[3]=(p3>>8);
	dmaBuffer[4]=(p3&0xFF);  
	sendInRsDma(6);
}  
void ansComSetPwm4(int8 canal, int16 p4)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_PWM_RK; 
	dmaBuffer[2]=canal;
	dmaBuffer[3]=(p4>>8);
	dmaBuffer[4]=(p4&0xFF);  
	sendInRsDma(6);
}  
void ansComSetPwm5(int8 canal, int16 p5)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_PWM_RK; 
	dmaBuffer[2]=canal;
	dmaBuffer[3]=(p5>>8);
	dmaBuffer[4]=(p5&0xFF);  
	sendInRsDma(6);
}  
void ansComSetPwm6(int8 canal, int16 p6)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_PWM_RK;
	dmaBuffer[2]=canal; 
	dmaBuffer[3]=(p6>>8);
	dmaBuffer[4]=(p6&0xFF);  
	sendInRsDma(6);
}  
void ansComSetRk(int8 canal, int8 rk)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_PWM_RK; 
	dmaBuffer[2]=canal;
	dmaBuffer[3]=rk; 
	sendInRsDma(5);
} 

void ansComReadCurAdc(int16 a1, int16 a2, int16 a3, int16 a4)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_READ_ADC; 
	dmaBuffer[2]=(a1>>8); 
	dmaBuffer[3]=(a1&0xFF);
	dmaBuffer[4]=(a2>>8);
	dmaBuffer[5]=(a2&0xFF);
	dmaBuffer[6]=(a3>>8);
	dmaBuffer[7]=(a3&0xFF); 
	dmaBuffer[8]=(a4>>8);
	dmaBuffer[9]=(a4&0xFF);  
	sendInRsDma(11);

}

void ansComOnOffPwm(int8 data)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_ONOFF_PWM; 
	dmaBuffer[2]=data;
	sendInRsDma(4);	
}



void ansComSetSpeedPwm(int16 canal, int16 speedMin, int16 speedMax)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_SPEED; 
	dmaBuffer[2]=canal;
	dmaBuffer[3]=(speedMin>>8); 
	dmaBuffer[4]=(speedMin&0xFF);
	dmaBuffer[5]=(speedMax>>8); 
	dmaBuffer[6]=(speedMax&0xFF);
	sendInRsDma(8);	
}
void ansComSetSpeedAllPwm(int16 can, int16 sMn3, int16 sMx3, int16 sMn4, int16 sMx4, int16 sMn5, int16 sMx5, int16 sMn6, int16 sMx6 )
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_SPEED; 
	dmaBuffer[2]=can;
	dmaBuffer[3]=(sMn3>>8); 
	dmaBuffer[4]=(sMn3&0xFF);
	dmaBuffer[5]=(sMx3>>8); 
	dmaBuffer[6]=(sMx3&0xFF);
	dmaBuffer[7]=(sMn4>>8); 
	dmaBuffer[8]=(sMn4&0xFF);
	dmaBuffer[9]=(sMx4>>8); 
	dmaBuffer[10]=(sMx4&0xFF);
	dmaBuffer[11]=(sMn5>>8); 
	dmaBuffer[12]=(sMn5&0xFF);
	dmaBuffer[13]=(sMx5>>8); 
	dmaBuffer[14]=(sMx5&0xFF);
	dmaBuffer[15]=(sMn6>>8); 
	dmaBuffer[16]=(sMn6&0xFF);
	dmaBuffer[17]=(sMx6>>8); 
	dmaBuffer[18]=(sMx6&0xFF);
	sendInRsDma(20);	

}

void ansComReadSpeed()
{
	 
	clearDmaBuf(); 
	dmaBuffer[1]=COM_READ_SPEED;
	// m3 min  
	int16 data = getMinSpeed(&m3);
	dmaBuffer[2]=(data>>8); 
	dmaBuffer[3]=(data&0xFF);
	// m4 min 
	data = getMinSpeed(&m4); 
	dmaBuffer[4]=(data>>8); 
	dmaBuffer[5]=(data&0xFF);
	// m5 min
	data = getMinSpeed(&m5); 
	dmaBuffer[6]=(data>>8); 
	dmaBuffer[7]=(data&0xFF);
	// m6 min 
	data = getMinSpeed(&m6); 
	dmaBuffer[8]=(data>>8); 
	dmaBuffer[9]=(data&0xFF);
	
	
	// m3 max 
	data = getMaxSpeed(&m3);
	dmaBuffer[10]=(data>>8); 
	dmaBuffer[11]=(data&0xFF);
	// m4 max 
	data = getMaxSpeed(&m4);
	dmaBuffer[12]=(data>>8); 
	dmaBuffer[13]=(data&0xFF);
	// m5 max 
	data = getMaxSpeed(&m5);
	dmaBuffer[14]=(data>>8); 
	dmaBuffer[15]=(data&0xFF);
	// m6 max
	data = getMaxSpeed(&m6);
	dmaBuffer[16]=(data>>8); 
	dmaBuffer[17]=(data&0xFF);
	sendInRsDma(19);	
 
}

void ansComRunCalibr()
{
	clearDmaBuf();
	dmaBuffer[1]=COM_RUN_CALIBR; 
	sendInRsDma(3);
}

void ansComReadError(int8 d1, int8 d2, int8 d3, int8 d4)
{
	clearDmaBuf();
	dmaBuffer[1]=COM_READ_ERROR; 
	dmaBuffer[2]=d1;
	dmaBuffer[3]=d2;
	dmaBuffer[4]=d3;
	dmaBuffer[5]=d4;
 	sendInRsDma(7);
}
//**********************

void ansReadCrc(int16 crc)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_READ_CRC; 
	dmaBuffer[2]=((crc>>8)&0xFF); 
	dmaBuffer[3]= (crc&0xFF); 
	sendInRsDma(5);
} 
void ansComInfo()
{
	clearDmaBuf(); 
	dmaBuffer[1]= COM_INFO;			//0x48
	dmaBuffer[2]= COM_SET_PWM_RK;	//0x31
	dmaBuffer[3]= COM_RUN_CALIBR;	//0x32
	dmaBuffer[4]= COM_SET_SPEED;	//0x33
	dmaBuffer[5]= COM_ONOFF_PWM;	//0x35
	dmaBuffer[6]= COM_READ_ADC;		//0x40
	dmaBuffer[7]= COM_LIMIT_ADC;	//0x41
	dmaBuffer[8]= COM_READ_ERROR;	//0x42	
	dmaBuffer[9]= COM_READ_SPEED;   //0x43
	dmaBuffer[10]= COM_READ_CRC;		//0x47
	dmaBuffer[11]= COM_READ_ID;		//0x46
	dmaBuffer[12]= COM_RESET_MK;		//0x55
	sendInRsDma(14);

}
void ansComId()
{
	clearDmaBuf(); 
	dmaBuffer[1]= COM_READ_ID;
	dmaBuffer[2]= ID1;
	dmaBuffer[3]= ID2;
	dmaBuffer[4]= ID3;
	dmaBuffer[5]= ID4; 
	sendInRsDma(7);
} 
void ansComRst(int8 com, int8 data)
{
	clearDmaBuf(); 
	dmaBuffer[1]= com;
	dmaBuffer[2]= data; 
	sendInRsDma(4);	
}
void ansErrorCom(int8 com)
{
	clearDmaBuf();  
	dmaBuffer[1]= (~com); 
	sendInRsDma(3);	
}

void ansErrorComCanal(int8 com)
{
	clearDmaBuf();  
	dmaBuffer[1]= COM_SET_PWM_RK;
	dmaBuffer[2]= (~com);  
	sendInRsDma(4);	
}

