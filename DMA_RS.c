#define SIZE_DMA_BUF 15
#define PIN_RS_SEND PIN_F6
int1 dmaBusy = 0; 
// ответы по RS
void ansComSetAllUi(int8 Ustr, int8 Uind, int8 Pstr, int8 Pind, int8 UPbln); 
void ansComSetUgolStr(int8 Ustr);  
void ansComSetUgolInd(int8 Uind);  
void ansComSetPrgStr(int8 Pstr);  
void ansComSetPrgInd(int8 Pind);  
void ansComSetUPBln(int8 Pbln); 

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


void ansComSetAllUi(int8 Ustr, int8 Uind, int8 Pstr, int8 Pind, int8 UPbln)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_ALL_UI; 
	dmaBuffer[2]=Ustr; 
	dmaBuffer[3]=Uind;
	dmaBuffer[4]=Pstr;
	dmaBuffer[5]=Pind;
	dmaBuffer[6]=UPbln;
	sendInRsDma(8);
} 
void ansComSetUgolStr(int8 Ustr)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_UGOL_STR; 
	dmaBuffer[2]=Ustr; 
	sendInRsDma(4);
}  
void ansComSetUgolInd(int8 Uind)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_UGOL_IND; 
	dmaBuffer[2]=Uind; 
	sendInRsDma(4);
}  
void ansComSetPrgStr(int8 Pstr)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_PRG_STR; 
	dmaBuffer[2]=Pstr; 
	sendInRsDma(4);
}  
void ansComSetPrgInd(int8 Pind)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_PRG_IND; 
	dmaBuffer[2]=Pind; 
	sendInRsDma(4);
}  
void ansComSetUPBln(int8 Pbln)
{
	clearDmaBuf(); 
	dmaBuffer[1]=COM_SET_UP_BLN; 
	dmaBuffer[2]=Pbln; 
	sendInRsDma(4);
} 


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
	dmaBuffer[1]= COM_INFO;
	dmaBuffer[2]= COM_SET_ALL_UI;
	dmaBuffer[3]= COM_SET_UGOL_STR;
	dmaBuffer[4]= COM_SET_UGOL_IND;
	dmaBuffer[5]= COM_SET_PRG_STR;
	dmaBuffer[6]= COM_SET_PRG_IND;
	dmaBuffer[7]= COM_SET_UP_BLN;

	dmaBuffer[8]= COM_READ_CRC;
	dmaBuffer[9]= COM_READ_ID;
	dmaBuffer[10]= COM_RESET_MK;
	sendInRsDma(12);

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