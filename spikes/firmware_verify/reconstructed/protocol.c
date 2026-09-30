/* Offline reconstruction of selected MP305B V51 routines.
 * This is research code, kept in a research spike outside the Cargo workspace.
 * Offsets are processor addresses in the main image loaded at 0x10000.
 * Preconditions follow the firmware: caller supplies full input and output
 * buffers.
 */
#include "state.h"
#include <stddef.h>
#include <stdint.h>

static uint16_t read16(const uint8_t *p) {
  return (uint16_t)(p[0] | ((uint16_t)p[1] << 8));
}
static void write16(uint8_t *p, uint16_t v) {
  p[0] = (uint8_t)v;
  p[1] = (uint8_t)(v >> 8);
}

/* Reconstructs 0x1caa4. The state byte array starts at 0x1fffaacc.
 * Writes before a later validation failure are preserved by the original code.
 * Request byte 5 is checked but never copied to state offset 0x2f.
 * Firmware byte 0x48 is set only after the final field succeeds.
 */
size_t reconstructed_c6(uint8_t *state, const uint8_t *request, size_t length,
                        uint8_t *reply, uint8_t type) {
  uint8_t status = 0;
  reply[0] = (uint8_t)(request[0] + 1);
  if (request[1] >= 80 && request[1] <= 100)
    state[STATE_CHARGE_LIMIT] = request[1];
  else
    status = 255;
  if (status == 0 && request[2] <= 3)
    state[STATE_VOLUME] = request[2];
  else
    status = 255;
  if (status == 0 && request[3] <= 1)
    state[STATE_SCREEN_OFF] = request[3];
  else
    status = 255;
  if (status == 0 && request[4] <= 30)
    state[STATE_SHUTDOWN] = request[4];
  else
    status = 255;
  if (status != 0 || request[5] > 1)
    status = 255;
  if (status == 0 && read16(request + 6) <= 1000)
    write16(state + STATE_SLOPE, read16(request + 6));
  else
    status = 255;
  if (status == 0 && read16(request + 8) <= 1000)
    write16(state + STATE_OCP_DELAY, read16(request + 8));
  else
    status = 255;
  if (status == 0 && request[10] <= 1)
    state[STATE_SYSTEM_FLAG] = request[10];
  else
    status = 255;
  if (status == 0 && request[11] <= 1)
    state[STATE_RECOVERY_FLAG] = request[11];
  else
    status = 255;
  if (status == 0 && read16(request + 12) <= 1000) {
    write16(state + STATE_USB_LINE, read16(request + 12));
    state[STATE_SETTINGS_DIRTY] = 1;
  } else
    status = 255;
  reply[1] = status;
  if (type == 6) {
    reply[2] = request[length - 1];
    return 3;
  }
  return 2;
}

/* Reconstructs 0x15430 / 0x1fedc and helper 0x1fff0.
 * Slot bytes: source nibble, destination nibble, length, unused, opcode and
 * data.
 */
static uint8_t *append(uint8_t *out, uint8_t v) {
  *out++ = v;
  if (v == 0xaa)
    *out++ = v;
  return out;
}
size_t reconstructed_encode(const uint8_t *slot, uint8_t *out) {
  uint8_t *p = out;
  uint8_t address = (uint8_t)((slot[0] << 4) | (slot[1] & 15));
  uint8_t checksum = (uint8_t)(address + slot[2]);
  *p++ = 0xaa;
  p = append(p, address);
  p = append(p, slot[2]);
  for (unsigned i = 0; i < slot[2]; ++i) {
    checksum = (uint8_t)(checksum + slot[4 + i]);
    p = append(p, slot[4 + i]);
  }
  p = append(p, checksum);
  return (size_t)(p - out);
}
