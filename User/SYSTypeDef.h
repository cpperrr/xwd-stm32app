//=======================================Copyright(c)==========================================
// 											Auto Code Making Company
//											Auto Code Department
//												CopyRight Private
//-------------------------------------------------FileMessage---------------------------------
//FileName	 SYSTypeDef.h 
//Author	 yys 
//Creation Time
//Description
//-----------------------------------------------当前版本修订----------------------------------
//修改人	
//版	本	 
//修改日期	
//Description
	
//=============================================================================================

#ifndef _SYSTYPEDEF_H
#define _SYSTYPEDEF_H

#include "stm32f10x.h"

//=============================================================================================
//宏参数定义
//=============================================================================================

//使能
#ifndef       ENABLE_YS
#define       ENABLE_YS          						0xaa
#endif
//不使能
#ifndef       DISABLE_YS
#define       DISABLE_YS         						0
#endif

//成立
#ifndef       TRUE
#define       TRUE                               				1
#endif

//不成立
#ifndef       FALSE
#define       FALSE											0
#endif

//不成立
#ifndef      ERROR_YS
#define       ERROR_YS									1
#endif

//不成立
#ifndef      RIGHT_YS
#define       RIGHT_YS									0
#endif

//数据空
#ifndef       NULL                                 
#define       NULL                              					0
#endif
//指针空
#ifndef       PNULL                                 
#define       PNULL                            					(void*(0))
#endif

//使能
#ifndef       BUSY_YS
#define       BUSY_YS          							0xaa
#endif
//不使能
#ifndef       FREE_YS
#define       FREE_YS         								0
#endif

//成立
#ifndef       CUT
#define       CUT                               					0
#endif

//不成立
#ifndef       CONNECT
#define       CONNECT									1
#endif

//============================================================================
//							宏函数定义
//============================================================================
#define BITSET(x, y)								((x) |= ((u8)1 << (y)))
#define BITCLR(x, y)								((x) &= ~((u8)1 << (y)))
#define BITGET(x, y)           				 		((u8)(((x) & ((u8)1 << (y))) >> (y)))

#define BITSET16(x, y)								((x) |= ((u16)1 << (y)))
#define BITCLR16(x, y)								((x) &= ~((u16)1 << (y)))
#define BITGET16(x, y)	        					(((x) & (u16)1 << (y)) >> (y))

#define BITSET32(x, y)		    					((x) |= ((u32)1 << (y)))
#define BITCLR32(x, y)		    					((x) &= ~((u32)1 << (y)))
#define BITGET32(x, y)          					((x & ((u32)1 << (y))) >> (y))
#define IsEqual(x, y)           						((x) == (y))
#define IsNotEqual(a,b)		   	 					((a)!=(b))                                  //a不等于b返回1 否则返回0

#define IsInside(x1, x, x2)     					(((x1) <= (x)) && ((x) <= (x2)))
#define ABS(x, y)               					((x) > (y) ? ((x) - (y)) : ((y) - (x)))

#define SysDelay(Count)     {volatile u16 i = Count; while(i--);}

//#define   EnableInterrupts      INTCONbits.GIE = 1
//#define   DisableInterrupts     INTCONbits.GIE = 0 

//#define   FeedDog()              {_asm clrwdt _endasm} //喂狗

//============================================================================
//							类型定义
//============================================================================

//typedef unsigned char 	u8;
//typedef signed char 	s8;
//typedef unsigned int 	u16;
//typedef signed int 		s16;
//typedef unsigned long 	u32;
//typedef signed long 	s32;

typedef union  
{
    u8   Byte;
    struct 
    {
        u8  B0       :1;                                       
        u8  B1       :1;                                      
        u8  B2       :1;                                    
        u8  B3       :1;                                       
        u8  B4       :1;                                   
        u8  B5       :1;                                     
        u8  B6       :1;                             
        u8  B7       :1;      				
    }Bits;
		
}uBits;


#ifndef OK
#define OK      0
#endif


//=============================================================================================
//声明全局变量
//=============================================================================================

//=============================================================================================
//声明接口函数
//=============================================================================================

#endif

