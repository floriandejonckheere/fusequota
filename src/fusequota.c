#define _XOPEN_SOURCE 500

#include "fuse_ops.h"
#include "quota.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>

#include <limits.h>
#include <fuse.h>
#include <string.h>
#include <unistd.h>

struct fuse_operations fuse_ops = {
  .getattr	= fuse_getattr,
  .readlink     = fuse_readlink,
  .mknod        = fuse_mknod,
  .mkdir        = fuse_mkdir,
  .unlink       = fuse_unlink,
  .rmdir        = fuse_rmdir,
  .symlink      = fuse_symlink,
  .rename       = fuse_rename,
  .link         = fuse_link,
  .chmod        = fuse_chmod,
  .chown        = fuse_chown,
  .truncate     = fuse_truncate,
  .utime        = fuse_utime,
  .open         = fuse_open,
  .read         = fuse_read,
  .write        = fuse_write,
  .statfs       = fuse_statfs,
  .release      = fuse_release,
  .fsync        = fuse_fsync,
  .setxattr     = fuse_setxattr,
  .getxattr     = fuse_getxattr,
  .listxattr    = fuse_listxattr,
  .removexattr  = fuse_removexattr,
  .opendir      = fuse_opendir,
  .readdir      = fuse_readdir,
  .releasedir   = fuse_releasedir,
  .access       = fuse_access,
  .init         = fuse_init,
};

void usage()
{
  printf("fusequota set <path> <size> [-u<B|K|M|G|T>]\n");
  printf("fusequota get <path> [-u<B|K|M|G|T>]\n");
  printf("fusequota unset <path>\n");

  printf("fusequota mount <mountpoint> <basedir>\n");

  exit(0);
}

void set()
{
  
}

int main(int argc, char* argv[])
{
  if(argc < 3)
    usage();

  char* command = argv[1];
  char* path = argv[2];

  char fpath[PATH_MAX];
  if(realpath(path, fpath) == NULL)
    error("main_realpath");

  if(strcmp(command, "set") == 0)
  {
    if(argc < 4)
      usage();

    int c = getopt(argc, argv, "u:");
    enum units unit = (c < 0) ? BYTES : char_to_units(optarg[0]);

    unsigned long size = (unsigned long) atol(argv[3]);

    quota_set(fpath, size, unit);
  }
  else if(strcmp(command, "get") == 0)
  {
    int c = getopt(argc, argv, "u:");
    enum units unit = (c < 0) ? BYTES : char_to_units(optarg[0]);

    long double size = quota_get(fpath, unit);

    printf("%Lf\n", size);
  }
  else if(strcmp(command, "unset") == 0)
    quota_unset(fpath);
  else if(strcmp(command, "mount") == 0)
  {
    if(argc < 4)
      usage();

    char base[PATH_MAX];
    if(realpath(argv[2], base) == NULL)
      error("main_realpath");

    int i = 1;
    for(; i < argc; i++)
      argv[i] = argv[i + 2];
    argc -= 2;

    int ret = fuse_main(argc, argv, &fuse_ops, base);

    if(ret < 0)
      error("fuse_main");

    return ret;
  }
  else
    usage();

  return 0;
}
