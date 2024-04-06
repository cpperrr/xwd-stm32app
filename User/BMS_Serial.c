#include "global.h"
extern void ModeBusRxUserHook(u8 *pRxdata, u8 len);
	static UINT8 SendDataBuff[255];
static   UINT8 Modbus_AddrData[128][2]; // ��ַ���ݴ洢��
MSG MSG_SERIAL_UART1; // ������S_RAM ����
MSG MSG_SERIAL_UART2; // ������S_RAM ����
MSG MSG_SERIAL_UART3; // ������S_RAM ����
MSG MSG_SERIAL_UART4; // ������S_RAM ����
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
// ��������У��
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
// ����У��
UINT16 LoadChkSum(UINT8 *pData, UINT8 count)
{
  UINT16 chkSum = 0;
  while (count--)
  {
    chkSum += (*pData++);
  }
  return (chkSum);
}


// ��������У��
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
// ����ջ����� ע���ڴ��ڽ����жϺ������治�ܵ��ô˺��� �����Լ�����д�������������
static void ClrRcvBuf(MSG *pMSG_SERIAL)
{	
 UINT16 i;
	
	(*pMSG_SERIAL).RecCount=0; // ��������ݼ�����
	(*pMSG_SERIAL).RecTimer=0; // ���ʱ��
	(*pMSG_SERIAL).RecOver=0;  // �����
	for(i=0;i<300;i++)
  (*pMSG_SERIAL).RecBuf[i]=0;
	
 
	//(*pMSG_SERIAL).UARTx=0;
}


