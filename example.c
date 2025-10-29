#include "main.h"
#include "ADM0802A.h"

#define RW_Pin GPIO_PIN_0
#define RW_GPIO_Port GPIOA
#define RS_Pin GPIO_PIN_1
#define RS_GPIO_Port GPIOA
#define CA_Pin GPIO_PIN_4
#define CA_GPIO_Port GPIOA
#define E_Pin GPIO_PIN_5
#define E_GPIO_Port GPIOA
#define DB0_Pin GPIO_PIN_6
#define DB0_GPIO_Port GPIOA
#define DB1_Pin GPIO_PIN_7
#define DB1_GPIO_Port GPIOA
#define DB6_Pin GPIO_PIN_4
#define DB6_GPIO_Port GPIOC
#define DB7_Pin GPIO_PIN_5
#define DB7_GPIO_Port GPIOC
#define DB2_Pin GPIO_PIN_0
#define DB2_GPIO_Port GPIOB
#define DB3_Pin GPIO_PIN_1
#define DB3_GPIO_Port GPIOB
#define DB4_Pin GPIO_PIN_2
#define DB4_GPIO_Port GPIOB
#define DB5_Pin GPIO_PIN_10
#define DB5_GPIO_Port GPIOB

// Optional for potentiometer for contrast adjust (CA) pin
DAC_HandleTypeDef hdac;

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_DAC_Init();

  HAL_DAC_Init (&hdac);
  HAL_DAC_Start (&hdac, DAC_CHANNEL_1);

  ADM0802A_Init ();
  // ADM0802A_Init (0);

  // Set CA to 3.3V/2
  HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 2048);


  HAL_Delay (1000);
  ADM0802A_DataWrite ('H', false);
  HAL_Delay (500);
  ADM0802A_DataWrite ('E', false);
  HAL_Delay (500);
  ADM0802A_DataWrite ('L', false);
  HAL_Delay (500);
  ADM0802A_DataWrite ('L', false);
  HAL_Delay (500);
  ADM0802A_DataWrite ('0', false);

  while (1) {}
}
