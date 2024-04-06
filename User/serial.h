
#ifndef  _SERIAL_H
#define  _SERIAL_H

#include "CPU.h"

 

/********************* 协议说明 ************************

数据格式：起始字节     (0xEA) +
          设备地址描述 (0x01) +
          产品ID       (0xD0) + 
          后续数据长度 (Len)  +   //包含到结束字节,不含该字节 
                        命令  + 
                        数据  +
          从Len开始的异或校验 +
          结束字节（0xF5）

********************************************************/



#define  TX1IE_EN   USART1->CR1|=((UINT32)1<<7);//USART_ConfigInt(USART1, USART_INT_TXDE, ENABLE); //使能接收中断//SET_BIT(USART1->CR1,   USART_CR1_TXEIE);       // 使能串口发送中断
#define  TX1IE_DIS  USART1->CR1&=~((UINT32)1<<7);//USART_ConfigInt(USART1, USART_INT_TXDE, DISABLE); //CLEAR_BIT(USART1->CR1, USART_CR1_TXEIE);   // 静止串口发送中断
#define  RX1IE_EN   USART1->CR1|=((UINT32)1<<5);//USART_ConfigInt(USART1, USART_INT_RXDNE, ENABLE); //SET_BIT(USART1->CR1,   USART_CR1_RXNEIE);      // 使能串口发送中断
#define  RX1IE_DIS  USART1->CR1&=~((UINT32)1<<5);//USART_ConfigInt(USART1, USART_INT_RXDNE, DISABLE);//CLEAR_BIT(USART1->CR1, USART_CR1_RXNEIE); 
#define  TX2IE_EN   USART2->CR1|=((UINT32)1<<7);//USART_ConfigInt(USART2, USART_INT_TXDE, ENABLE);//SET_BIT(USART2->CR1,   USART_CR1_TXEIE);       // 使能串口发送中断
#define  TX2IE_DIS  USART2->CR1&=~((UINT32)1<<7);//USART_ConfigInt(USART2, USART_INT_TXDE, DISABLE);//CLEAR_BIT(USART2->CR1, USART_CR1_TXEIE);   // 静止串口发送中断
#define  RX2IE_EN   USART2->CR1|=((UINT32)1<<5);//USART_ConfigInt(USART2, USART_INT_RXDNE, ENABLE);//SET_BIT(USART2->CR1,   USART_CR1_RXNEIE);      // 使能串口发送中断
#define  RX2IE_DIS  USART2->CR1&=~((UINT32)1<<5);//USART_ConfigInt(USART2, USART_INT_RXDNE, DISABLE);//CLEAR_BIT(USART2->CR1, USART_CR1_RXNEIE); 
 

#define  REC_MAX   300    // 定义接收缓存区的大小
#define  SEND_MAX  300    // 定义发送缓存区的大小

#define  SOI       0xEA      // 起始标志

 #define  CID       0xD1      // 设备描述符
 #define  EOI       0xF5      // 结束码
 #define  ADR       0x01
 
 
 #define  SERIAL_TIME_ISR   10        // 定时器间隔 ms
 #define  TIME_OUT   10      // 接收超时时间 ms
 #define  TIME_SLEEP 10000      // 休眠超时时间
typedef struct 
{
   UINT8 RecBuf[REC_MAX];    // 接收缓存区
   UINT16 RecCount;          // 接收的字节数
   UINT8 SendBuf[SEND_MAX];  // 发送缓存区
   UINT16 SendCount;         // 要发送的字节数
   UINT8 RecOver;            // 接收完成标志
   UINT16 RecTimer;          // 接收计时器
	 UINT16 SleepTime;         // 休眠计时
//	 UINT8 SleepFlag;          // 通讯休眠标志
	 UINT8 UARTx;              // 当前串口数据缓存区端口号
} MSG;
 
extern UINT8 MSG_SERIAL_CAN1_SleepFlag;
extern UINT8 MSG_SERIAL_CAN2_SleepFlag;
extern UINT8 MSG_SERIAL_UART1_SleepFlag;
extern UINT8 MSG_SERIAL_UART2_SleepFlag;
extern UINT8 MSG_SERIAL_UART3_SleepFlag;
extern UINT8 MSG_SERIAL_UART4_SleepFlag;


extern MSG *pMSGSERIAL;
 
extern  MSG MSG_SERIAL_UART1; // 定义在S_RAM 区域
extern  MSG MSG_SERIAL_UART2; // 定义在S_RAM 区域
extern  MSG MSG_SERIAL_UART3; // 定义在S_RAM 区域
extern  MSG MSG_SERIAL_UART4; // 定义在S_RAM 区域
extern  MSG MSG_SERIAL_CAN1;
extern  MSG MSG_SERIAL_CAN2;
//extern UINT32 KM;	
//extern UINT8 PowerOutputOk;
extern  UINT8 ADDR;
//extern  UINT8  UARTx;
extern  FP32 cellVlg;

extern void SerialInput(UINT8 RevData);
extern void SerialStartSend(UINT8 *pData);
extern void SerialTimer(void); // 由定时器调用
extern void SerialDecode(void);// 由主函数调用
extern void SerialOutput(void);

// 串口中断接收函数
extern void SerialInput_UART1(UINT8 RevData);
extern void SerialInput_UART2(UINT8 RevData);
extern void SerialInput_UART3(UINT8 RevData);
extern void SerialInput_UART4(UINT8 RevData);
// 串口中断发送函数
extern void SerialOutput_UART1(void);
extern void SerialOutput_UART2(void);
extern void SerialOutput_UART3(void);
extern void SerialOutput_UART4(void);
//功能函数
// 发送命令
//功能函数
// 发送命令
extern void SendCmd(UINT8 cmd1,UINT8 cmd2);
extern void SerialSendData(UINT8 cmd);
void SerialSendCurMul(UINT8 cmd1,UINT8 cmd2);
void SerialSendVlgMul(UINT8 cmd1,UINT8 cmd2); //电压倍数
void SerialSendVlg(UINT8 addr,UINT8 cmd1,UINT8 cmd2,UINT8 type);
void SerialSendCur(UINT8 cmd1,UINT8 cmd2);
void SerialSendFuel(UINT8 cmd1,UINT8 cmd2);
void SendConfigData(void);

//extern UINT8 ADR;
//extern UINT8 UART_TYPE;

UINT8 WriteVlgClb(UINT8 *pData);
void dec(void);
void UserSendMTFName(void);
void GetAllHVlgHook(void);
void SerialOutput_D(void);
void SerialInput_D(UINT8 RecData);
void SerialTimer_D(void);
void SerialDecode_DHook(void);
void SendSOCStopCHG(void);
void SendSOCCHG(void);
void SendDataToControl(void);
void SendLimitSpeed_D(UINT8 speed);
void SendLimitSpeed(UINT8 speed);
void RunCommand(void);
void SendConctrolData_D(void);
//void SendControlStates(UINT8 state);
//void GetBMSID(void);
//void SendSOCCHG(void);
//void SendSOCStopCHG(void);
void UserSendDataCode(void);
void UserRWData(void);
void LoadDataRecode(void);
void SerialDecoding(UINT8 *pData);
 
UINT8 RcvChk(void);
UINT8 LoadRcvChk(void);
 UINT16 LoadChkSum(UINT8 *pData,UINT8 count);
void SerialDecodeHook(void);
 
#endif





















