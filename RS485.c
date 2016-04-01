#include "RS485.h" 



//*****************************************************************
//* инициализация 
//*****************************************************************
void initRS()
{
	enable_interrupts(INT_RDA);
}

#INT_RDA
void interruptRS()
{
	buffer[indW] = getc();
	
	indW++;
	
	if(indW>RELOAD_INDW)
	{
		indW = 0; 
	}
	clear_interrupt(INT_RDA);
	
	pause3_5RS();
	
	
}

//*****************************************************************
//* пауза в 3,5 символа 
//*****************************************************************

void pause3_5RS()
{
	setup_timer4(TMR_DISABLED);
    clear_interrupt(INT_TIMER4);
	set_timer4(0); 	 
	setup_timer4(TMR_INTERNAL|TMR_DIV_BY_256, pause );///
	enable_interrupts(int_timer4);
//	output_high(PIN_G13);
	//3.8mS

}
//****************************************************************
// таймер расчета паузы в 3.5 символа 
//****************************************************************

#int_timer4 // 
void __timer4_isr__(void)
{
	 //1.6ms
//	output_low(PIN_G13);
	setup_timer4(TMR_DISABLED);
	clear_interrupt(INT_TIMER4);
	FLAG = TRUE; 
    set_timer4(0); 
	//1.6ms
	
}

//****************************************************************
// вывод  RS
//***************************************************************

void sendRS( int8 msg)
{

	output_high(ENABLE);
	while(MCU_UTXBF); 
	MCU_U1TXREG = msg;  
	#asm nop #endasm
	while(!MCU_TRMT); 
	output_low(ENABLE); 
}


void sendRS16( int16 msg)
{

	output_high(ENABLE);
	while(MCU_UTXBF); 
	MCU_U1TXREG = ((msg>>8)&0xFF);  
	#asm nop #endasm
	while(!MCU_TRMT); 

	while(MCU_UTXBF); 
	MCU_U1TXREG = (msg&0xFF);  
	#asm nop #endasm
	while(!MCU_TRMT); 
	output_low(ENABLE); 
}

