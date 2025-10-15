// ---------------------------------------------------------
// @rebwar_ai
// ---------------------------------------------------------
#include <stdint.h>  // Provides fixed-width integer types like uint8_t and uint16_t

// ---------------------------------------------------------
// ⚙️ System Configuration
// ---------------------------------------------------------
#define F_CPU 16000000UL        // Define CPU clock frequency: 16 MHz for ATmega2560
#define CYCLES_PER_LOOP 10UL    // Approximate number of CPU cycles each delay loop iteration takes
#define DELAY_COUNT (F_CPU / 1000UL / CYCLES_PER_LOOP)
// DELAY_COUNT represents how many inner loop iterations are needed for a 1 ms delay
// Formula: (CPU frequency / 1000 ms) / cycles per loop iteration

#define LED_PIN 7               // PB7 → Digital Pin 13 (built-in LED on Arduino Mega)

// ---------------------------------------------------------
// 🧩 Direct Register Access Definitions
// ---------------------------------------------------------
#define DDRB_REG  (*(volatile uint8_t*)0x24)
// DDRB: Data Direction Register for Port B
// Address: 0x24
// Setting a bit to 1 configures the corresponding pin as OUTPUT

#define PORTB_REG (*(volatile uint8_t*)0x25)
// PORTB: Data Register for Port B
// Address: 0x25
// Writing 1 to a bit sets the pin HIGH, writing 0 sets it LOW

// ---------------------------------------------------------
// 🕒 Function Prototype
// ---------------------------------------------------------
static inline void delay_ms(uint16_t ms);
// delay_ms() creates a time delay in milliseconds using nested loops and NOP instructions

// ---------------------------------------------------------
// 🚀 Main Function
// ---------------------------------------------------------
int main(void)
{
    // -----------------------------------------------------
    // 🧠 Step 1: Configure PB7 (LED pin) as OUTPUT
    // -----------------------------------------------------
    DDRB_REG |= (1 << LED_PIN);
    // Bitwise OR sets bit 7 (PB7) to 1 → configures LED pin as output

    // -----------------------------------------------------
    // 🔁 Step 2: Main Loop
    // -----------------------------------------------------
    while (1)
    {
        // ---------------------------------------------
        // Option 1: Classic ON/OFF Blink
        // ---------------------------------------------
        // PORTB_REG |= (1 << LED_PIN);   // Turn LED ON
        // delay_ms(500);                 // Wait 500 ms
        // PORTB_REG &= ~(1 << LED_PIN);  // Turn LED OFF
        // delay_ms(500);                 // Wait 500 ms

        // ---------------------------------------------
        // Option 2: Toggle LED Each Cycle
        // ---------------------------------------------
        PORTB_REG ^= (1 << LED_PIN);  // XOR toggles bit 7 → LED switches ON/OFF
        delay_ms(300);                // Wait 300 ms
    }
}

// ---------------------------------------------------------
// ⏱️ Software Delay Function
// ---------------------------------------------------------
static inline void delay_ms(uint16_t ms)
{
    // Outer loop → repeats for the specified number of milliseconds
    for (uint16_t i = 0; i < ms; ++i)
    {
        // Inner loop → creates ~1 ms delay per iteration
        for (uint16_t j = 0; j < DELAY_COUNT; ++j)
        {
            __asm__ __volatile__("nop");
            // 'nop' → No Operation (1 CPU cycle)
            // Keeps CPU busy, consuming time for the delay
        }
    }
}
