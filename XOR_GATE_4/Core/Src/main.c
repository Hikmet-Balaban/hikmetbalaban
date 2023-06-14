#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "main.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"

#define INPUT_COUNT 2

extern USBD_HandleTypeDef hUsbDeviceFS;

// Global variables
float weights[INPUT_COUNT];
float bias;

// Function prototypes
void UpdateOutput(USBD_HandleTypeDef *pdev);

int main(void)
{
  // Initialize HAL
  HAL_Init();

  // USB CDC device initialization
  MX_USB_DEVICE_Init();

  // Initialize weights and bias
  for (int i = 0; i < INPUT_COUNT; i++)
  {
    weights[i] = 1.0f;
  }
  bias = -1.0f;

  while (1)
  {
    // Send USB CDC data
    UpdateOutput(&hUsbDeviceFS);

    // Other operations here
  }
}

void UpdateOutput(USBD_HandleTypeDef *pdev)
{
  // Read input values
  uint8_t input[INPUT_COUNT];
  // Read input values from GPIO or other sources

  // Calculate output value
  float sum = 0.0f;
  for (int i = 0; i < INPUT_COUNT; i++)
  {
    sum += input[i] * weights[i];
  }
  sum += bias;

  uint8_t output;
  if (sum >= 0)
  {
    output = 1;
  }
  else
  {
    output = 0;
  }

  // Convert output to string
  char outputStr[2];
  outputStr[0] = output + '0';
  outputStr[1] = '\0';

  // Send data through USB CDC
  CDC_Transmit_FS((uint8_t *)outputStr, strlen(outputStr));
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  // Update input values

  // Calculate output value
  UpdateOutput(&hUsbDeviceFS);
}
