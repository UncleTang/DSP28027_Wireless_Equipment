// TI File $Revision: /main/3 $
// Checkin $Date: September 23, 2009   15:34:12 $
//###########################################################################
//
// FILE:   DSP2802x_EPwm.c
//
// TITLE:  DSP2802x EPwm Initialization & Support Functions.
//
//###########################################################################
// $TI Release: 2802x C/C++ Header Files and Peripheral Examples V1.29 $
// $Release Date: January 11, 2011 $
//###########################################################################

#include "User_all_include.h"

//---------------------------------------------------------------------------
// InitEPwm:
//---------------------------------------------------------------------------
// This function initializes the EPwm(s) to a known state.
//
void InitEPwm(void)
{
   // Initialize EPwm1/2/3/4
	 InitEPwm1Gpio();
	 InitEPwm2Gpio();
	 //InitEPwm3Gpio();
	 InitEPwm1();
	 InitEPwm2();
	 InitEPwm3();
   //tbd...

}

//---------------------------------------------------------------------------
// Example: InitEPwmGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as EPwm pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitEPwmGpio(void)
{
   InitEPwm1Gpio();
   InitEPwm2Gpio();
   InitEPwm3Gpio();
#if DSP28_EPWM4
  // InitEPwm4Gpio();
#endif // endif DSP28_EPWM4
}

void InitEPwm1Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO0 = 1;    // Disable pull-up on GPIO0 (EPWM1A)
    GpioCtrlRegs.GPAPUD.bit.GPIO1 = 1;    // Disable pull-up on GPIO1 (EPWM1B)

