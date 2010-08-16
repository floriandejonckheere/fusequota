/**
 * Project: fusequota
 * File: space.c
 * License: IBM Public License 1.0
 *
 * This file provides a means for computing the amount of space
 * used by a file or directory.
 */
#define _XOPEN_SOURCE 500

#include "space.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/statfs.h>
#include <sys/types.h>

long entry_size(const char* path);

/**
 * Computes the size of the directory at the given path.
 */
unsigned long directory_size(const char* path)
{
  struct statfs sfs;
  if(statfs(path, &sfs) != 0)
  {
    if(errno == EACCES)
      return 0;

    error("directory_size.statfs");
  }
  else if(sfs.f_type == 0x9fa0)    /* Ignore the proc filesystem. */
    return 0;

  /* Change the directory to the current path, so we can
     use relative paths. */
  if(chdir(path) != 0)
  {
    if(errno == EACCES)
      return 0;

    error("From directory_size.chdir");
  }

  /* Open the current directory, so we can enumerate its contents. */
  DIR* dir = opendir(".");

  if(dir == NULL)
  {
    if(errno == EACCES)
      return 0;

    error("directory_size.opendir");
  }

  struct dirent* ent = NULL;
  unsigned long size = 0;

  /* For each entry in the current directory, account for its size. */
  while((ent = readdir(dir)) != NULL)
  {
    /* Don't bother with the current directory or the parent directory. */
    if((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0))
      continue;

    /* This call takes care of recursing down the filesystem. */
    size += entry_size(ent->d_name);
  }

  /* Return to the parent directory. */
  if(chdir("..") != 0)
    error("directory_size.chdir");

  if(closedir(dir) != 0)
    error("directory_size.closedir");

  return size;
}

/**
 * Computes the size of the filesystem entry at the given path.
 */
long entry_size(const char* path)
{
  struct stat buf;
  if(lstat(path, &buf) != 0)
    return -1;

  /* If the entry is a directory, we need to enumerate its contents
     and recurse. Otherweise, we can get the size information from
     lstat directly. */
  if(S_ISDIR(buf.st_mode))
    return buf.st_size + directory_size(path);
  else
    return buf.st_size;
}

/**
 * Computes the amount of space on the filesystem taken up by
 * the file or directory at the given path.
 */
unsigned long space(const char* path)
{
  char fpath[PATH_MAX];
  if(realpath(path, fpath) == NULL)
    error("main.realpath");

  long size = entry_size(fpath);

  if(size < 0)
    error("main.entry_size");

  return (unsigned long) size;
}
