#ifndef __SYS_H
#define __SYS_H	
#include "stm32f10x.h"
#include "Delay.h"

typedef unsigned char  __IO UINT8;                   /* Unsigned  8 bit quantity                           */
typedef signed   char  __IO INT8;                    /* Signed    8 bit quantity                           */
typedef unsigned short __IO UINT16;                   /* Unsigned 16 bit quantity                           */
typedef signed   short __IO INT16;                   /* Signed   16 bit quantity                           */
typedef unsigned int   __IO UINT32;                   /* Unsigned 32 bit quantity */

typedef signed   int   __IO INT32;                   /* Signed   32 bit quantity                           */
typedef float          __IO FP32;                     /* Single precision floating poINT16                   */
typedef double         __IO FP64;                     /* Double precision floating poINT16                   */
typedef unsigned  __int64   __IO UINT64; 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.7
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	 

//0,不支持ucos
//1,支持ucos
#define SYSTEM_SUPPORT_OS		0		//定义系统文件夹是否支持UCOS
																	    
	 
//位带操作,实现51类似的GPIO控制功能
//具体实现思想,参考<<CM3权威指南>>第五章(87页~92页).
//IO口操作宏定义
//#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
//#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
//#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
////IO口地址映射
//#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
//#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
//#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
//#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
//#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
//#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
//#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

//#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
//#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
//#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
//#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
//#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
//#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
//#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
// 
////IO口操作,只对单一的IO口!
////确保n的值小于16!
//#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
//#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

//#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
//#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

//#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
//#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

//#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
//#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

//#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
//#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

//#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
//#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

//#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
//#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

//#ifndef  _BIT_1
//#define  _BIT_1

 
typedef struct _16_Bits_Struct
{
      unsigned pin0 : 1;
      unsigned pin1 : 1;
      unsigned pin2 : 1;
      unsigned pin3 : 1;
      unsigned pin4 : 1;
      unsigned pin5 : 1;
      unsigned pin6 : 1;
      unsigned pin7 : 1;
      unsigned pin8 : 1;
      unsigned pin9 : 1;
      unsigned pin10 : 1;
      unsigned pin11 : 1;
      unsigned pin12 : 1;
      unsigned pin13 : 1;
      unsigned pin14 : 1;
      unsigned pin15 : 1;
 } Bits_16_TypeDef;

 typedef struct _MODEL_Bits_Struct
{
      unsigned M0 : 4;
      unsigned M1 : 4;
      unsigned M2 : 4;
      unsigned M3 : 4;
      unsigned M4 : 4;
      unsigned M5 : 4;
      unsigned M6 : 4;
      unsigned M7 : 4;
 } Bits_MODEL_TypeDef;
 typedef struct _MODEH_Bits_Struct
 {	 
      unsigned M8 :  4;
      unsigned M9 :  4;
      unsigned M10 : 4;
      unsigned M11 : 4;
      unsigned M12 : 4;
      unsigned M13:  4;
      unsigned M14 : 4;
      unsigned M15 : 4;
 } Bits_MODEH_TypeDef;

// 输入
#define PA_IN         ((Bits_16_TypeDef *)(&(GPIOA->IDR)))
#define PB_IN         ((Bits_16_TypeDef *)(&(GPIOB->IDR)))
#define PC_IN         ((Bits_16_TypeDef *)(&(GPIOC->IDR)))
#define PD_IN         ((Bits_16_TypeDef *)(&(GPIOD->IDR)))
#define PE_IN         ((Bits_16_TypeDef *)(&(GPIOE->IDR)))
#define PF_IN         ((Bits_16_TypeDef *)(&(GPIOF->IDR))) 
// 方向向下拉

