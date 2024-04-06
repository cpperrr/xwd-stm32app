#ifndef  _CPU_H
#define  _CPU_H
#include "stm32f10x.h"                  // Device header

typedef unsigned char  __IO UINT8;                   /* Unsigned  8 bit quantity                           */
typedef signed   char  __IO INT8;                    /* Signed    8 bit quantity                           */
typedef unsigned short __IO UINT16;                   /* Unsigned 16 bit quantity                           */
typedef signed   short __IO INT16;                   /* Signed   16 bit quantity                           */
typedef unsigned int   __IO UINT32;                   /* Unsigned 32 bit quantity */

typedef signed   int   __IO INT32;                   /* Signed   32 bit quantity                           */
typedef float          __IO FP32;                     /* Single precision floating poINT16                   */
typedef double         __IO FP64;                     /* Double precision floating poINT16                   */
typedef unsigned  __int64   __IO UINT64;                   /* Unsigned 32 bit quantity  */
#define  ClrWdt()         (IWDG->KR =0xAAAAU)
#define  NOP()          __NOP()
#define  Nop()          __NOP()

 
 
#endif