/* Configure EPwm-1 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM1 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;   // Configure GPIO0 as EPWM1A
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;   // Configure GPIO1 as EPWM1B

    EDIS;
}

void InitEPwm2Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO2 = 1;    // Disable pull-up on GPIO2 (EPWM2A)
    GpioCtrlRegs.GPAPUD.bit.GPIO3 = 1;    // Disable pull-up on GPIO3 (EPWM2B)

/* Configure EPwm-2 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM2 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;   // Configure GPIO2 as EPWM2A
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;   // Configure GPIO3 as EPWM2B

    EDIS;
}

void InitEPwm3Gpio(void)
{
   EALLOW;

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO4 = 1;    // Disable pull-up on GPIO4 (EPWM3A)
    GpioCtrlRegs.GPAPUD.bit.GPIO5 = 1;    // Disable pull-up on GPIO5 (EPWM3B)

/* Configure EPwm-3 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM3 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;   // Configure GPIO4 as EPWM3A
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;   // Configure GPIO5 as EPWM3B

    EDIS;
}

#if DSP28_EPWM4
void InitEPwm4Gpio(void)
{
   EALLOW;
/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWM4A)
    GpioCtrlRegs.GPAPUD.bit.GPIO7 = 1;    // Disable pull-up on GPIO7 (EPWM4B)

/* Configure EPWM-4 pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPWM4 functional pins.
// Comment out other unwanted lines.

    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;   // Configure GPIO6 as EPWM4A
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;   // Configure GPIO7 as EPWM4B

    EDIS;
}
#endif // endif DSP28_EPWM4

void InitEPwm1(void)
{
	   //int SW_TBPRD = (int)(30000/SWITCH_FREQUENCY);  //���������£�300kHz�Ļ���������100
	   int SW_TBPRD = (int)(60000/SWITCH_FREQUENCY); //������ģʽ��

	   EPwm1Regs.TBPRD =  SW_TBPRD - 1;            // 3125 Set timer period period=(62.5/0.01)/2    ��������ģʽ����EPwm1Regs.TBPRD =  SW_TBPRD;
	   EPwm1Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
	   EPwm1Regs.TBCTR = 0x0000;                      // Clear counter

	   // Set Compare values
	   EPwm1Regs.CMPA.half.CMPA = 10;     // Set compare A value   ��ʼ�趨��CMPAӦ�ò���ֱ���ã������Ӧ��ռ�ձ���ʮ�ִ�ģ������ʼ���󣬲�������ʹ��TBCLKSYNC��Ҫ�ȵ���������HRPWM�����������ʹ��
	   // Setup counter mode
	   EPwm1Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP; // Count up DOWN   ��������������TB_COUNT_UPDOWN
	   EPwm1Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
	   EPwm1Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;    //CTR=zeroʱ���ͬ���źţ�EPWM2ͬ����
	   EPwm1Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT   100e6/(1*1)=0.01us
	   EPwm1Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	   // Setup shadowing (CC)
	   EPwm1Regs.CMPCTL.bit.SHDWAMODE =CC_SHADOW;
	   EPwm1Regs.CMPCTL.bit.SHDWBMODE =CC_SHADOW;
	   EPwm1Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
	   EPwm1Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;


	   // Set actions ��AQ��
	   //��������һ���Ƚ��¼���CAMPA��CAMPB����������Ϊ EPWM1A��EPWM1B�Ĵ���Դ��
	   //���Գ����п��Կ���ֻ��һ����CAMPA������������ʡȥװ�������Ƚ�ֵ����ֻҪװ��һ���Ϳ����ˡ�
	   //EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;             // Set PWM1A on event A, down count  ԭ����������ģʽ�£���EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;
	   //EPwm1Regs.AQCTLA.bit.CAU = AQ_SET;           // Clear PWM1A on event A, up count   ԭ����������ģʽ�£���EPwm1Regs.AQCTLA.bit.CAD = AQ_CLEAR;

	   EPwm1Regs.AQCTLA.bit.ZRO = AQ_SET;
	   EPwm1Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	   //EPwm1Regs.AQCTLB.bit.CAD = AQ_CLEAR;           // Set PWM1B on event A, down count
	   //EPwm1Regs.AQCTLB.bit.CAU = AQ_SET;             //



	   ////PWM����AD
	   EPwm1Regs.ETSEL.bit.SOCBEN=1;
	   EPwm1Regs.ETSEL.bit.SOCBSEL = 0x02; //TBΪPRDʱ����
	   EPwm1Regs.ETPS.bit.SOCBPRD = 0x01;
	   EPwm1Regs.ETSEL.bit.SOCAEN=1;
	   EPwm1Regs.ETSEL.bit.SOCASEL = 0x04; //TBΪCAUʱ����
	   EPwm1Regs.ETPS.bit.SOCAPRD = 0x01;


	//Setup TZ
	//�����ڻ������������ٿ����������ϵ���̿��������·��������������EPWM�����

/*	   EALLOW;
	   EPwm1Regs.TZSEL.bit.OSHT5 =1;                   //����TZ5Ϊ���δ�����һ��ʱ�Ӷ�ʧ��������ePWM1�������һֱά���趨�Ķ�����ֱ���ֶ������������TZ���жϺ��������
	   EPwm1Regs.TZSEL.bit.OSHT6 =1;                   //����TZ5Ϊ���δ�����һ��ʱ�Ӷ�ʧ��������ePWM1�������һֱά���趨�Ķ�����ֱ���ֶ������������TZ���жϺ��������
	   EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO;          //TZ�¼���ָTZ1-TZ6����һ�����趨�õ��¼�������ʱ��PWM����͵�ƽ����IGBT���
	   EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;          //PWM����͵�ƽ����IGBT���
	   EPwm1Regs.TZEINT.bit.OST = 1;                   //ʹ��OST�ж�
	   EDIS;jyw*/

	   //Comparator_DC_TZ_Protect_init();               //ͨ���Ƚ�����DCģ�顢TZģ�����õı������Ƴ�ʼ����������Ժ��и�COMP������������

	   // Interrupt where we will change the Compare Values
	   EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;       // Select INT on zero event
	 //  EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
	   EPwm1Regs.ETSEL.bit.INTEN = 1;                  // Enable INT,���輶�ж�����
	   EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;             // Generate INT on 1rd event


	   // ��ʼ���ø߾���PWM
	   EALLOW;
	   EPwm1Regs.HRCNFG.all = 0X0;   //clear all bits first
	   EPwm1Regs.HRCNFG.bit.EDGMODE = HR_FEP;      //MEP�������½���
	   EPwm1Regs.HRCNFG.bit.CTLMODE = HR_CMP;
	   //EPwm1Regs.HRPCTL.bit.HRPE = 0; //�����ֹ�߾������ڵ����ã�������˵��ֹ���ض�λ��TBPRDHR���ưɣ��������ϵ縴λĬ�ϵģ�Ӧ��Ҳ����д
	   EPwm1Regs.HRCNFG.bit.HRLOAD  = HR_CTR_ZERO;
	   EDIS;
}