#define PA_ML          ((Bits_MODEL_TypeDef *)(&(GPIOA->CRL)))
#define PB_ML          ((Bits_MODEL_TypeDef *)(&(GPIOB->CRL)))
#define PC_ML          ((Bits_MODEL_TypeDef *)(&(GPIOC->CRL)))
#define PD_ML          ((Bits_MODEL_TypeDef *)(&(GPIOD->CRL)))
#define PE_ML          ((Bits_MODEL_TypeDef *)(&(GPIOE->CRL)))
#define PF_ML          ((Bits_MODEL_TypeDef *)(&(GPIOF->CRL)))  
#define PA_MH          ((Bits_MODEH_TypeDef *)(&(GPIOA->CRH)))
#define PB_MH          ((Bits_MODEH_TypeDef *)(&(GPIOB->CRH)))
#define PC_MH          ((Bits_MODEH_TypeDef *)(&(GPIOC->CRH)))
#define PD_MH          ((Bits_MODEH_TypeDef *)(&(GPIOD->CRH)))
#define PE_MH          ((Bits_MODEH_TypeDef *)(&(GPIOE->CRH)))
#define PF_MH          ((Bits_MODEH_TypeDef *)(&(GPIOF->CRH))) 

#define PA0_IN         (PA_IN->pin0)
#define PA1_IN         (PA_IN->pin1)
#define PA2_IN         (PA_IN->pin2)
#define PA3_IN         (PA_IN->pin3)
#define PA4_IN         (PA_IN->pin4)
#define PA5_IN         (PA_IN->pin5)
#define PA6_IN         (PA_IN->pin6)
#define PA7_IN         (PA_IN->pin7)
#define PA8_IN         (PA_IN->pin8)
#define PA9_IN         (PA_IN->pin9)
#define PA10_IN        (PA_IN->pin10)
#define PA11_IN        (PA_IN->pin11)
#define PA12_IN        (PA_IN->pin12)
#define PA13_IN        (PA_IN->pin13)
#define PA14_IN        (PA_IN->pin14)
#define PA15_IN        (PA_IN->pin15)


#define PA0_M         (PA_ML->M0)
#define PA0_M         (PA_ML->M0)
#define PA1_M         (PA_ML->M1)
#define PA2_M         (PA_ML->M2)
#define PA3_M         (PA_ML->M3)
#define PA4_M         (PA_ML->M4)
#define PA5_M         (PA_ML->M5)
#define PA6_M         (PA_ML->M6)
#define PA7_M         (PA_ML->M7)
#define PA8_M         (PA_MH->M8)
#define PA9_M         (PA_MH->M9)
#define PA10_M        (PA_MH->M10)
#define PA11_M        (PA_MH->M11)
#define PA12_M        (PA_MH->M12)
#define PA13_M        (PA_MH->M13)
#define PA14_M        (PA_MH->M14)
#define PA15_M        (PA_MH->M15)

 
// B端口
#define PB0_IN         (PB_IN->pin0)
#define PB1_IN         (PB_IN->pin1)
#define PB2_IN         (PB_IN->pin2)
#define PB3_IN         (PB_IN->pin3)
#define PB4_IN         (PB_IN->pin4)
#define PB5_IN         (PB_IN->pin5)
#define PB6_IN         (PB_IN->pin6)
#define PB7_IN         (PB_IN->pin7)
#define PB8_IN         (PB_IN->pin8)
#define PB9_IN         (PB_IN->pin9)
#define PB10_IN        (PB_IN->pin10)
#define PB11_IN        (PB_IN->pin11)
#define PB12_IN        (PB_IN->pin12)
#define PB13_IN        (PB_IN->pin13)
#define PB14_IN        (PB_IN->pin14)
#define PB15_IN        (PB_IN->pin15)


#define PB0_M          (PB_ML->M0)
#define PB1_M          (PB_ML->M1)
#define PB2_M          (PB_ML->M2)
#define PB3_M          (PB_ML->M3)
#define PB4_M          (PB_ML->M4)
#define PB5_M          (PB_ML->M5)
#define PB6_M          (PB_ML->M6)
#define PB7_M          (PB_ML->M7)
#define PB8_M          (PB_MH->M8)
#define PB9_M          (PB_MH->M9)
#define PB10_M         (PB_MH->M10)
#define PB11_M         (PB_MH->M11)
#define PB12_M         (PB_MH->M12)
#define PB13_M         (PB_MH->M13)
#define PB14_M         (PB_MH->M14)
#define PB15_M         (PB_MH->M15) 

