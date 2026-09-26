/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Exercise 6 - Analog Clock LED Test
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* USER CODE BEGIN PFP */

void turnOffAllClockLEDs(void);
void testClockLEDs(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
 * Turn OFF all 12 LEDs.
 *
 * The circuit is assumed to be active-low:
 *
 * GPIO_PIN_RESET = LED ON
 * GPIO_PIN_SET   = LED OFF
 */
void turnOffAllClockLEDs(void)
{
    HAL_GPIO_WritePin(GPIOA,
                      CLOCK_0_Pin  |
                      CLOCK_1_Pin  |
                      CLOCK_2_Pin  |
                      CLOCK_3_Pin  |
                      CLOCK_4_Pin  |
                      CLOCK_5_Pin  |
                      CLOCK_6_Pin  |
                      CLOCK_7_Pin  |
                      CLOCK_8_Pin  |
                      CLOCK_9_Pin  |
                      CLOCK_10_Pin |
                      CLOCK_11_Pin,
                      GPIO_PIN_SET);
}


/*
 * Test all 12 LEDs one by one.
 *
 * LED sequence:
 *
 * CLOCK_0
 * CLOCK_1
 * CLOCK_2
 * ...
 * CLOCK_11
 */
void testClockLEDs(void)
{
    const uint16_t clockPins[12] =
    {
        CLOCK_0_Pin,
        CLOCK_1_Pin,
        CLOCK_2_Pin,
        CLOCK_3_Pin,
        CLOCK_4_Pin,
        CLOCK_5_Pin,
        CLOCK_6_Pin,
        CLOCK_7_Pin,
        CLOCK_8_Pin,
        CLOCK_9_Pin,
        CLOCK_10_Pin,
        CLOCK_11_Pin
    };

    for (int i = 0; i < 12; i++)
    {
        /*
         * Make sure all LEDs are OFF first.
         */
        turnOffAllClockLEDs();

        /*
         * Turn current LED ON.
         *
         * Active-low:
         * RESET = ON
         */
        HAL_GPIO_WritePin(GPIOA,
                          clockPins[i],
                          GPIO_PIN_RESET);

        /*
         * Keep LED ON for 500 ms.
         */
        HAL_Delay(500);
    }

    /*
     * Turn OFF the last LED
     * before starting the next cycle.
     */
    turnOffAllClockLEDs();

    HAL_Delay(500);
}

/* USER CODE END 0 */


/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /*
     * Reset of all peripherals,
     * Initializes the Flash interface and the Systick.
     */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /*
     * Configure the system clock
     */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /*
     * Initialize all configured peripherals
     */
    MX_GPIO_Init();

    /* USER CODE BEGIN 2 */

    /*
     * Turn OFF all 12 LEDs
     * before starting the test.
     */
    turnOffAllClockLEDs();

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    while (1)
    {
        /*
         * Test LEDs from CLOCK_0
         * to CLOCK_11 in sequence.
         */
        testClockLEDs();

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }

    /* USER CODE END 3 */
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /**
      * Initializes the RCC Oscillators
      * according to the specified parameters.
      */
    RCC_OscInitStruct.OscillatorType =
            RCC_OSCILLATORTYPE_HSI;

    RCC_OscInitStruct.HSIState =
            RCC_HSI_ON;

    RCC_OscInitStruct.HSICalibrationValue =
            RCC_HSICALIBRATION_DEFAULT;

    RCC_OscInitStruct.PLL.PLLState =
            RCC_PLL_NONE;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /**
      * Initializes CPU, AHB and APB clocks.
      */
    RCC_ClkInitStruct.ClockType =
            RCC_CLOCKTYPE_HCLK |
            RCC_CLOCKTYPE_SYSCLK |
            RCC_CLOCKTYPE_PCLK1 |
            RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource =
            RCC_SYSCLKSOURCE_HSI;

    RCC_ClkInitStruct.AHBCLKDivider =
            RCC_SYSCLK_DIV1;

    RCC_ClkInitStruct.APB1CLKDivider =
            RCC_HCLK_DIV1;

    RCC_ClkInitStruct.APB2CLKDivider =
            RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct,
                            FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}


/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /*
     * GPIO Ports Clock Enable
     */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*
     * Initial output level:
     *
     * Turn OFF all clock LEDs.
     *
     * Active-low:
     * SET = OFF
     */
    HAL_GPIO_WritePin(GPIOA,
                      CLOCK_0_Pin  |
                      CLOCK_1_Pin  |
                      CLOCK_2_Pin  |
                      CLOCK_3_Pin  |
                      CLOCK_4_Pin  |
                      CLOCK_5_Pin  |
                      CLOCK_6_Pin  |
                      CLOCK_7_Pin  |
                      CLOCK_8_Pin  |
                      CLOCK_9_Pin  |
                      CLOCK_10_Pin |
                      CLOCK_11_Pin,
                      GPIO_PIN_SET);

    /*
     * Configure PA4 -> PA15
     * as GPIO outputs.
     */
    GPIO_InitStruct.Pin =
                      CLOCK_0_Pin  |
                      CLOCK_1_Pin  |
                      CLOCK_2_Pin  |
                      CLOCK_3_Pin  |
                      CLOCK_4_Pin  |
                      CLOCK_5_Pin  |
                      CLOCK_6_Pin  |
                      CLOCK_7_Pin  |
                      CLOCK_8_Pin  |
                      CLOCK_9_Pin  |
                      CLOCK_10_Pin |
                      CLOCK_11_Pin;

    GPIO_InitStruct.Mode =
            GPIO_MODE_OUTPUT_PP;

    GPIO_InitStruct.Pull =
            GPIO_NOPULL;

    GPIO_InitStruct.Speed =
            GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA,
                  &GPIO_InitStruct);
}


/* USER CODE BEGIN 4 */

/* USER CODE END 4 */


/**
  * @brief  This function is executed
  *         in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */

    __disable_irq();

    while (1)
    {
    }

    /* USER CODE END Error_Handler_Debug */
}


#ifdef USE_FULL_ASSERT

/**
  * @brief Reports the name of the source file
  *        and source line number where
  *        assert_param error occurred.
  *
  * @param file Pointer to source file name
  * @param line Error line number
  * @retval None
  */
void assert_failed(uint8_t *file,
                   uint32_t line)
{
    /* USER CODE BEGIN 6 */

    /* User can add implementation here */

    /* USER CODE END 6 */
}

#endif /* USE_FULL_ASSERT */
