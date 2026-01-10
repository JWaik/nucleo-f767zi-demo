# PWM
### PWM Frequency
-   tell how many times the signal completes a full cycle in one second.
-   In PWM, ARR sets the total number of clock cycles for one full period, while the Capture/Compare Register (CCR) sets the pulse width. 

$$
f_{pwm} =  \frac{f_{timer}}{(PSC+1)(ARR+1)}
$$

-   Where
    - $f_{timer}$ - Timer clock
    - $PSC$ - Clock Prescaler
    - $ARR$ - 
        - the timer's period or frequency by setting **the maximum count value**;
        - the timer counter (CNT) counts up to this value, then resets to zero (or reloads).

### Duty cycles
-   defines the percentage of ON-time in each cycle.
$$
D\% =  \frac{CCR}{ARR+1} \times 100
$$
-   Where
    - $CCR$ Capture/Compare Register the output pin changes state (e.g., goes low) when the CNT reaches the CCR value.

> More information about register can be found in Reference Manual.

> How to design $f_{pwm}$? It's depended on application.
> Motor control need to be fast enough to prevent torque ripple.
> In **Ardupilot** the frequency is around 50Hz to 490Hz.

## STM32CubeMX Setup
### Timer Setting
-   **Clock Source**: Internal clock
    - sets the timer to use the internal APB2 clock as its source for generating precise time-based signals like PWM without relying on external clocks.
-   **Channel1**: PWM Generation CH1

### Counter Settings
-   **Prescaler**: 96-1 (We need 96MHz after prescaling, Our APB2 is 96MHz by default)
-   **Counter Mode**: Up (count from 0 to **ARR**)
-   **Counter Period (ARR)**: 2000-1 (In register,from reference manual, it's automatically add +1, why 2000? See below)

> Standard servo require $f_{pwm} = 50 Hz$ (max width = 20 ms).\
> We need 1 ${\mu}{s}$ resolution, so $f_{timer}/Prescaler$ must be $1MHz$. -> Prescaler = 96\
> With 1 ${\mu}{s}$ resolution, ARR count must set to $ARR+1 = 1MHz/50Hz = 20000$ (1 CCR = 1 ${\mu}{s}$)\
> We need pulse time in range 1000-2000 ${\mu}{s}$. So set CCR from 1000-2000


### PWM Generation Settings
-   **Mode**: 1
    - Output is HIGH when counter less than the pulse value.
    - Output is LOW when the counter is greater than or equal to the pulse value.
-   **Pulse (CCR1)**: 0
    - Initial duty cycle
    - The output will stay LOW until this value is changed in code.

### Pin mapping 
-   PE9 (STM32F767)

### PWM DMA Configuration
-   Direction: Memory to Peripheral (fetched from memory and written into the Timer’s Capture/Compare register (CCR).)
-   Data width: Half-word If pulse width values fit within 16 bits, using Half Word is the most efficient choice. (we need to write CCR register for calculating Duty Cycle, CCR <= ARR)

#### PWM DMA Modes
-   Normal Mode: transfers the data from memory to the Timer only once ('til last element of array).
    - you need to restart the DMA manually.
-   Circular Mode: automatically loops back and starts again from the beginning.


## Problems from testing (Especially circular mode)
> PWM not stay low after end of DMA(just pulled down? Need oscilloscope to verify that, Logic analyzer is not accurate enough).\
> Related issue from commuity. https://community.st.com/t5/stm32-mcus-products/configuring-idle-state-for-timers/td-p/237783/page/2\

## Ref code
-   https://controllerstech.com/pwm-in-stm32/