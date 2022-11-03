/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
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

//#define ns 92
//#define ns 64
#define ns 253

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 DAC_HandleTypeDef hdac;
DMA_HandleTypeDef hdma_dac1;

TIM_HandleTypeDef htim6;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM6_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
uint32_t Wave_LUT[ns] = {
		2048, 2189, 2329, 2469, 2606, 2740, 2872, 2999, 3122, 3240, 3352, 3457, 3556, 3648, 3733,
		3809, 3877, 3936, 3986, 4027, 4058, 4080, 4092, 4095, 4087, 4070, 4044, 4007, 3962, 3907,
		3844, 3772, 3691, 3603, 3508, 3405, 3296, 3181, 3061, 2936, 2806, 2673, 2537, 2399, 2259,
		2118, 1977, 1836, 1696, 1558, 1422, 1289, 1159, 1034, 914, 799, 690, 587, 492, 404,
		323, 251, 188, 133, 88, 51, 25, 8, 0, 3, 15, 37, 68, 109, 159,
		218, 286, 362, 447, 539, 638, 743, 855, 973, 1096, 1223, 1355, 1489, 1626, 1766,
		1906, 2047
						}; 			//200 muestras
 */

/*uint32_t Wave_LUT[ns] = {
		2048, 2251, 2453, 2651, 2843, 3027, 3201, 3364, 3513, 3648, 3767, 3870, 3953, 4018, 4064,
		4089, 4094, 4079, 4044, 3988, 3914, 3821, 3710, 3583, 3440, 3284, 3115, 2936, 2748, 2553,
		2353, 2150, 1945, 1742, 1542, 1347, 1159, 980, 811, 655, 512, 385, 274, 181, 107,
		51, 16, 1, 6, 31, 77, 142, 225, 328, 447, 582, 731, 894, 1068, 1252,
		1444, 1642, 1844, 2047
};64 muestras*/

/*uint32_t Wave_LUT[ns] = {
		2048, 2175, 2302, 2426, 2547, 2664, 2776, 2884, 2984, 3076, 3160, 3236, 3303, 3359, 3406,
		3443, 3468, 3485, 3490, 3485, 3470, 3446, 3413, 3370, 3320, 3263, 3200, 3130, 3056, 2977,
		2896, 2814, 2730, 2645, 2562, 2482, 2404, 2330, 2261, 2197, 2140, 2090, 2047, 2014, 1988,
		1972, 1965, 1967, 1980, 2002, 2032, 2073, 2122, 2180, 2245, 2318, 2398, 2483, 2574, 2668,
		2767, 2867, 2969, 3072, 3173, 3273, 3371, 3463, 3553, 3636, 3714, 3784, 3846, 3900, 3944,
		3979, 4003, 4018, 4022, 4014, 3997, 3968, 3929, 3880, 3820, 3752, 3675, 3590, 3497, 3398,
		3292, 3182, 3067, 2950, 2832, 2712, 2591, 2472, 2356, 2242, 2132, 2027, 1927, 1835, 1751,
		1673, 1604, 1544, 1494, 1453, 1421, 1401, 1390, 1388, 1397, 1414, 1440, 1475, 1518, 1568,
		1623, 1685, 1752, 1822, 1896, 1971, 2048, 2124, 2200, 2273, 2343, 2409, 2471, 2528, 2578,
		2620, 2655, 2681, 2699, 2707, 2706, 2695, 2673, 2643, 2602, 2551, 2491, 2422, 2345, 2259,
		2167, 2068, 1964, 1853, 1740, 1622, 1503, 1384, 1264, 1144, 1027, 914, 803, 698, 599,
		505, 420, 343, 274, 216, 166, 127, 99, 80, 74, 78, 91, 116, 151, 196,
		249, 311, 382, 458, 542, 631, 725, 822, 922, 1024, 1126, 1228, 1329, 1426, 1521,
		1611, 1698, 1777, 1850, 1916, 1973, 2022, 2062, 2094, 2116, 2127, 2131, 2123, 2107, 2082,
		2047, 2005, 1955, 1898, 1835, 1766, 1691, 1614, 1532, 1449, 1366, 1282, 1198, 1117, 1040,
		965, 896, 832, 774, 724, 683, 649, 625, 610, 606, 611, 626, 653, 690, 736,
		793, 859, 935, 1019, 1112, 1212, 1318, 1430, 1548, 1669, 1794, 1920, 2048
};253 muestras 2 freq en 10K y 50K*/

uint32_t Wave_LUT[ns] = {
		2049, 2270, 2487, 2690, 2875, 3038, 3174, 3279, 3353, 3393, 3402, 3379, 3329, 3253, 3158,
		3047, 2926, 2801, 2678, 2561, 2457, 2368, 2297, 2248, 2222, 2218, 2236, 2275, 2330, 2398,
		2476, 2558, 2639, 2716, 2780, 2831, 2864, 2877, 2864, 2828, 2770, 2688, 2587, 2469, 2340,
		2201, 2062, 1924, 1798, 1685, 1593, 1525, 1484, 1475, 1498, 1553, 1641, 1758, 1904, 2072,
		2257, 2456, 2662, 2867, 3067, 3254, 3424, 3572, 3692, 3781, 3840, 3865, 3859, 3822, 3756,
		3667, 3555, 3431, 3294, 3154, 3016, 2883, 2762, 2657, 2570, 2503, 2458, 2435, 2435, 2453,
		2488, 2534, 2590, 2649, 2708, 2759, 2800, 2825, 2832, 2817, 2779, 2715, 2628, 2519, 2388,
		2242, 2083, 1917, 1748, 1581, 1426, 1285, 1164, 1069, 1001, 964, 961, 991, 1054, 1148,
		1270, 1416, 1580, 1760, 1946, 2135, 2317, 2487, 2643, 2777, 2886, 2964, 3012, 3028, 3013,
		2969, 2897, 2802, 2686, 2556, 2417, 2274, 2133, 2000, 1877, 1770, 1683, 1616, 1572, 1548,
		1548, 1567, 1601, 1649, 1705, 1764, 1822, 1875, 1914, 1940, 1947, 1932, 1892, 1829, 1741,
		1632, 1502, 1355, 1196, 1030, 863, 698, 543, 405, 287, 194, 132, 99, 102, 138,
		208, 311, 442, 599, 774, 965, 1165, 1368, 1567, 1754, 1927, 2081, 2209, 2308, 2378,
		2418, 2426, 2407, 2360, 2291, 2203, 2100, 1988, 1874, 1761, 1657, 1563, 1486, 1426, 1389,
		1373, 1379, 1406, 1454, 1516, 1589, 1673, 1758, 1842, 1918, 1983, 2031, 2061, 2068, 2050,
		2007, 1940, 1849, 1738, 1610, 1469, 1319, 1168, 1020, 881, 758, 655, 578, 529, 513,
		529, 581, 665, 783, 929, 1101, 1292, 1499, 1714, 1932, 2147, 2352, 2541
};	//3 componentes en 10K 50K 100K

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

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_DAC_Init();
  MX_TIM6_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Base_Start(&htim6);
  HAL_DAC_Start_DMA(&hdac, DAC_CHANNEL_1, (uint32_t*)Wave_LUT, ns, DAC_ALIGN_12B_R);


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 64;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_T6_TRGO;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 8;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
