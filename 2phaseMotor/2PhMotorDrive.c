/////////////////////////////////////////////////////////////////////////

#include <24hj64gp206.h> 

#DEVICE ADC=10

#FUSES NOWDT                       //No Watch Dog Timer 
#FUSES PR,HS                   //High speed Osc (> 4mhz) 
#FUSES PUT64                       //Power Up Timer 
#FUSES NOPROTECT                   //Code not protected from reads 
#FUSES NODEBUG                     //No Debug mode for ICD 
#FUSES NOWRT                       //Program memory not write protected 

#use delay(clock=16Mhz) 

 
#use rs232(uart1, baud=9600,parity=N,  BITS =8,STOP=1,STREAM=RS485) 

#use standard_io(All)

//********************************************************************
//Регистры МК для ШИМ 
#word OC1R = getenv("sfr:OC1R") 
#word OC1RS = getenv("sfr:OC1RS")
#word OC2R = getenv("sfr:OC2R") 
#word OC2RS = getenv("sfr:OC2RS")
#word OC3R = getenv("sfr:OC3R") 
#word OC3RS = getenv("sfr:OC3RS")
#word OC4R = getenv("sfr:OC4R") 
#word OC4RS = getenv("sfr:OC4RS")
#word OC5R = getenv("sfr:OC5R") 
#word OC5RS = getenv("sfr:OC5RS")
#word OC6R = getenv("sfr:OC6R") 
#word OC6RS = getenv("sfr:OC6RS")
//********************************************************************
//Выходы управления
#define BL1 PIN_F0
#define BL2 PIN_F1
#define LED1 PIN_G7//Green LED
#define LED2 PIN_G8//Red LED
#define SD PIN_G15//Enable GEN
#define EXTLED1 PIN_G0
#define EXTLED2 PIN_G1
#define DIRRS PIN_F6
//********************************************************************
unsigned int Dat[10];      
char Ndat;
unsigned int D=0;
char inchar=0x1e;
unsigned int outchar;
unsigned int i;
unsigned int Nt[5],E1,E2,E3,E4,V[5],ADC;
unsigned int Adr=0x30;			//адрес модуля
//***********************************************************
//***********************************************************
void answer(){
//****************************************************************
//*************  Write 4 chanel (func 0x10) rs-485 *****
//****************************************************************
output_high(LED2);//Red LED On
if ((Ndat==6)&(Dat[1]==Adr)&(Dat[2]==0x10)){

disable_interrupts(INT_TIMER4);
disable_interrupts(INT_RDA);
	delay_ms(8);
Nt[1]=Dat[3];
Nt[2]=Dat[4];
Nt[3]=Dat[5];
Nt[4]=Dat[6];
output_high(PIN_F6);//enable tx rs485

	putc(Adr);//1 TX
	delay_us(1100);
	putc(0x10);//2 TX
	delay_us(1100);
	putc(Nt[1]);//3 TX
	delay_us(1100);
	putc(Nt[2]);//4 TX
	delay_us(1100);
	putc(Nt[3]);//5 TX
	delay_us(1100);
	putc(Nt[4]);//6 TX
	delay_us(1100);

output_low(PIN_F6);//enable rx rs485

Ndat=0;
//Restart UART1(soft var-better)
setup_uart(FALSE);
setup_uart(TRUE);
clear_interrupt(INT_TIMER4);

enable_interrupts(INT_TIMER4);
enable_interrupts(INT_RDA);
}
//****************************************************************
//*************  Write 1 chanel (func 0x06) rs-485 *****
//****************************************************************
if ((Ndat==3)&(Dat[1]==Adr)&(Dat[2]==0x06)){

disable_interrupts(INT_TIMER4);
disable_interrupts(INT_RDA);
	delay_ms(8);

if ( bit_test(Dat[3],0)) output_high(BL1);//BL1 OFF
	else output_low(BL1);//BL1 On
if ( bit_test(Dat[3],1)) output_high(BL2);//BL2 OFF
	else output_low(BL2);//BL2 On

output_high(PIN_F6);//enable tx rs485

	putc(Adr);//1 TX
	delay_us(1100);
	putc(0x06);//2 TX
	delay_us(1100);
	putc(Dat[3]);//3 TX
	delay_us(1100);

output_low(PIN_F6);//enable rx rs485

Ndat=0;
//Restart UART1(soft var-better)
setup_uart(FALSE);
setup_uart(TRUE);
clear_interrupt(INT_TIMER4);

enable_interrupts(INT_TIMER4);
enable_interrupts(INT_RDA);
}
}
//***********************************************************
//***********************************************************
#int_TIMER4
void  TIMER4_isr(void) 
{
disable_interrupts(INT_TIMER4);
disable_interrupts(INT_RDA);
answer();//Ответ
Ndat=0;
clear_interrupt(INT_TIMER4);
output_high(LED2);//Red LED ON
enable_interrupts(INT_RDA);
disable_interrupts(INT_TIMER4);

}

