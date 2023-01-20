#include <stdint.h>
#include <string.h>

static unsigned char smash[];

#include "smash.inc"

// We set the size of buffer to the smallest multiple of sizeof(uintptr_t).
// This prevents alignment issues.
#define BUFFER_SIZE    \
  (sizeof(uintptr_t) * \
   ((sizeof(smash) + sizeof(uintptr_t) - 1) / sizeof(uintptr_t)))
#define PAYLOAD_SIZE (BUFFER_SIZE + 2 * sizeof(uintptr_t))

// The payload is zero-initialized.
static unsigned char payload[PAYLOAD_SIZE] = {};

int main() {
  // The poor victim that will get overflowed.
  char buffer[BUFFER_SIZE];

  // Initialize the payload.
  memcpy(payload, smash, sizeof(smash));
  // Overwrite the saved rip value to the address of buffer, which will contain
  // the code copied from smash. We skip rbp by adding an additional
  // sizeof(uintptr_t).
  *(uintptr_t *)(payload + sizeof(buffer) + sizeof(uintptr_t)) =
      (uintptr_t)buffer;

  // Oops - stack buffer overflow!
  memcpy(buffer, payload, sizeof(payload));
}
