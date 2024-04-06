
 

#ifndef   _GlOBAL_H
#define   _GlOBAL_H

#include "stm32f10x.h"  

 
 
#include "CPU.h"
#include "serial.h"
  
	
	extern void ModbusSendDataCode(void);
// 过流
typedef struct
{
 // UINT8  OCVlg;
  UINT16 CHGOC1Dly;
	UINT16 DSGOC1Dly;
  FP32  DSGOC1;            // 放电一级过流
  FP32  CHGOC1;             // 充电一级过流
  // 过流恢复设定
  UINT8 CHGOCAutoCbSet; // 充电自动恢复设置 
  UINT8 CHGOCAutoCbInterval; // 充电自动恢复时间间隔
  UINT8 CHGOCAutoCbCounter; // 充电自动恢复次数
  UINT8 CHGOCDSGAutoCbSet; // 充电过流放电自动恢复
  UINT8 DSGOCAutoCbSet; // 放电自动恢复设置
  UINT8 DSGOCAutoCbInterval; // 放电自动恢复时间间隔
  UINT8 DSGOCAutoCbCounter; // 放电自动恢复次数
  UINT8 DSGOCCHGAutoCbSet; // 放电过流充电自动恢复
  
  UINT16 CHGOCCbCount; // 充电过流恢复次数计数器
  UINT16 DSGOCCbCount;
  UINT8 OCALAMSet;   // 过流告警设置
  FP32 CHGOCALAM;   // 充电过流告警
  FP32 DSGOCALAM;    // 放电过流告警
  FP32 CHGOCALAMCB;   // 充电过流告警
  FP32 DSGOCALAMCB;    // 放电过流告警
  UINT8 OC;
	UINT8 SC;
  UINT8 CHG_LCur; // 充电限流大小
}OCCB;

