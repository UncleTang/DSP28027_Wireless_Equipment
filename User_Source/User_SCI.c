/*
 * User_SCI.c
 *
 *  Created on: 2019年7月11日
 *      Author: Jialin Luo
 */

#include "User_all_include.h"


/*****************************************************************************串口模块基本设置函数******************************************************/
void scia_basic_init()
{   InitSciGpio();
 	SciaRegs.SCICCR.all =0x0007;       //一个停止位，禁止奇偶校验，禁止RX与TX内部相连，空闲线模式，有效数据位8位
	SciaRegs.SCICTL1.all =0x0003;      //禁止接收错误中断，禁止睡眠模式，使能SCI发送器，使能SCI接收器
	SciaRegs.SCICTL2.all =0x0003;      //使能RX/BK中断（但下面使能了FIFO模式，故该中断无效），使能TX中断（但下面使能了FIFO模式，故该中断无效）
    SciaRegs.SCIHBAUD    =0x0000;
    SciaRegs.SCILBAUD    =0x000F;      //波特率115200
    SciaRegs.SCICTL1.all =0x0023;      //SciaRegs.SCICTL1.bit.SWRESET =1;   // 复位标志位
    SciaRegs.SCIFFTX.all=0xE040;  //继续使能SCI_FIFO发送和接收，使能SCI_FIFO增强功能，重新恢复发送FIFO的操作，清除FIFO发送中断标志，禁止基于TXFHVL匹配的TX_FIFO中断，TXFFIL配置0级匹配
    SciaRegs.SCIFFRX.all=0x2044;  //清除清除RXFFOVF溢出标志位，重新恢复接收 FIFO 的操作，清除FIFO接收中断标志，禁止基于RXFHVL匹配的RX_FIFO中断，RXFFIL配置4级匹配
    SciaRegs.SCIFFCT.all=0x0;     //关于自动波特率的检测，不需要
}
/******************************************************************************************************************************************************/


/******************************************************************************用户参数接收函数*********************************************************/
void receive_parameter()
{   char *msg1;
	Uint16 ParameterH; //Parameter的高8位
    Uint16 ParameterL; //Parameter的低8位
    msg1 = "\r\n\n\nSelect a Parameter(kp, ki, vo, il or vi)\0";
	scia_send_Char_one_by_one(msg1);
	while(SciaRegs.SCIFFRX.bit.RXFFST != 2) {}  // 这里等到RX的FIFO把发送的两帧数据都接收到了才去读。
	ParameterH = SciaRegs.SCIRXBUF.all;   //获取用户输入字符串（kp、ki、vo 或 io）的高8位
	ParameterL = SciaRegs.SCIRXBUF.all;   //获取用户输入字符串（kp、ki、vo 或 io）的低8位
    while(SciaRegs.SCIFFRX.bit.RXFFST != 0) {}      //等待SCI接收完毕
    Parameter=(((ParameterH<<8) & 0xFF00) | ParameterL) & 0xFFFF;   //把高低8位重新组合，还原参数字符串对应数值
}
/***************************************************************************************************************************************************/


