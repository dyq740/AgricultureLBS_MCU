#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
/*
����GPS����������ũ���߶�λϵͳ
LED�Ƶ�����ģ��
�޸����ڣ�2018/3/31
*/						  
////////////////////////////////////////////////////////////////////////////////// 	  
//��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);//ʹ��PA,PD�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PD.2 �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOD.2
 GPIO_SetBits(GPIOD,GPIO_Pin_2);						 //PD.2 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //LED1-->PA.8 �˿�����, �������
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOA,GPIO_Pin_8); 						 //PA.8 ����� 
}
 