// C端口

#define PC0_IN         (PC_IN->pin0)
#define PC1_IN         (PC_IN->pin1)
#define PC2_IN         (PC_IN->pin2)
#define PC3_IN         (PC_IN->pin3)
#define PC4_IN         (PC_IN->pin4)
#define PC5_IN         (PC_IN->pin5)
#define PC6_IN         (PC_IN->pin6)
#define PC7_IN         (PC_IN->pin7)
#define PC8_IN         (PC_IN->pin8)
#define PC9_IN         (PC_IN->pin9)
#define PC10_IN        (PC_IN->pin10)
#define PC11_IN        (PC_IN->pin11)
#define PC12_IN        (PC_IN->pin12)
#define PC13_IN        (PC_IN->pin13)
#define PC14_IN        (PC_IN->pin14)
#define PC15_IN        (PC_IN->pin15)


#define PC0_M          (PC_ML->M0)
#define PC1_M          (PC_ML->M1)
#define PC2_M          (PC_ML->M2)
#define PC3_M          (PC_ML->M3)
#define PC4_M          (PC_ML->M4)
#define PC5_M          (PC_ML->M5)
#define PC6_M          (PC_ML->M6)
#define PC7_M          (PC_ML->M7)
#define PC8_M          (PC_MH->M8)
#define PC9_M          (PC_MH->M9)
#define PC10_M         (PC_MH->M10)
#define PC11_M         (PC_MH->M11)
#define PC12_M         (PC_MH->M12)
#define PC13_M         (PC_MH->M13)
#define PC14_M         (PC_MH->M14)
#define PC15_M         (PC_MH->M15) 

 // D端口

#define PD0_IN         (PD_IN->pin0)
#define PD1_IN         (PD_IN->pin1)
#define PD2_IN         (PD_IN->pin2)
#define PD3_IN         (PD_IN->pin3)
#define PD4_IN         (PD_IN->pin4)
#define PD5_IN         (PD_IN->pin5)
#define PD6_IN         (PD_IN->pin6)
#define PD7_IN         (PD_IN->pin7)
#define PD8_IN         (PD_IN->pin8)
#define PD9_IN         (PD_IN->pin9)
#define PD10_IN        (PD_IN->pin10)
#define PD11_IN        (PD_IN->pin11)
#define PD12_IN        (PD_IN->pin12)
#define PD13_IN        (PD_IN->pin13)
#define PD14_IN        (PD_IN->pin14)
#define PD15_IN        (PD_IN->pin15)


#define PD0_M          (PD_ML->M0)
#define PD1_M          (PD_ML->M1)
#define PD2_M          (PD_ML->M2)
#define PD3_M          (PD_ML->M3)
#define PD4_M          (PD_ML->M4)
#define PD5_M          (PD_ML->M5)
#define PD6_M          (PD_ML->M6)
#define PD7_M          (PD_ML->M7)
#define PD8_M          (PD_MH->M8)
#define PD9_M          (PD_MH->M9)
#define PD10_M         (PD_MH->M10)
#define PD11_M         (PD_MH->M11)
#define PD12_M         (PD_MH->M12)
#define PD13_M         (PD_MH->M13)
#define PD14_M         (PD_MH->M14)
#define PD15_M         (PD_MH->M15) 

 
 // E端口

#define PE0_IN         (PE_IN->pin0)
#define PE1_IN         (PE_IN->pin1)
#define PE2_IN         (PE_IN->pin2)
#define PE3_IN         (PE_IN->pin3)
#define PE4_IN         (PE_IN->pin4)
#define PE5_IN         (PE_IN->pin5)
#define PE6_IN         (PE_IN->pin6)
#define PE7_IN         (PE_IN->pin7)
#define PE8_IN         (PE_IN->pin8)
#define PE9_IN         (PE_IN->pin9)
#define PE10_IN        (PE_IN->pin10)
#define PE11_IN        (PE_IN->pin11)
#define PE12_IN        (PE_IN->pin12)
#define PE13_IN        (PE_IN->pin13)
#define PE14_IN        (PE_IN->pin14)
#define PE15_IN        (PE_IN->pin15)


