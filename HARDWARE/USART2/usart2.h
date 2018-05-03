#ifndef __USART2_H
#define __USART2_H	 
#include "sys.h"  

//////////////////////////////////////////////////////////////////////////////////	 
/*
����GPS����������ũ���߶�λϵͳ
GPSģ����������
�޸����ڣ�2018/3/31
*/							  
//////////////////////////////////////////////////////////////////////////////////

#define USART2_MAX_RECV_LEN		1024				//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		1024				//����ͻ����ֽ���
//#define USART2_RX_EN 			1					//0,������;1,����.

extern char  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern u16 USART2_RX_STA;   						//��������״̬

void USART2_Init(u32 bound);				//����2��ʼ�� 
void TIM4_Set(u8 sta);
void TIM4_Init(u16 arr,u16 psc);
#endif