/******************************************************************************用户修改参数函数******************************************************/
void PC_modify_kp_or_ki()
{    char *msg4;
	 char ReceivedChar[4]; //定义一个字符串数组用以记录用户输入的参数数值字符
	 Uint16 PC_Input_Value;
	 _iq PC_Input_Value_IQ;
	 int j = 0;  //中间变量，代表字符串数组的第j位
	 int dot = 4;
	 msg4 = "\r\n\n\nInput value(.000-.999 or 0.00-99.9 or 0000-9999)\0";
	 scia_send_Char_one_by_one(msg4); //提示用户输入参数修改的数值
     while(SciaRegs.SCIFFRX.bit.RXFFST !=4) {} // 等待RX的FIFO接收电脑发送的参数修改值（四个字符）
	 while(j < 4)
	 {
		  ReceivedChar[j] = SciaRegs.SCIRXBUF.all; //把接收到的四个字符逐一放到所定义的字符串数组中
		  if(ReceivedChar[j] == 46) dot = j;       //判断小数点在哪位
		  j++;
	 }
     while(SciaRegs.SCIFFRX.bit.RXFFST != 0) {}  //等待RX_FIFO读取完毕才进行下一步

     if ( (dot != 0) &&(dot != 1) && (dot != 2) )
     {
    	 PC_Input_Value = (ReceivedChar[0]-48)*1000 + (ReceivedChar[1]-48)*100 + (ReceivedChar[2]-48)*10 +(ReceivedChar[3]-48);  //把字符串数组还原成实际数值
         PC_Input_Value_IQ = _IQ15(PC_Input_Value);
     }
     else if (dot == 0) PC_Input_Value_IQ = _IQ15(0.1)*(ReceivedChar[1]-48) + _IQ15(0.01)*(ReceivedChar[2]-48) + _IQ15(0.001)*(ReceivedChar[3]-48);
     else if (dot == 1) PC_Input_Value_IQ = _IQ15(ReceivedChar[0]-48) + _IQ15(0.1)*(ReceivedChar[2]-48) + _IQ15(0.01)*(ReceivedChar[3]-48);
     else if (dot == 2) PC_Input_Value_IQ = _IQ15((ReceivedChar[0]-48)*10+(ReceivedChar[1]-48)) + _IQ15(0.1)*(ReceivedChar[3]-48);

     if (Parameter == 0x6B70) {kp_sci=PC_Input_Value; Kp = PC_Input_Value_IQ;}  //根据判断修改的参数是kp还是ki，把value赋给相应参数。
	 else if (Parameter == 0x6B69) {ki_sci=PC_Input_Value; Ki = PC_Input_Value_IQ;}
}
/*************************************************************************************************************************************************/


/**********************************************************************输出更新发送函数************************************************************/
void PC_update_vo_or_il_or_vi()
{
 char *msg2;
 char *msg3;
 char *msg5;
 msg2 = "\r\n\n\nVo update: \0";
 msg3 = "\r\n\n\nIL update: \0";
 msg5 = "\r\n\n\nVi update: \0";

/************************************************串口Vo更新*****************************************/
	if (Parameter == 0x766F)  //若用户请求的是vo
	{
		char StrU[8];    //定义一个字符串型数组，用以存放dsp采集的输出电压信息
		int j=0;         //定义中间变量j，代表字符串数组的第j位
		Uint16 buff1 = 0;   //定义缓冲变量，用以把整型变量的值赋给字符型变量，但这里buff1只能定义成Uint16，不能用int，因int是32位，与后面StrU不兼容
		scia_send_Char_one_by_one(msg2);  //语句提示更新值是输出电压

		Vo_test.actual_IQ = _IQ10div(_IQ10mpy(_IQ10(Vo),_IQ10(293.04)), _IQ10(4096));  //得到原数值的IQ值
		Vo_test.actual_int = _IQ10int(Vo_test.actual_IQ);  //提取原数值整数部分
		Vo_test.actual_fra_IQ = _IQ10frac(Vo_test.actual_IQ);  //提取原数值小数部分对应的IQ值
		Vo_test.actual_fra = ( (Vo_test.actual_fra_IQ)*1000L ) >> 10;  //把小数部分IQ值还原为小数部分数值

		buff1 = Vo_test.actual_int;      //把采集的电压值赋给缓冲变量buff1
		while(j < 3)     //下面的循环体是把整型的各位上的数据转换为字符型，如整型数据0xFFFF是65535。
		{                //把6、5、5、3、5五个数字通过除法取整取余的方式提取出来，然后需要加48才能得到字符定义下的6、5、5、3、5。
			StrU[j] = buff1 / pow(10,2-j)+48;
			buff1 = buff1 % pow(10,2-j);
			j++;
		}
		StrU[3]='.';  //后面必须加上空字符表明字符串结束
		j = 4;
		buff1 = Vo_test.actual_fra;
		while(j < 7 )
		{
			StrU[j] = buff1 / pow(10,6-j)+48;
			buff1 = buff1 % pow(10,6-j);
			j++;
		}
		StrU[7]='\0';

		j = 0;   //重新令中间变量为0，用以逐位发送
		while(StrU[j] != '\0')  //逐个字符发送出去，直到空字符就停止循环，然后退出。
		{
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //等待发送FIFO为空再发送下一个字符
			SciaRegs.SCITXBUF=StrU[j];
			j++;
		}
		while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}
	}
