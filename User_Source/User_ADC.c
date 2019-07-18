/********************* User_ADhandle.C*******************
文件功能：                        用于处理从AD口采样的数据
应用场合：    应用于500W 无尾厨电接收侧DC-DC端采样
作者：
建立时间：
修改时间：  每次修改要更新时间

函数1: AD_read()
函数1功能：处理采样数据
函数1输入参数：AD结果寄存器的值：12位；
                          采样电路增益系数： IQ15；

函数1输出参数：实际的直流输入电压；       _IQ15
                 实际的直流输出电压；_IQ15
                 实际的电感电流 _IQ15
*********************************************************/
#include "User_all_include.h"

//#define Channel_ADCINA0 0
//#define Channel_ADCINA1 1
//#define Channel_ADCINA2 2
//#define Channel_ADCINA3 3
//#define EPWM1ASOCA_Trigger 5
//#define EPWM1ASOCB_Trigger 6

void Adc_basic_init()
{
	//上电、复位、使能、校准
	InitAdc();//这里面的延时是否要加上？
	//AdcOffsetSelfCal(); //也不能用这个偏置选择，否则又他妈进入非法中断
	//ADC中断设置：EOC在转换结束后产生；使能ADCINT1和ADCINT2两路中断，ADCINT1由EOC2请求，ADCINT2由EOC5请求；禁止连续响应中断
	EALLOW;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;	//ADCINT1 trips after AdcResults latch，允许转换结束后产生EOC信号，EOC信号是产生ADC中断信号的脉冲
	AdcRegs.INTSEL1N2.bit.INT1E     = 1;	//Enabled ADCINT1
	AdcRegs.INTSEL1N2.bit.INT2E     = 1;    //Enabled ADCINT2
	AdcRegs.INTSEL1N2.bit.INT1CONT  = 1;	//Disable ADCINT1 Continuous mode  禁止连续响应，也就是说这个位设0时，相应的ADC中断标志位清零之前，不会产生新的ADCINT中断脉冲
	AdcRegs.INTSEL1N2.bit.INT2CONT  = 0;
	AdcRegs.INTSEL1N2.bit.INT1SEL	= 2;	//
	AdcRegs.INTSEL1N2.bit.INT2SEL	= 5;

/*    	for (j=0;j<12;j++)
	    {
	      if (j <= 2) (*ADCConfigure[j]).bit.CHSEL = 0;
	      else if ( (j >= 3) && (j <= 5) ) (*ADCConfigure[j]).bit.CHSEL = 1;
	      else if ( (j >= 6) && (j <= 8) ) (*ADCConfigure[j]).bit.CHSEL = 2;
	      else if ( (j >= 9) && (j <= 11) ) (*ADCConfigure[j]).bit.CHSEL = 3;

	      if ( (j >= 0) && (j <= 5) ) (*ADCConfigure[j]).bit.TRIGSEL = 5;
	      else if ( (j >= 6) && (j <= 11) ) (*ADCConfigure[j]).bit.TRIGSEL = 6;

	      (*ADCConfigure[j]).bit.ACQPS = 6;
	    }*/


	//SOC通道配置
	AdcRegs.ADCSOC0CTL.bit.CHSEL 	= 0; //Channel_ADCINA0;	//
	AdcRegs.ADCSOC1CTL.bit.CHSEL 	= 0; //Channel_ADCINA0;	//
	AdcRegs.ADCSOC2CTL.bit.CHSEL 	= 0; //Channel_ADCINA0;	//
	AdcRegs.ADCSOC3CTL.bit.CHSEL 	= 1; //Channel_ADCINA1; //
	AdcRegs.ADCSOC4CTL.bit.CHSEL 	= 1; //Channel_ADCINA1;	//
	AdcRegs.ADCSOC5CTL.bit.CHSEL 	= 1; //Channel_ADCINA1;	//
	AdcRegs.ADCSOC6CTL.bit.CHSEL 	= 2; //Channel_ADCINA2;	//
	AdcRegs.ADCSOC7CTL.bit.CHSEL 	= 2; //Channel_ADCINA2;  //
	AdcRegs.ADCSOC8CTL.bit.CHSEL 	= 2; //Channel_ADCINA2;	//
	AdcRegs.ADCSOC9CTL.bit.CHSEL 	= 3; //Channel_ADCINA3;	//
	AdcRegs.ADCSOC10CTL.bit.CHSEL 	= 3; //Channel_ADCINA3;	//
	AdcRegs.ADCSOC11CTL.bit.CHSEL 	= 3; //Channel_ADCINA3;  //
	//SOC触发源设置
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//EPWM1ASOCA触发
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//
	AdcRegs.ADCSOC3CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;  //
	AdcRegs.ADCSOC4CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//
	AdcRegs.ADCSOC5CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//
	AdcRegs.ADCSOC6CTL.bit.TRIGSEL 	= 6; //EPWM1ASOCB_Trigger;	//EPWM1ASOCB触发
	AdcRegs.ADCSOC7CTL.bit.TRIGSEL 	= 6; //EPWM1ASOCB_Trigger;  //
	AdcRegs.ADCSOC8CTL.bit.TRIGSEL 	= 6; //EPWM1ASOCB_Trigger;	//
	AdcRegs.ADCSOC9CTL.bit.TRIGSEL 	= 6; //EPWM1ASOCB_Trigger;	//
	AdcRegs.ADCSOC10CTL.bit.TRIGSEL = 6; //EPWM1ASOCB_Trigger;	//
	AdcRegs.ADCSOC11CTL.bit.TRIGSEL = 6; //EPWM1ASOCB_Trigger;  //
	//SOC采样窗设置
	AdcRegs.ADCSOC0CTL.bit.ACQPS 	= 6;	//
	AdcRegs.ADCSOC1CTL.bit.ACQPS 	= 6;	//
	AdcRegs.ADCSOC2CTL.bit.ACQPS 	= 6;	//
	AdcRegs.ADCSOC3CTL.bit.ACQPS 	= 6;    //
	AdcRegs.ADCSOC4CTL.bit.ACQPS 	= 6;	//
	AdcRegs.ADCSOC5CTL.bit.ACQPS 	= 6;	//
	AdcRegs.ADCSOC6CTL.bit.ACQPS 	= 6;	//
	AdcRegs.ADCSOC7CTL.bit.ACQPS 	= 6;    //
	AdcRegs.ADCSOC8CTL.bit.ACQPS 	= 6;	//
	AdcRegs.ADCSOC9CTL.bit.ACQPS 	= 6;	//
	AdcRegs.ADCSOC10CTL.bit.ACQPS 	= 6;	//
	AdcRegs.ADCSOC11CTL.bit.ACQPS 	= 6;    //
	//SOC优先级设置
	AdcRegs.SOCPRICTL.bit.SOCPRIORITY = 9;
    EDIS;
}


