/********************* User_filter.C*******************
文件功能：                        用于对相关数据进行滤波
应用场合：    应用于500W 无尾厨电接收侧DC-DC端采样
作者：
建立时间：
修改时间：  每次修改要更新时间

函数1: User_min_middel_max()
函数1功能：处理采样数据
函数1输入参数：三个值

函数1输出参数：中间值
*********************************************************/
#include "User_all_include.h"

/***************************************提取中位数******************************/
#pragma CODE_SECTION(ADC_Medium, "ramfuncs");
Uint16 ADC_Medium(Uint16 a0, Uint16 a1, Uint16 a2)
{
	Uint16 Medium;
    if( ((a0 >= a1) && (a1 >= a2)) || ((a0 <= a1) && (a1 <= a2)) )
        Medium = a1;
    else if( ((a0 >= a2) && (a2 >= a1)) || ((a0 <= a2) && (a2 <= a1)) )
    	Medium = a2;
    else
    	Medium = a0;
	return Medium;
}
/*******************************************************************************/

/***************************************提取最大值******************************/
Uint16 ADC_Maximum(Uint16 a0, Uint16 a1, Uint16 a2)
{
	Uint16 Maximum;
    if( (a0 >= a1) && (a0 >= a2) )
        Maximum = a0;
    else if( (a1 >= a0) && (a1 >= a2) )
    	Maximum = a1;
    else
    	Maximum = a2;
	return Maximum;
}
/*******************************************************************************/

/***************************************提取最小值******************************/
Uint16 ADC_Minimum(Uint16 a0, Uint16 a1, Uint16 a2)
{
	Uint16 Minimum;
    if( (a0 <= a1) && (a0 <= a2) )
    	Minimum = a0;
    else if( (a1 <= a0) && (a1 <= a2) )
    	Minimum = a1;
    else
    	Minimum = a2;
	return Minimum;
}
/*******************************************************************************/


/*
void User_min_middle_max_1(Uint16 a1, Uint16 a2, Uint16 a3)
{
**************************************IL的ADC数据处理*****************************
	int i,j;
	//IL_test.Record_0 = AdcResult.ADCRESULT0;
	//IL_test.Record_1 = AdcResult.ADCRESULT1;
	//IL_test.Record_2 = AdcResult.ADCRESULT2;
	IL_test.Record[0] = IL_test.Record_0;
	IL_test.Record[1] = IL_test.Record_1;
	IL_test.Record[2] = IL_test.Record_2;
	********从小到大排列*********
    for(i=0;i<3;i++)
    {
	   for(j=i+1;j<3;j++)
	   {
		 if(IL_test.Record[j]<IL_test.Record[i])
		 {
		  unsigned int t;
		  t=IL_test.Record[i];
		  IL_test.Record[i]=IL_test.Record[j];
		  IL_test.Record[j]=t;
		  }
	    }
	 }
    ***************************
    IL_test.Minimum = IL_test.Record[0];
    IL_test.Median = IL_test.Record[1];
    IL_test.Maximum = IL_test.Record[2];
    IL_test.Average = (IL_test.Record[0] + IL_test.Record[1] + IL_test.Record[2] )/ 3;
**********************************************************************************

**************************************Vo的ADC数据处理*****************************
    Vo_test.Record_0 = AdcResult.ADCRESULT3;
    Vo_test.Record_1 = AdcResult.ADCRESULT4;
    Vo_test.Record_2 = AdcResult.ADCRESULT5;
    Vo_test.Record[0] = Vo_test.Record_0;
    Vo_test.Record[1] = Vo_test.Record_1;
    Vo_test.Record[2] = Vo_test.Record_2;
    ********从小到大排列*********
    for(i=0;i<3;i++)
    {
      for(j=i+1;j<3;j++)
      {
        if(Vo_test.Record[j]<Vo_test.Record[i])
    	  {
    	    unsigned int t;
    		t=Vo_test.Record[i];
    		Vo_test.Record[i]=Vo_test.Record[j];
    		Vo_test.Record[j]=t;
    	  }
      }
    }
    ***************************
    Vo_test.Minimum = Vo_test.Record[0];
    Vo_test.Median = Vo_test.Record[1];
    Vo_test.Maximum = Vo_test.Record[2];
    Vo_test.Average = (Vo_test.Record[0] + Vo_test.Record[1] + Vo_test.Record[2] )/ 3;
**********************************************************************************
}

void User_min_middle_max_2()
{
**************************************Vi的ADC数据处理*****************************
	int i,j;
	Vi_test.Record_0 = AdcResult.ADCRESULT6;
	Vi_test.Record_1 = AdcResult.ADCRESULT7;
	Vi_test.Record_2 = AdcResult.ADCRESULT8;
	Vi_test.Record[0] = Vi_test.Record_0;
	Vi_test.Record[1] = Vi_test.Record_1;
	Vi_test.Record[2] = Vi_test.Record_2;
	********从小到大排列*********
    for(i=0;i<3;i++)
    {
	   for(j=i+1;j<3;j++)
	   {
		 if(Vi_test.Record[j]<Vi_test.Record[i])
		 {
		  unsigned int t;
		  t=Vi_test.Record[i];
		  Vi_test.Record[i]=Vi_test.Record[j];
		  Vi_test.Record[j]=t;
		  }
	    }
	 }
    ***************************
    Vi_test.Minimum = Vi_test.Record[0];
    Vi_test.Median = Vi_test.Record[1];
    Vi_test.Maximum = Vi_test.Record[2];
    Vi_test.Average = (Vi_test.Record[0] + Vi_test.Record[1] + Vi_test.Record[2] )/ 3;
**********************************************************************************

*********************************Temperature的ADC数据处理*************************
    Temperature_test.Record_0 = AdcResult.ADCRESULT9;
    Temperature_test.Record_1 = AdcResult.ADCRESULT10;
    Temperature_test.Record_2 = AdcResult.ADCRESULT11;
    Temperature_test.Record[0] = Temperature_test.Record_0;
    Temperature_test.Record[1] = Temperature_test.Record_1;
    Temperature_test.Record[2] = Temperature_test.Record_2;
    ********从小到大排列*********
    for(i=0;i<3;i++)
    {
      for(j=i+1;j<3;j++)
      {
        if(Temperature_test.Record[j]<Temperature_test.Record[i])
    	  {
    	    unsigned int t;
    		t=Temperature_test.Record[i];
    		Temperature_test.Record[i]=Temperature_test.Record[j];
    		Temperature_test.Record[j]=t;
    	  }
      }
    }
    ***************************
    Temperature_test.Minimum = Temperature_test.Record[0];
    Temperature_test.Median = Temperature_test.Record[1];
    Temperature_test.Maximum = Temperature_test.Record[2];
    Temperature_test.Average = (Temperature_test.Record[0] + Temperature_test.Record[1] + Temperature_test.Record[2] )/ 3;
**********************************************************************************
}
*/
