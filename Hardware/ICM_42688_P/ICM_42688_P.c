#include "ICM_42688_P.h"
#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "sys.h"

//unsigned char ICM_42688_Addr_AD0_LOW_READ = 0xD1;   //AD0低电平地址的读
//unsigned char ICM_42688_Addr_AD0_LOW_WRITE = 0xD0;	 //AD0低电平地址的写
//unsigned char ICM_42688_Addr_AD0_LOW_READ = 0xD3;   //AD0低电平地址的读
//unsigned char ICM_42688_Addr_AD0_LOW_WRITE = 0xD2;	 //AD0低电平地址的写


static float accSensitivity   = 0.244f;   //加速度的最小分辨率 mg/LSB
static float gyroSensitivity  = 32.8f;    //陀螺仪的最小分辨率

//unsigned char ICM_42688_Addr_AD0_HIGH_READ = 0xD3;	 //AD0高电平地址的读

//unsigned char ICM_42688_Addr_AD0_HIGH_WRITE = 0xD2; //AD0高电平地址的写

//GYRO Gyro_Get;
//ACC Acc_Get;
//TEMP Temp;

 

#define I2C_R_Add 0xD1   //定义I2C的读地址
#define I2C_W_Add 0xD0    //定义I2C的写地址
#define SCL_DIR                  PB6_M 
#define SDA_DIR                  PB7_M 
#define M_SCK_0                  PB6_OUT_0   //SCK输出控制寄存器位
#define M_SDA_1                  PB7_OUT_1   //SDA输出控制寄存器位
#define M_SDA_0                  PB7_OUT_0
#define R_M_SCK                  PB6_IN
#define R_M_SDA                  PB7_IN      //SDA读寄存器位






/**********************************I2C读端口定义**********************************/

#define I2C_SCL_LOW        SCL_DIR=0x3;//GPIOB->CRH&=(~((UINT32)0x0F<<(4*(10-8))));GPIOB->CRH|=((UINT32)3<<(4*(10-8)));//SCL_DIR=1           //SCL=0
#define I2C_SCL_HIGH       SCL_DIR=0x4; //GPIOB->CRH&=(~((UINT32)0x0F<<(4*(10-8))));GPIOB->CRH|=((UINT32)4<<(4*(10-8)));//SCL_DIR=0           //SCL=1
#define I2C_SDA_LOW        SDA_DIR=0x3; //GPIOB->CRH&=(~((UINT32)0x0F<<(4*(11-8))));GPIOB->CRH|=((UINT32)3<<(4*(11-8)));//SDA_DIR=1           //SDA=0
#define I2C_SDA_HIGH       SDA_DIR=0x4; //GPIOB->CRH&=(~((UINT32)0x0F<<(4*(11-8))));GPIOB->CRH|=((UINT32)4<<(4*(11-8)));//SDA_DIR=0           //SDA=1

#define I2C_Read_SDA        R_M_SDA           //读SDA
#define I2C_Read_SCK        R_M_SCK           //读SCK
#define I2C_ERROR           0

/***************************************函数声明************************************/


//UINT16 I2C_ReadData(UINT8 Command);            //从I2C读取16位数据数据


void ICM_IIC_Delay(void){
//	delay_us(2);
	delay_us(10);
}
/**************************************************/
/*函数名：Port_Init;***********************/
/*功能：初始化硬件IIC通道;************/
/*输入：无;****************************************/
/*输出：无;****************************************/
/**************************************************/
void ICM_Port_Init(){
	//delay_init();
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//先使能外设IO PORTB时钟 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;	 // 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //推挽输出
 
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIO 
	
  GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7);						 //PB10,PB11 输出高	

}	  
// CRC X8+X2+X+1  0x107  最高位忽略 为 0x07

