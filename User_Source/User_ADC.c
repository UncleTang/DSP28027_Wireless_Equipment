/********************* User_ADhandle.C*******************
�ļ����ܣ�                        ���ڴ����AD�ڲ���������
Ӧ�ó��ϣ�    Ӧ����500W ��β������ղ�DC-DC�˲���
���ߣ�
����ʱ�䣺
�޸�ʱ�䣺  ÿ���޸�Ҫ����ʱ��

����1: AD_read()
����1���ܣ������������
����1���������AD����Ĵ�����ֵ��12λ��
                          ������·����ϵ���� IQ15��

����1���������ʵ�ʵ�ֱ�������ѹ��       _IQ15
                 ʵ�ʵ�ֱ�������ѹ��_IQ15
                 ʵ�ʵĵ�е��� _IQ15
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
	//�ϵ硢��λ��ʹ�ܡ�У׼
	InitAdc();//���������ʱ�Ƿ�Ҫ���ϣ�
	//AdcOffsetSelfCal(); //Ҳ���������ƫ��ѡ�񣬷������������Ƿ��ж�
	//ADC�ж����ã�EOC��ת�������������ʹ��ADCINT1��ADCINT2��·�жϣ�ADCINT1��EOC2����ADCINT2��EOC5���󣻽�ֹ������Ӧ�ж�
	EALLOW;
	AdcRegs.ADCCTL1.bit.INTPULSEPOS	= 1;	//ADCINT1 trips after AdcResults latch������ת�����������EOC�źţ�EOC�ź��ǲ���ADC�ж��źŵ�����
	AdcRegs.INTSEL1N2.bit.INT1E     = 1;	//Enabled ADCINT1
	AdcRegs.INTSEL1N2.bit.INT2E     = 1;    //Enabled ADCINT2
	AdcRegs.INTSEL1N2.bit.INT1CONT  = 1;	//Disable ADCINT1 Continuous mode  ��ֹ������Ӧ��Ҳ����˵���λ��0ʱ����Ӧ��ADC�жϱ�־λ����֮ǰ����������µ�ADCINT�ж�����
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


	//SOCͨ������
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
	//SOC����Դ����
	AdcRegs.ADCSOC0CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//EPWM1ASOCA����
	AdcRegs.ADCSOC1CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//
	AdcRegs.ADCSOC2CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//
	AdcRegs.ADCSOC3CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;  //
	AdcRegs.ADCSOC4CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//
	AdcRegs.ADCSOC5CTL.bit.TRIGSEL 	= 5; //EPWM1ASOCA_Trigger;	//
	AdcRegs.ADCSOC6CTL.bit.TRIGSEL 	= 6; //EPWM1ASOCB_Trigger;	//EPWM1ASOCB����
	AdcRegs.ADCSOC7CTL.bit.TRIGSEL 	= 6; //EPWM1ASOCB_Trigger;  //
	AdcRegs.ADCSOC8CTL.bit.TRIGSEL 	= 6; //EPWM1ASOCB_Trigger;	//
	AdcRegs.ADCSOC9CTL.bit.TRIGSEL 	= 6; //EPWM1ASOCB_Trigger;	//
	AdcRegs.ADCSOC10CTL.bit.TRIGSEL = 6; //EPWM1ASOCB_Trigger;	//
	AdcRegs.ADCSOC11CTL.bit.TRIGSEL = 6; //EPWM1ASOCB_Trigger;  //
	//SOC����������
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
	//SOC���ȼ�����
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
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;     //һ���ж�������������裬һ�����������㼶���жϱ�־λ���ڶ�����PIE��Ӧ��Ӧ�𣬱�ʾCPU�Ѿ�����������ж��ˣ�������Ӧ��ġ�����ʲô�������Ӧ�����Զ���ɵ�
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
