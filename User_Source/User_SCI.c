/*
 * User_SCI.c
 *
 *  Created on: 2019��7��11��
 *      Author: Jialin Luo
 */

#include "User_all_include.h"
char receive_buffer[16];

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

    SciaRegs.SCIFFRX.bit.RXFFIL = 1;
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;
    SciaRegs.SCIFFRX.bit.RXFFIENA = 1;
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
	 int j = 0;  //�м�����������ַ�������ĵ�jλ
	 msg4 = "\r\n\n\nInput value(0000-9999)\0";
	 scia_send_Char_one_by_one(msg4); //��ʾ�û���������޸ĵ���ֵ
     while(SciaRegs.SCIFFRX.bit.RXFFST !=4) {} // �ȴ�RX��FIFO���յ��Է��͵Ĳ����޸�ֵ���ĸ��ַ���
	 while(j < 4)
	 {
		  ReceivedChar[j] = SciaRegs.SCIRXBUF.all; //�ѽ��յ����ĸ��ַ���һ�ŵ���������ַ���������
		  j++;
	 }
     while(SciaRegs.SCIFFRX.bit.RXFFST != 0) {}  //�ȴ�RX_FIFO��ȡ��ϲŽ�����һ��
     PC_Input_Value=(ReceivedChar[0]-48)*1000 + (ReceivedChar[1]-48)*100 + (ReceivedChar[2]-48)*10 +(ReceivedChar[3]-48);  //���ַ������黹ԭ��ʵ����ֵ
	 if (Parameter == 0x6B70) {kp_sci=PC_Input_Value;}  //�����ж��޸ĵĲ�����kp����ki����value������Ӧ������
	 else if (Parameter == 0x6B69) {ki_sci=PC_Input_Value;}
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

    /********************************����Vo����******************************/
	if (Parameter == 0x766F)  //���û��������vo
	{
		char StrU[6];    //����һ���ַ��������飬���Դ��dsp�ɼ��������ѹ��Ϣ
		int j=0;         //�����м����j�������ַ�������ĵ�jλ
		Uint16 buff1 = 0;   //���建����������԰����ͱ�����ֵ�����ַ��ͱ�����������buff1ֻ�ܶ����Uint16��������int����int��32λ�������StrU������
		scia_send_Char_one_by_one(msg2);  //�����ʾ����ֵ�������ѹ
		buff1 = Vo;      //�Ѳɼ��ĵ�ѹֵ�����������buff1
		while(j <5 )     //�����ѭ�����ǰ����͵ĸ�λ�ϵ�����ת��Ϊ�ַ��ͣ�����������0xFFFF��65535��
		{                //��6��5��5��3��5�������ͨ������ȡ��ȡ��ķ�ʽ��ȡ������Ȼ����Ҫ��48���ܵõ��ַ������µ�6��5��5��3��5��
			StrU[j] = buff1 / pow(10,4-j)+48;
			buff1 = buff1 % pow(10,4-j);
			j++;
		}
		StrU[5]='\0';  //���������Ͽ��ַ������ַ�������
		j = 0;   //�������м����Ϊ0��������λ����
		while(StrU[j] != '\0')  //����ַ����ͳ�ȥ��ֱ�����ַ���ֹͣѭ����Ȼ���˳���
		{
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //�ȴ�����FIFOΪ���ٷ�����һ���ַ�
			SciaRegs.SCITXBUF=StrU[j];
			j++;
		}
		while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
	}
    /***********************************************************************/

	/********************************����IL����******************************/
	else if (Parameter == 0x696C)  //���û��������il
	{
		char StrI[6];      //����һ���ַ��������飬���Դ��dsp�ɼ��ĵ�����Ϣ
		int j=0;           //�����м����j�������ַ�������ĵ�jλ
		Uint16 buff1;     //���建����������԰����ͱ�����ֵ�����ַ��ͱ���
		scia_send_Char_one_by_one(msg3);    //�����ʾ����ֵ�ǵ���
		buff1 = IL;        //�Ѳɼ��ĵ���ֵ�����������buff1
		while(j <5 )       //�����ѭ�����ǰ����͵ĸ�λ�ϵ�����ת��Ϊ�ַ���
		{
		   	StrI[j] = buff1 / pow(10,4-j)+48;
		   	buff1 = buff1 % pow(10,4-j);
		   	j++;
		}
		StrI[5]='\0';
		j = 0;
		while(StrI[j] != '\0')  //����ַ����ͳ�ȥ��ֱ�����ַ���ֹͣѭ����Ȼ���˳���
		{
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //�ȴ�����FIFOΪ���ٷ�����һ���ַ�
			SciaRegs.SCITXBUF=StrI[j];
			j++;
		}
		while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}    //�ȴ��������ݷ���������˳�����
	}
	/***********************************************************************/

	/********************************����Vi����******************************/
	else if (Parameter == 0x7669)  //���û��������vi
	{
		char StrVi[6];      //����һ���ַ��������飬���Դ��dsp�ɼ��������ѹ��Ϣ
		int j=0;           //�����м����j�������ַ�������ĵ�jλ
		Uint16 buff1;     //���建����������԰����ͱ�����ֵ�����ַ��ͱ���
		scia_send_Char_one_by_one(msg5);    //�����ʾ����ֵ�������ѹ
		buff1 = Vi;        //�Ѳɼ��ĵ���ֵ�����������buff1
		while(j <5 )       //�����ѭ�����ǰ����͵ĸ�λ�ϵ�����ת��Ϊ�ַ���
		{
		   	StrVi[j] = buff1 / pow(10,4-j)+48;
		   	buff1 = buff1 % pow(10,4-j);
		   	j++;
		}
		StrVi[5]='\0';
		j = 0;
		while(StrVi[j] != '\0')  //����ַ����ͳ�ȥ��ֱ�����ַ���ֹͣѭ����Ȼ���˳���
		{
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //�ȴ�����FIFOΪ���ٷ�����һ���ַ�
			SciaRegs.SCITXBUF=StrVi[j];
			j++;
		}
		while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}    //�ȴ��������ݷ���������˳�����
	}
	/***********************************************************************/

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

