#ifndef SWISSSKILLS_PROGRAMMING_BOARD_DEFINED
#define SWISSSKILLS_PROGRAMMING_BOARD_DEFINED

#include <Arduino.h>
#include <inttypes.h>
#include <LiquidCrystal.h>
#include <math.h>

#include "ATMEGA2560.h"

//Defines
#define LED_IOReg     (IOREGA)
#define Button_IOReg  (IOREGC)

//Macros
#define PIN_MASK(p) (0x01 << ((p) - 1))
#define REVERSE_BITORDER(b) ((((b) & 0x01) << 7) | (((b) & 0x02) << 5) | (((b) & 0x04) << 3) | (((b) & 0x08) << 1) | (((b) & 0x10) >> 1) | (((b) & 0x20) >> 3) | (((b) & 0x40) >> 5) | (((b) & 0x80) >> 7))
#define BINARY_TO_VOLTAGE(a) (5.0 * (a) / 1023.0)

class SwissSkillsProgrammingBoard
{
    public:
        SwissSkillsProgrammingBoard();
        //LED Functions
        void EnableLED_PortBit(uint8_t);
        void DisableLED_PortBit(uint8_t);
        void SetLED_PortEnable(uint8_t);
        void SetLED(uint8_t, bool);
        uint8_t GetLED(uint8_t);
        void ToggleLED(uint8_t);
        void ToggleLEDs(uint8_t);
        //Button Functions
        uint8_t GetButtonState(uint8_t);
        uint8_t GetButtonStates();
        //EXT_GPIO Functions
        void SetExtGPIO_Dir(uint8_t, bool);
        void SetExtGPIO_Dirs(uint8_t);
        void SetExtGPIO_Pullup(uint8_t, bool);
        void SetExtGPIO_Pullups(uint8_t);
        void SetExtGPIO(uint8_t, bool);
        void SetExtGPIOs(uint8_t);
        uint8_t GetExtGPIO(uint8_t);
        uint8_t GetExtGPIOs();
        //Display
        LiquidCrystal* lcdDisplay;
        //Ultrasonic
        uint16_t GetUltrasonicDistance();
};

#endif
