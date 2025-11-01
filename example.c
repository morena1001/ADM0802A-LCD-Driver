#include "main.h"
#include "ADM0802A.h"

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