// 均衡
typedef struct
{
  FP32  Dif;          // 均衡压差
  FP32  BSVlg;              // 均衡开启电压
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


// 标志结构体
typedef struct
{
  // 过温
  UINT8  OT_FLAG;             // 过温标志
  UINT8  OTC_MAY_FLAG;         // 充电虚过温标志
  UINT8  OTC_CB_MAY_FLAG;      // 充电虚过温恢复标志
  UINT8  OTD_MAY_FLAG;         // 放电虚过温标志
  UINT8  OTD_CB_MAY_FLAG;      // 放电虚过温恢复标志
  UINT8  OT_TIME_START_FLAG;     // 过温延时计时开关
  UINT8  OT_CB_TIME_START_FLAG;  // 过温恢复延时计时开关
  // 过温告警
  UINT8  OTC_ALAM_FLAG;             // 过温标志
  UINT8  OTD_ALAM_FLAG;             // 过温标志
  UINT8  OTC_MAY_ALAM_FLAG;         // 充电虚过温标志
  UINT8  OTC_CB_MAY_ALAM_FLAG;      // 充电虚过温恢复标志
  UINT8  OTD_MAY_ALAM_FLAG;         // 放电虚过温标志
  UINT8  OTD_CB_MAY_ALAM_FLAG;      // 放电虚过温恢复标志
  UINT8  OT_TIME_START_ALAM_FLAG;     // 过温延时计时开关
  UINT8  OT_CB_TIME_START_ALAM_FLAG;  // 过温恢复延时计时开关
	UINT8  EVOT_ALAM_FLAG;             // 过温标志
	UINT8  EVOT_FLAG;
	UINT8  MOSOT_ALAM_FLAG;
	// 过压
  UINT8  OV_FLAG;             // 过压标志
  UINT8  OV_MAY_FLAG;         // 虚过压标志
  UINT8  OV_CB_MAY_FLAG;      // 虚过压恢复标志
  UINT8  OV_TIME_START_FLAG;  // 过压延时计时开关
  UINT8  OV_CB_TIME_START_FLAG;    // 过压恢复延时计时开关
 // UINT8  TOV_FLAG;             // 过压标志
  UINT8  TOV_MAY_FLAG;         // 虚过压标志
  UINT8  TOV_CB_MAY_FLAG;      // 虚过压恢复标志
  UINT8  TOV_TIME_START_FLAG;  // 过压延时计时开关
  UINT8  TOV_CB_TIME_START_FLAG;    // 过压恢复延时计时开关
  // 欠压
  UINT8  UV_FLAG;             // 欠压
  UINT8  UV_MAY_FLAG;         // 虚过压标志
  UINT8  UV_CB_MAY_FLAG;      // 虚过压恢复标志
  UINT8  UV_TIME_START_FLAG;  // 过压延时计时开关
  UINT8  UV_CB_TIME_START_FLAG;    // 过压恢复延时计时开关
 // UINT8  TUV_FLAG;             // 过压标志
  UINT8  TVP_SET; // 总压保护标志 
  UINT8  TUV_MAY_FLAG;         // 虚过压标志
  UINT8  TUV_CB_MAY_FLAG;      // 虚过压恢复标志
  UINT8  TUV_TIME_START_FLAG;  // 过压延时计时开关
  UINT8  TUV_CB_TIME_START_FLAG;    // 过压恢复延时计时开关
  UINT8  UV_ALAM_FLAG;             // 欠压
  UINT8  UV_MAY_ALAM_FLAG;         // 虚过压标志
  UINT8  UV_CB_MAY_ALAM_FLAG;      // 虚过压恢复标志
  UINT8  UV_TIME_START_ALAM_FLAG;  // 过压延时计时开关
  UINT8  UV_CB_TIME_START_ALAM_FLAG;    // 过压恢复延时计时开关
  UINT8  TUV_ALAM_FLAG;             // 欠压
  UINT8  TUV_MAY_ALAM_FLAG;         // 虚过压标志
  UINT8  TUV_CB_MAY_ALAM_FLAG;      // 虚过压恢复标志
  UINT8  TUV_TIME_START_ALAM_FLAG;  // 过压延时计时开关
  UINT8  TUV_CB_TIME_START_ALAM_FLAG;    // 过压恢复延时计时开关
  UINT8  OV_ALAM_FLAG;             // 欠压
  UINT8  OV_MAY_ALAM_FLAG;         // 虚过压标志
  UINT8  OV_CB_MAY_ALAM_FLAG;      // 虚过压恢复标志
  UINT8  OV_TIME_START_ALAM_FLAG;  // 过压延时计时开关
  UINT8  OV_CB_TIME_START_ALAM_FLAG;    // 过压恢复延时计时开关
  UINT8  TOV_ALAM_FLAG;             // 欠压
  UINT8  TOV_MAY_ALAM_FLAG;         // 虚过压标志
  UINT8  TOV_CB_MAY_ALAM_FLAG;      // 虚过压恢复标志
  UINT8  TOV_TIME_START_ALAM_FLAG;  // 过压延时计时开关
  UINT8  TOV_CB_TIME_START_ALAM_FLAG;    // 过压恢复延时计时开关
  UINT8  OC_SC_FLAG;          // 过流短路标志
  UINT8  CHG_FLAG;             // 正在充电全局标志
  UINT8  DSG_FLAG;            // 正在放电全局标志
  UINT8  SEND_VLG_FLAG;       // 电压请求标志
  UINT8  SLEEP_UP_FLAG;       // 休眠唤醒标志
  UINT8  AVR_CUR_START_FLAG;  // 平均电流启动标志
  UINT8  BLA_START_FLAG;      // 均衡启动标志

  UINT8  WATCH_START_FLAG;    // 监控主程序标志
  UINT8  BLA_FLAG_ST;
  UINT8  RS485_FLAG;
  UINT8  OPNoCtr_FLAG;
  // 失效标志
  UINT8  CHGFail_FLAG; // 充电MOS失效
  UINT8  DSGFail_FLAG; // 放电MOS失效
  UINT8  VlgFail_FLAG; // 电压失效
  UINT8  TempFail_FLAG;// 温度失效
  // 过流告警标志
  UINT8  CHGOCALAM_FLAG;
  UINT8  DSGOCALAM_FLAG;
  UINT8  LCUR_SET;  // 限流设置标志
  UINT8  SPWMCHGCur_FLAG; // 启动限流充电标志
  UINT8  DSG_EN_FLAG;
  UINT8  CHG_EN_FLAG;
  // 温度高低告警标志
  UINT8  HT_ALAM_FLAG; // 高温告警
  UINT8  LT_ALAM_FLAG; // 低温告警
  UINT8  IMBALANCE_ALAM_FLAG; // 电芯不均衡告警 
	UINT8  OTMOS_FLAG;
	UINT8  SOCL_ALAM_FLAG;
}FCB;

typedef struct
{
   FP32  CellMul[31];
   FP32  CellVlg[32+1];        // 保存所有电池电压
   INT16  TemReg[10];    // 保存温度
   FP32  TotalVlg;    // 总电压
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
   UINT16    CHGRemTime;       // 充电剩余时间
   UINT16    DSGRemTime;       // 放电剩余时间 
   INT32  CapCount;         // 电量累积
   INT32  RemCapT1;         // t1时间剩余容量
   INT32  RemCapT2;         // t2时间剩余容量
   FP32     CHGCur;           // 用来计算充放电剩余时间
   FP32     DSGCur;
   UINT8     FuelChange;         // 电量容量数据改变
   UINT8     LAST_CHARGE_FULL_FLAG;     // 最后充满点标?
   UINT8     FUEL_CHANGE_FLAG;
   FP32     RS485Cur;
   UINT16    CHGTimeInterval;   // 最近充电间隔时间
   UINT16    CHGTimeIntervaler; // 最长充电间隔时间  
   FP32     T_U; // 温度衰减系数 计算用 
   FP32     Fuel_UpTVol;   // 更新总电压
   FP32     Fuel_UpCur;    // 更新电流  
   FP32     Set_1TempH; // 超过25度每增加一度衰减系数 
   FP32     Set_1TempL; // 低于25度每减少一度衰减系数
   FP32     SetCycleCount_U; // 每循环一次满容量衰减系数
	 UINT16    Fuel_UpDelay;
	 FP32     SelfDsg; // 自放电率
	 FP32     CycalCapPro; // 循环容量比
	 FP32     SOC8Vlg; // 8%对应电压
   UINT8     SOCLALAMSet;
	 UINT8     SOCLALAMSOC;
	 UINT32    TotalDSGTime; // 累计放电时间
	 UINT32    TotalCHGTime; // 累计充电时间
}soc_cb;

// 电量数据
typedef struct 
{
  FP32          RemFullCap;   // 电芯当
  UINT32        RemFullCapDesign; //设计满容量 单位AH
  INT32         RemCap;       // 当前剩余容量 
  INT32         DSGCap;       // 累积放电容量
  UINT16        CycleCount;   // 循环次数 
  UINT8         PercentCap;   // 容量百
	UINT8         PercentCap2;
	UINT8         VirtualPercentCap;// SOC高端与低端虚拟化之后的SOC
	UINT16        RemSOE;          // 当前SOE 单位WH
	FP32          RemFullSOE;   // 当前满能量
	UINT32        RemFullSOEDesign; //设计满能量 单位WH
}SOCCB;

// 电流控制块
typedef struct
{ 
  FP32  DSGCnt;         // 放电常量
  FP32  CHGCnt;         // 充电常量
  FP32  DSGMul;       // 定义放电放大倍数 
  FP32  CHGMul;       // 定义充电放大倍数 
  FP32  DSGCur;         // 放电电流    
  FP32  CHGCur;         // 充电电流
  FP32  CHGCur_;        // 异口单独检测充电电流
  FP32  DSGCur_;
  FP32  CHGCur5s;
  FP32  DSGCur5s;
}CCB;



// 欠压控制块
typedef struct
{
  FP32  UVVlg;           // 过压值
  FP32  UVCbVlg;         // 过压恢复电压
  UINT16 UVDly;           // 过压延时
  UINT16 UVCbDly;         // 过压恢复延时
  FP32  LVlg;            // 最高电池电压
  UINT16 LNum;            // 最低电压电池号
  UINT16 UVTime;          // 过压计时器  
  UINT16 UVCbTime;        // 过压恢复计时器
  FP32  TUVVlg;           // 过压值
  FP32  TUVCbVlg;         // 过压恢复电压
  UINT16 TUVDly;           // 总电压欠压延时
  UINT16 TUVCbDly;         // 总电压欠压恢复延时
  UINT16 TUVTime;          // 总电压欠压计时器  
  UINT16 TUVCbTime;        // 总电压欠压恢复计时器 
  UINT8  UVALAMSet;
  FP32  UVALAMVlg;           // 过压值
  FP32  UVCbALAMVlg;         // 过压恢复电压
  UINT16 UVALAMDly;           // 过压延时
  UINT16 UVCbALAMDly;         // 过压恢复延时
  UINT16 UVALAMTime;          // 过压计时器  
 // UINT16 UVCbALAMTime;        // 过压恢复计时器 
  FP32  TUVALAMVlg;           // 过压值
  FP32  TUVCbALAMVlg;         // 过压恢复电压 
  UINT16 TUVALAMDly;           // 过压延时
  UINT16 TUVCbALAMDly;         // 过压恢复延时
  UINT16 TUVALAMTime;          // 过压计时器  
 // UINT16 TUVCbALAMTime;        // 过压恢复计时器 
	FP32  ShutdownVlg;
  UINT32  ShutdownTime;		
}UVCB;


// 过温控制块
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
  UINT16 OTDly;          // 过温延时
  UINT16 OTCbDly;        // 恢复   
  UINT16 OTTime;         // 过温计时器
  UINT16 OTCbTime;       // 过温恢复计时器
  UINT16 OTNum;          // 过温编号
  INT16    HTemp;
  UINT8  HRegNum; 
  INT16    LTemp;
  UINT8  LRegNum;
  UINT8 OTALAMSet; 
  INT16  OTCHALAMTemp;
  INT16  OTCLALAMTemp; 
  INT16  OTDHALAMTemp;
  INT16  OTDLALAMTemp;  
  UINT16 OTALAMDly;          // 过温延时
  UINT16 OTCbALAMDly;        // 恢复   
  UINT16 COTALAMTime;         // 过温计时器
	 UINT16 DOTALAMTime;         // 过温计时器
  UINT16 COTCbALAMTime;       // 过温恢复计时器 
	UINT16 DOTCbALAMTime;       // 过温恢复计时器 
	UINT8 GJDSet;  // 干节点
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

// 过压控制块
typedef struct
{
  FP32  OVVlg;           // 过压值
  FP32  OVCbVlg;         // 过压恢复电压
  UINT16 OVDly;           // 过压延时
  UINT16 OVCbDly;         // 过压恢复延时
  FP32  HVlg;            // 最高电池电压
  UINT16 HNum;            // 最低电压电池号
  UINT16 OVTime;          // 过压计时器  
  UINT16 OVCbTime;        // 过压恢复计时器 
  FP32  TOVVlg;           // 过压值
  FP32  TOVCbVlg;         // 过压恢复电压
  UINT16 TOVDly;           // 总电压过压延时
  UINT16 TOVCbDly;         // 总电压过压恢复延时
  UINT16 TOVTime;          // 总电压过压计时器  
  UINT16 TOVCbTime;        // 总电压过压恢复计时器 
   UINT8 OVALAMSet;
  FP32  OVALAMVlg;           // 过压值
  FP32  OVCbALAMVlg;         // 过压恢复电压
  UINT16 OVALAMDly;           // 过压延时
  UINT16 OVCbALAMDly;         // 过压恢复延时
  UINT16 OVALAMTime;          // 过压计时器  
  //UINT16 OVCbALAMTime;        // 过压恢复计时器 
  FP32  TOVALAMVlg;           // 过压值
  FP32  TOVCbALAMVlg;         // 过压恢复电压 
  UINT16 TOVALAMDly;           // 过压延时
  UINT16 TOVCbALAMDly;         // 过压恢复延时
  UINT16 TOVALAMTime;          // 过压计时器  
 // UINT16 TOVCbALAMTime;        // 过压恢复计时器     
}OVCB;

#endif



