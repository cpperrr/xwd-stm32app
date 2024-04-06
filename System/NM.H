
#ifndef __NMNM_H
#define __NMNM_H	
#include "stm32f10x.h"
#define BYTE0(temp)	   (*(char*)(&temp))
#define BYTE1(temp)	   (*((char*)(&temp)+1))
#define BYTE2(temp)	   (*((char*)(&temp)+2))
#define BYTE3(temp)	   (*((char*)(&temp)+3))
 
typedef struct 							
{
	uint16_t par_id;                 //<参数id
	int32_t  par_val;                //<参数值
}par_struct;
typedef struct
{
	uint8_t head;					 //<帧头
	uint8_t target_addr;			 //<目标地址
	uint8_t function_id;			 //<该帧要实现某功能的功能码id
	uint8_t data_len;				 //<数据长度
	uint8_t data[40];				 //<数据内容，协议最高只支持40字节数据  
	uint8_t sum_check;				 //<和校验
	uint8_t add_check;				 //<附加校验
	
	par_struct* parameter;           //<参数
}ano_frameStruct;


#endif