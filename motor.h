#ifndef MOTOR_H
#define MOTOR_H

//#define MIN_ERROR  2.0f // ����������� ������ ��� �������� 

#define MIN_DADC 0x00FF //����������� ������� ����� ���������� ���������� ���

// Error
// bits
#define END_CALIBR    0x80 // ���� ��������� ����������
#define ERROR_CLBR   0x40 // ����� ����� ����������, �������� �� �����������
#define ERR_PWR_ANALOG_ON (0x20) // ������� ����� ��������
#define ERR_PWR_KZ    	   (0x10) // ��������� ������� ����� 
#define ERR_DADC      0x08 //(dADC<MIN_ADC) // ����� �� �������� ��������� ���� � ��� ��� ����� MIN_DADC 
#define ERR_VADC2_B   0x04 //vAdc1<vAdc2 // ���������� ���� � ���
#define ERR_VADC1_B   0x02 //vAdc1>vAdc2 // ���������� ���� � ���
#define ERR_VADC_RAVN 0x01 //vAdc1=vAdc2 // ���������� �� ���� 
//#define MAX_INT_ERROR 50    
//#define MIN_INT_ERROR (-50) 


typedef struct MotorAs
{
	int canalPwm;  // ��� ���
	int1 upValue; //���� ����������� ��������, ������ ������������� ���� �  ��� � ���������� �������
	int16 minValAdc; //����������� �������� ��� �� ����� ���� �����
	int16 maxValAdc; //������������ �������� ��� �� ������ ���� �����
	int16 oldValAdc; // ������� �������� ������������ ��� ��������� 
	int16 newValue; // ����� �������� � ������� ���������� ������� �������
	float dAdc; 	// �������� ���� � ��� �������� ���
	float kP;  // 	(m->maxSpeed/m->dAdc) ��� (m->maxSpeed = POL_POL_PERIOD(default)) ���� ��� ��� ���� 
				//��������(1/4���(90�������� ����� ����� �������� ���)))) 
				// � m->dAdc �������� ����� � ��������� ���
	float kD; 
	float kI; 
	int8 Error;    // ������ ������ � ������� ��������� 
	int16 minSpeed; // ����������� �������� ��� ��� ������� ������� ���������
	int16 maxSpeed; // ������������ �������� ��� ��� ������� ������� ��������� (1/4 �������� �������� ���)
	int16 maxAccel; // ������������ ���������
	int16 minAccel; // ����������� ��������� 
	int16 oldSpeed; // �������� �������� � ������� ���������� ���������
	int1 enabRotate; // ���������� �������� 
	signed int maxIEr; // ������������ ������ ������. ���� 
	signed int minIEr; // ����������� ������ ������. ����
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