void InitEPwm2(void)
{      int SW_TBPRD = (int)(30000/SWITCH_FREQUENCY);
	   EPwm2Regs.TBPRD =  SW_TBPRD;            // 3125 Set timer period period=(62.5/0.01)/2
	   EPwm2Regs.TBPHS.half.TBPHS = 0x0000;           // Phase is 0
	   EPwm2Regs.TBCTR = 0x0000;                      // Clear counter

	   // Set Compare values
	   EPwm2Regs.CMPA.half.CMPA = 1000;     // Set compare A value
	   EPwm2Regs.CMPB = 1500;
	   // Setup counter mode
	   EPwm2Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up DOWN
	   EPwm2Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
	   EPwm2Regs.TBCTL.bit.SYNCOSEL = TB_CTR_ZERO;    //CTR=zeroʱ���ͬ���źţ�EPWM2ͬ����
	   EPwm2Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT   100e6/(1*1)=0.01us
	   EPwm2Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	   // Setup shadowing (CC)
	   EPwm2Regs.CMPCTL.bit.SHDWAMODE =CC_SHADOW;
	   EPwm2Regs.CMPCTL.bit.SHDWBMODE =CC_SHADOW;
	   EPwm2Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
	   EPwm2Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;


	   // Set actions ��AQ��
	   //��������һ���Ƚ��¼���CAMPA��CAMPB����������Ϊ EPWM1A��EPWM1B�Ĵ���Դ��
	   //���Գ����п��Կ���ֻ��һ����CAMPA������������ʡȥװ�������Ƚ�ֵ����ֻҪװ��һ���Ϳ����ˡ�
	  EPwm2Regs.AQCTLA.bit.CAD = AQ_CLEAR;             // Set PWM1A on event A, down count
	  EPwm2Regs.AQCTLA.bit.CAU = AQ_SET;           // Clear PWM1A on event A, up count

	 //  EPwm2Regs.AQCTLB.bit.CAD = AQ_CLEAR;           // Set PWM1B on event A, down count
	 // EPwm2Regs.AQCTLB.bit.CAU = AQ_SET;



	   ////PWM����AD
//	   EPwm2Regs.ETSEL.bit.SOCBEN=1;
//	   EPwm2Regs.ETSEL.bit.SOCBSEL = 0x02; //TBΪPRDʱ����
//	   EPwm2Regs.ETPS.bit.SOCBPRD = 0x01;


	//Setup TZ
	//�����ڻ������������ٿ����������ϵ���̿��������·��������������EPWM�����

//	   EALLOW;
//	   EPwm2Regs.TZSEL.bit.CBC5 =0;                    //��ֹ��TZ5������TZ�жϣ����������������������
//	   EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO;          //PWM����͵�ƽ����IGBT���
//	   EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO;          //PWM����͵�ƽ����IGBT���
	  // EPwm1Regs.TZEINT.bit.CBC = 0;                   //����TZ-CBC�ж�
//	   EDIS;/*jyw*/

	   // Interrupt where we will change the Compare Values
//	   EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_ZERO;       // Select INT on zero event
	 //  EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;
//	   EPwm2Regs.ETSEL.bit.INTEN = 1;                  // Enable INT,���輶�ж�����
//	   EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;             // Generate INT on 1rd event
}