// ������ȡ
void SerialDecoding(UINT8 *pData)
{
  switch (*pData)
  {
  case 0x04: // ��ص�ѹ(0x02),����(0x03),����(0x04),��������
    //SerialSendFuelGuest(0x04);
    break;
  case 0xff: // �ڲ�������
    switch (*(pData + 1))
    {
    case 0x00: // д���������к�
    //  WriteProductCode(*(pData + 2) + 1, pData + 2);
      break;
    case 0x01: // ��ȡ�������к�
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
    } // ��ֹ��������// ʹ�ܴ��ڷ����ж�
  }
 // if (_UART2)
  {
    if ((*pMSGSERIAL).UARTx == 2) // ��ֹ��������// ʹ�ܴ��ڷ����ж�
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
//    } // ��ֹ��������// ʹ�ܴ��ڷ����ж�
//  }
// // if (_UART4)
//  {
//    if ((*pMSGSERIAL).UARTx == 4)
//    {
//      RX4IE_DIS;
//      TX4IE_EN;
//    } // ��ֹ��������// ʹ�ܴ��ڷ����ж�
//  }
}
void LoadDataRecode(void)
{

  if ((*pMSGSERIAL).RecBuf[2] == 1) // ��
  {
    (*pMSGSERIAL).SendBuf[4] = (*pMSGSERIAL).RecBuf[4];
    switch ((*pMSGSERIAL).RecBuf[4])
    {
    case 0x90: // ��ع̼��汾
      (*pMSGSERIAL).SendBuf[3] = 4;
      (*pMSGSERIAL).SendBuf[5] = (VERSION + 0.01f) * 10; // �̼��汾
      UARTSendData();
      break;
    }
  }
  else if ((*pMSGSERIAL).RecBuf[2] == 0) // д
  {
    (*pMSGSERIAL).SendBuf[4] = 0x80;
    switch ((*pMSGSERIAL).RecBuf[4])
    {
    case 0x80:
      switch ((*pMSGSERIAL).RecBuf[5])
      {
      case 0x22:
        (*pMSGSERIAL).SendBuf[3] = 4;
        (*pMSGSERIAL).SendBuf[5] = 0x33; // Ӧ��
        UARTSendData();
        break;
      case 0x55:               // ��������
                               /*
								      NVIC->ICER[0]=NVIC->ICER[0];// �ر������ж�
		  	             // HAL_RCC_DeInit();
                      if(((*(INT32U *)(0x08000000)) & 0x2FFE0000)==0x20000000)//���ջ����ַ�Ƿ�Ϸ�
                      {
                        __set_MSP (*(INT32U *)(0x08000000));// ��ʼ��APP��ջ
												Jump_To_Application=(pIapFun)(*(INT32U *)(0x08000000 + 4));//
				                Jump_To_Application();
		                  }
								*/
//        SaveFuleData();        //��������
//        SaveSatesData(0, 100); //������½���bootload
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
  mTimeoutCount = TIME_OUT / SERIAL_TIME_ISR;     // ͨѶ��ʱʱ��
  mTimeSleepCount = TIME_SLEEP / SERIAL_TIME_ISR; // ͨѶ����ʱ��
  // ͨѶ��ʱ�ж�
  if (MSG_SERIAL_CAN1.RecTimer > mTimeoutCount) // ������ճ�ʱ
  {
    MSG_SERIAL_CAN1.RecCount = 0; // ��������ݼ�����
    MSG_SERIAL_CAN1.RecTimer = 0; // ���ʱ��
    MSG_SERIAL_CAN1.RecOver = 0;  // �����
  }
  if (MSG_SERIAL_CAN2.RecTimer > mTimeoutCount) // ������ճ�ʱ
  {
    MSG_SERIAL_CAN2.RecCount = 0; // ��������ݼ�����
    MSG_SERIAL_CAN2.RecTimer = 0; // ���ʱ��
    MSG_SERIAL_CAN2.RecOver = 0;  // �����
  }
  if (MSG_SERIAL_UART1.RecTimer > mTimeoutCount) // ������ճ�ʱ
  {
    MSG_SERIAL_UART1.RecCount = 0; // ��������ݼ�����
    MSG_SERIAL_UART1.RecTimer = 0; // ���ʱ��
    MSG_SERIAL_UART1.RecOver = 0;  // �����
  }
  if (MSG_SERIAL_UART2.RecTimer > mTimeoutCount) // ������ճ�ʱ
  {
    MSG_SERIAL_UART2.RecCount = 0; // ��������ݼ�����
    MSG_SERIAL_UART2.RecTimer = 0; // ���ʱ��
    MSG_SERIAL_UART2.RecOver = 0;  // �����
  }
  if (MSG_SERIAL_UART3.RecTimer > mTimeoutCount) // ������ճ�ʱ
  {
    MSG_SERIAL_UART3.RecCount = 0; // ��������ݼ�����
    MSG_SERIAL_UART3.RecTimer = 0; // ���ʱ��
    MSG_SERIAL_UART3.RecOver = 0;  // �����
  }
  if (MSG_SERIAL_UART4.RecTimer > mTimeoutCount) // ������ճ�ʱ
  {
    MSG_SERIAL_UART4.RecCount = 0; // ��������ݼ�����
    MSG_SERIAL_UART4.RecTimer = 0; // ���ʱ��
    MSG_SERIAL_UART4.RecOver = 0;  // �����
  }
  // �����ж�
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
/**************************** ϵͳ���ú��� *****************************/
// �ɶ�ʱ������
void SerialTimer(void)
{
  // ͨѶ��ʱ��ʱ
  if ((MSG_SERIAL_CAN1.RecCount != 0) && (MSG_SERIAL_RecCount == MSG_SERIAL_CAN1.RecCount)) // ������������ж���
  {
    if (MSG_SERIAL_CAN1.RecOver != 1)
    {
      MSG_SERIAL_CAN1.RecTimer++; // ͨѶ��ʱ��ʱ
    }
  }
  if ((MSG_SERIAL_CAN2.RecCount != 0) && (MSG_SERIAL_GUEST_RecCount == MSG_SERIAL_CAN2.RecCount)) // ������������ж���
  {
    if (MSG_SERIAL_CAN2.RecOver != 1)
    {
      MSG_SERIAL_CAN2.RecTimer++; // ͨѶ��ʱ��ʱ
    }
  }
  if ((MSG_SERIAL_UART1.RecCount != 0) && (MSG_SERIAL_UART1_RecCount == MSG_SERIAL_UART1.RecCount)) // ������������ж���
  {
    if (MSG_SERIAL_UART1.RecOver != 1)
    {
      MSG_SERIAL_UART1.RecTimer++; // ͨѶ��ʱ��ʱ
    }
  }
  if ((MSG_SERIAL_UART2.RecCount != 0) && (MSG_SERIAL_UART2_RecCount == MSG_SERIAL_UART2.RecCount)) // ������������ж���
  {
    if (MSG_SERIAL_UART2.RecOver != 1)
    {
      MSG_SERIAL_UART2.RecTimer++; // ͨѶ��ʱ��ʱ
    }
  }
  if ((MSG_SERIAL_UART3.RecCount != 0) && (MSG_SERIAL_UART3_RecCount == MSG_SERIAL_UART3.RecCount)) // ������������ж���
  {
    if (MSG_SERIAL_UART3.RecOver != 1)
    {
      MSG_SERIAL_UART3.RecTimer++; // ͨѶ��ʱ��ʱ
    }
  }
  if ((MSG_SERIAL_UART4.RecCount != 0) && (MSG_SERIAL_UART4_RecCount == MSG_SERIAL_UART4.RecCount)) // ������������ж���
  {
    if (MSG_SERIAL_UART4.RecOver != 1)
    {
      MSG_SERIAL_UART4.RecTimer++; // ͨѶ��ʱ��ʱ
    }
  }
  // ���߼�ʱ
  if (MSG_SERIAL_CAN1.RecCount == 0)
  {
    MSG_SERIAL_CAN1.SleepTime++; // ���߼�ʱ
  }
  if (MSG_SERIAL_CAN2.RecCount == 0)
  {
    MSG_SERIAL_CAN2.SleepTime++; //���߼�ʱ
  }
  if (MSG_SERIAL_UART1.RecCount == 0)
  {
    MSG_SERIAL_UART1.SleepTime++; // ���߼�ʱ
  }
  if (MSG_SERIAL_UART2.RecCount == 0)
  {
    MSG_SERIAL_UART2.SleepTime++; // ���߼�ʱ
  }
  if (MSG_SERIAL_UART3.RecCount == 0)
  {
    MSG_SERIAL_UART3.SleepTime++; // ���߼�ʱ
  }
  if (MSG_SERIAL_UART4.RecCount == 0)
  {
    MSG_SERIAL_UART4.SleepTime++; // ���߼�ʱ
  }
  MSG_SERIAL_RecCount = MSG_SERIAL_CAN1.RecCount;
  MSG_SERIAL_GUEST_RecCount = MSG_SERIAL_CAN2.RecCount;
  MSG_SERIAL_UART1_RecCount = MSG_SERIAL_UART1.RecCount;
  MSG_SERIAL_UART2_RecCount = MSG_SERIAL_UART2.RecCount;
  MSG_SERIAL_UART3_RecCount = MSG_SERIAL_UART3.RecCount;
  MSG_SERIAL_UART4_RecCount = MSG_SERIAL_UART4.RecCount;
  SerialTimeOut_();
}

// UART1�жϽ�������
void SerialInput_UART1(UINT8 RecData)
{
	if (MSG_SERIAL_UART1.RecOver)
		return;
	//--------------------------------����Դ��λ��Э�����ݰ�-----------------------------/
	if ((RecData == SOI) && (MSG_SERIAL_UART1.RecCount == 0))
	{
		MSG_SERIAL_UART1.SleepTime = 0;
		MSG_SERIAL_UART1_SleepFlag = 0;
		MSG_SERIAL_UART1.RecBuf[0] = SOI;
		MSG_SERIAL_UART1.RecCount = 1;
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] == SOI) && (MSG_SERIAL_UART1.RecCount < REC_MAX)) //�������λ��Э�� ��������
	{
		MSG_SERIAL_UART1.RecBuf[MSG_SERIAL_UART1.RecCount++] = RecData;
		if ((MSG_SERIAL_UART1.RecCount >= 2) && (MSG_SERIAL_UART1.RecBuf[1] != CID)) // �жϵ�2���ֽ��Ƿ�����λ��Э��
		{
			MSG_SERIAL_UART1.RecCount = 0;
		}
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] != 0xeb) && (MSG_SERIAL_UART1.RecBuf[0] != ADDR) && (MSG_SERIAL_UART1.RecBuf[0] != 0x6e)  ) // �����������Э��Ҳ����MODBUSЭ��
	// else if(MSG_SERIAL_UART1.RecBuf[0]!=0xeb && MSG_SERIAL_UART1.RecBuf[0]!=ADDR && MSG_SERIAL_UART1.RecBuf[0]!=0xec  && (MSG_SERIAL_UART1.RecBuf[0]!=0x7e))
	{
		MSG_SERIAL_UART1.RecCount = 0;
	}

	if ((MSG_SERIAL_UART1.RecBuf[0] == SOI) && (RecData == EOI) && (MSG_SERIAL_UART1.RecCount == (MSG_SERIAL_UART1.RecBuf[3] + 4)))
	{
		MSG_SERIAL_UART1.RecOver = 1; // ��λ��Э��������
		MSG_SERIAL_UART1.RecTimer = 0;
		MSG_SERIAL_UART1.RecCount = 0;
	}
	//--------------------------------����Դ����Э��--------------------------------/
	if ((RecData == 0xEB) && (MSG_SERIAL_UART1.RecCount == 0))
	{
		MSG_SERIAL_UART1.RecBuf[0] = 0xEB;
		MSG_SERIAL_UART1.RecCount = 1; //
		MSG_SERIAL_UART1.SleepTime = 0;
		MSG_SERIAL_UART1_SleepFlag = 0;
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] == 0xEB) && (MSG_SERIAL_UART1.RecCount < 75)) // ����ǳ���Դ����Э���������
	{
		MSG_SERIAL_UART1.RecBuf[MSG_SERIAL_UART1.RecCount++] = RecData;
		if ((MSG_SERIAL_UART1.RecCount >= 2) && (MSG_SERIAL_UART1.RecBuf[1] != ADDR)) // ����ڶ����ֽڲ�������Э��
		{
			MSG_SERIAL_UART1.RecCount = 0;
		}
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] != SOI) && (MSG_SERIAL_UART1.RecBuf[0] != ADDR)  && (MSG_SERIAL_UART1.RecBuf[0] != 0x6e)  ) // ���������λ����Э��Ҳ����MODbusЭ��
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
	 //--------------------------------����������Э��--------------------------------/
	if ((RecData == 0X6E) && (MSG_SERIAL_UART1.RecCount == 0))
	{
		MSG_SERIAL_UART1.RecBuf[0] = 0X6E;
		MSG_SERIAL_UART1.RecCount = 1; //
		MSG_SERIAL_UART1.SleepTime = 0;
		MSG_SERIAL_UART1_SleepFlag = 0;
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] == 0X6E) && (MSG_SERIAL_UART1.RecCount < 75)) // ����ǳ���Դ����Э���������
	{
		MSG_SERIAL_UART1.RecBuf[MSG_SERIAL_UART1.RecCount++] = RecData;
//		if ((MSG_SERIAL_UART1.RecCount >= 2) && (MSG_SERIAL_UART1.RecBuf[1] != ADDR)) // ����ڶ����ֽڲ�������Э��
//		{
//			MSG_SERIAL_UART1.RecCount = 0;
//		}
	}
	else if ((MSG_SERIAL_UART1.RecBuf[0] != SOI) && (MSG_SERIAL_UART1.RecBuf[0] != ADDR)  && (MSG_SERIAL_UART1.RecBuf[0] != 0XEB)  ) // ���������λ����Э��Ҳ����MODbusЭ��
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
	
	//--------------------------------����ԴMODBUSЭ��--------------------------------/
	if ((RecData == ADDR) && (MSG_SERIAL_UART1.RecCount == 0))
	{
		MSG_SERIAL_UART1.SleepTime = 0;
		MSG_SERIAL_UART1_SleepFlag = 0;
		MSG_SERIAL_UART1.RecBuf[0] = RecData;
		MSG_SERIAL_UART1.RecCount = 1; // ��������
	}
	else if ((MSG_SERIAL_UART1.RecCount != 0) && (MSG_SERIAL_UART1.RecBuf[0] == ADDR) && (MSG_SERIAL_UART1.RecCount < REC_MAX)) // ����Ѿ����յ���ʼλ
	{
		MSG_SERIAL_UART1.RecBuf[MSG_SERIAL_UART1.RecCount++] = RecData;
	}																					  // ��������ӵ�������
	else if ((MSG_SERIAL_UART1.RecBuf[0] != SOI) && (MSG_SERIAL_UART1.RecBuf[0] != 0xeb)  && (MSG_SERIAL_UART1.RecBuf[0] != 0x6e) ) // ������λ�����ݣ�Ҳ������������
	{
		MSG_SERIAL_UART1.RecCount = 0;
	}
	if (MSG_SERIAL_UART1.RecBuf[0] == ADDR)
	{
		if (MSG_SERIAL_UART1.RecCount >= 6) //���յ�6���ֽ� ʶ����������
		{
			if ((MSG_SERIAL_UART1.RecBuf[2] != 0) || (MSG_SERIAL_UART1.RecBuf[3] > 150) || (MSG_SERIAL_UART1.RecBuf[4] != 0) || (MSG_SERIAL_UART1.RecBuf[5] > 150)) // ��ַ������������Χ
			{
				MSG_SERIAL_UART1.RecCount = 0;
				MSG_SERIAL_UART1.RecTimer = 0;
			}
		}
		if (((MSG_SERIAL_UART1.RecBuf[1] == 0x03) && (MSG_SERIAL_UART1.RecCount == 8))) // ��ȡ����
		{
			/*
				  // ֱ�ӽ���
				  if(!Modbus_UserRcvChk(MSG_SERIAL_UART1.RecBuf)) // MODBUSЭ��У��
				  {
					 MSG_SERIAL_UART1.RecBuf[0]=0;
				 MSG_SERIAL_UART1.RecBuf[1]=0;
				 MSG_SERIAL_UART1.RecCount=0; // ��������ݼ�����
				 MSG_SERIAL_UART1.RecOver=0;  // �����
				  }else
				  {
				  */
			/*
			  // ֱ���ж��лظ� ���ⶪ֡
		  Modbus_SendData(&MSG_SERIAL_UART1,MSG_SERIAL_UART1.RecBuf);   // ���� ��ȡ����
		Modbus_ClearBuff_UART1();
			  */
			// �����������
			MSG_SERIAL_UART1.RecOver = 2;  // MUDBUS �������� ��Ϊ��
			MSG_SERIAL_UART1.RecTimer = 0; // �峬ʱ��ʱ��
			MSG_SERIAL_UART1.RecCount = 0;

			// }
		}
		else if ((MSG_SERIAL_UART1.RecBuf[1] == 0x10) && (MSG_SERIAL_UART1.RecCount >= 11)) // д������
		{
			if (MSG_SERIAL_UART1.RecCount == (MSG_SERIAL_UART1.RecBuf[6] + 9))
			{
				/*
						if(!Modbus_UserRcvChk((*pMSG).RecBuf)) //if the check is bad.
					{
								MSG_SERIAL_UART1.RecBuf[0]=0;
								MSG_SERIAL_UART1.RecBuf[1]=0;
								MSG_SERIAL_UART1.RecCount=0; // ��������ݼ�����
								MSG_SERIAL_UART1.RecOver=0;  // �����
					}else
						{
				*/
				if ((MSG_SERIAL_UART1.RecBuf[5] << 1) == (MSG_SERIAL_UART1.RecBuf[6])) // д��Ĵ����ĸ�����д����ֽ������Ǻ�
				{

		 
					MSG_SERIAL_UART1.RecOver = 3;  // =2 ��ȡ���ݰ��������  =3д�����ݰ��������
					MSG_SERIAL_UART1.RecTimer = 0; // ���ʱ��
					MSG_SERIAL_UART1.RecCount = 0;
				}
				//	}
			}
		}
	}
}
// UART1�жϷ�������
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
		//	if ((MSG_SERIAL_UART1.UARTx == 1) && (RS485_DIR1)) // 485�˿�
			{
				while (!(USART1->SR & ((UINT32)1 << 6)))
					; // �ȴ��������
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
	//	if (RS485_DIR1) // 485�˿�
		{
		//	RS485DIR1_Output_1_Hook(); // ����Ϊ����
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
	MSG_SERIAL_UART1.RecCount = 0; // ��������ݼ�����
	MSG_SERIAL_UART1.RecOver = 0;  // ���������
								   //  MSG_SERIAL_UART1.UARTx=0;
}
void Modbus_ClearBuff_UART2(void)
{
	MSG_SERIAL_UART2.RecBuf[0] = 0;
	MSG_SERIAL_UART2.RecBuf[1] = 0;
	MSG_SERIAL_UART2.RecBuf[3] = 0;
	MSG_SERIAL_UART2.RecBuf[6] = 0;
	MSG_SERIAL_UART2.RecTimer = 0;
	MSG_SERIAL_UART2.RecCount = 0; // ��������ݼ�����
	MSG_SERIAL_UART2.RecOver = 0;  // ���������
	//	  MSG_SERIAL_UART2.UARTx=0;
}
void Modbus_ClearBuff_UART3(void)
{
	MSG_SERIAL_UART3.RecBuf[0] = 0;
	MSG_SERIAL_UART3.RecBuf[1] = 0;
	MSG_SERIAL_UART3.RecBuf[3] = 0;
	MSG_SERIAL_UART3.RecBuf[6] = 0;
	MSG_SERIAL_UART3.RecTimer = 0;
	MSG_SERIAL_UART3.RecCount = 0; // ��������ݼ�����
	MSG_SERIAL_UART3.RecOver = 0;  // ���������
	//	  MSG_SERIAL_UART3.UARTx=0;
}
void Modbus_ClearBuff_UART4(void)
{
	MSG_SERIAL_UART4.RecBuf[0] = 0;
	MSG_SERIAL_UART4.RecBuf[1] = 0;
	MSG_SERIAL_UART4.RecBuf[3] = 0;
	MSG_SERIAL_UART4.RecBuf[6] = 0;
	MSG_SERIAL_UART4.RecTimer = 0;
	MSG_SERIAL_UART4.RecCount = 0; // ��������ݼ�����
	MSG_SERIAL_UART4.RecOver = 0;  // ���������
								   //  MSG_SERIAL_UART4.UARTx=0;
}
void Modbus_ClearBuff_CAN1(void)
{
	MSG_SERIAL_CAN1.RecBuf[0] = 0;
	MSG_SERIAL_CAN1.RecBuf[1] = 0;
	MSG_SERIAL_CAN1.RecBuf[3] = 0;
	MSG_SERIAL_CAN1.RecBuf[6] = 0;
	MSG_SERIAL_CAN1.RecTimer = 0;
	MSG_SERIAL_CAN1.RecCount = 0; // ��������ݼ�����
	MSG_SERIAL_CAN1.RecOver = 0;  // ���������
								  // MSG_SERIAL_CAN1.UARTx=0;
}
void Modbus_ClearBuff_CAN2(void)
{
	MSG_SERIAL_CAN2.RecBuf[0] = 0;
	MSG_SERIAL_CAN2.RecBuf[1] = 0;
	MSG_SERIAL_CAN2.RecBuf[3] = 0;
	MSG_SERIAL_CAN2.RecBuf[6] = 0;
	MSG_SERIAL_CAN2.RecTimer = 0;
	MSG_SERIAL_CAN2.RecCount = 0; // ��������ݼ�����
	MSG_SERIAL_CAN2.RecOver = 0;  // ���������
								  // MSG_SERIAL_CAN2.UARTx=0;
}

// CRC����
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
// �������ڷ�������
// NumΪ���͵��ֽ���������2�ֽ�CRC
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
	Modbus_CAN_SendDataToCan(pMSG); // CAN����
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
		} // ��ֹ�������� ʹ�ܴ��ڷ����ж�
	}
