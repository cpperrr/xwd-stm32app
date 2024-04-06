
 

#ifndef   _GlOBAL_H
#define   _GlOBAL_H

#include "stm32f10x.h"  

 
 
#include "CPU.h"
#include "serial.h"
  
	
	extern void ModbusSendDataCode(void);
// ����
typedef struct
{
 // UINT8  OCVlg;
  UINT16 CHGOC1Dly;
	UINT16 DSGOC1Dly;
  FP32  DSGOC1;            // �ŵ�һ������
  FP32  CHGOC1;             // ���һ������
  // �����ָ��趨
  UINT8 CHGOCAutoCbSet; // ����Զ��ָ����� 
  UINT8 CHGOCAutoCbInterval; // ����Զ��ָ�ʱ����
  UINT8 CHGOCAutoCbCounter; // ����Զ��ָ�����
  UINT8 CHGOCDSGAutoCbSet; // �������ŵ��Զ��ָ�
  UINT8 DSGOCAutoCbSet; // �ŵ��Զ��ָ�����
  UINT8 DSGOCAutoCbInterval; // �ŵ��Զ��ָ�ʱ����
  UINT8 DSGOCAutoCbCounter; // �ŵ��Զ��ָ�����
  UINT8 DSGOCCHGAutoCbSet; // �ŵ��������Զ��ָ�
  
  UINT16 CHGOCCbCount; // �������ָ�����������
  UINT16 DSGOCCbCount;
  UINT8 OCALAMSet;   // �����澯����
  FP32 CHGOCALAM;   // �������澯
  FP32 DSGOCALAM;    // �ŵ�����澯
  FP32 CHGOCALAMCB;   // �������澯
  FP32 DSGOCALAMCB;    // �ŵ�����澯
  UINT8 OC;
	UINT8 SC;
  UINT8 CHG_LCur; // ���������С
}OCCB;

// ����
typedef struct
{
  FP32  Dif;          // ����ѹ��
  FP32  BSVlg;              // ���⿪����ѹ
  UINT32 BCellData[2];  
  UINT16 BTime;
  UINT16 LBTime_ST;
  UINT16 LBTimeSet;
 // UINT8  BLA_FLAG_ST;
  UINT8 StaticBlance;
	UINT8 ImbalaceAlamSet;
	FP32 ImbalaceAlamVlg;
	FP32 ImbalaceAlamCbVlg;
	UINT16 BQ_BTime;
	UINT16 BQ_BTime_H;
}BLACB;


