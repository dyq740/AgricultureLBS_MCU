#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "usart2.h"
#include "timer.h"
#include "usart3.h"
#include "lcd.h"
#include "gizwits_product.h" 
#include "gps.h"
/************************************************
����GPS����������ũ���߶�λϵͳ
����������
�޸����ڣ�2018/3/31
************************************************/

//WIFI�豸���ӱ�־λ 
//1��������  0���Ͽ�
u8 wifi_sta=0;

/* �û�����ǰ�豸״̬�ṹ��*/
dataPoint_t currentDataPoint;

/*gpsЭ����������ݴ�Žṹ��*/
nmea_msg gpsx;

//Э���ʼ��
void Gizwits_Init(void)
{	
	TIM3_Int_Init(9,7199);//1Sϵͳ��ʱ
  usart3_init(9600);//WIFI��ʼ��,����3���ں�wifiģ��ͨѶ
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//�豸״̬�ṹ���ʼ��
	gizwitsInit();//��������ʼ��
}

//���ݲɼ�
void userHandle(void)
{ 
	currentDataPoint.valuegps_jingdu=gpsx.longitude;
	currentDataPoint.valuegps_speed=gpsx.speed;
	currentDataPoint.valuegps_weidu=gpsx.latitude;  
}
//������
 int main(void)
 {
  u8 key;
	u8 wifi_con;            //��ʱ��¼wifi����״̬ 1:������ 0:�Ͽ�
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	    //���ڳ�ʼ��Ϊ115200
	USART2_Init(9600);
 	LED_Init();			    //LED�˿ڳ�ʼ��
	KEY_Init();             //������ʼ�� 
	Gizwits_Init();         //Э���ʼ��
	printf("--------����GPS����������ũ���߶�λϵͳ----------\r\n");
	printf("KEY1:AirLink����ģʽ\t KEY_UP:��λ\t \r\n\r\n");
   	while(1)
	{
		
//����Ϊ�޸��������Ϊ�ɼ�GPSλ������
		if(USART2_RX_STA&0X8000)		//���յ�һ��������
		{
			GPS_Analysis(&gpsx,(char*)USART2_RX_BUF);//�����ַ���

			  USART2_RX_STA=0;		   	//������һ�ν���			
		}
	    userHandle();//�û��ɼ�
         
        gizwitsHandle((dataPoint_t *)&currentDataPoint);//Э�鴦��
 		
	    key = KEY_Scan(0);
		if(key==KEY1_PRES)//KEY1����
		{
			printf("WIFI����AirLink����ģʽ\r\n");
			gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-linkģʽ����
		}			
		if(key==WKUP_PRES)//KEY_UP����
		{  
			printf("WIFI��λ����������������\r\n");
			gizwitsSetMode(WIFI_RESET_MODE);//WIFI��λ
			wifi_sta=0;//��־wifi�ѶϿ�
			
		}	
		if(wifi_con!=wifi_sta)
	    {
		   wifi_con=wifi_sta;		
	    }
	    delay_ms(200);
	    LED1=!LED1;			
	}	 
} 
 
