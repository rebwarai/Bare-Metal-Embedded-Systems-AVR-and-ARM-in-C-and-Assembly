#include <stdint.h>

#define F_CPU 16000000UL

#define CYCLES_PER_LOOP 10UL
#define DELAY_COUNT (F_CPU / 1000UL / CYCLES_PER_LOOP)

#define LED_PIN 7

#define DDRB_REG (*(volatile uint8_t*)0x24)
#define PORTB_REG (*(volatile uint8_t*)0x25)

static inline void delay_ms(uint16_t ms);

int main(void)
{
    DDRB_REG |= (1 << LED_PIN);

    while (1)
    {
        PORTB_REG |= (1 << LED_PIN);
        delay_ms(500);
        PORTB_REG &= ~(1 << LED_PIN);
        delay_ms(500);
    }
}

static inline void delay_ms(uint16_t ms)
{
    for (uint16_t i = 0; i < ms; ++i)
    {
        for (uint16_t j = 0; j < DELAY_COUNT; ++j)
        {
            __asm__ __voltaile__("nop");
        }
    }
}