// ��־�ṹ��
typedef struct
{
  // ����
  UINT8  OT_FLAG;             // ���±�־
  UINT8  OTC_MAY_FLAG;         // �������±�־
  UINT8  OTC_CB_MAY_FLAG;      // �������»ָ���־
  UINT8  OTD_MAY_FLAG;         // �ŵ�����±�־
  UINT8  OTD_CB_MAY_FLAG;      // �ŵ�����»ָ���־
  UINT8  OT_TIME_START_FLAG;     // ������ʱ��ʱ����
  UINT8  OT_CB_TIME_START_FLAG;  // ���»ָ���ʱ��ʱ����
  // ���¸澯
  UINT8  OTC_ALAM_FLAG;             // ���±�־
  UINT8  OTD_ALAM_FLAG;             // ���±�־
  UINT8  OTC_MAY_ALAM_FLAG;         // �������±�־
  UINT8  OTC_CB_MAY_ALAM_FLAG;      // �������»ָ���־
  UINT8  OTD_MAY_ALAM_FLAG;         // �ŵ�����±�־
  UINT8  OTD_CB_MAY_ALAM_FLAG;      // �ŵ�����»ָ���־
  UINT8  OT_TIME_START_ALAM_FLAG;     // ������ʱ��ʱ����
  UINT8  OT_CB_TIME_START_ALAM_FLAG;  // ���»ָ���ʱ��ʱ����
	UINT8  EVOT_ALAM_FLAG;             // ���±�־
	UINT8  EVOT_FLAG;
	UINT8  MOSOT_ALAM_FLAG;
	// ��ѹ
  UINT8  OV_FLAG;             // ��ѹ��־
  UINT8  OV_MAY_FLAG;         // ���ѹ��־
  UINT8  OV_CB_MAY_FLAG;      // ���ѹ�ָ���־
  UINT8  OV_TIME_START_FLAG;  // ��ѹ��ʱ��ʱ����
  UINT8  OV_CB_TIME_START_FLAG;    // ��ѹ�ָ���ʱ��ʱ����
 // UINT8  TOV_FLAG;             // ��ѹ��־
  UINT8  TOV_MAY_FLAG;         // ���ѹ��־
  UINT8  TOV_CB_MAY_FLAG;      // ���ѹ�ָ���־
  UINT8  TOV_TIME_START_FLAG;  // ��ѹ��ʱ��ʱ����
  UINT8  TOV_CB_TIME_START_FLAG;    // ��ѹ�ָ���ʱ��ʱ����
  // Ƿѹ
  UINT8  UV_FLAG;             // Ƿѹ
  UINT8  UV_MAY_FLAG;         // ���ѹ��־
  UINT8  UV_CB_MAY_FLAG;      // ���ѹ�ָ���־
  UINT8  UV_TIME_START_FLAG;  // ��ѹ��ʱ��ʱ����
  UINT8  UV_CB_TIME_START_FLAG;    // ��ѹ�ָ���ʱ��ʱ����
 // UINT8  TUV_FLAG;             // ��ѹ��־
  UINT8  TVP_SET; // ��ѹ������־ 
  UINT8  TUV_MAY_FLAG;         // ���ѹ��־
  UINT8  TUV_CB_MAY_FLAG;      // ���ѹ�ָ���־
  UINT8  TUV_TIME_START_FLAG;  // ��ѹ��ʱ��ʱ����
  UINT8  TUV_CB_TIME_START_FLAG;    // ��ѹ�ָ���ʱ��ʱ����
  UINT8  UV_ALAM_FLAG;             // Ƿѹ
  UINT8  UV_MAY_ALAM_FLAG;         // ���ѹ��־
  UINT8  UV_CB_MAY_ALAM_FLAG;      // ���ѹ�ָ���־
  UINT8  UV_TIME_START_ALAM_FLAG;  // ��ѹ��ʱ��ʱ����
  UINT8  UV_CB_TIME_START_ALAM_FLAG;    // ��ѹ�ָ���ʱ��ʱ����
  UINT8  TUV_ALAM_FLAG;             // Ƿѹ
  UINT8  TUV_MAY_ALAM_FLAG;         // ���ѹ��־
  UINT8  TUV_CB_MAY_ALAM_FLAG;      // ���ѹ�ָ���־
  UINT8  TUV_TIME_START_ALAM_FLAG;  // ��ѹ��ʱ��ʱ����
  UINT8  TUV_CB_TIME_START_ALAM_FLAG;    // ��ѹ�ָ���ʱ��ʱ����
  UINT8  OV_ALAM_FLAG;             // Ƿѹ
  UINT8  OV_MAY_ALAM_FLAG;         // ���ѹ��־
  UINT8  OV_CB_MAY_ALAM_FLAG;      // ���ѹ�ָ���־
  UINT8  OV_TIME_START_ALAM_FLAG;  // ��ѹ��ʱ��ʱ����
  UINT8  OV_CB_TIME_START_ALAM_FLAG;    // ��ѹ�ָ���ʱ��ʱ����
  UINT8  TOV_ALAM_FLAG;             // Ƿѹ
  UINT8  TOV_MAY_ALAM_FLAG;         // ���ѹ��־
  UINT8  TOV_CB_MAY_ALAM_FLAG;      // ���ѹ�ָ���־
  UINT8  TOV_TIME_START_ALAM_FLAG;  // ��ѹ��ʱ��ʱ����
  UINT8  TOV_CB_TIME_START_ALAM_FLAG;    // ��ѹ�ָ���ʱ��ʱ����
  UINT8  OC_SC_FLAG;          // ������·��־
  UINT8  CHG_FLAG;             // ���ڳ��ȫ�ֱ�־
  UINT8  DSG_FLAG;            // ���ڷŵ�ȫ�ֱ�־
  UINT8  SEND_VLG_FLAG;       // ��ѹ�����־
  UINT8  SLEEP_UP_FLAG;       // ���߻��ѱ�־
  UINT8  AVR_CUR_START_FLAG;  // ƽ������������־
  UINT8  BLA_START_FLAG;      // ����������־

  UINT8  WATCH_START_FLAG;    // ����������־
  UINT8  BLA_FLAG_ST;
  UINT8  RS485_FLAG;
  UINT8  OPNoCtr_FLAG;
  // ʧЧ��־
  UINT8  CHGFail_FLAG; // ���MOSʧЧ
  UINT8  DSGFail_FLAG; // �ŵ�MOSʧЧ
  UINT8  VlgFail_FLAG; // ��ѹʧЧ
  UINT8  TempFail_FLAG;// �¶�ʧЧ
  // �����澯��־
  UINT8  CHGOCALAM_FLAG;
  UINT8  DSGOCALAM_FLAG;
  UINT8  LCUR_SET;  // �������ñ�־
  UINT8  SPWMCHGCur_FLAG; // ������������־
  UINT8  DSG_EN_FLAG;
  UINT8  CHG_EN_FLAG;
  // �¶ȸߵ͸澯��־
  UINT8  HT_ALAM_FLAG; // ���¸澯
  UINT8  LT_ALAM_FLAG; // ���¸澯
  UINT8  IMBALANCE_ALAM_FLAG; // ��о������澯 
	UINT8  OTMOS_FLAG;
	UINT8  SOCL_ALAM_FLAG;
}FCB;

