/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Exercise 5 - Traffic Light with 7 Segment Countdown
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

void clearAllLEDs(void);
void display7SEG(int num);
void countdown(int seconds);

/* USER CODE END PFP */


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/*
 * Turn OFF all traffic-light LEDs.
 *
 * Traffic LEDs are active-low:
 *
 * GPIO_PIN_RESET = ON
 * GPIO_PIN_SET   = OFF
 */
void clearAllLEDs(void)
{
    HAL_GPIO_WritePin(GPIOA,
                      RED_1_Pin |
                      YELLOW_1_Pin |
                      GREEN_1_Pin |
                      RED_2_Pin |
                      YELLOW_2_Pin |
                      GREEN_2_Pin,
                      GPIO_PIN_SET);
}
void display7SEG(int num)
{
    const uint8_t segTable[10][7] =
    {
        {1,1,1,1,1,1,0},   // 0
        {0,1,1,0,0,0,0},   // 1
        {1,1,0,1,1,0,1},   // 2
        {1,1,1,1,0,0,1},   // 3
        {0,1,1,0,0,1,1},   // 4
        {1,0,1,1,0,1,1},   // 5
        {1,0,1,1,1,1,1},   // 6
        {1,1,1,0,0,0,0},   // 7
        {1,1,1,1,1,1,1},   // 8
        {1,1,1,1,0,1,1}    // 9
    };


    const uint16_t segPins[7] =
    {
        GPIO_PIN_0,     // a
        GPIO_PIN_1,     // b
        GPIO_PIN_2,     // c
        GPIO_PIN_3,     // d
        GPIO_PIN_4,     // e
        GPIO_PIN_5,     // f
        GPIO_PIN_6      // g
    };
    /* Only allow numbers from 0 to 9 */
    if (num < 0 || num > 9)
    {
        return;
    }
    for (int i = 0; i < 7; i++)
    {
        if (segTable[num][i] == 1)
        {
            HAL_GPIO_WritePin(GPIOB,
                              segPins[i],
                              GPIO_PIN_RESET);
        }
        else
        {
            HAL_GPIO_WritePin(GPIOB,
                              segPins[i],
                              GPIO_PIN_SET);
        }
    }
}
void countdown(int seconds)
{
    for (int i = seconds; i > 0; i--)
    {
        display7SEG(i);

        HAL_Delay(1000);
    }
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

    /* Reset of all peripherals, Initializes the Flash interface and Systick. */
    HAL_Init();


    /* USER CODE BEGIN Init */

    /* USER CODE END Init */


    /* Configure the system clock */
    SystemClock_Config();


    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */


    /* Initialize all configured peripherals */
    MX_GPIO_Init();


    /* USER CODE BEGIN 2 */


    /*
     * Turn OFF all traffic-light LEDs at startup.
     */
    clearAllLEDs();


    /*
     * Turn OFF all 7-segment segments at startup.
     *
     * Common Anode:
     *
     * SET = OFF
     */
    HAL_GPIO_WritePin(GPIOB,
                      GPIO_PIN_0 |
                      GPIO_PIN_1 |
                      GPIO_PIN_2 |
                      GPIO_PIN_3 |
                      GPIO_PIN_4 |
                      GPIO_PIN_5 |
                      GPIO_PIN_6,
                      GPIO_PIN_SET);


    /* USER CODE END 2 */


    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    while (1)
    {

        /*
         * ==========================================================
         * PHASE 1
         *
         * Road 1 = RED
         * Road 2 = GREEN
         *
         * Duration = 3 seconds
         *
         * 7SEG:
         *
         * 3 -> 2 -> 1
         * ==========================================================
         */

        clearAllLEDs();

        HAL_GPIO_WritePin(GPIOA,
                          RED_1_Pin,
                          GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOA,
                          GREEN_2_Pin,
                          GPIO_PIN_RESET);

        countdown(3);



        /*
         * ==========================================================
         * PHASE 2
         *
         * Road 1 = RED
         * Road 2 = YELLOW
         *
         * Duration = 2 seconds
         *
         * 7SEG:
         *
         * 2 -> 1
         * ==========================================================
         */

        clearAllLEDs();

        HAL_GPIO_WritePin(GPIOA,
                          RED_1_Pin,
                          GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOA,
                          YELLOW_2_Pin,
                          GPIO_PIN_RESET);

        countdown(2);



        /*
         * ==========================================================
         * PHASE 3
         *
         * Road 1 = GREEN
         * Road 2 = RED
         *
         * Duration = 3 seconds
         *
         * 7SEG:
         *
         * 3 -> 2 -> 1
         * ==========================================================
         */

        clearAllLEDs();

        HAL_GPIO_WritePin(GPIOA,
                          GREEN_1_Pin,
                          GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOA,
                          RED_2_Pin,
                          GPIO_PIN_RESET);

        countdown(3);



        /*
         * ==========================================================
         * PHASE 4
         *
         * Road 1 = YELLOW
         * Road 2 = RED
         *
         * Duration = 2 seconds
         *
         * 7SEG:
         *
         * 2 -> 1
         * ==========================================================
         */

        clearAllLEDs();

        HAL_GPIO_WritePin(GPIOA,
                          YELLOW_1_Pin,
                          GPIO_PIN_RESET);

        HAL_GPIO_WritePin(GPIOA,
                          RED_2_Pin,
                          GPIO_PIN_RESET);

        countdown(2);


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
      * Initializes the RCC Oscillators according to
      * the specified parameters.
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
    __HAL_RCC_GPIOB_CLK_ENABLE();


    /*
     * Initial level:
     *
     * Turn OFF traffic lights.
     */
    HAL_GPIO_WritePin(GPIOA,
                      RED_1_Pin |
                      YELLOW_1_Pin |
                      GREEN_1_Pin |
                      RED_2_Pin |
                      YELLOW_2_Pin |
                      GREEN_2_Pin,
                      GPIO_PIN_SET);


    /*
     * Initial level:
     *
     * Turn OFF 7-segment.
     */
    HAL_GPIO_WritePin(GPIOB,
                      GPIO_PIN_0 |
                      GPIO_PIN_1 |
                      GPIO_PIN_2 |
                      GPIO_PIN_3 |
                      GPIO_PIN_4 |
                      GPIO_PIN_5 |
                      GPIO_PIN_6,
                      GPIO_PIN_SET);


    /*
     * Configure traffic-light pins.
     *
     * PA1 = RED_1
     * PA2 = YELLOW_1
     * PA3 = GREEN_1
     * PA4 = RED_2
     * PA5 = YELLOW_2
     * PA6 = GREEN_2
     */
    GPIO_InitStruct.Pin =
            RED_1_Pin |
            YELLOW_1_Pin |
            GREEN_1_Pin |
            RED_2_Pin |
            YELLOW_2_Pin |
            GREEN_2_Pin;


    GPIO_InitStruct.Mode =
            GPIO_MODE_OUTPUT_PP;


    GPIO_InitStruct.Pull =
            GPIO_NOPULL;


    GPIO_InitStruct.Speed =
            GPIO_SPEED_FREQ_LOW;


    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    /*
     * Configure PB0 -> PB6 for 7-segment.
     *
     * PB0 = a
     * PB1 = b
     * PB2 = c
     * PB3 = d
     * PB4 = e
     * PB5 = f
     * PB6 = g
     */
    GPIO_InitStruct.Pin =
            GPIO_PIN_0 |
            GPIO_PIN_1 |
            GPIO_PIN_2 |
            GPIO_PIN_3 |
            GPIO_PIN_4 |
            GPIO_PIN_5 |
            GPIO_PIN_6;


    GPIO_InitStruct.Mode =
            GPIO_MODE_OUTPUT_PP;


    GPIO_InitStruct.Pull =
            GPIO_NOPULL;


    GPIO_InitStruct.Speed =
            GPIO_SPEED_FREQ_LOW;


    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


/* USER CODE BEGIN 4 */

/* USER CODE END 4 */


/**
  * @brief This function is executed in case of error occurrence.
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
  * @brief Reports the name of the source file and
  * the source line number where assert_param error occurred.
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */

    /* User can add implementation here */

    /* USER CODE END 6 */
}

#endif /* USE_FULL_ASSERT */
