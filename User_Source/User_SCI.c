/*
 * User_SCI.c
 *
 *  Created on: 2019��7��11��
 *      Author: Jialin Luo
 */

#include "User_all_include.h"


/*****************************************************************************����ģ��������ú���******************************************************/
void scia_basic_init()
{   InitSciGpio();
 	SciaRegs.SCICCR.all =0x0007;       //һ��ֹͣλ����ֹ��żУ�飬��ֹRX��TX�ڲ�������������ģʽ����Ч����λ8λ
	SciaRegs.SCICTL1.all =0x0003;      //��ֹ���մ����жϣ���ֹ˯��ģʽ��ʹ��SCI��������ʹ��SCI������
	SciaRegs.SCICTL2.all =0x0003;      //ʹ��RX/BK�жϣ�������ʹ����FIFOģʽ���ʸ��ж���Ч����ʹ��TX�жϣ�������ʹ����FIFOģʽ���ʸ��ж���Ч��
    SciaRegs.SCIHBAUD    =0x0000;
    SciaRegs.SCILBAUD    =0x000F;      //������115200
    SciaRegs.SCICTL1.all =0x0023;      //SciaRegs.SCICTL1.bit.SWRESET =1;   // ��λ��־λ
    SciaRegs.SCIFFTX.all=0xE040;  //����ʹ��SCI_FIFO���ͺͽ��գ�ʹ��SCI_FIFO��ǿ���ܣ����»ָ�����FIFO�Ĳ��������FIFO�����жϱ�־����ֹ����TXFHVLƥ���TX_FIFO�жϣ�TXFFIL����0��ƥ��
    SciaRegs.SCIFFRX.all=0x2044;  //������RXFFOVF�����־λ�����»ָ����� FIFO �Ĳ��������FIFO�����жϱ�־����ֹ����RXFHVLƥ���RX_FIFO�жϣ�RXFFIL����4��ƥ��
    SciaRegs.SCIFFCT.all=0x0;     //�����Զ������ʵļ�⣬����Ҫ
}
/******************************************************************************************************************************************************/


/******************************************************************************�û��������պ���*********************************************************/
void receive_parameter()
{   char *msg1;
	Uint16 ParameterH; //Parameter�ĸ�8λ
    Uint16 ParameterL; //Parameter�ĵ�8λ
    msg1 = "\r\n\n\nSelect a Parameter(kp, ki, vo, il or vi)\0";
	scia_send_Char_one_by_one(msg1);
	while(SciaRegs.SCIFFRX.bit.RXFFST != 2) {}  // ����ȵ�RX��FIFO�ѷ��͵���֡���ݶ����յ��˲�ȥ����
	ParameterH = SciaRegs.SCIRXBUF.all;   //��ȡ�û������ַ�����kp��ki��vo �� io���ĸ�8λ
	ParameterL = SciaRegs.SCIRXBUF.all;   //��ȡ�û������ַ�����kp��ki��vo �� io���ĵ�8λ
    while(SciaRegs.SCIFFRX.bit.RXFFST != 0) {}      //�ȴ�SCI�������
    Parameter=(((ParameterH<<8) & 0xFF00) | ParameterL) & 0xFFFF;   //�Ѹߵ�8λ������ϣ���ԭ�����ַ�����Ӧ��ֵ
}
/***************************************************************************************************************************************************/


/******************************************************************************�û��޸Ĳ�������******************************************************/
void PC_modify_kp_or_ki()
{    char *msg4;
	 char ReceivedChar[4]; //����һ���ַ����������Լ�¼�û�����Ĳ�����ֵ�ַ�
	 Uint16 PC_Input_Value;
	 _iq PC_Input_Value_IQ;
	 int j = 0;  //�м�����������ַ�������ĵ�jλ
	 int dot = 4;
	 msg4 = "\r\n\n\nInput value(.000-.999 or 0.00-99.9 or 0000-9999)\0";
	 scia_send_Char_one_by_one(msg4); //��ʾ�û���������޸ĵ���ֵ
     while(SciaRegs.SCIFFRX.bit.RXFFST !=4) {} // �ȴ�RX��FIFO���յ��Է��͵Ĳ����޸�ֵ���ĸ��ַ���
	 while(j < 4)
	 {
		  ReceivedChar[j] = SciaRegs.SCIRXBUF.all; //�ѽ��յ����ĸ��ַ���һ�ŵ���������ַ���������
		  if(ReceivedChar[j] == 46) dot = j;       //�ж�С��������λ
		  j++;
	 }
     while(SciaRegs.SCIFFRX.bit.RXFFST != 0) {}  //�ȴ�RX_FIFO��ȡ��ϲŽ�����һ��

     if ( (dot != 0) &&(dot != 1) && (dot != 2) )
     {
    	 PC_Input_Value = (ReceivedChar[0]-48)*1000 + (ReceivedChar[1]-48)*100 + (ReceivedChar[2]-48)*10 +(ReceivedChar[3]-48);  //���ַ������黹ԭ��ʵ����ֵ
         PC_Input_Value_IQ = _IQ15(PC_Input_Value);
     }
     else if (dot == 0) PC_Input_Value_IQ = _IQ15(0.1)*(ReceivedChar[1]-48) + _IQ15(0.01)*(ReceivedChar[2]-48) + _IQ15(0.001)*(ReceivedChar[3]-48);
     else if (dot == 1) PC_Input_Value_IQ = _IQ15(ReceivedChar[0]-48) + _IQ15(0.1)*(ReceivedChar[2]-48) + _IQ15(0.01)*(ReceivedChar[3]-48);
     else if (dot == 2) PC_Input_Value_IQ = _IQ15((ReceivedChar[0]-48)*10+(ReceivedChar[1]-48)) + _IQ15(0.1)*(ReceivedChar[3]-48);

     if (Parameter == 0x6B70) {kp_sci=PC_Input_Value; Kp = PC_Input_Value_IQ;}  //�����ж��޸ĵĲ�����kp����ki����value������Ӧ������
	 else if (Parameter == 0x6B69) {ki_sci=PC_Input_Value; Ki = PC_Input_Value_IQ;}
}
/*************************************************************************************************************************************************/