//	if (_UART2)
	{
		if (pMSG->UARTx == 2)
		{
			RX2IE_DIS;
			TX2IE_EN;
		} // ��ֹ�������� ʹ�ܴ��ڷ����ж�
	}
//	if (_UART3)
//	{
//		if (pMSG->UARTx == 3)
//		{
//			RX3IE_DIS;
//			TX3IE_EN;
//		} // ��ֹ�������� ʹ�ܴ��ڷ����ж�
//	}
//	if (_UART4)
//	{
//		if (pMSG->UARTx == 4)
//		{
//			RX4IE_DIS;
//			TX4IE_EN;
//		} // ��ֹ�������� ʹ�ܴ��ڷ����ж�
//	}
	MSG_SERIAL_UART1_SleepFlag = 0;
	MSG_SERIAL_UART1.SleepTime = 0;
}


// ���ʹ������
void Modbus_SendError(MSG *pMSG, UINT8 cmd, UINT8 bype)
{
	// UINT8 sendData[5];
	SendDataBuff[0] = ADDR;
	SendDataBuff[1] = cmd | 0x80;
	SendDataBuff[2] = bype;
	Modbus_SerialStartSend(pMSG, SendDataBuff, 3);
}
// д�� len�Ĵ���������
//void UserWriteDataToAddr(MSG *pMSG, UINT16 StartAddr, UINT8 *pdata, UINT8 RegNum)
//{
//	

