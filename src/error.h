/**
 * Project: fusequota
 * Author: August Sodora III <augsod@gmail.com>
 * File: error.h
 * License: GPLv3
 *
 * fusequota is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fusequota is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with fusequota. If not, see <http://www.gnu.org/licenses/>.
 *
 * Description:
 * This file provides a simple mechanism for reporting errors
 * and translating errno values.
 */
#ifndef ERROR_H
#define ERROR_H

/**
 * Report the error described by the current errno to the
 * user, prefixed by the given message. 
 */
void error (char *msg);

#endif /* ERROR_H */
