#ifndef RS485_H
#define RS485_H



#define ENABLE PIN_F6

int indW = 0; 

#define SIZE_RS_BUFFER 24
#define RELOAD_INDW  22// SIZE_RS_BUFFER - 2  

int8  buffer[SIZE_RS_BUFFER] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int1 FLAG = 0; 
int16 pause = 47;/*115200/80MHZ*/ //35;/*115200/60MHz*/ 


void pause3_5RS(); 
void sendRS( int8 msg); 
void sendRS16( int8 msg);
void initRS(); 

#endif