/**
 * Project: fusequota
 * File: error.h
 * License: IBM Public License 1.0
 *
 * This file provides a simple mechanism for reporting errors
 * and translating errno values.
 */
#ifndef ERROR_H
#define ERROR_H

/**
 * Report the error described by the current errno to the
 * user, prefixed by the given message. 
 */
void error(char* msg);

#endif /* ERROR_H */