UINT8 crc8(UINT8 buffer[],UINT8 len)
{
		 unsigned char i,j=0;
		 unsigned char crc_register=0;
		 while(len--!=0) // 总字节数
     {
						for(i=0x80; i!=0; i=i>>1) //一个字节8位，故循环8次
            {
                    if((crc_register &0x80)!=0) // 高位为1则进行位或运算crc-16 则为0x8000
                    {
											crc_register<<= 1;   //高位肯定为1，无需运算
											crc_register ^=0x07; // 与生成多项式异或
                    }else{crc_register <<= 1;} //高位不为1，则乘2 
                    if((buffer[j] &i)!=0)  
                    {
                      crc_register^= 0x07; //加上本位的CRC码
                    }
						}				
						j++; // 指向下一字节
      }
      return(crc_register); // 返回CRC-8校验码
}


/***************************  I2C_Fuel  *******************************/
#define   SYS_CLK       72   
// SH367309 最高100K
static void I2C_I2cWait(void)
{
	static UINT8 i;
	if(SYS_CLK!=8)
	{  
//		i=(SYS_CLK-8)>>4;		
i=10;		
	    while(i--)
		  {
			//  ClrWdt();
			  NOP();
			  NOP();
				NOP();
			  NOP();
			  NOP();
				NOP();
				NOP();
			  NOP();
				NOP();
		  }
  }
}
 //起动I2C时序
static void I2C_Start(void)     
{
 M_SCK_0;M_SDA_0;
 I2C_SDA_HIGH;    
 I2C_SCL_HIGH;     
 I2C_I2cWait();
 I2C_I2cWait();
 I2C_SDA_LOW;                                      
 I2C_I2cWait();
 I2C_I2cWait();
 I2C_SCL_LOW; 
 I2C_I2cWait();
}
static void I2C_NoACK(void)
{
 I2C_SDA_HIGH;                                       
 I2C_SCL_HIGH;  
 I2C_I2cWait();
 I2C_I2cWait();
 I2C_SCL_LOW;                                       
 I2C_SDA_LOW; 
 I2C_I2cWait();
 I2C_I2cWait();
}
static void I2C_Stop(void)    //停止I2C时序
{
 I2C_SDA_LOW;                        
 I2C_SCL_HIGH;                         
 I2C_I2cWait();
 I2C_I2cWait(); 
 I2C_SDA_HIGH;  
 I2C_I2cWait();
 I2C_I2cWait();

}
static UINT8 I2C_SlaveACK(void)//检测i2c的应答信号
{
   UINT8 Ask_Data=0;
   INT16 Count=100;
   I2C_SDA_HIGH;            
   I2C_I2cWait();
   I2C_SCL_HIGH;   
   I2C_I2cWait();   	 
   while(I2C_Read_SDA)
   {
//    ClrWdt();           //清看门狗 
    Count--;
    if(Count<=0) 
		{ Ask_Data=1;
		  break;
		}
   }
	 I2C_I2cWait();
   I2C_SCL_LOW;  
   I2C_I2cWait();	
	 I2C_I2cWait();	
   return (Ask_Data);
}
static void I2C_MainAck(void)
{
 I2C_SDA_LOW;
 I2C_I2cWait();
 I2C_SCL_HIGH;                                      
 I2C_I2cWait();
 I2C_I2cWait();
 I2C_SCL_LOW;                                    
 I2C_SDA_HIGH; 
 I2C_I2cWait(); 
 I2C_I2cWait();
}
static void I2C_WriteByte_(UINT8 W_Data)   //往MCP322写一个8位数据
{
  UINT8 i=8;
  do
  {
    if ((W_Data&0x80)==0x80)
    {I2C_SDA_HIGH; } 
    else
    { I2C_SDA_LOW; }           
    I2C_I2cWait();
		I2C_I2cWait();
    I2C_SCL_HIGH;                                       
    I2C_I2cWait();
    I2C_I2cWait();
    I2C_SCL_LOW; 
//#if(CLK===16)		
 //   I2C_I2cWait(); // // CPU 16M 时需要添加 
//#endif
    W_Data<<=1;
  }while(--i!=0);
}
static UINT8 I2C_ReadByte_(void)         //读取一个8位数据
{
  UINT8 i=8,R_Char=0;
  do
  {
    I2C_SDA_HIGH;
    I2C_SCL_HIGH;            
    I2C_I2cWait();
    if(I2C_Read_SDA)
    {R_Char=(R_Char<<1)+1;}
    else
    {R_Char=R_Char<<1;}
    I2C_I2cWait(); 
    I2C_SCL_LOW;  
    I2C_I2cWait(); 
    I2C_I2cWait(); // CPU 16M 时需要添加
  }while(--i!=0); 
  return(R_Char);
}



