#include <stdint.h> 


#define WDT_BASE   0x400E1A50UL
#define WDT_MR    (*(volatile uint32_t *)(WDT_BASE + 0x04u))
#define WDT_MR_WDDIS_pos  15u
#define WDT_MR_WDDIS  (0x1u << WDT_MR_WDDIS_pos)

extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;


void Reset_Handler(void);
void Default_Handler(void);
void HardFault_Handler(void) __attribute__((weak,alias("Default_Handler")));

__attribute__((section(".isr_vector")))
const void *vector_tabel[] = {
    (void *)&_estack,
    Reset_Handler,
    HardFault_Handler,
    HardFault_Handler,
    0,
};


void Reset_Handler(void)
{
    WDT_MR = WDT_MR_WDDIS;

    const uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while (dst < &_edata) {*dst++ = *src++;}


    dst = &_sbss;
    while (dst < &_ebss) {*dst++ = 0;}

    extern int main(void);
    main();

    while (1) {}
}

void Default_Handler(void)
{
    while (1) {}
}