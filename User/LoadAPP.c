//=======================================Copyright(c)====================================
// 											��������ӹɷ����޹�˾
//											�з��������С��
//												����� 
//-------------------------------------------------�ļ���Ϣ------------------------------
//�ļ���		: mcg.c 
//������		: ������
//��������		:  
//��	��		: MCGģ������
//-----------------------------------------------��ǰ�汾�޶�----------------------------
//�޸���		:
//��	��		: 
//�޸�����		:
//��	��		:
//=======================================================================================

//=======================================================================================
//ͷ�ļ�
//=======================================================================================
#include "stm32f10x.h"
#include "SYSTypeDef.h"
#include "BSPFLASH.h"
#include "LoadAPP.h"
#include "global.h"
//=======================================================================================
//������趨
//=======================================================================================
#define FLASH_IAP_ADDR		0x08000000  	//iap������ʼ��ַ(�����FLASH)
#define FLASH_APP1_ADDR   0x08002000 	

//=======================================================================================
//ȫ�ֱ�������
//=======================================================================================
u16 gFlashLoadData[e_CANLOAD_BUF_NUM] = {0};

static u8 sUartTxBuf[255] = {0};
extern __asm void GenerateSystemReset(void) ;
extern MSG *pMSGSERIAL;
//=======================================================================================
//��̬��������
//=======================================================================================
//=======================================================================================
//��������	: void ResetSoftByUpdateCommand(void)
//�������	: void
//�������	: void
//��̬����	: void
//��	��	: ��λ�豸
//ע	��	:  ����ʱ�������н�����ѯ
//=======================================================================================
static void ResetSoftByUpdateCommand(void);

//=======================================================================================
//��������	: static void ResetPro(void)
//�������	: void
//�������	: void
//��̬����	: void
//��	��	: �����λ
//ע	��	:  
//=======================================================================================
static void ResetPro(void);
//=======================================================================================
//��������
//=======================================================================================

//=======================================================================================
//��������	: static void ResetPro(void)
//�������	: addr:ջ����ַ
//�������	: void
//��̬����	: void
//��	��	: ����ջ����ַ
//ע	��	:  
//=======================================================================================

//=======================================================================================
//��������	: void BootloaderInit(void)
//�������	: void  
//�������	: void
//��̬����	: void
//��	��	: ��ʼ��CAN��¼����
//ע	��	:  
//=======================================================================================
void BootloaderInit(void)
{
		gFlashLoadData[e_DEVICE_TYPE] = 0xfe;
		gFlashLoadData[e_DEVICE_NUM] = 0xfe;

		gFlashLoadData[e_RUN_STATE] = e_PROGRAME_MODEL;
		gFlashLoadData[e_CANLOAD_STATE] = e_PRORUN_STATE;
		gFlashLoadData[e_SOFT_VERSION] = PRO_VERSION;
		gFlashLoadData[e_BOOT_VERSION] = PRO_VERSION;  
}

//=======================================================================================
//��������	: u16* flashUpdateByModbus(u8 fncCode, u8 sciNum, u16 address, u16 data)
//�������	: fncCode:������ sciNum:���ں� address:��ַ data:����
//�������	: void
//��̬����	: void
//��	��	: ���մ���
//ע	��	:  
//=======================================================================================
u16* flashUpdateByModbus(u8 fncCode, u8 sciNum, u16 address, u16 data)
{
    u16 *temp = (void *)0;
    u16  arrayIndex = 0;
    
    (void)sciNum;
    (void)data;
    
    switch(fncCode)
    {
        case 0x03:
            if(address >= BOOT_READ_START_ADDR && address <= BOOT_READ_END_ADDR)
            {
                arrayIndex = address - BOOT_READ_START_ADDR;    
                temp = &gFlashLoadData[arrayIndex];  
            }
            break;
        case 0x06:
        case 0x10:
            if(address >= BOOT_CMD_START_ADDR && address <= BOOT_CMD_END_ADDR)
            {
                arrayIndex = address - BOOT_READ_START_ADDR;
                temp = &gFlashLoadData[arrayIndex];
            }
            break;
			
        default:
            break;
    }
    
    ResetSoftByUpdateCommand();

    return (temp);    
}

