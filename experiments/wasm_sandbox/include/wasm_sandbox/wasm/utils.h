#pragma once

#include "WAVM/IR/Types.h"
#include <cerrno>
#include <cinttypes>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

namespace sandbox::backend::utils {
bool readFile(const char *path, std::vector<WAVM::U8> &outBytes) {
  FILE *file = fopen(path, "rb");
  if (!file) {
    fprintf(stderr, "Failed to open '%s' for reading: %s\n", path,
            strerror(errno));
    return false;
  }

  if (fseek(file, 0, SEEK_END)) {
    fprintf(stderr, "Failed to seek to end of '%s': %s\n", path,
            strerror(errno));
    return false;
  }

  const long numBytes = ftell(file);
  if (numBytes < 0) {
    fprintf(stderr, "Failed to query position in '%s': %s\n", path,
            strerror(errno));
    return false;
  }
  const unsigned long numBytesUnsigned = (unsigned long)numBytes;

  if (fseek(file, 0, SEEK_SET)) {
    fprintf(stderr, "Failed to seek to beginning of '%s': %s\n", path,
            strerror(errno));
    return false;
  }

  outBytes.resize(numBytesUnsigned);

  size_t numBytesRead = fread(outBytes.data(), 1, numBytesUnsigned, file);
  if (numBytesRead != numBytesUnsigned) {
    fprintf(stderr, "Failed to read %lu bytes from '%s': %s\n",
            numBytesUnsigned, path, strerror(errno));
    return false;
  }

  if (fclose(file)) {
    fprintf(stderr, "Failed to close '%s': %s\n", path, strerror(errno));
    return false;
  }
  return true;
}

} // namespace sandbox::backend::utils
