/**
 * @file  gpio_utils.c
 * @brief Implementation of gpio_utils — simple GPIO output helpers.
 * @author Martin Calamel
 * @date 22/04/2026
 */

#include "gpio_utils.h"
#include <lgpio.h>
#include <stdio.h>

/* -------------------------------------------------------------------------
 * Internal helper
 * ---------------------------------------------------------------------- */

/**
 * @brief Claim pin as output and write desired level.
 *
 * @param handle       lgpio chip handle.
 * @param gpio_number  BCM GPIO number.
 * @param level        Desired logic level: 0 (LOW) or 1 (HIGH).
 *
 * @return GPIO_UTILS_OK, GPIO_UTILS_ERR_CLAIM, or GPIO_UTILS_ERR_WRITE.
 */
static int _set_gpio(int handle, int gpio_number, int level)
{
    int rc;

    /* Claim pin as output, initialise to desired level */
    rc = lgGpioClaimOutput(handle, 0, gpio_number, level);
    if (rc < 0) {
        fprintf(stderr,
                "[gpio_utils] ERROR: cannot claim GPIO%d as output: %s\n",
                gpio_number, lguErrorText(rc));
        return GPIO_UTILS_ERR_CLAIM;
    }

    /* Write the level explicitly (covers re-claim case) */
    rc = lgGpioWrite(handle, gpio_number, level);
    if (rc < 0) {
        fprintf(stderr,
                "[gpio_utils] ERROR: cannot write GPIO%d: %s\n",
                gpio_number, lguErrorText(rc));
        return GPIO_UTILS_ERR_WRITE;
    }

    return GPIO_UTILS_OK;
}

/* -------------------------------------------------------------------------
 * Public API
 * ---------------------------------------------------------------------- */

int up_gpio(int handle, int gpio_number)
{
    return _set_gpio(handle, gpio_number, 1);
}

int down_gpio(int handle, int gpio_number)
{
    return _set_gpio(handle, gpio_number, 0);
}