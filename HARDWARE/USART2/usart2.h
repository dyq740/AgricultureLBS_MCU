#ifndef __USART2_H
#define __USART2_H	 
#include "sys.h"  

//////////////////////////////////////////////////////////////////////////////////	 
/*
基于GPS和物联网的农机具定位系统
GPS模块驱动代码
修改日期：2018/3/31
*/							  
//////////////////////////////////////////////////////////////////////////////////

#define USART2_MAX_RECV_LEN		1024				//最大接收缓存字节数
#define USART2_MAX_SEND_LEN		1024				//最大发送缓存字节数
//#define USART2_RX_EN 			1					//0,不接收;1,接收.

extern char  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//接收缓冲,最大USART2_MAX_RECV_LEN字节
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//发送缓冲,最大USART2_MAX_SEND_LEN字节
extern u16 USART2_RX_STA;   						//接收数据状态

void USART2_Init(u32 bound);				//串口2初始化 
void TIM4_Set(u8 sta);
void TIM4_Init(u16 arr,u16 psc);
#endif

