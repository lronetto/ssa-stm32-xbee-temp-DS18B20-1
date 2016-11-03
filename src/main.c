#include "stm32f10x.h"
#include "conf.h"
//#include "controle.h"
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ds18b20.h"
#include "xbee.h"
#include "func.h"
#include "ssa.h"
#include "media.h"

<<<<<<< HEAD
ds18b20_TypeDef ds1,ds2;
=======
ds18b20_TypeDef ds;
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
void func_process();
void xbee_process();

GPIO_InitTypeDef GPIO_InitStructure;

Inout_T	inout;
Func_T func;
xbee_t xbee;
<<<<<<< HEAD
Media_T mtemp[2];
=======
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
EE_t eep;
AnalogVar_T var;
AnalogVar_T var_aux;

uint8_t payload[100];

uint8_t	xbee_broadcast[]={0,0,0,0,0,0,0xFF,0xFF};
uint8_t xbee_coord[8];
<<<<<<< HEAD

=======
Media_T temp1;
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
uint8_t flag_in[]={0,0,0,0};
int i,j;
int main(){
	uint32_t start,start1,start2;

	Delay_Init();
	usart1_init();
<<<<<<< HEAD
	//EXTI_config();
	usart2_init();
	//usart3_init();
	//ADC1_Initm();
	uint8_t func_addr[8]={0x00,0x13,0xA2,0x00,0x40,0xE5,0xF2,0x44};



	eep.var.type[0]=1;
	//2 minutos
	eep.var.tempo[0]=2;
	eep.var.temposum[0]=0;

	eep.var.type[1]=1;
	//2 minutos
	eep.var.tempo[1]=2;
	eep.var.temposum[1]=0;
	eep.var.qtd=2;

	//EE_Write(eep);
	//EE_Write(eep);



	EE_Read(&eep);
	EE_Read(&eep);

	memset(eep.var.temposum,0,sizeof(eep.var.temposum));
	inout.out[0].GPIO=GPIOC;
	inout.out[0].pin=GPIO_Pin_13;
=======
	EXTI_config();
	//usart2_init();
	usart3_init();
	//ADC1_Initm();
	uint8_t func_addr[8]={0x00,0x13,0xA2,0x00,0x40,0xE5,0xF2,0x44};

	//temp
	eep.var.type[0]=1;
	//2 minutos
	eep.var.tempo[0]=60;
	eep.var.temposum[0]=0;
	eep.var.medias[0]=3;
	eep.var.qtd=1;

	inout.out[0].GPIO=GPIOA;
	inout.out[0].pin=GPIO_Pin_0;
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb

	inout.out[1].GPIO=GPIOA;
	inout.out[1].pin=GPIO_Pin_1;

	inout.out[2].GPIO=GPIOA;
	inout.out[2].pin=GPIO_Pin_2;

	inout.out[3].GPIO=GPIOA;
	inout.out[3].pin=GPIO_Pin_3;

	inout.out[4].GPIO=GPIOA;
	inout.out[4].pin=GPIO_Pin_4;

	//se pressionar in0 vou acionar o out1
	eep.func.aci[0].type=FUNC_LOCAL;
	eep.func.aci[0].out=1;
	eep.func.aci[0].act=1;

	eep.func.aci[1].type=FUNC_LOCAL;
	eep.func.aci[1].out=2;
	eep.func.aci[1].act=1;

	eep.func.aci[2].type=FUNC_LOCAL;
	eep.func.aci[2].out=3;
	eep.func.aci[2].act=1;

	eep.func.aci[3].type=FUNC_REMOTE;
<<<<<<< HEAD
	eep.func.aci[3].out=4;
=======
	eep.func.aci[3].out=0;
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
	eep.func.aci[3].act=1;
	memcpy(eep.func.aci[3].dest_addr,func_addr,8);
	//func.aci[3].dest_addr=func_addr;

<<<<<<< HEAD

	//SysTick_Config(SystemCoreClock / 1000);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	static uint8_t addr1[]={0x28,0xFF,0XAB,0xA9,0x83,0x15,0x02,0x18};
	static uint8_t addr2[]={0x28,0xFF,0x90,0x5E,0x90,0x15,0x03,0xEB};
	//static uint8_t addr2[]={0x28,0xFF,0x88,0x9E,0x83,0x15,0x02,0x60};

	Ds18b20_Init(&ds1,GPIOB,GPIO_Pin_12,addr1);
	Ds18b20_Init(&ds2,GPIOB,GPIO_Pin_12,addr2);
	//Ds18b20_ReadROM(&ds2);
	//Ds18b20_ConvertTemperature(ds);
	//Ds18b20_ReadTemperature(&ds);
	media_Init(&mtemp[0],eep.var.medias[0]);
	media_Init(&mtemp[1],eep.var.medias[1]);
	payload[0]=SSA_F_CORD_ADDR;
	printf("ola mundo qtd=%d\r\n",eep.var.qtd);
	xbee_SendData(&xbee,xbee_broadcast,payload,1);

	start=TIM2->CNT;
	start2=TIM2->CNT;
	while(1){
		if((TIM2->CNT-start)>=1000){
			//printf("teste\r\n");
			Ds18b20_ConvertTemperature(ds1);
			Ds18b20_ReadTemperature(&ds1);
			eep.var.ana[0].val=media_process(&mtemp[0],ds1.temp);
			Delay_ms(10);
			Ds18b20_ConvertTemperature(ds2);
			Ds18b20_ReadTemperature(&ds2);
			eep.var.ana[1].val=media_process(&mtemp[1],ds2.temp);

			//printf("temp1=%2.2f temp2=%2.2f\r\n",eep.var.ana[0].val,eep.var.ana[1].val);
			start=TIM2->CNT;
		}
		if((TIM2->CNT-start2)>1000){
					var_aux.qtd=0;
					for(i=0;i<eep.var.qtd;i++){

						if(eep.var.temposum[i]==eep.var.tempo[i]){

							var_aux.type[var_aux.qtd]=eep.var.type[i];
							var_aux.tempo[var_aux.qtd]=eep.var.tempo[i];
							var_aux.medias[var_aux.qtd]=eep.var.medias[i];
							var_aux.ana[var_aux.qtd]=eep.var.ana[i];
							var_aux.n[var_aux.qtd]=i;
							var_aux.qtd++;
							eep.var.temposum[i]=0;
							}
						else eep.var.temposum[i]++;

					}
					if(var_aux.qtd>0){
						payload[0]=SSA_F_ANALOG;
						payload[1]=var_aux.qtd;
						for(i=0;i<var_aux.qtd;i++){
							//id da variavel no dispositivo
							payload[2+i*8]=var_aux.n[i];
							payload[3+i*8]=var_aux.tempo[i];
							payload[4+i*8]=var_aux.type[i];
							payload[5+i*8]=var_aux.medias[i];
							for(j=0;j<4;j++)
								payload[6+i*8+j]=var_aux.ana[i].byte.b[j];
							}

						xbee_SendData(&xbee,xbee_coord,payload,2+var_aux.qtd*8+1);
						printf("send %2.2f\r\n",var.ana[0].val);
						fflush(stdout);

					}
					start2=TIM2->CNT;
				}
=======
	//EE_Write(eep);
	//EE_Write(eep);

	EE_Read(&eep);

	//SysTick_Config(SystemCoreClock / 1000);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |  GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	uint8_t addr[8]={0x28,0xff,0x90,0x5e,0x90,0x15,0x3,0xeb};
	Ds18b20_Init(&ds,GPIOB,GPIO_Pin_5,addr);
	Ds18b20_ReadROM(&ds);
	//Ds18b20_ConvertTemperature(ds);
	//Ds18b20_ReadTemperature(&ds);
	media_Init(&temp1,eep.var.medias[0]);
	payload[0]=SSA_F_CORD_ADDR;
	printf("ola mundo\r\n");
	xbee_SendData(&xbee,xbee_broadcast,payload,1);

	start=TIM2->CNT;
	start1=TIM2->CNT;
	start2=TIM2->CNT;
	while(1){
		if((TIM2->CNT-start1)>1000){
			Ds18b20_ConvertTemperature(ds);
			Ds18b20_ReadTemperature(&ds);
			eep.var.ana[0].val=media_process(&temp1,ds.temp);
			//printf("temp=%2.2f\r\n",eep.var.ana[0].val);
			start1=TIM2->CNT;
		}
		if((TIM2->CNT-start2)>1000){
			var_aux.qtd=0;
			for(i=0;i<eep.var.qtd;i++){
				if(eep.var.temposum[i]==eep.var.tempo[i]){

					var_aux.type[var_aux.qtd]=eep.var.type[i];
					var_aux.tempo[var_aux.qtd]=eep.var.tempo[i];
					var_aux.ana[var_aux.qtd]=eep.var.ana[i];
					var_aux.medias[var_aux.qtd]=eep.var.medias[i];
					var_aux.n[var_aux.qtd]=i;
					var_aux.qtd++;
					eep.var.temposum[i]=0;
					}
				else
					eep.var.temposum[i]++;
			}
			if(var_aux.qtd>0){
				payload[0]=SSA_F_ANALOG;
				payload[1]=var_aux.qtd;
				for(i=0;i<var_aux.qtd;i++){
					//id da variavel no dispositivo
					payload[2+i*8]=var_aux.n[i];
					payload[3+i*8]=var_aux.tempo[i];
					payload[4+i*8]=var_aux.type[i];
					payload[5+i*8]=var_aux.medias[i];
					for(j=0;j<4;j++)
						payload[6+i*8+j]=var_aux.ana[i].byte.b[j];
					}

				xbee_SendData(&xbee,xbee_coord,payload,2+var_aux.qtd*8+1);
				printf("send %2.2f\r\n",eep.var.ana[0].val);

			}
			start2=TIM2->CNT;
		}
		if((TIM2->CNT-start)>500){
			if(GPIOA->ODR & GPIO_Pin_0) GPIOA->ODR&=~GPIO_Pin_0;
			else GPIOA->ODR|=GPIO_Pin_0;
			start=TIM2->CNT;
		}
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
		xbee_process();
		func_process();
		}
	}
<<<<<<< HEAD
void USART2_IRQHandler(void){
	if(USART_GetFlagStatus(USART2,USART_IT_RXNE)){
	xbee_usart(&xbee,USART_ReceiveData(USART2));
	}
	USART_ClearITPendingBit(USART2,USART_IT_RXNE);
=======
void USART1_IRQHandler(void){
	if(USART_GetFlagStatus(USART1,USART_IT_RXNE)){
	xbee_usart(&xbee,USART_ReceiveData(USART1));
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
}
void EXTI9_5_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line9) != RESET){
		flag_in[0]=1;
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
	if(EXTI_GetITStatus(EXTI_Line8) != RESET){
			flag_in[1]=1;
			EXTI_ClearITPendingBit(EXTI_Line8);
		}
	if(EXTI_GetITStatus(EXTI_Line7) != RESET){
			flag_in[2]=1;
			EXTI_ClearITPendingBit(EXTI_Line7);
		}
	if(EXTI_GetITStatus(EXTI_Line6) != RESET){
			flag_in[3]=1;
			EXTI_ClearITPendingBit(EXTI_Line6);
		}
}
void func_process(){
	for(i=0;i<4;i++){
		if(flag_in[i]){
			printf("in %d\r\n",i);
			//funcao ativa?
<<<<<<< HEAD
			if(eep.func.aci[i].act){
				//é funcao local?
				switch(func.aci[i].type){
					case FUNC_LOCAL:
						func_GPIO_T((inout.out[func.aci[i].out]));
						payload[0]=SSA_F_OUTP;
						payload[1]=eep.func.aci[i].out;
						xbee_SendData(&xbee,xbee_coord,payload,2);
=======
			if(func.aci[i].act){
				//é funcao local?
				switch(eep.func.aci[i].type){
					case FUNC_LOCAL:
						payload[2]=func_GPIO_T((inout.out[func.aci[i].out]));
						payload[0]=SSA_F_OUTP;
						payload[1]=eep.func.aci[i].out;
						xbee_SendData(&xbee,xbee_coord,payload,3);
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
						printf("teste\r\n");
						break;
					case FUNC_REMOTE:
						payload[0]=SSA_F_OUT;
						payload[1]=eep.func.aci[i].out;
						xbee_SendData(&xbee,eep.func.aci[i].dest_addr,payload,2);
						break;
<<<<<<< HEAD

=======
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
					}
				}
			flag_in[i]=0;
			}
		}
	}
void xbee_process(void){

	if(!xbee.start){
		xbee_reciver(&xbee);
<<<<<<< HEAD

=======
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
		printf("rec: ");
		for(i=0;i<xbee.buf[2]+4;i++)
			printf("%02X ",xbee.buf[i]);
		printf("\r\n");
		switch(xbee.type){
			case XBEE_STATUS:
				if(!xbee.buf[XBEE_STATUS_SUCESS]){
<<<<<<< HEAD
					//printf("success\r\n");
=======
					printf("success\r\n");
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
					}
				break;
			case XBEE_RECEIVE_PACKET:
				switch(xbee.buf[XBEE_PAYLOAD_OFFSET]){
					//recebe o endereco de coordinator
					case SSA_F_CORD_ADDRP:
						printf("cord addr: ");
						for(i=0;i<8;i++){
							xbee.addr_cord[i]=xbee.buf[XBEE_PAYLOAD_OFFSET+1+i];
							printf("0x%02X ",xbee.buf[XBEE_PAYLOAD_OFFSET+1+i]);
						}
						printf("\r\n");
					break;
					//altera o estado da saida e manda o estado atual de volta
					case SSA_F_OUT:
						payload[0]=SSA_F_OUTP;
						payload[1]=xbee.buf[XBEE_PAYLOAD_OFFSET+1];
						printf("out=%d\r\n",payload[1]);
						payload[2]=func_GPIO_T((inout.out[xbee.buf[XBEE_PAYLOAD_OFFSET+1]]));
<<<<<<< HEAD
						xbee_SendData(&xbee,xbee.addr_cord,payload,3);
=======
						xbee_SendData(&xbee,xbee.source_Address,payload,3);
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
						break;
					case SSA_F_FUNC:
						eep.func.aci[xbee.buf[XBEE_PAYLOAD_OFFSET+2]].act=1;
						eep.func.aci[xbee.buf[XBEE_PAYLOAD_OFFSET+2]].type=xbee.buf[XBEE_PAYLOAD_OFFSET+1];
						eep.func.aci[xbee.buf[XBEE_PAYLOAD_OFFSET+2]].out=xbee.buf[XBEE_PAYLOAD_OFFSET+3];
						for(i=0;i<8;i++)
							eep.func.aci[xbee.buf[XBEE_PAYLOAD_OFFSET+2]].dest_addr[i]=xbee.buf[XBEE_PAYLOAD_OFFSET+4+i];

						break;
					case SSA_F_ANALOG_TEMPO:
<<<<<<< HEAD
						printf("teste\r\n");
						//printf("ind=%d  tempo=%d\r\n",xbee.buf[XBEE_PAYLOAD_OFFSET+2+0*2],xbee.buf[XBEE_PAYLOAD_OFFSET+3+0*2]);
=======
						//printf("teste tempo=%d\r\n",xbee.buf[XBEE_PAYLOAD_OFFSET+3+i*2]);
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
						for(i=0;i<xbee.buf[XBEE_PAYLOAD_OFFSET+1];i++){
							//tempo
							eep.var.tempo[xbee.buf[XBEE_PAYLOAD_OFFSET+2+i*3]]=xbee.buf[XBEE_PAYLOAD_OFFSET+3+i*3];
							//media
							eep.var.medias[xbee.buf[XBEE_PAYLOAD_OFFSET+2+i*3]]=xbee.buf[XBEE_PAYLOAD_OFFSET+4+i*3];
<<<<<<< HEAD
							media_Init(&mtemp[xbee.buf[XBEE_PAYLOAD_OFFSET+2+i*3]],eep.var.medias[xbee.buf[XBEE_PAYLOAD_OFFSET+2+i*3]]);
							}
						memset(eep.var.temposum,0,sizeof(eep.var.temposum));
						EE_Write(eep);
						break;
=======
							media_Init(&temp1,eep.var.medias[xbee.buf[XBEE_PAYLOAD_OFFSET+2+i*3]]);
							}
						memset(eep.var.temposum,0,sizeof(eep.var.temposum));

						EE_Write(eep);
						break;

>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
					}
				break;
			}
		xbee.start=1;
		}
	}
<<<<<<< HEAD

=======
>>>>>>> 121759d14967f77fcd5ccc583bb7c81a86b42bbb
