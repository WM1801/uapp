#ifndef MOTOR_H
#define MOTOR_H

//#define MIN_ERROR  2.0f // минимальная ошибка для доворота 

#define MIN_DADC 0x00FF //минимальная разница между граничными значениями АЦП

// Error
// bits
#define END_CALIBR    0x80 // флаг окончания калибровки
#define ERROR_CLBR   0x40 // вышло время калибровки, значения не прочитались
#define ERR_PWR_ANALOG_ON (0x20) // силовая часть включена
#define ERR_PWR_KZ    	   (0x10) // замыкание силовой части 
#define ERR_DADC      0x08 //(dADC<MIN_ADC) // мотор не крутится положение макс и мин ацп менее MIN_DADC 
#define ERR_VADC2_B   0x04 //vAdc1<vAdc2 // определяет верх и низ
#define ERR_VADC1_B   0x02 //vAdc1>vAdc2 // определяет верх и низ
#define ERR_VADC_RAVN 0x01 //vAdc1=vAdc2 // калибровки не было 
//#define MAX_INT_ERROR 50    
//#define MIN_INT_ERROR (-50) 


typedef struct MotorAs
{
	int canalPwm;  // пин ШИМ
	int1 upValue; //флаг направления движения, вводит относительный верх и  низ у нескольких моторов
	int16 minValAdc; //минимальное значение ацп на одном краю шкалы
	int16 maxValAdc; //максимальное значение ацп на другом краю шкалы
	int16 oldValAdc; // прошлое значение используемое для установки 
	int16 newValue; // новое значение в которое необходимо перейти стрелке
	float dAdc; 	// разность макс и мин значения АЦП
	float kP;  // 	(m->maxSpeed/m->dAdc) где (m->maxSpeed = POL_POL_PERIOD(default)) знач ШИМ для макс 
				//скорости(1/4Шим(90градусов сдвиг между каналами ШИМ)))) 
				// и m->dAdc диапазон шкалы в значениях АЦП
	float kD; 
	float kI; 
	int8 Error;    // хранит ошибки и текущее состояние 
	int16 minSpeed; // минимальное значение ШИМ при котором стрелка двигается
	int16 maxSpeed; // максимальное значение ШИМ при котором стрелка двигается (1/4 значения счетчика ШИМ)
	int16 maxAccel; // максимальное ускорение
	int16 minAccel; // минимальное ускорение 
	int16 oldSpeed; // значение скорости в прошлый перерасчет положения
	int1 enabRotate; // разрешение вращения 
	signed int maxIEr; // максимальная ошибка интегр. сост 
	signed int minIEr; // минимальная ошибка интегр. сост
	signed int integrError;
} Motor; 

 
 
void initMotor(Motor * m, int cPwm, int16 tPwm, int16 vAdc1, int16 vAdc2); 
void setLimitAdcMotor(Motor *m, int16 vAdc1, int16 vAdc2);
void setMinSpeed(Motor *m,int16 data); 
void setMaxSpeed(Motor *m,int16 data);    
void setRotate(Motor *m, int16 currentData, int16 newData); 
int16 difSost(Motor *m, float data); 
int16 intSost(Motor *m, int1 dir, float data); 
int16 proSost(Motor *m, int16 data, float eData); 
void setNewValueMotor (Motor *m, int16 data); 
void setK(Motor *m);
void setMaxAccel(Motor *m, int16 data);  

void setIntError(Motor *m,signed int minE, signed int maxE);
void setOrError(Motor *m, int8 data); 
void setAndError(Motor *m, int8 data); 
//void setError(Motor *m, int8 data); 
void updateError(Motor *m);
//void setMinRotate(int16 min_error);  

//get setting motor
int16 getMinSpeed(Motor *m); 
int16 getMaxSpeed(Motor *m); 
int16 getMinAccel(Motor *m); 
int16 getMaxAccel(Motor *m); 
int8  getError(Motor *m); 





#endif