#define PE0_M          (PE_ML->M0)
#define PE1_M          (PE_ML->M1)
#define PE2_M          (PE_ML->M2)
#define PE3_M          (PE_ML->M3)
#define PE4_M          (PE_ML->M4)
#define PE5_M          (PE_ML->M5)
#define PE6_M          (PE_ML->M6)
#define PE7_M          (PE_ML->M7)
#define PE8_M          (PE_MH->M8)
#define PE9_M          (PE_MH->M9)
#define PE10_M         (PE_MH->M10)
#define PE11_M         (PE_MH->M11)
#define PE12_M         (PE_MH->M12)
#define PE13_M         (PE_MH->M13)
#define PE14_M         (PE_MH->M14)
#define PE15_M         (PE_MH->M15) 

 
 // F端口

#define PF0_IN         (PF_IN->pin0)
#define PF1_IN         (PF_IN->pin1)
#define PF2_IN         (PF_IN->pin2)
#define PF3_IN         (PF_IN->pin3)
#define PF4_IN         (PF_IN->pin4)
#define PF5_IN         (PF_IN->pin5)
#define PF6_IN         (PF_IN->pin6)
#define PF7_IN         (PF_IN->pin7)
#define PF8_IN         (PF_IN->pin8)
#define PF9_IN         (PF_IN->pin9)
#define PF10_IN        (PF_IN->pin10)
#define PF11_IN        (PF_IN->pin11)
#define PF12_IN        (PF_IN->pin12)
#define PF13_IN        (PF_IN->pin13)
#define PF14_IN        (PF_IN->pin14)
#define PF15_IN        (PF_IN->pin15)


#define PF0_M          (PF_ML->M0)
#define PF1_M          (PF_ML->M1)
#define PF2_M          (PF_ML->M2)
#define PF3_M          (PF_ML->M3)
#define PF4_M          (PF_ML->M4)
#define PF5_M          (PF_ML->M5)
#define PF6_M          (PF_ML->M6)
#define PF7_M          (PF_ML->M7)
#define PF8_M          (PF_MH->M8)
#define PF9_M          (PF_MH->M9)
#define PF10_M         (PF_MH->M10)
#define PF11_M         (PF_MH->M11)
#define PF12_M         (PF_MH->M12)
#define PF13_M         (PF_MH->M13)
#define PF14_M         (PF_MH->M14)
#define PF15_M         (PF_MH->M15) 

 
// A端口
#define PA0_OUT_1        (GPIOA->BSRR=GPIO_Pin_0)
#define PA1_OUT_1        (GPIOA->BSRR=GPIO_Pin_1)
#define PA2_OUT_1        (GPIOA->BSRR=GPIO_Pin_2)
#define PA3_OUT_1        (GPIOA->BSRR=GPIO_Pin_3)
#define PA4_OUT_1        (GPIOA->BSRR=GPIO_Pin_4)
#define PA5_OUT_1        (GPIOA->BSRR=GPIO_Pin_5)
#define PA6_OUT_1        (GPIOA->BSRR=GPIO_Pin_6)
#define PA7_OUT_1        (GPIOA->BSRR=GPIO_Pin_7)
#define PA8_OUT_1        (GPIOA->BSRR=GPIO_Pin_8)
#define PA9_OUT_1        (GPIOA->BSRR=GPIO_Pin_9)
#define PA10_OUT_1       (GPIOA->BSRR=GPIO_Pin_10)
#define PA11_OUT_1       (GPIOA->BSRR=GPIO_Pin_11)
#define PA12_OUT_1       (GPIOA->BSRR=GPIO_Pin_12)
#define PA13_OUT_1       (GPIOA->BSRR=GPIO_Pin_13)
#define PA14_OUT_1       (GPIOA->BSRR=GPIO_Pin_14)
#define PA15_OUT_1       (GPIOA->BSRR=GPIO_Pin_15)

