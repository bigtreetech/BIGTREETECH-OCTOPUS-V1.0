/*
 * Startup.cpp
 *
 *  Created on: 10 Dec 2020
 *      Author: David
 */

#include <CoreIO.h>

extern "C" void __libc_init_array();

// Forward declaration
static void InitClocks() noexcept;

extern uint32_t _sfixed;
//extern uint32_t _efixed;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;
//extern uint32_t _sstack;

// Clock Settings (120MHz)
const uint32_t FlashWaitStates = 5;		// the FWS value needed, one less than the actual number of flash wait states
#define SYS_BOARD_OSCOUNT   (CKGR_MOR_MOSCXTST(0x8U))
#define SYS_BOARD_PLLAR     (CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(0x13U) | CKGR_PLLAR_PLLACOUNT(0x3fU) | CKGR_PLLAR_DIVA(0x1U))
#define SYS_BOARD_MCKR      (PMC_MCKR_PRES_CLK_2 | PMC_MCKR_CSS_PLLA_CLK)

#define CONFIG_PLL0_SOURCE          PLL_SRC_MAINCK_XTAL

#if SAM4E || SAM4S
# define CONFIG_PLL0_MUL			20		// (20 * 12)/2 = 120MHz
#elif SAM3XA
# define CONFIG_PLL0_MUL			14		// (14 * 12)/2 = 84MHz
#elif SAME70
#define CONFIG_PLL0_MUL             25		// (25 * 12)/1 = 300MHz
#endif

#define CONFIG_PLL0_DIV				1

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
void Reset_Handler() noexcept
{
	uint32_t *pSrc, *pDest;

	/* Initialize the relocate segment */
	pSrc = &_etext;
	pDest = &_srelocate;

	if (pSrc != pDest) {
		for (; pDest < &_erelocate;) {
			*pDest++ = *pSrc++;
		}
	}

	/* Clear the zero segment */
	for (pDest = &_szero; pDest < &_ezero;) {
		*pDest++ = 0;
	}

	/* Set the vector table base address */
	pSrc = (uint32_t *) & _sfixed;
	SCB->VTOR = ((uint32_t) pSrc & SCB_VTOR_TBLOFF_Msk);

	/* Initialize the C library */
	__libc_init_array();

	// Set up the standard clocks
	InitClocks();

	// Temporarily set up systick so that delayMicroseconds works
	SysTick->LOAD = ((SystemCoreClockFreq/1000) - 1) << SysTick_LOAD_RELOAD_Pos;
	SysTick->CTRL = (1 << SysTick_CTRL_ENABLE_Pos) | (1 << SysTick_CTRL_CLKSOURCE_Pos);

	// Initialise application, which includes setting up any additional clocks
	AppInit();

	// Run the application
	AppMain();

	/* Infinite loop */
	while (1);
}

#define PLL_COUNT           0x3fU

/**
 * \brief Setup the microcontroller system.
 * Initialize the System and update the SystemFrequency variable.
 */
static void InitClocks()
{
	/* Set flash wait state to max in case the below clock switching. */
	EFC0->EEFC_FMR = EEFC_FMR_FWS(FlashWaitStates) | EEFC_FMR_CLOE;

	// Initialize crystal oscillator
	if ( !(PMC->CKGR_MOR & CKGR_MOR_MOSCSEL) )
	{
		PMC->CKGR_MOR = CKGR_MOR_KEY_PASSWD | SYS_BOARD_OSCOUNT |
				CKGR_MOR_MOSCRCEN | CKGR_MOR_MOSCXTEN;
		while (!(PMC->PMC_SR & PMC_SR_MOSCXTS)) { }
	}

	// Switch to crystal oscillator
	PMC->CKGR_MOR |= CKGR_MOR_KEY_PASSWD | CKGR_MOR_MOSCSEL;
	while (!(PMC->PMC_SR & PMC_SR_MOSCSELS)) { }

	// Switch master clock to main clock
	PMC->PMC_MCKR = (PMC->PMC_MCKR & ~(uint32_t)PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
	while ( !(PMC->PMC_SR & PMC_SR_MCKRDY) ) { }

	// Stop the PLL before we change it
	PMC->CKGR_PLLAR = CKGR_PLLAR_ONE | CKGR_PLLAR_MULA(0);

	// Initialize PLLA
	PMC->CKGR_PLLAR = SYS_BOARD_PLLAR;
	while (!(PMC->PMC_SR & PMC_SR_LOCKA)) { }

	// Switch to main clock
	PMC->PMC_MCKR = (SYS_BOARD_MCKR & ~PMC_MCKR_CSS_Msk) | PMC_MCKR_CSS_MAIN_CLK;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) { }

	// Switch to PLLA
	PMC->PMC_MCKR = SYS_BOARD_MCKR;
	while (!(PMC->PMC_SR & PMC_SR_MCKRDY)) { }

	SystemCoreClock = SystemCoreClockFreq;
}

// End
