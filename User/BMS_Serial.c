#include "global.h"
extern void ModeBusRxUserHook(u8 *pRxdata, u8 len);
	static UINT8 SendDataBuff[255];
static   UINT8 Modbus_AddrData[128][2]; // 地址数据存储区
MSG MSG_SERIAL_UART1; // 定义在S_RAM 区域
MSG MSG_SERIAL_UART2; // 定义在S_RAM 区域
MSG MSG_SERIAL_UART3; // 定义在S_RAM 区域
MSG MSG_SERIAL_UART4; // 定义在S_RAM 区域
MSG MSG_SERIAL_CAN1;
MSG MSG_SERIAL_CAN2;
	BLACB  BLA_CB;
    OTCB   OT_CB;
    OVCB   OV_CB;
    UVCB   UV_CB;
    OCCB   OC_CB;
    FCB    F_CB;
    CCB    C_CB;
    VCB    V_CB;
		    RTCCCB  RTCC_CB;
SOCCB SOC;
soc_cb SOC_CB;
		UINT8 RTCC=0;
MSG *pMSGSERIAL;

UINT8 MSG_SERIAL_CAN1_SleepFlag;
UINT8 MSG_SERIAL_CAN2_SleepFlag;
UINT8 MSG_SERIAL_UART1_SleepFlag;
UINT8 MSG_SERIAL_UART2_SleepFlag;
UINT8 MSG_SERIAL_UART3_SleepFlag;
UINT8 MSG_SERIAL_UART4_SleepFlag;
UINT8   ADDR=1;
float VERSION=1.0;
UINT8 Hardware_VER=10;
UINT8 TCell_count=10;
UINT8 TTemp_count=2;
UINT8 MOS_OT=1;
UINT8 E_OT=1;
UINT8 Guset_CMDDSGFET_EN=1;
UINT8 Guset_CMDCHGFET_EN=1;
UINT8 Guset_Heat_EN=1;
UINT8 WriteEepromFlag=0;
    UINT8 ProductCode[32];

UINT8 Guset_CMDGPSPOWER_EN=0;



UINT8 ReadCfgData[32];
UINT8 ReadCfgEData[32];
  UINT8 ReadAlamData[32];
  UINT8 ReadFuelData[32];
	
	


UINT8 RS485_DIR1=0;
UINT8 RS485_DIR2=0;
UINT8 RS485_DIR3=0;
UINT8 RS485_DIR4=0;


UINT16 MSG_SERIAL_RecCount = 0;
UINT16 MSG_SERIAL_GUEST_RecCount = 0;
UINT16 MSG_SERIAL_UART1_RecCount = 0;
UINT16 MSG_SERIAL_UART2_RecCount = 0;
UINT16 MSG_SERIAL_UART3_RecCount = 0;
UINT16 MSG_SERIAL_UART4_RecCount = 0;


