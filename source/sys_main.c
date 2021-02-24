#include "sys_common.h"
#include "system.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "os_task.h"
#include "os_timer.h"
#include "os_queue.h"
#include "os_semphr.h"
#include "os_list.h"

#include "gio.h"


/* Define Task Handles */
xTaskHandle xTask1Handle,
            xTask2Handle;

xTimerHandle xTimer1;
uint32 i = 0;


void vTimerFunction(xTimerHandle xTimer1)
{
    // toggle port bits
    i++;;
    // restart timer
    //xTimerReset(xTimer1, 0);
    //xTimerStop( xTimer1 ,0 );
}


void vTaskALL(void *pvParameters)
{
    for(;;)
    {

        vTaskDelay(10);
    }
}

void main(void)
{
/* USER CODE BEGIN (3) */

    gioInit();
    /* Create Task 1 */
    xTaskCreate(vTaskALL, "TaskALL", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, &xTask1Handle);

    xTimer1 = xTimerCreate("Timer1", 500, pdTRUE, (void*) 0, vTimerFunction);
    xTimerStart( xTimer1, 0 );

    /* Start Scheduler */
    vTaskStartScheduler();

    /* Run forever */
    while(1);
/* USER CODE END */
}
