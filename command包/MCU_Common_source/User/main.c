/**
************************************************************
* @file         main.c
* @brief        MCU版 入口文件
* @author       Gizwits
* @date         2016-09-05
* @version      V03010101
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
/********************************************************
** 代码移植说明
*
* 1、实现与模组通信串口驱动（1、中断收数据写入环形缓冲区;2、实现uartWrite()串口发送函数）
* 2、实现串口打印函数printf()
* 3、实现ms定时器，gizTimerMs()维护系统时间
* 4、实现MCU复位函数,模组可请求MCU复位
* 5、实现配置入网功能,调用gizwitsSetMode()函数实现模组配网功能
* 6、实现userHandle()数据的采集（上行逻辑）
* 7、实现gizwitsEventProcess()控制命令的具体执行(下行逻辑)
* 8、实现mcuRestart()复位函数
* 
*
*********************************************************/

#include <string.h>
#include "gizwits_protocol.h"

/** 用户区当前设备状态结构体*/
dataPoint_t currentDataPoint;

/**
* 用户初始化函数

* 在该函数中完成了外设驱动初始化以及用户相关数据的初始
* @param none
* @return none
* @note 开发者可在此函数内添加新的驱动初始及状态初始化
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
}

/**
* 用户数据获取

* 此处需要用户实现除可写数据点之外所有传感器数据的采集,可自行定义采集频率和设计数据过滤算法
* @param none
* @return none
*/
void userHandle(void)
{
        /*

    */
}

/**
* @brief程序入口函数

* 在该函数中完成用户相关的初始化,及主逻辑循环
* @param none
* @return none
*/
int main(void)
{  
    userInit();

    gizwitsInit();
    
    while(1)
    {
        userHandle();
        
        gizwitsHandle((dataPoint_t *)&currentDataPoint);
    }
}