static UINT8 ReadByte_BQ76940(UINT8 Command,UINT8 *pData)
{
	UINT8 crc,data[2];
	data[0]=I2C_R_Add;
	//DIS_TIME_IRQ();	
  I2C_Start();
  I2C_WriteByte_(I2C_W_Add);         //I2C地址写信号
  I2C_SlaveACK();
  I2C_WriteByte_(Command);           //写入命令  
  I2C_SlaveACK();
  I2C_Start();
  I2C_WriteByte_(I2C_R_Add);         //I2C地址读信号
	I2C_SlaveACK();
  data[1]=I2C_ReadByte_();  // 读8为数据
//	I2C_MainAck();
//  crc=I2C_ReadByte_();      //读CRC
  I2C_NoACK();
  I2C_Stop();
	//EN_TIME_IRQ(); 
//	if(crc==crc8(data,2))
//  {
		*pData=data[1];
		return 1;
//  }else
//	{ *pData=0;
//		return I2C_ERROR;
//	}
}




static UINT8 WriteByte_BQ76940(UINT8 Command,UINT8 Byte) //从I2C写入数据
{
	UINT8 crc,data[3];
	data[0]=I2C_W_Add;
	data[1]=Command;
	data[2]=Byte;
	crc=crc8(data,3);
	//DIS_TIME_IRQ();	
  I2C_Start();
  I2C_WriteByte_(I2C_W_Add);         //I2C地址写信号
  if(I2C_SlaveACK()){I2C_Stop();return I2C_ERROR;}I2C_I2cWait(); 
  I2C_WriteByte_(Command);           //写入命令  
  if(I2C_SlaveACK()){I2C_Stop();return I2C_ERROR;}I2C_I2cWait(); 
  I2C_WriteByte_(Byte); 
  if(I2C_SlaveACK()){I2C_Stop();return I2C_ERROR;}  
//  I2C_WriteByte_(crc);	
//  if(I2C_SlaveACK()){I2C_Stop();return I2C_ERROR;}
  I2C_Stop();
	//EN_TIME_IRQ();
	return 1;
}

static UINT8 I2C_ReadByte_BQ76940(UINT8 Command,UINT8 *pData) //从I2C读取数据
{
	 UINT8 count=5;
	 while(ReadByte_BQ76940(Command,pData)==I2C_ERROR)
   {  count--;
			if(count==0) break;
	 }
   if(count!=0){return 1;}
   else{return 0;}
}
void I2C_WriteByte_BQ76940(UINT8 Command,UINT8 Byte) //从I2C写入数据
{
	 UINT8 count=5;
	 while(WriteByte_BQ76940(Command,Byte)==I2C_ERROR)
   {
		  count--;
			if(count==0) break;
	 }
}



//// 读取块字节
  UINT8 ReadBlockByte_BQ76940(UINT8 Command,UINT8 *pData,UINT8 byteCount)
{
	UINT8 crc,data[61],i,count;
	    count=(byteCount<<1);
	    data[0]=I2C_R_Add;	
			I2C_Start();
			I2C_WriteByte_(I2C_W_Add);         //I2C地址写信号
			I2C_SlaveACK();
			I2C_WriteByte_(Command);           //写入命令  
			I2C_SlaveACK();
			I2C_Start();
			I2C_WriteByte_(I2C_R_Add);         //I2C地址读信号
			I2C_SlaveACK();
		  for(i=0;i<count;i++)
		 {
			data[1+i]=I2C_ReadByte_();  // 读8为数据
			I2C_MainAck();
		 }
			I2C_NoACK();
			I2C_Stop();
		//	if(data[count]==crc8(data+(count-1),1))
			{
				for(i=0;i<byteCount;i++)
				{
				  *(pData+i)=data[1+(i<<1)];
				}
				return 1;
			}
//			else
//			{ *pData=0;
//				return I2C_ERROR;
//			}
}