//	UINT16 i, X, N;
//	UINT16 nAddr = 0;
//	UINT8 chkSumdata = 0;
//	UINT8 WriteErrFlag = 0; // д������־
//	X = TTemp_count + MOS_OT + E_OT;
//	N = TCell_count;
//	for (i = 0; i < RegNum; i++)
//	{
//		nAddr = StartAddr + i; // �Ĵ�����ַ
//		if ((nAddr >= (0x1B + N + X)) && (nAddr <= (0x21 + N + X)))
//		{
//			if (nAddr == (0x1B + N + X)) // MOS����  /******************���ݵ�ǰ��Ŀ�����޸�*********************/
//			{
//				if (*(pdata + (i << 1) + 1) & 0x01) // ����ŵ�
//				{
//					Guset_CMDDSGFET_EN = 1;
//				//	DSGFET_ON();
//				}
//				else // ��ֹ�ŵ�
//				{
//					Guset_CMDDSGFET_EN = 0;
//				//	DSGFET_OFF();
//				}
//				if (*(pdata + (i << 1) + 1) & 0x02) // ������
//				{
//					Guset_CMDCHGFET_EN = 1;
//				//	CHGFET_ON();
//				}
//				else // ��ֹ���
//				{
//					Guset_CMDCHGFET_EN = 0;
//				//	CHGFET_OFF();
//				}
//			}
//			else if (nAddr == (0x1C + N + X)) // ���ȿ��� /******************���ݵ�ǰ��Ŀ�����޸�*********************/
//			{
//				if (*(pdata + (i << 1) + 1) & 0x01) // ���ȿ�
//				{
//					Guset_Heat_EN = 1;
//					// �򿪼���
//				}
//				else
//				{
//					Guset_Heat_EN = 0;
//					// �رռ���
//				}
//			}
//			else if (nAddr == (0x20 + N + X)) // GPS��Դ���� /******************���ݵ�ǰ��Ŀ�����޸�*********************/
//			{
//				if (*(pdata + (i << 1) + 1) & 0x01) // GPS��Դ��
//				{
//					Guset_CMDGPSPOWER_EN = 1;
//					// ��GPS��Դ
//				}
//				else
//				{
//					Guset_CMDGPSPOWER_EN = 0;
//					// �ر�GPS��Դ
//				}
//			}
//			else if (nAddr == (0x21 + N + X)) // RTC ����
//			{
////				if (RTCC)
////				{
////					RTC_SetTime(*(pdata + (i << 1)), *(pdata + (i << 1) + 1), *(pdata + (i << 1) + 2), *(pdata + (i << 1) + 3), *(pdata + (i << 1) + 4), *(pdata + (i << 1) + 5));
////					RTC_GetTime();
////				}
//			}
//		}
//		// �������ò���
//		if ((nAddr >= (0x45 + N + X)) && (nAddr <= (0x53 + N + X)))
//		{
//			WriteEepromFlag |= 0x01;
//			if (nAddr == (0x45 + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 250))
//				{
//					WriteErrFlag = 3;
//				} // ����Χ
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 50))
//				{
//					WriteErrFlag = 3;
//				}												 // ����Χ
//				ReadCfgData[1] = *(pdata + (i << 1)) - 1;		 // ������
//				ReadCfgData[22] = (*(pdata + (i << 1) + 1)) - 1; // ��������ʱ
//			}
//			else if (nAddr == (0x46 + N + X))
//			{
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 100))
//				{
//					WriteErrFlag = 3;
//				}												// ����Χ
//				ReadCfgData[2] = *(pdata + (i << 1));			// ��о��ѹ
//				ReadCfgData[3] = (*(pdata + (i << 1) + 1)) - 1; // ��ѹ��ʱ
//			}
//			else if (nAddr == (0x47 + N + X))
//			{
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 100))
//				{
//					WriteErrFlag = 3;
//				}											  // ����Χ
//				ReadCfgData[4] = *(pdata + (i << 1));		  // ��о����
//				ReadCfgData[5] = *(pdata + (i << 1) + 1) - 1; // ������ʱ
//			}
//			else if (nAddr == (0x48 + N + X))
//			{
//				ReadCfgData[6] = *(pdata + (i << 1));	  // ��ѹ�ͺ��ѹ
//				ReadCfgData[7] = *(pdata + (i << 1) + 1); // �����ͺ��ѹ
//			}
//			else if (nAddr == (0x49 + N + X))
//			{
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 100))
//				{
//					WriteErrFlag = 3;
//				}											   // ����Χ
//				ReadCfgData[25] = *(pdata + (i << 1)) - 1;	   // ��о��ѹ�ָ���ʱ
//				ReadCfgData[26] = *(pdata + (i << 1) + 1) - 1; // ��о���Żָ���ʱ
//			}
//			else if (nAddr == (0x4F + N + X))
//			{
//				if ((*(pdata + (i << 1) + 1) <= 1) || (*(pdata + (i << 1) + 1) > 100))
//				{
//					WriteErrFlag = 3;
//				}											   // ����Χ
//				ReadCfgData[18] = *(pdata + (i << 1));		   // ���⿪����ѹ
//				ReadCfgData[19] = *(pdata + (i << 1) + 1) - 2; // ���⿪��ѹ��
//			}
//			else if (nAddr == (0x50 + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 250))
//				{
//					WriteErrFlag = 3;
//				} // ����Χ
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 120))
//				{
//					WriteErrFlag = 3;
//				}											   // ����Χ
//				ReadCfgData[20] = *(pdata + (i << 1)) - 1;	   // �ŵ����1
//				ReadCfgData[21] = *(pdata + (i << 1) + 1) - 1; // �ŵ����1��ʱ
//			}
//			// �ŵ����2 �ŵ����2��ʱ �ŵ���±��� �ŵ���±����ָ� �ŵ�͵��±��� �����±��� �����±����ָ� �����±��� �����±����ָ�
//			if ((nAddr >= (0x4A + N + X)) && (nAddr <= (0x4E + N + X)))
//			{
//				ReadCfgData[8 + ((nAddr << 1) - ((0x4A + N + X) << 1))] = *(pdata + (i << 1));
//				ReadCfgData[9 + ((nAddr << 1) - ((0x4A + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//			// �ŵ��·���� �ŵ��·������ʱ �������±��� �������±����ָ� �������±��� �������±����ָ�
//			if ((nAddr >= (0x51 + N + X)) && (nAddr <= (0x53 + N + X)))
//			{
//				ReadCfgData[23 + ((nAddr << 1) - ((0x51 + N + X) << 1))] = *(pdata + (i << 1));
//				ReadCfgData[24 + ((nAddr << 1) - ((0x51 + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//		}
//		// ��չ���ò���
//		if ((nAddr >= (0x54 + N + X)) && (nAddr <= (0x5B + N + X)))
//		{
//			WriteEepromFlag |= 0x02;
//			if (nAddr == (0x5B + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 250))
//				{
//					WriteErrFlag = 3;
//				}											// ����Χ
//				ReadCfgEData[25] = *(pdata + (i << 1)) - 1; // MOS���±�����ʱ
//			}
//			// ��ѹ��ѹ���� ��ѹ��ѹ�����ָ� ��ѹ���ű��� ��ѹ���Żָ�
//			if ((nAddr >= (0x54 + N + X)) && (nAddr <= (0x57 + N + X)))
//			{
//				ReadCfgEData[2 + ((nAddr << 1) - ((0x54 + N + X) << 1))] = *(pdata + (i << 1));
//				ReadCfgEData[3 + ((nAddr << 1) - ((0x54 + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//			// ��ѹ��ѹ������ʱ ��ѹ���ű�����ʱ �ܹ�ѹ�ָ���ʱ �ܹ��Żָ���ʱ MOS���±��� MOS���±����ָ�
//			if (nAddr == (0x58 + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 30))
//				{
//					WriteErrFlag = 3;
//				} // ����Χ
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 30))
//				{
//					WriteErrFlag = 3;
//				} // ����Χ
//			}
//			if (nAddr == (0x59 + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 50))
//				{
//					WriteErrFlag = 3;
//				} // ����Χ
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 50))
//				{
//					WriteErrFlag = 3;
//				} // ����Χ
//			}
//			if (nAddr == (0x5A + N + X))
//			{
//				if ((*(pdata + (i << 1)) == 0) || (*(pdata + (i << 1)) > 120))
//				{
//					WriteErrFlag = 3;
//				} // ����Χ
//				if ((*(pdata + (i << 1) + 1) == 0) || (*(pdata + (i << 1) + 1) > 120))
//				{
//					WriteErrFlag = 3;
//				} // ����Χ
//			}
//			if ((nAddr >= (0x58 + N + X)) && (nAddr <= (0x5A + N + X)))
//			{
//				ReadCfgEData[2 + ((nAddr << 1) - ((0x58 + N + X) << 1))] = *(pdata + (i << 1)) - 1;
//				ReadCfgEData[3 + ((nAddr << 1) - ((0x58 + N + X) << 1))] = *(pdata + (i << 1) + 1) - 1;
//			}
//		}
//		if ((nAddr == (0x60 + N + X)) && ((*(pdata + (i << 1))) & 0x01)) // ʹ������
//		{
//			WriteEepromFlag |= 0x02;
//			if ((*(pdata + (i << 1))) & 0x01) // ��ѹ������
//			{
//				ReadCfgEData[1] |= 0x01; //
//			}
//			else
//			{
//				ReadCfgEData[1] &= (~0x01); // ��ѹ�������ù�
//			}
//		}
//		// �������ݲ���
//		if ((nAddr >= (0x5C + N + X)) && (nAddr <= (0x5E + N + X)))
//		{
//			WriteEepromFlag |= 0x04;
//			if (nAddr == (0x5E + N + X))
//			{
//				ReadFuelData[10] = *(pdata + (i << 1)) - 1; // �������� ��ʱ
//			}
//			// �������� ��ѹ���� ��������
//			if ((nAddr >= (0x5C + N + X)) && (nAddr <= (0x5D + N + X)))
//			{
//				ReadFuelData[0 + ((nAddr << 1) - ((0x5C + N + X) << 1))] = *(pdata + (i << 1));
//				ReadFuelData[1 + ((nAddr << 1) - ((0x5C + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//		}
//		//�澯����
//		if ((nAddr >= (0x5F + N + X)) && (nAddr <= (0x6B + N + X)))
//		{
//			WriteEepromFlag |= 0x08;
//			// switch(nAddr)
//			//{
//			if (nAddr == (0x5F + N + X))
//			{
//				ReadAlamData[22] = *(pdata + (i << 1));		// ����/���ȿ����¶�
//				ReadAlamData[23] = *(pdata + (i << 1) + 1); // ����/���Ȼָ��¶�
//			}
//			else if (nAddr == (0x60 + N + X)) // ʹ������
//			{
//				ReadAlamData[0] = *(pdata + (i << 1) + 1); // �澯ʹ��
//			}
//			else if (nAddr == (0x6B + N + X))
//			{
//				ReadAlamData[21] = *(pdata + (i << 1)); // SOC�͸澯
//			}
//			//}
//			// ��ѹ��ѹ�澯��ѹ  ��ѹ���Ÿ澯��ѹ ��о��ѹ�澯��ѹ ��о���Ÿ澯��ѹ �������澯���� �ŵ�����澯����
//			// �����¸澯�¶� �ŵ���¸澯�¶� MOS���¸澯�¶� MOS���¸澯�ָ��¶� ��о������澯ѹ�� ������澯�ָ�ѹ��
//			// �������¸澯 �������¸澯
//			if ((nAddr >= (0x61 + N + X)) && (nAddr <= (0x6A + N + X)))
//			{
//				ReadAlamData[1 + ((nAddr << 1) - ((0x61 + N + X) << 1))] = *(pdata + (i << 1));
//				ReadAlamData[2 + ((nAddr << 1) - ((0x61 + N + X) << 1))] = *(pdata + (i << 1) + 1);
//			}
//		}
//	}

//	// �ظ�д��ɹ�
//	if (WriteErrFlag == 0)
//	{
//		//WriteEepromFlag <<= 4;
//	//	ModbusInitVal(); // ������д��EEPROM
//		SendDataBuff[0] = ADDR;
//		SendDataBuff[1] = 0x10;
//		SendDataBuff[2] = StartAddr >> 8;
//		SendDataBuff[3] = StartAddr;
//		SendDataBuff[4] = RegNum >> 8;
//		SendDataBuff[5] = RegNum;
//		Modbus_SerialStartSend(pMSG, SendDataBuff, 6); // �ظ�д��ɹ�
//	}
//	else // д��ʧ��
//	{
//		WriteEepromFlag = 0; // ���д��־
//		// ���³�ʼ������
////		InitBaskVal();								// ��������
////		InitExpandVal();							// ��չ����
////		InitAlamVal();								// �澯����
////		InitCap();									// ��������
//		Modbus_SendError(pMSG, 0x10, WriteErrFlag); // ����д��ʧ��ԭ��
//		WriteErrFlag = 0;							// ���ʧ�ܱ�־
//	}
//}