UINT8 ChkSum(UINT8 *pData, UINT8 count)
{
  UINT8 chkSum = 0;
  count -= 1;
  while (count--)
  {
    chkSum ^= (*pData++);
  }
  return (chkSum);
}
// 接收数据校验
UINT8 RcvChk(void)
{
  if ((*pMSGSERIAL).RecBuf[(*pMSGSERIAL).RecBuf[3] + 2] == ChkSum(&(*pMSGSERIAL).RecBuf[3], (*pMSGSERIAL).RecBuf[3]))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
// 下载校验
UINT16 LoadChkSum(UINT8 *pData, UINT8 count)
{
  UINT16 chkSum = 0;
  while (count--)
  {
    chkSum += (*pData++);
  }
  return (chkSum);
}


// 接收数据校验
UINT8 LoadRcvChk(void)
{
  if ((*pMSGSERIAL).RecBuf[(*pMSGSERIAL).RecBuf[3] + 2] == LoadChkSum(&(*pMSGSERIAL).RecBuf[3], (*pMSGSERIAL).RecBuf[3] - 1))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
// 清接收缓存区 注意在串口接收中断函数里面不能调用此函数 必须自己单独写清除缓存区函数
static void ClrRcvBuf(MSG *pMSG_SERIAL)
{	
 UINT16 i;
	
	(*pMSG_SERIAL).RecCount=0; // 清接收数据计数器
	(*pMSG_SERIAL).RecTimer=0; // 清计时器
	(*pMSG_SERIAL).RecOver=0;  // 允许接
	for(i=0;i<300;i++)
  (*pMSG_SERIAL).RecBuf[i]=0;
	
 
	//(*pMSG_SERIAL).UARTx=0;
}


// 数据提取
void SerialDecoding(UINT8 *pData)
{
  switch (*pData)
  {
  case 0x04: // 电池电压(0x02),电流(0x03),电量(0x04),数据请求
    //SerialSendFuelGuest(0x04);
    break;
  case 0xff: // 内部用命令
    switch (*(pData + 1))
    {
    case 0x00: // 写入生产序列号
    //  WriteProductCode(*(pData + 2) + 1, pData + 2);
      break;
    case 0x01: // 读取生产序列号
    //  SendProductCode();
      break;
	}
}
	}
void UARTSendData(void)
{ //UINT8 i;
  if (RS485_DIR1 == 1)
  {
    if ((*pMSGSERIAL).UARTx == 1)
    {
   ////   RS485DIR1_Output_0_Hook();
    }
  }
  if (RS485_DIR2 == 1)
  {
    if ((*pMSGSERIAL).UARTx == 2)
    {
  //    RS485DIR2_Output_0_Hook();
    }
  }
  if (RS485_DIR3 == 1)
  {
    if ((*pMSGSERIAL).UARTx == 3)
    {
   //   RS485DIR3_Output_0_Hook();
    }
  }
  if (RS485_DIR4 == 1)
  {
    if ((*pMSGSERIAL).UARTx == 4)
    {
   //   RS485DIR4_Output_0_Hook();
    }
  }
  (*pMSGSERIAL).SendBuf[0] = 0xEB;
  (*pMSGSERIAL).SendBuf[1] = 0x01;
  (*pMSGSERIAL).SendBuf[2] = 0x01;
  (*pMSGSERIAL).SendBuf[(*pMSGSERIAL).SendBuf[3] + 2] = LoadChkSum(&(*pMSGSERIAL).SendBuf[3], (*pMSGSERIAL).SendBuf[3] - 1);
  (*pMSGSERIAL).SendBuf[(*pMSGSERIAL).SendBuf[3] + 3] = 0xF5;
  (*pMSGSERIAL).SendCount = (*pMSGSERIAL).SendBuf[3] + 4;
  //CAN_SendDataToBoxHook();
 // if (_UART1)
  {
    if ((*pMSGSERIAL).UARTx == 1)
    {
      RX1IE_DIS;
      TX1IE_EN;
    } // 禁止接收数据// 使能串口发送中断
  }
 // if (_UART2)
  {
    if ((*pMSGSERIAL).UARTx == 2) // 禁止接收数据// 使能串口发送中断
    {
      {
        RX2IE_DIS;
        TX2IE_EN;
      }
    }
  }
//  //if (_UART3)
//  {
//    if ((*pMSGSERIAL).UARTx == 3)
//    {
//      RX3IE_DIS;
//      TX3IE_EN;
//    } // 禁止接收数据// 使能串口发送中断
//  }
// // if (_UART4)
//  {
//    if ((*pMSGSERIAL).UARTx == 4)
//    {
//      RX4IE_DIS;
//      TX4IE_EN;
//    } // 禁止接收数据// 使能串口发送中断
//  }
}
void LoadDataRecode(void)
{

  if ((*pMSGSERIAL).RecBuf[2] == 1) // 读
  {
    (*pMSGSERIAL).SendBuf[4] = (*pMSGSERIAL).RecBuf[4];
    switch ((*pMSGSERIAL).RecBuf[4])
    {
    case 0x90: // 电池固件版本
      (*pMSGSERIAL).SendBuf[3] = 4;
      (*pMSGSERIAL).SendBuf[5] = (VERSION + 0.01f) * 10; // 固件版本
      UARTSendData();
      break;
    }
  }
  else if ((*pMSGSERIAL).RecBuf[2] == 0) // 写
  {
    (*pMSGSERIAL).SendBuf[4] = 0x80;
    switch ((*pMSGSERIAL).RecBuf[4])
    {
    case 0x80:
      switch ((*pMSGSERIAL).RecBuf[5])
      {
      case 0x22:
        (*pMSGSERIAL).SendBuf[3] = 4;
        (*pMSGSERIAL).SendBuf[5] = 0x33; // 应答
        UARTSendData();
        break;
      case 0x55:               // 启动升级
                               /*
								      NVIC->ICER[0]=NVIC->ICER[0];// 关闭所有中断
		  	             // HAL_RCC_DeInit();
                      if(((*(INT32U *)(0x08000000)) & 0x2FFE0000)==0x20000000)//检测栈顶地址是否合法
                      {
                        __set_MSP (*(INT32U *)(0x08000000));// 初始化APP堆栈
												Jump_To_Application=(pIapFun)(*(INT32U *)(0x08000000 + 4));//
				                Jump_To_Application();
		                  }
								*/
//        SaveFuleData();        //保存数据
//        SaveSatesData(0, 100); //程序更新进入bootload
        NVIC_SystemReset();
        break;
      }
      break;
    }
  }
}
void SerialTimeOut_(void)
{
  UINT16 mTimeoutCount = 0;
  UINT16 mTimeSleepCount = 0;
  mTimeoutCount = TIME_OUT / SERIAL_TIME_ISR;     // 通讯超时时间
  mTimeSleepCount = TIME_SLEEP / SERIAL_TIME_ISR; // 通讯休眠时间
  // 通讯超时判断
  if (MSG_SERIAL_CAN1.RecTimer > mTimeoutCount) // 如果接收超时
  {
    MSG_SERIAL_CAN1.RecCount = 0; // 清接收数据计数器
    MSG_SERIAL_CAN1.RecTimer = 0; // 清计时器
    MSG_SERIAL_CAN1.RecOver = 0;  // 允许接
  }
  if (MSG_SERIAL_CAN2.RecTimer > mTimeoutCount) // 如果接收超时
  {
    MSG_SERIAL_CAN2.RecCount = 0; // 清接收数据计数器
    MSG_SERIAL_CAN2.RecTimer = 0; // 清计时器
    MSG_SERIAL_CAN2.RecOver = 0;  // 允许接
  }
  if (MSG_SERIAL_UART1.RecTimer > mTimeoutCount) // 如果接收超时
  {
    MSG_SERIAL_UART1.RecCount = 0; // 清接收数据计数器
    MSG_SERIAL_UART1.RecTimer = 0; // 清计时器
    MSG_SERIAL_UART1.RecOver = 0;  // 允许接
  }
  if (MSG_SERIAL_UART2.RecTimer > mTimeoutCount) // 如果接收超时
  {
    MSG_SERIAL_UART2.RecCount = 0; // 清接收数据计数器
    MSG_SERIAL_UART2.RecTimer = 0; // 清计时器
    MSG_SERIAL_UART2.RecOver = 0;  // 允许接
  }
  if (MSG_SERIAL_UART3.RecTimer > mTimeoutCount) // 如果接收超时
  {
    MSG_SERIAL_UART3.RecCount = 0; // 清接收数据计数器
    MSG_SERIAL_UART3.RecTimer = 0; // 清计时器
    MSG_SERIAL_UART3.RecOver = 0;  // 允许接
  }
  if (MSG_SERIAL_UART4.RecTimer > mTimeoutCount) // 如果接收超时
  {
    MSG_SERIAL_UART4.RecCount = 0; // 清接收数据计数器
    MSG_SERIAL_UART4.RecTimer = 0; // 清计时器
    MSG_SERIAL_UART4.RecOver = 0;  // 允许接
  }
  // 休眠判断
  if (MSG_SERIAL_CAN1_SleepFlag == 0)
  {
    if (MSG_SERIAL_CAN1.SleepTime > mTimeSleepCount)
    {
      MSG_SERIAL_CAN1_SleepFlag = 1;
    }
  }
  if (MSG_SERIAL_CAN2_SleepFlag == 0)
  {
    if (MSG_SERIAL_CAN2.SleepTime > mTimeSleepCount)
    {
      MSG_SERIAL_CAN2_SleepFlag = 1;
    }
  }
  if (MSG_SERIAL_UART1_SleepFlag == 0)
  {
    if (MSG_SERIAL_UART1.SleepTime > mTimeSleepCount)
    {
      MSG_SERIAL_UART1_SleepFlag = 1;
    }
  }
  if (MSG_SERIAL_UART2_SleepFlag == 0)
  {
    if (MSG_SERIAL_UART2.SleepTime > mTimeSleepCount)
    {
      MSG_SERIAL_UART2_SleepFlag = 1;
    }
  }
  if (MSG_SERIAL_UART3_SleepFlag == 0)
  {
    if (MSG_SERIAL_UART3.SleepTime > mTimeSleepCount)
    {
      MSG_SERIAL_UART3_SleepFlag = 1;
    }
  }
  if (MSG_SERIAL_UART4_SleepFlag == 0)
  {
    if (MSG_SERIAL_UART4.SleepTime > mTimeSleepCount)
    {
      MSG_SERIAL_UART4_SleepFlag = 1;
    }
  }
}
/**************************** 系统调用函数 *****************************/
// 由定时器调用
void SerialTimer(void)
{
  // 通讯超时计时
  if ((MSG_SERIAL_CAN1.RecCount != 0) && (MSG_SERIAL_RecCount == MSG_SERIAL_CAN1.RecCount)) // 如果接收数据中断了
  {
    if (MSG_SERIAL_CAN1.RecOver != 1)
    {
      MSG_SERIAL_CAN1.RecTimer++; // 通讯超时计时
    }
  }
  if ((MSG_SERIAL_CAN2.RecCount != 0) && (MSG_SERIAL_GUEST_RecCount == MSG_SERIAL_CAN2.RecCount)) // 如果接收数据中断了
  {
    if (MSG_SERIAL_CAN2.RecOver != 1)
    {
      MSG_SERIAL_CAN2.RecTimer++; // 通讯超时计时
    }
  }
  if ((MSG_SERIAL_UART1.RecCount != 0) && (MSG_SERIAL_UART1_RecCount == MSG_SERIAL_UART1.RecCount)) // 如果接收数据中断了
  {
    if (MSG_SERIAL_UART1.RecOver != 1)
    {
      MSG_SERIAL_UART1.RecTimer++; // 通讯超时计时
    }
  }
  if ((MSG_SERIAL_UART2.RecCount != 0) && (MSG_SERIAL_UART2_RecCount == MSG_SERIAL_UART2.RecCount)) // 如果接收数据中断了
  {
    if (MSG_SERIAL_UART2.RecOver != 1)
    {
      MSG_SERIAL_UART2.RecTimer++; // 通讯超时计时
    }
  }
  if ((MSG_SERIAL_UART3.RecCount != 0) && (MSG_SERIAL_UART3_RecCount == MSG_SERIAL_UART3.RecCount)) // 如果接收数据中断了
  {
    if (MSG_SERIAL_UART3.RecOver != 1)
    {
      MSG_SERIAL_UART3.RecTimer++; // 通讯超时计时
    }
  }
  if ((MSG_SERIAL_UART4.RecCount != 0) && (MSG_SERIAL_UART4_RecCount == MSG_SERIAL_UART4.RecCount)) // 如果接收数据中断了
  {
    if (MSG_SERIAL_UART4.RecOver != 1)
    {
      MSG_SERIAL_UART4.RecTimer++; // 通讯超时计时
    }
  }
  // 休眠计时
  if (MSG_SERIAL_CAN1.RecCount == 0)
  {
    MSG_SERIAL_CAN1.SleepTime++; // 休眠计时
  }
  if (MSG_SERIAL_CAN2.RecCount == 0)
  {
    MSG_SERIAL_CAN2.SleepTime++; //休眠计时
  }
  if (MSG_SERIAL_UART1.RecCount == 0)
  {
    MSG_SERIAL_UART1.SleepTime++; // 休眠计时
  }
  if (MSG_SERIAL_UART2.RecCount == 0)
  {
    MSG_SERIAL_UART2.SleepTime++; // 休眠计时
  }
  if (MSG_SERIAL_UART3.RecCount == 0)
  {
    MSG_SERIAL_UART3.SleepTime++; // 休眠计时
  }
  if (MSG_SERIAL_UART4.RecCount == 0)
  {
    MSG_SERIAL_UART4.SleepTime++; // 休眠计时
  }
  MSG_SERIAL_RecCount = MSG_SERIAL_CAN1.RecCount;
  MSG_SERIAL_GUEST_RecCount = MSG_SERIAL_CAN2.RecCount;
  MSG_SERIAL_UART1_RecCount = MSG_SERIAL_UART1.RecCount;
  MSG_SERIAL_UART2_RecCount = MSG_SERIAL_UART2.RecCount;
  MSG_SERIAL_UART3_RecCount = MSG_SERIAL_UART3.RecCount;
  MSG_SERIAL_UART4_RecCount = MSG_SERIAL_UART4.RecCount;
  SerialTimeOut_();
}

// UART1中断接收数据
void SerialInput_UART1(UINT8 RecData)
{
	if (MSG_SERIAL_UART1.RecOver)
		return;
	//--------------------------------超力源上位机协议数据包-----------------------------/
	if ((RecData == SOI) && (MSG_SERIAL_UART1.RecCount == 0))
	{
		MSG_SERIAL_UART1.SleepTime = 0;
		MSG_SERIAL_UART1_SleepFlag = 0;
		MSG_SERIAL_UART1.RecBuf[0] = SOI;
		MSG_SERIAL_UART1.RecCount = 1;
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] == SOI) && (MSG_SERIAL_UART1.RecCount < REC_MAX)) //如果是上位机协议 接收数据
	{
		MSG_SERIAL_UART1.RecBuf[MSG_SERIAL_UART1.RecCount++] = RecData;
		if ((MSG_SERIAL_UART1.RecCount >= 2) && (MSG_SERIAL_UART1.RecBuf[1] != CID)) // 判断第2个字节是否是上位机协议
		{
			MSG_SERIAL_UART1.RecCount = 0;
		}
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] != 0xeb) && (MSG_SERIAL_UART1.RecBuf[0] != ADDR) && (MSG_SERIAL_UART1.RecBuf[0] != 0x6e)  ) // 如果不是升级协议也不是MODBUS协议
	// else if(MSG_SERIAL_UART1.RecBuf[0]!=0xeb && MSG_SERIAL_UART1.RecBuf[0]!=ADDR && MSG_SERIAL_UART1.RecBuf[0]!=0xec  && (MSG_SERIAL_UART1.RecBuf[0]!=0x7e))
	{
		MSG_SERIAL_UART1.RecCount = 0;
	}

	if ((MSG_SERIAL_UART1.RecBuf[0] == SOI) && (RecData == EOI) && (MSG_SERIAL_UART1.RecCount == (MSG_SERIAL_UART1.RecBuf[3] + 4)))
	{
		MSG_SERIAL_UART1.RecOver = 1; // 上位机协议接收完成
		MSG_SERIAL_UART1.RecTimer = 0;
		MSG_SERIAL_UART1.RecCount = 0;
	}
	//--------------------------------超力源升级协议--------------------------------/
	if ((RecData == 0xEB) && (MSG_SERIAL_UART1.RecCount == 0))
	{
		MSG_SERIAL_UART1.RecBuf[0] = 0xEB;
		MSG_SERIAL_UART1.RecCount = 1; //
		MSG_SERIAL_UART1.SleepTime = 0;
		MSG_SERIAL_UART1_SleepFlag = 0;
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] == 0xEB) && (MSG_SERIAL_UART1.RecCount < 75)) // 如果是超力源升级协议接收数据
	{
		MSG_SERIAL_UART1.RecBuf[MSG_SERIAL_UART1.RecCount++] = RecData;
		if ((MSG_SERIAL_UART1.RecCount >= 2) && (MSG_SERIAL_UART1.RecBuf[1] != ADDR)) // 如果第二个字节不是升级协议
		{
			MSG_SERIAL_UART1.RecCount = 0;
		}
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] != SOI) && (MSG_SERIAL_UART1.RecBuf[0] != ADDR)  && (MSG_SERIAL_UART1.RecBuf[0] != 0x6e)  ) // 如果不是上位机器协议也不是MODbus协议
	// else if(MSG_SERIAL_UART1.RecBuf[0]!=SOI && MSG_SERIAL_UART1.RecBuf[0]!=ADDR && MSG_SERIAL_UART1.RecBuf[0]!=0xec  && (MSG_SERIAL_UART1.RecBuf[0]!=0x7e))
	{
		MSG_SERIAL_UART1.RecCount = 0;
	}
	if ((MSG_SERIAL_UART1.RecBuf[0] == 0xEB) && (RecData == EOI) && (MSG_SERIAL_UART1.RecCount == (MSG_SERIAL_UART1.RecBuf[3] + 4)))
	{
		MSG_SERIAL_UART1.RecOver = 1;
		MSG_SERIAL_UART1.RecTimer = 0;
		MSG_SERIAL_UART1.RecCount = 0;
	}
	 //--------------------------------欣旺达升级协议--------------------------------/
	if ((RecData == 0X6E) && (MSG_SERIAL_UART1.RecCount == 0))
	{
		MSG_SERIAL_UART1.RecBuf[0] = 0X6E;
		MSG_SERIAL_UART1.RecCount = 1; //
		MSG_SERIAL_UART1.SleepTime = 0;
		MSG_SERIAL_UART1_SleepFlag = 0;
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] == 0X6E) && (MSG_SERIAL_UART1.RecCount < 75)) // 如果是超力源升级协议接收数据
	{
		MSG_SERIAL_UART1.RecBuf[MSG_SERIAL_UART1.RecCount++] = RecData;
//		if ((MSG_SERIAL_UART1.RecCount >= 2) && (MSG_SERIAL_UART1.RecBuf[1] != ADDR)) // 如果第二个字节不是升级协议
//		{
//			MSG_SERIAL_UART1.RecCount = 0;
//		}
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] != SOI) && (MSG_SERIAL_UART1.RecBuf[0] != ADDR)  && (MSG_SERIAL_UART1.RecBuf[0] != 0XEB)  ) // 如果不是上位机器协议也不是MODbus协议
	// else if(MSG_SERIAL_UART1.RecBuf[0]!=SOI && MSG_SERIAL_UART1.RecBuf[0]!=ADDR && MSG_SERIAL_UART1.RecBuf[0]!=0xec  && (MSG_SERIAL_UART1.RecBuf[0]!=0x7e))
	{
		MSG_SERIAL_UART1.RecCount = 0;
	}
	if (((MSG_SERIAL_UART1.RecBuf[0] == 0X6E)&&(MSG_SERIAL_UART1.RecBuf[1] == 0X3)&&(MSG_SERIAL_UART1.RecCount == 8))
	|| ((MSG_SERIAL_UART1.RecBuf[0] == 0X6E)&&(MSG_SERIAL_UART1.RecBuf[1] == 0X10)&&(MSG_SERIAL_UART1.RecCount == (MSG_SERIAL_UART1.RecBuf[6] + 9)))
	)
	
	{
		MSG_SERIAL_UART1.RecOver = 1;
		MSG_SERIAL_UART1.RecTimer = 0;
		MSG_SERIAL_UART1.RecCount = 0;
	}
	
	//--------------------------------超力源MODBUS协议--------------------------------/
	if ((RecData == ADDR) && (MSG_SERIAL_UART1.RecCount == 0))
	{
		MSG_SERIAL_UART1.SleepTime = 0;
		MSG_SERIAL_UART1_SleepFlag = 0;
		MSG_SERIAL_UART1.RecBuf[0] = RecData;
		MSG_SERIAL_UART1.RecCount = 1; // 启动接收
	}
	else if ((MSG_SERIAL_UART1.RecCount != 0) && (MSG_SERIAL_UART1.RecBuf[0] == ADDR) && (MSG_SERIAL_UART1.RecCount < REC_MAX)) // 如果已经接收到起始位
	{
		MSG_SERIAL_UART1.RecBuf[MSG_SERIAL_UART1.RecCount++] = RecData;
	}																					  // 将数据添加到缓存区
	else if ((MSG_SERIAL_UART1.RecBuf[0] != SOI) && (MSG_SERIAL_UART1.RecBuf[0] != 0xeb)  && (MSG_SERIAL_UART1.RecBuf[0] != 0x6e) ) // 不是上位机数据，也不是升级数据
	{
		MSG_SERIAL_UART1.RecCount = 0;
	}
	if (MSG_SERIAL_UART1.RecBuf[0] == ADDR)
	{
		if (MSG_SERIAL_UART1.RecCount >= 6) //接收到6个字节 识别特征数据
		{
			if ((MSG_SERIAL_UART1.RecBuf[2] != 0) || (MSG_SERIAL_UART1.RecBuf[3] > 150) || (MSG_SERIAL_UART1.RecBuf[4] != 0) || (MSG_SERIAL_UART1.RecBuf[5] > 150)) // 地址及数量超出范围
			{
				MSG_SERIAL_UART1.RecCount = 0;
				MSG_SERIAL_UART1.RecTimer = 0;
			}
		}
		if (((MSG_SERIAL_UART1.RecBuf[1] == 0x03) && (MSG_SERIAL_UART1.RecCount == 8))) // 读取数据
		{
			/*
				  // 直接解码
				  if(!Modbus_UserRcvChk(MSG_SERIAL_UART1.RecBuf)) // MODBUS协议校验
				  {
					 MSG_SERIAL_UART1.RecBuf[0]=0;
				 MSG_SERIAL_UART1.RecBuf[1]=0;
				 MSG_SERIAL_UART1.RecCount=0; // 清接收数据计数器
				 MSG_SERIAL_UART1.RecOver=0;  // 允许接
				  }else
				  {
				  */
			/*
			  // 直接中断中回复 避免丢帧
		  Modbus_SendData(&MSG_SERIAL_UART1,MSG_SERIAL_UART1.RecBuf);   // 解码 读取数据
		Modbus_ClearBuff_UART1();
			  */
			// 空闲任务解码
			MSG_SERIAL_UART1.RecOver = 2;  // MUDBUS 接收完整 且为读
			MSG_SERIAL_UART1.RecTimer = 0; // 清超时计时器
			MSG_SERIAL_UART1.RecCount = 0;

			// }
		}
		else if ((MSG_SERIAL_UART1.RecBuf[1] == 0x10) && (MSG_SERIAL_UART1.RecCount >= 11)) // 写入数据
		{
			if (MSG_SERIAL_UART1.RecCount == (MSG_SERIAL_UART1.RecBuf[6] + 9))
			{
				/*
						if(!Modbus_UserRcvChk((*pMSG).RecBuf)) //if the check is bad.
					{
								MSG_SERIAL_UART1.RecBuf[0]=0;
								MSG_SERIAL_UART1.RecBuf[1]=0;
								MSG_SERIAL_UART1.RecCount=0; // 清接收数据计数器
								MSG_SERIAL_UART1.RecOver=0;  // 允许接
					}else
						{
				*/
				if ((MSG_SERIAL_UART1.RecBuf[5] << 1) == (MSG_SERIAL_UART1.RecBuf[6])) // 写入寄存器的个数与写入的字节数相吻合
				{

		 
					MSG_SERIAL_UART1.RecOver = 3;  // =2 读取数据包接收完成  =3写入数据包接收完成
					MSG_SERIAL_UART1.RecTimer = 0; // 清计时器
					MSG_SERIAL_UART1.RecCount = 0;
				}
				//	}
			}
		}
	}
}
// UART1中断发送数据
void SerialOutput_UART1(void)
{
	static UINT8 mSendCount = 0;
	if (MSG_SERIAL_UART1.SendCount)
	{
		ClrWdt();
		MSG_SERIAL_UART1.SendCount--;
		if  (MSG_SERIAL_UART1.UARTx == 1)
		{
			USART1->DR = MSG_SERIAL_UART1.SendBuf[mSendCount++];
		}
		if (MSG_SERIAL_UART1.SendCount == 0)
		{
			mSendCount = 0;
		//	if ((MSG_SERIAL_UART1.UARTx == 1) && (RS485_DIR1)) // 485端口
			{
				while (!(USART1->SR & ((UINT32)1 << 6)))
					; // 等待发送完成
			}
		}
	}
	else
	{
		mSendCount = 0;
		MSG_SERIAL_UART1.SendCount = 0;
	//	if (_UART1)
		{
			TX1IE_DIS;
			RX1IE_EN;
		}
	//	if (RS485_DIR1) // 485端口
		{
		//	RS485DIR1_Output_1_Hook(); // 设置为接收
		}
	}
}
 
