/********************* Main_C*******************
�ļ����ܣ�                        �������ļ�
Ӧ�ó��ϣ�    Ӧ����500W ��β������ղ�DC-DC�˿���
���ߣ�
����ʱ�䣺
�޸�ʱ�䣺  ÿ���޸�Ҫ����ʱ��

*********************************************************/
#define TARGET_GLOBAL 1    //ʮ����Ҫ��һ��Ҫ���ڵ�һ�䣬�������� ͷ�ļ��еı����Ƕ��廹��������

#include "User_all_include.h"

interrupt void epwm1_isr(void);
//interrupt void TZ_protect_isr(void);
interrupt void Adcint1_isr(void);
interrupt void Adcint2_isr(void);
__interrupt void cpu_timer0_isr(void);
//_iq dc_dc2_duty;
	_iq dc_dc2_duty_init;
	//_iq dc_dc2_duty_correct_init;
	//_iq modulate_duty;
	//_iq modulate_duty_correct;
	_iq epwm1_data_init;           //PWM�Ƚ�ֵ
//	Uint32 epwm1_data_int_init;   //PWM�Ƚ�ֵ ��������
//	Uint32 epwm1_data_fra_init;   //PWM�Ƚ�ֵ С������
	//Uint32 epwm2_data;
    //int SW_TBPRD;
	//_iq15 SW_TBPRD_IQ15;
	Uint16 MEP_status;
	//Uint32 MEP_status_count = 0;
	//Uint32 MEP_ScaleFactor;
	//Uint32 ePWM;
Uint32 test;
void main(void)
{

	/****************ϵͳ��ʼ����ʼ*****************/
	//�˲���һ�������޸�
	InitSysCtrl();
	//��Flash�еĳ��򿽱���RAM��

	#if Flash_Open   //#if Flash_Open      Flash_Open �ڱ���ͷ�ļ��ж���
	//MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);   //MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
	//#pragma CODE_SECTION(InitFlash, "ramfuncs"); //#pragma���ܷ����������У�Ҫ�������InitFlash�����Ķ���ǰ
	InitFlash();
	#endif


	DINT;   //�ص������жϣ���ȫ�ּ�CPU�жϣ�
	InitPieCtrl(); //������PIE
	IER = 0x0000;  //PIE��CPU���ж�
	IFR = 0x0000;
	InitPieVectTable();
	/****************ϵͳ��ʼ������*****************/



	/*************�ж��������ʼ����ʼ**************/
	EALLOW;  //ȥ������
	PieVectTable.EPWM1_INT 	=	&epwm1_isr;                          //PWM�ж�
	//PieVectTable.EPWM1_TZINT 	=	&TZ_protect_isr;                 //PWM��TZ�жϣ�����Ӧ��
	PieVectTable.ADCINT1 	=	&Adcint1_isr;                        //CPU��ADC�ж��ж�ȡ��������
	PieVectTable.ADCINT2 	=	&Adcint2_isr;
    PieVectTable.SCIRXINTA  =   &sciaRxFifoIsr;
    PieVectTable.TINT0 = &cpu_timer0_isr;
	EDIS;    //���±���
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;                        //�ر��������õ�EPWMģ��ʱ��
	EDIS;
	/*************�ж��������ʼ������**************/


	//�û�������ʼ����������PWM��ʼ��֮ǰ
	Initial_User_variables();


	/*************DSP����ģ���ʼ����ʼ**************/
	 MEP_status = SFO_INCOMPLETE;// Calling SFO() updates the HRMSTEP register with calibrated MEP_ScaleFactor. HRMSTEP must be populated with a scale factor value prior to enabling high resolution period control.
	 while(MEP_status == SFO_INCOMPLETE)  //
	 {
	    MEP_status = SFO();
		if(MEP_status == SFO_ERROR)
		{
			 ESTOP0;   // Stop here and handle error  // SFO function returns 2 if an error occurs & # of MEP
		}              // steps/coarse step exceeds maximum of 255.
	 }

	InitGpio(); //GPIO��ʼ����ͨ��GPIO�ڴ����ã�����GPIO�����������ģ���ʼ��������
	InitEPwm(); //PWMģ���������
	Adc_basic_init();   //ADCģ���������
	scia_basic_init();  //���ڻ������ã�����SCI��Ӧ��GPIO�Լ�������������
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 60, 1000000);
	/***********************************************/


	/***HRPWM�����ĳ�ʼ���ã��������ڡ�ռ�ձȡ�����HRPWM��������InitEPwm()�У�***/
	//��SFO����Ļ���HRPWM�Ĳ�����ʼ����ʵ��ֻ��ѣ�ռ�ձ�*��������ʱ���������������ַ���CMPA���ѣ�ռ�ձ�*��������ʱ��������С����������16λ����CMPAHR������Ҫֱ�����ƣ�������ö�����IQ����õ�
/*
	dc_dc2_duty_correct_init = _IQ(1) - _IQ(DC_DUTY_INIT);   //��������������ģʽ������CAUʱ����ߵ�ƽ����CADʱ����͵�ƽ������д��CMP��ֵ��Ӧ����(1-ռ�ձ�)����
	MEP_status_count = MEP_status_count+1;
	epwm1_data_init =  _IQmpy(dc_dc2_duty_correct_init,_IQ(EPwm1Regs.TBPRD));  //��ռ�ձ�*��������ʱ���������������ֵ�IQ15ֵ����������15λ�ģ�
	epwm1_data_int_init =  _IQint(epwm1_data_init);   //д��Ĵ����Ļ�Ҫ��IQ15ֵ��ԭΪԭ��������������_IQint��GLOBAL_QΪ15���Ƕ�Ӧ����15λ����ʱ��ԭΪ������С�����־ͻ���Ե���
	epwm1_data_fra_init =  _IQint(  _IQmpy(_IQfrac(epwm1_data_init),_IQ(256)) );  //_IQfrac()������ȡ��IQ��ԭ��ֵ����С������С�����ֵ�IQֵ�������С������IQֵ��ȡ������������8λ��Ȼ����ȡint������15λ�����Եõ��Ľ����ԭ����ռ�ձ�����ʱ������С������ʵ����ֵ������8λ
	EPwm1Regs.CMPA.half.CMPA   = epwm1_data_int_init;
	EPwm1Regs.CMPA.half.CMPAHR = epwm1_data_fra_init<<8;   //����CMPAHR�Ǹ�8λ��Ч�ģ�����epwm1_data_fra��Ҫ����8λ����д��CMPAHR��
*/
	dc_dc2_duty_init = _IQ(DC_DUTY_INIT);   //����������ģʽ
	MEP_status_count = MEP_status_count+1;
	epwm1_data_init =  _IQmpy(dc_dc2_duty_init,_IQ(EPwm1Regs.TBPRD));  //��ռ�ձ�*��������ʱ���������������ֵ�IQ15ֵ����������15λ�ģ�
	epwm1_data_int_init =  _IQint(epwm1_data_init);   //д��Ĵ����Ļ�Ҫ��IQ15ֵ��ԭΪԭ��������������_IQint��GLOBAL_QΪ15���Ƕ�Ӧ����15λ����ʱ��ԭΪ������С�����־ͻ���Ե���
	epwm1_data_fra_init =  _IQint(  _IQmpy(_IQfrac(epwm1_data_init),_IQ(256)) );  //_IQfrac()������ȡ��IQ��ԭ��ֵ����С������С�����ֵ�IQֵ�������С������IQֵ��ȡ������������8λ��Ȼ����ȡint������15λ�����Եõ��Ľ����ԭ����ռ�ձ�����ʱ������С������ʵ����ֵ������8λ
	EPwm1Regs.CMPA.half.CMPA   = epwm1_data_int_init;
	EPwm1Regs.CMPA.half.CMPAHR = epwm1_data_fra_init<<8;   //����CMPAHR�Ǹ�8λ��Ч�ģ�����epwm1_data_fra��Ҫ����8λ����д��CMPAHR��
	/*************DSP����ģ���ʼ������**************/
	/***********************************************/



	/********�����ж�����������ģ��ʱ�ӿ���***********/
    IER |= M_INT3; //�����IERӦ�þ���Interrupt Enable Register��������14��PIE����CPU֮���ʹ�ܣ�ÿһ���Ӧ�üĴ����ϵ�һλ��ǰ���Ѿ���IER��ʼ��Ϊ0�������û����ʽʹ�ܵ�3��PIE����ePWM1���ж��ɵ�����PIE����
    //IER |= M_INT2; //ʹ�ܵڶ���PIE��EPWM1_TZINT��ADCINT2�ɵڶ����жϹ���
    IER |= M_INT1; //ʹ�ܵ�һ��PIE��ADCINT1��ADCINT2�ɵ�һ���жϹ���
    IER |= M_INT9; //SCIA FIFORX interrupt
    IER |= M_INT1; //timer0 interrupt
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;     //�������õ�EPWMģ��ʱ��  �������ʱ�Ӳ�ʹ�ܣ���debug���Զ����У���û���û������м��������ˣ������������߶�д����
	EDIS;

	PieCtrlRegs.PIEIER3.bit.INTx1 = 0;          //���������ô�PIE�鵽����֮����ж�ʹ�ܣ�ePWM1�ж��Ƕ�Ӧ��3��PIE�ĵ�һ��
	//PieCtrlRegs.PIEIER2.bit.INTx1 = 0;          //EPWM1_TZINT�ж��Ƕ�Ӧ��2��PIE�ĵ�һ��
	PieCtrlRegs.PIEIER1.bit.INTx1 = 0;          //ADCINT1�ж��Ƕ�Ӧ��1��PIE�ĵ�һ��
	PieCtrlRegs.PIEIER1.bit.INTx2 = 0;          //ADCINT2�ж��Ƕ�Ӧ��1��PIE�ĵڶ���
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;          //PIE RXFIFO
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; //PIE timer0 interrupt
	/***********************************************/
	/*************�û������ʼ��ִ�п�ʼ*************/


	/*************�û������ʼ��ִ�н���**************/

	EINT;   // Enable Global interrupt INTM  //��ȫ���жϣ���CPU����жϣ���Ӧ�����DINT��ȫ���жϣ�
    ERTM;   // Enable Global realtime interrupt DBGM  //ʹ�ܵ����¼�����Ӧ��DGBM��0�������ֹ���¼�����DGBM��λ�����ᵼ�·������޷���ʵʱ״̬�·����ڴ桢�Ĵ�����
            //������������������Ӳ���ϵ��ֹͣ���󱻺��ԣ���˼���޷��������ԣ���

    StartCpuTimer0();