// ��ַ���ݱ���  1�����һ��
void ModbusSendDataCode(void)
{
	UINT16 data = 0, i;
	UINT8 N = 0, X = 0;
	UINT32 U32data = 0;
	UINT32 BalanceStates = 0;
	// ��ذ�����
	Modbus_AddrData[0x00][0] = 0;
	Modbus_AddrData[0x00][1] = TCell_count;
	// �¶�̽ͷ����
	Modbus_AddrData[0x01][0] = 0;
	Modbus_AddrData[0x01][1] = TTemp_count + MOS_OT + E_OT;
	// ��о��ѹ
	for (i = 0; i < TCell_count; i++)
	{
		data = (V_CB.CellVlg[i + 1] + 0.0005f) * 1000;
		Modbus_AddrData[0x02 + i][0] = (data >> 8);
		Modbus_AddrData[0x02 + i][1] = data;
	}
	N = TCell_count;
	// ��ǰ����
	if (F_CB.DSG_FLAG) // ����ڷŵ�
	{
		data = (UINT16)(C_CB.DSGCur * 100);
		data = ~data + 1; // ת��Ϊ����
	}
	else if (F_CB.CHG_FLAG) // ����ڳ��
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
	} // �ŵ�
	if (F_CB.CHG_FLAG)
	{
		data |= 0x0002;
	} // ���
	if (F_CB.CHG_FLAG)
	{
		data |= 0x0004;
	} // �����������   /******************���ݵ�ǰ��Ŀ�����޸�*********************/
	if (MOS_OT)
	{
		data |= 0x0010;
	} // �л�MOS�¶�
	if (E_OT)
	{
		data |= 0x0020;
	} // �л����¶�
	if (F_CB.OV_FLAG & 0x01)
	{
		data |= 0x0100;
	} // ��о��ѹ����
	if (F_CB.OV_FLAG & 0x02)
	{
		data |= 0x0200;
	} // ��ѹ��ѹ����
	if (F_CB.OV_FLAG & 0x10)
	{
		data |= 0x1000;
	} // ��������
	Modbus_AddrData[0x03 + N][0] = (data >> 8);
	Modbus_AddrData[0x03 + N][1] = data;
	// state2
	data = 0;
	if (F_CB.UV_FLAG & 0x01)
	{
		data |= 0x0001;
	} // ��оǷѹ����
	if (F_CB.UV_FLAG & 0x02)
	{
		data |= 0x0002;
	} // ��ѹǷѹ����
	if ((F_CB.OT_FLAG & 0x11) == 0x11)
	{
		data |= 0x0100;
	} // �����±���
	if ((F_CB.OT_FLAG & 0x21) == 0x21)
	{
		data |= 0x0200;
	} // �����±���
	if (F_CB.OTMOS_FLAG)
	{
		data |= 0x0400;
	} // MOS���±���
	if ((F_CB.OT_FLAG & 0x12) == 0x12)
	{
		data |= 0x1000;
	} // �ŵ���±���
	if ((F_CB.OT_FLAG & 0x22) == 0x22)
	{
		data |= 0x2000;
	} // �ŵ���±���
	Modbus_AddrData[0x04 + N][0] = (data >> 8);
	Modbus_AddrData[0x04 + N][1] = data;
	// state3
	data = 0;
	if (F_CB.OC_SC_FLAG & 0x01)
	{
		data |= 0x0001;
	} // �ŵ��·����
	if (F_CB.OC_SC_FLAG & 0x02)
	{
		data |= 0x0002;
	} // �ŵ��������
	if (F_CB.OC_SC_FLAG & 0x04)
	{
		data |= 0x0004;
	} // ����������
	if (F_CB.EVOT_FLAG & 0x01)
	{
		data |= 0x0010;
	} // �������±���
	if (F_CB.EVOT_FLAG & 0x02)
	{
		data |= 0x0020;
	} // �������±���
	Modbus_AddrData[0x05 + N][0] = (data >> 8);
	Modbus_AddrData[0x05 + N][1] = data;
	// ��о�¶�
	for (i = 0; i < TTemp_count; i++)
	{
		data = V_CB.TemReg[i + 1] + 40;
		Modbus_AddrData[0x05 + N + 1 + i][0] = (data >> 8);
		Modbus_AddrData[0x05 + N + 1 + i][1] = data;
	}
	// MOS�¶�
	if (MOS_OT == 1)
	{
		data = OT_CB.MosTemp + 40;
		Modbus_AddrData[0x05 + N + TTemp_count + MOS_OT][0] = (data >> 8);
		Modbus_AddrData[0x05 + N + TTemp_count + MOS_OT][1] = data;
	}
	X = TTemp_count + MOS_OT + E_OT;
	// �����¶�
	if (E_OT == 1)
	{
		data = V_CB.EnvironmentTemp + 40;
		Modbus_AddrData[0x05 + N + X][0] = (data >> 8);
		Modbus_AddrData[0x05 + N + X][1] = data;
	}
	BalanceStates = BLA_CB.BCellData[1];
	// ����״̬1
	Modbus_AddrData[0x06 + N + X][0] = (BalanceStates >> 8);
	Modbus_AddrData[0x06 + N + X][1] = BalanceStates;
	// ����״̬2
	Modbus_AddrData[0x07 + N + X][0] = (BalanceStates >> 24);
	Modbus_AddrData[0x07 + N + X][1] = (BalanceStates >> 16);
	// ����汾
	Modbus_AddrData[0x08 + N + X][0] = (VERSION + 0.01f) * 10;
	// Ӳ���汾
	Modbus_AddrData[0x08 + N + X][1] = Hardware_VER;
	// ״̬
	data = 0;
	if (F_CB.DSG_EN_FLAG)
	{
		data |= 0x0002;
	} // �ŵ�MOS��
	if (F_CB.CHG_EN_FLAG)
	{
		data |= 0x0004;
	} // ���MOS��
	if (F_CB.TempFail_FLAG)
	{
		data |= 0x0100;
	} // �¶Ȳɼ�ʧЧ
	if (F_CB.VlgFail_FLAG)
	{
		data |= 0x0200;
	} // ��ѹ�ɼ�ʧЧ
	if (F_CB.DSGFail_FLAG)
	{
		data |= 0x0400;
	} // �ŵ�MOSʧЧ ��
	if (F_CB.CHGFail_FLAG)
	{
		data |= 0x0800;
	} // ���MOSʧЧ ��
	if (F_CB.IMBALANCE_ALAM_FLAG)
	{
		data |= 0x1000;
	} // ��о������澯
	if (F_CB.OTD_ALAM_FLAG & 0x10)
	{
		data |= 0x4000;
	} // �ŵ���¸澯
	if (F_CB.OTC_ALAM_FLAG & 0x10)
	{
		data |= 0x8000;
	} // �����¸澯
	Modbus_AddrData[0x09 + N + X][0] = (data >> 8);
	Modbus_AddrData[0x09 + N + X][1] = data;
	// �澯״̬
	data = 0;
	if (F_CB.UV_ALAM_FLAG)
	{
		data |= 0x0001;
	} // ��о���Ÿ澯
	if (F_CB.TUV_ALAM_FLAG)
	{
		data |= 0x0002;
	} // ��ѹ���Ÿ澯
	if (F_CB.OV_ALAM_FLAG)
	{
		data |= 0x0004;
	} // ��о��ѹ�澯
	if (F_CB.TOV_ALAM_FLAG)
	{
		data |= 0x0008;
	} // ��ѹ��ѹ�澯
	if (F_CB.DSGOCALAM_FLAG)
	{
		data |= 0x0010;
	} // �ŵ�����澯
	if (F_CB.CHGOCALAM_FLAG)
	{
		data |= 0x0020;
	} // �������澯
	if (F_CB.OTD_ALAM_FLAG & 0x01)
	{
		data |= 0x0040;
	} // �ŵ���¸澯
	if (F_CB.OTC_ALAM_FLAG & 0x01)
	{
		data |= 0x0080;
	} // �����¸澯
	if (F_CB.EVOT_ALAM_FLAG & 0x01)
	{
		data |= 0x0100;
	} // �������¸澯
	if (F_CB.EVOT_ALAM_FLAG & 0x02)
	{
		data |= 0x0200;
	} // �������¸澯
	if (F_CB.SOCL_ALAM_FLAG)
	{
		data |= 0x0400;
	} // SOC�͸澯
	if (F_CB.MOSOT_ALAM_FLAG)
	{
		data |= 0x0800;
	} // MOS���¸澯
	Modbus_AddrData[0x0A + N + X][0] = (data >> 8);
	Modbus_AddrData[0x0A + N + X][1] = data;
	// ����SOC
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
	// ѭ������
	Modbus_AddrData[0x0D + N + X][0] = (SOC.CycleCount >> 8);
	Modbus_AddrData[0x0D + N + X][1] = SOC.CycleCount;
	// ��ذ�������
	U32data = SOC.RemFullCapDesign * (1 + 0.000001f);
	U32data *= 100;
	Modbus_AddrData[0x0E + N + X][0] = (U32data >> 24);
	Modbus_AddrData[0x0E + N + X][1] = (U32data >> 16);
	Modbus_AddrData[0x0F + N + X][0] = (U32data >> 8);
	Modbus_AddrData[0x0F + N + X][1] = U32data;
	// ��ǰ���������
	U32data = SOC.RemFullCap * (1 + 0.000001f);
	Modbus_AddrData[0x10 + N + X][0] = (U32data >> 24);
	Modbus_AddrData[0x10 + N + X][1] = (U32data >> 16);
	Modbus_AddrData[0x11 + N + X][0] = (U32data >> 8);
	Modbus_AddrData[0x11 + N + X][1] = U32data;
	// ���ʣ������
	if ((float)SOC.RemCap > (long int)0)
	{
		U32data = SOC.RemCap;
	}
	else
	{
		U32data = 0;
	}
	if (U32data > SOC.RemFullCap) // ��ֹ����������
	{
		U32data = SOC.RemFullCap;
	}
	U32data = U32data * (1 + 0.000001f);
	Modbus_AddrData[0x12 + N + X][0] = (U32data >> 24);
	Modbus_AddrData[0x12 + N + X][1] = (U32data >> 16);
	Modbus_AddrData[0x13 + N + X][0] = (U32data >> 8);
	Modbus_AddrData[0x13 + N + X][1] = U32data;
	// �ŵ�ʣ��ʱ��
	Modbus_AddrData[0x14 + N + X][0] = (SOC_CB.DSGRemTime >> 8);
	Modbus_AddrData[0x14 + N + X][1] = SOC_CB.DSGRemTime;
	// ���ʣ��ʱ��
	Modbus_AddrData[0x15 + N + X][0] = (SOC_CB.CHGRemTime >> 8);
	Modbus_AddrData[0x15 + N + X][1] = SOC_CB.CHGRemTime;
	// ��ǰ�����
	Modbus_AddrData[0x16 + N + X][0] = (SOC_CB.CHGTimeInterval >> 8);
	Modbus_AddrData[0x16 + N + X][1] = SOC_CB.CHGTimeInterval;
	// ������
	Modbus_AddrData[0x17 + N + X][0] = (SOC_CB.CHGTimeIntervaler >> 8);
	Modbus_AddrData[0x17 + N + X][1] = SOC_CB.CHGTimeIntervaler;
	// ����ܵ�ѹ
	data = V_CB.TotalVlg * 100;
	Modbus_AddrData[0x18 + N + X][0] = (data >> 8);
	Modbus_AddrData[0x18 + N + X][1] = data;
	// ��ذ���ߵ�ѹ
	data = OV_CB.HVlg * 1000;
	Modbus_AddrData[0x19 + N + X][0] = (data >> 8);
	Modbus_AddrData[0x19 + N + X][1] = data;
	// ��ذ���͵�ѹ
	data = UV_CB.LVlg * 1000;
	Modbus_AddrData[0x1A + N + X][0] = (data >> 8);
	Modbus_AddrData[0x1A + N + X][1] = data;
	// MOS����
	data = 0;
	if (Guset_CMDDSGFET_EN)
	{
		data |= 0x0001;
	} // �ŵ�MOS����
	if (Guset_CMDCHGFET_EN)
	{
		data |= 0x0002;
	} // ���MOS����
	Modbus_AddrData[0x1B + N + X][0] = data >> 8;
	Modbus_AddrData[0x1B + N + X][1] = data;
	// ���ȿ���
	data = 0;
	if (Guset_Heat_EN)
	{
		data = 0x0001;
	}
	Modbus_AddrData[0x1C + N + X][0] = data >> 8;
	Modbus_AddrData[0x1C + N + X][1] = data;
	// ������������ ��λ10mA
	data = SOC.RemFullCapDesign >> 1; // 0.5C /*******************������Ҫ�޸�**********************/
	Modbus_AddrData[0x1D + N + X][0] = data >> 8;
	Modbus_AddrData[0x1D + N + X][1] = data;
	// ��׼����ѹ ��λmV