//=======================================================================================
//��̬��������
//=======================================================================================
//=======================================================================================
//��������	: void ResetSoftByUpdateCommand(void)
//�������	: void
//�������	: void
//��̬����	: void
//��	��	: ��λ�豸
//ע	��	:  ����ʱ�������н�����ѯ
//=======================================================================================
static void ResetSoftByUpdateCommand(void)
{
    if(gFlashLoadData[e_USER_COMMAND] == e_Cmd_IntoTransmit && gFlashLoadData[e_FLASH_SECTION_NUM] == BOOT_TRANS_FLAG)
    {
        FlashErase(FLASH_END_ADDR,1);
        ResetPro();
    }
    else if(gFlashLoadData[e_USER_COMMAND] == e_Cmd_Reset && gFlashLoadData[e_FLASH_SECTION_NUM] == BOOT_TRANS_FLAG)
    {
        ResetPro();    
    }
}

//=======================================================================================
//��������	: static void ResetPro(void)
//�������	: void
//�������	: void
//��̬����	: void
//��	��	: �����λ
//ע	��	:  
//=======================================================================================
static void ResetPro(void)
{  	 
		GenerateSystemReset(); 
}

//CRC ѭ�������
const u8 auchCRCHi_exp[] = {
    0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
	0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0,
	0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01,
	0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41,
	0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81,
	0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0,
	0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01,
	0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40,
	0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
	0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0,
	0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01,
	0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
	0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
	0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0,
	0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01,
	0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81, 0x40, 0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41,
	0x00, 0xc1, 0x81, 0x40, 0x01, 0xc0, 0x80, 0x41, 0x01, 0xc0, 0x80, 0x41, 0x00, 0xc1, 0x81,
	0x40
};

const  u8 auchCRCLo_exp[] = {
	0x00, 0xc0, 0xc1, 0x01, 0xc3, 0x03, 0x02, 0xc2, 0xc6, 0x06, 0x07, 0xc7, 0x05, 0xc5, 0xc4,
	0x04, 0xcc, 0x0c, 0x0d, 0xcd, 0x0f, 0xcf, 0xce, 0x0e, 0x0a, 0xca, 0xcb, 0x0b, 0xc9, 0x09,
	0x08, 0xc8, 0xd8, 0x18, 0x19, 0xd9, 0x1b, 0xdb, 0xda, 0x1a, 0x1e, 0xde, 0xdf, 0x1f, 0xdd,
	0x1d, 0x1c, 0xdc, 0x14, 0xd4, 0xd5, 0x15, 0xd7, 0x17, 0x16, 0xd6, 0xd2, 0x12, 0x13, 0xd3,
	0x11, 0xd1, 0xd0, 0x10, 0xf0, 0x30, 0x31, 0xf1, 0x33, 0xf3, 0xf2, 0x32, 0x36, 0xf6, 0xf7,
	0x37, 0xf5, 0x35, 0x34, 0xf4, 0x3c, 0xfc, 0xfd, 0x3d, 0xff, 0x3f, 0x3e, 0xfe, 0xfa, 0x3a,
	0x3b, 0xfb, 0x39, 0xf9, 0xf8, 0x38, 0x28, 0xe8, 0xe9, 0x29, 0xeb, 0x2b, 0x2a, 0xea, 0xee,
	0x2e, 0x2f, 0xef, 0x2d, 0xed, 0xec, 0x2c, 0xe4, 0x24, 0x25, 0xe5, 0x27, 0xe7, 0xe6, 0x26,
	0x22, 0xe2, 0xe3, 0x23, 0xe1, 0x21, 0x20, 0xe0, 0xa0, 0x60, 0x61, 0xa1, 0x63, 0xa3, 0xa2,
	0x62, 0x66, 0xa6, 0xa7, 0x67, 0xa5, 0x65, 0x64, 0xa4, 0x6c, 0xac, 0xad, 0x6d, 0xaf, 0x6f,
	0x6e, 0xae, 0xaa, 0x6a, 0x6b, 0xab, 0x69, 0xa9, 0xa8, 0x68, 0x78, 0xb8, 0xb9, 0x79, 0xbb,
	0x7b, 0x7a, 0xba, 0xbe, 0x7e, 0x7f, 0xbf, 0x7d, 0xbd, 0xbc, 0x7c, 0xb4, 0x74, 0x75, 0xb5,
	0x77, 0xb7, 0xb6, 0x76, 0x72, 0xb2, 0xb3, 0x73, 0xb1, 0x71, 0x70, 0xb0, 0x50, 0x90, 0x91,
	0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9c, 0x5c,
	0x5d, 0x9d, 0x5f, 0x9f, 0x9e, 0x5e, 0x5a, 0x9a, 0x9b, 0x5b, 0x99, 0x59, 0x58, 0x98, 0x88,
	0x48, 0x49, 0x89, 0x4b, 0x8b, 0x8a, 0x4a, 0x4e, 0x8e, 0x8f, 0x4f, 0x8d, 0x4d, 0x4c, 0x8c,
	0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
	0x40
};

