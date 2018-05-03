#include "led.h"

//////////////////////////////////////////////////////////////////////////////////	 
/*
基于GPS和物联网的农机具定位系统
LED灯的驱动模块
修改日期：2018/3/31
*/						  
////////////////////////////////////////////////////////////////////////////////// 	  
//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);//使能PA,PD端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 //LED0-->PD.2 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOD.2
 GPIO_SetBits(GPIOD,GPIO_Pin_2);						 //PD.2 输出高

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //LED1-->PA.8 端口配置, 推挽输出
 GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //推挽输出 ，IO口速度为50MHz
 GPIO_SetBits(GPIOA,GPIO_Pin_8); 						 //PA.8 输出高 
}
 
