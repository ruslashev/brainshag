#pragma once

#include <string>

void die(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n");

  exit(0);
}

std::string get_file_contents(std::string filename)
{
  FILE *fd = fopen(filename.c_str(), "r");
  if (!fd)
    die("Failed to open file \"%s\": %s", filename.c_str(), strerror(errno));

  if (fseek(fd, 0L, SEEK_END) != 0)
    die("Failed to seek end of file \"%s\": %s", filename.c_str(), strerror(errno));

  size_t flen = ftell(fd);
  if (flen == -1)
    die("Failed to get file \"%s\" length: %s", filename.c_str(), strerror(errno));

  char *contents_cbuffer = new char [flen + 1];

  if (fseek(fd, 0L, SEEK_SET) != 0)
    die("Failed to seek start of file \"%s\": %s", filename.c_str(), strerror(errno));

  size_t readlen = fread(contents_cbuffer, sizeof(char), flen, fd);
  if (readlen == 0)
    die("Failed to read file \"%s\": %s", filename.c_str(), strerror(errno));
  contents_cbuffer[readlen++] = 0;

  std::string contents_string(contents_cbuffer);

  delete [] contents_cbuffer;

  fclose(fd);

  return contents_string;
}