//===========================================================================
//��������	: static u16 GetModbusCRC16(u8 *data, u16 len)
//�������	: chkbuf: ָ����Ҫ��֤��ModBus��Ϣ֡��ָ��
//					  len   : ҪЧ���Modbus��Ϣ֡�ֽ�����������Ч����CRC
//�������	: UINT16: Ч����CRC	
//��̬����	: 
//��	��	: ���㲢����ModBus RTUģʽ����Ϣ��CRCЧ����
//ע	��	:  
//===========================================================================
static u16 CRC16(u8 *data, u16 len)
{
		u8   uchCRCHi = 0xff;   //CRC���ֽڳ�ʼ��
		u8   uchCRCLo = 0xff;   //CRC���ֽڳ�ʼ��
		u16  uIndex;            //��ѯ������
		u16  temp_code;

		while (len)
		{
				uIndex = (u16)(uchCRCHi ^ *data++);  
				uchCRCHi = (u8)(uchCRCLo ^ auchCRCHi_exp[uIndex]);
				uchCRCLo = auchCRCLo_exp[uIndex];
				len--;
		}
		
		temp_code = (u16)uchCRCHi;
		temp_code = (u16)(temp_code << 8);

		return(u16)(temp_code | uchCRCLo);
}

void UartTxQueueUser(u8 uartNum,u8 * pdata,u8 len)
{ 
	UINT8 i;
   for(i=0;i<len;i++)
  (*pMSGSERIAL).SendBuf[i] = pdata[i];
//  (*pMSGSERIAL).SendBuf[1] = 0x01;
//  (*pMSGSERIAL).SendBuf[2] = 0x01;
//  (*pMSGSERIAL).SendBuf[(*pMSGSERIAL).SendBuf[3] + 2] = LoadChkSum(&(*pMSGSERIAL).SendBuf[3], (*pMSGSERIAL).SendBuf[3] - 1);
//  (*pMSGSERIAL).SendBuf[(*pMSGSERIAL).SendBuf[3] + 3] = 0xF5;
  (*pMSGSERIAL).SendCount = len;
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
 
}
//=============================================================================
//��������: u8 ModeBusRxUserHook(u8 *pRxdata, u8 len)
//�������: 
//�������:
//����ֵ  : 
//��������: ����������ModbusЭ������п���Ϊ�ӻ���
//ע������: void
//=============================================================================
void ModeBusRxUserHook(u8 *pRxdata, u8 len)
{
		u8   addr = 0;
		u8   funcode = 0;
		u8   i = 0;
		u16  ModBusAddr     = 0;
		u16  ModBusRegLen   = 0;
		u8   ModBusDataLen  = 0;
		u8   ModBusSendLen = 0;
		u16  ModBusDataBuf = 0;
		u16  *temp = 0;
		u16  crc = 0;

		addr	= pRxdata[0];
		funcode = pRxdata[1];

		if(addr != 0x6e)
		{
				return;
		}
		
		sUartTxBuf[0] = addr;
		sUartTxBuf[1] = funcode;

		//��ȡ����
		ModBusAddr = pRxdata[2];
		ModBusAddr = (ModBusAddr << 8) | pRxdata[3];
		if(funcode == 0x03) 
		{		
			ModBusRegLen  = pRxdata[4];
			ModBusRegLen  = (ModBusRegLen << 8) | pRxdata[5];
		}
		else if(funcode == 0x06)
		{
			ModBusRegLen  =  1;
		}
		else if(funcode == 0x10)
		{
			ModBusRegLen  = pRxdata[4];
			ModBusRegLen  = (ModBusRegLen << 8) | pRxdata[5];
			ModBusDataLen = pRxdata[6];
		}

		ModBusDataLen = ModBusRegLen * 2;

		if(funcode == 0x03)
		{	
			sUartTxBuf[2] = ModBusDataLen;				
			if(ModBusDataLen > 60)
			{
				 return;
			}
			else
			{
					ModBusSendLen = ModBusDataLen + 3;
				
			}

			if(ModBusAddr >= BOOT_READ_START_ADDR && ModBusAddr <= BOOT_READ_END_ADDR)
			{	 	
				temp = flashUpdateByModbus(funcode,0,ModBusAddr,0);
				if(temp)
				{
					for(i = 0;i < ModBusDataLen;)
					{
						sUartTxBuf[i+3] = *(((u8*)temp)+ i + 1);
						sUartTxBuf[i+3+1] = *(((u8*)temp)+ i);
						i += 2;
						
					}
				}
			}
			
			//���óɷ���ģʽ
			crc = CRC16((u8*)&sUartTxBuf,(ModBusSendLen));
			sUartTxBuf[ModBusSendLen]    = (u8)(crc >> 8);
			sUartTxBuf[ModBusSendLen+1]  = (u8)(crc);
			
 
			(void)UartTxQueueUser(1,sUartTxBuf,ModBusSendLen + 2);
		}	
		//д������
		else if((funcode == 0x06) || (funcode == 0x10))
		{		
			if(ModBusDataLen > 60)
			{
					return;
			}
			else
			{		
				ModBusSendLen = 6;			
			}
		
			//д���ַ
			ModBusAddr = pRxdata[2];
			ModBusAddr = (ModBusAddr << 8) | pRxdata[3];
			sUartTxBuf[2] = pRxdata[2];						   
			sUartTxBuf[3] = pRxdata[3];
			sUartTxBuf[4] = pRxdata[4];						   
			sUartTxBuf[5] = pRxdata[5];
			
			//���Ϊд�����ַ
			if(funcode == 0x10)
			{
				ModBusRegLen  = pRxdata[4];
				ModBusRegLen  = (ModBusRegLen << 8) | pRxdata[5];
				ModBusDataLen = pRxdata[6];	

				if(ModBusAddr >= BOOT_CMD_START_ADDR && ModBusAddr <= BOOT_CMD_END_ADDR)
				{	 	
					temp = flashUpdateByModbus(funcode,0,ModBusAddr,0);
					if(temp)
					{
						for(i = 0;i < ModBusDataLen;)
						{
							*(((u8*)temp)+ i + 1) = pRxdata[i+7];
							*(((u8*)temp)+ i) = pRxdata[i+7+1];
							i += 2;
						}
					}
				}
			}
			else
			{
				ModBusDataBuf = pRxdata[4];
				ModBusDataBuf = (ModBusDataBuf << 8) + pRxdata[5];
			}

			crc = CRC16((u8*)&sUartTxBuf,(ModBusSendLen));
			sUartTxBuf[ModBusSendLen]    = (u8)(crc >> 8);
			sUartTxBuf[ModBusSendLen+1]  = (u8)(crc);		

		 	(void)UartTxQueueUser(1,sUartTxBuf,ModBusSendLen + 2);
			
		}
}


//========================================FILE END=======================================
