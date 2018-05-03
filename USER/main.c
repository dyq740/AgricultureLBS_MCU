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
基于GPS和物联网的农机具定位系统
主函数代码
修改日期：2018/3/31
************************************************/

//WIFI设备连接标志位 
//1：已连接  0：断开
u8 wifi_sta=0;

/* 用户区当前设备状态结构体*/
dataPoint_t currentDataPoint;

/*gps协议解析后数据存放结构体*/
nmea_msg gpsx;

//协议初始化
void Gizwits_Init(void)
{	
	TIM3_Int_Init(9,7199);//1S系统定时
  usart3_init(9600);//WIFI初始化,串口3用于和wifi模组通讯
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//设备状态结构体初始化
	gizwitsInit();//缓冲区初始化
}

//数据采集
void userHandle(void)
{ 
	currentDataPoint.valuegps_jingdu=gpsx.longitude;
	currentDataPoint.valuegps_speed=gpsx.speed;
	currentDataPoint.valuegps_weidu=gpsx.latitude;  
}
//主函数
 int main(void)
 {
  u8 key;
	u8 wifi_con;            //临时记录wifi连接状态 1:已连接 0:断开
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	    //串口初始化为115200
	USART2_Init(9600);
 	LED_Init();			    //LED端口初始化
	KEY_Init();             //按键初始化 
	Gizwits_Init();         //协议初始化
	printf("--------基于GPS和物联网的农机具定位系统----------\r\n");
	printf("KEY1:AirLink连接模式\t KEY_UP:复位\t \r\n\r\n");
   	while(1)
	{
		
//以下为修改下面代码为采集GPS位置数据
		if(USART2_RX_STA&0X8000)		//接收到一次数据了
		{
			GPS_Analysis(&gpsx,(char*)USART2_RX_BUF);//分析字符串

			  USART2_RX_STA=0;		   	//启动下一次接收			
		}
	    userHandle();//用户采集
         
        gizwitsHandle((dataPoint_t *)&currentDataPoint);//协议处理
 		
	    key = KEY_Scan(0);
		if(key==KEY1_PRES)//KEY1按键
		{
			printf("WIFI进入AirLink连接模式\r\n");
			gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-link模式接入
		}			
		if(key==WKUP_PRES)//KEY_UP按键
		{  
			printf("WIFI复位，请重新配置连接\r\n");
			gizwitsSetMode(WIFI_RESET_MODE);//WIFI复位
			wifi_sta=0;//标志wifi已断开
			
		}	
		if(wifi_con!=wifi_sta)
	    {
		   wifi_con=wifi_sta;		
	    }
	    delay_ms(200);
	    LED1=!LED1;			
	}	 
} 
 
