
#ifndef  _SERIAL_H
#define  _SERIAL_H

#include "CPU.h"

 

/********************* Э��˵�� ************************

���ݸ�ʽ����ʼ�ֽ�     (0xEA) +
          �豸��ַ���� (0x01) +
          ��ƷID       (0xD0) + 
          �������ݳ��� (Len)  +   //�����������ֽ�,�������ֽ� 
                        ����  + 
                        ����  +
          ��Len��ʼ�����У�� +
          �����ֽڣ�0xF5��

********************************************************/



#define  TX1IE_EN   USART1->CR1|=((UINT32)1<<7);//USART_ConfigInt(USART1, USART_INT_TXDE, ENABLE); //ʹ�ܽ����ж�//SET_BIT(USART1->CR1,   USART_CR1_TXEIE);       // ʹ�ܴ��ڷ����ж�
#define  TX1IE_DIS  USART1->CR1&=~((UINT32)1<<7);//USART_ConfigInt(USART1, USART_INT_TXDE, DISABLE); //CLEAR_BIT(USART1->CR1, USART_CR1_TXEIE);   // ��ֹ���ڷ����ж�
#define  RX1IE_EN   USART1->CR1|=((UINT32)1<<5);//USART_ConfigInt(USART1, USART_INT_RXDNE, ENABLE); //SET_BIT(USART1->CR1,   USART_CR1_RXNEIE);      // ʹ�ܴ��ڷ����ж�
#define  RX1IE_DIS  USART1->CR1&=~((UINT32)1<<5);//USART_ConfigInt(USART1, USART_INT_RXDNE, DISABLE);//CLEAR_BIT(USART1->CR1, USART_CR1_RXNEIE); 
#define  TX2IE_EN   USART2->CR1|=((UINT32)1<<7);//USART_ConfigInt(USART2, USART_INT_TXDE, ENABLE);//SET_BIT(USART2->CR1,   USART_CR1_TXEIE);       // ʹ�ܴ��ڷ����ж�
#define  TX2IE_DIS  USART2->CR1&=~((UINT32)1<<7);//USART_ConfigInt(USART2, USART_INT_TXDE, DISABLE);//CLEAR_BIT(USART2->CR1, USART_CR1_TXEIE);   // ��ֹ���ڷ����ж�
#define  RX2IE_EN   USART2->CR1|=((UINT32)1<<5);//USART_ConfigInt(USART2, USART_INT_RXDNE, ENABLE);//SET_BIT(USART2->CR1,   USART_CR1_RXNEIE);      // ʹ�ܴ��ڷ����ж�
#define  RX2IE_DIS  USART2->CR1&=~((UINT32)1<<5);//USART_ConfigInt(USART2, USART_INT_RXDNE, DISABLE);//CLEAR_BIT(USART2->CR1, USART_CR1_RXNEIE); 
 

#define  REC_MAX   300    // ������ջ������Ĵ�С
#define  SEND_MAX  300    // ���巢�ͻ������Ĵ�С

#define  SOI       0xEA      // ��ʼ��־

 #define  CID       0xD1      // �豸������
 #define  EOI       0xF5      // ������
 #define  ADR       0x01
 
 
 #define  SERIAL_TIME_ISR   10        // ��ʱ����� ms
 #define  TIME_OUT   10      // ���ճ�ʱʱ�� ms
 #define  TIME_SLEEP 10000      // ���߳�ʱʱ��
typedef struct 
{
   UINT8 RecBuf[REC_MAX];    // ���ջ�����
   UINT16 RecCount;          // ���յ��ֽ���
   UINT8 SendBuf[SEND_MAX];  // ���ͻ�����
   UINT16 SendCount;         // Ҫ���͵��ֽ���
   UINT8 RecOver;            // ������ɱ�־
   UINT16 RecTimer;          // ���ռ�ʱ��
	 UINT16 SleepTime;         // ���߼�ʱ
//	 UINT8 SleepFlag;          // ͨѶ���߱�־
	 UINT8 UARTx;              // ��ǰ�������ݻ������˿ں�
} MSG;
 
extern UINT8 MSG_SERIAL_CAN1_SleepFlag;
extern UINT8 MSG_SERIAL_CAN2_SleepFlag;
extern UINT8 MSG_SERIAL_UART1_SleepFlag;
extern UINT8 MSG_SERIAL_UART2_SleepFlag;
extern UINT8 MSG_SERIAL_UART3_SleepFlag;
extern UINT8 MSG_SERIAL_UART4_SleepFlag;


extern MSG *pMSGSERIAL;
 
extern  MSG MSG_SERIAL_UART1; // ������S_RAM ����
extern  MSG MSG_SERIAL_UART2; // ������S_RAM ����
extern  MSG MSG_SERIAL_UART3; // ������S_RAM ����
extern  MSG MSG_SERIAL_UART4; // ������S_RAM ����
extern  MSG MSG_SERIAL_CAN1;
extern  MSG MSG_SERIAL_CAN2;
//extern UINT32 KM;	
//extern UINT8 PowerOutputOk;
extern  UINT8 ADDR;
//extern  UINT8  UARTx;
extern  FP32 cellVlg;

extern void SerialInput(UINT8 RevData);
extern void SerialStartSend(UINT8 *pData);
extern void SerialTimer(void); // �ɶ�ʱ������
extern void SerialDecode(void);// ������������
extern void SerialOutput(void);

// �����жϽ��պ���
extern void SerialInput_UART1(UINT8 RevData);
extern void SerialInput_UART2(UINT8 RevData);
extern void SerialInput_UART3(UINT8 RevData);
extern void SerialInput_UART4(UINT8 RevData);
// �����жϷ��ͺ���
extern void SerialOutput_UART1(void);
extern void SerialOutput_UART2(void);
extern void SerialOutput_UART3(void);
extern void SerialOutput_UART4(void);
//���ܺ���
// ��������
//���ܺ���
// ��������
extern void SendCmd(UINT8 cmd1,UINT8 cmd2);
extern void SerialSendData(UINT8 cmd);
void SerialSendCurMul(UINT8 cmd1,UINT8 cmd2);
void SerialSendVlgMul(UINT8 cmd1,UINT8 cmd2); //��ѹ����
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





