void Modbus_ClearBuff_UART1(void)
{
	MSG_SERIAL_UART1.RecBuf[0] = 0;
	MSG_SERIAL_UART1.RecBuf[1] = 0;
	MSG_SERIAL_UART1.RecBuf[3] = 0;
	MSG_SERIAL_UART1.RecBuf[6] = 0;
	MSG_SERIAL_UART1.RecTimer = 0;
	MSG_SERIAL_UART1.RecCount = 0; // 清接收数据计数器
	MSG_SERIAL_UART1.RecOver = 0;  // 允许接数据
								   //  MSG_SERIAL_UART1.UARTx=0;
}
void Modbus_ClearBuff_UART2(void)
{
	MSG_SERIAL_UART2.RecBuf[0] = 0;
	MSG_SERIAL_UART2.RecBuf[1] = 0;
	MSG_SERIAL_UART2.RecBuf[3] = 0;
	MSG_SERIAL_UART2.RecBuf[6] = 0;
	MSG_SERIAL_UART2.RecTimer = 0;
	MSG_SERIAL_UART2.RecCount = 0; // 清接收数据计数器
	MSG_SERIAL_UART2.RecOver = 0;  // 允许接数据
	//	  MSG_SERIAL_UART2.UARTx=0;
}
void Modbus_ClearBuff_UART3(void)
{
	MSG_SERIAL_UART3.RecBuf[0] = 0;
	MSG_SERIAL_UART3.RecBuf[1] = 0;
	MSG_SERIAL_UART3.RecBuf[3] = 0;
	MSG_SERIAL_UART3.RecBuf[6] = 0;
	MSG_SERIAL_UART3.RecTimer = 0;
	MSG_SERIAL_UART3.RecCount = 0; // 清接收数据计数器
	MSG_SERIAL_UART3.RecOver = 0;  // 允许接数据
	//	  MSG_SERIAL_UART3.UARTx=0;
}
void Modbus_ClearBuff_UART4(void)
{
	MSG_SERIAL_UART4.RecBuf[0] = 0;
	MSG_SERIAL_UART4.RecBuf[1] = 0;
	MSG_SERIAL_UART4.RecBuf[3] = 0;
	MSG_SERIAL_UART4.RecBuf[6] = 0;
	MSG_SERIAL_UART4.RecTimer = 0;
	MSG_SERIAL_UART4.RecCount = 0; // 清接收数据计数器
	MSG_SERIAL_UART4.RecOver = 0;  // 允许接数据
								   //  MSG_SERIAL_UART4.UARTx=0;
}
void Modbus_ClearBuff_CAN1(void)
{
	MSG_SERIAL_CAN1.RecBuf[0] = 0;
	MSG_SERIAL_CAN1.RecBuf[1] = 0;
	MSG_SERIAL_CAN1.RecBuf[3] = 0;
	MSG_SERIAL_CAN1.RecBuf[6] = 0;
	MSG_SERIAL_CAN1.RecTimer = 0;
	MSG_SERIAL_CAN1.RecCount = 0; // 清接收数据计数器
	MSG_SERIAL_CAN1.RecOver = 0;  // 允许接数据
								  // MSG_SERIAL_CAN1.UARTx=0;
}
void Modbus_ClearBuff_CAN2(void)
{
	MSG_SERIAL_CAN2.RecBuf[0] = 0;
	MSG_SERIAL_CAN2.RecBuf[1] = 0;
	MSG_SERIAL_CAN2.RecBuf[3] = 0;
	MSG_SERIAL_CAN2.RecBuf[6] = 0;
	MSG_SERIAL_CAN2.RecTimer = 0;
	MSG_SERIAL_CAN2.RecCount = 0; // 清接收数据计数器
	MSG_SERIAL_CAN2.RecOver = 0;  // 允许接数据
								  // MSG_SERIAL_CAN2.UARTx=0;
}

// CRC计算
static UINT16 Modbus_crc_chk(UINT8 *data, UINT16 length)
{
	int j;
	UINT16 reg_crc = 0xffff;
	while (length--)
	{
		reg_crc ^= *data++;
		for (j = 0; j < 8; j++)
		{
			if (reg_crc & 0x01)
			{
				reg_crc = (reg_crc >> 1) ^ 0xA001;
			}
			else
			{
				reg_crc = reg_crc >> 1;
			}
		}
	}
	return reg_crc;
}
// 启动串口发送数据
// Num为发送的字节数量不含2字节CRC
void Modbus_SerialStartSend(MSG *pMSG, UINT8 *pData, UINT16 Num)
{
	UINT8 i;
	UINT16 DataCRC = 0;
	if (RS485_DIR1 == 1)
	{
		if (pMSG->UARTx == 1)
		{
		//	RS485DIR1_Output_0_Hook();
		}
	}
	if (RS485_DIR2 == 1)
	{
		if (pMSG->UARTx == 2)
		{
		//	RS485DIR2_Output_0_Hook();
		}
	}
	if (RS485_DIR3 == 1)
	{
		if (pMSG->UARTx == 3)
		{
	//		RS485DIR3_Output_0_Hook();
		}
	}
	if (RS485_DIR4 == 1)
	{
		if (pMSG->UARTx == 4)
		{
		//	RS485DIR4_Output_0_Hook();
		}
	}
#if ((CAN1_ON == 1) || (CAN2_ON == 1))
	Modbus_CAN_SendDataToCan(pMSG); // CAN发送
#endif
	DataCRC = Modbus_crc_chk(pData, Num);
	*(pData + Num) = DataCRC;
	*(pData + Num + 1) = DataCRC >> 8;
	for (i = 0; i < (Num + 2); i++)
	{
		(*pMSG).SendBuf[i] = *(pData + i);
	}
	(*pMSG).SendCount = Num + 2;
	//if (_UART1)
	{
		if (pMSG->UARTx == 1)
		{
			RX1IE_DIS;
			TX1IE_EN;
		} // 禁止接收数据 使能串口发送中断
	}
//	if (_UART2)
	{
		if (pMSG->UARTx == 2)
		{
			RX2IE_DIS;
			TX2IE_EN;
		} // 禁止接收数据 使能串口发送中断
	}
//	if (_UART3)
//	{
//		if (pMSG->UARTx == 3)
//		{
//			RX3IE_DIS;
//			TX3IE_EN;
//		} // 禁止接收数据 使能串口发送中断
//	}
//	if (_UART4)
//	{
//		if (pMSG->UARTx == 4)
//		{
//			RX4IE_DIS;
//			TX4IE_EN;
//		} // 禁止接收数据 使能串口发送中断
//	}
	MSG_SERIAL_UART1_SleepFlag = 0;
	MSG_SERIAL_UART1.SleepTime = 0;
}