//UINT8 I2C_ReadBlock_BQ76940(UINT8 Command,UINT8 *pData,UINT8 byteCount) //从I2C读取数据
//{
//	 UINT8 count=5;
//	 while(ReadBlockByte_BQ76940(Command,pData,byteCount)==I2C_ERROR)
//   {  count--;
//			if(count==0) break;
//	 }
//   if(count!=0){return 1;}
//   else{return 0;}
//}
 
 
unsigned char ICM_IIC_WRITE_BYTE(unsigned char RA, unsigned char data_byte)
{
I2C_WriteByte_BQ76940(RA,data_byte);
}

float bsp_Icm42688GetAres(uint8_t Ascale)
{
    switch(Ascale)
    {
    // Possible accelerometer scales (and their register bit settings) are:
    // 2 Gs (11), 4 Gs (10), 8 Gs (01), and 16 Gs  (00).
    case AFS_2G:
        accSensitivity = 2000 / 32768.0f;
        break;
    case AFS_4G:
        accSensitivity = 4000 / 32768.0f;
        break;
    case AFS_8G:
        accSensitivity = 8000 / 32768.0f;
        break;
    case AFS_16G:
        accSensitivity = 16000 / 32768.0f;
        break;
    }

    return accSensitivity;
}

float bsp_Icm42688GetGres(uint8_t Gscale)
{
    switch(Gscale)
    {
    case GFS_15_125DPS:
        gyroSensitivity = 15.125f / 32768.0f;
        break;
    case GFS_31_25DPS:
        gyroSensitivity = 31.25f / 32768.0f;
        break;
    case GFS_62_5DPS:
        gyroSensitivity = 62.5f / 32768.0f;
        break;
    case GFS_125DPS:
        gyroSensitivity = 125.0f / 32768.0f;
        break;
    case GFS_250DPS:
        gyroSensitivity = 250.0f / 32768.0f;
        break;
    case GFS_500DPS:
        gyroSensitivity = 500.0f / 32768.0f;
        break;
    case GFS_1000DPS:
        gyroSensitivity = 1000.0f / 32768.0f;
        break;
    case GFS_2000DPS:
        gyroSensitivity = 2000.0f / 32768.0f;
        break;
    }
    return gyroSensitivity;
}
int8_t bsp_IcmGetRawData(icm42688RawData_t* accData, icm42688RawData_t* GyroData)
{
    uint8_t buffer[12] = {0};

   // icm42688_read_regs(ICM42688_ACCEL_DATA_X1, buffer, 12);
		ReadBlockByte_BQ76940(ICM42688_ACCEL_DATA_X1, buffer, 12);

    accData->x  = ((uint16_t)buffer[0] << 8)  | buffer[1];
    accData->y  = ((uint16_t)buffer[2] << 8)  | buffer[3];
    accData->z  = ((uint16_t)buffer[4] << 8)  | buffer[5];
    GyroData->x = ((uint16_t)buffer[6] << 8)  | buffer[7];
    GyroData->y = ((uint16_t)buffer[8] << 8)  | buffer[9];
    GyroData->z = ((uint16_t)buffer[10] << 8) | buffer[11];


    accData->x = (int16_t)(accData->x * accSensitivity);
    accData->y = (int16_t)(accData->y * accSensitivity);
    accData->z = (int16_t)(accData->z * accSensitivity);

    GyroData->x = (int16_t)(GyroData->x * gyroSensitivity);
    GyroData->y = (int16_t)(GyroData->y * gyroSensitivity);
    GyroData->z = (int16_t)(GyroData->z * gyroSensitivity);

    return 0;
} 
/******************************************************************/
/*函数名：ICM_INIT;***************************************/
/*功能：ICM芯片初始化;*************/
/*输入：无;********************************************************/
/*输出：0 成功 1 失败;***************************************/
/******************************************************************/
unsigned char ICM_INIT(){
	static UINT8 reg_val;
	 I2C_ReadByte_BQ76940(ICM42688_WHO_AM_I,&reg_val );
	 
    WriteByte_BQ76940(ICM42688_REG_BANK_SEL, 0); //设置bank 0区域寄存器
    WriteByte_BQ76940(ICM42688_REG_BANK_SEL, 0x01); //软复位传感器
	  delay_ms(10); 
	 if(reg_val == ICM42688_ID)
    {
        WriteByte_BQ76940(ICM42688_REG_BANK_SEL, 1); //设置bank 1区域寄存器
        WriteByte_BQ76940(ICM42688_INTF_CONFIG4, 0x02); //设置为4线SPI通信

        WriteByte_BQ76940(ICM42688_REG_BANK_SEL, 0); //设置bank 0区域寄存器
        WriteByte_BQ76940(ICM42688_FIFO_CONFIG, 0x40); //Stream-to-FIFO Mode(page63)


        I2C_ReadByte_BQ76940(ICM42688_INT_SOURCE0,&reg_val );
        WriteByte_BQ76940(ICM42688_INT_SOURCE0, 0x00);
        WriteByte_BQ76940(ICM42688_FIFO_CONFIG2, 0x00); // watermark
        WriteByte_BQ76940(ICM42688_FIFO_CONFIG3, 0x02); // watermark
        WriteByte_BQ76940(ICM42688_INT_SOURCE0, reg_val);
        WriteByte_BQ76940(ICM42688_FIFO_CONFIG1, 0x63); // Enable the accel and gyro to the FIFO

        WriteByte_BQ76940(ICM42688_REG_BANK_SEL, 0x00);
        WriteByte_BQ76940(ICM42688_INT_CONFIG, 0x36);

        WriteByte_BQ76940(ICM42688_REG_BANK_SEL, 0x00);
        I2C_ReadByte_BQ76940(ICM42688_INT_SOURCE0,&reg_val );
        reg_val |= (1 << 2); //FIFO_THS_INT1_ENABLE
        WriteByte_BQ76940(ICM42688_INT_SOURCE0, reg_val);

        bsp_Icm42688GetAres(AFS_8G);
        WriteByte_BQ76940(ICM42688_REG_BANK_SEL, 0x00);
       I2C_ReadByte_BQ76940(ICM42688_ACCEL_CONFIG0,&reg_val );//page74
        reg_val |= (AFS_8G << 5);   //量程 ±8g
        reg_val |= (AODR_50Hz);     //输出速率 50HZ
        WriteByte_BQ76940(ICM42688_ACCEL_CONFIG0, reg_val);

        bsp_Icm42688GetGres(GFS_1000DPS);
        WriteByte_BQ76940(ICM42688_REG_BANK_SEL, 0x00);
      I2C_ReadByte_BQ76940(ICM42688_GYRO_CONFIG0,&reg_val );//page73
        reg_val |= (GFS_1000DPS << 5);   //量程 ±1000dps
        reg_val |= (GODR_50Hz);     //输出速率 50HZ
        WriteByte_BQ76940(ICM42688_GYRO_CONFIG0, reg_val);

        WriteByte_BQ76940(ICM42688_REG_BANK_SEL, 0x00);
         I2C_ReadByte_BQ76940(ICM42688_PWR_MGMT0,&reg_val ); //读取PWR—MGMT0当前寄存器的值(page72)
        reg_val &= ~(1 << 5);//使能温度测量
        reg_val |= ((3) << 2);//设置GYRO_MODE  0:关闭 1:待机 2:预留 3:低噪声
        reg_val |= (3);//设置ACCEL_MODE 0:关闭 1:关闭 2:低功耗 3:低噪声
        WriteByte_BQ76940(ICM42688_PWR_MGMT0, reg_val);
        delay_ms(10); //操作完PWR—MGMT0寄存器后 200us内不能有任何读写寄存器的操作

        return 0;
    }
	return 0;
}
 