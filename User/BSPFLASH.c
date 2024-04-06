#include "BSPFLASH.h"
#include "SYSTypeDef.h"

u16 STMFLASH_BUF[STM_SECTOR_SIZE/2];//�����2K�ֽ�


#define ERR_FLASH_WR        1           //flashд����
#define ERR_FLASH_RD        1           //flash������
//#define NULL                   ((void *) 0)
	
#define FLASH_WR_BYTE(addr) *(vu8*)addr;

//��̬��������
//=======================================================================================
//�������ƣ�void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
//���������ReadAddr	��ַ  pBuffer  NumToRead
//���������0-->�ɹ�	��0-->ʧ��
//����������  Flash��Ϊ����д
//ע	�⣺
//=======================================================================================
static void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);
//=======================================================================================
//�������ƣ�static u8 FlashSectionErase(u32 addr)
//���������addr	��ַ
//���������0-->�ɹ�	��0-->ʧ��
//����������flash��������
//ע	�⣺
//=======================================================================================
static u8 FlashSectionErase(u32 Addr);

//=======================================================================================
//�������ƣ�void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
//���������ReadAddr	��ַ  pBuffer  NumToRead
//���������0-->�ɹ�	��0-->ʧ��
//����������  Flash��Ϊ����д
//ע	�⣺
//=======================================================================================
static void STMFLASH_Write_NoCheck(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
    u16 i;
    for(i=0;i<NumToWrite;i++)
    {
        FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
        WriteAddr+=2;//��ַ����2.
    }  
}   
//=======================================================================================
//�������ƣ�static u8 FlashSectionErase(u32 addr)
//���������addr	��ַ
//���������0-->�ɹ�	��0-->ʧ��
//����������flash��������
//ע	�⣺
//=======================================================================================
static u8 FlashSectionErase(u32 Addr)
{
		volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
	
		if((Addr % FLASH_PAGE_SIZE) != 0)
		{
				return FALSE;
		}
		
		FLASH_UnlockBank1();//����BANK1��ֻ�н�������ܲ�����д��
		FLASHStatus = FLASH_ErasePage(Addr);	//����FLASH
		FLASH_LockBank1();//������ɺ����
		
		if(FLASH_COMPLETE == FLASHStatus)
		{
				return TRUE;
		}
		else
		{
				return FALSE;
		}	
}
//=======================================================================================
//�������ƣ�u16 STMFLASH_ReadHalfWord(u32 faddr)
//���������ReadAddr	��ַ  pBuffer  NumToRead
//���������0-->�ɹ�	��0-->ʧ��
//����������  ����Flash��ַ������
//ע	�⣺
//=======================================================================================
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
    return *(vu16*)faddr; 
}
//=======================================================================================
//�������ƣ�u8 FlashReadByte(u32 addr, u8* pData, u32 len)
//���������addr	��ַ
//			buf		������
//          size	��������С
//���������0-->�ɹ�	��0-->ʧ��
//����������flash������
//ע	�⣺
//=======================================================================================
void FlashReadByte(u32 addr, u8* pData, u32 len)
{   
	if(addr < FLASH_START_ADDR || addr > FLASH_END_ADDR)
	{
		return; 
	}

	if(pData == NULL)
	{
		return; 
	}

	while(len--)
	{
		*pData = FLASH_WR_BYTE(addr);
		pData++;
		addr++;
	}

}
//=======================================================================================
//�������ƣ�void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)
//���������ReadAddr	��ַ  pBuffer  NumToRead
//���������0-->�ɹ�	��0-->ʧ��
//����������  дFlash�ĵײ㺯��
//ע	�⣺
//=======================================================================================
void STMFLASH_Write(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
    u32 secpos;	   //������ַ
    u16 secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
    u16 secremain; //������ʣ���ַ(16λ�ּ���)	   
    u16 i;    
    u32 offaddr;   //ȥ��0X08000000��ĵ�ַ
    if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//�Ƿ���ַ
    FLASH_Unlock();						//����
    offaddr=WriteAddr-STM32_FLASH_BASE;		        //ʵ��ƫ�Ƶ�ַ.
    secpos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
    secoff=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
    secremain=STM_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
    if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
    while(1) 
    {	
        STMFLASH_Read(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//������������������
        for(i=0;i<secremain;i++)//У������
        {
            if(STMFLASH_BUF[secoff+i]!=0XFFFF)break;//��Ҫ����  	  
        }
        if(i<secremain)//��Ҫ����
        {
            FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//�����������
            for(i=0;i<secremain;i++)//����
            {
                STMFLASH_BUF[i+secoff]=pBuffer[i];	  
            }
            STMFLASH_Write_NoCheck(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF,STM_SECTOR_SIZE/2);//д����������  
        }else STMFLASH_Write_NoCheck(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
        if(NumToWrite==secremain)break;//д�������
        else//д��δ����
        {
            secpos++;				//������ַ��1
            secoff=0;				//ƫ��λ��Ϊ0 	 
            pBuffer+=secremain;  	//ָ��ƫ��
            WriteAddr+=secremain;	//д��ַƫ��	   
            NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
            if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//��һ����������д����
            else secremain=NumToWrite;//��һ����������д����
        }	 
    };	
    FLASH_Lock();//����
}  
//=======================================================================================
//�������ƣ�void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead) 
//���������ReadAddr	��ַ  pBuffer  NumToRead
//���������0-->�ɹ�	��0-->ʧ��
//����������  ��ȡflash����
//ע	�⣺
//=======================================================================================
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
    u16 i;
    for(i=0;i<NumToRead;i++)
    {
        pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
        ReadAddr+=2;//ƫ��2���ֽ�.	
    }
}
 

//=======================================================================================
//�������ƣ�u8 FlashErase(u32 addr, u8 size)
//���������addr	��ַ    size  ҳ��С
//���������0-->�ɹ�	��0-->ʧ��
//����������flash��������  addrΪҳ���׵�ַ��size��ҳ�Ĵ�С
//ע	�⣺
//=======================================================================================
u8 FlashErase(u32 addr, u8 size)
{	
	u16 i = 0;

	for(i = 0;i < size;i++)
	{
		(void)FlashSectionErase(addr);
		addr += FLASH_BLOCK_SIZE;
	}

	return OK;
}
//=======================================================================================
//�������ƣ�u8 FlashWriteSection(u32 addr, u8* Data, u8 Length);
//���������addr	��ַ
//			buf		д����
//			size	��������С
//���������0-->�ɹ�	��0-->ʧ��
//����������flashд����
//ע	�⣺STM32ÿ��д��������ֻ��߰��� ��Length����Ϊż��
//=======================================================================================
u8 FlashWriteSection(u32 addr, u8* Data, u16 Length)
{
		u16 i = 0;
		u16 flashHalfWord = 0xffff;
		u32 realAddr = 0;
		volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

		if((FALSE == FlashSectionErase(addr)) || (Length % 2 == 1))
		{
				return FALSE;
		}

		realAddr = addr;
		FLASH_UnlockBank1();//����BANK1��ֻ�н�������ܲ�����д��
		for(i = 0; i < Length; i += 2)
		{
				flashHalfWord = Data[i+1];
				flashHalfWord = (flashHalfWord << 8) + Data[i];
				FLASHStatus = FLASH_ProgramHalfWord(realAddr, flashHalfWord);	//д��FLASH
				realAddr += 2;
		}
		FLASH_LockBank1();//������ɺ����

		if(FLASHStatus == FLASH_COMPLETE)
		{
				return TRUE;
		}
		else
		{
				return FALSE;
		}	
}








