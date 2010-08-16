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

enum units char_to_units(const char c);

void quota_set(const char* path, unsigned long size, enum units unit);
long double quota_get(const char* path, enum units unit);
long double quota_get_binding(const char* path, enum units unit, char* binding_path);
int quota_exceeded(const char* path);
void quota_unset(const char* path);

#endif /* QUOTA_H */