//	if (OV_VLG_2 > 4.1f)
//	{
//		data = 420 * TCell_count;
//	} // ��Ԫ��� ����ѹ4.2V
//	else
//	{
//		data = 360 * TCell_count;
//	} // ��﮵�� ����ѹ3.6
	Modbus_AddrData[0x1E + N + X][0] = data >> 8;
	Modbus_AddrData[0x1E + N + X][1] = data;
	// ��ǰʪ��
	Modbus_AddrData[0x1F + N + X][0] = 0;
	Modbus_AddrData[0x1F + N + X][1] = 0;
	// GPSģ���Դ����
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
	// ��ذ�����
	if (ProductCode[0] < 32)
	{
		for (i = 0; i < ProductCode[0]; i++) // ȡ����Ӧ�ֽ������ı���
		{
			*((UINT8 *)Modbus_AddrData + ((0x24 + N + X) << 1) + i) = ProductCode[i + 1];
		}
	}
	else
	{
		ProductCode[0] = 0;
	}
	for (i = ProductCode[0]; i < 32; i++) // ����32�ֽڲ�0
	{
		*((UINT8 *)Modbus_AddrData + ((0x24 + N + X + ProductCode[0]) << 1) + i) = 0;
	}
	/***************************Ԥ��32�ֽ�*******************************/

	/********************************��������**********************************/
	// �����ɼ�����
	data = (0.1 + 0.00001f) * 100000;
	Modbus_AddrData[0x44 + N + X][0] = (data >> 8);
	Modbus_AddrData[0x44 + N + X][1] = data;
	// ����������
	Modbus_AddrData[0x45 + N + X][0] = ReadCfgData[1] + 1;	//
															// ��������ʱ
	Modbus_AddrData[0x45 + N + X][1] = ReadCfgData[22] + 1; //
															// ��о��ѹ����
	Modbus_AddrData[0x46 + N + X][0] = ReadCfgData[2];
	// ��ѹ������ʱ
	Modbus_AddrData[0x46 + N + X][1] = ReadCfgData[3];
	// ��о���ű���
	Modbus_AddrData[0x47 + N + X][0] = ReadCfgData[4];
	// ���ű�����ʱ
	Modbus_AddrData[0x47 + N + X][1] = ReadCfgData[5];
	// ��ѹ�ͺ��ѹ
	Modbus_AddrData[0x48 + N + X][0] = ReadCfgData[6];
	// �����ͺ��ѹ
	Modbus_AddrData[0x48 + N + X][1] = ReadCfgData[7];
	// ��ѹ�ָ���ʱ
	Modbus_AddrData[0x49 + N + X][0] = ReadCfgData[25] + 1;
	// ���Żָ���ʱ
	Modbus_AddrData[0x49 + N + X][1] = ReadCfgData[26] + 1;
	// �ŵ����2
	Modbus_AddrData[0x4A + N + X][0] = ReadCfgData[8];
	// �ŵ����2��ʱ
	Modbus_AddrData[0x4A + N + X][1] = ReadCfgData[9];
	// �ŵ���±���
	Modbus_AddrData[0x4B + N + X][0] = ReadCfgData[10];
	// �ŵ���±����ָ�
	Modbus_AddrData[0x4B + N + X][1] = ReadCfgData[11];
	// �ŵ�͵��±���
	Modbus_AddrData[0x4C + N + X][0] = ReadCfgData[12];
	// �ŵ���±����ָ�
	Modbus_AddrData[0x4C + N + X][1] = ReadCfgData[13];
	// �����±���
	Modbus_AddrData[0x4D + N + X][0] = ReadCfgData[14];
	// �����±����ָ�
	Modbus_AddrData[0x4D + N + X][1] = ReadCfgData[15];
	// �����±���
	Modbus_AddrData[0x4E + N + X][0] = ReadCfgData[16];
	// �����±����ָ�
	Modbus_AddrData[0x4E + N + X][1] = ReadCfgData[17];
	// ���⿪����ѹ
	Modbus_AddrData[0x4F + N + X][0] = ReadCfgData[18];
	// ���⿪��ѹ��
	Modbus_AddrData[0x4F + N + X][1] = ReadCfgData[19] + 2;
	// �ŵ����1����
	Modbus_AddrData[0x50 + N + X][0] = ReadCfgData[20] + 1;
	// �ŵ����1��ʱ
	Modbus_AddrData[0x50 + N + X][1] = ReadCfgData[21] + 1;
	// �ŵ��·����
	Modbus_AddrData[0x51 + N + X][0] = ReadCfgData[23];
	// �ŵ��·������ʱ
	Modbus_AddrData[0x51 + N + X][1] = ReadCfgData[24];
	// �������±���
	Modbus_AddrData[0x52 + N + X][0] = ReadCfgData[27];
	// �������±����ָ�
	Modbus_AddrData[0x52 + N + X][1] = ReadCfgData[28];
	// �������±���
	Modbus_AddrData[0x53 + N + X][0] = ReadCfgData[29];
	// �������±����ָ�
	Modbus_AddrData[0x53 + N + X][1] = ReadCfgData[30];
	// ��ѹ��ѹ����
	Modbus_AddrData[0x54 + N + X][0] = ReadCfgEData[2];
	Modbus_AddrData[0x54 + N + X][1] = ReadCfgEData[3];
	// ��ѹ��ѹ�����ָ�
	Modbus_AddrData[0x55 + N + X][0] = ReadCfgEData[4];
	Modbus_AddrData[0x55 + N + X][1] = ReadCfgEData[5];
	// ��ѹ���ű���
	Modbus_AddrData[0x56 + N + X][0] = ReadCfgEData[6];
	Modbus_AddrData[0x56 + N + X][1] = ReadCfgEData[7];
	// ��ѹ���Żָ�
	Modbus_AddrData[0x57 + N + X][0] = ReadCfgEData[8];
	Modbus_AddrData[0x57 + N + X][1] = ReadCfgEData[9];
	// ��ѹ��ѹ������ʱ
	Modbus_AddrData[0x58 + N + X][0] = ReadCfgEData[10] + 1;
	// ��ѹ���ű�����ʱ
	Modbus_AddrData[0x58 + N + X][1] = ReadCfgEData[11] + 1;
	// �ܹ�ѹ�ָ���ʱ
	Modbus_AddrData[0x59 + N + X][0] = ReadCfgEData[18] + 1;
	// �ܹ��Żָ���ʱ
	Modbus_AddrData[0x59 + N + X][1] = ReadCfgEData[19] + 1;
	// MOS���±���
	Modbus_AddrData[0x5A + N + X][0] = ReadCfgEData[23] + 1;
	// MOS���±����ָ�
	Modbus_AddrData[0x5A + N + X][1] = ReadCfgEData[24] + 1;
	// MOS���±�����ʱ
	Modbus_AddrData[0x5B + N + X][0] = ReadCfgEData[25] + 1;
	Modbus_AddrData[0x5B + N + X][1] = 0;
	// �������� ��ѹ����
	Modbus_AddrData[0x5C + N + X][0] = ReadFuelData[0];
	Modbus_AddrData[0x5C + N + X][1] = ReadFuelData[1];
	// �������� ��������
	Modbus_AddrData[0x5D + N + X][0] = ReadFuelData[2];
	Modbus_AddrData[0x5D + N + X][1] = ReadFuelData[3];
	// �������� ��ʱ
	Modbus_AddrData[0x5E + N + X][0] = ReadFuelData[10];
	Modbus_AddrData[0x5E + N + X][1] = 0;
	// ����/���ȿ����¶�
	Modbus_AddrData[0x5F + N + X][0] = ReadAlamData[22];
	// ����/���Ȼָ��¶�
	Modbus_AddrData[0x5F + N + X][1] = ReadAlamData[23];
	// ʹ������
	Modbus_AddrData[0x60 + N + X][0] = 0x01 & ReadCfgEData[1]; // ��ѹ��������
	Modbus_AddrData[0x60 + N + X][1] = ReadAlamData[0];
	// ��ѹ��ѹ�澯��ѹ
	Modbus_AddrData[0x61 + N + X][0] = ReadAlamData[1];
	Modbus_AddrData[0x61 + N + X][1] = ReadAlamData[2];
	// ��ѹ���Ÿ澯��ѹ
	Modbus_AddrData[0x62 + N + X][0] = ReadAlamData[3];
	Modbus_AddrData[0x62 + N + X][1] = ReadAlamData[4];
	// ��о��ѹ�澯��ѹ
	Modbus_AddrData[0x63 + N + X][0] = ReadAlamData[5];
	// ��о���Ÿ澯��ѹ
	Modbus_AddrData[0x63 + N + X][1] = ReadAlamData[6];
	// �������澯����
	Modbus_AddrData[0x64 + N + X][0] = ReadAlamData[7];
	// �ŵ�����澯����
	Modbus_AddrData[0x64 + N + X][1] = ReadAlamData[8];
	// �����¸澯�¶�
	Modbus_AddrData[0x65 + N + X][0] = ReadAlamData[9];
	// �����¸澯�¶�
	Modbus_AddrData[0x65 + N + X][1] = ReadAlamData[10];
	// �ŵ���¸澯�¶�
	Modbus_AddrData[0x66 + N + X][0] = ReadAlamData[11];
	// �ŵ���¸澯�¶�
	Modbus_AddrData[0x66 + N + X][1] = ReadAlamData[12];
	// MOS���¸澯�¶�
	Modbus_AddrData[0x67 + N + X][0] = ReadAlamData[13];
	// MOS���¸澯�ָ��¶�
	Modbus_AddrData[0x67 + N + X][1] = ReadAlamData[14];
	// ��о������澯ѹ��
	Modbus_AddrData[0x68 + N + X][0] = ReadAlamData[15];
	Modbus_AddrData[0x68 + N + X][1] = ReadAlamData[16];
	// ������澯�ָ�ѹ��
	Modbus_AddrData[0x69 + N + X][0] = ReadAlamData[17];
	Modbus_AddrData[0x69 + N + X][1] = ReadAlamData[18];
	// �������¸澯
	Modbus_AddrData[0x6A + N + X][0] = ReadAlamData[19];
	// �������¸澯
	Modbus_AddrData[0x6A + N + X][1] = ReadAlamData[20];
	// SOC�͸澯
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
	} // ��ַ������
	SendDataBuff[0] = ADDR;
	SendDataBuff[1] = 0x03;
	data = RegNum * 2;
	if (data > 250)
	{
		Modbus_SendError(pMSG, 0x03, 3);
		return;
	} // �Ƿ���������
	SendDataBuff[2] = data;
	for (i = 0; i < RegNum; i++) // ��������ӵ����ͻ�����
	{
		SendDataBuff[3 + i * 2] = Modbus_AddrData[StartAddr + i][0];
		SendDataBuff[4 + i * 2] = Modbus_AddrData[StartAddr + i][1];
	}
	Modbus_SerialStartSend(pMSG, SendDataBuff, data + 3);
}

