/* Address: 0001f5c0; name: FUN_0001f5c0; body bytes: 78 */

void FUN_0001f5c0(uint param_1)

{
  if (DAT_1fffaaad != '\x05') {
    if (param_1 < DAT_1fffaaa8) {
      DAT_1fffaaa8 = DAT_1fffaaa8 - param_1;
    }
    else {
      DAT_1fffaaa8 = 100;
      DAT_1fffaa78 = DAT_1fffaa78 + 100;
    }
    if (DAT_1fffaa7c <= DAT_1fffaa78) {
      DAT_1fffaa78 = DAT_1fffaa7c;
    }
    if (DAT_1fffaa74 <= DAT_1fffaa6a) {
      DAT_1fffaaac = 2;
    }
    if (DAT_1fffaa72 <= DAT_1fffaa68) {
      DAT_1fffaaac = 4;
    }
    return;
  }
  DAT_1fffaaac = 2;
  return;
}

