/** @file
 * Header file providing access to the handler function.
 * @author Gevorg Chobanyan
 * @date 27.04.2020
 */
#ifndef GAMMA_HANDLER_H
#define GAMMA_HANDLER_H
#include "parser.h"
#include "gamma.h"
#include <stdbool.h>

/** @brief Handle a given Command
 * @param [in] g - gamma game's pointer
 * @param [in] command - structure containing command data
 * @return @p true if the command was executed and @p false
 * otherwise.
 */
bool handle_command(gamma_t** g, Command command);

#endif //GAMMA_HANDLER_H