// MUDBUS�������ݰ�У��
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
// ���� ���ڽ���ص����� ������������
void Modbus_SerialDecode(void)
{
	// MODBUSЭ�����
	//----------------------------MODBUSЭ�� UART1 �������----------------------------/
	if (MSG_SERIAL_UART1.RecOver == 2) // Modbus��ȡ���ݰ�
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART1.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_UART1.UARTx = 1;									 // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
			Modbus_SendData(&MSG_SERIAL_UART1, MSG_SERIAL_UART1.RecBuf); // ���� ��ȡ����
		}
		Modbus_ClearBuff_UART1(); // �建����
	}
	else if (MSG_SERIAL_UART1.RecOver == 3) // MOdbusд������
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART1.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_UART1.UARTx = 1;																																				   // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
		//	UserWriteDataToAddr(&MSG_SERIAL_UART1, (((UINT16)MSG_SERIAL_UART1.RecBuf[2]) << 8) | MSG_SERIAL_UART1.RecBuf[3], &MSG_SERIAL_UART1.RecBuf[7], MSG_SERIAL_UART1.RecBuf[5]); // ���� д������
		}
		Modbus_ClearBuff_UART1(); // �建����
	}
	//----------------------------MODBUSЭ�� UART2 �������----------------------------/
	if (MSG_SERIAL_UART2.RecOver == 2) // Modbus��ȡ���ݰ�
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART2.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_UART2.UARTx = 2;									 // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
			Modbus_SendData(&MSG_SERIAL_UART2, MSG_SERIAL_UART2.RecBuf); // ���� ��ȡ����
		}
		Modbus_ClearBuff_UART2(); // �建����
	}
	else if (MSG_SERIAL_UART2.RecOver == 3) // MOdbusд������
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART2.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_UART2.UARTx = 2;																																				   // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
		//	UserWriteDataToAddr(&MSG_SERIAL_UART2, (((UINT16)MSG_SERIAL_UART2.RecBuf[2]) << 8) | MSG_SERIAL_UART2.RecBuf[3], &MSG_SERIAL_UART2.RecBuf[7], MSG_SERIAL_UART2.RecBuf[5]); // ���� д������
		}
		Modbus_ClearBuff_UART2(); // �建����
	}
	//----------------------------MODBUSЭ�� UART3 �������----------------------------/
	if (MSG_SERIAL_UART3.RecOver == 2) // Modbus��ȡ���ݰ�
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART3.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_UART3.UARTx = 3;									 // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
			Modbus_SendData(&MSG_SERIAL_UART3, MSG_SERIAL_UART3.RecBuf); // ���� ��ȡ����
		}
		Modbus_ClearBuff_UART3(); // �建����
	}
	else if (MSG_SERIAL_UART3.RecOver == 3) // MOdbusд������
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART3.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_UART3.UARTx = 3;																																				   // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
	//		UserWriteDataToAddr(&MSG_SERIAL_UART3, (((UINT16)MSG_SERIAL_UART3.RecBuf[2]) << 8) | MSG_SERIAL_UART3.RecBuf[3], &MSG_SERIAL_UART3.RecBuf[7], MSG_SERIAL_UART3.RecBuf[5]); // ���� д������
		}
		Modbus_ClearBuff_UART3(); // �建����
	}
	//----------------------------MODBUSЭ�� UART4 �������----------------------------/
	if (MSG_SERIAL_UART4.RecOver == 2) // Modbus��ȡ���ݰ�
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART4.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_UART4.UARTx = 4;									 // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
			Modbus_SendData(&MSG_SERIAL_UART4, MSG_SERIAL_UART4.RecBuf); // ���� ��ȡ����
		}
		Modbus_ClearBuff_UART4(); // �建����
	}
	else if (MSG_SERIAL_UART4.RecOver == 3) // MOdbusд������
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_UART4.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_UART4.UARTx = 4;																																				   // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
		//	UserWriteDataToAddr(&MSG_SERIAL_UART4, (((UINT16)MSG_SERIAL_UART4.RecBuf[2]) << 8) | MSG_SERIAL_UART4.RecBuf[3], &MSG_SERIAL_UART4.RecBuf[7], MSG_SERIAL_UART4.RecBuf[5]); // ���� д������
		}
		Modbus_ClearBuff_UART4(); // �建����
	}
	//----------------------------MODBUSЭ�� CAN1 �������----------------------------/
	if (MSG_SERIAL_CAN1.RecOver == 2) // Modbus��ȡ���ݰ�
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_CAN1.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_CAN1.UARTx = 5;								   // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
			Modbus_SendData(&MSG_SERIAL_CAN1, MSG_SERIAL_CAN1.RecBuf); // ���� ��ȡ����
		}
		Modbus_ClearBuff_CAN1(); // �建����
	}
	else if (MSG_SERIAL_CAN1.RecOver == 3) // MOdbusд������
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_CAN1.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_CAN1.UARTx = 5;																																			  // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
		//	UserWriteDataToAddr(&MSG_SERIAL_CAN1, (((UINT16)MSG_SERIAL_CAN1.RecBuf[2]) << 8) | MSG_SERIAL_CAN1.RecBuf[3], &MSG_SERIAL_CAN1.RecBuf[7], MSG_SERIAL_CAN1.RecBuf[5]); // ���� д������
		}
		Modbus_ClearBuff_CAN1(); // �建����
	}
	//----------------------------MODBUSЭ�� CAN2 �������----------------------------/
	if (MSG_SERIAL_CAN2.RecOver == 2) // Modbus��ȡ���ݰ�
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_CAN2.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_CAN2.UARTx = 6;								   // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
			Modbus_SendData(&MSG_SERIAL_CAN2, MSG_SERIAL_CAN2.RecBuf); // ���� ��ȡ����
		}
		Modbus_ClearBuff_CAN2(); // �建����
	}
	else if (MSG_SERIAL_CAN2.RecOver == 3) // MOdbusд������
	{
		if (Modbus_UserRcvChk(MSG_SERIAL_CAN2.RecBuf)) // CRCУ����ȷ
		{
			MSG_SERIAL_CAN2.UARTx = 6;																																			  // �˿ں� ���߷��ͱ��뺯�������ĸ��˿ڽ��з���
	//		UserWriteDataToAddr(&MSG_SERIAL_CAN2, (((UINT16)MSG_SERIAL_CAN2.RecBuf[2]) << 8) | MSG_SERIAL_CAN2.RecBuf[3], &MSG_SERIAL_CAN2.RecBuf[7], MSG_SERIAL_CAN2.RecBuf[5]); // ���� д������
		}
		Modbus_ClearBuff_CAN2(); // �建����
	}
}


