//=======================================Copyright(c)====================================
// 											��������ӹɷ����޹�˾
//											�з��������С��
//												����� 
//-------------------------------------------------�ļ���Ϣ------------------------------
//�ļ���		: mcg.h 
//������		: ������
//��������		:  
//��	��		: MCGģ������ͷ�ļ�
//-----------------------------------------------��ǰ�汾�޶�----------------------------
//�޸���		:
//��	��		: 
//�޸�����		:
//��	��		:
//=======================================================================================
#ifndef _CANLOAD_APP_H
#define _CANLOAD_APP_H

//=======================================================================================
//�궨��
//=======================================================================================
#define PRO_VERSION         (0x302)         /*����屾��*/
#define BOOT_TRANS_FLAG     (0x5AA5)        /*ת����־*/
#define BOOT_PRO_TRY_FLAG   (0x5AA5)        /*�Ѿ����Եı�־*/
#define  BOOT_ENRTY_POINT    (0x10fb)        /*Boot��ڵ�ַ*/

#define BOOT_READ_START_ADDR (33)           //RS485��¼�ɶ���ʼ��ַ(����)
#define BOOT_READ_END_ADDR   (41)           //RS485��¼�ɶ�������ַ(����)

#define BOOT_CMD_START_ADDR (42)            //RS485��¼��д��ʼ��ַ(����)
#define BOOT_CMD_END_ADDR   (43)            //RS485��¼��д������ַ(����)

//=======================================================================================
//���ݶ���
//=======================================================================================
typedef enum _BOOT_STATE_INFO
{
    e_PRO_TYPE     = 0,            //Э������
    e_DEVICE_TYPE  = 1,            //�豸����
    e_DEVICE_NUM   = 2,            //�豸��
    e_CHIP_TYPE    = 3,            //оƬ����
    e_SOFT_VERSION = 4,             //����汾��
    e_BOOT_VERSION = 5,             //BOOT�汾��
    e_CANLOAD_STATE = 6,            //��¼״̬
    e_RUN_STATE     = 7,            //����״̬
    e_LOADING_NUM   = 8,            //������д�Ķκ�
    e_USER_COMMAND  = 9,            //�û�ָ��
    e_FLASH_SECTION_NUM = 10,       //�γ�      
    e_CANLOAD_BUF_NUM = 11           //���ݶγ���
}e_BOOT_STATE_INFO;

typedef enum _MCU_TYPE_
{
    e_FREESCALE_DZ60 = 0,       //оƬ����
    e_FREESCALE_XEQ512 = 1,
    e_COMTEX_TM4C129ENDPT = 2,
}e_MCU_TYPE;

typedef enum _RUNMODEL_ENUM_
{
    e_TRANSMIT_MODEL = 0,    //ת��ģʽ
    e_CANLOAD_MODEL = 1,     //��¼ģʽ
    e_PROGRAME_MODEL = 2,    //Ӧ�ó�������ģʽ   
}e_RUNMODEL_ENUM;

typedef enum _RUNMODEL_STATE_
{
    e_LOADTRANSMIT_STATE    = 0,            /*��Ӧ�ó���ת��״̬*/
    e_PROTRANSMIT_STATE     = 1,            /*Ӧ�ó���ת��״̬*/
    e_CANLOADREADY_OK       = 2,            /*��¼׼��*/
    e_CANLOADREADY_FAIL     = 3,            /*��¼׼��ʧ��*/
   // e_CANLOADPRE_OK         = 4,            /*��¼����*/
    e_CANLOADTRANSMITING    = 5,            /*���ڴ���*/   
    e_CANLOADTRANSMIT_FAIL  = 6,            /*����ʧ��*/
 //   e_CANLOADTRANSMIT_OK    = 7,            /*����ɹ�*/
    e_CANLOADFLASH_FAIL     = 8,            /*��¼ʧ��*/
    e_CANLOADFLASH_OK       = 9,             /*��¼�ɹ�*/
    e_PRORUN_STATE          = 10,           /*Ӧ�ó�������״̬*/
}e_RUNMODEL_STATE;

typedef enum _MESSAGE_TYPE_
{
    e_Cmd_IntoTransmit      = 0xE0,                 /*����ת��ģʽ*/
    e_Cmd_ExitTransmit      = 0xE1,                 /*�˳�ת��ģʽ*/
    e_Cmd_Reset             = 0xE2,                 /*����λ*/
    e_Cmd_IntoLoad          = 0xE3,                 /*������¼*/
    e_Cmd_ExitLoad          = 0xE4,                 /*�˳���¼*/
    e_Cmd_FinishLoad        = 0xE5,                 /*��¼���*/
}e_MESSAGE_TYPE;


typedef enum _BOOT_FLAG_ADDR_               /*��ʼ��ַΪ0xD600*/
{
    e_BOOT_TRANSMIT_FLAG_ADDR = 6,          /*ת��ģ־��ŵ�ַ*/
    e_BOOT_CRC_ADDR = 8,                    /*Ӧ�ó���CRC��ŵ�ַ*/
    e_BOOT_PRO_FLAG_ADDR = 10,              /*Ӧ�ó����־*/
    e_BOOT_PRO_TRY_FLAG_ADDR = 12,          /*�������б�־*/
    e_BOOT_PRO_VERSION_ADDR = 14,           /*Ӧ�ó���汾��*/ 
    e_BOOT_SOTE_VERION_ADDR = 16,           /*Boot����汾�Ŵ洢��ַ*/
    e_BOOT_NETECU_FLAG = 20,               /*�豸�ż��豸���ͱ�־��ŵ�ַ*/
	e_BOOT_NET_ADDR = 22,                  /*�豸���ʹ�ŵ�ַ*/
    e_BOOT_ECU_ADDR = 24,                  /*�豸�Ŵ�ŵ�ַ*/

}E_BOOT_FLAG_ADDR;

//=======================================================================================
//�����ӿں���
//=======================================================================================
//=======================================================================================
//��������	: u16* flashUpdateByModbus(u8 fncCode, u8 sciNum, u16 address, u16 data)
//�������	: fncCode:������ sciNum:���ں� address:��ַ data:����
//�������	: void
//��̬����	: void
//��	��	: ���մ���
//ע	��	:  
//=======================================================================================
u16* flashUpdateByModbus(u8 fncCode, u8 sciNum, u16 address, u16 data);

//=======================================================================================
//��������	: void BootloaderInit(void)
//�������	: void  
//�������	: void
//��̬����	: void
//��	��	: ��ʼ��CAN��¼����
//ע	��	:  
//=======================================================================================
void BootloaderInit(void);

#endif
