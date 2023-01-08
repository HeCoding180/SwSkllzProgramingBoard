#include "SwissSkillsProgrammingBoard.h"

SwissSkillsProgrammingBoard::SwissSkillsProgrammingBoard()
{
    //Ultrasonic sensor init
    IOREGD->DDR |= 0x80;
    IOREGD->PORT &= 0x7F;

    SwissSkillsProgrammingBoard::lcdDisplay = new LiquidCrystal(11, 10, 12, 2, 3, 4, 5, 6, 7, 8, 9);
}

//LED Functions
void SwissSkillsProgrammingBoard::EnableLED_PortBit(uint8_t num)
{
    LED_IOReg->DDR &= ~PIN_MASK(num);
}
void SwissSkillsProgrammingBoard::DisableLED_PortBit(uint8_t num)
{
    uint8_t mask = PIN_MASK(num);
    LED_IOReg->DDR &= ~mask;
    LED_IOReg->PORT &= ~mask;
}
void SwissSkillsProgrammingBoard::SetLED_PortEnable(uint8_t mask)
{
    LED_IOReg->DDR = mask;
    LED_IOReg->PORT &= ~mask;
}
void SwissSkillsProgrammingBoard::SetLED(uint8_t num, bool value)
{
    LED_IOReg->PORT = (LED_IOReg->PORT & ~PIN_MASK(num)) | ((value ? 0x01 : 0x00) << (num - 1));
}
uint8_t SwissSkillsProgrammingBoard::GetLED(uint8_t num)
{
    return (LED_IOReg->PORT & PIN_MASK(num)) ? 0x01 : 0x00;
}
void SwissSkillsProgrammingBoard::ToggleLED(uint8_t num)
{
    LED_IOReg->PORT ^= PIN_MASK(num);
}
void SwissSkillsProgrammingBoard::ToggleLEDs(uint8_t mask)
{
    LED_IOReg->PORT ^= mask;
}
//Button Functions
uint8_t SwissSkillsProgrammingBoard::GetButtonState(uint8_t num)
{
    return (Button_IOReg->PIN & PIN_MASK(num)) ? 0x01 : 0x00;
}
uint8_t SwissSkillsProgrammingBoard::GetButtonStates()
{
    return Button_IOReg->PIN;
}
//EXT_GPIO Functions
void SwissSkillsProgrammingBoard::SetExtGPIO_Dir(uint8_t num, bool value)
{
    if (num > 1)
    {
        uint8_t mask = 0x80 >> (num - 2);
        IOREGL->DDR = (IOREGL->DDR & ~mask) | (value ? mask : 0x00);
    }
    else
    {
        uint8_t mask = 0x02 >> num;
        IOREGG->DDR = (IOREGG->DDR & ~mask) | (value ? mask : 0x00);
    }
}
void SwissSkillsProgrammingBoard::SetExtGPIO_Dirs(uint8_t mask)
{
    uint8_t maskReversed = REVERSE_BITORDER(mask);
    IOREGG->DDR = (IOREGG->DDR & 0xFC) | ((maskReversed >> 6) & 0x03);
    IOREGL->DDR = (IOREGL->DDR & 0x03) | ((maskReversed << 2) & 0xFC);
}
void SwissSkillsProgrammingBoard::SetExtGPIO_Pullup(uint8_t num, bool value)
{
    if (num > 1)
    {
        uint8_t mask = 0x80 >> (num - 2);
        IOREGL->PORT = (IOREGL->PORT & ~mask) | (value ? mask : 0x00);
    }
    else
    {
        uint8_t mask = 0x02 >> num;
        IOREGG->PORT = (IOREGG->PORT & ~mask) | (value ? mask : 0x00);
    }
}
void SwissSkillsProgrammingBoard::SetExtGPIO_Pullups(uint8_t mask)
{
    uint8_t maskReversed = REVERSE_BITORDER(mask);
    IOREGG->PORT = (IOREGG->PORT & 0xFC) | ((maskReversed >> 6) & 0x03);
    IOREGL->PORT = (IOREGL->PORT & 0x03) | ((maskReversed << 2) & 0xFC);
}
void SwissSkillsProgrammingBoard::SetExtGPIO(uint8_t num, bool value)
{
    if (num > 1)
    {
        uint8_t mask = 0x80 >> (num - 2);
        IOREGL->PORT = (IOREGL->PORT & ~mask) | (value ? mask : 0x00);
    }
    else
    {
        uint8_t mask = 0x02 >> num;
        IOREGG->PORT = (IOREGG->PORT & ~mask) | (value ? mask : 0x00);
    }
}
void SwissSkillsProgrammingBoard::SetExtGPIOs(uint8_t mask)
{
    uint8_t maskReversed = REVERSE_BITORDER(mask);
    IOREGG->PORT = (IOREGG->PORT & 0xFC) | ((maskReversed >> 6) & 0x03);
    IOREGL->PORT = (IOREGL->PORT & 0x03) | ((maskReversed << 2) & 0xFC);
}
uint8_t SwissSkillsProgrammingBoard::GetExtGPIO(uint8_t num)
{
    if (num > 1)
    {
        uint8_t mask = (0x80 >> (num - 2));
        return (((IOREGL->PORT & mask) == mask) ? 0x01 : 0x00);
    }
    else
    {
        uint8_t mask = 0x02 >> num;
        return (((IOREGG->PORT & mask) == mask) ? 0x01 : 0x00);
    }
}
uint8_t SwissSkillsProgrammingBoard::GetExtGPIOs()
{
    return REVERSE_BITORDER(((IOREGG->PORT << 6) & 0x03) | ((IOREGL->PORT >> 2) & 0xFC));
}
//Display

//Ultrasonic
uint16_t SwissSkillsProgrammingBoard::GetUltrasonicDistance()
{
    TIM1->TCNT = 0x0000;
    //Generate trigger pulse
    IOREGD->PORT |= 0x80;
    delayMicroseconds(11);
    IOREGD->PORT &= 0x7F;

    //wait for echo signal
    while ((IOREGG->PIN & 0x04) != 0x04);
    TIM1->TCCR.CS = 4;
    while ((IOREGG->PIN & 0x04) == 0x04);
    TIM1->TCCR.CS = 0;
    return floor(((double)(TIM1->TCNT))/0.42 + 0.5);
}