#define PA0_OUT_0        (GPIOA->BRR=GPIO_Pin_0)
#define PA1_OUT_0        (GPIOA->BRR=GPIO_Pin_1)
#define PA2_OUT_0        (GPIOA->BRR=GPIO_Pin_2)
#define PA3_OUT_0        (GPIOA->BRR=GPIO_Pin_3)
#define PA4_OUT_0        (GPIOA->BRR=GPIO_Pin_4)
#define PA5_OUT_0        (GPIOA->BRR=GPIO_Pin_5)
#define PA6_OUT_0        (GPIOA->BRR=GPIO_Pin_6)
#define PA7_OUT_0        (GPIOA->BRR=GPIO_Pin_7)
#define PA8_OUT_0        (GPIOA->BRR=GPIO_Pin_8)
#define PA9_OUT_0        (GPIOA->BRR=GPIO_Pin_9)
#define PA10_OUT_0       (GPIOA->BRR=GPIO_Pin_10)
#define PA11_OUT_0       (GPIOA->BRR=GPIO_Pin_11)
#define PA12_OUT_0       (GPIOA->BRR=GPIO_Pin_12)
#define PA13_OUT_0       (GPIOA->BRR=GPIO_Pin_13)
#define PA14_OUT_0       (GPIOA->BRR=GPIO_Pin_14)
#define PA15_OUT_0       (GPIOA->BRR=GPIO_Pin_15)
 
 
 // B端口
#define PB0_OUT_1        (GPIOB->BSRR=GPIO_Pin_0)
#define PB1_OUT_1        (GPIOB->BSRR=GPIO_Pin_1)
#define PB2_OUT_1        (GPIOB->BSRR=GPIO_Pin_2)
#define PB3_OUT_1        (GPIOB->BSRR=GPIO_Pin_3)
#define PB4_OUT_1        (GPIOB->BSRR=GPIO_Pin_4)
#define PB5_OUT_1        (GPIOB->BSRR=GPIO_Pin_5)
#define PB6_OUT_1        (GPIOB->BSRR=GPIO_Pin_6)
#define PB7_OUT_1        (GPIOB->BSRR=GPIO_Pin_7)
#define PB8_OUT_1        (GPIOB->BSRR=GPIO_Pin_8)
#define PB9_OUT_1        (GPIOB->BSRR=GPIO_Pin_9)
#define PB10_OUT_1       (GPIOB->BSRR=GPIO_Pin_10)
#define PB11_OUT_1       (GPIOB->BSRR=GPIO_Pin_11)
#define PB12_OUT_1       (GPIOB->BSRR=GPIO_Pin_12)
#define PB13_OUT_1       (GPIOB->BSRR=GPIO_Pin_13)
#define PB14_OUT_1       (GPIOB->BSRR=GPIO_Pin_14)
#define PB15_OUT_1       (GPIOB->BSRR=GPIO_Pin_15)

#define PB0_OUT_0        (GPIOB->BRR=GPIO_Pin_0)
#define PB1_OUT_0        (GPIOB->BRR=GPIO_Pin_1)
#define PB2_OUT_0        (GPIOB->BRR=GPIO_Pin_2)
#define PB3_OUT_0        (GPIOB->BRR=GPIO_Pin_3)
#define PB4_OUT_0        (GPIOB->BRR=GPIO_Pin_4)
#define PB5_OUT_0        (GPIOB->BRR=GPIO_Pin_5)
#define PB6_OUT_0        (GPIOB->BRR=GPIO_Pin_6)
#define PB7_OUT_0        (GPIOB->BRR=GPIO_Pin_7)
#define PB8_OUT_0        (GPIOB->BRR=GPIO_Pin_8)
#define PB9_OUT_0        (GPIOB->BRR=GPIO_Pin_9)
#define PB10_OUT_0       (GPIOB->BRR=GPIO_Pin_10)
#define PB11_OUT_0       (GPIOB->BRR=GPIO_Pin_11)
#define PB12_OUT_0       (GPIOB->BRR=GPIO_Pin_12)
#define PB13_OUT_0       (GPIOB->BRR=GPIO_Pin_13)
#define PB14_OUT_0       (GPIOB->BRR=GPIO_Pin_14)
#define PB15_OUT_0       (GPIOB->BRR=GPIO_Pin_15)
 
 
 
 // C端口
