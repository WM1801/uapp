#ifndef MOTOR_H
#define MOTOR_H

typedef struct MotorAs
{
	int canalPwm;  // пин ШИМ
	int1 upValue; //флаг направления движения, вводит относительный верх и  низ у нескольких моторов
	int16 minValAdc; //минимальное значение ацп на одном краю шкалы
	int16 maxValAdc; //максимальное значение ацп на другом краю шкалы
	int16 oldValAdc; // прошлое обработанное значение из АЦП 	
	float dAdc; 	// разность макс и мин значения АЦП

	int8 Error;    // хранит ошибки и текущее состояние 
	int16 minSpeed; // минимальное значение ШИМ при котором стрелка двигается
	int1 enabRotate; // разрешение вращения  
} Motor; 

void initMotor(Motor * m, int cPwm, int16 tPwm, int16 vAdc1, int16 vAdc2); 
void setLimitAdcMotor(Motor *m, int16 vAdc1, int16 vAdc2);
void setMinSpeed(Motor *m,int16 data);   
void setRotate(Motor *m, int16 currentData, int16 newData); 


#endif