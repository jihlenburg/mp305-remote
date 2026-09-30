/* Address: 0001aea4; name: set_current_raw; body bytes: 20 */

/* Stores the requested raw current at 0x1fffa944 inside a critical section. */

void set_current_raw(undefined4 param_1)

{
  enter_critical();
  current_requested_raw = param_1;
  exit_critical();
  return;
}