//***********************************************************
#int_RDA
void  RDA_isr(void)
{

disable_interrupts(INT_TIMER4);

inchar= getc(RS485);

output_high(LED2);//Red LED ON

Ndat=Ndat+1;
Dat[Ndat]=inchar;

set_timer4(0);

//Restart UART1(soft var-better)
setup_uart(FALSE);
setup_uart(TRUE);
clear_interrupt(INT_TIMER4);
enable_interrupts(INT_TIMER4);

}
//***********************************************************
void main() 
{ 

output_low(BL1);//BL1 On
output_low(BL2);//BL2 On
delay_ms(1000);

Ndat=0;

output_high(BL1);//BL1 OFF
output_high(BL2);//BL2 OFF

output_low(LED1);//Green LED OFF

enable_interrupts(INTR_GLOBAL);
enable_interrupts(INT_RDA);

	setup_timer4(TMR_INTERNAL|TMR_DIV_BY_256,250); //4ms

	setup_timer3(TMR_INTERNAL | TMR_DIV_BY_1,20000 );



//2 PHASE 400 Hz 
setup_compare( 1,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC1R   = 0;
OC1RS =10000;

setup_compare( 2,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC2R   = 10000;
OC2RS =0;

setup_compare( 3,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC3R   = 5000;
OC3RS =15000;

setup_compare( 4,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC4R   = 5000;
OC4RS =15000;

setup_compare( 5,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC5R   = 15000;
OC5RS =5000;

setup_compare( 6,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC6R   = 5000;
OC6RS =15000;

output_high(LED1);//Green LED ON
output_high(SD);//Enable GEN 

setup_adc_ports( sAN2|sAN3|sAN13|sAN14|VSS_VDD ); //setup_adc_ports(AN); 
setup_adc(ADC_CLOCK_DIV_8); //enables the a/d module and sets the clock to internal adc clock 

Nt[1]=0x85;
Nt[2]=0x85;
Nt[3]=0x85;
Nt[4]=0x85;
           
while (TRUE) 
    {

output_high(LED1);//Green LED ON

//************ 1 Chanel (left index)***********************
set_adc_channel(2);
delay_us(100);
V[1]=0;
For ( i=1; i<= 4;++i)
{
ADC= read_adc(ADC_START_AND_READ);
V[1]=V[1]+ADC;
}
V[1]=V[1]/16;


D=10000;
if (Nt[1]>V[1]){
 D=10000+((Nt[1]-V[1])*100)-((E1-(Nt[1]-V[1]))*100);
 E1=Nt[1]-V[1];
if (Nt[1]>(V[1]+50)) D=15000;
}
if (Nt[1]<V[1]){

 D=10000-((V[1]-Nt[1])*100)+((E1-(V[1]-Nt[1]))*100);
 E1=V[1]-Nt[1];
if ((Nt[1]+50)<V[1]) D=5000;
}

// if (Nt>(outchar+1)) D=10200;
//if (Nt<(outchar-1)) D=9800;
//if (Nt>(outchar+10)) D=10500;
//if (outchar>10) if (Nt<(outchar-10)) D=9500;
//if (Nt>(outchar+20)) D=10800;
//if (outchar>20) if (Nt<(outchar-20)) D=9200;
//if (Nt>(outchar+50)) D=15000;
//if (outchar>50) if (Nt<(outchar-50)) D=5000;
//if (D>=20000) D=0;

//setup_compare( 3,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC3R   = D;
if (D<=10000) OC3RS =10000+D;
else OC3RS =D-10000;

//************ 2 Chanel (arrow right)***********************

set_adc_channel(3);
delay_us(100);
V[2]=0;
For ( i=1; i<= 4;++i)
{
ADC= read_adc(ADC_START_AND_READ);
V[2]=V[2]+ADC;
}
V[2]=V[2]/16;

D=10000;
if (Nt[2]>V[2]){

 D=10000-((Nt[2]-V[2])*100)+((E2-(Nt[2]-V[2]))*100);
 E2=Nt[2]-V[2];
if (Nt[2]>(V[2]+50)) D=5000;
}

if (Nt[2]<V[2]){

 D=10000+((V[2]-Nt[2])*100)-((E2-(V[2]-Nt[2]))*100);
 E2=V[2]-Nt[2];
if ((Nt[2]+50)<V[2]) D=15000;
}

//setup_compare( 4,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC4R   = D;
if (D<=10000) OC4RS =10000+D;
else OC4RS =D-10000;

//************ 3 Chanel (arrow left)***********************
set_adc_channel(13);
delay_us(100);
V[3]=0;
For ( i=1; i<= 4;++i)
{
ADC= read_adc(ADC_START_AND_READ);
V[3]=V[3]+ADC;
}
V[3]=V[3]/16;

D=10000;
if (Nt[3]>V[3]){
 D=10000-((Nt[3]-V[3])*100)+((E3-(Nt[3]-V[3]))*100);
 E3=Nt[3]-V[3];
if (Nt[3]>(V[3]+50)) D=5000;
}

if (Nt[3]<V[3]){

 D=10000+((V[3]-Nt[3])*100)-((E3-(V[3]-Nt[3]))*100);
 E3=V[3]-Nt[3];
if ((Nt[3]+50)<V[3]) D=15000;
}

//setup_compare( 5,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC5R   = D;
if (D<=10000) OC5RS =10000+D;
else OC5RS =D-10000;

//************ 4 Chanel (right index)***********************
set_adc_channel(14);
delay_us(100);
V[4]=0;
For ( i=1; i<= 4;++i)
{
ADC= read_adc(ADC_START_AND_READ);
V[4]=V[4]+ADC;
}
V[4]=V[4]/16;

D=10000;
if (Nt[4]>V[4]){
 D=10000+((Nt[4]-V[4])*100)-((E4-(Nt[4]-V[4]))*100);
 E4=Nt[4]-V[4];
if (Nt[4]>(V[4]+50)) D=15000;
}

if (Nt[4]<V[4]){

 D=10000-((V[4]-Nt[4])*100)+((E4-(V[4]-Nt[4]))*100);
 E4=V[4]-Nt[4];
if ((Nt[4]+50)<V[4]) D=5000;
}

//setup_compare( 6,COMPARE_CONT_PULSE | COMPARE_TIMER3 );
OC6R   = D;
if (D<=10000) OC6RS =10000+D;
else OC6RS =D-10000;

//*****************************************

output_low(LED2);//Red LED OFF
output_low(LED1);//Green LED OFF
delay_ms(50);

    } 
} 