typedef struct
{
   FP32  CellMul[31];
   FP32  CellVlg[32+1];        // �������е�ص�ѹ
   INT16  TemReg[10];    // �����¶�
   FP32  TotalVlg;    // �ܵ�ѹ
	 INT16 EnvironmentTemp;
	// INT16 ClibEnvironmentTemp;
}VCB;

typedef struct 
{
  UINT8 start_flash_LED1; 
  UINT8 start_flash_LED2; 
  UINT8 start_flash_LED3; 
  UINT8 start_flash_LED4; 
  UINT16 LED1Time;
  UINT16 LED2Time;
  UINT16 LED3Time;
  UINT16 LED4Time;
}FUELLEDCB;

typedef struct 
{
  
  UINT8  start_idle; 
  UINT32 idle_time;
	//UINT16 KeyTime;
}TICB;
typedef struct 
{ 
  UINT8 year; 
  UINT8 month;
  UINT8 day;
  UINT8 hour;
  UINT8 minute;
  UINT8 Second;
}RTCCCB;


typedef struct
{
   UINT16    CHGRemTime;       // ���ʣ��ʱ��
   UINT16    DSGRemTime;       // �ŵ�ʣ��ʱ�� 
   INT32  CapCount;         // �����ۻ�
   INT32  RemCapT1;         // t1ʱ��ʣ������
   INT32  RemCapT2;         // t2ʱ��ʣ������
   FP32     CHGCur;           // ���������ŵ�ʣ��ʱ��
   FP32     DSGCur;
   UINT8     FuelChange;         // �����������ݸı�
   UINT8     LAST_CHARGE_FULL_FLAG;     // ���������?
   UINT8     FUEL_CHANGE_FLAG;
   FP32     RS485Cur;
   UINT16    CHGTimeInterval;   // ��������ʱ��
   UINT16    CHGTimeIntervaler; // ������ʱ��  
   FP32     T_U; // �¶�˥��ϵ�� ������ 
   FP32     Fuel_UpTVol;   // �����ܵ�ѹ
   FP32     Fuel_UpCur;    // ���µ���  
   FP32     Set_1TempH; // ����25��ÿ����һ��˥��ϵ�� 
   FP32     Set_1TempL; // ����25��ÿ����һ��˥��ϵ��
   FP32     SetCycleCount_U; // ÿѭ��һ��������˥��ϵ��
	 UINT16    Fuel_UpDelay;
	 FP32     SelfDsg; // �Էŵ���
	 FP32     CycalCapPro; // ѭ��������
	 FP32     SOC8Vlg; // 8%��Ӧ��ѹ
   UINT8     SOCLALAMSet;
	 UINT8     SOCLALAMSOC;
	 UINT32    TotalDSGTime; // �ۼƷŵ�ʱ��
	 UINT32    TotalCHGTime; // �ۼƳ��ʱ��
}soc_cb;

