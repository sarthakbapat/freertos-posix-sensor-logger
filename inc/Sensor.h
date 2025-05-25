#ifndef SENSOR_H
#define SENSOR_H

#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

QueueHandle_t sensorDataSharedQueue; 

typedef enum SensorType{
    TEMPERATURE_SENSOR,
    HUMIDITY_SENSOR
}SensorType;

// Struct to write the data to the queue.
typedef struct SensorData {
    uint8_t sensorReading;
    SensorType sensor;
    time_t timeStamp;
}SensorData;

// Structure to pass in 2 params to the task func. Min and Max for random data generation.
typedef struct TaskParams {
    uint8_t minValue;
    uint8_t maxValue;
}TaskParams;

/* ------ Methods for sensor tasks --------- */

void temperature_task(void*);

void humidity_task(void*);

void logger_task(void*);

/* ------------------------------------------ */

/* ------- Methods for logging data to file -------------- */

FILE* log_init(void);

void log_data(FILE**, SensorData*);

/* ------------------------------------------------------- */

#endif