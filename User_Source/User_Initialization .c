/********************* User_Initialization.C*******************
�ļ����ܣ�                      �û�������ʼ��
Ӧ�ó��ϣ�    Ӧ����500W ��β������ղ�DC-DC�˿��Ƴ���
���ߣ�
����ʱ�䣺
�޸�ʱ�䣺  2019.07.11


*********************************************************/

#include "User_all_include.h"
void Initial_User_variables()
{
	/*************PWM��ر�����ʼ��**********/
    //SW_TBPRD = (int)(30000/SWITCH_FREQUENCY);  //300kHz�Ļ���������100
	//MEP_status_count = 0;
	/*************************************/

	/*******ռ�ձȿ��Ʋ�����ʼ��*******/
	Kp = _IQ15(1);
	Ki = _IQ15(0);
	PIout_This_Time = _IQ15(0);
	PIout_Last_Time = _IQ15(0);
	Error_This_Time = _IQ15(0);
	Error_Last_Time = _IQ15(0);
	SoftStart_Flag  = 1;
	SoftStart_Period = _IQ15(0);
	/********************************/

	/**********���ڲ�����ʼ��********/
	Parameter = 0;
	kp_sci = 0;
	ki_sci = 0;
	Vo = 0;
	IL = 0;
	Vi = 0;
	/********************************/
}

