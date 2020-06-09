/** @file
 * Source file providing access to the functions
 * responsible for the interactive mode
 * @author Gevorg Chobanyan
 * @date 30.04.2020
 */
#ifndef GAMMA_UI_H
#define GAMMA_UI_H

#include <stdbool.h>
#include "gamma.h"

/** @brief Start Interactive Game Mode
 * @param [in] g - pointer to the structure that stores the game state
 * @return @p true when Interactive Mode finishes, and @p false if the
 * given @p g pointer is NULL
 */
bool start_interactive(gamma_t* g);
#endif //GAMMA_UI_H
