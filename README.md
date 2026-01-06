# UART with DMA
-   Using UART2 send data to UART5 with DMA on RX PIN
-   Using UART3 as debugger

## Setup
-   Transmission between UART5 and UART2
    - UART5 Tx pin PC12
    - UART5 Rx pin PB12
    - UART2 Tx pin PD5
    - UART2 Rx pin PA3
-   DMA Settings
    - Enable on uart5 Rx pin
    - Mode: Normal or Circular (see below for detail)
-   NVIC Settings
    - DMA global interrupt: Enable
    - uart global interrupt: Enable

## Ex1. UART DMA with IDLE line interrupt feature
### use case (https://controllerstech.com/stm32-uart-5-receive-data-using-idle-line/)
-   When it has sent the entire message and then stops completely. (Normal buffer is fitted for this)
-   When large data is transmitted in multiple chunks, with a brief delay between each chunk. (Circular buffer is suitable for this)

###  Usage
-   Send data with uart2 using `HAL_UART_Transmit`
-   Receive data with uart5
    - `HAL_UARTEx_ReceiveToIdle_DMA` -  
    - `HAL_UARTEx_RxEventCallback` - called when MAX-buff is reached or **IDLE Line** (wait time that no data coming) is detected before that.
        - Normal Buffer - `HAL_UARTEx_ReceiveToIdle_DMA` need to call again to listen new data.
        - Circular Buffer - Never stop listening (no need to call `HAL_UARTEx_ReceiveToIdle_DMA` again)
    - `HAL_UART_ErrorCallback` - Error handling


<!-- ## Ex2. UART DMA Normal mode
### use case (https://controllerstech.com/stm32-uart-4-receive-data-using-dma/)
-   The incoming data has a known size
-   You’re expecting the full buffer to fill once
-   You can afford to pause data reception while processing

## Ex3. UART DMA Circular mode -->


## Ref
-   STM32World
-   https://controllerstech.com/