/**********************************************************************������·��ͺ���************************************************************/
void PC_update_vo_or_il_or_vi()
{
 char *msg2;
 char *msg3;
 char *msg5;
 msg2 = "\r\n\n\nVo update: \0";
 msg3 = "\r\n\n\nIL update: \0";
 msg5 = "\r\n\n\nVi update: \0";

/************************************************����Vo����*****************************************/
	if (Parameter == 0x766F)  //���û��������vo
	{
		char StrU[8];    //����һ���ַ��������飬���Դ��dsp�ɼ��������ѹ��Ϣ
		int j=0;         //�����м����j�������ַ�������ĵ�jλ
		Uint16 buff1 = 0;   //���建����������԰����ͱ�����ֵ�����ַ��ͱ�����������buff1ֻ�ܶ����Uint16��������int����int��32λ�������StrU������
		scia_send_Char_one_by_one(msg2);  //�����ʾ����ֵ�������ѹ

		Vo_test.actual_IQ = _IQ10div(_IQ10mpy(_IQ10(Vo),_IQ10(293.04)), _IQ10(4096));  //�õ�ԭ��ֵ��IQֵ
		Vo_test.actual_int = _IQ10int(Vo_test.actual_IQ);  //��ȡԭ��ֵ��������
		Vo_test.actual_fra_IQ = _IQ10frac(Vo_test.actual_IQ);  //��ȡԭ��ֵС�����ֶ�Ӧ��IQֵ
		Vo_test.actual_fra = ( (Vo_test.actual_fra_IQ)*1000L ) >> 10;  //��С������IQֵ��ԭΪС��������ֵ

		buff1 = Vo_test.actual_int;      //�Ѳɼ��ĵ�ѹֵ�����������buff1
		while(j < 3)     //�����ѭ�����ǰ����͵ĸ�λ�ϵ�����ת��Ϊ�ַ��ͣ�����������0xFFFF��65535��
		{                //��6��5��5��3��5�������ͨ������ȡ��ȡ��ķ�ʽ��ȡ������Ȼ����Ҫ��48���ܵõ��ַ������µ�6��5��5��3��5��
			StrU[j] = buff1 / pow(10,2-j)+48;
			buff1 = buff1 % pow(10,2-j);
			j++;
		}
		StrU[3]='.';  //���������Ͽ��ַ������ַ�������
		j = 4;
		buff1 = Vo_test.actual_fra;
		while(j < 7 )
		{
			StrU[j] = buff1 / pow(10,6-j)+48;
			buff1 = buff1 % pow(10,6-j);
			j++;
		}
		StrU[7]='\0';

		j = 0;   //�������м����Ϊ0��������λ����
		while(StrU[j] != '\0')  //����ַ����ͳ�ȥ��ֱ�����ַ���ֹͣѭ����Ȼ���˳���
		{
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //�ȴ�����FIFOΪ���ٷ�����һ���ַ�
			SciaRegs.SCITXBUF=StrU[j];
			j++;
		}
		while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
	}
/***************************************************************************************************************/

/****************************************************����IL����*************************************************/
	else if (Parameter == 0x696C)  //���û��������il
	{
		char StrI[8];      //����һ���ַ��������飬���Դ��dsp�ɼ��ĵ�����Ϣ
		int j=0;           //�����м����j�������ַ�������ĵ�jλ
		Uint16 buff1;     //���建����������԰����ͱ�����ֵ�����ַ��ͱ���
		scia_send_Char_one_by_one(msg3);    //�����ʾ����ֵ�ǵ���

		IL_test.actual_IQ = _IQ14div(_IQ14mpy(_IQ14(IL),_IQ14(16.5)), _IQ14(4096));
		IL_test.actual_int = _IQ14int(IL_test.actual_IQ);
		IL_test.actual_fra_IQ = _IQ14frac(IL_test.actual_IQ);
		IL_test.actual_fra = ( (IL_test.actual_fra_IQ)*1000L ) >> 14;

		buff1 = IL_test.actual_int;        //�Ѳɼ��ĵ���ֵ�����������buff1
		while(j <3 )       //�����ѭ�����ǰ����͵ĸ�λ�ϵ�����ת��Ϊ�ַ���
		{
		   	StrI[j] = buff1 / pow(10,2-j)+48;
		   	buff1 = buff1 % pow(10,2-j);
		   	j++;
		}
		StrI[3]='.';
		j = 4;
		buff1 = IL_test.actual_fra;
		while(j < 7 )
		{
			StrI[j] = buff1 / pow(10,6-j)+48;
			buff1 = buff1 % pow(10,6-j);
			j++;
		}
		StrI[7]='\0';

		j = 0;
		while(StrI[j] != '\0')  //����ַ����ͳ�ȥ��ֱ�����ַ���ֹͣѭ����Ȼ���˳���
		{
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //�ȴ�����FIFOΪ���ٷ�����һ���ַ�
			SciaRegs.SCITXBUF=StrI[j];
			j++;
		}
		while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}    //�ȴ��������ݷ���������˳�����
	}