// 发送错误代码
void Modbus_SendError(MSG *pMSG, UINT8 cmd, UINT8 bype)
{
	// UINT8 sendData[5];
	SendDataBuff[0] = ADDR;
	SendDataBuff[1] = cmd | 0x80;
	SendDataBuff[2] = bype;
	Modbus_SerialStartSend(pMSG, SendDataBuff, 3);
}
// 写入 len寄存器的数量
//void UserWriteDataToAddr(MSG *pMSG, UINT16 StartAddr, UINT8 *pdata, UINT8 RegNum)
//{
//	

//	UINT16 i, X, N;
//	UINT16 nAddr = 0;
//	UINT8 chkSumdata = 0;
//	UINT8 WriteErrFlag = 0; // 写入错误标志
//	X = TTemp_count + MOS_OT + E_OT;
//	N = TCell_count;
//	for (i = 0; i < RegNum; i++)
//	{
//		nAddr = StartAddr + i; // 寄存器地址
//		if ((nAddr >= (0x1B + N + X)) && (nAddr <= (0x21 + N + X)))
//		{
//			if (nAddr == (0x1B + N + X)) // MOS控制  /******************根据当前项目进行修改*********************/
//			{
//				if (*(pdata + (i << 1) + 1) & 0x01) // 允许放电
//				{
//					Guset_CMDDSGFET_EN = 1;
//				//	DSGFET_ON();
//				}
//				else // 禁止放电
//				{
//					Guset_CMDDSGFET_EN = 0;
//				//	DSGFET_OFF();
//				}
//				if (*(pdata + (i << 1) + 1) & 0x02) // 允许充电
//				{
//					Guset_CMDCHGFET_EN = 1;
//				//	CHGFET_ON();
//				}
//				else // 禁止充电
//				{
//					Guset_CMDCHGFET_EN = 0;
//				//	CHGFET_OFF();
//				}
//			}
//			else if (nAddr == (0x1C + N + X)) // 加热控制 /******************根据当前项目进行修改*********************/
//			{
//				if (*(pdata + (i << 1) + 1) & 0x01) // 加热开
//				{
//					Guset_Heat_EN = 1;
//					// 打开加热
//				}
//				else
//				{
//					Guset_Heat_EN = 0;
//					// 关闭加热
//				}
//			}
//			else if (nAddr == (0x20 + N + X)) // GPS电源控制 /******************根据当前项目进行修改*********************/
//			{
//				if (*(pdata + (i << 1) + 1) & 0x01) // GPS电源开
//				{
//					Guset_CMDGPSPOWER_EN = 1;
//					// 打开GPS电源
//				}
//				else
//				{
//					Guset_CMDGPSPOWER_EN = 0;
//					// 关闭GPS电源
//				}
//			}
//			else if (nAddr == (0x21 + N + X)) // RTC 设置
//			{
////				if (RTCC)
////				{
////					RTC_SetTime(*(pdata + (i << 1)), *(pdata + (i << 1) + 1), *(pdata + (i << 1) + 2), *(pdata + (i << 1) + 3), *(pdata + (i << 1) + 4), *(pdata + (i << 1) + 5));
////					RTC_GetTime();
////				}
//			}
//		}
//		// 基本配置参数
//		if ((nAddr >= (0x45 + N + X)) && (nAddr <= (0x53 + N + X)))
//		{
//			WriteEepromFlag |= 0x01;
//			if (nAddr == (0x45 + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 250))
//				{
//					WriteErrFlag = 3;
//				} // 超范围
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 50))
//				{
//					WriteErrFlag = 3;
//				}												 // 超范围
//				ReadCfgData[1] = *(pdata + (i << 1)) - 1;		 // 充电过流
//				ReadCfgData[22] = (*(pdata + (i << 1) + 1)) - 1; // 充电过流延时
//			}
//			else if (nAddr == (0x46 + N + X))
//			{
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 100))
//				{
//					WriteErrFlag = 3;
//				}												// 超范围
//				ReadCfgData[2] = *(pdata + (i << 1));			// 电芯过压
//				ReadCfgData[3] = (*(pdata + (i << 1) + 1)) - 1; // 过压延时
//			}
//			else if (nAddr == (0x47 + N + X))
//			{
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 100))
//				{
//					WriteErrFlag = 3;
//				}											  // 超范围
//				ReadCfgData[4] = *(pdata + (i << 1));		  // 电芯过放
//				ReadCfgData[5] = *(pdata + (i << 1) + 1) - 1; // 过放延时
//			}
//			else if (nAddr == (0x48 + N + X))
//			{
//				ReadCfgData[6] = *(pdata + (i << 1));	  // 过压滞后电压
//				ReadCfgData[7] = *(pdata + (i << 1) + 1); // 过放滞后电压
//			}
//			else if (nAddr == (0x49 + N + X))
//			{
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 100))
//				{
//					WriteErrFlag = 3;
//				}											   // 超范围
//				ReadCfgData[25] = *(pdata + (i << 1)) - 1;	   // 电芯过压恢复延时
//				ReadCfgData[26] = *(pdata + (i << 1) + 1) - 1; // 电芯过放恢复延时
//			}
//			else if (nAddr == (0x4F + N + X))
//			{
//				if ((*(pdata + (i << 1) + 1) <= 1) || (*(pdata + (i << 1) + 1) > 100))
//				{
//					WriteErrFlag = 3;
//				}											   // 超范围
//				ReadCfgData[18] = *(pdata + (i << 1));		   // 均衡开启电压
//				ReadCfgData[19] = *(pdata + (i << 1) + 1) - 2; // 均衡开启压差
//			}
//			else if (nAddr == (0x50 + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 250))
//				{
//					WriteErrFlag = 3;
//				} // 超范围
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 120))
//				{
//					WriteErrFlag = 3;
//				}											   // 超范围
//				ReadCfgData[20] = *(pdata + (i << 1)) - 1;	   // 放电过流1
//				ReadCfgData[21] = *(pdata + (i << 1) + 1) - 1; // 放电过流1延时
//			}
//			// 放电过流2 放电过流2延时 放电高温保护 放电高温保护恢复 放电低低温保护 充电高温保护 充电高温保护恢复 充电低温保护 充电低温保护恢复
//			if ((nAddr >= (0x4A + N + X)) && (nAddr <= (0x4E + N + X)))
//			{
//				ReadCfgData[8 + ((nAddr << 1) - ((0x4A + N + X) << 1))] = *(pdata + (i << 1));
//				ReadCfgData[9 + ((nAddr << 1) - ((0x4A + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//			// 放电短路保护 放电短路保护延时 环境高温保护 环境高温保护恢复 环境低温保护 环境低温保护恢复
//			if ((nAddr >= (0x51 + N + X)) && (nAddr <= (0x53 + N + X)))
//			{
//				ReadCfgData[23 + ((nAddr << 1) - ((0x51 + N + X) << 1))] = *(pdata + (i << 1));
//				ReadCfgData[24 + ((nAddr << 1) - ((0x51 + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//		}
//		// 扩展配置参数
//		if ((nAddr >= (0x54 + N + X)) && (nAddr <= (0x5B + N + X)))
//		{
//			WriteEepromFlag |= 0x02;
//			if (nAddr == (0x5B + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 250))
//				{
//					WriteErrFlag = 3;
//				}											// 超范围
//				ReadCfgEData[25] = *(pdata + (i << 1)) - 1; // MOS高温保护延时
//			}
//			// 总压过压保护 总压过压保护恢复 总压过放保护 总压过放恢复
//			if ((nAddr >= (0x54 + N + X)) && (nAddr <= (0x57 + N + X)))
//			{
//				ReadCfgEData[2 + ((nAddr << 1) - ((0x54 + N + X) << 1))] = *(pdata + (i << 1));
//				ReadCfgEData[3 + ((nAddr << 1) - ((0x54 + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//			// 总压过压保护延时 总压过放保护延时 总过压恢复延时 总过放恢复延时 MOS高温保护 MOS高温保护恢复
//			if (nAddr == (0x58 + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 30))
//				{
//					WriteErrFlag = 3;
//				} // 超范围
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 30))
//				{
//					WriteErrFlag = 3;
//				} // 超范围
//			}
//			if (nAddr == (0x59 + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 50))
//				{
//					WriteErrFlag = 3;
//				} // 超范围
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 50))
//				{
//					WriteErrFlag = 3;
//				} // 超范围
//			}
//			if (nAddr == (0x5A + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 120))
//				{
//					WriteErrFlag = 3;
//				} // 超范围
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 120))
//				{
//					WriteErrFlag = 3;
//				} // 超范围
//			}
//			if ((nAddr >= (0x58 + N + X)) && (nAddr <= (0x5A + N + X)))
//			{
//				ReadCfgEData[2 + ((nAddr << 1) - ((0x58 + N + X) << 1))] = *(pdata + (i << 1)) - 1;
//				ReadCfgEData[3 + ((nAddr << 1) - ((0x58 + N + X) << 1))] = *(pdata + (i << 1) + 1) - 1;
//			}
//		}
//		if ((nAddr == (0x60 + N + X)) && ((*(pdata + (i << 1))) & 0x01)) // 使能设置
//		{
//			WriteEepromFlag |= 0x02;
//			if ((*(pdata + (i << 1))) & 0x01) // 总压保护开
//			{
//				ReadCfgEData[1] |= 0x01; //
//			}
//			else
//			{
//				ReadCfgEData[1] &= (~0x01); // 总压保护设置关
//			}
//		}
//		// 电量数据参数
//		if ((nAddr >= (0x5C + N + X)) && (nAddr <= (0x5E + N + X)))
//		{
//			WriteEepromFlag |= 0x04;
//			if (nAddr == (0x5E + N + X))
//			{
//				ReadFuelData[10] = *(pdata + (i << 1)) - 1; // 充满保护 延时
//			}
//			// 充满保护 总压高于 电流低于
//			if ((nAddr >= (0x5C + N + X)) && (nAddr <= (0x5D + N + X)))
//			{
//				ReadFuelData[0 + ((nAddr << 1) - ((0x5C + N + X) << 1))] = *(pdata + (i << 1));
//				ReadFuelData[1 + ((nAddr << 1) - ((0x5C + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//		}
//		//告警参数
//		if ((nAddr >= (0x5F + N + X)) && (nAddr <= (0x6B + N + X)))
//		{
//			WriteEepromFlag |= 0x08;
//			// switch(nAddr)
//			//{
//			if (nAddr == (0x5F + N + X))
//			{
//				ReadAlamData[22] = *(pdata + (i << 1));		// 加热/风扇开启温度
//				ReadAlamData[23] = *(pdata + (i << 1) + 1); // 加热/风扇恢复温度
//			}
//			else if (nAddr == (0x60 + N + X)) // 使能设置
//			{
//				ReadAlamData[0] = *(pdata + (i << 1) + 1); // 告警使能
//			}
//			else if (nAddr == (0x6B + N + X))
//			{
//				ReadAlamData[21] = *(pdata + (i << 1)); // SOC低告警
//			}
//			//}
//			// 总压过压告警电压  总压过放告警电压 电芯过压告警电压 电芯过放告警电压 充电过流告警电流 放电过流告警电流
//			// 充电高温告警温度 放电低温告警温度 MOS过温告警温度 MOS过温告警恢复温度 电芯不均衡告警压差 不均衡告警恢复压差
//			// 环境高温告警 环境低温告警
//			if ((nAddr >= (0x61 + N + X)) && (nAddr <= (0x6A + N + X)))
//			{
//				ReadAlamData[1 + ((nAddr << 1) - ((0x61 + N + X) << 1))] = *(pdata + (i << 1));
//				ReadAlamData[2 + ((nAddr << 1) - ((0x61 + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//		}
//	}

