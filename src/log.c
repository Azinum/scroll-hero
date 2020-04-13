// log.c

#include "log.h"

#include <stdarg.h>
#include <stdio.h>

void log_out(const char* format, ...) {
  va_list args;
  va_start(args, format);

  vprintf(format, args);
  va_end(args);
}