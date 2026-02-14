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