// log.c

#include <stdarg.h>
#include <stdio.h>

#include "log.h"

void log_printf(const char* format, ...) {
  va_list args;
  va_start(args, format);

  vprintf(format, args);
  va_end(args);
}