void InitEPwm3(void)
{
	   //ADC�ɵ�е�������ePWM3������Ƶ���ǿ������ڵ�10��������һ���������ڿ��Բ�10����е���������ƽ��
	   int SW_TBPRD_3 = (int)(6000/SWITCH_FREQUENCY); //������ģʽ��

	   EPwm3Regs.TBPRD =  SW_TBPRD_3 - 1;
	   EPwm3Regs.TBPHS.half.TBPHS = 0x0000;
	   EPwm3Regs.TBCTR = 0x0000;

	   // Set Compare values
	   EPwm3Regs.CMPA.half.CMPA = 10;                 //0.5����ռ�ձȣ������׼�Ļ����ⲻ��
	   // Setup counter mode
	   EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UP;     //
	   EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;        //
	   EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       //
	   EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV1;

	   // Setup shadowing (CC)
	   EPwm3Regs.CMPCTL.bit.SHDWAMODE =CC_SHADOW;
	   EPwm3Regs.CMPCTL.bit.SHDWBMODE =CC_SHADOW;
	   EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;  // Load on Zero
	   EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

	   EPwm3Regs.AQCTLA.bit.ZRO = AQ_SET;
	   EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;

	   ////PWM����AD
	   //EPwm3Regs.ETSEL.bit.SOCBEN=1;
	   //EPwm3Regs.ETSEL.bit.SOCBSEL = 0x02; //TBΪPRDʱ����
	   //EPwm3Regs.ETPS.bit.SOCBPRD = 0x01;
	   EPwm3Regs.ETSEL.bit.SOCAEN=1;
	   EPwm3Regs.ETSEL.bit.SOCASEL = 0x04; //TBΪCAUʱ����
	   EPwm3Regs.ETPS.bit.SOCAPRD = 0x01;
}


//---------------------------------------------------------------------------
// Example: InitEPwmSyncGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as EPwm Synch pins
//

void InitEPwmSyncGpio(void)
{

//   EALLOW;

/* Configure EPWMSYNCI  */

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;    // Enable pull-up on GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;// Enable pull-up on GPIO32 (EPWMSYNCI)

/* Set qualification for selected pins to asynch only */
// This will select synch to SYSCLKOUT for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO6 = 0;   // Synch to SYSCLKOUT GPIO6 (EPWMSYNCI)
// GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 0;  // Synch to SYSCLKOUT GPIO32 (EPWMSYNCI)

/* Configure EPwmSync pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be EPwmSync functional pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 2;    // Configures GPIO6 for EPWMSYNCI operation
// GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 2;   // Configures GPIO32 for EPWMSYNCI operation.

/* Configure EPWMSYNC0  */

/* Disable internal pull-up for the selected output pins
   for reduced power consumption */
// Pull-ups can be enabled or disabled by the user.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 1;    // Disable pull-up on GPIO6 (EPWMSYNCO)
// GpioCtrlRegs.GPBPUD.bit.GPIO33 = 1;    // Disable pull-up on GPIO33 (EPWMSYNCO)

   GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 3;    // Configures GPIO6 for EPWMSYNCO
// GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 2;   // Configures GPIO33 for EPWMSYNCO

}

//---------------------------------------------------------------------------
// Example: InitTzGpio:
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as Trip Zone (TZ) pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.
//

void InitTzGpio(void)
{
   EALLOW;

/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled by the user.
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAPUD.bit.GPIO12 = 0;    // Enable pull-up on GPIO12 (TZ1)
   GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;    // Enable pull-up on GPIO16 (TZ2)
// GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;    // Enable pull-up on GPIO28 (TZ2)
   GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;    // Enable pull-up on GPIO17 (TZ3)
// GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;    // Enable pull-up on GPIO29 (TZ3)

/* Set qualification for selected pins to asynch only */
// Inputs are synchronized to SYSCLKOUT by default.
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

   GpioCtrlRegs.GPAQSEL1.bit.GPIO12 = 3;  // Asynch input GPIO12 (TZ1)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;  // Asynch input GPIO16 (TZ2)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;  // Asynch input GPIO28 (TZ2)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;  // Asynch input GPIO17 (TZ3)
// GpioCtrlRegs.GPAQSEL2.bit.GPIO29 = 3;  // Asynch input GPIO29 (TZ3)


/* Configure TZ pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be TZ functional pins.
// Comment out other unwanted lines.
   GpioCtrlRegs.GPAMUX1.bit.GPIO12 = 1;  // Configure GPIO12 as TZ1
   GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 3;  // Configure GPIO16 as TZ2
// GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // Configure GPIO28 as TZ2
   GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 3;  // Configure GPIO17 as TZ3
// GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // Configure GPIO29 as TZ3

   EDIS;

}

//===========================================================================
// End of file.
//===========================================================================