/*************************************************/
	for(;;)
	{
		/************HRPWM����************/
		if(MEP_status_count >=330000000) //
			{
				MEP_status_count = 0;
				MEP_status = SFO(); // in background, MEP calibration module continuously updates MEP_ScaleFactor
				if (MEP_status == SFO_ERROR)
				{
					ESTOP0; // SFO function returns 2 if an error occurs & # of MEP steps/coarse step
				}
			}
		/*******************************/


		/*if(Drive_on_or_off == 1)
		   {
			   GpioDataRegs.GPASET.bit.GPIO5 = 1;			//Boost ���ع�����
		   }
		   else
		   {
			   GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;			//Boost ���ع�������
		   }*/

	}
}


__interrupt void cpu_timer0_isr(void) //������һЩ��ʱ��Ҫ���ϸ������
{
    CpuTimer0.InterruptCount++;
    send_data_to_pc(2000, send_voltage_output);
    send_data_to_pc(3000, send_current_output);
    CpuTimer0Regs.TCR.bit.TIF = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

#pragma CODE_SECTION(epwm1_isr, "ramfuncs");
interrupt void epwm1_isr(void)
{
//###########################################################
// Set interrupt priority:�����ж�Ƕ�ס������ĳ������������������жϷ�����֮��CPU��ص�ȫ���ж�ʹ�ܣ����Ը����ȼ����жϴ�ϲ��˵����ȼ�����жϡ�����C2000Ҳ��֧���ж�Ƕ�׵ģ�Ҳ����������Ҫ�ĸ����ȼ�����ж��ܹ���ϵ����ȼ�����жϡ�
	                                   //���統CPU��ִ��EPWM1���жϷ�����ʱ�����Ա�ADCINT1�ж�����ϣ�ʵ���ж�Ƕ�ף�PIE���ԽС���ȼ�Խ�ߣ�PIE���µ�����Ҳ���ź�ԽС���ȼ�Խ�ߣ�һ��PIE���ȼ����Ǻ��ʵģ������Զ������ȼ����������Ҫ�����������
//	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;  //���ǰ�ԭ���ĵ�����PIE�ж�ʹ�������������

	////////////////end////////////
//	IER |= M_INT3;                  //
//	IER	&= MINT3;					// Set "global" priority   ���������ʾ�����ȼ����ڵ�3���жϼ�����ж�ʹ�ܣ�С�ڵ�3���жϼ�����жϲ�ʹ��

//	PieCtrlRegs.PIEIER3.all &= MG31;	// Set "group"  priority
//	PieCtrlRegs.PIEACK.all = 0xFFFF;	// Enable PIE interrupts  ���������ʾ���ȼ����ڵ�3���е�1���жϵ��ж�ʹ�ܣ�����ʹ�ܡ���PieCtrlRegs.PIEACK.all = 0xFFFF��ʾӦ���������ж��ˣ�CPU��������Ӧ�жϣ��Ӷ�������������жϺ����У�
//	EINT;
//###########################################################//

//   User_PID();

/*	dc_dc2_duty_correct = _IQ(1) - _IQ(DC_DUTY_INIT);
	MEP_status_count = MEP_status_count+1;

	epwm1_data =  _IQmpy(dc_dc2_duty_correct,_IQ(EPwm1Regs.TBPRD));
	epwm1_data_int =  _IQint(epwm1_data);
	epwm1_data_fra =  _IQint(  _IQmpy(_IQfrac(epwm1_data),_IQ(256)) );

	EPwm1Regs.CMPA.half.CMPA   = epwm1_data_int;
	EPwm1Regs.CMPA.half.CMPAHR = epwm1_data_fra<<8;*/

//###########################################################//
// Restore registers saved:
//   PWM_INT1_Count	 += 1;
//   DINT;
//   PieCtrlRegs.PIEIER3.all = TempPIEIER;   //��ԭ�üĴ�����ȷ����������֮����жϡ�
//###########################################################
	PWM_INT1_Count++;
	//EPwm1Regs.ETFLG.bit.INT = 1;
	EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;    //ADCINT1��ADCINT2�������ڵ�һ��PIE
    return;
}


