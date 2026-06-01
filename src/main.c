/*---------------------------------------------------------------------------------------------------------*/
/*  50 Channel LED Controller using 74HC595 Shift Registers                                                */
/*  Microcontroller: N76E003 (SDCC Compatible)                                                             */
/*  All previous errors fixed                                                                              */
/*---------------------------------------------------------------------------------------------------------*/

#include "N76E003.h"
#include "SFR_Macro.h"
#include "Function_define.h"
#include "Common.h"
#include "Delay.h"

/* ==================== PIN DEFINITIONS ==================== */
#define DATA_PIN    P10
#define CLK_PIN     P11
#define LATCH_PIN   P12

#define NUM_SHIFT_REGS  7

/* ==================== GLOBAL VARIABLES ==================== */
uint8_t ledState[NUM_SHIFT_REGS];

/* ==================== FUNCTION PROTOTYPES ==================== */
void Setup(void);
void Loop(void);
void ShiftOutAll(void);
void SetLED(uint8_t led_number, uint8_t state);
void AllLEDs(uint8_t state);
void TestPattern(void);
void ShortDelay(void);          // New small delay function

/*==========================================================================*/
void main(void) 
{
    Setup();
    while(1)
    {
        Loop();
    }
}

//====================================================================
// Small delay for clock stability (replaces _nop_)
//====================================================================
void ShortDelay(void)
{
    uint8_t i = 2;              // Adjust if needed (1~5)
    while(i--);
}

//====================================================================
// SETUP
//====================================================================
void Setup(void)
{
    P1M1 &= ~0x07;      // P1.0, P1.1, P1.2 as output
    P1M2 |=  0x07;

    DATA_PIN  = 0;
    CLK_PIN   = 0;
    LATCH_PIN = 0;

    AllLEDs(0);
    ShiftOutAll();

    Timer0_Delay1ms(200);
}

//====================================================================
// MAIN LOOP
//====================================================================
void Loop(void)
{
    TestPattern();
}

//====================================================================
// SHIFT OUT ALL REGISTERS
//====================================================================
void ShiftOutAll(void)
{
    uint8_t i, j;
    
    LATCH_PIN = 0;

    for(i = NUM_SHIFT_REGS; i > 0; i--)
    {
        uint8_t byte = ledState[i-1];
        
        for(j = 0; j < 8; j++)
        {
            DATA_PIN = (byte & 0x80) ? 1 : 0;
            byte <<= 1;

            CLK_PIN = 1;
            ShortDelay();           // Stable clock pulse
            CLK_PIN = 0;
            ShortDelay();
        }
    }
    
    LATCH_PIN = 1;
    ShortDelay();
    LATCH_PIN = 0;
}

//====================================================================
// Set Individual LED (0 to 49)
//====================================================================
void SetLED(uint8_t led_number, uint8_t state)
{
    if(led_number >= 50) return;
    
    uint8_t reg = led_number / 8;
    uint8_t bit = led_number % 8;
    
    if(state)
        ledState[reg] |=  (1 << (7 - bit));
    else
        ledState[reg] &= ~(1 << (7 - bit));
}

//====================================================================
// Set All LEDs
//====================================================================
void AllLEDs(uint8_t state)
{
    uint8_t i;
    uint8_t value = state ? 0xFF : 0x00;
    for(i = 0; i < NUM_SHIFT_REGS; i++)
        ledState[i] = value;
}

//====================================================================
// Test Pattern
//====================================================================
void TestPattern(void)
{
    static uint8_t pos = 0;
    static uint8_t direction = 1;
    
    AllLEDs(0);
    
    SetLED(pos, 1);
    if(pos > 0)  SetLED(pos-1, 1);
    if(pos > 1)  SetLED(pos-2, 1);
    
    ShiftOutAll();
    
    Timer0_Delay1ms(80);        // Adjust speed here
    
    if(direction)
    {
        pos++;
        if(pos >= 49) direction = 0;
    }
    else
    {
        pos--;
        if(pos == 0) direction = 1;
    }
}