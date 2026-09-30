/* Readable reconstructions of two bounded V51 operations.
 * These functions have no device I/O and are compared with original ARM code.
 * They preserve observed arithmetic and packet behavior, including edge cases.
 */
#include <stddef.h>
#include <stdint.h>
#include <string.h>

/* Main 0x19116: pack the ten-bit external reference into registers 3 and 4.
 * The endpoint is inferred to be SC8815-compatible. Input scaling is not
 * asserted here. Unsigned underflow at zero deliberately matches the image.
 */
void reconstructed_reference_registers(uint32_t target, uint8_t out[2]) {
  uint32_t code = (target * 5u + 5u) / 10u - 1u;
  if (code > 1023u) {
    code = 1023u;
  }
  out[0] = (uint8_t)(code >> 2);
  out[1] = (uint8_t)((code & 3u) << 6);
}

/* Main 0x15ca0: one deferred D9 program-record reply.
 * Preconditions: records contains record_count entries of twelve bytes,
 * cursor is valid, and reply can hold 123 bytes. Slot validation and storage
 * loading belong to the preceding D8 request and worker, outside this routine.
 * route_kind 6 retains an internal route suffix, stripped by the BLE bridge.
 */
size_t reconstructed_d9(const uint8_t *records, uint8_t record_count,
                        uint8_t program_id, uint8_t *cursor, uint8_t route_kind,
                        uint8_t route_suffix, uint8_t *reply) {
  size_t size = 2;
  unsigned copied = 0;
  reply[0] = 0xd9;
  reply[1] = program_id;
  while (*cursor < record_count && copied < 10) {
    memcpy(reply + size, records + (size_t)*cursor * 12, 12);
    size += 12;
    ++*cursor;
    ++copied;
  }
  if (route_kind == 6) {
    reply[size++] = route_suffix;
  }
  return size;
}