__interrupt void sciaRxFifoIsr()
{
    static char i = 3;
    float temp = 0;

    if(i ==3)
    {
        receive_buffer[0] = receive_buffer[1];
        receive_buffer[1] = receive_buffer[2];
        receive_buffer[2] = receive_buffer[3];
    }
    *(receive_buffer + i) = SciaRegs.SCIRXBUF.all;
    if(receive_buffer[0] == 0x01 && receive_buffer[1] == 0x02 && receive_buffer[2] == 0x03 && receive_buffer[3] == 0x04)
    {
        i++;
    }
    if(i == 9)
    {
        switch(receive_buffer[4])
        {
        case 0x01:
            temp = ((receive_buffer[5] << 16) + (receive_buffer[6] << 8) + receive_buffer[7]) / 100.0;
            break;
        case 0x00:
            temp = -((receive_buffer[5] << 16) + (receive_buffer[6] << 8) + receive_buffer[7]) / 100.0;
            break;
        }
        switch(receive_buffer[8])
        {
        case 0x00:
        {
            if(kp_sci != temp)
                kp_sci = temp;
        }
        case 0x01:
        {
            if(ki_sci != temp)
                ki_sci = temp;
        }
//        case 0x02:
//            kp_sci = (float)(temp / 1000.0);
//        case 0x03:
//            kp_sci = (float)(temp / 1000.0);
          i = 3;
        }
    }
    //SciaRegs.SCIFFRX.bit.RXFIFORESET = 0;   //ָ�븴λ
    //SciaRegs.SCIFFRX.bit.RXFIFORESET = 1;
    SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;  // Clear SCI interrupt flag
    PieCtrlRegs.PIEACK.bit.ACK9 = 1;     //PIEӦ������
}

char SEND_BUF[9] = {0xc0, 0xfb, 0xe1, 0, 0, 0, 0, 0, 0xdd};
void send_data_to_pc(Uint16 num, char num_type) //������������PC�ٴ���
{
    int i;
    if(num < 0)
    {
        num = 0 - num;
        SEND_BUF[3] = 0x00;
    }
    else
    {
        SEND_BUF[3] = 0x01;
    }
    switch(num_type)
    {
    case 0x01:
        SEND_BUF[4] = 0x01;
        break;
    case 0x02:
        SEND_BUF[4] = 0x02;
        break;
    case 0x03:
        SEND_BUF[4] = 0x03;
        break;
    case 0x04:
        SEND_BUF[4] = 0x04;
        break;
    }
    SEND_BUF[5] = (char)(num >> 16);
    SEND_BUF[6] = (char)(num >> 8);
    SEND_BUF[7] = (char)(num %256);

    for(i = 0; i < 9; i++)
    {
        SciaRegs.SCITXBUF = SEND_BUF[i];
        while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
    }
}
