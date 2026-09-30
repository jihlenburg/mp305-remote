/* Address: 0001fb4c; name: FUN_0001fb4c; body bytes: 96 */

void FUN_0001fb4c(uint param_1)

{
  uint uVar1;
  
  if ((DAT_1fffaaad != '\x05') && (DAT_1fffaaad != '\x03')) {
    if (param_1 < DAT_1fffaaa8) {
      DAT_1fffaaa8 = DAT_1fffaaa8 - param_1;
      return;
    }
    DAT_1fffaaa8 = 100;
    if ((uint)DAT_1fffaa68 < DAT_1fffaa72 + 5) {
      if ((uint)DAT_1fffaa72 < DAT_1fffaa68 + 5) {
        DAT_1fffaaa8 = 100;
        return;
      }
      uVar1 = ((uint)DAT_1fffaa78 * 0x65) / 100;
      if ((uVar1 & 0xffff) != 0) {
        DAT_1fffaa78 = (short)uVar1;
        DAT_1fffaaa8 = 100;
        return;
      }
      DAT_1fffaa78 = 1;
      return;
    }
    uVar1 = ((uint)DAT_1fffaa78 * 0x62) / 100;
    if ((uVar1 & 0xffff) != 0) {
      DAT_1fffaa78 = (short)uVar1;
      DAT_1fffaaa8 = 100;
      return;
    }
  }
  DAT_1fffaa78 = 0;
  return;
}

