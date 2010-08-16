/**
 * Project: fusequota
 * File: error.c
 * License: IBM Public License 1.0
 *
 * This file provides a simple mechanism for reporting errors
 * and translating errno values.
 */
#include "error.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Report the error described by the current errno to the
 * user, prefixed by the given message. 
 */
void error(char* msg)
{
  perror(msg);
  exit(errno);
}