#pragma CODE_SECTION(Adcint1_isr, "ramfuncs");
__interrupt void Adcint1_isr()
{
	   /*typedef struct
	   {
		Uint16 Record_0;
		Uint16 Record_1;
		Uint16 Record_2;
		Uint16 Record[3];
		Uint16 Median;
		Uint16 Minimum;
		Uint16 Maximum;
		Uint16 Average;
	   }ADC_Sample;
	ADC_Sample Vo_test;
	ADC_Sample IL_test;*/

	IL_test.Record_0 = AdcResult.ADCRESULT0;
	IL_test.Record_1 = AdcResult.ADCRESULT1;
	IL_test.Record_2 = AdcResult.ADCRESULT2;
	Vo_test.Record_0 = AdcResult.ADCRESULT3;
	Vo_test.Record_1 = AdcResult.ADCRESULT4;
	Vo_test.Record_2 = AdcResult.ADCRESULT5;
	//User_min_middle_max_1(IL_test.Record_0, IL_test.Record_1, IL_test.Record_2);
	IL_test.Median = ADC_Medium(IL_test.Record_0, IL_test.Record_1, IL_test.Record_2);
	Vo_test.Median = ADC_Medium(Vo_test.Record_0, Vo_test.Record_1, Vo_test.Record_2);
	IL = IL_test.Median;
	Vo = Vo_test.Median;
	AdcRegs.ADCINTFLGCLR.bit.ADCINT1 = 1;		//Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     //一般中断最后有两个步骤，一个是清除外设层级的中断标志位，第二个是PIE相应组应答，表示CPU已经处理完这个中断了，可以响应别的。其他什么清除工作应该是自动完成的
}

#pragma CODE_SECTION(Adcint2_isr, "ramfuncs");
__interrupt void Adcint2_isr()
{
	/*typedef struct
	   {
		Uint16 Record_0;
		Uint16 Record_1;
		Uint16 Record_2;
		Uint16 Record[3];
		Uint16 Median;
		Uint16 Minimum;
		Uint16 Maximum;
		Uint16 Average;
	   }ADC_Sample;
	ADC_Sample Vi_test;
	ADC_Sample Temperature_test;*/

	Vi_test.Record_0 = AdcResult.ADCRESULT6;
	Vi_test.Record_1 = AdcResult.ADCRESULT7;
	Vi_test.Record_2 = AdcResult.ADCRESULT8;
	Temperature_test.Record_0 = AdcResult.ADCRESULT9;
	Temperature_test.Record_1 = AdcResult.ADCRESULT10;
	Temperature_test.Record_2 = AdcResult.ADCRESULT11;
	//User_min_middle_max_2();
	Vi_test.Median = ADC_Medium(Vi_test.Record_0, Vi_test.Record_1, Vi_test.Record_2);
	Vi = Vi_test.Median;
	//Temperature = Temperature_test.Median;

	AdcRegs.ADCINTFLGCLR.bit.ADCINT2 = 1;		//Clear ADCINT1 flag reinitialize for next SOC
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}



/*#pragma CODE_SECTION(User_AD_Read, "ramfuncs");
void User_AD_Read()
{

}*/
