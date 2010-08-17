/**
 * Project: fusequota
 * Author: August Sodora III <augsod@gmail.com>
 * File: quota.c
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
#define _XOPEN_SOURCE 600

#include "quota.h"
#include "space.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <fuse.h>
#include <limits.h>
#include <string.h>

#include <sys/types.h>
#include <attr/xattr.h>

enum units
char_to_units (const char c)
{
  switch (c)
    {
    case 'B':
      return BYTES;
    case 'K':
      return KILOBYTES;
    case 'M':
      return MEGABYTES;
    case 'G':
      return GIGABYTES;
    case 'T':
      return TERABYTES;
    default:
      return BYTES;
    }
}

/**
 * Gets the parent path of the given path, or returns -1 if the given
 * path has no parent. The result is returned in parent.
 */
int
get_parent (const char *path, char *parent)
{
  if (strcmp (path, "/") == 0)
    return -1;

  int lastslash = 0;
  int i = strlen (path) - 1;

  /* The idea here is to remove everything up to and including the
     final '/', when the string is traversed from right to left. */
  for (; i >= 0; i--)
    {
      if (path[i] == '/')
	{
	  lastslash = i;
	  break;
	}
    }

  if (lastslash == 0)
    strcpy (parent, "/\0");
  else
    {
      strncpy (parent, path, lastslash);
      parent[lastslash] = '\0';
    }

  return 0;
}

unsigned long
min (unsigned long l1, unsigned long l2)
{
  return l1 < l2 ? l1 : l2;
}

void
quota_set (const char *path, unsigned long size, enum units unit)
{
  char value[256];
  int vsize = sprintf (value, "%ld", (long) (size * unit));

  if (lsetxattr (path, "user.quota", value, vsize, 0) != 0)
    error ("quota_set_lsetxattr");
}

long double
quota_get (const char *path, enum units unit)
{
  char value[256];
  ssize_t len = lgetxattr (path, "user.quota", value, 256);

  if (len < 0)
    if(errno != ENODATA)
      error ("quota_get_lgetxattr");
    else
      return 0;
  else
    value[len] = '\0';

  long double size = (long double) atol (value);
  return size / unit;
}

/**
 * Gets the value of the quota at the given path. If a parent path has
 * a stricter quota, that quota prevails. The path with the strictest
 * quota is returned as binding_quota.
 */
long double
quota_get_binding (const char *path, enum units unit, char *binding_quota)
{
  unsigned long min_so_far = 0;

  strcpy (binding_quota, path);

  char current_path[PATH_MAX];
  strcpy (current_path, path);

  /* Only loop until we reach the root of the current filesystem. */
  while (strcmp ((char *) fuse_get_context ()->private_data, current_path) !=
	 0)
    {
      unsigned long current_quota = quota_get(current_path, BYTES);

      if ((min_so_far == 0 && current_quota != 0)
	  || (current_quota < min_so_far))
	{
	  min_so_far = current_quota;
	  strcpy (binding_quota, current_path);
	}

      char parent_path[PATH_MAX];
      if (get_parent (current_path, parent_path) == -1)
	{
	  printf ("This should never happen.\n");
	  return min_so_far;
	}

      printf ("Parent path: %s\n", parent_path);

      strcpy (current_path, parent_path);
    }

  /* For the root path */
  unsigned long current_quota = quota_get(current_path, BYTES);

  if ((min_so_far == 0 && current_quota != 0) || (current_quota < min_so_far))
    {
      min_so_far = current_quota;
      strcpy (binding_quota, current_path);
    }

  return min_so_far / unit;
}

/**
 * Determines if a write can succeed under the quota restrictions.
 */
int
quota_exceeded (const char *path)
{
  char binding_quota[PATH_MAX];

  unsigned long quota =
    (unsigned long) quota_get_binding (path, BYTES, binding_quota);

  if (quota == 0)
    return 0;

  unsigned long size = space (binding_quota);

  if (size >= quota)
    return -1;

  return 0;
}


void
quota_unset (const char *path)
{
  if (lremovexattr (path, "user.quota") != 0)
    if (errno != ENOATTR)
      error ("quota_unset_lremovexattr");
}