// ���ݽ���
void SerialDecodeHook(void)
{
 
/**************************UART1 ��λ�����ݽ���*********************/
    if(MSG_SERIAL_UART1.RecOver==1)//������յ����������ݱ�
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
							 MSG_SERIAL_UART1.UARTx=1; // �˿ں�
							 pMSGSERIAL= &MSG_SERIAL_UART1;  // ������ָ�븶����
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_UART1); return; } // У��  
							 SerialDecoding(&MSG_SERIAL_UART1.RecBuf[4]); // ������λ�����ݰ�
					}
			}else if(MSG_SERIAL_UART1.RecBuf[0]==0xeb) // ����Э��
			{
					if(MSG_SERIAL_UART1.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART1);return;} // 
					MSG_SERIAL_UART1.UARTx=1; // ���ݶ˿ں�
					pMSGSERIAL= &MSG_SERIAL_UART1; // ������ָ�븶����     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART1);} // У��
					LoadDataRecode(); // �����������ݰ�        
			} 	
			else if(MSG_SERIAL_UART1.RecBuf[0]==0X6E) // ����Э��
			{
				//	if(MSG_SERIAL_UART1.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART1);return;} // 
					MSG_SERIAL_UART1.UARTx=1; // ���ݶ˿ں�
					pMSGSERIAL= &MSG_SERIAL_UART1; // ������ָ�븶����     
			//		if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART1);} // У��
			//		LoadDataRecode(); // �����������ݰ�     
ModeBusRxUserHook(MSG_SERIAL_UART1.RecBuf,MSG_SERIAL_UART1.RecCount);	
			} 	
			ClrRcvBuf(&MSG_SERIAL_UART1); // �建������
	  }			
/**************************UART2 ��λ�����ݽ���*********************/
    if(MSG_SERIAL_UART2.RecOver==1)//������յ����������ݱ�
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
							 MSG_SERIAL_UART2.UARTx=2; // �˿ں�
							 pMSGSERIAL= &MSG_SERIAL_UART2;  // ������ָ�븶����
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_UART2); return; } // У��  
							 SerialDecoding(&MSG_SERIAL_UART2.RecBuf[4]); // ������λ�����ݰ�
					}
			}else if(MSG_SERIAL_UART2.RecBuf[0]==0xeb) // ����Э��
			{
					if(MSG_SERIAL_UART2.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART2);return;} // 
					MSG_SERIAL_UART2.UARTx=2; // ���ݶ˿ں�
					pMSGSERIAL= &MSG_SERIAL_UART2; // ������ָ�븶����     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART2);} // У��
					LoadDataRecode(); // �����������ݰ�        
			} 	
			ClrRcvBuf(&MSG_SERIAL_UART2); // �建������
	  }	
/**************************UART3 ��λ�����ݽ���*********************/
    if(MSG_SERIAL_UART3.RecOver==1)//������յ����������ݱ�
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
							 MSG_SERIAL_UART3.UARTx=3; // �˿ں�
							 pMSGSERIAL= &MSG_SERIAL_UART3;  // ������ָ�븶����
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_UART3); return; } // У��  
							 SerialDecoding(&MSG_SERIAL_UART3.RecBuf[4]); // ������λ�����ݰ�
					}
			}else if(MSG_SERIAL_UART3.RecBuf[0]==0xeb) // ����Э��
			{
					if(MSG_SERIAL_UART3.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART3);return;} // 
					MSG_SERIAL_UART3.UARTx=3; // ���ݶ˿ں�
					pMSGSERIAL= &MSG_SERIAL_UART3; // ������ָ�븶����     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART3);} // У��
					LoadDataRecode(); // �����������ݰ�        
			} 	
			ClrRcvBuf(&MSG_SERIAL_UART3); // �建������
	  }
/**************************UART4 ��λ�����ݽ���*********************/
    if(MSG_SERIAL_UART4.RecOver==1)//������յ����������ݱ�
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
							 MSG_SERIAL_UART4.UARTx=4; // �˿ں�
							 pMSGSERIAL= &MSG_SERIAL_UART4;  // ������ָ�븶����
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_UART4); return; } // У��  
							 SerialDecoding(&MSG_SERIAL_UART4.RecBuf[4]); // ������λ�����ݰ�
					}
			}else if(MSG_SERIAL_UART4.RecBuf[0]==0xeb) // ����Э��
			{
					if(MSG_SERIAL_UART4.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_UART4);return;} // 
					MSG_SERIAL_UART4.UARTx=4; // ���ݶ˿ں�
					pMSGSERIAL= &MSG_SERIAL_UART4; // ������ָ�븶����     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_UART4);} // У��
					LoadDataRecode(); // �����������ݰ�        
			} 	
			ClrRcvBuf(&MSG_SERIAL_UART4); // �建������
	  }	
/**************************CAN1 ��λ�����ݽ���*********************/
    if(MSG_SERIAL_CAN1.RecOver==1)//������յ����������ݱ�
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
							 MSG_SERIAL_CAN1.UARTx=5; // �˿ں�
							 pMSGSERIAL= &MSG_SERIAL_CAN1;  // ������ָ�븶����
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_CAN1); return; } // У��  
							 SerialDecoding(&MSG_SERIAL_CAN1.RecBuf[4]); // ������λ�����ݰ�
					}
			}else if(MSG_SERIAL_CAN1.RecBuf[0]==0xeb) // ����Э��
			{
					if(MSG_SERIAL_CAN1.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_CAN1);return;} // 
					MSG_SERIAL_CAN1.UARTx=5; // ���ݶ˿ں�
					pMSGSERIAL= &MSG_SERIAL_CAN1; // ������ָ�븶����     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_CAN1);} // У��
					LoadDataRecode(); // �����������ݰ�        
			} 	
			ClrRcvBuf(&MSG_SERIAL_CAN1); // �建������
	  }		
/**************************CAN1 ��λ�����ݽ���*********************/
    if(MSG_SERIAL_CAN2.RecOver==1)//������յ����������ݱ�
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
							 MSG_SERIAL_CAN2.UARTx=6; // �˿ں�
							 pMSGSERIAL= &MSG_SERIAL_CAN2;  // ������ָ�븶����
							 if(!RcvChk()){ ClrRcvBuf(&MSG_SERIAL_CAN2); return; } // У��  
							 SerialDecoding(&MSG_SERIAL_CAN2.RecBuf[4]); // ������λ�����ݰ�
					}
			}else if(MSG_SERIAL_CAN2.RecBuf[0]==0xeb) // ����Э��
			{
					if(MSG_SERIAL_CAN2.RecBuf[1]!=ADR) {ClrRcvBuf(&MSG_SERIAL_CAN2);return;} // 
					MSG_SERIAL_CAN2.UARTx=6; // ���ݶ˿ں�
					pMSGSERIAL= &MSG_SERIAL_CAN2; // ������ָ�븶����     
					if(!LoadRcvChk()) {ClrRcvBuf(&MSG_SERIAL_CAN2);} // У��
					LoadDataRecode(); // �����������ݰ�        
			} 	
			ClrRcvBuf(&MSG_SERIAL_CAN2); // �建������
	  }
   Modbus_SerialDecode(); //MODBUSЭ�����		
}

