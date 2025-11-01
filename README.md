# 8 by 2 LCD library for ADM0802A module

[Datasheet and register map](https://cdn.sparkfun.com/datasheets/LCD/Monochrome/ADM0802A-FSY-YBS-3.3V.pdf) used to develop this library. 

Current version: 1.2.1

### Framework support
This library only supports STM32 MCUs, with default support for the F3 line of MCUs. If not using an F3, simply change the included file in line 20 of ADM0802A.h to your desired hal file.

`#include "stm32f3xx_hal.h"`

### Disclaimer and current downsides
A current major downside to the setup of the library is that the output pins that the module has to connect to is hardcoded. A major update in the future will resolve that issue, which is discussed in further detail in the issues and updates section.

### Command shortcuts
Includes command shortcuts to facilitate the use of this library. Simpler examples include `ADM0802A_COMMAND_CLEAR_DISPLAY`, while more complex shortcuts require the setting of certain bits to perform a specified option, like `ADM0802A_COMMAND_DISPLAY_CONTROL(D, C, B)`, where parameter D sets the bit to control the entire display, C sets the bit to display the cursor, and B sets the bit to display cursor blinking.

### Library functions
There are currently only three functions: 
- `void ADM0802A_Init ()` 
- `void ADM0802A_CommandWrite (uint8_t command)`
- `void ADM0802A_DataWrite (char character, bool upper_set)`

The init function sends default parameter commands to the module, like turning on display, enabling cursor, enabling blink, and so on. The CommandWrite and DataWrite commands were developed under the rudimentary idea that users of this library will only send a single command, and a single character at a time. Updates for these functions will be discussed in the next section.

### Issues and updates
There are a few issues currently plaging this library. Firstly, the pins that the device needs to connect to are hardcoded, making it difficult to integrate in projects where multiple different modules are used, and difficult to use in non STM32F3 MCUs. 

Another issue is the lack of beginner friendly command shortcuts. The current command shortcuts were designed to encapsulate an entire command, meaning that individual bits that change entirely different settings are combined with other bits that are under the same command. For example, to change the display, cursor, and cursor blinking, the same command shortcut is used, which could make development troublesome. 

Another issue is the apparent lack of higher level functions that can work with strings or can accept multiple commands at once. 

To address all these issues, the list below maps out the direction and updates that will library will take. 

- ~~Update repo to only include library header and source files, along with a simple example file to showcase how the library works.~~
- The init function will have a list of parameters to keep track of which pins in the MCU the module will connect to.
    - The hardcoded pins will then become default pins
    - Helper functions will update the MCU pin that connects to a specific pin in the module. 
- Alongside command shortcuts, helper functions will be able to change a specific setting without having to invoke the entire command and set all its individual bits.
- A more complex data write function will be able to work with strings.

