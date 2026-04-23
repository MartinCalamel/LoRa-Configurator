/**
 * @file    gpio_utils.h
 * @brief   Simple GPIO helper library for Raspberry Pi 4 (lgpio backend)
 *
 * The caller is responsible for opening and closing the GPIO chip handle.
 * These functions only claim the requested pin as output and drive it.
 *
 * Typical usage:
 * @code
 *   #include "gpio_utils.h"
 *   #include <lgpio.h>
 *
 *   int handle = lgGpiochipOpen(0);      // open chip — caller's job
 *   up_gpio(handle, 17);                 // GPIO17 HIGH
 *   down_gpio(handle, 17);               // GPIO17 LOW
 *   lgGpiochipClose(handle);             // close chip — caller's job
 * @endcode
 *
 * Compile:
 *   gcc main.c gpio_utils.c -o app -llgpio
 *
 * Dependencies:
 *   sudo apt install liblgpio-dev
 */

#ifndef GPIO_UTILS_H
#define GPIO_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Return codes
 * ---------------------------------------------------------------------- */
#define GPIO_UTILS_OK           0   /**< Success                          */
#define GPIO_UTILS_ERR_CLAIM   -1   /**< Failed to claim pin as output    */
#define GPIO_UTILS_ERR_WRITE   -2   /**< Failed to write pin value        */

/* -------------------------------------------------------------------------
 * Function prototypes
 * ---------------------------------------------------------------------- */

/**
 * @brief  Drive a GPIO pin HIGH (3.3 V).
 *
 * Claims @p gpio_number as an output on the chip identified by @p handle,
 * then sets it to logic 1. If the pin is already claimed as output by the
 * same handle, the claim is refreshed transparently.
 *
 * @param[in] handle       GPIO chip handle returned by lgGpiochipOpen().
 * @param[in] gpio_number  BCM GPIO number (e.g. 17 for GPIO17).
 *
 * @return  GPIO_UTILS_OK        on success.
 * @return  GPIO_UTILS_ERR_CLAIM if lgGpioClaimOutput() fails.
 * @return  GPIO_UTILS_ERR_WRITE if lgGpioWrite() fails.
 */
int up_gpio(int handle, int gpio_number);

/**
 * @brief  Drive a GPIO pin LOW (0 V).
 *
 * Claims @p gpio_number as an output on the chip identified by @p handle,
 * then sets it to logic 0. If the pin is already claimed as output by the
 * same handle, the claim is refreshed transparently.
 *
 * @param[in] handle       GPIO chip handle returned by lgGpiochipOpen().
 * @param[in] gpio_number  BCM GPIO number (e.g. 17 for GPIO17).
 *
 * @return  GPIO_UTILS_OK        on success.
 * @return  GPIO_UTILS_ERR_CLAIM if lgGpioClaimOutput() fails.
 * @return  GPIO_UTILS_ERR_WRITE if lgGpioWrite() fails.
 */
int down_gpio(int handle, int gpio_number);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_UTILS_H */