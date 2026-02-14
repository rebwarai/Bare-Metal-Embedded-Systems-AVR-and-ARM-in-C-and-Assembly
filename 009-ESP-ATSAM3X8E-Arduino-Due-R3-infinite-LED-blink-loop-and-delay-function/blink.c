#include <stdint.h>

#define F_CPU 84000000UL

#define REG32(addr) (*(volatile uint32_t *)(addr))

#define PMC_BASE           0x400E0600UL
#define PMC_PCER0          REG32(PMC_BASE + 0x10u)
#define PMC_CKGR_MOR       REG32(PMC_BASE + 0x20u)
#define PMC_CKGR_PLLAR     REG32(PMC_BASE + 0x28u)
#define PMC_MCKR           REG32(PMC_BASE + 0x30u)
#define PMC_SR             REG32(PMC_BASE + 0x68u)

#define CKGR_MOR_MOSCXTEN_Pos  0u
#define CKGR_MOR_MOSCXTEN (0x1u << CKGR_MOR_MOSCXTEN_Pos)
#define CKGR_MOR_MOSCRCEN_Pos  3u
#define CKGR_MOR_MOSCRCEN (0x1u << CKGR_MOR_MOSCRCEN_Pos)

#define CKGR_MOR_MOSCXTST_Pos  8u
#define CKGR_MOR_MOSCXTST(v)  (((uint32_t)(v) <<CKGR_MOR_MOSCXTST_Pos) & (0xffu << CKGR_MOR_MOSCXTST_Pos))
#define CKGR_MOR_KEY_Pos  16u
#define CKGR_MOR_KEY(v)  (((uint32_t)(v) << CKGR_MOR_KEY_Pos) & (0xffu << CKGR_MOR_KEY_Pos))
#define CKGR_MOR_MOSCSEL_Pos  24u
#define CKGR_MOR_MOSCSEL (0x1u << CKGR_MOR_MOSCSEL_Pos)

#define CKGR_PLLAR_DIVA_Pos  0u
#define CKGR_PLLAR_DIVA(v)  (((uint32_t)(v) << CKGR_PLLAR_DIVA_Pos) & (0xffu << CKGR_PLLAR_DIVA_Pos))
#define CKGR_PLLAR_PLLACOUNT_Pos  8u
#define CKGR_PLLAR_PLLACOUNT(v) (((uint32_t)(v) << CKGR_PLLAR_PLLACOUNT_Pos) & (0x3fu << CKGR_PLLAR_PLLACOUNT_Pos))
#define CKGR_PLLAR_MULA_Pos  16u
#define CKGR_PLLAR_MULA(v) (((uint32_t)(v) << CKGR_PLLAR_MULA_Pos) & (0x7ffu << CKGR_PLLAR_MULA_Pos))
#define CKGR_PLLAR_ONE_Pos  29u
#define CKGR_PLLAR_ONE  (0x1u << CKGR_PLLAR_ONE_Pos)

#define PMC_SR_MOSCXTS_Pos  0u
#define PMC_SR_MOSCXTS  (0x1u << PMC_SR_MOSCXTS_Pos)

#define PMC_SR_LOCKA_Pos  1u
#define PMC_SR_LOCKA  (0x1u << PMC_SR_LOCKA_Pos)

#define PMC_SR_MCKRDY_Pos  3u
#define PMC_SR_MCKRDY  (0x1u << PMC_SR_MCKRDY_Pos)

#define PMC_SR_MOSCSELS_Pos  16u
#define PMC_SR_MOSCSELS  (0x1u << PMC_SR_MOSCSELS_Pos)


#define PMC_MCKR_CSS_Pos  0u
#define PMC_MCKR_CSS_Msk  (0x3u << PMC_MCKR_CSS_Pos)
#define PMC_MCKR_CSS_MAIN_CLK  (0x1u << PMC_MCKR_CSS_Pos)
#define PMC_MCKR_CSS_PLLA_CLK  (0x2u << PMC_MCKR_CSS_Pos)

