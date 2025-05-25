cmake_minimum_required(VERSION 3.19)
project(FreeRTOS_POSIX_Sim C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_COMPILER "gcc")

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/FreeRTOS-kernel/include
    ${CMAKE_SOURCE_DIR}/FreeRTOS-kernel/portable/ThirdParty/GCC/Posix
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}
)

# Source files
set(SRC
    src/main.c
    src/Sensor.c
    inc/Sensor.h
    FreeRTOS-kernel/tasks.c
    FreeRTOS-kernel/list.c
    FreeRTOS-kernel/queue.c
    FreeRTOS-kernel/timers.c
    FreeRTOS-kernel/event_groups.c
    FreeRTOS-kernel/portable/MemMang/heap_4.c
    FreeRTOS-kernel/portable/ThirdParty/GCC/Posix/port.c
    FreeRTOS-kernel/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
)

add_executable(freertos_sim ${SRC})

# Link POSIX threads (required)
target_link_libraries(freertos_sim pthread)