/**************************************************************************************************************/

/**************************************************����Vi����**************************************************/
	else if (Parameter == 0x7669)  //���û��������vi
	{
		char StrVi[8];      //����һ���ַ��������飬���Դ��dsp�ɼ��������ѹ��Ϣ
		int j=0;           //�����м����j�������ַ�������ĵ�jλ
		Uint16 buff1;     //���建����������԰����ͱ�����ֵ�����ַ��ͱ���
		scia_send_Char_one_by_one(msg5);    //�����ʾ����ֵ�������ѹ

	    Vi_test.actual_IQ = _IQ12div(_IQ12mpy(_IQ12(Vi),_IQ12(99)), _IQ12(4096));
	    Vi_test.actual_int = _IQ12int(Vi_test.actual_IQ);
	    Vi_test.actual_fra_IQ = _IQ12frac(Vi_test.actual_IQ);
	    Vi_test.actual_fra = ( (Vi_test.actual_fra_IQ)*1000L ) >> 12;

		buff1 = Vi_test.actual_int;        //�Ѳɼ��ĵ���ֵ�����������buff1
		while(j < 3 )       //�����ѭ�����ǰ����͵ĸ�λ�ϵ�����ת��Ϊ�ַ���
		{
		   	StrVi[j] = buff1 / pow(10,2-j) + 48;
		   	buff1 = buff1 % pow(10,2-j);
		   	j++;
		}
		StrVi[3]='.';
		j = 4;
		buff1 = Vi_test.actual_fra;
		while(j < 7 )
		{
		    StrVi[j] = buff1 / pow(10,6-j)+48;
			buff1 = buff1 % pow(10,6-j);
			j++;
		}
		StrVi[7]='\0';

		j = 0;
		while(StrVi[j] != '\0')  //����ַ����ͳ�ȥ��ֱ�����ַ���ֹͣѭ����Ȼ���˳���
		{
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //�ȴ�����FIFOΪ���ٷ�����һ���ַ�
			SciaRegs.SCITXBUF=StrVi[j];
			j++;
		}
		while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}    //�ȴ��������ݷ���������˳�����
	}
/***************************************************************************************************************/

}
/*********************************************************************************************************************************************/


/******************************************************************�˷�����*******************************************************************/
int pow(int a, int b)
{
	int T=1;
	int i=0;
	while(i<b)
	{
		T=T*a;
		i=i+1;
	}
	return T;
}
/*******************************************************************************************************************************************/


/*******************************************************************��䷢�ͺ���*************************************************************/
void scia_send_Char_one_by_one(char *Str)
{
	int j = 0;     //�����м����j�������ַ����ĵ�jλ
	int a = 0;     //�����м����a��������ĵ�j���ַ�
	while(Str[j] != '\0')  //����ַ����ͳ�ȥ��ֱ���������һ���ַ���ֹͣѭ����Ȼ���˳����ַ���ָ�����ֱ�����������ַ���msg[i]
	{
	   a=Str[j];
	   while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //�ȴ�����FIFOΪ����ִ����һ��
	   SciaRegs.SCITXBUF=a;   //��Ҫ���͵Ķ����ŵ�SCITXBUF
	   j++;
	}
	while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}  //�ȴ��������ݷ���������˳�����
}
/******************************************************************************************************************************************/


