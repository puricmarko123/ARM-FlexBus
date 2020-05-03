i/*
 * @what: FlexBus Interface
 * @why: Parallel bus for VRIO SRAM
 * @who: Marko Puric
 * @when: 03.02.2020.
 *
 */

#include "FlexBus.h"
#include "PE_Types.h"
#include "MK65F18.h"

/* Macros for External SRAM  */
#define EXT_SRAM_END_ADDRESS        (0x600FFFFEU)
#define EXT_SRAM_ADDRESS_MASK       (0x000EU)

/* Macros for Parallel Bus */
#define PARALLEL_BUS_START_ADDRESS  (0x601fffffU)
#define PARALLEL_BUS_END_ADDRESS    0xffffffffffffffffU
#define PARALLEL_BUS_ADDRESS_MASK   (0x000EU)

/*
 * @what: FlexBus Ports Initialization
 * @why: General FlexBus Initialization
 */
void FlexBus_Init(void)
{
	/* Enable the clock to the FlexBus */
	SIM_SCGC7 = SIM_SCGC7 | SIM_SCGC7_FLEXBUS_MASK;

	/* FlexBus clock set to 60 MHz*/
	SIM_CLKDIV1 = SIM_CLKDIV1 | SIM_CLKDIV1_OUTDIV3(0x00U);

	/* Enable GPIO clocks (Enable All Ports) */
	SIM_SCGC5 = SIM_SCGC5 |
                SIM_SCGC5_PORTA_MASK | 
                SIM_SCGC5_PORTB_MASK | 
                SIM_SCGC5_PORTC_MASK | 
                SIM_SCGC5_PORTD_MASK | 
                SIM_SCGC5_PORTE_MASK;

	/* Enable FlexBus Clock */
	PORTA_PCR6 = PORT_PCR_MUX(0x5U);

	/* Set FB_CSPMCR register for multiplexed signals */
	FB_CSPMCR = FB_CSPMCR_GROUP1(0x01U) 	|
				FB_CSPMCR_GROUP2(0x02U)     |
				FB_CSPMCR_GROUP3(0x02U)		|
				FB_CSPMCR_GROUP4(0x02U)		|
				FB_CSPMCR_GROUP5(0x02U);

	FB_CSMR0 = FB_CSMR0 | FB_CSMR_V_MASK;

	return;
}

/*
 * @what: FlexBus Initialization for External SRAM
 * @why: Parallel Interface for SRAM
 */