//	// 回复写入成功
//	if (WriteErrFlag == 0)
//	{
//		//WriteEepromFlag <<= 4;
//	//	ModbusInitVal(); // 将参数写入EEPROM
//		SendDataBuff[0] = ADDR;
//		SendDataBuff[1] = 0x10;
//		SendDataBuff[2] = StartAddr >> 8;
//		SendDataBuff[3] = StartAddr;
//		SendDataBuff[4] = RegNum >> 8;
//		SendDataBuff[5] = RegNum;
//		Modbus_SerialStartSend(pMSG, SendDataBuff, 6); // 回复写入成功
//	}
//	else // 写入失败
//	{
//		WriteEepromFlag = 0; // 清除写标志
//		// 重新初始化变量
////		InitBaskVal();								// 基本参数
////		InitExpandVal();							// 扩展参数
////		InitAlamVal();								// 告警参数
////		InitCap();									// 电量参数
//		Modbus_SendError(pMSG, 0x10, WriteErrFlag); // 返回写入失败原因
//		WriteErrFlag = 0;							// 清除失败标志
//	}
//}


// 地址数据编码  1秒调用一次
void ModbusSendDataCode(void)
{
	UINT16 data = 0, i;
	UINT8 N = 0, X = 0;
	UINT32 U32data = 0;
	UINT32 BalanceStates = 0;
	// 电池包串数
	Modbus_AddrData[0x00][0] = 0;
	Modbus_AddrData[0x00][1] = TCell_count;
	// 温度探头总数
	Modbus_AddrData[0x01][0] = 0;
	Modbus_AddrData[0x01][1] = TTemp_count + MOS_OT + E_OT;
	// 电芯电压
	for (i = 0; i < TCell_count; i++)
	{
		data = (V_CB.CellVlg[i + 1] + 0.0005f) * 1000;
		Modbus_AddrData[0x02 + i][0] = (data >> 8);
		Modbus_AddrData[0x02 + i][1] = data;
	}
	N = TCell_count;
	// 当前电流
	if (F_CB.DSG_FLAG) // 如果在放电
	{
		data = (UINT16)(C_CB.DSGCur * 100);
		data = ~data + 1; // 转化为负数
	}
	else if (F_CB.CHG_FLAG) // 如果在充电
	{
		data = (UINT16)(C_CB.CHGCur * 100);
	}
	else
	{
		data = 0;
	}
	Modbus_AddrData[0x02 + N][0] = (data >> 8);
	Modbus_AddrData[0x02 + N][1] = data;
	// state1
	data = 0;
	if (F_CB.DSG_FLAG)
	{
		data |= 0x0001;
	} // 放电
	if (F_CB.CHG_FLAG)
	{
		data |= 0x0002;
	} // 充电
	if (F_CB.CHG_FLAG)
	{
		data |= 0x0004;
	} // 充电器已连接   /******************根据当前项目进行修改*********************/
	if (MOS_OT)
	{
		data |= 0x0010;
	} // 有环MOS温度
	if (E_OT)
	{
		data |= 0x0020;
	} // 有环境温度
	if (F_CB.OV_FLAG & 0x01)
	{
		data |= 0x0100;
	} // 电芯过压保护
	if (F_CB.OV_FLAG & 0x02)
	{
		data |= 0x0200;
	} // 总压过压保护
	if (F_CB.OV_FLAG & 0x10)
	{
		data |= 0x1000;
	} // 充满保护
	Modbus_AddrData[0x03 + N][0] = (data >> 8);
	Modbus_AddrData[0x03 + N][1] = data;
	// state2
	data = 0;
	if (F_CB.UV_FLAG & 0x01)
	{
		data |= 0x0001;
	} // 电芯欠压保护
	if (F_CB.UV_FLAG & 0x02)
	{
		data |= 0x0002;
	} // 总压欠压保护
	if ((F_CB.OT_FLAG & 0x11) == 0x11)
	{
		data |= 0x0100;
	} // 充电高温保护
	if ((F_CB.OT_FLAG & 0x21) == 0x21)
	{
		data |= 0x0200;
	} // 充电低温保护
	if (F_CB.OTMOS_FLAG)
	{
		data |= 0x0400;
	} // MOS高温保护
	if ((F_CB.OT_FLAG & 0x12) == 0x12)
	{
		data |= 0x1000;
	} // 放电高温保护
	if ((F_CB.OT_FLAG & 0x22) == 0x22)
	{
		data |= 0x2000;
	} // 放电低温保护
	Modbus_AddrData[0x04 + N][0] = (data >> 8);
	Modbus_AddrData[0x04 + N][1] = data;
	// state3
	data = 0;
	if (F_CB.OC_SC_FLAG & 0x01)
	{
		data |= 0x0001;
	} // 放电短路保护
	if (F_CB.OC_SC_FLAG & 0x02)
	{
		data |= 0x0002;
	} // 放电过流保护
	if (F_CB.OC_SC_FLAG & 0x04)
	{
		data |= 0x0004;
	} // 充电过流保护
	if (F_CB.EVOT_FLAG & 0x01)
	{
		data |= 0x0010;
	} // 环境高温保护
	if (F_CB.EVOT_FLAG & 0x02)
	{
		data |= 0x0020;
	} // 环境低温保护
	Modbus_AddrData[0x05 + N][0] = (data >> 8);
	Modbus_AddrData[0x05 + N][1] = data;
	// 电芯温度
	for (i = 0; i < TTemp_count; i++)
	{
		data = V_CB.TemReg[i + 1] + 40;
		Modbus_AddrData[0x05 + N + 1 + i][0] = (data >> 8);
		Modbus_AddrData[0x05 + N + 1 + i][1] = data;
	}
	// MOS温度
	if (MOS_OT == 1)
	{
		data = OT_CB.MosTemp + 40;
		Modbus_AddrData[0x05 + N + TTemp_count + MOS_OT][0] = (data >> 8);
		Modbus_AddrData[0x05 + N + TTemp_count + MOS_OT][1] = data;
	}
	X = TTemp_count + MOS_OT + E_OT;
	// 环境温度
	if (E_OT == 1)
	{
		data = V_CB.EnvironmentTemp + 40;
		Modbus_AddrData[0x05 + N + X][0] = (data >> 8);
		Modbus_AddrData[0x05 + N + X][1] = data;
	}
	BalanceStates = BLA_CB.BCellData[1];
	// 均衡状态1
	Modbus_AddrData[0x06 + N + X][0] = (BalanceStates >> 8);
	Modbus_AddrData[0x06 + N + X][1] = BalanceStates;
	// 均衡状态2
	Modbus_AddrData[0x07 + N + X][0] = (BalanceStates >> 24);
	Modbus_AddrData[0x07 + N + X][1] = (BalanceStates >> 16);
	// 软件版本
	Modbus_AddrData[0x08 + N + X][0] = (VERSION + 0.01f) * 10;
	// 硬件版本
	Modbus_AddrData[0x08 + N + X][1] = Hardware_VER;
	// 状态
	data = 0;
	if (F_CB.DSG_EN_FLAG)
	{
		data |= 0x0002;
	} // 放电MOS开
	if (F_CB.CHG_EN_FLAG)
	{
		data |= 0x0004;
	} // 充电MOS开
	if (F_CB.TempFail_FLAG)
	{
		data |= 0x0100;
	} // 温度采集失效
	if (F_CB.VlgFail_FLAG)
	{
		data |= 0x0200;
	} // 电压采集失效
	if (F_CB.DSGFail_FLAG)
	{
		data |= 0x0400;
	} // 放电MOS失效 损坏
	if (F_CB.CHGFail_FLAG)
	{
		data |= 0x0800;
	} // 充电MOS失效 损坏
	if (F_CB.IMBALANCE_ALAM_FLAG)
	{
		data |= 0x1000;
	} // 电芯不均衡告警
	if (F_CB.OTD_ALAM_FLAG & 0x10)
	{
		data |= 0x4000;
	} // 放电低温告警
	if (F_CB.OTC_ALAM_FLAG & 0x10)
	{
		data |= 0x8000;
	} // 充电低温告警
	Modbus_AddrData[0x09 + N + X][0] = (data >> 8);
	Modbus_AddrData[0x09 + N + X][1] = data;
	// 告警状态
	data = 0;
	if (F_CB.UV_ALAM_FLAG)
	{
		data |= 0x0001;
	} // 电芯过放告警
	if (F_CB.TUV_ALAM_FLAG)
	{
		data |= 0x0002;
	} // 总压过放告警
	if (F_CB.OV_ALAM_FLAG)
	{
		data |= 0x0004;
	} // 电芯过压告警
	if (F_CB.TOV_ALAM_FLAG)
	{
		data |= 0x0008;
	} // 总压过压告警
	if (F_CB.DSGOCALAM_FLAG)
	{
		data |= 0x0010;
	} // 放电过流告警
	if (F_CB.CHGOCALAM_FLAG)
	{
		data |= 0x0020;
	} // 充电过流告警
	if (F_CB.OTD_ALAM_FLAG & 0x01)
	{
		data |= 0x0040;
	} // 放电高温告警
	if (F_CB.OTC_ALAM_FLAG & 0x01)
	{
		data |= 0x0080;
	} // 充电高温告警
	if (F_CB.EVOT_ALAM_FLAG & 0x01)
	{
		data |= 0x0100;
	} // 环境高温告警
	if (F_CB.EVOT_ALAM_FLAG & 0x02)
	{
		data |= 0x0200;
	} // 环境低温告警
	if (F_CB.SOCL_ALAM_FLAG)
	{
		data |= 0x0400;
	} // SOC低告警
	if (F_CB.MOSOT_ALAM_FLAG)
	{
		data |= 0x0800;
	} // MOS高温告警
	Modbus_AddrData[0x0A + N + X][0] = (data >> 8);
	Modbus_AddrData[0x0A + N + X][1] = data;
	// 电量SOC
	Modbus_AddrData[0x0B + N + X][0] = 0;
	Modbus_AddrData[0x0B + N + X][1] = (SOC.VirtualPercentCap >> 1);
	// SOH;
	data = SOC.RemFullCap / SOC.RemFullCapDesign + 0.9f;
	if (data > 100)
	{
		data = 100;
	}
	Modbus_AddrData[0x0C + N + X][0] = 0;
	Modbus_AddrData[0x0C + N + X][1] = data;
	// 循环次数
	Modbus_AddrData[0x0D + N + X][0] = (SOC.CycleCount >> 8);
	Modbus_AddrData[0x0D + N + X][1] = SOC.CycleCount;
	// 电池包设容量
	U32data = SOC.RemFullCapDesign * (1 + 0.000001f);
	U32data *= 100;
	Modbus_AddrData[0x0E + N + X][0] = (U32data >> 24);
	Modbus_AddrData[0x0E + N + X][1] = (U32data >> 16);
	Modbus_AddrData[0x0F + N + X][0] = (U32data >> 8);
	Modbus_AddrData[0x0F + N + X][1] = U32data;
	// 当前电池满容量
	U32data = SOC.RemFullCap * (1 + 0.000001f);
	Modbus_AddrData[0x10 + N + X][0] = (U32data >> 24);
	Modbus_AddrData[0x10 + N + X][1] = (U32data >> 16);
	Modbus_AddrData[0x11 + N + X][0] = (U32data >> 8);
	Modbus_AddrData[0x11 + N + X][1] = U32data;
	// 电池剩余容量
	if ((float)SOC.RemCap > (long int)0)
	{
		U32data = SOC.RemCap;
	}
	else
	{
		U32data = 0;
	}
	if (U32data > SOC.RemFullCap) // 防止超出满容量
	{
		U32data = SOC.RemFullCap;
	}
	U32data = U32data * (1 + 0.000001f);
	Modbus_AddrData[0x12 + N + X][0] = (U32data >> 24);
	Modbus_AddrData[0x12 + N + X][1] = (U32data >> 16);
	Modbus_AddrData[0x13 + N + X][0] = (U32data >> 8);
	Modbus_AddrData[0x13 + N + X][1] = U32data;
	// 放电剩余时间
	Modbus_AddrData[0x14 + N + X][0] = (SOC_CB.DSGRemTime >> 8);
	Modbus_AddrData[0x14 + N + X][1] = SOC_CB.DSGRemTime;
	// 充电剩余时间
	Modbus_AddrData[0x15 + N + X][0] = (SOC_CB.CHGRemTime >> 8);
	Modbus_AddrData[0x15 + N + X][1] = SOC_CB.CHGRemTime;
	// 当前充电间隔
	Modbus_AddrData[0x16 + N + X][0] = (SOC_CB.CHGTimeInterval >> 8);
	Modbus_AddrData[0x16 + N + X][1] = SOC_CB.CHGTimeInterval;
	// 最长充电间隔
	Modbus_AddrData[0x17 + N + X][0] = (SOC_CB.CHGTimeIntervaler >> 8);
	Modbus_AddrData[0x17 + N + X][1] = SOC_CB.CHGTimeIntervaler;
	// 电池总电压
	data = V_CB.TotalVlg * 100;
	Modbus_AddrData[0x18 + N + X][0] = (data >> 8);
	Modbus_AddrData[0x18 + N + X][1] = data;
	// 电池包最高电压
	data = OV_CB.HVlg * 1000;
	Modbus_AddrData[0x19 + N + X][0] = (data >> 8);
	Modbus_AddrData[0x19 + N + X][1] = data;
	// 电池包最低电压
	data = UV_CB.LVlg * 1000;
	Modbus_AddrData[0x1A + N + X][0] = (data >> 8);
	Modbus_AddrData[0x1A + N + X][1] = data;
	// MOS控制
	data = 0;
	if (Guset_CMDDSGFET_EN)
	{
		data |= 0x0001;
	} // 放电MOS明年
	if (Guset_CMDCHGFET_EN)
	{
		data |= 0x0002;
	} // 充电MOS命令
	Modbus_AddrData[0x1B + N + X][0] = data >> 8;
	Modbus_AddrData[0x1B + N + X][1] = data;
	// 加热控制
	data = 0;
	if (Guset_Heat_EN)
	{
		data = 0x0001;
	}
	Modbus_AddrData[0x1C + N + X][0] = data >> 8;
	Modbus_AddrData[0x1C + N + X][1] = data;
	// 最大允许充电电流 单位10mA
	data = SOC.RemFullCapDesign >> 1; // 0.5C /*******************根据需要修改**********************/
	Modbus_AddrData[0x1D + N + X][0] = data >> 8;
	Modbus_AddrData[0x1D + N + X][1] = data;
	// 标准充电电压 单位mV
//	if (OV_VLG_2 > 4.1f)
//	{
//		data = 420 * TCell_count;
//	} // 三元电池 充电电压4.2V
//	else
//	{
//		data = 360 * TCell_count;
//	} // 铁锂电池 充电电压3.6
	Modbus_AddrData[0x1E + N + X][0] = data >> 8;
	Modbus_AddrData[0x1E + N + X][1] = data;
	// 当前湿度
	Modbus_AddrData[0x1F + N + X][0] = 0;
	Modbus_AddrData[0x1F + N + X][1] = 0;
	// GPS模块电源控制
	data = 0;
	if (Guset_CMDGPSPOWER_EN)
	{
		data = 0x0001;
	}
	Modbus_AddrData[0x20 + N + X][0] = data >> 8;
	Modbus_AddrData[0x20 + N + X][1] = data;
	// RTC
	if (RTCC)
	{
	//	RTC_GetTime();
		Modbus_AddrData[0x21 + N + X][0] = RTCC_CB.year;
		Modbus_AddrData[0x21 + N + X][1] = RTCC_CB.month;
		Modbus_AddrData[0x22 + N + X][0] = RTCC_CB.day;
		Modbus_AddrData[0x22 + N + X][1] = RTCC_CB.hour;
		Modbus_AddrData[0x23 + N + X][0] = RTCC_CB.minute;
		Modbus_AddrData[0x23 + N + X][1] = RTCC_CB.Second;
	}
	else
	{
		Modbus_AddrData[0x21 + N + X][0] = 0;
		Modbus_AddrData[0x21 + N + X][1] = 0;
		Modbus_AddrData[0x22 + N + X][0] = 0;
		Modbus_AddrData[0x22 + N + X][1] = 0;
		Modbus_AddrData[0x23 + N + X][0] = 0;
		Modbus_AddrData[0x23 + N + X][1] = 0;
	}
	// 电池包编码
	if (ProductCode[0] < 32)
	{
		for (i = 0; i < ProductCode[0]; i++) // 取出对应字节数量的编码
		{
			*((UINT8 *)Modbus_AddrData + ((0x24 + N + X) << 1) + i) = ProductCode[i + 1];
		}
	}
	else
	{
		ProductCode[0] = 0;
	}
	for (i = ProductCode[0]; i < 32; i++) // 不足32字节补0
	{
		*((UINT8 *)Modbus_AddrData + ((0x24 + N + X + ProductCode[0]) << 1) + i) = 0;
	}
	/***************************预留32字节*******************************/

	/********************************保护参数**********************************/
	// 电流采集电阻
	data = (0.1 + 0.00001f) * 100000;
	Modbus_AddrData[0x44 + N + X][0] = (data >> 8);
	Modbus_AddrData[0x44 + N + X][1] = data;
	// 充电过流保护
	Modbus_AddrData[0x45 + N + X][0] = ReadCfgData[1] + 1;	//
															// 充电过流延时
	Modbus_AddrData[0x45 + N + X][1] = ReadCfgData[22] + 1; //
															// 电芯过压保护
	Modbus_AddrData[0x46 + N + X][0] = ReadCfgData[2];
	// 过压保护延时
	Modbus_AddrData[0x46 + N + X][1] = ReadCfgData[3];
	// 电芯过放保护
	Modbus_AddrData[0x47 + N + X][0] = ReadCfgData[4];
	// 过放保护延时
	Modbus_AddrData[0x47 + N + X][1] = ReadCfgData[5];
	// 过压滞后电压
	Modbus_AddrData[0x48 + N + X][0] = ReadCfgData[6];
	// 过放滞后电压
	Modbus_AddrData[0x48 + N + X][1] = ReadCfgData[7];
	// 过压恢复延时
	Modbus_AddrData[0x49 + N + X][0] = ReadCfgData[25] + 1;
	// 过放恢复延时
	Modbus_AddrData[0x49 + N + X][1] = ReadCfgData[26] + 1;
	// 放电过流2
	Modbus_AddrData[0x4A + N + X][0] = ReadCfgData[8];
	// 放电过流2延时
	Modbus_AddrData[0x4A + N + X][1] = ReadCfgData[9];
	// 放电高温保护
	Modbus_AddrData[0x4B + N + X][0] = ReadCfgData[10];
	// 放电高温保护恢复
	Modbus_AddrData[0x4B + N + X][1] = ReadCfgData[11];
	// 放电低低温保护
	Modbus_AddrData[0x4C + N + X][0] = ReadCfgData[12];
	// 放电低温保护恢复
	Modbus_AddrData[0x4C + N + X][1] = ReadCfgData[13];
	// 充电高温保护
	Modbus_AddrData[0x4D + N + X][0] = ReadCfgData[14];
	// 充电高温保护恢复
	Modbus_AddrData[0x4D + N + X][1] = ReadCfgData[15];
	// 充电低温保护
	Modbus_AddrData[0x4E + N + X][0] = ReadCfgData[16];
	// 充电低温保护恢复
	Modbus_AddrData[0x4E + N + X][1] = ReadCfgData[17];
	// 均衡开启电压
	Modbus_AddrData[0x4F + N + X][0] = ReadCfgData[18];
	// 均衡开启压差
	Modbus_AddrData[0x4F + N + X][1] = ReadCfgData[19] + 2;
	// 放电过流1保护
	Modbus_AddrData[0x50 + N + X][0] = ReadCfgData[20] + 1;
	// 放电过流1延时
	Modbus_AddrData[0x50 + N + X][1] = ReadCfgData[21] + 1;
	// 放电短路保护
	Modbus_AddrData[0x51 + N + X][0] = ReadCfgData[23];
	// 放电短路保护延时
	Modbus_AddrData[0x51 + N + X][1] = ReadCfgData[24];
	// 环境高温保护
	Modbus_AddrData[0x52 + N + X][0] = ReadCfgData[27];
	// 环境高温保护恢复
	Modbus_AddrData[0x52 + N + X][1] = ReadCfgData[28];
	// 环境低温保护
	Modbus_AddrData[0x53 + N + X][0] = ReadCfgData[29];
	// 环境低温保护恢复
	Modbus_AddrData[0x53 + N + X][1] = ReadCfgData[30];
	// 总压过压保护
	Modbus_AddrData[0x54 + N + X][0] = ReadCfgEData[2];
	Modbus_AddrData[0x54 + N + X][1] = ReadCfgEData[3];
	// 总压过压保护恢复
	Modbus_AddrData[0x55 + N + X][0] = ReadCfgEData[4];
	Modbus_AddrData[0x55 + N + X][1] = ReadCfgEData[5];
	// 总压过放保护
	Modbus_AddrData[0x56 + N + X][0] = ReadCfgEData[6];
	Modbus_AddrData[0x56 + N + X][1] = ReadCfgEData[7];
	// 总压过放恢复
	Modbus_AddrData[0x57 + N + X][0] = ReadCfgEData[8];
	Modbus_AddrData[0x57 + N + X][1] = ReadCfgEData[9];
	// 总压过压保护延时
	Modbus_AddrData[0x58 + N + X][0] = ReadCfgEData[10] + 1;
	// 总压过放保护延时
	Modbus_AddrData[0x58 + N + X][1] = ReadCfgEData[11] + 1;
	// 总过压恢复延时
	Modbus_AddrData[0x59 + N + X][0] = ReadCfgEData[18] + 1;
	// 总过放恢复延时
	Modbus_AddrData[0x59 + N + X][1] = ReadCfgEData[19] + 1;
	// MOS高温保护
	Modbus_AddrData[0x5A + N + X][0] = ReadCfgEData[23] + 1;
	// MOS高温保护恢复
	Modbus_AddrData[0x5A + N + X][1] = ReadCfgEData[24] + 1;
	// MOS高温保护延时
	Modbus_AddrData[0x5B + N + X][0] = ReadCfgEData[25] + 1;
	Modbus_AddrData[0x5B + N + X][1] = 0;
	// 充满保护 总压高于
	Modbus_AddrData[0x5C + N + X][0] = ReadFuelData[0];
	Modbus_AddrData[0x5C + N + X][1] = ReadFuelData[1];
	// 充满保护 电流低于
	Modbus_AddrData[0x5D + N + X][0] = ReadFuelData[2];
	Modbus_AddrData[0x5D + N + X][1] = ReadFuelData[3];
	// 充满保护 延时
	Modbus_AddrData[0x5E + N + X][0] = ReadFuelData[10];
	Modbus_AddrData[0x5E + N + X][1] = 0;
	// 加热/风扇开启温度
	Modbus_AddrData[0x5F + N + X][0] = ReadAlamData[22];
	// 加热/风扇恢复温度
	Modbus_AddrData[0x5F + N + X][1] = ReadAlamData[23];
	// 使能设置
	Modbus_AddrData[0x60 + N + X][0] = 0x01 & ReadCfgEData[1]; // 总压保护设置
	Modbus_AddrData[0x60 + N + X][1] = ReadAlamData[0];
	// 总压过压告警电压
	Modbus_AddrData[0x61 + N + X][0] = ReadAlamData[1];
	Modbus_AddrData[0x61 + N + X][1] = ReadAlamData[2];
	// 总压过放告警电压
	Modbus_AddrData[0x62 + N + X][0] = ReadAlamData[3];
	Modbus_AddrData[0x62 + N + X][1] = ReadAlamData[4];
	// 电芯过压告警电压
	Modbus_AddrData[0x63 + N + X][0] = ReadAlamData[5];
	// 电芯过放告警电压
	Modbus_AddrData[0x63 + N + X][1] = ReadAlamData[6];
	// 充电过流告警电流
	Modbus_AddrData[0x64 + N + X][0] = ReadAlamData[7];
	// 放电过流告警电流
	Modbus_AddrData[0x64 + N + X][1] = ReadAlamData[8];
	// 充电高温告警温度
	Modbus_AddrData[0x65 + N + X][0] = ReadAlamData[9];
	// 充电低温告警温度
	Modbus_AddrData[0x65 + N + X][1] = ReadAlamData[10];
	// 放电高温告警温度
	Modbus_AddrData[0x66 + N + X][0] = ReadAlamData[11];
	// 放电低温告警温度
	Modbus_AddrData[0x66 + N + X][1] = ReadAlamData[12];
	// MOS过温告警温度
	Modbus_AddrData[0x67 + N + X][0] = ReadAlamData[13];
	// MOS过温告警恢复温度
	Modbus_AddrData[0x67 + N + X][1] = ReadAlamData[14];
	// 电芯不均衡告警压差
	Modbus_AddrData[0x68 + N + X][0] = ReadAlamData[15];
	Modbus_AddrData[0x68 + N + X][1] = ReadAlamData[16];
	// 不均衡告警恢复压差
	Modbus_AddrData[0x69 + N + X][0] = ReadAlamData[17];
	Modbus_AddrData[0x69 + N + X][1] = ReadAlamData[18];
	// 环境高温告警
	Modbus_AddrData[0x6A + N + X][0] = ReadAlamData[19];
	// 环境低温告警
	Modbus_AddrData[0x6A + N + X][1] = ReadAlamData[20];
	// SOC低告警
	Modbus_AddrData[0x6B + N + X][0] = ReadAlamData[21];
	Modbus_AddrData[0x6B + N + X][1] = 0;
}

