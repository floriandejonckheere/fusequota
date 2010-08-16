/**
 * Project: fusequota
 * File: space.h
 * License: IBM Public License 1.0
 *
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
unsigned long space(const char* path);

#endif /* SPACE_H */
