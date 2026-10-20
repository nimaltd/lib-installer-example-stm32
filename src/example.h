/**
 * @file        example.h
 * @brief       A small library made to try stm32-installer on: a period that never blocks.
 * @version     1.2.0
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

#ifndef EXAMPLE_H
#define EXAMPLE_H

/*
 * ****************************************************************************************************
 * Includes
 * ****************************************************************************************************
*/

#include <stdbool.h>
#include <stdint.h>
#include "example_config.h"

/*
 * ****************************************************************************************************
 * Configuration checks
 * ****************************************************************************************************
*/

#ifndef EXAMPLE_PERIOD_MS
#error "EXAMPLE_PERIOD_MS is not defined. Add it to example_config.h"
#elif (EXAMPLE_PERIOD_MS < 1U) || (EXAMPLE_PERIOD_MS > 86400000U)
#error "EXAMPLE_PERIOD_MS must be from 1 to 86400000"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * ****************************************************************************************************
 * Types
 * ****************************************************************************************************
*/

/*****************************************************************************************************/
/**
 * @brief One period. Declare one for each thing that repeats, and hand it to example_init().
 */
typedef struct
{
    uint32_t start; /**< HAL_GetTick() when the period under way began. */
    uint32_t count; /**< Times example_due() has said yes.             */

} example_t;

/*
 * ****************************************************************************************************
 * Public function prototypes
 * ****************************************************************************************************
*/

/*****************************************************************************************************/
/**
 * @brief Start a period of EXAMPLE_PERIOD_MS from now.
 */
void example_init(example_t *handle);

/*****************************************************************************************************/
/**
 * @brief Whether the period has passed. Returns at once, and starts the next one when it has.
 */
bool example_due(example_t *handle);

/*****************************************************************************************************/
/**
 * @brief How many times example_due() has said yes.
 */
uint32_t example_count(const example_t *handle);

/*****************************************************************************************************/
/**
 * @brief This device's own ID, from the example_id.h the make-id step made, or 0.
 */
uint32_t example_id(void);

#ifdef __cplusplus
}
#endif

#endif /* EXAMPLE_H */
