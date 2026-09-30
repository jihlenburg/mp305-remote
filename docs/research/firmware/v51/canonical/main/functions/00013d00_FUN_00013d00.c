/* Address: 00013d00; name: FUN_00013d00; body bytes: 98 */

void FUN_00013d00(undefined4 param_1)

{
  FUN_0001fbb0();
  switch(DAT_1fffaaac) {
  case 0:
    FUN_0001d858();
    break;
  case 1:
  case 2:
  case 3:
  case 4:
  case 6:
    FUN_0001f9b8();
    FUN_0001f6c4(param_1);
    break;
  default:
    DAT_1fffaaac = 0;
  }
  set_voltage_raw(DAT_1fffaa7a / 10);
  set_current_raw(DAT_1fffaa86);
  FUN_0001aebc(DAT_1fffaa5c);
  if (DAT_1fffaa86 == 0) {
    FUN_0001aebc();
    return;
  }
  return;
}

