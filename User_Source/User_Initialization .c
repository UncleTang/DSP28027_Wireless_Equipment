/********************* User_Initialization.C*******************
文件功能：                      用户变量初始化
应用场合：    应用于500W 无尾厨电接收侧DC-DC端控制程序
作者：
建立时间：
修改时间：  2019.07.11


*********************************************************/

#include "User_all_include.h"
void Initial_User_variables()
{
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
	/********************************/

	/**********串口参数初始化********/
	Parameter = 0;
	kp_sci = 0;
	ki_sci = 0;
	Vo = 0;
	IL = 0;
	Vi = 0;
	/********************************/
}

