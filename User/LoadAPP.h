//=======================================Copyright(c)====================================
// 											欣旺达电子股份有限公司
//											研发三部软件小组
//												软件部 
//-------------------------------------------------文件信息------------------------------
//文件名		: mcg.h 
//创建人		: 易行云
//创建日期		:  
//描	述		: MCG模块驱动头文件
//-----------------------------------------------当前版本修订----------------------------
//修改人		:
//版	本		: 
//修改日期		:
//描	述		:
//=======================================================================================
#ifndef _CANLOAD_APP_H
#define _CANLOAD_APP_H

//=======================================================================================
//宏定义
//=======================================================================================
#define PRO_VERSION         (0x302)         /*软件板本号*/
#define BOOT_TRANS_FLAG     (0x5AA5)        /*转发标志*/
#define BOOT_PRO_TRY_FLAG   (0x5AA5)        /*已经尝试的标志*/
#define  BOOT_ENRTY_POINT    (0x10fb)        /*Boot入口地址*/

#define BOOT_READ_START_ADDR (33)           //RS485烧录可读起始地址(包括)
#define BOOT_READ_END_ADDR   (41)           //RS485烧录可读结束地址(包括)

#define BOOT_CMD_START_ADDR (42)            //RS485烧录可写起始地址(包括)
#define BOOT_CMD_END_ADDR   (43)            //RS485烧录可写结束地址(包括)

//=======================================================================================
//数据定义
//=======================================================================================
typedef enum _BOOT_STATE_INFO
{
    e_PRO_TYPE     = 0,            //协议类型
    e_DEVICE_TYPE  = 1,            //设备类型
    e_DEVICE_NUM   = 2,            //设备号
    e_CHIP_TYPE    = 3,            //芯片类型
    e_SOFT_VERSION = 4,             //软件版本号
    e_BOOT_VERSION = 5,             //BOOT版本号
    e_CANLOAD_STATE = 6,            //烧录状态
    e_RUN_STATE     = 7,            //运行状态
    e_LOADING_NUM   = 8,            //正在烧写的段号
    e_USER_COMMAND  = 9,            //用户指令
    e_FLASH_SECTION_NUM = 10,       //段长      
    e_CANLOAD_BUF_NUM = 11           //数据段长度
}e_BOOT_STATE_INFO;

typedef enum _MCU_TYPE_
{
    e_FREESCALE_DZ60 = 0,       //芯片类型
    e_FREESCALE_XEQ512 = 1,
    e_COMTEX_TM4C129ENDPT = 2,
}e_MCU_TYPE;

typedef enum _RUNMODEL_ENUM_
{
    e_TRANSMIT_MODEL = 0,    //转发模式
    e_CANLOAD_MODEL = 1,     //烧录模式
    e_PROGRAME_MODEL = 2,    //应用程序运行模式   
}e_RUNMODEL_ENUM;

typedef enum _RUNMODEL_STATE_
{
    e_LOADTRANSMIT_STATE    = 0,            /*无应用程序转发状态*/
    e_PROTRANSMIT_STATE     = 1,            /*应用程序转发状态*/
    e_CANLOADREADY_OK       = 2,            /*烧录准备*/
    e_CANLOADREADY_FAIL     = 3,            /*烧录准备失败*/
   // e_CANLOADPRE_OK         = 4,            /*烧录就绪*/
    e_CANLOADTRANSMITING    = 5,            /*正在传输*/   
    e_CANLOADTRANSMIT_FAIL  = 6,            /*传输失败*/
 //   e_CANLOADTRANSMIT_OK    = 7,            /*传输成功*/
    e_CANLOADFLASH_FAIL     = 8,            /*烧录失败*/
    e_CANLOADFLASH_OK       = 9,             /*烧录成功*/
    e_PRORUN_STATE          = 10,           /*应用程序运行状态*/
}e_RUNMODEL_STATE;

typedef enum _MESSAGE_TYPE_
{
    e_Cmd_IntoTransmit      = 0xE0,                 /*进入转发模式*/
    e_Cmd_ExitTransmit      = 0xE1,                 /*退出转发模式*/
    e_Cmd_Reset             = 0xE2,                 /*请求复位*/
    e_Cmd_IntoLoad          = 0xE3,                 /*请求烧录*/
    e_Cmd_ExitLoad          = 0xE4,                 /*退出烧录*/
    e_Cmd_FinishLoad        = 0xE5,                 /*烧录完成*/
}e_MESSAGE_TYPE;


typedef enum _BOOT_FLAG_ADDR_               /*起始地址为0xD600*/
{
    e_BOOT_TRANSMIT_FLAG_ADDR = 6,          /*转发模志存放地址*/
    e_BOOT_CRC_ADDR = 8,                    /*应用程序CRC存放地址*/
    e_BOOT_PRO_FLAG_ADDR = 10,              /*应用程序标志*/
    e_BOOT_PRO_TRY_FLAG_ADDR = 12,          /*尝试运行标志*/
    e_BOOT_PRO_VERSION_ADDR = 14,           /*应用程序版本号*/ 
    e_BOOT_SOTE_VERION_ADDR = 16,           /*Boot软件版本号存储地址*/
    e_BOOT_NETECU_FLAG = 20,               /*设备号及设备类型标志存放地址*/
	e_BOOT_NET_ADDR = 22,                  /*设备类型存放地址*/
    e_BOOT_ECU_ADDR = 24,                  /*设备号存放地址*/

}E_BOOT_FLAG_ADDR;

//=======================================================================================
//声明接口函数
//=======================================================================================
//=======================================================================================
//函数名称	: u16* flashUpdateByModbus(u8 fncCode, u8 sciNum, u16 address, u16 data)
//输入参数	: fncCode:功能码 sciNum:串口号 address:地址 data:数据
//输出参数	: void
//静态变量	: void
//功	能	: 接收处理
//注	意	:  
//=======================================================================================
u16* flashUpdateByModbus(u8 fncCode, u8 sciNum, u16 address, u16 data);

//=======================================================================================
//函数名称	: void BootloaderInit(void)
//输入参数	: void  
//输出参数	: void
//静态变量	: void
//功	能	: 初始化CAN烧录参数
//注	意	:  
//=======================================================================================
void BootloaderInit(void);

#endif
