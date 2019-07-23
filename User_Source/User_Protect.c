/********************* User_protect.C*******************
文件功能：                      过流与过压保护
应用场合：    应用于500W 无尾厨电接收侧DC-DC端控制程序
作者：
建立时间：
修改时间：  每次修改要更新时间


*********************************************************/
#include "User_all_include.h"

/*
__interrupt void TZ_protect_isr()
{
	int i,j;
	for(i = 0; i < 1000; i++)
	{
		for(j = 0; j < 1000; j++);      //延迟一段时间才恢复输出
	}
    EPwm1Regs.TZCLR.bit.OST = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;
}
*/


/*void Comparator_DC_TZ_Protect_init()
{
	   EALLOW;                                                                        //以后如果要到比较器模块可以结合ePWM的DC模块进行更快速的保护

	   EPwm1Regs.TZDCSEL.bit.DCAEVT1 = DCH_High_DCL_NotCare;   //产生DCAEVT1触发事件的条件：DCA的高端输入为高电平，其低端输入是什么不管
	   EPwm1Regs.TZSEL.bit.DCAEVT1 = 1;                        //选择DCAEVT1作为TZ的触发源（注意DCEVT1只能作为OSHT触发，DCEVT2只能作为CBC触发）
	   EPwm1Regs.TZCTL.bit.DCAEVT1 = TZ_FORCE_LO;              //发生DCAEVT1事件后强制拉低
	   EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO;
	   //EPwm1Regs.TZEINT.bit.DCAEVT1 = 1;  //其实已经选择了DCAEVT1作为OSHT触发源，且使能了OST中断，则不再需要使能DCAEVT中断

	   EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = 8; //DC模块的DCA高端输入是COMP1OUT
	   EPwm1Regs.DCTRIPSEL.bit.DCALCOMPSEL = 0; //DC模块的DCA低端输入是TZ0
	   EPwm1Regs.DCACTL.bit.EVT2FRCSYNCSEL = 1; //异步更新输出值（如果对实时性要求不高，但对可靠性要求高的话最好是同步更新）
	   EPwm1Regs.DCACTL.bit.EVT1SRCSEL = 0; //事件不经过滤波，直接输出（滤波的话还有什么空窗的概念，这里没细看）

	   Comp1Regs.COMPCTL.bit.SYNCSEL = 0; //选择是否把结果与时钟同步（这里是与时钟同步还是与ePWM的输出同步呢）输出到ePWM或GPIO模块，这里选择不同步
	   //Comp1Regs.COMPCTL.bit.QUALSEL = 0; //这个选择了同步模式才有效，经历多少个时钟才同步更新，设置为0的话则一个时钟同步更新一次，设置为1的话两个时钟才更新一次
	   Comp1Regs.COMPCTL.bit.COMPSOURCE = 0; //这里选择Comp1的反相输入端来源，设为0选择的是内部DAC生成的参考模拟信号，设为1则是外部引脚。（注意同相输入端都是外部引脚输入的）
	   Comp1Regs.COMPCTL.bit.CMPINV = 0; //输出不反相
	   Comp1Regs.COMPCTL.bit.COMPDACEN = 1; //使能比较器
	   Comp1Regs.DACVAL.bit.DACVAL = 979; //10位参考电压，参考电压设置为3.16V，对应输入电压限值95V
	   //这里不能选择反相输入端的源是内部参考电压DACVAL还是由斜坡发生器产生，估计默认是DACVAL，斜坡发生器那里还没搞明白

	   EDIS;
}*/

