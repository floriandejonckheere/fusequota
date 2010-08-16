/**
 * Project: fusequota
 * Author: August Sodora III <augsod@gmail.com>
 * File: space.h
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
 * This file provides a means for computing the amount of space
 * used by a file or directory.
 */
#ifndef SPACE_H
#define SPACE_H

/**
 * Constants to facilitate conversions. Not sure if this is the
 * best way to represent these, but they can be read as the
 * number of bytes that are in the relevant unit.
 */
#define BYTES_IN_KILOBYTE 1024.0L
#define BYTES_IN_MEGABYTE 1048576.0L
#define BYTES_IN_GIGABYTE 1073741824.0L
#define BYTES_IN_TERABYTE 1099511627776.0L

/**
 * Computes the amount of space on the filesystem taken up by
 * the file or directory at the given path.
 */
unsigned long space (const char *path);

#endif /* SPACE_H */
