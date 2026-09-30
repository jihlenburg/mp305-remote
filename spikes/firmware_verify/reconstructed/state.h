/* Selected offsets in the V51 main state block at 0x1fffaacc.
 * Names describe observed software use. They do not establish physical units.
 * This is a byte view because the complete original C structure is unknown.
 */
#ifndef MP305_RESEARCH_STATE_H
#define MP305_RESEARCH_STATE_H
enum main_state_offset {
  STATE_CHARGE_LIMIT = 0x2d,
  STATE_SCREEN_OFF = 0x2e,
  STATE_SCREEN_DIRECTION = 0x2f,
  STATE_MODE = 0x30,
  STATE_REQUESTED_MODE = 0x31,
  STATE_VOLUME = 0x32,
  STATE_SHUTDOWN = 0x33,
  STATE_SYSTEM_FLAG = 0x35,
  STATE_RECOVERY_FLAG = 0x36,
  STATE_REMOTE_GRANTED = 0x42,
  STATE_REMOTE_REQUEST = 0x45,
  STATE_REMOTE_DECISION = 0x46,
  STATE_REMOTE_PENDING = 0x47,
  STATE_SETTINGS_DIRTY = 0x48,
  STATE_CONTROL_DIRTY = 0x49,
  STATE_SLOPE = 0x96,
  STATE_OCP_DELAY = 0x98,
  STATE_USB_LINE = 0xa4
};
#endif
