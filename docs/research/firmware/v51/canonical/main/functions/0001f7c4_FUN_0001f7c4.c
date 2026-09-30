/* Address: 0001f7c4; name: FUN_0001f7c4; body bytes: 284 */

void FUN_0001f7c4(uint param_1)

{
  uint uVar1;
  
  if (param_1 < DAT_1fffaaa8) {
    DAT_1fffaaa8 = DAT_1fffaaa8 - param_1;
  }
  else {
    DAT_1fffaaa8 = 100;
    DAT_1fffaa78 = DAT_1fffaa78 + 100;
    if (DAT_1fffaa6e < DAT_1fffaa78) {
      DAT_1fffaa78 = DAT_1fffaa6e;
    }
  }
  if (DAT_1fffaaad != '\x05') {
    if (DAT_1fffaa72 <= DAT_1fffaa68) {
      DAT_1fffaaac = 4;
    }
    return;
  }
  uVar1 = (uint)DAT_1fffaa80;
  if (param_1 < DAT_1fffaac8) {
    DAT_1fffaac8 = DAT_1fffaac8 - param_1;
  }
  else if (DAT_1fffaa5c == '\0') {
    if (DAT_1fffaab8 < uVar1) {
      DAT_1fffaac4 = 0;
      DAT_1fffaab8 = DAT_1fffaa80;
    }
    if (DAT_1fffaabc + uVar1 < (uint)DAT_1fffaab8) {
      DAT_1fffaab5 = DAT_1fffaab5 + 1;
      if (DAT_1fffaab5 < 3) {
        DAT_1fffaac8 = 0x1d4c;
      }
      else {
        DAT_1fffaab4 = 1;
        DAT_1fffaaac = 6;
      }
    }
    else {
      DAT_1fffaab5 = 0;
      DAT_1fffaac8 = 30000;
    }
    if (uVar1 < (uint)((short)(ushort)DAT_1fffaa61 * 0x5dc)) {
      DAT_1fffaab6 = 0;
    }
    else {
      DAT_1fffaab6 = DAT_1fffaab6 + 1;
      if (3 < DAT_1fffaab6) {
        DAT_1fffaab4 = 2;
        DAT_1fffaaac = 6;
      }
    }
    DAT_1fffaa5c = '\x01';
  }
  else {
    DAT_1fffaa5c = '\0';
    DAT_1fffaac8 = 1000;
  }
  if (0x9c3 < DAT_1fffaa90) {
    DAT_1fffaab4 = 3;
    DAT_1fffaaac = 6;
  }
  if (DAT_1fffaaba <= uVar1) {
    DAT_1fffaaba = DAT_1fffaa80;
    DAT_1fffaac4 = 0;
    return;
  }
  DAT_1fffaac4 = param_1 + DAT_1fffaac4;
  if (899999 < DAT_1fffaac4) {
    DAT_1fffaab4 = 4;
    DAT_1fffaaac = 6;
  }
  return;
}

