/********************* Main_C*******************
文件功能：                        主函数文件
应用场合：    应用于500W 无尾厨电接收侧DC-DC端控制
作者：
建立时间：
修改时间：  每次修改要更新时间

*********************************************************/
#define TARGET_GLOBAL 1    //十分重要，一定要放在第一句，用于区分 头文件中的变量是定义还是声明。

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
	_iq epwm1_data_init;           //PWM比较值
//	Uint32 epwm1_data_int_init;   //PWM比较值 整数部分
//	Uint32 epwm1_data_fra_init;   //PWM比较值 小数部分
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

	/****************系统初始化开始*****************/
	//此部分一般无需修改
	InitSysCtrl();
	//把Flash中的程序拷贝到RAM运

	#if Flash_Open   //#if Flash_Open      Flash_Open 在变量头文件中定义
	//MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);   //MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
	memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);
	//#pragma CODE_SECTION(InitFlash, "ramfuncs"); //#pragma不能放在主函数中，要放在这个InitFlash函数的定义前
	InitFlash();
	#endif


	DINT;   //关掉所有中断（关全局即CPU中断）
	InitPieCtrl(); //外设至PIE
	IER = 0x0000;  //PIE至CPU的中断
	IFR = 0x0000;
	InitPieVectTable();
	/****************系统初始化结束*****************/



	/*************中断向量表初始化开始**************/
	EALLOW;  //去掉保护
	PieVectTable.EPWM1_INT 	=	&epwm1_isr;                          //PWM中断
	//PieVectTable.EPWM1_TZINT 	=	&TZ_protect_isr;                 //PWM的TZ中断（保护应答）
	PieVectTable.ADCINT1 	=	&Adcint1_isr;                        //CPU在ADC中断中读取采样数据
	PieVectTable.ADCINT2 	=	&Adcint2_isr;
    PieVectTable.SCIRXINTA  =   &sciaRxFifoIsr;
    PieVectTable.TINT0 = &cpu_timer0_isr;
	EDIS;    //重新保护
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;                        //关闭启动启用的EPWM模块时钟
	EDIS;
	/*************中断向量表初始化结束**************/


	//用户变量初始化，必须在PWM初始化之前
	Initial_User_variables();


	/*************DSP外设模块初始化开始**************/
	 MEP_status = SFO_INCOMPLETE;// Calling SFO() updates the HRMSTEP register with calibrated MEP_ScaleFactor. HRMSTEP must be populated with a scale factor value prior to enabling high resolution period control.
	 while(MEP_status == SFO_INCOMPLETE)  //
	 {
	    MEP_status = SFO();
		if(MEP_status == SFO_ERROR)
		{
			 ESTOP0;   // Stop here and handle error  // SFO function returns 2 if an error occurs & # of MEP
		}              // steps/coarse step exceeds maximum of 255.
	 }

	InitGpio(); //GPIO初始化，通用GPIO在此配置，功能GPIO在下面的外设模块初始化里配置
	InitEPwm(); //PWM模块基本设置
	Adc_basic_init();   //ADC模块基本设置
	scia_basic_init();  //串口基本设置：包括SCI对应的GPIO以及其他基本设置
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 60, 1000000);
	/***********************************************/


	/***HRPWM参数的初始设置，包括周期、占空比。（而HRPWM的配置在InitEPwm()中）***/
	//有SFO软件的话，HRPWM的参数初始设置实质只需把（占空比*周期所含时钟数）的整数部分放入CMPA，把（占空比*周期所含时钟数）的小数部分左移16位放入CMPAHR。但不要直接左移，两者最好都是用IQ计算得到