// ��������
typedef struct 
{
  FP32          RemFullCap;   // ��о��
  UINT32        RemFullCapDesign; //��������� ��λAH
  INT32         RemCap;       // ��ǰʣ������ 
  INT32         DSGCap;       // �ۻ��ŵ�����
  UINT16        CycleCount;   // ѭ������ 
  UINT8         PercentCap;   // ������
	UINT8         PercentCap2;
	UINT8         VirtualPercentCap;// SOC�߶���Ͷ����⻯֮���SOC
	UINT16        RemSOE;          // ��ǰSOE ��λWH
	FP32          RemFullSOE;   // ��ǰ������
	UINT32        RemFullSOEDesign; //��������� ��λWH
}SOCCB;

// �������ƿ�
typedef struct
{ 
  FP32  DSGCnt;         // �ŵ糣��
  FP32  CHGCnt;         // ��糣��
  FP32  DSGMul;       // ����ŵ�Ŵ��� 
  FP32  CHGMul;       // ������Ŵ��� 
  FP32  DSGCur;         // �ŵ����    
  FP32  CHGCur;         // ������
  FP32  CHGCur_;        // ��ڵ�����������
  FP32  DSGCur_;
  FP32  CHGCur5s;
  FP32  DSGCur5s;
}CCB;



// Ƿѹ���ƿ�
typedef struct
{
  FP32  UVVlg;           // ��ѹֵ
  FP32  UVCbVlg;         // ��ѹ�ָ���ѹ
  UINT16 UVDly;           // ��ѹ��ʱ
  UINT16 UVCbDly;         // ��ѹ�ָ���ʱ
  FP32  LVlg;            // ��ߵ�ص�ѹ
  UINT16 LNum;            // ��͵�ѹ��غ�
  UINT16 UVTime;          // ��ѹ��ʱ��  
  UINT16 UVCbTime;        // ��ѹ�ָ���ʱ��
  FP32  TUVVlg;           // ��ѹֵ
  FP32  TUVCbVlg;         // ��ѹ�ָ���ѹ
  UINT16 TUVDly;           // �ܵ�ѹǷѹ��ʱ
  UINT16 TUVCbDly;         // �ܵ�ѹǷѹ�ָ���ʱ
  UINT16 TUVTime;          // �ܵ�ѹǷѹ��ʱ��  
  UINT16 TUVCbTime;        // �ܵ�ѹǷѹ�ָ���ʱ�� 
  UINT8  UVALAMSet;
  FP32  UVALAMVlg;           // ��ѹֵ
  FP32  UVCbALAMVlg;         // ��ѹ�ָ���ѹ
  UINT16 UVALAMDly;           // ��ѹ��ʱ
  UINT16 UVCbALAMDly;         // ��ѹ�ָ���ʱ
  UINT16 UVALAMTime;          // ��ѹ��ʱ��  
 // UINT16 UVCbALAMTime;        // ��ѹ�ָ���ʱ�� 
  FP32  TUVALAMVlg;           // ��ѹֵ
  FP32  TUVCbALAMVlg;         // ��ѹ�ָ���ѹ 
  UINT16 TUVALAMDly;           // ��ѹ��ʱ
  UINT16 TUVCbALAMDly;         // ��ѹ�ָ���ʱ
  UINT16 TUVALAMTime;          // ��ѹ��ʱ��  
 // UINT16 TUVCbALAMTime;        // ��ѹ�ָ���ʱ�� 
	FP32  ShutdownVlg;
  UINT32  ShutdownTime;		
}UVCB;


