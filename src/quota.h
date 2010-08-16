/**
 * Project: fusequota
 * Author: August Sodora III <augsod@gmail.com>
 * File: quota.h
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
 */
#ifndef QUOTA_H
#define QUOTA_H

enum units
{
  BYTES = 1L,
  KILOBYTES = 1024L,
  MEGABYTES = 1048576L,
  GIGABYTES = 1073741824L,
  TERABYTES = 1099511627776L
};

enum units char_to_units (const char c);

void quota_set (const char *path, unsigned long size, enum units unit);
long double quota_get (const char *path, enum units unit);
long double quota_get_binding (const char *path, enum units unit,
			       char *binding_path);
int quota_exceeded (const char *path);
void quota_unset (const char *path);

#endif /* QUOTA_H */
