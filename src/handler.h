#ifndef GAMMA_HANDLER_H
#define GAMMA_HANDLER_H
#include "parser.h"
#include "gamma.h"
#include <stdbool.h>

// Handle a given Command
bool handle_command(gamma_t** g, Command command);

#endif //GAMMA_HANDLER_H
