/********************* User_Initialization.C*******************
文件功能：                      用户变量初始化
应用场合：    应用于500W 无尾厨电接收侧DC-DC端控制程序
作者：
建立时间：
修改时间：  2019.07.11


*********************************************************/

#include "User_all_include.h"
void Initial_User_variables()
{   int j;
	/*************PWM相关变量初始化**********/
    //SW_TBPRD = (int)(30000/SWITCH_FREQUENCY);  //300kHz的话，这里是100
	//MEP_status_count = 0;
	/*************************************/

	/*******占空比控制参数初始化*******/
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

	/**********串口参数初始化********/
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

