/********************* User_PID.C*******************
文件功能：                        用于计算DC-DC电流环给定，电压环PID
应用场合：    应用于500W 无尾厨电接收侧DC-DC端采样
作者：
建立时间：
修改时间：  2019.07.13

函数1: User_PID()
函数1功能：电压环PID
函数1输入参数：当前输出电压值；
                          输出电压给定；
                          比例系数；
                          积分系数

函数1输出参数：电流环给定
*********************************************************/
#include "User_all_include.h"
#pragma CODE_SECTION(User_PID, "ramfuncs");
void User_PID()
{
	_iq PIout;
	_iq DutyCycle_Correct;
	_iq DutyCycle_Int;
	_iq DutyCycle_Fra;
    //_iq PIout_Maximum = _IQ15(100);
    //_iq PIout_Minimum = _IQ15(0);

    Error_This_Time = _IQ15(Vo_Ref)-_IQ15(Vo);
   /******带内部饱和的数字PI计算******/
   PIout_This_Time = PIout_Last_Time + _IQ15mpy((Error_This_Time - Error_Last_Time) , Kp) + _IQ15mpy(Error_This_Time,Ki);  //离散PI：y(k+1)=y(k)+kp*[e(k+1)-e(k)]+ki*△t*e(k+1)。这里取Kp=_IQ15(kp)，KI=_IQ15(ki*△t)，△t是指采样周期
   if (PIout_This_Time >= PIout_Maximum) {PIout_Last_Time = PIout_Maximum;}//饱和值，PI计算的值不能超过该值（PI内部限幅）
   else if (PIout_This_Time <= PIout_Minimum) {PIout_Last_Time = PIout_Minimum;}
   else PIout_Last_Time = PIout_This_Time;

  /*******************/

   /******软启动函数******/
   if(SoftStart_Flag==1)  //如果是处于软启动阶段
   {
	   SoftStart_Period += _IQ15(0.0001);
   }
   if(SoftStart_Period>=_IQ15(1))  //如果SoftStart_Period已经增大到1，则软启动阶段结束
   {
	   SoftStart_Flag = 0;
	   SoftStart_Period = _IQ15(1);
   }
   PIout = _IQ15mpy(PIout_This_Time , SoftStart_Period);
   /*******************/

   /******把计算结果转化为写入CMP寄存器的值******/
   DutyCycle_Correct = PIout;   //增减计数+CAU_SET+CAD_CLEAR的方案则是 DutyCycle_Correct = _IQ15(100) - PIout;
   DutyCycle_Int = _IQ15int(DutyCycle_Correct);
   DutyCycle_Fra = _IQ15int(_IQ15mpy(_IQfrac(DutyCycle_Correct),_IQ(256)) );
   //DutyCycle_Fra = _IQfrac(DutyCycle_Correct) >> 7; //这一句和上面一句是一样的意思。_IQfrac取得的值仍是IQ数（即实际小数左移了15位）

   if(DutyCycle_Int >= 190) EPwm1Regs.CMPA.half.CMPA = 190;   //HRPWM要求增减计数模式下要预留3个时钟周期的时钟裕度。这里设置占空比限制为0.05和0.95；而减计数模式下0.95占空比对应190,0.05占空比对应10
   else if(DutyCycle_Int <= 10) EPwm1Regs.CMPA.half.CMPA = 10;
   else EPwm1Regs.CMPA.half.CMPA = DutyCycle_Int;
   EPwm1Regs.CMPA.half.CMPAHR = DutyCycle_Fra << 8;

}
