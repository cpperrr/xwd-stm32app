
#include "NM.h"
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

extern void Serial_SendArray(uint8_t *Array, uint16_t Length);
static ano_frameStruct send_frame_struct;    //<(发送)通信帧结构体

static void ano_check_calculate(ano_frameStruct* frame)
{
	frame->sum_check=0;
	frame->add_check=0;
	
	//除去和校验，附加校验及数据部分，有4个部分4个字节，长度固定
	for(uint32_t i=0;i<4;i++)
	{
	  frame->sum_check+= *(uint8_t*)(&frame->head+i);
	  frame->add_check+=frame->sum_check;
	}
	//获取数据长度部位,把数据部分全加上
	for(uint32_t i=0;i<frame->data_len;i++)
	{
	  frame->sum_check+=*((uint8_t*)(frame->data)+i);
	  frame->add_check+=frame->sum_check;
	} 
 }

 static void frame_turn_to_array(ano_frameStruct* frame,uint8_t*str)
{
	memcpy(str,(uint8_t*)frame,4);
	memcpy(str+4,(uint8_t*)frame->data,frame->data_len);
	memcpy(str+4+frame->data_len,(uint8_t*)(&frame->sum_check),2);
}
 
/**
  * @brief   通信帧校验检查(接收上位机通信帧时用)
  * @param   通信帧结构体对象
 * @retval   1：校验成功 0:校验失败
  **/
static uint8_t ano_check(ano_frameStruct* frame)
{
	uint8_t sum_check=0;
	uint8_t add_check=0;

	for(uint32_t i=0;i<4;i++)
	{
	  sum_check+= *(uint8_t*)(&frame->head+i);
	  add_check+=sum_check;
	}
	for(uint32_t i=0;i<frame->data_len;i++)
	{
	  sum_check+=*((uint8_t*)(frame->data)+i);
	  add_check+=sum_check;
	}
    //如果计算与获取的相等，校验成功
	if((sum_check==frame->sum_check)&&(add_check==frame->add_check))
	 return 1;
	else
	 return 0;
}
 
void ano_send_flexible_frame(uint8_t id,int32_t x_coordinate,int32_t y_coordinate)
{
	uint8_t buff[46];
	
	memset(send_frame_struct.data,0,40);
	send_frame_struct.function_id=id;
	send_frame_struct.data_len=8;			   //<根据自己的参数数填写							
	
	/*第一个x_coordinate数据从低位到高位截断*/
	send_frame_struct.data[0]=BYTE0(x_coordinate);
	send_frame_struct.data[1]=BYTE1(x_coordinate);
	send_frame_struct.data[2]=BYTE2(x_coordinate);
	send_frame_struct.data[3]=BYTE3(x_coordinate);
	/*第二个数据y_coordinate从低位到高位截断*/
	send_frame_struct.data[4]=BYTE0(y_coordinate);
	send_frame_struct.data[5]=BYTE1(y_coordinate);
	send_frame_struct.data[6]=BYTE2(y_coordinate);
	send_frame_struct.data[7]=BYTE3(y_coordinate);
	/*第N个数据xxx从低位到高位截断*/
	//......用户自行添加

	ano_check_calculate(&send_frame_struct);
	frame_turn_to_array(&send_frame_struct,buff);


Serial_SendArray(buff,6+send_frame_struct.data_len);
	//ano_usart_send(buff,6+send_frame_struct.data_len);
}
 