// ���¿��ƿ�
typedef struct
{
  INT16  OTCHTemp;
  INT16  OTCHCbTemp;
  INT16  OTCLTemp; 
  INT16  OTCLCbTemp;
  INT16  OTDHTemp;
  INT16  OTDHCbTemp;
  INT16  OTDLTemp; 
  INT16  OTDLCbTemp;  
  UINT16 OTDly;          // ������ʱ
  UINT16 OTCbDly;        // �ָ�   
  UINT16 OTTime;         // ���¼�ʱ��
  UINT16 OTCbTime;       // ���»ָ���ʱ��
  UINT16 OTNum;          // ���±��
  INT16    HTemp;
  UINT8  HRegNum; 
  INT16    LTemp;
  UINT8  LRegNum;
  UINT8 OTALAMSet; 
  INT16  OTCHALAMTemp;
  INT16  OTCLALAMTemp; 
  INT16  OTDHALAMTemp;
  INT16  OTDLALAMTemp;  
  UINT16 OTALAMDly;          // ������ʱ
  UINT16 OTCbALAMDly;        // �ָ�   
  UINT16 COTALAMTime;         // ���¼�ʱ��
	 UINT16 DOTALAMTime;         // ���¼�ʱ��
  UINT16 COTCbALAMTime;       // ���»ָ���ʱ�� 
	UINT16 DOTCbALAMTime;       // ���»ָ���ʱ�� 
	UINT8 GJDSet;  // �ɽڵ�
	INT16 GJDONTemp;
  INT16 GJDCbTemp;  
	INT16   MosTemp; 
	INT16  MOSOTTemp;
  INT16  MOSOTCTemp;
  UINT16 MOSOTDelay;
	UINT8 EVOTALAMSet; 
	INT16  EVOTALAMTemp;
  INT16  EVLTALAMTemp; 
  INT16  EVOTTemp;
	INT16  EVOTCbTemp;	
	INT16  EVLTTemp;
	INT16  EVLTCbTemp;	
	INT16  MOSOTALAMTemp;
	INT16  MOSOTALAMCbTemp;
	UINT8 MOSOTALAMSet;
}OTCB;

// ��ѹ���ƿ�
typedef struct
{
  FP32  OVVlg;           // ��ѹֵ
  FP32  OVCbVlg;         // ��ѹ�ָ���ѹ
  UINT16 OVDly;           // ��ѹ��ʱ
  UINT16 OVCbDly;         // ��ѹ�ָ���ʱ
  FP32  HVlg;            // ��ߵ�ص�ѹ
  UINT16 HNum;            // ��͵�ѹ��غ�
  UINT16 OVTime;          // ��ѹ��ʱ��  
  UINT16 OVCbTime;        // ��ѹ�ָ���ʱ�� 
  FP32  TOVVlg;           // ��ѹֵ
  FP32  TOVCbVlg;         // ��ѹ�ָ���ѹ
  UINT16 TOVDly;           // �ܵ�ѹ��ѹ��ʱ
  UINT16 TOVCbDly;         // �ܵ�ѹ��ѹ�ָ���ʱ
  UINT16 TOVTime;          // �ܵ�ѹ��ѹ��ʱ��  
  UINT16 TOVCbTime;        // �ܵ�ѹ��ѹ�ָ���ʱ�� 
   UINT8 OVALAMSet;
  FP32  OVALAMVlg;           // ��ѹֵ
  FP32  OVCbALAMVlg;         // ��ѹ�ָ���ѹ
  UINT16 OVALAMDly;           // ��ѹ��ʱ
  UINT16 OVCbALAMDly;         // ��ѹ�ָ���ʱ
  UINT16 OVALAMTime;          // ��ѹ��ʱ��  
  //UINT16 OVCbALAMTime;        // ��ѹ�ָ���ʱ�� 
  FP32  TOVALAMVlg;           // ��ѹֵ
  FP32  TOVCbALAMVlg;         // ��ѹ�ָ���ѹ 
  UINT16 TOVALAMDly;           // ��ѹ��ʱ
  UINT16 TOVCbALAMDly;         // ��ѹ�ָ���ʱ
  UINT16 TOVALAMTime;          // ��ѹ��ʱ��  
 // UINT16 TOVCbALAMTime;        // ��ѹ�ָ���ʱ��     
}OVCB;

#endif



