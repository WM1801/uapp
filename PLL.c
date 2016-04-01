#include "PLL.h"
void init_PLL()
{
	//********* Фстановка рабочей частоты 80 Юvц при кварце 16 Юvц *********
// OSCILLATOR CONFIGURATION
// PLLPRE=4  Luego N1=2 
   PLLPRE_0 = 0; 
   PLLPRE_1 = 1; 
   PLLPRE_2 = 0; 
   PLLPRE_3 = 0; 
   PLLPRE_4 = 0; 

   // PLLPOST=0  Luego N2=0
   PLLPOST_0 = 0; 
   PLLPOST_1 = 0; 

   // PLLDIV=30  Luego M=26 
   PLLDIV_0 = 0; 
   PLLDIV_1 = 1; 
   PLLDIV_2 = 1; 
   PLLDIV_3 = 0; 
   PLLDIV_4 = 0; 
   PLLDIV_5 = 1; 
   PLLDIV_6 = 0; 
   PLLDIV_7 = 0; 
   PLLDIV_8 = 0; 
//**********************************************************************
}