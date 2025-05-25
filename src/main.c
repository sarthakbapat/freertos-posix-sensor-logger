#include "Sensor.h"

extern QueueHandle_t sensorDataSharedQueue; 

int main(void) {

    BaseType_t xTempTaskReturn, xLoggerTaskReturn;
    TaskHandle_t tempTaskHandle = NULL;
    TaskHandle_t loggerTaskHandle = NULL;

    TaskParams temperatureParams;
    temperatureParams.minValue = 0;
    temperatureParams.maxValue = 55;

    xTempTaskReturn = xTaskCreate(temperature_task, "Task1-Temperature", configMINIMAL_STACK_SIZE, &temperatureParams, 2, &tempTaskHandle);
    
    if (xTempTaskReturn == pdPASS)
    {
        printf("Temperature task created successfully.\n");
    }
    else
    {
        printf("Failed to create temperature task.\n");
        while(1);   // Trap here.
    }

    xLoggerTaskReturn = xTaskCreate(logger_task, "Task3-Logger", configMINIMAL_STACK_SIZE, NULL, 1, &loggerTaskHandle);

    if (xLoggerTaskReturn == pdPASS)
    {
        printf("Logger task created successfully.\n");
    }
    else
    {
        printf("Failed to create logger task.\n");
        while(1);   // Trap here.
    }
    printf("SizeOf SensorData*: %lu\n", sizeof(SensorData*));
    printf("SizeOf SensorData: %lu\n", sizeof(SensorData));
    sensorDataSharedQueue = xQueueCreate(10, sizeof(SensorData));
    
    vTaskStartScheduler();
    for (;;); // Should never reach here
    return 0;
}