void Modbus_SendData(MSG *pMSG, UINT8 *pData)
{

	UINT16 StartAddr = 0;
	UINT16 RegNum = 0;
	UINT16 data = 0;
	UINT8 i = 0;
	StartAddr = *(pData + 2);
	StartAddr = (StartAddr << 8) | (*(pData + 3));
	RegNum = *(pData + 4);
	RegNum = (RegNum << 8) | (*(pData + 5));
	if ((StartAddr + RegNum - 1) > (0x6B + TCell_count + (TTemp_count + MOS_OT + E_OT)))
	{
		Modbus_SendError(pMSG, 0x03, 2);
		return;
	} // 地址不存在
	SendDataBuff[0] = ADDR;
	SendDataBuff[1] = 0x03;
	data = RegNum * 2;
	if (data > 250)
	{
		Modbus_SendError(pMSG, 0x03, 3);
		return;
	} // 非法操作数据
	SendDataBuff[2] = data;
	for (i = 0; i < RegNum; i++) // 将数据添加到发送缓存区
	{
		SendDataBuff[3 + i * 2] = Modbus_AddrData[StartAddr + i][0];
		SendDataBuff[4 + i * 2] = Modbus_AddrData[StartAddr + i][1];
	}
	Modbus_SerialStartSend(pMSG, SendDataBuff, data + 3);
}

