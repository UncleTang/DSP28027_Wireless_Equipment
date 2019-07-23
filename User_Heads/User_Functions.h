/*
 * User_Function.h
 *
 *  Created on: 2019��6��25��
 *      Author: JYW
 */

#ifndef USER_HEADS_USER_FUNCTIONS_H_
#define USER_HEADS_USER_FUNCTIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TARGET_GLOBAL
   #define TARGET_EXT 	extern
#else
   #define TARGET_EXT
#endif




/***********����������ʼ***********/

extern void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);  //TI�ֳɺ��� �����޸�

TARGET_EXT void Initial_User_variables(void);
//TARGET_EXT void Comparator_DC_TZ_Protect_init();   //�бȽ���ʱ����
/*TARGET_EXT __interrupt void epwm1_isr(void);
TARGET_EXT __interrupt void TZ_protect_isr(void);*/
TARGET_EXT void User_PID(void);
TARGET_EXT void User_Soft_start(void);


/*************����ͨ����غ���**********/
TARGET_EXT void scia_basic_init(void);     //SCIģ��������ó�ʼ��
TARGET_EXT void receive_parameter(void);   //��ȡ�û�ϣ�����в����Ĳ���
TARGET_EXT void PC_modify_kp_or_ki(void);  //dspͨ��SCI���յ��Է��͵��޸Ĳ���
TARGET_EXT void PC_update_vo_or_il_or_vi(void);  //��dsp�ɼ��������ѹ��������ͨ��SCI���͸�����
TARGET_EXT int pow(int a, int b);   //�˷�����
TARGET_EXT void scia_send_Char_one_by_one(char * Str);  //���ڷ�����ʾ���

/*************************************/

/*************ADC��غ���**********/
TARGET_EXT void Adc_basic_init(void);
/*TARGET_EXT __interrupt void Adcint1_isr(void);
TARGET_EXT __interrupt void Adcint2_isr(void);*/
TARGET_EXT Uint16 ADC_Medium(Uint16, Uint16, Uint16);
TARGET_EXT Uint16 ADC_Maximum(Uint16, Uint16, Uint16);
TARGET_EXT Uint16 ADC_Minimum(Uint16, Uint16, Uint16);
//TARGET_EXT void User_AD_Read();

/*************************************/



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /* USER_HEADS_USER_FUNCTIONS_H_ */