#define PC0_OUT_1        (GPIOC->BSRR=GPIO_Pin_0)
#define PC1_OUT_1        (GPIOC->BSRR=GPIO_Pin_1)
#define PC2_OUT_1        (GPIOC->BSRR=GPIO_Pin_2)
#define PC3_OUT_1        (GPIOC->BSRR=GPIO_Pin_3)
#define PC4_OUT_1        (GPIOC->BSRR=GPIO_Pin_4)
#define PC5_OUT_1        (GPIOC->BSRR=GPIO_Pin_5)
#define PC6_OUT_1        (GPIOC->BSRR=GPIO_Pin_6)
#define PC7_OUT_1        (GPIOC->BSRR=GPIO_Pin_7)
#define PC8_OUT_1        (GPIOC->BSRR=GPIO_Pin_8)
#define PC9_OUT_1        (GPIOC->BSRR=GPIO_Pin_9)
#define PC10_OUT_1       (GPIOC->BSRR=GPIO_Pin_10)
#define PC11_OUT_1       (GPIOC->BSRR=GPIO_Pin_11)
#define PC12_OUT_1       (GPIOC->BSRR=GPIO_Pin_12)
#define PC13_OUT_1       (GPIOC->BSRR=GPIO_Pin_13)
#define PC14_OUT_1       (GPIOC->BSRR=GPIO_Pin_14)
#define PC15_OUT_1       (GPIOC->BSRR=GPIO_Pin_15)

#define PC0_OUT_0        (GPIOC->BRR=GPIO_Pin_0)
#define PC1_OUT_0        (GPIOC->BRR=GPIO_Pin_1)
#define PC2_OUT_0        (GPIOC->BRR=GPIO_Pin_2)
#define PC3_OUT_0        (GPIOC->BRR=GPIO_Pin_3)
#define PC4_OUT_0        (GPIOC->BRR=GPIO_Pin_4)
#define PC5_OUT_0        (GPIOC->BRR=GPIO_Pin_5)
#define PC6_OUT_0        (GPIOC->BRR=GPIO_Pin_6)
#define PC7_OUT_0        (GPIOC->BRR=GPIO_Pin_7)
#define PC8_OUT_0        (GPIOC->BRR=GPIO_Pin_8)
#define PC9_OUT_0        (GPIOC->BRR=GPIO_Pin_9)
#define PC10_OUT_0       (GPIOC->BRR=GPIO_Pin_10)
#define PC11_OUT_0       (GPIOC->BRR=GPIO_Pin_11)
#define PC12_OUT_0       (GPIOC->BRR=GPIO_Pin_12)
#define PC13_OUT_0       (GPIOC->BRR=GPIO_Pin_13)
#define PC14_OUT_0       (GPIOC->BRR=GPIO_Pin_14)
#define PC15_OUT_0       (GPIOC->BRR=GPIO_Pin_15)
 
  // D端口
#define PD0_OUT_1        (GPIOD->BSRR=GPIO_Pin_0)
#define PD1_OUT_1        (GPIOD->BSRR=GPIO_Pin_1)
#define PD2_OUT_1        (GPIOD->BSRR=GPIO_Pin_2)
#define PD3_OUT_1        (GPIOD->BSRR=GPIO_Pin_3)
#define PD4_OUT_1        (GPIOD->BSRR=GPIO_Pin_4)
#define PD5_OUT_1        (GPIOD->BSRR=GPIO_Pin_5)
#define PD6_OUT_1        (GPIOD->BSRR=GPIO_Pin_6)
#define PD7_OUT_1        (GPIOD->BSRR=GPIO_Pin_7)
#define PD8_OUT_1        (GPIOD->BSRR=GPIO_Pin_8)
#define PD9_OUT_1        (GPIOD->BSRR=GPIO_Pin_9)
#define PD10_OUT_1       (GPIOD->BSRR=GPIO_Pin_10)
#define PD11_OUT_1       (GPIOD->BSRR=GPIO_Pin_11)
#define PD12_OUT_1       (GPIOD->BSRR=GPIO_Pin_12)
#define PD13_OUT_1       (GPIOD->BSRR=GPIO_Pin_13)
#define PD14_OUT_1       (GPIOD->BSRR=GPIO_Pin_14)
#define PD15_OUT_1       (GPIOD->BSRR=GPIO_Pin_15)

