#include "Sensor.h"
#include "queue.h"

extern QueueHandle_t sensorDataSharedQueue; 

static uint8_t _generate_data(uint8_t min, uint8_t max);
static void _get_readable_timestamp(const time_t, char*);


void temperature_task(void* params)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 100;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    // Typecast the params to TaskParams to extract the params.
    TaskParams* taskParams = (TaskParams*)params;
    uint8_t sensorData = 0;
    SensorData dataToQueue;

    time_t now;

    while(1) {
        // Generate the simulated sensor values and write them to the structure to send to the shared queue.
        sensorData = _generate_data(taskParams->minValue, taskParams->maxValue);

        dataToQueue.sensorReading = sensorData;
        dataToQueue.sensor = TEMPERATURE_SENSOR;
        now = time(NULL);
        dataToQueue.timeStamp = now;

        // Call the queue API to send the sensor data to the end of the queue.
        if (xQueueSendToBack(sensorDataSharedQueue, (void*)&dataToQueue, ( TickType_t )0) != pdPASS)
        {
            printf("Failed to add the data to queue in temperature task.\n");
        }
        else
        {
            printf("Added temperature data to queue successfully.\n");
        }

        // Call the task delay API to make this task periodic.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
    
}

void humidity_task(void* params)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 100;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    // Typecast the params to TaskParams to extract the params.
    TaskParams* taskParams = (TaskParams*)params;
    uint8_t sensorData = 0;
    SensorData dataToQueue;

    time_t now;

    while(1) {
        // Generate the simulated sensor values and write them to the structure to send to the shared queue.
        sensorData = _generate_data(taskParams->minValue, taskParams->maxValue);

        dataToQueue.sensorReading = sensorData;
        dataToQueue.sensor = HUMIDITY_SENSOR;
        now = time(NULL);
        dataToQueue.timeStamp = now;

        // Call the queue API to send the sensor data to the end of the queue.
        if (xQueueSendToBack(sensorDataSharedQueue, (void*)&dataToQueue, ( TickType_t )0) != pdPASS)
        {
            printf("Failed to add the data to queue in humidity task.\n");
        }
        else
        {
            printf("Added humidity data to queue successfully.\n");
        }

        // Call the task delay until API to make this task periodic.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void logger_task(void* params)
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 50;
    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    // Create a local instance to SensorData to receive the data from queue.
    SensorData receivedSensorData;
    memset(&receivedSensorData, 0, sizeof(SensorData));

    // Initialize the file here.
    FILE *ptr = NULL;
    ptr = log_init();

    while (1)
    {
        // Receive from the queue here and write the contents to the file.
        if (xQueueReceive(sensorDataSharedQueue, &receivedSensorData, ( TickType_t )0) == pdPASS)
        {
            printf("Sensor data received from the queue successfully\n");
            // log the data to the csv file.
            log_data(&ptr, &receivedSensorData);
        }
        else
        {
            printf("Failed to read the data successfully from the queue\n");
        }

        // Call the task delay API to make this task periodic.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

// Init function for CSV logger file.
FILE* log_init()
{
    FILE* fptr;
    fptr = fopen("../sensor_readings.csv", "w");
    fprintf(fptr, "SensorID, SensorData, TimeStamp\n");
    fclose(fptr);

    return fptr;
}

// Function to write data to the file.
void log_data(FILE** fptr, SensorData* data)
{
    // Open the file in read+append mode (a+)
    *fptr = fopen("../sensor_readings.csv", "a+");
    // Create a buffer to get the timestamp in readable state.
    char buffer[20];
    _get_readable_timestamp(data->timeStamp, buffer);
    
    // Write the sensorid, sensorreading and readable timestamp obtained in buffer to the file.
    fprintf(*fptr, "%d, %d, %s\n", data->sensor, data->sensorReading, buffer);
    fclose(*fptr);
}

// Helper function to get a readable timestamp in the buffer.
static void _get_readable_timestamp(const time_t time, char* buff)
{
    // Convert the timestamp in %Y-%m-&d %H:%m:%S format and copy to buff.
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&time));
}

// Helper function to generate random values in a given range.
static uint8_t _generate_data(uint8_t min, uint8_t max)
{
    return (rand() % (max - min + 1)) + min;
}