void FlexBus_SRAM_Init(void)
{
	/* SRAM Ports Configuration */
	/* Data Ports */
	PORTB_PCR17 = PORT_PCR_MUX(0x5U);		// FB_D0
	PORTB_PCR16 = PORT_PCR_MUX(0x5U);		// FB_D1
	PORTB_PCR11 = PORT_PCR_MUX(0x5U);		// FB_D2
	PORTB_PCR10 = PORT_PCR_MUX(0x5U);		// FB_D3
	PORTB_PCR9 = PORT_PCR_MUX(0x5U);		// FB_D4
	PORTB_PCR8 = PORT_PCR_MUX(0x5U);		// FB_D5
	PORTB_PCR7 = PORT_PCR_MUX(0x5U);		// FB_D6
	PORTB_PCR6 = PORT_PCR_MUX(0x5U);		// FB_D7
	PORTC_PCR15 = PORT_PCR_MUX(0x5U);		// FB_D8
	PORTC_PCR14 = PORT_PCR_MUX(0x5U);		// FB_D9
	PORTC_PCR13 = PORT_PCR_MUX(0x5U);		// FB_D10
	PORTC_PCR12 = PORT_PCR_MUX(0x5U);		// FB_D11
	PORTB_PCR23 = PORT_PCR_MUX(0x5U);		// FB_D12
	PORTB_PCR22 = PORT_PCR_MUX(0x5U);		// FB_D13
	PORTB_PCR21 = PORT_PCR_MUX(0x5U);		// FB_D14
	PORTB_PCR20 = PORT_PCR_MUX(0x5U);		// FB_D15

	/* Address Ports */
	PORTC_PCR28 = PORT_PCR_MUX(0x5U);		// FB_A1
	PORTD_PCR4 = PORT_PCR_MUX(0x5U);		// FB_A2
	PORTD_PCR3 = PORT_PCR_MUX(0x5U);		// FB_A3
	PORTD_PCR2 = PORT_PCR_MUX(0x5U);		// FB_A4
	PORTC_PCR10 = PORT_PCR_MUX(0x5U);		// FB_A5
	PORTC_PCR9 = PORT_PCR_MUX(0x5U);		// FB_A6
	PORTC_PCR8 = PORT_PCR_MUX(0x5U);		// FB_A7
	PORTC_PCR7 = PORT_PCR_MUX(0x5U);		// FB_A8
	PORTC_PCR6 = PORT_PCR_MUX(0x5U);		// FB_A9
	PORTC_PCR5 = PORT_PCR_MUX(0x5U);		// FB_A10
	PORTC_PCR4 = PORT_PCR_MUX(0x5U);		// FB_A11
	PORTC_PCR2 = PORT_PCR_MUX(0x5U);		// FB_A12
	PORTC_PCR1 = PORT_PCR_MUX(0x5U);		// FB_A13
	PORTC_PCR0 = PORT_PCR_MUX(0x5U);		// FB_A14
	PORTB_PCR18 = PORT_PCR_MUX(0x5U);		// FB_A15
	PORTD_PCR8 = PORT_PCR_MUX(0x5U);		// FB_A16
	PORTD_PCR9 = PORT_PCR_MUX(0x5U);		// FB_A17
	PORTD_PCR10 = PORT_PCR_MUX(0x5U);		// FB_A18
	PORTD_PCR11 = PORT_PCR_MUX(0x5U);		// FB_A19

	/* Control signals */
	PORTC_PCR17 = PORT_PCR_MUX(0x5U);		// FB_UE
	PORTC_PCR16 = PORT_PCR_MUX(0x5U);		// FB_LE
	PORTB_PCR19 = PORT_PCR_MUX(0x5U);		// FB_OE
	PORTC_PCR11 = PORT_PCR_MUX(0x5U);		// FB_WE
	PORTD_PCR0 = PORT_PCR_MUX(0x5U);		// FB_CS1

	/* Set CS1 Start Address */
	FB_CSAR1 = (uint32_t)EXT_SRAM_START_ADDRESS;

	/* Set FB CSCR1 for SRAM Configuration*/
	FB_CSCR1 = FB_CSCR_PS(0x02U) 	|
			   FB_CSCR_AA_MASK   	|
			   FB_CSCR_BEM_MASK		|
			   FB_CSCR_WS(0x03U);

	/* Set base address mask to 512K address space */
	FB_CSMR1 = FB_CSMR_BAM(EXT_SRAM_ADDRESS_MASK) |
			   FB_CSMR_V_MASK;

	return;
}

/*
 * @what: FlexBus Initialization for Parallel Interface
 * @why: Parallel Interface Communication with modules
 */
