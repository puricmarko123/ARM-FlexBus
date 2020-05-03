/*
 * @what: FlexBus Interface
 * @why: Parallel bus for VRIO SRAM
 * @who: Marko Puric
 * @when: 03.02.2020.
 *
 */

#ifndef UTASKER_HARDWARE_KINETIS_FLEXBUS_H_
#define UTASKER_HARDWARE_KINETIS_FLEXBUS_H_

/* FlexBus Ports Initialization */
void FlexBus_Init(void);

/* FlexBus Initialization for External SRAM */
void FlexBus_SRAM_Init(void);

/* FlexBus Initialization for Parallel Interface */
void FlexBus_Comm_Init(void);

#endif /* UTASKER_HARDWARE_KINETIS_FLEXBUS_H_ */

