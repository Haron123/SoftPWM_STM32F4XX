#include "error_handler.h"

void error_handler(char* msg, uint32_t msg_len, char* file, uint32_t line)
{
    // Turn on Error LED
    __disable_irq();
    // TODO : Write msg, but where to ?
    while(1);
}

void warning_handler(char* msg, uint32_t msg_len, char* file, uint32_t line)
{
    // TODO : Write msg, but where to ?
}
