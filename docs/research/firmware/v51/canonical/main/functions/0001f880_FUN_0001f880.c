/* Address: 0001f880; name: FUN_0001f880; body bytes: 76 */

void FUN_0001f880(uint param_1)

{
  if (param_1 < DAT_1fffaaa8) {
    DAT_1fffaaa8 = DAT_1fffaaa8 - param_1;
  }
  else {
    DAT_1fffaaa8 = 100;
    DAT_1fffaa78 = DAT_1fffaa78 + 100;
  }
  if (DAT_1fffaaad == '\x05') {
    if (DAT_1fffaa6e <= DAT_1fffaa78) {
      DAT_1fffaa78 = DAT_1fffaa6e;
      DAT_1fffaaac = 3;
      return;
    }
  }
  else {
    if (DAT_1fffaa6e <= DAT_1fffaa78) {
      DAT_1fffaaac = 3;
    }
    if (DAT_1fffaa72 <= DAT_1fffaa68) {
      DAT_1fffaaac = 4;
    }
  }
  return;
}