#define PD0_OUT_0        (GPIOD->BRR=GPIO_Pin_0)
#define PD1_OUT_0        (GPIOD->BRR=GPIO_Pin_1)
#define PD2_OUT_0        (GPIOD->BRR=GPIO_Pin_2)
#define PD3_OUT_0        (GPIOD->BRR=GPIO_Pin_3)
#define PD4_OUT_0        (GPIOD->BRR=GPIO_Pin_4)
#define PD5_OUT_0        (GPIOD->BRR=GPIO_Pin_5)
#define PD6_OUT_0        (GPIOD->BRR=GPIO_Pin_6)
#define PD7_OUT_0        (GPIOD->BRR=GPIO_Pin_7)
#define PD8_OUT_0        (GPIOD->BRR=GPIO_Pin_8)
#define PD9_OUT_0        (GPIOD->BRR=GPIO_Pin_9)
#define PD10_OUT_0       (GPIOD->BRR=GPIO_Pin_10)
#define PD11_OUT_0       (GPIOD->BRR=GPIO_Pin_11)
#define PD12_OUT_0       (GPIOD->BRR=GPIO_Pin_12)
#define PD13_OUT_0       (GPIOD->BRR=GPIO_Pin_13)
#define PD14_OUT_0       (GPIOD->BRR=GPIO_Pin_14)
#define PD15_OUT_0       (GPIOD->BRR=GPIO_Pin_15)
 
  // E端口
#define PE0_OUT_1        (GPIOE->BSRR=GPIO_Pin_0)
#define PE1_OUT_1        (GPIOE->BSRR=GPIO_Pin_1)
#define PE2_OUT_1        (GPIOE->BSRR=GPIO_Pin_2)
#define PE3_OUT_1        (GPIOE->BSRR=GPIO_Pin_3)
#define PE4_OUT_1        (GPIOE->BSRR=GPIO_Pin_4)
#define PE5_OUT_1        (GPIOE->BSRR=GPIO_Pin_5)
#define PE6_OUT_1        (GPIOE->BSRR=GPIO_Pin_6)
#define PE7_OUT_1        (GPIOE->BSRR=GPIO_Pin_7)
#define PE8_OUT_1        (GPIOE->BSRR=GPIO_Pin_8)
#define PE9_OUT_1        (GPIOE->BSRR=GPIO_Pin_9)
#define PE10_OUT_1       (GPIOE->BSRR=GPIO_Pin_10)
#define PE11_OUT_1       (GPIOE->BSRR=GPIO_Pin_11)
#define PE12_OUT_1       (GPIOE->BSRR=GPIO_Pin_12)
#define PE13_OUT_1       (GPIOE->BSRR=GPIO_Pin_13)
#define PE14_OUT_1       (GPIOE->BSRR=GPIO_Pin_14)
#define PE15_OUT_1       (GPIOE->BSRR=GPIO_Pin_15)