// MUDBUS接收数据包校验
static UINT8 Modbus_UserRcvChk(UINT8 *pdata)
{

	UINT16 chkSum = 0;
	if (pdata[1] == 0x03)
	{
		chkSum = Modbus_crc_chk(&pdata[0], 6);
		if ((pdata[6] == (chkSum & 0x00ff)) && (pdata[7] == (chkSum >> 8)))
		{
			return 1;
		}
		else
		{
			return 0;
		} // 0
	}
	else if (pdata[1] == 0x10)
	{
		chkSum = Modbus_crc_chk(&pdata[0], pdata[6] + 7);
		if ((pdata[pdata[6] + 7] == (chkSum & 0x00ff)) && (pdata[pdata[6] + 8] == (chkSum >> 8)))
		{
			return 1;
		}
		else
		{
			return 0;
		} // 0
	}
	return 0;
}
// 解码 串口解码回调函数 或空闲任务调用
void Modbus_SerialDecode(void)
{
	// MODBUS协议解码
	//----------------------------MODBUS协议 UART1 缓存解码----------------------------/
	if (MSG_SERIAL_UART1.RecOver == 2) // Modbus读取数据包
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART1.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_UART1.UARTx = 1;									 // 端口号 告诉发送编码函数启动哪个端口进行发送
			Modbus_SendData(&MSG_SERIAL_UART1, MSG_SERIAL_UART1.RecBuf); // 解码 读取数据
		}
		Modbus_ClearBuff_UART1(); // 清缓存区
	}
	else if (MSG_SERIAL_UART1.RecOver == 3) // MOdbus写入数据
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART1.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_UART1.UARTx = 1;																																				   // 端口号 告诉发送编码函数启动哪个端口进行发送
		//	UserWriteDataToAddr(&MSG_SERIAL_UART1, (((UINT16)MSG_SERIAL_UART1.RecBuf[2]) << 8) | MSG_SERIAL_UART1.RecBuf[3], &MSG_SERIAL_UART1.RecBuf[7], MSG_SERIAL_UART1.RecBuf[5]); // 解码 写入数据
		}
		Modbus_ClearBuff_UART1(); // 清缓存区
	}
	//----------------------------MODBUS协议 UART2 缓存解码----------------------------/
	if (MSG_SERIAL_UART2.RecOver == 2) // Modbus读取数据包
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART2.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_UART2.UARTx = 2;									 // 端口号 告诉发送编码函数启动哪个端口进行发送
			Modbus_SendData(&MSG_SERIAL_UART2, MSG_SERIAL_UART2.RecBuf); // 解码 读取数据
		}
		Modbus_ClearBuff_UART2(); // 清缓存区
	}
	else if (MSG_SERIAL_UART2.RecOver == 3) // MOdbus写入数据
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART2.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_UART2.UARTx = 2;																																				   // 端口号 告诉发送编码函数启动哪个端口进行发送
		//	UserWriteDataToAddr(&MSG_SERIAL_UART2, (((UINT16)MSG_SERIAL_UART2.RecBuf[2]) << 8) | MSG_SERIAL_UART2.RecBuf[3], &MSG_SERIAL_UART2.RecBuf[7], MSG_SERIAL_UART2.RecBuf[5]); // 解码 写入数据
		}
		Modbus_ClearBuff_UART2(); // 清缓存区
	}
	//----------------------------MODBUS协议 UART3 缓存解码----------------------------/
	if (MSG_SERIAL_UART3.RecOver == 2) // Modbus读取数据包
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART3.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_UART3.UARTx = 3;									 // 端口号 告诉发送编码函数启动哪个端口进行发送
			Modbus_SendData(&MSG_SERIAL_UART3, MSG_SERIAL_UART3.RecBuf); // 解码 读取数据
		}
		Modbus_ClearBuff_UART3(); // 清缓存区
	}
	else if (MSG_SERIAL_UART3.RecOver == 3) // MOdbus写入数据
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART3.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_UART3.UARTx = 3;																																				   // 端口号 告诉发送编码函数启动哪个端口进行发送
	//		UserWriteDataToAddr(&MSG_SERIAL_UART3, (((UINT16)MSG_SERIAL_UART3.RecBuf[2]) << 8) | MSG_SERIAL_UART3.RecBuf[3], &MSG_SERIAL_UART3.RecBuf[7], MSG_SERIAL_UART3.RecBuf[5]); // 解码 写入数据
		}
		Modbus_ClearBuff_UART3(); // 清缓存区
	}
	//----------------------------MODBUS协议 UART4 缓存解码----------------------------/
	if (MSG_SERIAL_UART4.RecOver == 2) // Modbus读取数据包
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART4.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_UART4.UARTx = 4;									 // 端口号 告诉发送编码函数启动哪个端口进行发送
			Modbus_SendData(&MSG_SERIAL_UART4, MSG_SERIAL_UART4.RecBuf); // 解码 读取数据
		}
		Modbus_ClearBuff_UART4(); // 清缓存区
	}
	else if (MSG_SERIAL_UART4.RecOver == 3) // MOdbus写入数据
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART4.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_UART4.UARTx = 4;																																				   // 端口号 告诉发送编码函数启动哪个端口进行发送
		//	UserWriteDataToAddr(&MSG_SERIAL_UART4, (((UINT16)MSG_SERIAL_UART4.RecBuf[2]) << 8) | MSG_SERIAL_UART4.RecBuf[3], &MSG_SERIAL_UART4.RecBuf[7], MSG_SERIAL_UART4.RecBuf[5]); // 解码 写入数据
		}
		Modbus_ClearBuff_UART4(); // 清缓存区
	}
	//----------------------------MODBUS协议 CAN1 缓存解码----------------------------/
	if (MSG_SERIAL_CAN1.RecOver == 2) // Modbus读取数据包
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_CAN1.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_CAN1.UARTx = 5;								   // 端口号 告诉发送编码函数启动哪个端口进行发送
			Modbus_SendData(&MSG_SERIAL_CAN1, MSG_SERIAL_CAN1.RecBuf); // 解码 读取数据
		}
		Modbus_ClearBuff_CAN1(); // 清缓存区
	}
	else if (MSG_SERIAL_CAN1.RecOver == 3) // MOdbus写入数据
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_CAN1.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_CAN1.UARTx = 5;																																			  // 端口号 告诉发送编码函数启动哪个端口进行发送
		//	UserWriteDataToAddr(&MSG_SERIAL_CAN1, (((UINT16)MSG_SERIAL_CAN1.RecBuf[2]) << 8) | MSG_SERIAL_CAN1.RecBuf[3], &MSG_SERIAL_CAN1.RecBuf[7], MSG_SERIAL_CAN1.RecBuf[5]); // 解码 写入数据
		}
		Modbus_ClearBuff_CAN1(); // 清缓存区
	}
	//----------------------------MODBUS协议 CAN2 缓存解码----------------------------/
	if (MSG_SERIAL_CAN2.RecOver == 2) // Modbus读取数据包
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_CAN2.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_CAN2.UARTx = 6;								   // 端口号 告诉发送编码函数启动哪个端口进行发送
			Modbus_SendData(&MSG_SERIAL_CAN2, MSG_SERIAL_CAN2.RecBuf); // 解码 读取数据
		}
		Modbus_ClearBuff_CAN2(); // 清缓存区
	}
	else if (MSG_SERIAL_CAN2.RecOver == 3) // MOdbus写入数据
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_CAN2.RecBuf)) // CRC校验正确
		{
			MSG_SERIAL_CAN2.UARTx = 6;																																			  // 端口号 告诉发送编码函数启动哪个端口进行发送
	//		UserWriteDataToAddr(&MSG_SERIAL_CAN2, (((UINT16)MSG_SERIAL_CAN2.RecBuf[2]) << 8) | MSG_SERIAL_CAN2.RecBuf[3], &MSG_SERIAL_CAN2.RecBuf[7], MSG_SERIAL_CAN2.RecBuf[5]); // 解码 写入数据
		}
		Modbus_ClearBuff_CAN2(); // 清缓存区
	}
}


