/*
 * User_Function.h
 *
 *  Created on: 2019年6月25日
 *      Author: JYW
 */

#ifndef USER_HEADS_USER_FUNCTIONS_H_
#define USER_HEADS_USER_FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TARGET_GLOBAL
   #define TARGET_EXT 	extern
#else
   #define TARGET_EXT
#endif




/***********函数声明开始***********/

extern void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);  //TI现成函数 无需修改


//TARGET_EXT interrupt void epwm1_isr(void);
TARGET_EXT void Initial_User_variables();
//TARGET_EXT void User_min_middle_max_1();
//TARGET_EXT void User_min_middle_max_2();
TARGET_EXT void User_PID();
TARGET_EXT void User_Protect();
TARGET_EXT void User_Soft_start();
TARGET_EXT __interrupt void epwm1_isr();


/*************串口通信相关函数**********/
TARGET_EXT void scia_basic_init();     //SCI模块基本设置初始化
TARGET_EXT void receive_parameter();   //获取用户希望进行操作的参数
TARGET_EXT void PC_modify_kp_or_ki();  //dsp通过SCI接收电脑发送的修改参数
TARGET_EXT void PC_update_vo_or_il_or_vi();  //把dsp采集的输出电压电流参数通过SCI发送给电脑
TARGET_EXT int pow(int a, int b);   //乘方函数
TARGET_EXT void scia_send_Char_one_by_one(char * Str);  //用于发送提示语句
TARGET_EXT void scia_working();

/*************************************/

/*************ADC相关函数**********/
TARGET_EXT void Adc_basic_init();
TARGET_EXT __interrupt void Adcint1_isr();
TARGET_EXT __interrupt void Adcint2_isr();
TARGET_EXT Uint16 ADC_Medium(Uint16, Uint16, Uint16);
TARGET_EXT Uint16 ADC_Maximum(Uint16, Uint16, Uint16);
TARGET_EXT Uint16 ADC_Minimum(Uint16, Uint16, Uint16);
//TARGET_EXT void User_AD_Read();

/*************************************/



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* USER_HEADS_USER_FUNCTIONS_H_ */