#define PE0_OUT_0        (GPIOE->BRR=GPIO_Pin_0)
#define PE1_OUT_0        (GPIOE->BRR=GPIO_Pin_1)
#define PE2_OUT_0        (GPIOE->BRR=GPIO_Pin_2)
#define PE3_OUT_0        (GPIOE->BRR=GPIO_Pin_3)
#define PE4_OUT_0        (GPIOE->BRR=GPIO_Pin_4)
#define PE5_OUT_0        (GPIOE->BRR=GPIO_Pin_5)
#define PE6_OUT_0        (GPIOE->BRR=GPIO_Pin_6)
#define PE7_OUT_0        (GPIOE->BRR=GPIO_Pin_7)
#define PE8_OUT_0        (GPIOE->BRR=GPIO_Pin_8)
#define PE9_OUT_0        (GPIOE->BRR=GPIO_Pin_9)
#define PE10_OUT_0       (GPIOE->BRR=GPIO_Pin_10)
#define PE11_OUT_0       (GPIOE->BRR=GPIO_Pin_11)
#define PE12_OUT_0       (GPIOE->BRR=GPIO_Pin_12)
#define PE13_OUT_0       (GPIOE->BRR=GPIO_Pin_13)
#define PE14_OUT_0       (GPIOE->BRR=GPIO_Pin_14)
#define PE15_OUT_0       (GPIOE->BRR=GPIO_Pin_15)

// F端口
#define PF0_OUT_1        (GPIOF->BSRR=GPIO_Pin_0)
#define PF1_OUT_1        (GPIOF->BSRR=GPIO_Pin_1)
#define PF2_OUT_1        (GPIOF->BSRR=GPIO_Pin_2)
#define PF3_OUT_1        (GPIOF->BSRR=GPIO_Pin_3)
#define PF4_OUT_1        (GPIOF->BSRR=GPIO_Pin_4)
#define PF5_OUT_1        (GPIOF->BSRR=GPIO_Pin_5)
#define PF6_OUT_1        (GPIOF->BSRR=GPIO_Pin_6)
#define PF7_OUT_1        (GPIOF->BSRR=GPIO_Pin_7)
#define PF8_OUT_1        (GPIOF->BSRR=GPIO_Pin_8)
#define PF9_OUT_1        (GPIOF->BSRR=GPIO_Pin_9)
#define PF10_OUT_1       (GPIOF->BSRR=GPIO_Pin_10)
#define PF11_OUT_1       (GPIOF->BSRR=GPIO_Pin_11)
#define PF12_OUT_1       (GPIOF->BSRR=GPIO_Pin_12)
#define PF13_OUT_1       (GPIOF->BSRR=GPIO_Pin_13)
#define PF14_OUT_1       (GPIOF->BSRR=GPIO_Pin_14)
#define PF15_OUT_1       (GPIOF->BSRR=GPIO_Pin_15)

#define PF0_OUT_0        (GPIOF->BRR=GPIO_Pin_0)
#define PF1_OUT_0        (GPIOF->BRR=GPIO_Pin_1)
#define PF2_OUT_0        (GPIOF->BRR=GPIO_Pin_2)
#define PF3_OUT_0        (GPIOF->BRR=GPIO_Pin_3)
#define PF4_OUT_0        (GPIOF->BRR=GPIO_Pin_4)
#define PF5_OUT_0        (GPIOF->BRR=GPIO_Pin_5)
#define PF6_OUT_0        (GPIOF->BRR=GPIO_Pin_6)
#define PF7_OUT_0        (GPIOF->BRR=GPIO_Pin_7)
#define PF8_OUT_0        (GPIOF->BRR=GPIO_Pin_8)
#define PF9_OUT_0        (GPIOF->BRR=GPIO_Pin_9)
#define PF10_OUT_0       (GPIOF->BRR=GPIO_Pin_10)
#define PF11_OUT_0       (GPIOF->BRR=GPIO_Pin_11)
#define PF12_OUT_0       (GPIOF->BRR=GPIO_Pin_12)
#define PF13_OUT_0       (GPIOF->BRR=GPIO_Pin_13)
#define PF14_OUT_0       (GPIOF->BRR=GPIO_Pin_14)
#define PF15_OUT_0       (GPIOF->BRR=GPIO_Pin_15)

 #define  NOP()          __NOP()
#define  Nop()          __NOP()

//以下为汇编函数
void WFI_SET(void);		//执行WFI指令
void INTX_DISABLE(void);//关闭所有中断
void INTX_ENABLE(void);	//开启所有中断
void MSR_MSP(u32 addr);	//设置堆栈地址

#endif