/*
	dc_dc2_duty_correct_init = _IQ(1) - _IQ(DC_DUTY_INIT);   //由于是增减计数模式，而且CAU时输出高电平，到CAD时输出低电平，所以写入CMP的值对应的是(1-占空比)的数
	MEP_status_count = MEP_status_count+1;
	epwm1_data_init =  _IQmpy(dc_dc2_duty_correct_init,_IQ(EPwm1Regs.TBPRD));  //（占空比*周期所含时钟数）的整数部分的IQ15值（即左移了15位的）
	epwm1_data_int_init =  _IQint(epwm1_data_init);   //写入寄存器的话要把IQ15值还原为原来的整数，这里_IQint在GLOBAL_Q为15下是对应右移15位，此时还原为整数后，小数部分就会忽略掉了
	epwm1_data_fra_init =  _IQint(  _IQmpy(_IQfrac(epwm1_data_init),_IQ(256)) );  //_IQfrac()可以提取出IQ数原数值（含小数）的小数部分的IQ值。这里把小数部分IQ值提取出来后再左移8位，然后再取int即右移15位，所以得到的结果是原来的占空比所含时钟数的小数部分实际数值左移了8位
	EPwm1Regs.CMPA.half.CMPA   = epwm1_data_int_init;
	EPwm1Regs.CMPA.half.CMPAHR = epwm1_data_fra_init<<8;   //由于CMPAHR是高8位有效的，所以epwm1_data_fra还要左移8位才能写入CMPAHR。
*/
	dc_dc2_duty_init = _IQ(DC_DUTY_INIT);   //改用增计数模式
	MEP_status_count = MEP_status_count+1;
	epwm1_data_init =  _IQmpy(dc_dc2_duty_init,_IQ(EPwm1Regs.TBPRD));  //（占空比*周期所含时钟数）的整数部分的IQ15值（即左移了15位的）
	epwm1_data_int_init =  _IQint(epwm1_data_init);   //写入寄存器的话要把IQ15值还原为原来的整数，这里_IQint在GLOBAL_Q为15下是对应右移15位，此时还原为整数后，小数部分就会忽略掉了
	epwm1_data_fra_init =  _IQint(  _IQmpy(_IQfrac(epwm1_data_init),_IQ(256)) );  //_IQfrac()可以提取出IQ数原数值（含小数）的小数部分的IQ值。这里把小数部分IQ值提取出来后再左移8位，然后再取int即右移15位，所以得到的结果是原来的占空比所含时钟数的小数部分实际数值左移了8位
	EPwm1Regs.CMPA.half.CMPA   = epwm1_data_int_init;
	EPwm1Regs.CMPA.half.CMPAHR = epwm1_data_fra_init<<8;   //由于CMPAHR是高8位有效的，所以epwm1_data_fra还要左移8位才能写入CMPAHR。
	/*************DSP外设模块初始化结束**************/
	/***********************************************/



	/********外设中断允许与外设模块时钟开启***********/
    IER |= M_INT3; //这里的IER应该就是Interrupt Enable Register，是配置14组PIE连到CPU之间的使能；每一组对应该寄存器上的一位，前面已经把IER初始化为0，这里用或的形式使能第3组PIE。（ePWM1的中断由第三组PIE管理）
    //IER |= M_INT2; //使能第二组PIE（EPWM1_TZINT和ADCINT2由第二组中断管理）
    IER |= M_INT1; //使能第一组PIE（ADCINT1和ADCINT2由第一组中断管理）
    IER |= M_INT9; //SCIA FIFORX interrupt
    IER |= M_INT1; //timer0 interrupt
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;     //启动启用的EPWM模块时钟  。如果该时钟不使能，点debug后还自动运行（还没等用户点运行键就运行了），还不能在线读写数据
	EDIS;

	PieCtrlRegs.PIEIER3.bit.INTx1 = 0;          //这里是配置从PIE组到外设之间的中断使能，ePWM1中断是对应第3组PIE的第一个
	//PieCtrlRegs.PIEIER2.bit.INTx1 = 0;          //EPWM1_TZINT中断是对应第2组PIE的第一个
	PieCtrlRegs.PIEIER1.bit.INTx1 = 0;          //ADCINT1中断是对应第1组PIE的第一个
	PieCtrlRegs.PIEIER1.bit.INTx2 = 0;          //ADCINT2中断是对应第1组PIE的第二个
    PieCtrlRegs.PIEIER9.bit.INTx1 = 1;          //PIE RXFIFO
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1; //PIE timer0 interrupt
	/***********************************************/
	/*************用户程序初始化执行开始*************/


	/*************用户程序初始化执行结束**************/

	EINT;   // Enable Global interrupt INTM  //开全局中断，即CPU层的中断（对应上面的DINT关全局中断）
    ERTM;   // Enable Global realtime interrupt DBGM  //使能调试事件，对应把DGBM清0。如果禁止调事件，或DGBM置位，将会导致仿真器无法在实时状态下访问内存、寄存器；
            //而且来自主处理器和硬件断点的停止请求被忽略（意思是无法单步调试？）

    StartCpuTimer0();
/*************************************************/
	for(;;)
	{
		/************HRPWM更新************/
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
			   GpioDataRegs.GPASET.bit.GPIO5 = 1;			//Boost 开关管驱动
		   }
		   else
		   {
			   GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;			//Boost 开关管驱动关
		   }*/

	}
}


__interrupt void cpu_timer0_isr(void) //可以做一些对时间要求不严格的任务
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
// Set interrupt priority:设置中断嵌套。正常的程序设置来讲，进入中断服务函数之后，CPU会关掉全局中断使能，所以高优先级的中断打断不了低优先级别的中断。但是C2000也是支持中断嵌套的，也就是你所需要的高优先级别的中断能够打断低优先级别的中断。
	                                   //比如当CPU在执行EPWM1的中断服务函数时，可以被ADCINT1中断来打断，实现中断嵌套（PIE组号越小优先级越高，PIE组下的外设也是排号越小优先级越高，一般PIE优先级就是合适的，无需自定义优先级）。这就需要下面的设置了
//	volatile Uint16 TempPIEIER = PieCtrlRegs.PIEIER3.all;  //先是把原来的第三组PIE中断使能情况保存起来

	////////////////end////////////
//	IER |= M_INT3;                  //
//	IER	&= MINT3;					// Set "global" priority   上面两句表示，优先级大于第3组中断级别的中断使能，小于第3组中断级别的中断不使能

//	PieCtrlRegs.PIEIER3.all &= MG31;	// Set "group"  priority
//	PieCtrlRegs.PIEACK.all = 0xFFFF;	// Enable PIE interrupts  上面两句表示优先级大于第3组中第1个中断的中断使能，否则不使能。（PieCtrlRegs.PIEACK.all = 0xFFFF表示应答了所有中断了，CPU可以再响应中断，从而可以跳到别的中断函数中）
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
//   PieCtrlRegs.PIEIER3.all = TempPIEIER;   //还原该寄存器，确保不会屏蔽之后的中断。
//###########################################################
	PWM_INT1_Count++;
	//EPwm1Regs.ETFLG.bit.INT = 1;
	EPwm1Regs.ETCLR.bit.INT = 1;
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;    //ADCINT1和ADCINT2都是属于第一组PIE
    return;
}


