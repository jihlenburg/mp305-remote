/* Address: 0001af64; name: set_voltage_raw; body bytes: 20 */

/* Stores the requested raw voltage at 0x1fffa940 inside a critical section. */

void set_voltage_raw(undefined4 param_1)

{
  enter_critical();
  voltage_requested_raw = param_1;
  exit_critical();
  return;
}

