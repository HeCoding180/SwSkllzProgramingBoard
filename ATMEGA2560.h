/**
 * @file ATMEGA2560.h
 * @author HeCoding180
 * @brief Header file containing required register defines for the SwissSkillsProgrammingBoard header and c++ file 
 *        according to https://ww1.microchip.com/downloads/en/devicedoc/atmel-2549-8-bit-avr-microcontroller-atmega640-1280-1281-2560-2561_datasheet.pdf
 * @version 0.1
 * @date 2023-01-07
 */

#include <inttypes.h>

//   ---   Typedefs   ---
// IO Register Typedefs
typedef volatile struct                 // IO Registers
{
    uint8_t PIN;                        // Input Pins Address (Holds synchronized digital signal level of the input pins, readonly)
    uint8_t DDR;                        // Data Direction Register
    uint8_t PORT;                       // Data Register (Used to set the digital output signal levels or pull-up resistors if set as digital input)
} IOREG_t;
// Timer Register Typedefs
#pragma pack(1)
typedef volatile struct                 // 16 bit Timer Registers
{
    struct                              // Timer/Counter Control Registers
    {
        union                           // Timer/Counter Control Register A
        {
            uint8_t TCCRnA;
            struct
            {
                uint8_t WGMa        :2; // Waveform Generator Mode [0:1]
                uint8_t COMnC       :2; // Compare Output Mode for Channel C
                uint8_t COMnB       :2; // Compare Output Mode for Channel B
                uint8_t COMnA       :2; // Compare Output Mode for Channel A
            };
        };
        union                           // Timer/Counter Control Register B
        {
            uint8_t TCCRnB;
            struct
            {
                uint8_t CS          :3; // Clock Select
                uint8_t WGMb        :2; // Waveform Generator Mode [2:3]
                uint8_t             :1; // [reserved bit]
                uint8_t ICES        :1; // Input Capture Edge Select
                uint8_t ICNC        :1; // Input Capture Noise Canceler
            };
        };
        union                           // Timer/Counter Control Register C
        {
            uint8_t TCCRnC;
            struct
            {
                uint8_t             :5; // [reserved bits]
                uint8_t FOCnC       :1; // Force Output Compare for Channel C
                uint8_t FOCnB       :1; // Force Output Compare for Channel B
                uint8_t FOCnA       :1; // Force Output Compare for Channel A
            };
        };
    } TCCR;
    uint8_t Reserved;
    union                               // Timer/Counter
    {
        uint16_t TCNT;
        struct
        {
            uint8_t TCNTnL;             // Timer/Counter Low Byte
            uint8_t TCNTnH;             // Timer/Counter High Byte
        };
    };
    union                               // Input Capture Register
    {
        uint16_t ICR;
        struct
        {
            uint8_t ICRnL;              // Input Capture Register Low Byte
            uint8_t ICRnH;              // Input Capture Register High Byte
        };
    };
    union                               // Output Compare Register A
    {
        uint16_t OCRnA;
        struct
        {
            uint8_t OCRnAL;              // Output Compare Register A Low Byte
            uint8_t OCRnAH;              // Output Compare Register A High Byte
        };
    };
    union                               // Output Compare Register B
    {
        uint16_t OCRnB;
        struct
        {
            uint8_t OCRnBL;              // Output Compare Register B Low Byte
            uint8_t OCRnBH;              // Output Compare Register B High Byte
        };
    };
    union                               // Output Compare Register C
    {
        uint16_t OCRnC;
        struct
        {
            uint8_t OCRnCL;              // Output Compare Register C Low Byte
            uint8_t OCRnCH;              // Output Compare Register C High Byte
        };
    };
} TIM16_t;
typedef volatile union                  // Timer/Counter Interrupt Mask Register
{
    uint8_t TIMSK;
    struct
    {
        uint8_t TOIE                :1; // Timer/Counter Overflow Interrupt Enable
        uint8_t OCIEnA              :1; // Timer/Counter Output Compare A Match Interrupt Enable
        uint8_t OCIEnB              :1; // Timer/Counter Output Compare B Match Interrupt Enable
        uint8_t OCIEnC              :1; // Timer/Counter Output Compare C Match Interrupt Enable
        uint8_t                     :1; // [reserved bit]
        uint8_t ICIE                :1; // Timer/Counter Input Capture Interrupt Enable
        uint8_t                     :2; // [reserved bits]
    };
} TIMSK16_t;
typedef volatile union                  // Timer/Counter Interrupt Flag Register
{
    uint8_t TIFR;
    struct
    {
        uint8_t TOV                 :1; // Timer/Counter Overflow Flag
        uint8_t OCFnA               :1; // Timer/Counter Output Compare A Match Flag
        uint8_t OCFnB               :1; // Timer/Counter Output Compare B Match Flag
        uint8_t OCFnC               :1; // Timer/Counter Output Compare C Match Flag
        uint8_t                     :1; // [reserved bit]
        uint8_t ICF                 :1; // Timer/Counter Input Capture Flag
        uint8_t                     :2; // [reserved bits]
    };
} TIFR16_t;
// ADC Register Typedefs


//   ---   Register Defines   ---
//      Name             Datatype           Address
// IO Register Defines
#define IOREGA          ((IOREG_t *)        (0x0020))
#define IOREGB          ((IOREG_t *)        (0x0023))
#define IOREGC          ((IOREG_t *)        (0x0026))
#define IOREGD          ((IOREG_t *)        (0x0029))
#define IOREGE          ((IOREG_t *)        (0x002C))
#define IOREGF          ((IOREG_t *)        (0x002F))
#define IOREGG          ((IOREG_t *)        (0x0032))
#define IOREGH          ((IOREG_t *)        (0x0100))
#define IOREGJ          ((IOREG_t *)        (0x0103))
#define IOREGK          ((IOREG_t *)        (0x0106))
#define IOREGL          ((IOREG_t *)        (0x0109))
// Timer Register Defines
#define TIM1            ((TIM16_t *)        (0x0080))
#define TIM3            ((TIM16_t *)        (0x0090))
#define TIM4            ((TIM16_t *)        (0x00A0))
#define TIM5            ((TIM16_t *)        (0x0120))
#define TIMSK1          ((TIMSK16_t *)      (0x006F))
#define TIMSK3          ((TIMSK16_t *)      (0x0071))
#define TIMSK4          ((TIMSK16_t *)      (0x0072))
#define TIMSK5          ((TIMSK16_t *)      (0x0073))
#define TIFR1           ((TIFR16_t *)       (0x0036))
#define TIFR3           ((TIFR16_t *)       (0x0038))
#define TIFR4           ((TIFR16_t *)       (0x0039))
#define TIFR5           ((TIFR16_t *)       (0x003A))
// ADC Register Defines

