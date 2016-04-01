#ifndef MOTOR_H
#define MOTOR_H

typedef struct MotorAs
{
	int canalPwm;  // ��� ���
	int1 upValue; //���� ����������� ��������, ������ ������������� ���� �  ��� � ���������� �������
	int16 minValAdc; //����������� �������� ��� �� ����� ���� �����
	int16 maxValAdc; //������������ �������� ��� �� ������ ���� �����
	int16 oldValAdc; // ������� ������������ �������� �� ��� 	
	float dAdc; 	// �������� ���� � ��� �������� ���

	int8 Error;    // ������ ������ � ������� ��������� 
	int16 minSpeed; // ����������� �������� ��� ��� ������� ������� ���������
	int1 enabRotate; // ���������� ��������  
} Motor; 

void initMotor(Motor * m, int cPwm, int16 tPwm, int16 vAdc1, int16 vAdc2); 
void setLimitAdcMotor(Motor *m, int16 vAdc1, int16 vAdc2);
void setMinSpeed(Motor *m,int16 data);   
void setRotate(Motor *m, int16 currentData, int16 newData); 


#endif