#include <stm32f4xx.h>

#define ENABLE_AHB1_BUS 		0x0001
#define ENABLE_APB1_BUS 		0x20000
#define GPIOA_PIN5_OUTPUT_MODE 	0x0400
#define GPIOA_PIN2_AF_MODE 		0x0020
#define GPIOA_PIN3_AF_MODE 		0x0080
#define GPIOA_ENABLE_PIN2_AFR 	0x0700
#define GPIOA_ENABLE_PIN3_AFR 	0x7000
#define BAUD_RATE 				0x0683
#define ENABLE_USART2			0x2000
#define ENABLE_USART2_TE		0x0008
#define ENABLE_USART2_RE		0x0004
#define TURN_LED_ON				0x0020
#define USART2_SR_RXE			0x0020
#define USART2_SR_TXE			0x0080

void BUS_Init(void);
void GPIOA_Init(void);
void USART2_Init(void);
void blink_dot(int count);
void blink_dash(int count);
void delayMs(int delay);
char USART2_Read(void);
void USART2_Write(int ch);

int main(void)
{
	// Initiate BUS and peripherals
	BUS_Init();
	GPIOA_Init();
	USART2_Init();

	char ch;
	USART2_Write('M');
	USART2_Write('C');
	USART2_Write(':');
	USART2_Write(' ');

	while (1) {
		ch = USART2_Read();
		USART2_Write(ch);
		switch (ch) {
		case 'a' :
			blink_dot(1);
			blink_dash(1);
			break;
		case 'b' :
			blink_dash(1);
			blink_dot(3);
			break;
		case 'c' :
			blink_dash(1);
			blink_dot(1);
			blink_dash(1);
			blink_dot(1);
			break;
		case 'd' :
			blink_dash(1);
			blink_dot(2);
			break;
		case 'e' :
			blink_dot(1);
			break;
		case 'f' :
			blink_dot(2);
			blink_dash(1);
			blink_dot(1);
			break;
		case 'g' :
			blink_dash(2);
			blink_dot(1);
			break;
		case 'h' :
			blink_dot(4);
			break;
		case 'i' :
			blink_dot(2);
			break;
		case 'j' :
			blink_dot(1);
			blink_dash(3);
			break;
		case 'k' :
			blink_dash(1);
			blink_dot(1);
			blink_dash(1);
			break;
		case 'l' :
			blink_dot(1);
			blink_dash(1);
			blink_dot(2);
			break;
		case 'm' :
			blink_dash(2);
			break;
		case 'n' :
			blink_dash(1);
			blink_dot(1);
			break;
		case 'o' :
			blink_dash(3);
			break;
		case 'p' :
			blink_dot(1);
			blink_dash(2);
			blink_dot(1);
			break;
		case 'q' :
			blink_dash(2);
			blink_dot(1);
			blink_dash(1);
			break;
		case 'r' :
			blink_dot(1);
			blink_dash(1);
			blink_dot(1);
			break;
		case 's' :
			blink_dot(3);
			break;
		case 't' :
			blink_dash(1);
			break;
		case 'u' :
			blink_dot(2);
			blink_dash(1);
			break;
		case 'v' :
			blink_dot(3);
			blink_dash(1);
			break;
		case 'w' :
			blink_dot(1);
			blink_dash(2);
			break;
		case 'x' :
			blink_dash(1);
			blink_dot(2);
			blink_dash(1);
			break;
		case 'y' :
			blink_dash(1);
			blink_dot(1);
			break;
		case'z' :
			blink_dash(2);
			blink_dot(2);
			break;
		case '0' :
			blink_dash(5);
			break;
		case '1' :
			blink_dot(1);
			blink_dash(4);
			break;
		case '2' :
			blink_dot(2);
			blink_dash(3);
			break;
		case '3' :
			blink_dot(3);
			blink_dash(2);
			break;
		case '4' :
			blink_dot(4);
			blink_dash(1);
			break;
		case '5' :
			blink_dot(5);
			break;
		case '6' :
			blink_dash(1);
			blink_dot(4);
			break;
		case '7' :
			blink_dash(2);
			blink_dot(3);
			break;
		case '8' :
			blink_dash(3);
			blink_dot(2);
			break;
		case '9' :
			blink_dash(4);
			blink_dot(1);
			break;
		default : break;
		}
	}

	delayMs(1);
}

void blink_dot(int count)
{
	while (count > 0) {
		GPIOA->ODR |= TURN_LED_ON;
		delayMs(100);
		GPIOA->ODR &=~ TURN_LED_ON;
		delayMs(100);
		--count;
	}
}

void blink_dash(int count)
{
	while (count > 0) {
		GPIOA->ODR |= TURN_LED_ON;
		delayMs(300);
		GPIOA->ODR &=~ TURN_LED_ON;
		delayMs(100);
		--count;
	}
}

void BUS_Init(void)
{
	RCC->AHB1ENR |= ENABLE_AHB1_BUS;
	RCC->APB1ENR |= ENABLE_APB1_BUS;
}

void GPIOA_Init(void)
{
	GPIOA->MODER |= GPIOA_PIN5_OUTPUT_MODE;
	GPIOA->MODER |= GPIOA_PIN2_AF_MODE;
	GPIOA->MODER |= GPIOA_PIN3_AF_MODE;
	GPIOA->AFR[0] = GPIOA_ENABLE_PIN2_AFR;
	GPIOA->AFR[0] |= GPIOA_ENABLE_PIN3_AFR;
}

void USART2_Init(void)
{
	USART2->BRR = BAUD_RATE;
	USART2->CR1 = ENABLE_USART2;
	USART2->CR1 |= ENABLE_USART2_TE;
	USART2->CR1 |= ENABLE_USART2_RE;
}

char USART2_Read(void)
{
	while (!(USART2->SR & USART2_SR_RXE)) {}
	return USART2->DR;
}

void USART2_Write(int ch)
{
	while(!(USART2->SR & USART2_SR_TXE)) {}
	USART2->DR = ch & 0x00FF;
}

void delayMs(int delay)
{
	int i;
	while (delay > 0) {
		for (i = 0; i < 3195; i++) {
			//
		}
		--delay;
	}
}






