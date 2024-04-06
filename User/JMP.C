
#include "stm32f10x.h"
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

__asm void GenerateSystemReset(void) 
{ 
	  MOV R0, #1           //;  
	  MSR FAULTMASK, R0    //; FAULTMASK 禁止一切中断产生 
	  LDR R0, =0xE000ED0C  //; 
	  LDR R1, =0x05FA0004  //;  
	  STR R1, [R0]         //;    
} 
