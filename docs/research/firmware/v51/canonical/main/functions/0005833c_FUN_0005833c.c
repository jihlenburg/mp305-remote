/* Address: 0005833c; name: FUN_0005833c; body bytes: 42 */

void FUN_0005833c(undefined4 param_1)

{
  if (DAT_1fffaad7 != '\0') {
    FUN_000569b8();
    set_current_raw(param_1);
    return;
  }
  FUN_00058268(param_1);
  set_voltage_raw(param_1);
  return;
}

