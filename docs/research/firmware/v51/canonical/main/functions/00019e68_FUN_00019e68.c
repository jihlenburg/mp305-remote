/* Address: 00019e68; name: FUN_00019e68; body bytes: 170 */

void FUN_00019e68(short param_1)

{
  uint uVar1;
  
  if (DAT_1fffa950 == voltage_requested_raw) goto LAB_00019ebc;
  uVar1 = voltage_requested_raw;
  if (DAT_1fffaa35 != '\0') {
    if (DAT_1fffaa12 == 0) {
      uVar1 = DAT_1fffaa1a / 10;
      if (DAT_1fffa950 < voltage_requested_raw) {
        DAT_1fffa950 = uVar1 + DAT_1fffa950;
        if (voltage_requested_raw < DAT_1fffa950) {
LAB_00019ea6:
          DAT_1fffa950 = voltage_requested_raw;
        }
      }
      else {
        if (uVar1 < DAT_1fffa950) {
          DAT_1fffa950 = DAT_1fffa950 - uVar1;
        }
        else {
          DAT_1fffa950 = 0;
        }
        if (DAT_1fffa950 < voltage_requested_raw) goto LAB_00019ea6;
      }
    }
    DAT_1fffaa12 = DAT_1fffaa12 + param_1;
    uVar1 = DAT_1fffa950;
    if (DAT_1fffaa12 < 100) goto LAB_00019ebc;
  }
  DAT_1fffa950 = uVar1;
  DAT_1fffaa12 = 0;
LAB_00019ebc:
  if (DAT_1fffa954 == current_requested_raw) {
    if ((DAT_1fffaa2e != '\0') && (current_requested_raw <= (uint)((DAT_1fffa968 + 500) / 1000))) {
      DAT_1fffaa14 = param_1 + DAT_1fffaa14;
      if (((int)(uint)DAT_1fffaa1c <= (int)DAT_1fffaa14) && (DAT_1fffaa36 != '\0')) {
        DAT_1fffaa1e = DAT_1fffaa1e | 0x20;
      }
      return;
    }
  }
  else {
    DAT_1fffa954 = current_requested_raw;
  }
  DAT_1fffaa14 = 0;
  return;
}