void FlexBus_Comm_Init(void)
{
	/* Parallel Interface Ports Configuration */
	/* Data Ports */
	PORTB_PCR17 = PORT_PCR_MUX(0x5U);		// FB_D0
	PORTB_PCR16 = PORT_PCR_MUX(0x5U);		// FB_D1
	PORTB_PCR11 = PORT_PCR_MUX(0x5U);		// FB_D2
	PORTB_PCR10 = PORT_PCR_MUX(0x5U);		// FB_D3
	PORTB_PCR9 = PORT_PCR_MUX(0x5U);		// FB_D4
	PORTB_PCR8 = PORT_PCR_MUX(0x5U);		// FB_D5
	PORTB_PCR7 = PORT_PCR_MUX(0x5U);		// FB_D6
	PORTB_PCR6 = PORT_PCR_MUX(0x5U);		// FB_D7
	PORTC_PCR15 = PORT_PCR_MUX(0x5U);		// FB_D8
	PORTC_PCR14 = PORT_PCR_MUX(0x5U);		// FB_D9
	PORTC_PCR13 = PORT_PCR_MUX(0x5U);		// FB_D10
	PORTC_PCR12 = PORT_PCR_MUX(0x5U);		// FB_D11
	PORTB_PCR23 = PORT_PCR_MUX(0x5U);		// FB_D12
	PORTB_PCR22 = PORT_PCR_MUX(0x5U);		// FB_D13
	PORTB_PCR21 = PORT_PCR_MUX(0x5U);		// FB_D14
	PORTB_PCR20 = PORT_PCR_MUX(0x5U);		// FB_D15

	/* Address Ports */
	PORTC_PCR28 = PORT_PCR_MUX(0x5U);		// FB_A1
	PORTD_PCR4 = PORT_PCR_MUX(0x5U);		// FB_A2
	PORTD_PCR3 = PORT_PCR_MUX(0x5U);		// FB_A3
	PORTD_PCR2 = PORT_PCR_MUX(0x5U);		// FB_A4
	PORTC_PCR10 = PORT_PCR_MUX(0x5U);		// FB_A5
	PORTC_PCR9 = PORT_PCR_MUX(0x5U);		// FB_A6
	PORTC_PCR8 = PORT_PCR_MUX(0x5U);		// FB_A7
	PORTC_PCR7 = PORT_PCR_MUX(0x5U);		// FB_A8
	PORTC_PCR6 = PORT_PCR_MUX(0x5U);		// FB_A9
	PORTC_PCR5 = PORT_PCR_MUX(0x5U);		// FB_A10
	PORTC_PCR4 = PORT_PCR_MUX(0x5U);		// FB_A11
	PORTC_PCR2 = PORT_PCR_MUX(0x5U);		// FB_A12
	PORTC_PCR1 = PORT_PCR_MUX(0x5U);		// FB_A13
	PORTC_PCR0 = PORT_PCR_MUX(0x5U);		// FB_A14
	PORTB_PCR18 = PORT_PCR_MUX(0x5U);		// FB_A15
	PORTD_PCR8 = PORT_PCR_MUX(0x5U);		// FB_A16
	PORTD_PCR9 = PORT_PCR_MUX(0x5U);		// FB_A17
	PORTD_PCR10 = PORT_PCR_MUX(0x5U);		// FB_A18
	PORTD_PCR11 = PORT_PCR_MUX(0x5U);		// FB_A19

	/* Control signals */
	PORTC_PCR17 = PORT_PCR_MUX(0x5U);		// FB_UE
	PORTC_PCR16 = PORT_PCR_MUX(0x5U);		// FB_LE
	PORTB_PCR19 = PORT_PCR_MUX(0x5U);		// FB_OE
	PORTC_PCR11 = PORT_PCR_MUX(0x5U);		// FB_WE
	PORTD_PCR1 = PORT_PCR_MUX(0x5U);		// FB_CS0

	/* Set CS0 Start Address */
	FB_CSAR0 = (uint32_t) (PARALLEL_BUS_START_ADDRESS);

	/* Set FB_CSCR0 register. Configured for 16_bit data transfer, data is sampled on FB_D[31:16] when BLS = 0 */
	FB_CSCR0 = FB_CSCR_PS(0x02U) 	|
			   FB_CSCR_AA_MASK   	|
			   FB_CSCR_BEM_MASK		|
			   FB_CSCR_WS(0x1FU);

	/* Set FB_CSMR0 register */
	FB_CSMR0 = FB_CSMR_BAM(PARALLEL_BUS_ADDRESS_MASK) |
			   FB_CSMR_V_MASK;
	return;
}

