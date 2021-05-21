#include "array.h"
/*
矩阵键盘程序
*/
uint8_t keyvalue=99;
uint8_t set_free=0,key_press=99;
/** Configure pins as
		H1,H2,H3,H4 PC0 PC1	PC2 PC3 //行，推挽，扫描时高电平
		L1,L2,L3,L4 PA4 PA5	PA6 PA7 //列  （下拉）输入，检测高电平
		如电源不稳会导致输出高电平失灵！！
		keyvalue，输出值
*/
void ArrayKey_Init(void)
{
  //RCC->APB2ENR|=(5<<2);
	
  /*Configure GPIO pin : GPIOA in */	
	GPIOA->CRL&=~ (0xffff0000);//操作在前四位
	GPIOA->CRL|=  (0x88880000);//1000B PU/PD_input
	GPIOA->ODR&=~ (0x0f<<4);   //下拉
	
  /*Configure GPIO pins : GPIOC out */
	GPIOC->CRL&=~(0x0000ffff);//???????????!!!!!
	GPIOC->CRL|=(0x00001111);//0*4
}

/* USER CODE BEGIN 2 */




void Key_Scan(void){  //扫描
	key_press=99;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
	if		 (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==1)key_press=1;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==1)key_press=2;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==1)key_press=3;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)==1)key_press=10;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	if		 (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==1)key_press=4;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==1)key_press=5;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==1)key_press=6;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)==1)key_press=11;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
	if		 (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==1)key_press=7;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==1)key_press=8;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==1)key_press=9;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)==1)key_press=12;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
	if		 (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4)==1)key_press=0;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5)==1)key_press=15;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6)==1)key_press=14;
	else if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7)==1)key_press=13;
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
	
	//按键消抖
	if(set_free==0){if(key_press!=99){keyvalue=key_press;}}//keyvalue设置成功
	if(key_press==99)set_free=0;                         //上一次是否松开
	else             set_free=1;
	
}