#define PMC_MCKR_PRES_Pos  4u
#define PMC_MCKR_PRES_Msk  (0x7u << PMC_MCKR_PRES_Pos)
#define PMC_MCKR_PRES_CLK_2  (0x1u << PMC_MCKR_PRES_Pos)


#define EEFC0_BASE   0x400E0A00UL
#define EEFC1_BASE   0x400E0C00UL

#define EEFC0_FMR    REG32(EEFC0_BASE + 0x00u)
#define EEFC1_FMR    REG32(EEFC1_BASE + 0x00u)

#define EEFC_FMR_FWS_Pos  8u
#define EEFC_FMR_FWS(v)  (((uint32_t)(v) << EEFC_FMR_FWS_Pos) & (0xfu << EEFC_FMR_FWS_Pos))


#define PIOB_BASE   0x400E1000UL
#define PIOB_PER    REG32(PIOB_BASE + 0x00u)
#define PIOB_OER    REG32(PIOB_BASE + 0x10u)
#define PIOB_SODR   REG32(PIOB_BASE + 0x30u)
#define PIOB_CODR   REG32(PIOB_BASE + 0x34u)

#define ID_PIOB 12u
#define LED_PIN 27u
#define LED_MASK  (1u << LED_PIN)

static void board_clock_to_84mhz(void)
{
    const uint32_t MOR_KEY = CKGR_MOR_KEY(0x37u);
    const uint32_t OSCOUNT = CKGR_MOR_MOSCXTST(0x8u);

    EEFC0_FMR = EEFC_FMR_FWS(4u);
    EEFC1_FMR = EEFC_FMR_FWS(4u);

    if(!(PMC_CKGR_MOR & CKGR_MOR_MOSCSEL))
    {
        PMC_CKGR_MOR = MOR_KEY | OSCOUNT |
            CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN;
        
        while (!(PMC_SR & PMC_SR_MOSCXTS)) {}
    }

    PMC_CKGR_MOR = MOR_KEY | OSCOUNT | 
                   CKGR_MOR_MOSCRCEN |
                   CKGR_MOR_MOSCXTEN |
                   CKGR_MOR_MOSCSEL;

    while (!(PMC_SR & PMC_SR_MOSCSELS)) {}

    PMC_MCKR = (PMC_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
    while (!(PMC_SR & PMC_SR_MCKRDY)) {}

    PMC_CKGR_PLLAR = CKGR_PLLAR_ONE |
               CKGR_PLLAR_MULA(13u) |
               CKGR_PLLAR_PLLACOUNT(0x3fu) |
               CKGR_PLLAR_DIVA(1u);
    while (!(PMC_SR & PMC_SR_LOCKA)) {}

    PMC_MCKR = (PMC_MCKR & ~(PMC_MCKR_PRES_Msk | PMC_MCKR_CSS_Msk)) |
            PMC_MCKR_CSS_MAIN_CLK |
            PMC_MCKR_PRES_CLK_2;
    while (!(PMC_SR & PMC_SR_MCKRDY)) {}

    PMC_MCKR = (PMC_MCKR & ~(PMC_MCKR_CSS_Msk)) |
            PMC_MCKR_CSS_PLLA_CLK;
    while (!(PMC_SR & PMC_SR_MCKRDY)) {}
}

static void delay_ms(uint32_t ms)
{
    volatile uint32_t i,j;
    const uint32_t loop_per_ms = F_CPU / 18200u;

    for(i=0 ; i < ms ; ++i)
    {
        for(j=0; j < loop_per_ms; ++j)
        {
            __asm__ __volatile__("nop");
        }
    }
}


int main(void)
{
    board_clock_to_84mhz();

    PMC_PCER0 = (1u << ID_PIOB);
    PIOB_PER = LED_MASK;
    PIOB_OER = LED_MASK;

    while(1)
    {
        PIOB_SODR = LED_MASK;
        delay_ms(500);
        PIOB_CODR = LED_MASK;
        delay_ms(500);
    }
}