/***************************************************************************************************************/

/****************************************************串口IL更新*************************************************/
	else if (Parameter == 0x696C)  //若用户请求的是il
	{
		char StrI[8];      //定义一个字符串型数组，用以存放dsp采集的电流信息
		int j=0;           //定义中间变量j，代表字符串数组的第j位
		Uint16 buff1;     //定义缓冲变量，用以把整型变量的值赋给字符型变量
		scia_send_Char_one_by_one(msg3);    //语句提示更新值是电流

		IL_test.actual_IQ = _IQ14div(_IQ14mpy(_IQ14(IL),_IQ14(16.5)), _IQ14(4096));
		IL_test.actual_int = _IQ14int(IL_test.actual_IQ);
		IL_test.actual_fra_IQ = _IQ14frac(IL_test.actual_IQ);
		IL_test.actual_fra = ( (IL_test.actual_fra_IQ)*1000L ) >> 14;

		buff1 = IL_test.actual_int;        //把采集的电流值赋给缓冲变量buff1
		while(j <3 )       //下面的循环体是把整型的各位上的数据转换为字符型
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
		while(StrI[j] != '\0')  //逐个字符发送出去，直到空字符就停止循环，然后退出。
		{
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //等待发送FIFO为空再发送下一个字符
			SciaRegs.SCITXBUF=StrI[j];
			j++;
		}
		while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}    //等待所有数据发送完毕再退出函数
	}
/**************************************************************************************************************/

/**************************************************串口Vi更新**************************************************/
	else if (Parameter == 0x7669)  //若用户请求的是vi
	{
		char StrVi[8];      //定义一个字符串型数组，用以存放dsp采集的输入电压信息
		int j=0;           //定义中间变量j，代表字符串数组的第j位
		Uint16 buff1;     //定义缓冲变量，用以把整型变量的值赋给字符型变量
		scia_send_Char_one_by_one(msg5);    //语句提示更新值是输入电压

	    Vi_test.actual_IQ = _IQ12div(_IQ12mpy(_IQ12(Vi),_IQ12(99)), _IQ12(4096));
	    Vi_test.actual_int = _IQ12int(Vi_test.actual_IQ);
	    Vi_test.actual_fra_IQ = _IQ12frac(Vi_test.actual_IQ);
	    Vi_test.actual_fra = ( (Vi_test.actual_fra_IQ)*1000L ) >> 12;

		buff1 = Vi_test.actual_int;        //把采集的电流值赋给缓冲变量buff1
		while(j < 3 )       //下面的循环体是把整型的各位上的数据转换为字符型
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
		while(StrVi[j] != '\0')  //逐个字符发送出去，直到空字符就停止循环，然后退出。
		{
			while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //等待发送FIFO为空再发送下一个字符
			SciaRegs.SCITXBUF=StrVi[j];
			j++;
		}
		while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}    //等待所有数据发送完毕再退出函数
	}
/***************************************************************************************************************/

}
/*********************************************************************************************************************************************/


/******************************************************************乘方函数*******************************************************************/
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


/*******************************************************************语句发送函数*************************************************************/
void scia_send_Char_one_by_one(char *Str)
{
	int j = 0;     //定义中间变量j，代表字符串的第j位
	int a = 0;     //定义中间变量a，存放语句的第j个字符
	while(Str[j] != '\0')  //逐个字符发送出去，直到发送最后一个字符就停止循环，然后退出。字符型指针可以直接这样访问字符串msg[i]
	{
	   a=Str[j];
	   while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}   //等待发送FIFO为空再执行下一步
	   SciaRegs.SCITXBUF=a;   //把要发送的东西放到SCITXBUF
	   j++;
	}
	while (SciaRegs.SCIFFTX.bit.TXFFST != 0) {}  //等待所有数据发送完毕再退出函数
}
/******************************************************************************************************************************************/