// 数据解码
void SerialDecodeHook(void)
{
 
/**************************UART1 上位机数据解码*********************/
    if(MSG_SERIAL_UART1.RecOver==1)//如果接收到完整的数据报
		{			
			if(MSG_SERIAL_UART1.RecBuf[0]==0xea)
			{
					if(MSG_SERIAL_UART1.RecBuf[1]==CID) //   
					{ 
							if(MSG_SERIAL_UART1.RecBuf[2]!=0xff)    // 
							{       
									if(MSG_SERIAL_UART1.RecBuf[2]!=ADR) 
									{
											ClrRcvBuf(&MSG_SERIAL_UART1);
											return;
									}   
							}      
							 MSG_SERIAL_UART1.UARTx=1; // 端口号
							 pMSGSERIAL= &MSG_SERIAL_UART1;  // 缓存区指针付给库
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_UART1); return; } // 校验  
							 SerialDecoding(&MSG_SERIAL_UART1.RecBuf[4]); // 解码上位机数据包
					}
			}else if(MSG_SERIAL_UART1.RecBuf[0]==0xeb) // 升级协议
			{
					if(MSG_SERIAL_UART1.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART1);return;} // 
					MSG_SERIAL_UART1.UARTx=1; // 数据端口号
					pMSGSERIAL= &MSG_SERIAL_UART1; // 缓存区指针付给库     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART1);} // 校验
					LoadDataRecode(); // 解码升级数据包        
			} 	
			else if(MSG_SERIAL_UART1.RecBuf[0]==0X6E) // 升级协议
			{
				//	if(MSG_SERIAL_UART1.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART1);return;} // 
					MSG_SERIAL_UART1.UARTx=1; // 数据端口号
					pMSGSERIAL= &MSG_SERIAL_UART1; // 缓存区指针付给库     
			//		if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART1);} // 校验
			//		LoadDataRecode(); // 解码升级数据包     
ModeBusRxUserHook(MSG_SERIAL_UART1.RecBuf,MSG_SERIAL_UART1.RecCount);	
			} 	
			ClrRcvBuf(&MSG_SERIAL_UART1); // 清缓存区域
	  }			
/**************************UART2 上位机数据解码*********************/
    if(MSG_SERIAL_UART2.RecOver==1)//如果接收到完整的数据报
		{			
			if(MSG_SERIAL_UART2.RecBuf[0]==0xea)
			{
					if(MSG_SERIAL_UART2.RecBuf[1]==CID) //   
					{ 
							if(MSG_SERIAL_UART2.RecBuf[2]!=0xff)    // 
							{       
									if(MSG_SERIAL_UART2.RecBuf[2]!=ADR) 
									{
											ClrRcvBuf(&MSG_SERIAL_UART2);
											return;
									}   
							}      
							 MSG_SERIAL_UART2.UARTx=2; // 端口号
							 pMSGSERIAL= &MSG_SERIAL_UART2;  // 缓存区指针付给库
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_UART2); return; } // 校验  
							 SerialDecoding(&MSG_SERIAL_UART2.RecBuf[4]); // 解码上位机数据包
					}
			}else if(MSG_SERIAL_UART2.RecBuf[0]==0xeb) // 升级协议
			{
					if(MSG_SERIAL_UART2.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART2);return;} // 
					MSG_SERIAL_UART2.UARTx=2; // 数据端口号
					pMSGSERIAL= &MSG_SERIAL_UART2; // 缓存区指针付给库     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART2);} // 校验
					LoadDataRecode(); // 解码升级数据包        
			} 	
			ClrRcvBuf(&MSG_SERIAL_UART2); // 清缓存区域
	  }	
/**************************UART3 上位机数据解码*********************/
    if(MSG_SERIAL_UART3.RecOver==1)//如果接收到完整的数据报
		{			
			if(MSG_SERIAL_UART3.RecBuf[0]==0xea)
			{
					if(MSG_SERIAL_UART3.RecBuf[1]==CID) //   
					{ 
							if(MSG_SERIAL_UART3.RecBuf[2]!=0xff)    // 
							{       
									if(MSG_SERIAL_UART3.RecBuf[2]!=ADR) 
									{
											ClrRcvBuf(&MSG_SERIAL_UART3);
											return;
									}   
							}      
							 MSG_SERIAL_UART3.UARTx=3; // 端口号
							 pMSGSERIAL= &MSG_SERIAL_UART3;  // 缓存区指针付给库
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_UART3); return; } // 校验  
							 SerialDecoding(&MSG_SERIAL_UART3.RecBuf[4]); // 解码上位机数据包
					}
			}else if(MSG_SERIAL_UART3.RecBuf[0]==0xeb) // 升级协议
			{
					if(MSG_SERIAL_UART3.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART3);return;} // 
					MSG_SERIAL_UART3.UARTx=3; // 数据端口号
					pMSGSERIAL= &MSG_SERIAL_UART3; // 缓存区指针付给库     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART3);} // 校验
					LoadDataRecode(); // 解码升级数据包        
			} 	
			ClrRcvBuf(&MSG_SERIAL_UART3); // 清缓存区域
	  }
/**************************UART4 上位机数据解码*********************/
    if(MSG_SERIAL_UART4.RecOver==1)//如果接收到完整的数据报
		{			
			if(MSG_SERIAL_UART4.RecBuf[0]==0xea)
			{
					if(MSG_SERIAL_UART4.RecBuf[1]==CID) //   
					{ 
							if(MSG_SERIAL_UART4.RecBuf[2]!=0xff)    // 
							{       
									if(MSG_SERIAL_UART4.RecBuf[2]!=ADR) 
									{
											ClrRcvBuf(&MSG_SERIAL_UART4);
											return;
									}   
							}      
							 MSG_SERIAL_UART4.UARTx=4; // 端口号
							 pMSGSERIAL= &MSG_SERIAL_UART4;  // 缓存区指针付给库
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_UART4); return; } // 校验  
							 SerialDecoding(&MSG_SERIAL_UART4.RecBuf[4]); // 解码上位机数据包
					}
			}else if(MSG_SERIAL_UART4.RecBuf[0]==0xeb) // 升级协议
			{
					if(MSG_SERIAL_UART4.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART4);return;} // 
					MSG_SERIAL_UART4.UARTx=4; // 数据端口号
					pMSGSERIAL= &MSG_SERIAL_UART4; // 缓存区指针付给库     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART4);} // 校验
					LoadDataRecode(); // 解码升级数据包        
			} 	
			ClrRcvBuf(&MSG_SERIAL_UART4); // 清缓存区域
	  }	
/**************************CAN1 上位机数据解码*********************/
    if(MSG_SERIAL_CAN1.RecOver==1)//如果接收到完整的数据报
		{			
			if(MSG_SERIAL_CAN1.RecBuf[0]==0xea)
			{
					if(MSG_SERIAL_CAN1.RecBuf[1]==CID) //   
					{ 
							if(MSG_SERIAL_CAN1.RecBuf[2]!=0xff)    // 
							{       
									if(MSG_SERIAL_CAN1.RecBuf[2]!=ADR) 
									{
											ClrRcvBuf(&MSG_SERIAL_CAN1);
											return;
									}   
							}      
							 MSG_SERIAL_CAN1.UARTx=5; // 端口号
							 pMSGSERIAL= &MSG_SERIAL_CAN1;  // 缓存区指针付给库
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_CAN1); return; } // 校验  
							 SerialDecoding(&MSG_SERIAL_CAN1.RecBuf[4]); // 解码上位机数据包
					}
			}else if(MSG_SERIAL_CAN1.RecBuf[0]==0xeb) // 升级协议
			{
					if(MSG_SERIAL_CAN1.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_CAN1);return;} // 
					MSG_SERIAL_CAN1.UARTx=5; // 数据端口号
					pMSGSERIAL= &MSG_SERIAL_CAN1; // 缓存区指针付给库     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_CAN1);} // 校验
					LoadDataRecode(); // 解码升级数据包        
			} 	
			ClrRcvBuf(&MSG_SERIAL_CAN1); // 清缓存区域
	  }		
/**************************CAN1 上位机数据解码*********************/
    if(MSG_SERIAL_CAN2.RecOver==1)//如果接收到完整的数据报
		{			
			if(MSG_SERIAL_CAN2.RecBuf[0]==0xea)
			{
					if(MSG_SERIAL_CAN2.RecBuf[1]==CID) //   
					{ 
							if(MSG_SERIAL_CAN2.RecBuf[2]!=0xff)    // 
							{       
									if(MSG_SERIAL_CAN2.RecBuf[2]!=ADR) 
									{
											ClrRcvBuf(&MSG_SERIAL_CAN2);
											return;
									}   
							}      
							 MSG_SERIAL_CAN2.UARTx=6; // 端口号
							 pMSGSERIAL= &MSG_SERIAL_CAN2;  // 缓存区指针付给库
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_CAN2); return; } // 校验  
							 SerialDecoding(&MSG_SERIAL_CAN2.RecBuf[4]); // 解码上位机数据包
					}
			}else if(MSG_SERIAL_CAN2.RecBuf[0]==0xeb) // 升级协议
			{
					if(MSG_SERIAL_CAN2.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_CAN2);return;} // 
					MSG_SERIAL_CAN2.UARTx=6; // 数据端口号
					pMSGSERIAL= &MSG_SERIAL_CAN2; // 缓存区指针付给库     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_CAN2);} // 校验
					LoadDataRecode(); // 解码升级数据包        
			} 	
			ClrRcvBuf(&MSG_SERIAL_CAN2); // 清缓存区域
	  }
   Modbus_SerialDecode(); //MODBUS协议解码		
}

