/**
 * @file        example_uptime.c
 * @brief       How long the board has been running. The uptime option of the example library.
 * @version     1.4.0
 *
 * @author      Nima Askari (NimaLTD)
 * @email       nima.askari@gmail.com
 * @github      https://www.github.com/nimaltd
 * @linkedin    https://www.linkedin.com/in/nimaltd
 * @youtube     https://www.youtube.com/@nimaltd
 * @instagram   https://instagram.com/github.nimaltd
 *
 * @copyright   (c) 2026 Nima Askari (NimaLTD)
 *              SPDX-License-Identifier: Apache-2.0
 *              See LICENSE.md in the project root for the full license text.
 */

/*
 * ****************************************************************************************************
 * Includes
 * ****************************************************************************************************
*/

#include "example_uptime.h"
#include "main.h"

/*
 * ****************************************************************************************************
 * Public function implementations
 * ****************************************************************************************************
*/

/*****************************************************************************************************/
/**
 * @brief How long the board has been running.
 *
 * @return Hours, minutes and seconds since start up. The tick wraps round after 49 days.
 */
example_uptime_t example_uptime(void)
{
    example_uptime_t uptime;
    uint32_t         seconds = HAL_GetTick() / 1000U;

    uptime.hours   = seconds / 3600U;
    uptime.minutes = (uint8_t)((seconds / 60U) % 60U);
    uptime.seconds = (uint8_t)(seconds % 60U);

    return uptime;
}
