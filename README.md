# freertos-posix-sensor-logger

A multitasking sensor data logger system simulated on macOS using the FreeRTOS POSIX port.  
This project demonstrates core embedded systems concepts such as task scheduling, inter-task communication, and structured logging — all without requiring physical microcontroller hardware.

---

## Features

- Simulates multiple periodic sensor tasks (temperature, humidity)
- Logger task aggregates and logs data to a csv file
- Uses FreeRTOS queues for safe inter-task communication
- Tasks run with different priorities and intervals
- Modular and scalable architecture for real-world embedded systems

---

## 🧱 System Architecture

```plaintext
+-------------------+      +-------------------+
|  Temp task        | ---> |                   |
|                   |      |                   |
+-------------------+      |                   |
                           |                   |
+-------------------+      |   Message Queue   | ---> Logger Task
|  Humidity task    | ---> |   (FreeRTOS)      |      (every N ms)
|                   |      |                   |
+-------------------+      |                   |
                           |                   |
                           +-------------------+
```

## How to build and run

Requirements:

- macOS or Linux
- GCC or Clang
- Make

Commands:

mkdir build && cd build
cmake ..
make
./freertos_sim

## Key Concepts Demonstrated

- Real-time task management
- Periodic task scheduling (vTaskDelayUntil)
- Inter-task communication via xQueueSend() / xQueueReceive()
- Modular architecture design
- Simulated embedded development without MCU

