#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "ICM_42688_P.h"
#include "sys.h"
#include "delay.h"
#include "NM.h"
#include "global.h"

#define ENABLE_INT() __set_PRIMASK(0)  /* 使能全局中断 */
#define DISABLE_INT() __set_PRIMASK(1) /* 禁止全局中断 */
extern u32 task_time_100ms;
extern u32 task_time_1s;
extern u32 task_time_4s;

		icm42688RawData_t stAccData;
	icm42688RawData_t stGyroData;
//	InvnAlgoAGMConfig config;
//	InvnAlgoAGMInput input;
//  InvnAlgoAGMOutput output;
	
extern unsigned char ICM_Port_Init();

extern void ano_send_flexible_frame(uint8_t id,int32_t x_coordinate,int32_t y_coordinate);
extern unsigned char ICM_INIT();
u32  g_uc=0;
extern void uart_init(u32 bound);
extern void TIM_Interrupt_Init(TIM_TypeDef* TIMx, unsigned int arr, unsigned int psc);
  void led_task()
	{
		static int state=0;
		
		if(state==0)
		{	PC13_OUT_1;state=1;}
		else 	 {	PC13_OUT_0;state=0;}	
	}
int main(void)
{
 
	
	SCB->VTOR = FLASH_BASE | 0x2000;
	//	SCB->VTOR = FLASH_BASE | 0;
uart_init(9600);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
 
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
 //	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//	ICM_Port_Init();
	//while(ICM_Gyroscope_Reset()==1);
BootloaderInit();
//	ICM_INIT();
	TIM_Interrupt_Init(TIM2,10000,72);
	ENABLE_INT();
	while(1)
	{
		
 SerialDecodeHook();
			if (task_time_1s >= 100 ) // 1s任务
		{
			task_time_1s = 0;
	ModbusSendDataCode();
		}
			if (task_time_100ms >= 10 ) // 100ms任务
		{
			task_time_100ms = 0;
			led_task();
				//	bsp_IcmGetRawData(&stAccData,&stGyroData);
//			ano_send_flexible_frame(0xf1,g_uc,stAccData.x);
//			g_uc++;
//		  	printf("AccX:%d--AccY:%d--AccZ:%d----GyroX:%d--GyroY:%d--GyroZ:%d\n",stAccData.x,stAccData.y,stAccData.z,stGyroData.x,stGyroData.y,stGyroData.z);
//			input.sRacc_data[0] = stAccData.x;
//		input.sRacc_data[1] = stAccData.y;
//		input.sRacc_data[2] = stAccData.z;
//		input.sRgyr_data[0] = stGyroData.x;
//		input.sRgyr_data[1] = stGyroData.y;
//		input.sRgyr_data[2] = stGyroData.z;
//			invn_algo_agm_process (&input, &output);
		//	printf("X:%d--Y:%d--Z:%d---temp:%d\n",output.grv_quat_q30[0],output.grv_quat_q30[1],output.grv_quat_q30[2],output.grv_quat_q30[3]);

				//	GYRO_ACC_TEMP_GET();
 	
	 
		}

//		OLED_ShowSignedNum(1, 1, Acc_Get.X, 5);
//		OLED_ShowSignedNum(2, 1, Acc_Get.Y, 5);
//		OLED_ShowSignedNum(3, 1, Acc_Get.Z, 5);
//		OLED_ShowSignedNum(1, 7, Gyro_Get.X, 5);
//		OLED_ShowSignedNum(2, 7, Gyro_Get.Y, 5);
//		OLED_ShowSignedNum(3, 7, Gyro_Get.Z, 5);
//		OLED_ShowSignedNum(4, 1, Temp.T, 5);


	}
}
