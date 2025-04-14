/*! ----------------------------------------------------------------------------
 * @file    port_platform.h
 * @brief   HW specific definitions and functions for portability
 *
 * @attention
 *
 * Copyright 2015 (c) DecaWave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author DecaWave
 */

#ifndef PORT_PLATFORM_H_
#define PORT_PLATFORM_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <string.h>

#include "deca_types.h"
// #include "app_util_platform.h"
// #include "boards.h"
// #include "app_error.h"
#include "deca_device_api.h"

/*

Note: Antenna Delay Values
The sum of the values is the TX to RX antenna delay, this should be experimentally determined by a calibration process. Here we use a hard coded
value (expected to be a little low so a positive error will be seen on the resultant distance estimate. For a real production application, each
device should have its own antenna delay properly calibrated to get good precision when performing range measurements.

*/

/* Default antenna delay values for 64 MHz PRF.*/
#define TX_ANT_DLY 16456
#define RX_ANT_DLY 16456

  int readfromspi(uint16 headerLength, const uint8 *headerBuffer, uint32 readlength, uint8 *readBuffer);
  int writetospi(uint16 headerLength, const uint8 *headerBuffer, uint32 bodylength, const uint8 *bodyBuffer);
  decaIrqStatus_t decamutexon(void);
  void decamutexoff(decaIrqStatus_t s);

#if 0

/* DW1000 IRQ (EXTI9_5_IRQ) handler type. */
typedef void (*port_deca_isr_t)(void);

/* DW1000 IRQ handler declaration. */
port_deca_isr_t port_deca_isr;

/*! ------------------------------------------------------------------------------------------------------------------
 * @fn port_set_deca_isr()
 *
 * @brief This function is used to install the handling function for DW1000 IRQ.
 *
 * NOTE:
 *   - As EXTI9_5_IRQHandler does not check that port_deca_isr is not null, the user application must ensure that a
 *     proper handler is set by calling this function before any DW1000 IRQ occurs!
 *   - This function makes sure the DW1000 IRQ line is deactivated while the handler is installed.
 *
 * @param deca_isr function pointer to DW1000 interrupt handler to install
 *
 * @return none
 */
void port_set_deca_isr(port_deca_isr_t deca_isr);

#endif

  /*****************************************************************************************************************/ /*
                                                                                                                       **/

  /****************************************************************************/ /**
                                                                                  *
                                                                                  *                                 Types definitions
                                                                                  *
                                                                                  *******************************************************************************/
  typedef uint64_t uint64;

  typedef int64_t int64;

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

  /****************************************************************************/ /**
                                                                                  *
                                                                                  *                              MACRO function
                                                                                  *
                                                                                  *******************************************************************************/

  /****************************************************************************/ /**
                                                                                  *
                                                                                  *                              port function prototypes
                                                                                  *
                                                                                  *******************************************************************************/

  void Sleep(uint32_t Delay);
  unsigned long portGetTickCnt(void);

  void port_wakeup_dw1000(void);
  void port_wakeup_dw1000_fast(void);

  void port_set_dw1000_slowrate(void);
  void port_set_dw1000_fastrate(void);

  void process_dwRSTn_irq(void);
  void process_deca_irq(void);

  void setup_DW1000RSTnIRQ(int enable);

  void reset_DW1000(void);

  typedef enum
  {
    dwSpiSpeedLow,
    dwSpiSpeedHigh
  } dwSpiSpeed_t;

  typedef struct dwOps_s
  {
    /**
     * Function that activates the chip-select, sends header, read data and
     * disable the chip-select.
     */
    void (*spiRead)(const void *header, size_t headerLength,
                    void *data, size_t dataLength);

    /**
     * Function that activates the chip-select, sends header, sends data and
     * disable the chip-select.
     */
    void (*spiWrite)(const void *header, size_t headerLength,
                     const void *data, size_t dataLength);

    /**
     * Sets the SPI bus speed. Take as argument:
     *	 - dwSpiSpeedLow: <= 4MHz
     *	 - dwSpiSpeedHigh: <= 20MHz
     */
    void (*spiSetSpeed)(dwSpiSpeed_t speed);

    /**
     * Waits at least 'delay' miliseconds.
     */
    void (*delayms)(unsigned int delay);

    /**
     * Resets the DW3000 by pulling the reset pin low and then releasing it.
     * This function is optional, if not set softreset via SPI will be used.
     */
    void (*reset)(void);
  } dwOps_t;

  dwOps_t dwt_ops;

#ifdef __cplusplus
}
#endif

#endif /* PORT_PLATFORM_H_ */