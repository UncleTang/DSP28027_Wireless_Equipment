/********************* User_protect.C*******************
�ļ����ܣ�                      �������ѹ����
Ӧ�ó��ϣ�    Ӧ����500W ��β������ղ�DC-DC�˿��Ƴ���
���ߣ�
����ʱ�䣺
�޸�ʱ�䣺  ÿ���޸�Ҫ����ʱ��


*********************************************************/
#include "User_all_include.h"

/*
__interrupt void TZ_protect_isr()
{
	int i,j;
	for(i = 0; i < 1000; i++)
	{
		for(j = 0; j < 1000; j++);      //�ӳ�һ��ʱ��Żָ����
	}
    EPwm1Regs.TZCLR.bit.OST = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}
*/


/*void Comparator_DC_TZ_Protect_init()
{
	   EALLOW;                                                                        //�Ժ����Ҫ���Ƚ���ģ����Խ��ePWM��DCģ����и����ٵı���

	   EPwm1Regs.TZDCSEL.bit.DCAEVT1 = DCH_High_DCL_NotCare;   //����DCAEVT1�����¼���������DCA�ĸ߶�����Ϊ�ߵ�ƽ����Ͷ�������ʲô����
	   EPwm1Regs.TZSEL.bit.DCAEVT1 = 1;                        //ѡ��DCAEVT1��ΪTZ�Ĵ���Դ��ע��DCEVT1ֻ����ΪOSHT������DCEVT2ֻ����ΪCBC������
	   EPwm1Regs.TZCTL.bit.DCAEVT1 = TZ_FORCE_LO;              //����DCAEVT1�¼���ǿ������
	   EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;
	   //EPwm1Regs.TZEINT.bit.DCAEVT1 = 1;  //��ʵ�Ѿ�ѡ����DCAEVT1��ΪOSHT����Դ����ʹ����OST�жϣ�������Ҫʹ��DCAEVT�ж�

	   EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 8; //DCģ���DCA�߶�������COMP1OUT
	   EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL = 0; //DCģ���DCA�Ͷ�������TZ0
	   EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = 1; //�첽�������ֵ�������ʵʱ��Ҫ�󲻸ߣ����Կɿ���Ҫ��ߵĻ������ͬ�����£�
	   EPwm1Regs.DCACTL.bit.EVT1SRCSEL = 0; //�¼��������˲���ֱ��������˲��Ļ�����ʲô�մ��ĸ������ûϸ����

	   Comp1Regs.COMPCTL.bit.SYNCSEL = 0; //ѡ���Ƿ�ѽ����ʱ��ͬ������������ʱ��ͬ��������ePWM�����ͬ���أ������ePWM��GPIOģ�飬����ѡ��ͬ��
	   //Comp1Regs.COMPCTL.bit.QUALSEL = 0; //���ѡ����ͬ��ģʽ����Ч���������ٸ�ʱ�Ӳ�ͬ�����£�����Ϊ0�Ļ���һ��ʱ��ͬ������һ�Σ�����Ϊ1�Ļ�����ʱ�ӲŸ���һ��
	   Comp1Regs.COMPCTL.bit.COMPSOURCE = 0; //����ѡ��Comp1�ķ����������Դ����Ϊ0ѡ������ڲ�DAC���ɵĲο�ģ���źţ���Ϊ1�����ⲿ���š���ע��ͬ������˶����ⲿ��������ģ�
	   Comp1Regs.COMPCTL.bit.CMPINV = 0; //���������
	   Comp1Regs.COMPCTL.bit.COMPDACEN = 1; //ʹ�ܱȽ���
	   Comp1Regs.DACVAL.bit.DACVAL = 979; //10λ�ο���ѹ���ο���ѹ����Ϊ3.16V����Ӧ�����ѹ��ֵ95V
	   //���ﲻ��ѡ��������˵�Դ���ڲ��ο���ѹDACVAL������б�·���������������Ĭ����DACVAL��б�·��������ﻹû������

	   EDIS;
}*/

