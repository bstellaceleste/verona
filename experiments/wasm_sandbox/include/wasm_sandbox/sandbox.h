#pragma once

#include <cstddef>

namespace sandbox {

class Library {

private:
  /**
   * The first unused vtable entry.  When a sandboxed library is created, all
   * of the functions register themselves at a specific index.
   *
   * The first vtable entry is reserved for the function that returns the
   * type encoding of a specific vtable entry.  This is used to ensure that
   * the child and parent agree on the type signatures of all exported
   * functions.
   */
  int last_vtable_entry = 1;

public:
  virtual void send(int index, void *ptr) = 0;

  virtual void *alloc_in_sandbox(size_t bytes, size_t count = 1) = 0;

  virtual void free_in_sandbox(void *ptr) = 0;

  /**
   * Returns the next vtable entry to use, incrementing the counter so
   * subsequent calls will always return a fresh value.
   */
  int next_vtable_entry() { return last_vtable_entry++; }
};
} // namespace sandbox.
