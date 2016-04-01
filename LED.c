// used timer5 

#define LED_GREEN_ON {output_high(PIN_G7); output_low(PIN_G0);}
#define LED_GREEN_OFF {output_low(PIN_G7); output_high(PIN_G0);}
#define LED_RED_ON {output_high(PIN_G8); output_low(PIN_G1);}
#define LED_RED_OFF {output_low(PIN_G8); output_high(PIN_G1);}

// color vd
#define LED_RED   0x5555
#define LED_GREEN 0xAAAA

int1 runRedVd = 0; 
int1 runGreenVd = 0; 
int1 periodRed = 0;
int1 periodGreen = 0;

void runVD(int color); 
void initLed(); 

static const int16 time = 15625; //10Hz//23528; // Fcy = Fosc/2; t=Fcy*256 (t.k. (TMR_INTERNAL|TMR_DIV_BY_256)
//************************************************************
//*
//************************************************************
void initLed()
{
	setup_timer5(TMR_INTERNAL|TMR_DIV_BY_256, time );
	set_timer5(0);
	enable_interrupts(INT_TIMER5);
	runVD(LED_GREEN); 
	runVD(LED_RED); 
}
//************************************************************
// управление светодиодом
//************************************************************
void runVD(int color)
{

	switch(color)
	{
		case LED_RED: 
		{
			if(!periodRed) 
			{
				runRedVd = 1; 				
			} 		
			break; 
		}
		case LED_GREEN: 
		{
			if(!periodGreen)
			{
				runGreenVd = 1; 
			} 
			break; 
		}
		default:
		{

		}
	}
}



//***************************************************************
//*
//***************************************************************
#int_timer5
void timer5_isr(void)
{
	if(runRedVd)
	{
		LED_RED_ON;
		runRedVd = 0;
		periodRed = 1; 
	}
	else 
	{	
	 	LED_RED_OFF;
		periodRed = 0; 
	
	}
	
	if(runGreenVd)
	{
			LED_GREEN_OFF;
			runGreenVd = 0; 
			periodGreen = 1;  
	}
	else
	{
		LED_GREEN_ON; 
		periodGreen = 0; 

	}
	clear_interrupt(INT_TIMER5);
//	disable_interrupts(INT_TIMER5);
	set_timer5(0);
 
}

