#include "Sensor.h"

extern QueueHandle_t sensorDataSharedQueue; 

int main(void) {
    // Create the taskHandles and task return variables.
    BaseType_t xTempTaskReturn, xLoggerTaskReturn, xHumidityTaskReturn;
    TaskHandle_t tempTaskHandle = NULL;
    TaskHandle_t loggerTaskHandle = NULL;
    TaskHandle_t humidityTaskHandle = NULL;

    // Set the temperature range to be generated as param to the temp task.
    TaskParams temperatureParams;
    temperatureParams.minValue = 0;
    temperatureParams.maxValue = 55;

    // Set the humidity range to be generated as a param to the humidity task.
    TaskParams humidityParams;
    humidityParams.minValue = 0;
    humidityParams.maxValue = 100;

    // Create the temperature task.
    xTempTaskReturn = xTaskCreate(temperature_task, "Task1-Temperature", configMINIMAL_STACK_SIZE, &temperatureParams, 2, &tempTaskHandle);
    
    if (xTempTaskReturn == pdPASS)
    {
        printf("Temperature task created successfully.\n");
    }
    else
    {
        printf("Failed to create temperature task.\n");
        while(1);   // Trap here if failed.
    }

    // Create the logger task.
    xLoggerTaskReturn = xTaskCreate(logger_task, "Task3-Logger", configMINIMAL_STACK_SIZE, NULL, 1, &loggerTaskHandle);

    if (xLoggerTaskReturn == pdPASS)
    {
        printf("Logger task created successfully.\n");
    }
    else
    {
        printf("Failed to create logger task.\n");
        while(1);   // Trap here if failed.
    }
    
    // Create the humidity task.
    xHumidityTaskReturn = xTaskCreate(humidity_task, "Task2-Humidity", configMINIMAL_STACK_SIZE, &humidityParams, 2, &humidityTaskHandle);

    if (xHumidityTaskReturn == pdPASS)
    {
        printf("Humidity task created successfully.\n");
    }
    else
    {
        printf("Failed to create Humidity task.\n");
        while(1);   // Trap here if failed.
    }

    // Create a queue to be shared between different tasks. Size = 10.
    sensorDataSharedQueue = xQueueCreate(10, sizeof(SensorData));
    
    vTaskStartScheduler();
    for (;;); // Should never reach here
    return 0;
}
