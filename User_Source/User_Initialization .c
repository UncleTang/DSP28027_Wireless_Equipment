/********************* User_Initialization.C*******************
�ļ����ܣ�                      �û�������ʼ��
Ӧ�ó��ϣ�    Ӧ����500W ��β������ղ�DC-DC�˿��Ƴ���
���ߣ�
����ʱ�䣺
�޸�ʱ�䣺  2019.07.11


*********************************************************/

#include "User_all_include.h"
void Initial_User_variables()
{   int j;
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
	PWM_INT1_Count = 0;
	/********************************/

	/**********���ڲ�����ʼ��********/
	Parameter = 0;
	kp1_sci = 0;
	ki1_sci = 0;
    kp2_sci = 0;
    ki2_sci = 0;
	Vo = 0;
	IL = 0;
	Vi = 0;

    send_voltage_input = 0x01;
    send_current_input = 0x02;
    send_voltage_output = 0x03;
    send_current_output = 0x04;
	/********************************/

	ADC_INT1_Count = 0;
	ADC_INT2_Count = 0;
	for (j=0; j<=10 ;j++) Vo_test.Slide_record[j] = 0;
	for (j=0; j<=10 ;j++) Vi_test.Slide_record[j] = 0;
	for (j=0; j<=10 ;j++) IL_test.Slide_record[j] = 0;
	Vo_test.Average = 0;
	Vo_test.actual_int = 0;
	Vo_test.actual_fra = 0;
	Vi_test.Average = 0;
	Vi_test.actual_int = 0;
	Vi_test.actual_fra = 0;
	IL_test.Average = 0;
	IL_test.actual_int = 0;
	IL_test.actual_fra = 0;
}

