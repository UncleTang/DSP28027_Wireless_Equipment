/*
 * User_variable.h
 *
 *  Created on: 2019年6月25日
 *      Author: JYW
 *修改人：Jialin Luo
 * 修改日期：2019年7月11日
 */  //头文件中只能声明全局变量，用extern，不能定义全局变量。因为若全局变量定义在h文件中，多个c文件都包括了该头文件，则变量定义了多次，会报错。所以全局变量只能在源文件中定义。（定义只能一次，生命可以很多次）

#ifndef USER_HEADS_USER_VARIABLES_H_
#define USER_HEADS_USER_VARIABLES_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TARGET_GLOBAL
   #define TARGET_EXT 	extern
#else
   #define TARGET_EXT
#endif

/*
TARGET_EXT Uint16 RamfuncsLoadStart;
TARGET_EXT Uint16 RamfuncsLoadEnd;
TARGET_EXT Uint16 RamfuncsRunStart;
TARGET_EXT Uint16 RamfuncsLoadSize;*/



/*********控制系统相关变量宏定义********/
#define Flash_Open 1         //Flash 运行方式切换位 0---RAM;1---Flash
#define SWITCH_FREQUENCY      100	//开关频率(kHz)
#define DC_DUTY_INIT          0.773  //  初始占空比
#define Drive_on_or_off       1    //  1 为on    2 为off
#define pi 3.141592653
/************************************/


/**********系统级相关变量**************/
struct SYSTEMRunstate_Flag
{
	   Bool normal;//系统正常运行标志位
	   Bool error; //系统总故障标志位
};
TARGET_EXT volatile struct SYSTEMRunstate_Flag System_Runstate_Flag;
/*************************************/


/**********PWM控制相关变量************/
TARGET_EXT _iq dc_dc2_duty;
TARGET_EXT _iq dc_dc2_duty_correct;
TARGET_EXT _iq modulate_duty;
TARGET_EXT _iq modulate_duty_correct;

TARGET_EXT _iq epwm1_data;           //PWM比较值
TARGET_EXT Uint32 epwm1_data_int;   //PWM比较值 整数部分
TARGET_EXT Uint32 epwm1_data_fra;   //PWM比较值 小数部分
TARGET_EXT Uint32 epwm2_data;

//TARGET_EXT int SW_TBPRD;
//TARGET_EXT _iq15 SW_TBPRD_IQ15;
TARGET_EXT 	Uint32 epwm1_data_int_init;   //PWM比较值 整数部分
TARGET_EXT 	Uint32 epwm1_data_fra_init;   //PWM比较值 小数部分

TARGET_EXT Uint16 MEP_status;
TARGET_EXT Uint32 MEP_status_count;

TARGET_EXT Uint32 MEP_ScaleFactor;
TARGET_EXT Uint32 ePWM;

TARGET_EXT Uint16 PWM_INT1_Count;
/*************************************/

/*************AD采样相关变量**********/
//TARGET_EXT Uint16 Vi_ADC;
//TARGET_EXT Uint16 IL_ADC;
//TARGET_EXT Uint16 Vo_ADC;
//TARGET_EXT Uint16 Temperature_ADC;
typedef struct
   {
	Uint16 Record_0;
	Uint16 Record_1;
	Uint16 Record_2;
	Uint16 Record[3];
	Uint16 Median;
	Uint16 Minimum;
	Uint16 Maximum;
	Uint16 Slide_record[10];
	Uint16 Average;
	_iq actual_IQ;
	Uint16 actual_int;
	Uint16 actual_fra_IQ;
	Uint16 actual_fra;
   }ADC_Sample;
TARGET_EXT ADC_Sample Vi_test;
TARGET_EXT ADC_Sample IL_test;
TARGET_EXT ADC_Sample Vo_test;
TARGET_EXT ADC_Sample Temperature_test;
TARGET_EXT Uint16 ADC_INT1_Count;
TARGET_EXT Uint16 ADC_INT2_Count;
//TARGET_EXT Uint16 Slide_Average_Vo[10];
//TARGET_EXT Uint16 Slide_Average_Vi[10];
//TARGET_EXT Uint16 Slide_Average_IL[10];
//TARGET_EXT Uint16 Vo_average;
//TARGET_EXT Uint16 Vi_average;
//TARGET_EXT Uint16 IL_average;
//TARGET_EXT _iq Vi_real_IQ;
//TARGET_EXT Uint16 Vi_real_int;
//TARGET_EXT Uint16 Vi_real_fra_IQ;
//TARGET_EXT Uint16 Vi_real_fra;
/*************************************/

/*************控制算法相关变量**********/
#define PIout_Maximum  _IQ15(200)   //增减计数下用#define PIout_Maximum  _IQ15(100)
#define PIout_Minimum  _IQ15(0)
#define Vo_Ref 3078  //输出电压参考值220V，送进DSP的值为2.48，ADC后为3078
#define Vo_max 3351  //输出电压最大限值240V，送进DSP的值为2.48，ADC后为3351
TARGET_EXT _iq Kp;
TARGET_EXT _iq Ki;
TARGET_EXT _iq PIout_This_Time;
TARGET_EXT _iq PIout_Last_Time;
TARGET_EXT _iq Error_This_Time;
TARGET_EXT _iq Error_Last_Time;
TARGET_EXT Uint16 SoftStart_Flag;
TARGET_EXT _iq SoftStart_Period;
/*************************************/


/*************串口通信相关变量及宏定义**********/
//#define SCI_BAUD_9600 0x00C2  //对应9600波特率
//#define SCI_BAUD_115200 0x000F  //对应115200波特率
//#define ASK_FOR_KP 0x6B70   //用户输入kp的对应字符
//#define ASK_FOR_KI 0x6B69   //用户输入ki的对应字符
//#define ASK_FOR_Vo 0x766F   //用户输入vo的对应字符
//#define ASK_FOR_Io 0x696F   //用户输入io的对应字符
//TARGET_EXT Uint16 ParameterH; //Parameter的高8位
//TARGET_EXT Uint16 ParameterL; //Parameter的低8位
TARGET_EXT Uint16 Parameter;  //用以判断电脑写入参数为kp还是ki
//TARGET_EXT Uint16 PC_Input_Value;  //用以记录由电脑发送过来的kp或ki值
TARGET_EXT float kp_sci;  //读取电脑发过来的kp值
TARGET_EXT float ki_sci;  //读取电脑发过来的ki值
TARGET_EXT Uint16 Vo;  //当前输出电压值
TARGET_EXT Uint16 IL;  //当前电感电流值
TARGET_EXT Uint16 Vi;  //当前输入电压值
//TARGET_EXT Uint16 Temperature;  //当前温度值
//TARGET_EXT char *msg1;  //语句1
//TARGET_EXT char *msg2;  //语句2
//TARGET_EXT char *msg3;  //语句3
//TARGET_EXT char *msg4;  //语句4
TARGET_EXT char send_voltage_input;
TARGET_EXT char send_current_input;
TARGET_EXT char send_voltage_output;
TARGET_EXT char send_current_output;
/*************************************/

/*************保护作用变量及宏定义**********/
#define Disable DCEVT          0
#define DCH_Low_DCL_NotCare    1
#define DCH_High_DCL_NotCare   2
#define DCH_NotCare_DCL_Low    3
#define DCH_NotCare_DCL_High   4
#define DCH_Low_DCL_High       5  //定义DC模块产生DCEVT事件的条件
#define Vo_Max  3351  //对应输出电压上限240V
#define Vi_Max  3922  //对应输入电压上限95V
/*****************************************/

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* USER_HEADS_USER_VARIABLES_H_ */
